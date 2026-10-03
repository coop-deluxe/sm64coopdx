#include <SDL3/SDL.h>

#include "types.h"

#include "gfx_sdl_gpu.h"

#include "pc/pc_main.h"
#include "pc/configfile.h"
#include "pc/debuglog.h"
#include "pc/lua/smlua.h"
#include "pc/mods/mods_utils.h"

#include "gfx_window_manager.h"
#include "gfx_rendering_api.h"
#include "gfx_pc.h"
#include "gfx_shader.h"

#if defined(_WIN32)
#include <d3dcompiler.h>
#endif

#define DEBUG_SDL_GPU true

#define MAX_FRAMES_IN_FLIGHT 3
#define START_VERTEX_BUFFER_SLOT_SIZE (4 * 1024 * 1024)
#define MAX_VERTEX_BUFFER_SLOT_SIZE (32 * 1024 * 1024)

#if SDL_VERSION_ATLEAST(3, 4, 0)
static SDL_GPUVulkanOptions sVulkanOptions = { .vulkan_api_version = (1u << 22) | (2u << 12) };
#endif

static SDL_GPUShaderFormat sShaderFormat = SDL_GPU_SHADERFORMAT_SPIRV;
static SDL_GPUDevice *sGpuDevice = NULL;
static SDL_Window *sSdlWindow = NULL;
static SDL_GPUCommandBuffer *sCmdBuffer = NULL;
static SDL_GPUCommandBuffer *sUploadCmdBuffer = NULL;
static SDL_GPURenderPass *sRenderPass = NULL;
static SDL_GPUTexture *sDepthTexture = NULL;
static u32 sCurrDepthTexWidth = 0;
static u32 sCurrDepthTexHeight = 0;
static SDL_GPUTexture *sSwapchainTex = NULL;
static SDL_GPUTextureFormat sSwapchainFormat = SDL_GPU_TEXTUREFORMAT_INVALID;
static SDL_GPUPresentMode sPresentMode = SDL_GPU_PRESENTMODE_VSYNC;

struct CachedRenderPassInfo {
    SDL_GPUTexture *colorTex;
    SDL_GPUTexture *depthTex;
    f32 clearColor[4];
    bool cleared;
};

static struct CachedRenderPassInfo sCachedRenderPassInfo = { 0 };

struct InternalTexture {
    const char *name;
    SDL_GPUTextureSamplerBinding textureSamplerBinding;
    u32 width;
    u32 height;
    enum TextureFilter filter;
};

static struct InternalTexture sInternalTextures[MAX_SHADER_SAMPLERS] = { 0 };
static u32 sInternalTexturesCount = 0;

struct GpuRingBuffer {
    SDL_GPUBuffer *gpuBuffer;
    SDL_GPUTransferBuffer *transferBuffer;
    u8 *mappedData;
    u32 maxSlotSize;
    u32 slotSize;
    u32 slot;
    u32 currentOffset;
    u32 startOffset;
};

static struct GpuRingBuffer sVertexRingBuffer = { 0 };

struct TextureData {
    SDL_GPUTexture *texture;
    SDL_GPUSampler *sampler;
    const Texture *addr;
    u32 width;
    u32 height;
    bool linearFilter;
    u32 cms;
    u32 cmt;
};

struct ShaderProgramSdlGpu {
    SDL_GPUGraphicsPipeline *pipelines[2][2][2][GPU_CULL_MODE_COUNT];
    SDL_GPUShader *sdlVertexShader;
    SDL_GPUShader *sdlFragmentShader;
    struct Shader *vertexShader;
    struct Shader *fragmentShader;
    u64 hash;
    u8 numInputs;
    bool usedTextures[MAX_TEXTURES];
    bool usedFog;
};

static struct ShaderProgramSdlGpu sShaderProgramPool[MAX_FRAME_PASSES][CC_MAX_SHADERS];
static u8 sShaderProgramPoolSize[MAX_FRAME_PASSES] = { 0 };
static u8 sShaderProgramPoolIndex[MAX_FRAME_PASSES] = { 0 };

static struct ShaderProgramSdlGpu sPostProcessShaderProgramPool[MAX_FRAME_PASSES];

static struct ShaderProgramSdlGpu *sShaderProgram = NULL;

static u32 sRenderWidth = 0;
static u32 sRenderHeight = 0;

static struct TextureData *sTextureCache = NULL;
static u32 sTextureCacheCapacity = 0;
static u32 sTextureCacheCount = 0;

static SDL_GPUTextureSamplerBinding sLastSamplerBindings[MAX_SHADER_SAMPLERS];
static u32 sLastSamplerBindingsCount = 0;

static const char *sVanillaTexUniformNames[MAX_TEXTURES] = { "uTex0", "uTex1" };
static const char *sTexSizeUniformNames[MAX_TEXTURES] = { "uTex0Size", "uTex1Size" };
static const char *sTexFilterUniformNames[MAX_TEXTURES] = { "uTex0Filter", "uTex1Filter" };

static s32 sCurrentTile = 0;
static u32 sCurrentTextureIds[MAX_TEXTURES] = { 0 };

static SDL_GPUSampler *sLinearClampSampler = NULL;
static SDL_GPUSampler *sNearestClampSampler = NULL;
static SDL_GPUSampler *sLinearClampDepthSampler = NULL;
static SDL_GPUSampler *sNearestClampDepthSampler = NULL;

static SDL_GPUTextureSamplerBinding sFallbackTextureBinding;

static bool sSwapchainCleared = false;
static bool sFramePassCleared[MAX_FRAME_PASSES] = { false };

static bool sDepthTest = false;
static bool sDepthMask = false;
static bool sZModeDecal = false;

static SDL_GPUCullMode sCullingMap[GPU_CULL_MODE_COUNT] = {
    [GPU_CULL_MODE_NONE]  = SDL_GPU_CULLMODE_NONE,
    [GPU_CULL_MODE_BACK]  = SDL_GPU_CULLMODE_BACK,
    [GPU_CULL_MODE_FRONT] = SDL_GPU_CULLMODE_FRONT
};

static struct ShaderUniformBlock *sPushedUniformBlocks[2][MAX_UNIFORM_BLOCKS] = { 0 };

static SDL_GPUGraphicsPipeline *sLastPipeline = NULL;
static struct ShaderProgramSdlGpu *sLastCachedProgram = NULL;

static bool sStartedFrame = false;

#if defined(_WIN32)
static HMODULE sD3dCompilerModule = NULL;
static pD3DCompile sD3dCompile = NULL;

static bool gfx_sdl_gpu_load_d3d_compiler(void) {
    if (sD3dCompile != NULL) { return true; }

    if (sD3dCompilerModule == NULL) {
        sD3dCompilerModule = LoadLibraryW(L"D3DCompiler_47.dll");
        if (sD3dCompilerModule == NULL) {
            sD3dCompilerModule = LoadLibraryW(L"D3DCompiler_43.dll");
        }
        if (sD3dCompilerModule == NULL) { return false; }
    }

    sD3dCompile = (pD3DCompile)(void *)GetProcAddress(sD3dCompilerModule, "D3DCompile");
    return sD3dCompile != NULL;
}
#endif

static const char *gfx_sdl_gpu_driver_for_backend(enum GfxWindowBackend backend) {
    switch (backend) {
#if defined(_WIN32)
        case GFX_WINDOW_BACKEND_DIRECTX:
            return "direct3d12";
        case GFX_WINDOW_BACKEND_VULKAN:
            return "vulkan";
#elif defined(__APPLE__)
        case GFX_WINDOW_BACKEND_METAL:
            return "metal";
#else
        case GFX_WINDOW_BACKEND_VULKAN:
            return "vulkan";
#endif
        default:
            return NULL;
    }
}

static SDL_GPUShaderFormat gfx_sdl_gpu_shader_format_for_backend(enum GfxWindowBackend backend) {
    switch (backend) {
#if defined(_WIN32)
        case GFX_WINDOW_BACKEND_DIRECTX:
            return SDL_GPU_SHADERFORMAT_DXBC;
        case GFX_WINDOW_BACKEND_VULKAN:
            return SDL_GPU_SHADERFORMAT_SPIRV;
#elif defined(__APPLE__)
        case GFX_WINDOW_BACKEND_METAL:
            return SDL_GPU_SHADERFORMAT_MSL;
#else
        case GFX_WINDOW_BACKEND_VULKAN:
            return SDL_GPU_SHADERFORMAT_SPIRV;
#endif
        default:
            return SDL_GPU_SHADERFORMAT_INVALID;
    }
}

static SDL_PropertiesID gfx_sdl_gpu_create_device_properties(enum GfxWindowBackend backend) {
    SDL_GPUShaderFormat format = gfx_sdl_gpu_shader_format_for_backend(backend); // grab shader format
    SDL_PropertiesID props = SDL_CreateProperties();

    // set which shader type to use
    SDL_SetBooleanProperty(props, SDL_PROP_GPU_DEVICE_CREATE_SHADERS_SPIRV_BOOLEAN, format == SDL_GPU_SHADERFORMAT_SPIRV);
    SDL_SetBooleanProperty(props, SDL_PROP_GPU_DEVICE_CREATE_SHADERS_DXBC_BOOLEAN, format == SDL_GPU_SHADERFORMAT_DXBC);
    SDL_SetBooleanProperty(props, SDL_PROP_GPU_DEVICE_CREATE_SHADERS_MSL_BOOLEAN, format == SDL_GPU_SHADERFORMAT_MSL);

    // set debugmode
    SDL_SetBooleanProperty(props, SDL_PROP_GPU_DEVICE_CREATE_DEBUGMODE_BOOLEAN, DEBUG_SDL_GPU);

    // set gpu driver
    SDL_SetStringProperty(props, SDL_PROP_GPU_DEVICE_CREATE_NAME_STRING, gfx_sdl_gpu_driver_for_backend(backend));

    // if possible, set vulkan version to 1.2
#if SDL_VERSION_ATLEAST(3, 4, 0)
    SDL_SetPointerProperty(props, SDL_PROP_GPU_DEVICE_CREATE_VULKAN_OPTIONS_POINTER, &sVulkanOptions);
#endif

    return props;
}

bool gfx_sdl_gpu_is_backend_supported(enum GfxWindowBackend backend) {
    const char *driver = gfx_sdl_gpu_driver_for_backend(backend);
    if (driver == NULL) { return false; }

#if defined(_WIN32)
    if (backend == GFX_WINDOW_BACKEND_DIRECTX && !gfx_sdl_gpu_load_d3d_compiler()) { return false; }
#endif

    if (!SDL_WasInit(SDL_INIT_VIDEO) && !SDL_InitSubSystem(SDL_INIT_VIDEO)) { return false; }

    SDL_PropertiesID props = gfx_sdl_gpu_create_device_properties(backend);
    bool supported = SDL_GPUSupportsProperties(props);
    SDL_DestroyProperties(props);

    return supported;
}

static void gfx_sdl_gpu_reset_ring_buffer_slot(struct GpuRingBuffer *ringBuffer, u32 slot) {
    // set current slot
    ringBuffer->slot = slot;

    // set start offset and current offset to the start offset
    ringBuffer->startOffset = slot * ringBuffer->slotSize;
    ringBuffer->currentOffset = ringBuffer->startOffset;
}

static void gfx_sdl_gpu_create_ring_buffer(struct GpuRingBuffer *ringBuffer, u32 slotSize, u32 maxSize, SDL_GPUBufferUsageFlags usage) {
    // grab total size and set slot size
    u32 size = slotSize * MAX_FRAMES_IN_FLIGHT;
    ringBuffer->slotSize = slotSize;
    ringBuffer->maxSlotSize = maxSize;

    // reset the first slot for use
    gfx_sdl_gpu_reset_ring_buffer_slot(ringBuffer, 0);

    // create gpu buffer
    SDL_GPUBufferCreateInfo bufferInfo = {
        .usage = usage,
        .size = size
    };
    ringBuffer->gpuBuffer = SDL_CreateGPUBuffer(sGpuDevice, &bufferInfo);

    // create transfer buffer for the gpu buffer
    SDL_GPUTransferBufferCreateInfo transferInfo = {
        .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
        .size = size
    };
    ringBuffer->transferBuffer = SDL_CreateGPUTransferBuffer(sGpuDevice, &transferInfo);

    if (!ringBuffer->gpuBuffer || !ringBuffer->transferBuffer) {
        sys_fatal("Failed to allocate ring buffer!");
    }
}

static u8 *gfx_sdl_gpu_map_ring_buffer(struct GpuRingBuffer *ringBuffer) {
    if (ringBuffer->mappedData != NULL) { return ringBuffer->mappedData; }

    // map transfer buffer to gpu device
    ringBuffer->mappedData = (u8 *)SDL_MapGPUTransferBuffer(sGpuDevice, ringBuffer->transferBuffer, false);
    if (!ringBuffer->mappedData) {
        sys_fatal("Failed to map ring buffer: %s", SDL_GetError());
    }

    return ringBuffer->mappedData;
}

static void gfx_sdl_gpu_unmap_ring_buffer(struct GpuRingBuffer *ringBuffer) {
    if (ringBuffer->mappedData == NULL) { return; }

    SDL_UnmapGPUTransferBuffer(sGpuDevice, ringBuffer->transferBuffer);
    ringBuffer->mappedData = NULL;
}

static void gfx_sdl_gpu_release_ring_buffer(struct GpuRingBuffer *ringBuffer) {
    // free transfer buffer
    if (ringBuffer->transferBuffer != NULL) {
        gfx_sdl_gpu_unmap_ring_buffer(ringBuffer);
        SDL_ReleaseGPUTransferBuffer(sGpuDevice, ringBuffer->transferBuffer);
    }

    // free gpu buffer
    if (ringBuffer->gpuBuffer != NULL) {
        SDL_ReleaseGPUBuffer(sGpuDevice, ringBuffer->gpuBuffer);
    }

    // zero out
    memset(ringBuffer, 0, sizeof(*ringBuffer));
}

static void gfx_sdl_gpu_flush_vertex_uploads(void) {
    // unmap transfer buffer
    gfx_sdl_gpu_unmap_ring_buffer(&sVertexRingBuffer);

    // sanity check offsets
    if (sVertexRingBuffer.currentOffset <= sVertexRingBuffer.startOffset) { return; }

    // grab upload command buffer
    if (sUploadCmdBuffer == NULL) {
        sUploadCmdBuffer = SDL_AcquireGPUCommandBuffer(sGpuDevice);
        if (sUploadCmdBuffer == NULL) {
            sys_fatal("Failed to acquire GPU upload command buffer: %s", SDL_GetError());
        }
    }

    // configure transfer buffer location
    SDL_GPUTransferBufferLocation transferSrc = {
        .transfer_buffer = sVertexRingBuffer.transferBuffer,
        .offset = sVertexRingBuffer.startOffset
    };

    // configure the gpu buffer region to upload
    SDL_GPUBufferRegion bufferDst = {
        .buffer = sVertexRingBuffer.gpuBuffer,
        .offset = sVertexRingBuffer.startOffset,
        .size = sVertexRingBuffer.currentOffset - sVertexRingBuffer.startOffset
    };

    // start copy pass, upload to gpu, end copy pass
    SDL_GPUCopyPass *copyPass = SDL_BeginGPUCopyPass(sUploadCmdBuffer);
    SDL_UploadToGPUBuffer(copyPass, &transferSrc, &bufferDst, false);
    SDL_EndGPUCopyPass(copyPass);

    // set the start offset to the current offset
    sVertexRingBuffer.startOffset = sVertexRingBuffer.currentOffset;
}

static bool gfx_sdl_gpu_resize_ring_buffer(struct GpuRingBuffer *ringBuffer, u32 slotBytesNeeded) {
    u32 slotSize = ringBuffer->slotSize;
    while (slotSize < slotBytesNeeded) {
        if (slotSize >= ringBuffer->maxSlotSize) { return false; }
        slotSize *= 2;
    }

    gfx_sdl_gpu_flush_vertex_uploads();

    u32 slot = ringBuffer->slot;
    gfx_sdl_gpu_release_ring_buffer(ringBuffer);
    gfx_sdl_gpu_create_ring_buffer(ringBuffer, slotSize, MAX_VERTEX_BUFFER_SLOT_SIZE, SDL_GPU_BUFFERUSAGE_VERTEX);
    gfx_sdl_gpu_reset_ring_buffer_slot(ringBuffer, slot);

    LOG_INFO("Resized the ring buffer to %u bytes per frame", slotSize);

    return true;
}

static void gfx_sdl_gpu_begin_render_pass(SDL_GPUTexture *colorTex, SDL_GPUTexture *depthTex, f32 clearColor[4], bool cleared);
static void gfx_sdl_gpu_end_render_pass(void);

static void gfx_sdl_gpu_setup_command_buffer(void) {
    if (sCmdBuffer != NULL) { return; }

    // end any render passes that may be in progress
    gfx_sdl_gpu_end_render_pass();

    // create command buffer
    sCmdBuffer = SDL_AcquireGPUCommandBuffer(sGpuDevice);
    if (sCmdBuffer == NULL) {
        sys_fatal("Failed to acquire GPU command buffer: %s", SDL_GetError());
    }
}

static void gfx_sdl_gpu_submit_frame(void);

static bool gfx_sdl_gpu_allocate_to_ring_buffer(struct GpuRingBuffer *ringBuffer, u32 bytesNeeded, u32 *outOffset) {
    // align to 16 bytes
    u32 alignedBytes = (bytesNeeded + 16 - 1) & ~(16 - 1);

    // if a single allocation needed is greater than our slot size, try resizing
    if (alignedBytes > ringBuffer->slotSize) {
        if (!gfx_sdl_gpu_resize_ring_buffer(ringBuffer, alignedBytes)) {
            return false;
        }
    }

    u32 slotEndOffset = (ringBuffer->slot + 1) * ringBuffer->slotSize;

    // if we can't fit in the available space...
    if (ringBuffer->currentOffset + alignedBytes > slotEndOffset) {
        // ... grab the amount of bytes we need to write
        u32 slotBytesNeeded = (ringBuffer->currentOffset - ringBuffer->slot * ringBuffer->slotSize) + alignedBytes;
        // attempt to resize the ring buffer to have it fit
        if (!gfx_sdl_gpu_resize_ring_buffer(ringBuffer, slotBytesNeeded)) {
            // if it failed, see if we have the render pass cached. If we do, submit
            // the current frame, wait for gpu, and recover the render pass with
            // a freed up vertex storage buffer
            if (sCachedRenderPassInfo.colorTex == NULL || sCachedRenderPassInfo.depthTex == NULL) {
                return false;
            }

            // save what we have in the cache since it will be deleted when ending the
            // current render pass
            struct CachedRenderPassInfo cachedRenderPassInfo = sCachedRenderPassInfo;

            // end the render pass
            gfx_sdl_gpu_end_render_pass();

            // flush vertex uploads
            gfx_sdl_gpu_flush_vertex_uploads();

            // submit upload and normal command buffers
            if (sUploadCmdBuffer != NULL) {
                SDL_SubmitGPUCommandBuffer(sUploadCmdBuffer);
                sUploadCmdBuffer = NULL;
            }

            if (sCmdBuffer != NULL) {
                SDL_SubmitGPUCommandBuffer(sCmdBuffer);
                sCmdBuffer = NULL;
            }

            // wait for gpu to finish
            SDL_WaitForGPUIdle(sGpuDevice);

            // spin up command buffer and render pass
            gfx_sdl_gpu_setup_command_buffer();
            gfx_sdl_gpu_begin_render_pass(cachedRenderPassInfo.colorTex, cachedRenderPassInfo.depthTex, cachedRenderPassInfo.clearColor, true);

            // reset the start offset to the start of the slot and the
            // current offset to the slot
            ringBuffer->startOffset = ringBuffer->slot * ringBuffer->slotSize;
            ringBuffer->currentOffset = ringBuffer->startOffset;
        }
    }

    *outOffset = ringBuffer->currentOffset;
    ringBuffer->currentOffset += alignedBytes; // increment current offset by written bytes

    return true;
}

static void gfx_sdl_gpu_reset_state(void) {
    sLastPipeline = NULL;
    sLastCachedProgram = NULL;

    memset(sPushedUniformBlocks, 0, sizeof(sPushedUniformBlocks));

    sLastSamplerBindingsCount = 0;
    memset(sLastSamplerBindings, 0, sizeof(sLastSamplerBindings));
}

static void gfx_sdl_gpu_cleanup_internal_textures(void) {
    // preserve vanilla internal textures
    struct InternalTexture vanillaInternalTextures[MAX_TEXTURES];
    u32 vanillaTextureCount = 0;

    for (u32 i = 0; i < sInternalTexturesCount; i++) {
        // check if it's a vanilla texture
        for (u32 j = 0; j < MAX_TEXTURES; j++) {
            if (strcmp(sInternalTextures[i].name, sVanillaTexUniformNames[j]) == 0) {
                // copy it to readd later
                vanillaInternalTextures[vanillaTextureCount++] = sInternalTextures[i];

                if (vanillaTextureCount == MAX_TEXTURES) { break; }
            }
        }

        if (vanillaTextureCount == MAX_TEXTURES) { break; }
    }

    // clear internal textures
    memset(sInternalTextures, 0, sizeof(sInternalTextures));
    sInternalTexturesCount = vanillaTextureCount;

    // restore vanilla internal textures into cache
    for (u32 i = 0; i < vanillaTextureCount; i++) {
        sInternalTextures[i] = vanillaInternalTextures[i];
    }
}

static void gfx_sdl_gpu_create_depth_texture(void) {
    // end any render passes that may be in progress
    gfx_sdl_gpu_end_render_pass();

    // clear out currently existing depth texture if it exists
    if (sDepthTexture != NULL) {
        SDL_ReleaseGPUTexture(sGpuDevice, sDepthTexture);
        sDepthTexture = NULL;
    }

    // create new depth texture
    SDL_GPUTextureCreateInfo desc = {
        .type = SDL_GPU_TEXTURETYPE_2D,
        .format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT,
        .usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
        .width = sRenderWidth,
        .height = sRenderHeight,
        .layer_count_or_depth = 1,
        .num_levels = 1,
    };
    sDepthTexture = SDL_CreateGPUTexture(sGpuDevice, &desc);
    if (!sDepthTexture) {
        sys_fatal("Failed to create swapchain depth texture: %s", SDL_GetError());
    }

    // set depth texture width and height
    sCurrDepthTexWidth = sRenderWidth;
    sCurrDepthTexHeight = sRenderHeight;
}

static SDL_GPUShader *gfx_sdl_gpu_create_shader_from_bytes(struct Shader *shader, SDL_GPUShaderStage stage, const void *code, size_t codeSize, const char *entrypoint) {
    SDL_GPUShaderCreateInfo createInfo = {
        .code_size = codeSize,
        .code = (const u8 *)code,
        .entrypoint = entrypoint,
        .format = sShaderFormat,
        .stage = stage,
        .num_samplers = shader->samplerCount,
        .num_storage_textures = 0,
        .num_storage_buffers = 0,
        .num_uniform_buffers = shader->uniformBlockCount
    };
    return SDL_CreateGPUShader(sGpuDevice, &createInfo);
}

static SDL_GPUShader *gfx_sdl_gpu_create_shader(struct Shader *shader) {
    SDL_GPUShaderStage stage = (shader->stage == SHADER_STAGE_VERTEX ? SDL_GPU_SHADERSTAGE_VERTEX : SDL_GPU_SHADERSTAGE_FRAGMENT);

    switch (sShaderFormat) {
        case SDL_GPU_SHADERFORMAT_MSL: {
            char *mslCode = NULL;
            gfx_convert_spirv_to_msl(&mslCode, shader);

            SDL_GPUShader *sdlShader = gfx_sdl_gpu_create_shader_from_bytes(shader, stage, mslCode, strlen(mslCode), "main0");

            free(mslCode);
            return sdlShader;
        }
#if defined(_WIN32)
        case SDL_GPU_SHADERFORMAT_DXBC: {
            char *hlslCode = NULL;
            gfx_convert_spirv_to_hlsl(&hlslCode, shader, 51);

            const char *target = (stage == SDL_GPU_SHADERSTAGE_VERTEX) ? "vs_5_1" : "ps_5_1";
            ID3DBlob *codeBlob = NULL;
            ID3DBlob *errorBlob = NULL;

            HRESULT hr = sD3dCompile(hlslCode, strlen(hlslCode), NULL, NULL, NULL, "main", target,
                D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &codeBlob, &errorBlob);
            free(hlslCode);

            if (FAILED(hr)) {
                const char *message = (errorBlob != NULL) ? (const char *)errorBlob->lpVtbl->GetBufferPointer(errorBlob) : "unknown error";
                LOG_ERROR("Failed to compile %s shader to DXBC: %s", target, message);
                if (errorBlob != NULL) { errorBlob->lpVtbl->Release(errorBlob); }
                if (codeBlob != NULL) { codeBlob->lpVtbl->Release(codeBlob); }
                return NULL;
            }
            if (errorBlob != NULL) { errorBlob->lpVtbl->Release(errorBlob); }

            SDL_GPUShader *sdlShader = gfx_sdl_gpu_create_shader_from_bytes(shader, stage, codeBlob->lpVtbl->GetBufferPointer(codeBlob), codeBlob->lpVtbl->GetBufferSize(codeBlob), "main");

            codeBlob->lpVtbl->Release(codeBlob);
            return sdlShader;
        }
#endif
        default: {
            gfx_process_spirv(shader);
            return gfx_sdl_gpu_create_shader_from_bytes(shader, stage, shader->spirVShader.words, (size_t)shader->spirVShader.size * sizeof(u32), "main");
        }
    }
}

static void gfx_sdl_gpu_create_pipeline_variants(struct ShaderProgramSdlGpu *prg, SDL_GPUGraphicsPipelineCreateInfo *pipelineInfo) {
    for (s32 test = 0; test < 2; test++) {
        for (s32 mask = 0; mask < 2; mask++) {
            for (s32 decal = 0; decal < 2; decal++) {
                for (s32 cullMode = 0; cullMode < GPU_CULL_MODE_COUNT; cullMode++) {
                    pipelineInfo->depth_stencil_state.enable_depth_test = (test != 0);
                    pipelineInfo->depth_stencil_state.enable_depth_write = (mask != 0);
                    pipelineInfo->depth_stencil_state.compare_op = (test != 0) ? SDL_GPU_COMPAREOP_LESS_OR_EQUAL : SDL_GPU_COMPAREOP_ALWAYS;

                    pipelineInfo->rasterizer_state.cull_mode = sCullingMap[cullMode];
                    pipelineInfo->rasterizer_state.enable_depth_bias = (decal != 0);
                    pipelineInfo->rasterizer_state.depth_bias_constant_factor = (decal != 0) ? -2.0f : 0.0f;
                    pipelineInfo->rasterizer_state.depth_bias_slope_factor = (decal != 0) ? -2.0f : 0.0f;

                    prg->pipelines[test][mask][decal][cullMode] = SDL_CreateGPUGraphicsPipeline(sGpuDevice, pipelineInfo);
                    if (!prg->pipelines[test][mask][decal][cullMode]) {
                        sys_fatal("Failed to create SDL GPU Graphics Pipeline: %s", SDL_GetError());
                    }
                }
            }
        }
    }
}

static SDL_GPUSamplerAddressMode gfx_cm_to_sdl_gpu(u32 cm) {
    if (cm & G_TX_CLAMP) {
        return SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    }
    return (cm & G_TX_MIRROR) ? SDL_GPU_SAMPLERADDRESSMODE_MIRRORED_REPEAT : SDL_GPU_SAMPLERADDRESSMODE_REPEAT;
}

static bool gfx_sdl_gpu_z_is_from_0_to_1(void) {
    return true;
}

static void gfx_sdl_gpu_unload_shader(UNUSED struct ShaderProgram *oldPrg) {
}

static void gfx_sdl_gpu_load_shader(struct ShaderProgram *newPrg) {
    sShaderProgram = (struct ShaderProgramSdlGpu *)newPrg;
}

static void gfx_sdl_gpu_release_program(struct ShaderProgramSdlGpu *prg) {
    for (s32 test = 0; test < 2; test++) {
        for (s32 mask = 0; mask < 2; mask++) {
            for (s32 decal = 0; decal < 2; decal++) {
                for (s32 cullMode = 0; cullMode < GPU_CULL_MODE_COUNT; cullMode++) {
                    if (prg->pipelines[test][mask][decal][cullMode] != NULL) {
                        SDL_ReleaseGPUGraphicsPipeline(sGpuDevice, prg->pipelines[test][mask][decal][cullMode]);
                    }
                }
            }
        }
    }

    if (prg->sdlVertexShader != NULL) {
        SDL_ReleaseGPUShader(sGpuDevice, prg->sdlVertexShader);
    }

    if (prg->sdlFragmentShader != NULL) {
        SDL_ReleaseGPUShader(sGpuDevice, prg->sdlFragmentShader);
    }

    gfx_destroy_shader(prg->vertexShader);
    gfx_destroy_shader(prg->fragmentShader);

    memset(prg, 0, sizeof(*prg));
}

static void gfx_sdl_gpu_remove_shaders(void) {
    for (s32 i = 0; i < MAX_FRAME_PASSES; i++) {
        for (s32 j = 0; j < CC_MAX_SHADERS; j++) {
            gfx_sdl_gpu_release_program(&sShaderProgramPool[i][j]);
        }
        sShaderProgramPoolIndex[i] = 0;
        sShaderProgramPoolSize[i] = 0;

        gfx_sdl_gpu_release_program(&sPostProcessShaderProgramPool[i]);
    }

    sShaderProgram = NULL;
}

static void gfx_sdl_gpu_build_program(struct ShaderProgramSdlGpu *prg, struct Shader *vertexShader, struct Shader *fragmentShader, bool useAlpha) {
    // create an sdl gpu vertex and fragment shader
    SDL_GPUShader *sdlVs = gfx_sdl_gpu_create_shader(vertexShader);
    SDL_GPUShader *sdlFs = gfx_sdl_gpu_create_shader(fragmentShader);

    if (!sdlVs || !sdlFs) {
        sys_fatal("Failed to create SDL GPU Shaders: %s", SDL_GetError());
    }

    // create vertex attribute layout
    SDL_GPUVertexAttribute vertexAttributes[MAX_SHADER_INPUTS];

    u32 attributeCount = 0;
    u32 vertexPitch = 0;

    // iterate through all shader inputs
    for (s32 i = 0; i < MAX_SHADER_INPUTS; i++) {
        s32 size = vertexShader->shaderInputs[i].size;
        if (size == 0) { continue; }

        // get the format of the element
        SDL_GPUVertexElementFormat format;
        switch (size) {
            case 1: format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT; break;
            case 2: format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2; break;
            case 3: format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3; break;
            default: format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4; break;
        }

        // set attribute info
        vertexAttributes[attributeCount].location = vertexShader->shaderInputs[i].location;
        vertexAttributes[attributeCount].buffer_slot = 0;
        vertexAttributes[attributeCount].format = format;
        vertexAttributes[attributeCount].offset = vertexPitch;

        // increment pitch and attribute count
        vertexPitch += (u32)size * sizeof(f32);
        attributeCount++;
    }

    // create vertex buffer desc
    SDL_GPUVertexBufferDescription vertexBufferDesc = {
        .slot = 0,
        .pitch = vertexPitch,
        .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
        .instance_step_rate = 0
    };

    // create color target desc
    SDL_GPUColorTargetDescription colorTargetDesc = {
        .format = sSwapchainFormat,
        .blend_state = {
            .enable_blend = useAlpha,
            .src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
            .dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            .color_blend_op = SDL_GPU_BLENDOP_ADD,
            .src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE,
            .dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ZERO,
            .alpha_blend_op = SDL_GPU_BLENDOP_ADD,
            .color_write_mask = SDL_GPU_COLORCOMPONENT_R | SDL_GPU_COLORCOMPONENT_G | SDL_GPU_COLORCOMPONENT_B | SDL_GPU_COLORCOMPONENT_A
        }
    };

    // create base pipeline information
    SDL_GPUGraphicsPipelineCreateInfo pipelineInfo = {
        .vertex_shader = sdlVs,
        .fragment_shader = sdlFs,
        .vertex_input_state = {
            .vertex_buffer_descriptions = &vertexBufferDesc,
            .num_vertex_buffers = (attributeCount > 0) ? 1 : 0,
            .vertex_attributes = vertexAttributes,
            .num_vertex_attributes = attributeCount
        },
        .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        .target_info = {
            .color_target_descriptions = &colorTargetDesc,
            .num_color_targets = 1,
            .depth_stencil_format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT,
            .has_depth_stencil_target = true
        },
        .rasterizer_state = {
            .cull_mode = SDL_GPU_CULLMODE_NONE,
            .front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE
        }
    };

    // create pipeline variants for different depth test, depth mask, and z mode decal values
    gfx_sdl_gpu_create_pipeline_variants(prg, &pipelineInfo);

    // set sdl vertex and fragment shader, along with standard vertex and fragment shader
    prg->sdlVertexShader = sdlVs;
    prg->sdlFragmentShader = sdlFs;
    prg->vertexShader = vertexShader;
    prg->fragmentShader = fragmentShader;
}

static struct ShaderProgram *gfx_sdl_gpu_create_and_load_new_shader(struct ColorCombiner *cc) {
    // get color combiner features
    struct CCFeatures ccf = { 0 };
    gfx_cc_get_features(cc, &ccf);

    // allocate vertex and fragment shader
    struct Shader *vertexShader = (struct Shader *)calloc(1, sizeof(struct Shader));
    struct Shader *fragmentShader = (struct Shader *)calloc(1, sizeof(struct Shader));
    if (!vertexShader || !fragmentShader) {
        sys_fatal("Failed to allocate shaders, ran out of memory!");
    }

    // generate vertex and fragment shader from color combiner
    gfx_generate_vertex_and_fragment_shader_from_cc(vertexShader, fragmentShader, cc, NULL, NULL);

    // get our current frame pass index
    s32 framePassIndex = gCurrentFramePassIndex + 1;
    if (framePassIndex < 0 || framePassIndex >= MAX_FRAME_PASSES) { framePassIndex = 0; }

    // get the pool index and get our program from the program pool
    u8 poolIndex = sShaderProgramPoolIndex[framePassIndex];
    struct ShaderProgramSdlGpu *prg = &sShaderProgramPool[framePassIndex][poolIndex];

    // increment pool index
    sShaderProgramPoolIndex[framePassIndex] = (poolIndex + 1) % CC_MAX_SHADERS;
    if (sShaderProgramPoolSize[framePassIndex] < CC_MAX_SHADERS) {
        sShaderProgramPoolSize[framePassIndex]++;
    }

    // free current shader program and build a new one
    if (sShaderProgram == prg) { sShaderProgram = NULL; } // make sure we dont clear the current shader program!
    gfx_sdl_gpu_release_program(prg);
    gfx_sdl_gpu_build_program(prg, vertexShader, fragmentShader, cc->cm.use_alpha);

    // configure program
    prg->hash = cc->hash;
    prg->numInputs = ccf.num_inputs;
    prg->usedTextures[0] = ccf.used_textures[0];
    prg->usedTextures[1] = ccf.used_textures[1];
    prg->usedFog = cc->cm.use_fog;

    sShaderProgram = prg;
    return (struct ShaderProgram *)prg;
}

static struct ShaderProgram *gfx_sdl_gpu_create_or_load_post_process_shader(void) {
    // get frame pass index
    s32 framePassIndex = gCurrentFramePassIndex + 1;
    if (framePassIndex < 0 || framePassIndex >= MAX_FRAME_PASSES) { framePassIndex = 0; }

    // get program from cache
    struct ShaderProgramSdlGpu *prg = &sPostProcessShaderProgramPool[framePassIndex];

    // if the cache entry is valid, use it
    if (prg->pipelines[0][0][0][0] != NULL) {
        sShaderProgram = prg;
        return (struct ShaderProgram *)prg;
    }

    // allocate vertex and fragment shader
    struct Shader *vertexShader = (struct Shader *)calloc(1, sizeof(struct Shader));
    struct Shader *fragmentShader = (struct Shader *)calloc(1, sizeof(struct Shader));
    if (!vertexShader || !fragmentShader) {
        sys_fatal("Failed to allocate shaders, ran out of memory!");
    }

    // build post process shader
    gfx_generate_post_process_vertex_and_fragment_shader(vertexShader, fragmentShader, NULL, NULL);

    // build program
    gfx_sdl_gpu_build_program(prg, vertexShader, fragmentShader, false);

    sShaderProgram = prg;
    return (struct ShaderProgram *)prg;
}

static struct ShaderProgram *gfx_sdl_gpu_lookup_shader(struct ColorCombiner *cc) {
    s32 framePassIndex = gCurrentFramePassIndex + 1;
    if (framePassIndex < 0 || framePassIndex >= MAX_FRAME_PASSES) { return NULL; }
    for (s32 i = 0; i < sShaderProgramPoolSize[framePassIndex]; i++) {
        if (sShaderProgramPool[framePassIndex][i].hash == cc->hash) {
            return (struct ShaderProgram *)&sShaderProgramPool[framePassIndex][i];
        }
    }
    return NULL;
}

static void gfx_sdl_gpu_shader_get_info(struct ShaderProgram *prg, u8 *numInputs, bool used_textures[2]) {
    struct ShaderProgramSdlGpu *p = (struct ShaderProgramSdlGpu *)prg;
    if (!p) { return; }

    *numInputs = p->numInputs;
    used_textures[0] = p->usedTextures[0];
    used_textures[1] = p->usedTextures[1];
}

static void gfx_sdl_gpu_create_framebuffer(struct FramePass *framePass) {
    if (framePass == NULL) { return; }

    // get viewport dimensions
    u32 viewportWidth;
    u32 viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(framePass, &viewportWidth, &viewportHeight);

    // create color texture
    SDL_GPUTextureCreateInfo colorDesc = {
        .type = SDL_GPU_TEXTURETYPE_2D,
        .format = sSwapchainFormat,
        .usage = SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER,
        .width = viewportWidth,
        .height = viewportHeight,
        .layer_count_or_depth = 1,
        .num_levels = 1,
    };
    SDL_GPUTexture *colorTex = SDL_CreateGPUTexture(sGpuDevice, &colorDesc);
    if (colorTex == NULL) { return; }

    // create depth texture
    SDL_GPUTextureCreateInfo depthDesc = {
        .type = SDL_GPU_TEXTURETYPE_2D,
        .format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT,
        .usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER,
        .width = viewportWidth,
        .height = viewportHeight,
        .layer_count_or_depth = 1,
        .num_levels = 1,
    };
    SDL_GPUTexture *depthTex = SDL_CreateGPUTexture(sGpuDevice, &depthDesc);
    if (depthTex == NULL) {
        SDL_ReleaseGPUTexture(sGpuDevice, colorTex);
        return;
    }

    // set pass tex, color tex, and depth tex, as well as fbo for tracking
    framePass->colorTexture = (u64)(uintptr_t)colorTex;
    framePass->depthTexture = (u64)(uintptr_t)depthTex;
    framePass->colorTex = (void *)colorTex;
    framePass->depthTex = (void *)depthTex;
    framePass->fbo = 1;
}

static void gfx_sdl_gpu_delete_framebuffer(struct FramePass *framePass) {
    if (framePass == NULL || !framePass->fbo) {
        return;
    }

    gfx_sdl_gpu_end_render_pass();
    gfx_sdl_gpu_cleanup_internal_textures();

    if (framePass->colorTex != NULL) {
        SDL_ReleaseGPUTexture(sGpuDevice, (SDL_GPUTexture *)framePass->colorTex);
        framePass->colorTex = NULL;
    }

    if (framePass->depthTex != NULL) {
        SDL_ReleaseGPUTexture(sGpuDevice, (SDL_GPUTexture *)framePass->depthTex);
        framePass->depthTex = NULL;
    }

    framePass->colorTexture = 0;
    framePass->depthTexture = 0;
    framePass->fbo = 0;
}

static void gfx_sdl_gpu_begin_render_pass(SDL_GPUTexture *colorTex, SDL_GPUTexture *depthTex, f32 clearColor[4], bool cleared) {
    // set load operation depending on if we have cleared the screen
    // for the current pass already or not
    SDL_GPULoadOp loadOp = cleared ? SDL_GPU_LOADOP_LOAD : SDL_GPU_LOADOP_CLEAR;

    // get color info
    SDL_GPUColorTargetInfo colorTargetInfo = {
        .texture = colorTex,
        .clear_color = { clearColor[0], clearColor[1], clearColor[2], clearColor[3] },
        .load_op = loadOp,
        .store_op = SDL_GPU_STOREOP_STORE,
    };

    // get depth info
    SDL_GPUDepthStencilTargetInfo depthTargetInfo = {
        .texture = depthTex,
        .clear_depth = 1.0f,
        .load_op = loadOp,
        .store_op = SDL_GPU_STOREOP_STORE,
    };

    // startup render pass
    sRenderPass = SDL_BeginGPURenderPass(sCmdBuffer, &colorTargetInfo, 1, (depthTex != NULL) ? &depthTargetInfo : NULL);
    if (sRenderPass == NULL) { return; }

    // cache current state
    sCachedRenderPassInfo.colorTex = colorTex;
    sCachedRenderPassInfo.depthTex = depthTex;
    memcpy(sCachedRenderPassInfo.clearColor, clearColor, sizeof(f32) * 4);
    sCachedRenderPassInfo.cleared = cleared;

    // reset pipelines and pushed uniforms
    gfx_sdl_gpu_reset_state();
}

static void gfx_sdl_gpu_end_render_pass(void) {
    if (sRenderPass == NULL) { return; }

    // end render pass
    SDL_EndGPURenderPass(sRenderPass);
    sRenderPass = NULL;

    // clear cache
    memset(&sCachedRenderPassInfo, 0, sizeof(sCachedRenderPassInfo));
}

static void gfx_sdl_gpu_set_framebuffer(struct FramePass *framePass) {
    if (framePass == NULL || !framePass->fbo) {
        return;
    }

    gfx_sdl_gpu_setup_command_buffer();
    gfx_sdl_gpu_end_render_pass();

    s32 framePassIndex = gCurrentFramePassIndex + 1;
    if (framePassIndex < 0 || framePassIndex >= MAX_FRAME_PASSES) { framePassIndex = 0; }

    bool cleared = sFramePassCleared[framePassIndex];
    sFramePassCleared[framePassIndex] = true;

    f32 clearColor[4] = {
        (f32)framePass->clearColor[0] / 255.0f,
        (f32)framePass->clearColor[1] / 255.0f,
        (f32)framePass->clearColor[2] / 255.0f,
        (f32)framePass->clearColor[3] / 255.0f
    };

    gfx_sdl_gpu_begin_render_pass((SDL_GPUTexture *)framePass->colorTex, (SDL_GPUTexture *)framePass->depthTex, clearColor, cleared);
}

static void gfx_sdl_gpu_reset_framebuffer(void) {
    gfx_sdl_gpu_setup_command_buffer();
    gfx_sdl_gpu_end_render_pass();

    if (!sStartedFrame) {
        if (!SDL_WaitAndAcquireGPUSwapchainTexture(sCmdBuffer, sSdlWindow, &sSwapchainTex, &sRenderWidth, &sRenderHeight) || sSwapchainTex == NULL) {
            return;
        }
        sStartedFrame = true;
    }

    if (sCurrDepthTexWidth != sRenderWidth || sCurrDepthTexHeight != sRenderHeight) {
        gfx_sdl_gpu_create_depth_texture();
    }

    bool cleared = sSwapchainCleared;
    sSwapchainCleared = true;

    f32 clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    gfx_sdl_gpu_begin_render_pass(sSwapchainTex, sDepthTexture, clearColor, cleared);
}

static struct Shader *gfx_sdl_gpu_shader_for_stage(enum ShaderStage stage) {
    if (sShaderProgram == NULL) { return NULL; }
    if (stage == SHADER_STAGE_VERTEX) { return sShaderProgram->vertexShader; }
    if (stage == SHADER_STAGE_FRAGMENT) { return sShaderProgram->fragmentShader; }
    return NULL;
}

static struct ShaderUniformBlock *gfx_sdl_gpu_get_active_uniform_buffer(enum ShaderStage stage) {
    struct Shader *shader = gfx_sdl_gpu_shader_for_stage(stage);
    if (shader == NULL) { return NULL; }

    s32 selectedUniformBuffer = (stage == SHADER_STAGE_VERTEX) ? gSelectedVertexUniformBuffer : gSelectedFragmentUniformBuffer;
    return &shader->uniformBlocks[selectedUniformBuffer];
}

static void gfx_sdl_gpu_set_uniform_buffer(enum ShaderStage stage, const char *name) {
    struct Shader *shader = gfx_sdl_gpu_shader_for_stage(stage);
    if (shader == NULL) { return; }

    s32 *destination = (stage == SHADER_STAGE_VERTEX) ? &gSelectedVertexUniformBuffer : &gSelectedFragmentUniformBuffer;

    for (s32 i = 0; i < MAX_UNIFORM_BLOCKS; i++) {
        struct ShaderUniformBlock *uniformBlock = &shader->uniformBlocks[i];

        if (strcmp(uniformBlock->name, name) == 0) {
            *destination = i;
            return;
        }
    }
}

static void gfx_sdl_gpu_set_uniform_for_specific_shader(struct ShaderUniformBlock *uniformBlock, const char *name, const void *data, u32 numElements) {
    if (uniformBlock == NULL || uniformBlock->buffer == NULL) {
        return;
    }

    for (s32 i = 0; i < MAX_SHADER_UNIFORMS; i++) {
        struct ShaderUniform *uniform = &uniformBlock->uniforms[i];
        if (uniform->size == 0) { break; }

        if (strcmp(uniform->name, name) == 0) {
            u8 *dst = uniformBlock->buffer;
            dst += uniform->location;

            if (uniform->arrayLength > 1) {
                const u8 *src = (const u8 *)data;
                u32 count = MIN(numElements, (u32)uniform->arrayLength);
                for (u32 j = 0; j < count; j++) {
                    u8 *elementDst = dst + j * uniform->arrayStride;
                    const u8 *elementSrc = src + j * uniform->elementSize;
                    if (memcmp(elementDst, elementSrc, uniform->elementSize) == 0) { continue; }
                    memcpy(elementDst, elementSrc, uniform->elementSize);
                    uniformBlock->hasChanged = true;
                }
            } else if (memcmp(dst, data, uniform->size) != 0) {
                memcpy(dst, data, uniform->size);
                uniformBlock->hasChanged = true;
            }
            return;
        }
    }
}

static void gfx_sdl_gpu_set_uniform(struct ShaderProgram *prg, const char *name, const void *data, u32 numElements) {
    struct ShaderProgramSdlGpu *sdlPrg = (struct ShaderProgramSdlGpu *)prg;
    if (sdlPrg == NULL) {
        if (sShaderProgram == NULL) { return; }
        sdlPrg = sShaderProgram;
    }

    if (gfx_shader_stage_is(SHADER_STAGE_VERTEX) && sdlPrg->vertexShader != NULL) {
        gfx_sdl_gpu_set_uniform_for_specific_shader(&sdlPrg->vertexShader->uniformBlocks[gSelectedVertexUniformBuffer], name, data, numElements);
    }

    if (gfx_shader_stage_is(SHADER_STAGE_FRAGMENT) && sdlPrg->fragmentShader != NULL) {
        gfx_sdl_gpu_set_uniform_for_specific_shader(&sdlPrg->fragmentShader->uniformBlocks[gSelectedFragmentUniformBuffer], name, data, numElements);
    }
}

static u32 gfx_sdl_gpu_get_texture_id(const Texture *addr) {
    // allocate a new slot to the texture cache
    if (sTextureCacheCount >= sTextureCacheCapacity) {
        sTextureCacheCapacity = (sTextureCacheCapacity == 0) ? 16 : sTextureCacheCapacity * 2;
        sTextureCache = realloc(sTextureCache, sTextureCacheCapacity * sizeof(struct TextureData));
        if (!sTextureCache) {
            sys_fatal("Failed to reallocate texture storage array!");
        }
    }

    memset(&sTextureCache[sTextureCacheCount], 0, sizeof(struct TextureData));
    sTextureCache[sTextureCacheCount].addr = addr;
    return sTextureCacheCount++;
}

static u64 gfx_sdl_gpu_get_render_texture(const Texture *addr) {
    // grab render texture from texture cache
    for (u32 i = 0; i < sTextureCacheCount; i++) {
        if (sTextureCache[i].addr == addr) {
            return (u64)sTextureCache[i].texture;
        }
    }
    return 0;
}

static void gfx_sdl_gpu_bind_texture_using_name(const char *name, u64 renderTexture);

static void gfx_sdl_gpu_select_texture(s32 tile, u32 texture_id) {
    sCurrentTile = tile;
    if (tile >= 0 && tile < MAX_TEXTURES) {
        sCurrentTextureIds[tile] = texture_id;
    }
    gfx_sdl_gpu_bind_texture_using_name(sVanillaTexUniformNames[tile], (u64)sTextureCache[texture_id].texture);
}

static struct TextureData *gfx_sdl_gpu_texture_for_tile(s32 tile) {
    if (tile < 0 || tile >= MAX_TEXTURES) { return NULL; }

    u32 textureId = sCurrentTextureIds[tile];
    if (textureId >= sTextureCacheCount) { return NULL; }

    return &sTextureCache[textureId];
}

static bool gfx_sdl_gpu_render_texture_valid(u64 renderTexture) {
    SDL_GPUTexture *texture = (SDL_GPUTexture *)renderTexture;
    if (texture == NULL) { return false; }

    // check the texture cache
    for (u32 i = 0; i < sTextureCacheCount; i++) {
        if (sTextureCache[i].texture == texture) {
            return true;
        }
    }

    // check frame passes
    for (s32 i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
        struct FramePass *framePass = &gFramePasses[i];
        if (!framePass->active) { continue; }
        if (framePass->colorTex == texture) {
            return true;
        }

        if (framePass->depthTex == texture) {
            return true;
        }
    }

    if (gDefaultGeoFramePass.colorTex == texture) {
        return true;
    }

    if (gDefaultGeoFramePass.depthTex == texture) {
        return true;
    }

    // the texture id must be invalid
    return false;
}

static void gfx_sdl_gpu_bind_texture_using_name(const char *name, u64 renderTexture) {
    SDL_GPUTexture *texture = (SDL_GPUTexture *)renderTexture;
    if (name == NULL || texture == NULL) { return; }

    SDL_GPUSampler *sampler = NULL;
    u32 width = 0;
    u32 height = 0;
    enum TextureFilter filter = TEXTURE_FILTER_LINEAR;

    // try looking in texture cache
    for (u32 i = 0; i < sTextureCacheCount; i++) {
        if (sTextureCache[i].texture == texture) {
            sampler = sTextureCache[i].sampler;
            width = sTextureCache[i].width;
            height = sTextureCache[i].height;
            filter = sTextureCache[i].linearFilter ? TEXTURE_FILTER_LINEAR : TEXTURE_FILTER_NEAREST;
        }
    }

    if (sampler == NULL) {
        // check frame pass textures, both depth and color
        struct FramePass *currentFramePass = NULL;
        bool isDepthTexture = false;

        for (s32 i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
            struct FramePass *framePass = &gFramePasses[i];
            if (!framePass->active) { continue; }
            if (framePass->colorTex == texture) {
                isDepthTexture = false;
                currentFramePass = framePass;
                break;
            }

            if (framePass->depthTex == texture) {
                isDepthTexture = true;
                currentFramePass = framePass;
                break;
            }
        }

        if (currentFramePass == NULL) {
            if (gDefaultGeoFramePass.colorTex == texture) {
                isDepthTexture = false;
                currentFramePass = &gDefaultGeoFramePass;
            }

            if (gDefaultGeoFramePass.depthTex == texture) {
                isDepthTexture = true;
                currentFramePass = &gDefaultGeoFramePass;
            }

            if (currentFramePass == NULL) { return; }
        }

        SDL_GPUSampler *linearSampler = (isDepthTexture ? sLinearClampDepthSampler : sLinearClampSampler);
        SDL_GPUSampler *nearestSampler = (isDepthTexture ? sNearestClampDepthSampler : sNearestClampSampler);

        sampler = (filter == TEXTURE_FILTER_LINEAR) ? linearSampler : nearestSampler;
        width = currentFramePass->width;
        height = currentFramePass->height;
        filter = (isDepthTexture ? currentFramePass->passDepthFilter : currentFramePass->passColorFilter);
    }

    if (sampler != NULL) {
        struct InternalTexture *texSamplerBind = NULL;

        // check for a entry with the same name
        for (u32 i = 0; i < sInternalTexturesCount; i++) {
            if (sInternalTextures[i].name != NULL && strcmp(sInternalTextures[i].name, name) == 0) {
                texSamplerBind = &sInternalTextures[i];
                break;
            }
        }

        if (texSamplerBind == NULL) {
            if (sInternalTexturesCount >= MAX_SHADER_SAMPLERS) {
                LOG_ERROR("Ran out of sampler slots!");
                return;
            }
            texSamplerBind = &sInternalTextures[sInternalTexturesCount++];
        }

        texSamplerBind->name = name;
        texSamplerBind->textureSamplerBinding.sampler = sampler;
        texSamplerBind->textureSamplerBinding.texture = texture;
        texSamplerBind->width = width;
        texSamplerBind->height = height;
        texSamplerBind->filter = filter;
    }
}

static void gfx_sdl_gpu_upload_texture(const u8 *rgba32_buf, s32 width, s32 height) {
    if (width <= 0 || height <= 0) { sys_fatal("Texture dimensions are invalid!"); }

    struct TextureData *textureData = gfx_sdl_gpu_texture_for_tile(sCurrentTile);
    if (textureData == NULL) { return; }

    // create sdl gpu texture
    SDL_GPUTextureCreateInfo desc = {
        .type = SDL_GPU_TEXTURETYPE_2D,
        .format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
        .usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
        .width = (u32)width,
        .height = (u32)height,
        .layer_count_or_depth = 1,
        .num_levels = 1,
    };
    SDL_GPUTexture *texture = SDL_CreateGPUTexture(sGpuDevice, &desc);
    if (!texture) {
        sys_fatal("Failed to create SDL GPU texture for upload: %s", SDL_GetError());
    }

    // get buffer size for upload
    u32 bufferSize = (u32)(width * height * 4);
    SDL_GPUTransferBufferCreateInfo transferCreateInfo = {
        .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
        .size = bufferSize
    };

    // create transfer buffer
    SDL_GPUTransferBuffer *transferBuffer = SDL_CreateGPUTransferBuffer(sGpuDevice, &transferCreateInfo);
    if (!transferBuffer) {
        sys_fatal("Failed to create transfer buffer: %s", SDL_GetError());
    }

    // map, copy data, and unmap
    void *map = SDL_MapGPUTransferBuffer(sGpuDevice, transferBuffer, false);
    if (map) {
        memcpy(map, rgba32_buf, bufferSize);
        SDL_UnmapGPUTransferBuffer(sGpuDevice, transferBuffer);
    }

    // create upload command buffer
    SDL_GPUCommandBuffer *uploadCmdBuffer = SDL_AcquireGPUCommandBuffer(sGpuDevice);
    if (uploadCmdBuffer == NULL) {
        sys_fatal("Failed to acquire GPU command buffer for texture upload: %s", SDL_GetError());
    }

    // create copy pass
    SDL_GPUCopyPass *copyPass = SDL_BeginGPUCopyPass(uploadCmdBuffer);

    // define transfer info
    SDL_GPUTextureTransferInfo source = {
        .transfer_buffer = transferBuffer,
        .offset = 0
    };

    // define texture info
    SDL_GPUTextureRegion destination = {
        .texture = texture,
        .w = (u32)width,
        .h = (u32)height,
        .d = 1
    };

    // upload texture in copy pass
    SDL_UploadToGPUTexture(copyPass, &source, &destination, false);
    SDL_EndGPUCopyPass(copyPass);

    // submit the command buffer
    gfx_sdl_gpu_flush_vertex_uploads();
    SDL_SubmitGPUCommandBuffer(uploadCmdBuffer);

    // free transfer buffer
    SDL_ReleaseGPUTransferBuffer(sGpuDevice, transferBuffer);

    // set texture data's width and height
    textureData->width = (u32)width;
    textureData->height = (u32)height;

    // free already existing texture if necessary
    if (textureData->texture != NULL) {
        SDL_ReleaseGPUTexture(sGpuDevice, textureData->texture);
    }
    textureData->texture = texture;
    gfx_sdl_gpu_cleanup_internal_textures();
}

static void gfx_sdl_gpu_set_sampler_parameters(s32 tile, bool linear_filter, u32 cms, u32 cmt) {
    struct TextureData *textureData = gfx_sdl_gpu_texture_for_tile(tile);
    if (textureData == NULL) { return; }

    if (textureData->sampler != NULL &&
        textureData->linearFilter == linear_filter &&
        textureData->cms == cms &&
        textureData->cmt == cmt) {
        return;
    }

    if (textureData->sampler != NULL) {
        SDL_ReleaseGPUSampler(sGpuDevice, textureData->sampler);
    }

    SDL_GPUFilter filterMode = linear_filter ? SDL_GPU_FILTER_LINEAR : SDL_GPU_FILTER_NEAREST;

    SDL_GPUSamplerCreateInfo samplerCreateInfo = {
        .min_filter = filterMode,
        .mag_filter = filterMode,
        .mipmap_mode = linear_filter ? SDL_GPU_SAMPLERMIPMAPMODE_LINEAR : SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
        .address_mode_u = gfx_cm_to_sdl_gpu(cms),
        .address_mode_v = gfx_cm_to_sdl_gpu(cmt),
        .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
    };

    textureData->sampler = SDL_CreateGPUSampler(sGpuDevice, &samplerCreateInfo);
    textureData->linearFilter = linear_filter;
    textureData->cms = cms;
    textureData->cmt = cmt;
    gfx_sdl_gpu_cleanup_internal_textures();
}

static void gfx_sdl_gpu_set_depth_test(bool depthTest) {
    sDepthTest = depthTest;
}

static void gfx_sdl_gpu_set_depth_mask(bool zUpd) {
    sDepthMask = zUpd;
}

static void gfx_sdl_gpu_set_zmode_decal(bool zModeDecal) {
    sZModeDecal = zModeDecal;
}

static void gfx_sdl_gpu_set_viewport(s32 x, s32 y, s32 width, s32 height) {
    if (sRenderPass == NULL) {
        return;
    }

    u32 viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(gfx_get_current_frame_pass(), NULL, &viewportHeight);

    SDL_GPUViewport vp = {
        .x = (f32)x,
        .y = (f32)(viewportHeight - y - height),
        .w = (f32)width,
        .h = (f32)height,
        .min_depth = 0.0f,
        .max_depth = 1.0f
    };

    SDL_SetGPUViewport(sRenderPass, &vp);
}

static void gfx_sdl_gpu_set_scissor(s32 x, s32 y, s32 width, s32 height) {
    if (sRenderPass == NULL) {
        return;
    }

    u32 viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(gfx_get_current_frame_pass(), NULL, &viewportHeight);

    SDL_Rect r = {
        .x = x,
        .y = (s32)viewportHeight - y - height,
        .w = width,
        .h = height
    };

    SDL_SetGPUScissor(sRenderPass, &r);
}

static void gfx_sdl_gpu_set_use_alpha(UNUSED bool useAlpha) {
}

static void gfx_sdl_gpu_set_vsync(bool enabled) {
    if (sGpuDevice == NULL || sSdlWindow == NULL) { return; }

    // grab present mode depending on vsync being enabled or not
    SDL_GPUPresentMode presentMode = (enabled ? SDL_GPU_PRESENTMODE_VSYNC : SDL_GPU_PRESENTMODE_IMMEDIATE);

    // make sure we support the present mode being requested. If not, fall back on
    // vsync
    if (!SDL_WindowSupportsGPUPresentMode(sGpuDevice, sSdlWindow, presentMode)) {
        presentMode = SDL_GPU_PRESENTMODE_VSYNC;
    }

    // if we are already using the present mode, return
    if (presentMode == sPresentMode) { return; }

    // submit current frame and wait for gpu
    gfx_sdl_gpu_submit_frame();
    SDL_WaitForGPUIdle(sGpuDevice);

    // release the current window and reclaim the window
    SDL_ReleaseWindowFromGPUDevice(sGpuDevice, sSdlWindow);
    if (!SDL_ClaimWindowForGPUDevice(sGpuDevice, sSdlWindow)) {
        sys_fatal("Failed to reclaim window for gpu device: %s", SDL_GetError());
    }

    // refetch swapchain format
    sSwapchainFormat = SDL_GetGPUSwapchainTextureFormat(sGpuDevice, sSdlWindow);
    if (sSwapchainFormat == SDL_GPU_TEXTUREFORMAT_INVALID) {
        sSwapchainFormat = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    }

    sPresentMode = presentMode;

    // set swapchain parameters if necessary
    if (presentMode == SDL_GPU_PRESENTMODE_VSYNC) { return; }

    if (!SDL_SetGPUSwapchainParameters(sGpuDevice, sSdlWindow, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, presentMode)) {
        LOG_ERROR("Couldn't set the swapchain present mode: %s", SDL_GetError());
    }
}

static void upload_uniform_buffers_for_shader(struct Shader *shader) {
    if (shader == NULL || sRenderPass == NULL) { return; }

    bool isVertex = (shader->stage == SHADER_STAGE_VERTEX);

    // get our already pushed blocks
    struct ShaderUniformBlock **pushedBlocks = sPushedUniformBlocks[isVertex ? 0 : 1];

    // iterate through uniform blocks in shader
    for (s32 i = 0; i < shader->uniformBlockCount; i++) {
        struct ShaderUniformBlock *uniformBlock = &shader->uniformBlocks[i];
        if (uniformBlock->size == 0) { continue; } // sanity check

        // get slot
        u32 slot = uniformBlock->location;

        // if we haven't changed and the uniform block is in the pushed blocks, ignore this block
        if (!uniformBlock->hasChanged && pushedBlocks[slot] == uniformBlock) { continue; }

        // push either vertex or fragment uniform data
        if (isVertex) {
            SDL_PushGPUVertexUniformData(sCmdBuffer, slot, uniformBlock->buffer, uniformBlock->size);
        } else {
            SDL_PushGPUFragmentUniformData(sCmdBuffer, slot, uniformBlock->buffer, uniformBlock->size);
        }

        // mark as no longer changed, and mark the block as pushed
        uniformBlock->hasChanged = false;
        pushedBlocks[slot] = uniformBlock;
    }
}

static void gfx_sdl_gpu_draw_triangles(f32 buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {
    if (sShaderProgram == NULL || sRenderPass == NULL) { return; }

    smlua_call_event_hooks(HOOK_ON_DRAW_TRIANGLE);

    u32 offset = 0;
    u32 vboByteSize = (u32)(buf_vbo_len * sizeof(f32));

    if (buf_vbo_len > 0) {
        // allocate and copy data to vertex buffer
        if (!gfx_sdl_gpu_allocate_to_ring_buffer(&sVertexRingBuffer, vboByteSize, &offset)) { return; }
        memcpy(gfx_sdl_gpu_map_ring_buffer(&sVertexRingBuffer) + offset, buf_vbo, vboByteSize);
    }

    if (sLastCachedProgram != sShaderProgram) {
        sLastCachedProgram = sShaderProgram;
    }

    struct Shader *fragmentShader = sShaderProgram->fragmentShader;

    // bind samplers
    SDL_GPUTextureSamplerBinding samplerBindings[MAX_SHADER_SAMPLERS];
    u32 samplerBindingsCount = 0;

    for (s32 i = 0; i < fragmentShader->samplerCount; i++) {
        // make sure the sampler is valid, if not the shader is invalid and use fallback
        if (fragmentShader->shaderSamplers[i].name[0] == '\0') {
            samplerBindings[samplerBindingsCount++] = sFallbackTextureBinding;
            continue;
        }

        u8 samplerBinding = fragmentShader->shaderSamplers[i].binding;

        struct InternalTexture *internalTexture = NULL;

        bool vanillaSampler = false;

        // iterate and do a lookup on names
        for (u32 j = 0; j < sInternalTexturesCount; j++) {
            if (strcmp(sInternalTextures[j].name, fragmentShader->shaderSamplers[i].name) == 0) {
                // set internal texture
                internalTexture = &sInternalTextures[j];
                for (u32 k = 0; k < MAX_TEXTURES; k++) {
                    // check and see if it's a vanilla texture
                    if (strcmp(sInternalTextures[j].name, sVanillaTexUniformNames[k]) == 0) {
                        vanillaSampler = true;
                    }
                }
                break;
            }
        }

        // if no texture exists, use fallback
        if (internalTexture == NULL) {
            samplerBindings[samplerBindingsCount++] = sFallbackTextureBinding;
            continue;
        }

        if (vanillaSampler) {
            // set tex size and filter uniforms
            f32 texSize[2] = { (f32)internalTexture->width, (f32)internalTexture->height };
            gfx_sdl_gpu_set_uniform((struct ShaderProgram *)sShaderProgram, sTexSizeUniformNames[samplerBinding], texSize, 1);

            u32 isLinear = internalTexture->filter == TEXTURE_FILTER_LINEAR ? 1 : 0;
            gfx_sdl_gpu_set_uniform((struct ShaderProgram *)sShaderProgram, sTexFilterUniformNames[samplerBinding], &isLinear, 1);
        }

        // set the sampler bindings texture and sampler
        samplerBindings[samplerBindingsCount].texture = internalTexture->textureSamplerBinding.texture;
        samplerBindings[samplerBindingsCount].sampler = internalTexture->textureSamplerBinding.sampler;
        samplerBindingsCount++;
    }

    // bind fragment samplers
    if (samplerBindingsCount > 0) {
        // do a basic count check to see if samplers changed first
        bool samplersChanged = (samplerBindingsCount != sLastSamplerBindingsCount);

        // if the counts line up, iterate and compare to see if a sampler changes
        if (!samplersChanged) {
            for (u32 i = 0; i < samplerBindingsCount; i++) {
                if (sLastSamplerBindings[i].texture != samplerBindings[i].texture || sLastSamplerBindings[i].sampler != samplerBindings[i].sampler) {
                    samplersChanged = true;
                    break;
                }
            }
        }

        // if the sampler changed, bind the sampler and update the cache
        if (samplersChanged) {
            SDL_BindGPUFragmentSamplers(sRenderPass, 0, samplerBindings, samplerBindingsCount);

            sLastSamplerBindingsCount = samplerBindingsCount;
            memcpy(sLastSamplerBindings, samplerBindings, sizeof(SDL_GPUTextureSamplerBinding) * samplerBindingsCount);
        }
    }

    // update matrix and fog uniforms
    gfx_update_matrices();
    if (sShaderProgram->usedFog) {
        gfx_update_fog_uniforms();
    }

    // upload uniform buffers for vertex and fragment shader
    upload_uniform_buffers_for_shader(sShaderProgram->vertexShader);
    upload_uniform_buffers_for_shader(sShaderProgram->fragmentShader);

    // get current shader pipeline and bind the pipeline
    SDL_GPUGraphicsPipeline *pipeline = sShaderProgram->pipelines[sDepthTest ? 1 : 0][sDepthMask ? 1 : 0][sZModeDecal ? 1 : 0][gGpuCullMode];
    if (pipeline == NULL) { return; }

    if (sLastPipeline != pipeline) {
        SDL_BindGPUGraphicsPipeline(sRenderPass, pipeline);
        sLastPipeline = pipeline;
    }

    if (buf_vbo_len > 0) {
        // bind vertex buffers
        SDL_GPUBufferBinding vboBinding = {
            .buffer = sVertexRingBuffer.gpuBuffer,
            .offset = offset
        };
        SDL_BindGPUVertexBuffers(sRenderPass, 0, &vboBinding, 1);

        // draw triangles
        u32 numVertices = (u32)(buf_vbo_num_tris * 3);
        SDL_DrawGPUPrimitives(sRenderPass, numVertices, 1, 0, 0);
    }
}

static void gfx_sdl_gpu_init(void) {
    // grab window
    sSdlWindow = gfx_wm_get_window();

    // grab shader format
    // windows uses DXBC for dx12 or spirv for vulkan
    // linux uses vulkan's spirv
    // macOS uses metal's msl
    sShaderFormat = gfx_sdl_gpu_shader_format_for_backend(configGraphicsBackend);

#if defined(_WIN32)
    if (sShaderFormat == SDL_GPU_SHADERFORMAT_DXBC && !gfx_sdl_gpu_load_d3d_compiler()) {
        sys_fatal("Couldn't load the HLSL compiler needed by the DirectX 12 renderer.");
    }
#endif

    // get and claim gpu device
    SDL_PropertiesID props = gfx_sdl_gpu_create_device_properties(configGraphicsBackend);
    sGpuDevice = SDL_CreateGPUDeviceWithProperties(props);
    SDL_DestroyProperties(props);
    if (sGpuDevice == NULL) {
        sys_fatal("Couldn't create GPU device: %s", SDL_GetError());
    }

    if (!SDL_SetGPUAllowedFramesInFlight(sGpuDevice, MAX_FRAMES_IN_FLIGHT)) {
        LOG_ERROR("Couldn't allow %d frames in flight: %s", MAX_FRAMES_IN_FLIGHT, SDL_GetError());
    }

    if (!SDL_ClaimWindowForGPUDevice(sGpuDevice, sSdlWindow)) {
        sys_fatal("Failed to claim window for gpu device: %s", SDL_GetError());
    }

    // set vsync
    gfx_sdl_gpu_set_vsync(configWindow.vsync);

    // set width and height of screen
    gfx_wm_get_dimensions(&sRenderWidth, &sRenderHeight);

    // init default linear sampler
    SDL_GPUSamplerCreateInfo linearClampInfo = {
        .min_filter = SDL_GPU_FILTER_LINEAR,
        .mag_filter = SDL_GPU_FILTER_LINEAR,
        .address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
        .address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
        .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE
    };
    sLinearClampSampler = SDL_CreateGPUSampler(sGpuDevice, &linearClampInfo);
    if (!sLinearClampSampler) {
        sys_fatal("Failed to create default linear clamp sampler: %s", SDL_GetError());
    }

    // init default linear depth sampler
    linearClampInfo.compare_op = SDL_GPU_COMPAREOP_LESS_OR_EQUAL;
    linearClampInfo.enable_compare = true;
    sLinearClampDepthSampler = SDL_CreateGPUSampler(sGpuDevice, &linearClampInfo);
    if (!sLinearClampDepthSampler) {
        sys_fatal("Failed to create default linear clamp depth sampler: %s", SDL_GetError());
    }

    // init default nearest sampler
    SDL_GPUSamplerCreateInfo nearestClampInfo = {
        .min_filter = SDL_GPU_FILTER_NEAREST,
        .mag_filter = SDL_GPU_FILTER_NEAREST,
        .address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
        .address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
        .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE
    };
    sNearestClampSampler = SDL_CreateGPUSampler(sGpuDevice, &nearestClampInfo);
    if (!sNearestClampSampler) {
        sys_fatal("Failed to create default nearest clamp sampler: %s", SDL_GetError());
    }

    // init default nearest depth sampler
    nearestClampInfo.compare_op = SDL_GPU_COMPAREOP_LESS_OR_EQUAL;
    nearestClampInfo.enable_compare = true;
    sNearestClampDepthSampler = SDL_CreateGPUSampler(sGpuDevice, &nearestClampInfo);
    if (!sNearestClampDepthSampler) {
        sys_fatal("Failed to create default linear clamp depth sampler: %s", SDL_GetError());
    }

    // create a fallback texture
    SDL_GPUTextureCreateInfo fallbackTexInfo = {
        .type = SDL_GPU_TEXTURETYPE_2D,
        .format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
        .usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
        .width = 2,
        .height = 2,
        .layer_count_or_depth = 1,
        .num_levels = 1
    };
    sFallbackTextureBinding.texture = SDL_CreateGPUTexture(sGpuDevice, &fallbackTexInfo);
    if (!sFallbackTextureBinding.texture) {
        sys_fatal("Failed to create fallback GPU texture: %s", SDL_GetError());
    }

    u8 fallbackPixels[16] = {
        255, 0, 0, 255,  0, 0, 0, 255,
        0, 0, 0, 255,      255, 0, 0, 255,
    };

    // define information for an upload
    SDL_GPUTransferBufferCreateInfo transferInfo = {
        .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
        .size = sizeof(fallbackPixels)
    };

    // create transfer buffer
    SDL_GPUTransferBuffer *transferBuffer = SDL_CreateGPUTransferBuffer(sGpuDevice, &transferInfo);

    if (transferBuffer == NULL) {
        sys_fatal("Failed to create transfer buffer for fallback GPU texture: %s", SDL_GetError());
    }

    // map pixels to buffer
    void *mapPtr = SDL_MapGPUTransferBuffer(sGpuDevice, transferBuffer, false);
    if (mapPtr == NULL) {
        sys_fatal("Failed to create map pointer for fallback GPU texture: %s", SDL_GetError());
    }
    memcpy(mapPtr, fallbackPixels, sizeof(fallbackPixels));
    SDL_UnmapGPUTransferBuffer(sGpuDevice, transferBuffer);

    // grab command buffer
    SDL_GPUCommandBuffer *cmdBuffer = SDL_AcquireGPUCommandBuffer(sGpuDevice);
    if (cmdBuffer == NULL) {
        sys_fatal("Failed to create command buffer for fallback GPU texture: %s", SDL_GetError());
    }

    // begin copy pass
    SDL_GPUCopyPass *copyPass = SDL_BeginGPUCopyPass(cmdBuffer);
    if (copyPass == NULL) {
        sys_fatal("Failed to create copy pass for fallback GPU texture: %s", SDL_GetError());
    }

    // grab the texture transfer info
    SDL_GPUTextureTransferInfo srcLocation = {
        .transfer_buffer = transferBuffer,
        .offset = 0
    };

    // grab the fallback texture and configure its dimensions
    SDL_GPUTextureRegion dstRegion = {
        .texture = sFallbackTextureBinding.texture,
        .w = 2,
        .h = 2,
        .d = 1
    };

    // upload fallback texture
    SDL_UploadToGPUTexture(copyPass, &srcLocation, &dstRegion, false);

    // cleanup
    SDL_EndGPUCopyPass(copyPass);
    SDL_SubmitGPUCommandBuffer(cmdBuffer);
    SDL_ReleaseGPUTransferBuffer(sGpuDevice, transferBuffer);

    sFallbackTextureBinding.sampler = sNearestClampSampler;

    // queue swapchain format
    sSwapchainFormat = SDL_GetGPUSwapchainTextureFormat(sGpuDevice, sSdlWindow);
    if (sSwapchainFormat == SDL_GPU_TEXTUREFORMAT_INVALID) {
        sSwapchainFormat = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    }

    // create vertex ring buffer
    gfx_sdl_gpu_create_ring_buffer(&sVertexRingBuffer, START_VERTEX_BUFFER_SLOT_SIZE, MAX_VERTEX_BUFFER_SLOT_SIZE, SDL_GPU_BUFFERUSAGE_VERTEX);

    // create depth texture
    gfx_sdl_gpu_create_depth_texture();
}

static void gfx_sdl_gpu_on_resize(void) {
    // get new dimensions
    u32 newWidth = 0;
    u32 newHeight = 0;
    gfx_wm_get_dimensions(&newWidth, &newHeight);

    // if they are the same, bail
    if (newWidth == sRenderWidth && newHeight == sRenderHeight && sDepthTexture != NULL) {
        return;
    }

    // submit current frame and dismiss internal textures
    gfx_sdl_gpu_submit_frame();

    for (s32 i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
        struct FramePass *framePass = &gFramePasses[i];
        if (!framePass->active) { continue; }

        if (framePass->width == 0 || framePass->height == 0) {
            // needs to be recreated to redo viewport size
            gfx_sdl_gpu_delete_framebuffer(framePass);
        }
    }

    // apply dimensions to render width and render height
    gfx_wm_get_dimensions(&sRenderWidth, &sRenderHeight);

    // create new depth texture
    gfx_sdl_gpu_create_depth_texture();
}

static void gfx_sdl_gpu_start_frame(void) {
    gfx_sdl_gpu_setup_command_buffer();
}

static void gfx_sdl_gpu_submit_frame(void) {
    gfx_sdl_gpu_end_render_pass();

    gfx_sdl_gpu_flush_vertex_uploads();

    // upload command buffers
    if (sUploadCmdBuffer != NULL) {
        SDL_SubmitGPUCommandBuffer(sUploadCmdBuffer);
        sUploadCmdBuffer = NULL;
    }

    if (sCmdBuffer != NULL) {
        SDL_SubmitGPUCommandBuffer(sCmdBuffer);
        sCmdBuffer = NULL;
    }

    // reset state
    sSwapchainTex = NULL;
    sStartedFrame = false;
    gfx_sdl_gpu_reset_ring_buffer_slot(&sVertexRingBuffer, (sVertexRingBuffer.slot + 1) % MAX_FRAMES_IN_FLIGHT);
    gfx_sdl_gpu_reset_state();

    sSwapchainCleared = false;
    memset(sFramePassCleared, 0, sizeof(sFramePassCleared));
}

static void gfx_sdl_gpu_end_frame(void) {
    gfx_sdl_gpu_end_render_pass();
    gfx_sdl_gpu_cleanup_internal_textures();
}

static void gfx_sdl_gpu_finish_render(void) {
    gfx_sdl_gpu_submit_frame();
}

static const char *gfx_sdl_gpu_get_name(void) {
    return "SDL Gpu";
}

static bool gfx_sdl_gpu_is_legacy(void) {
    return false;
}

static void gfx_sdl_gpu_shutdown(void) {
}

struct GfxRenderingAPI gfx_sdl_gpu_api = {
    gfx_sdl_gpu_z_is_from_0_to_1,
    gfx_sdl_gpu_unload_shader,
    gfx_sdl_gpu_load_shader,
    gfx_sdl_gpu_remove_shaders,
    gfx_sdl_gpu_create_and_load_new_shader,
    gfx_sdl_gpu_create_or_load_post_process_shader,
    gfx_sdl_gpu_lookup_shader,
    gfx_sdl_gpu_shader_get_info,
    gfx_sdl_gpu_create_framebuffer,
    gfx_sdl_gpu_delete_framebuffer,
    gfx_sdl_gpu_set_framebuffer,
    gfx_sdl_gpu_reset_framebuffer,
    gfx_sdl_gpu_get_active_uniform_buffer,
    gfx_sdl_gpu_set_uniform_buffer,
    gfx_sdl_gpu_set_uniform,
    gfx_sdl_gpu_get_texture_id,
    gfx_sdl_gpu_get_render_texture,
    gfx_sdl_gpu_select_texture,
    gfx_sdl_gpu_render_texture_valid,
    gfx_sdl_gpu_bind_texture_using_name,
    gfx_sdl_gpu_upload_texture,
    gfx_sdl_gpu_set_sampler_parameters,
    gfx_sdl_gpu_set_depth_test,
    gfx_sdl_gpu_set_depth_mask,
    gfx_sdl_gpu_set_zmode_decal,
    gfx_sdl_gpu_set_viewport,
    gfx_sdl_gpu_set_scissor,
    gfx_sdl_gpu_set_use_alpha,
    gfx_sdl_gpu_set_vsync,
    gfx_sdl_gpu_draw_triangles,
    gfx_sdl_gpu_init,
    gfx_sdl_gpu_on_resize,
    gfx_sdl_gpu_start_frame,
    gfx_sdl_gpu_end_frame,
    gfx_sdl_gpu_finish_render,
    gfx_sdl_gpu_get_name,
    gfx_sdl_gpu_is_legacy,
    gfx_sdl_gpu_shutdown
};
