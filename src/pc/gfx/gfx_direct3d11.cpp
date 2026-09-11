#if defined(_WIN32)

#include <cstdio>
#include <vector>
#include <cmath>
#include <string>

#include <windows.h>
#include <versionhelpers.h>
#include <wrl/client.h>

#include <dxgi1_3.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#ifndef _LANGUAGE_C
#define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#include "types.h"
#include "pc/configfile.h"

#include "gfx_cc.h"
#include "gfx_window_manager.h"
#include "gfx_rendering_api.h"
#include "gfx_shader.h"

#include "game/rendering_graph_node.h"

extern "C" {
#include "gfx_pc.h"
#include "pc/lua/smlua.h"
#include "pc/mods/mods_utils.h"
#include "pc/controller/controller_bind_mapping.h"
#include "engine/math_util.h"
extern Color gVertexColor;
}

#define DECLARE_GFX_DXGI_FUNCTIONS
#include "gfx_window_dxgi.h"

#include "gfx_screen_config.h"

#define DEBUG_D3D 0

using namespace Microsoft::WRL; // For ComPtr

namespace {

struct TextureData {
    ComPtr<ID3D11ShaderResourceView> resource_view;
    ComPtr<ID3D11SamplerState> sampler_state;
    uint32_t width;
    uint32_t height;
    bool linear_filtering;
};

struct ShaderProgramD3D11 {
    ComPtr<ID3D11VertexShader> dx_vertex_shader;
    ComPtr<ID3D11PixelShader> dx_pixel_shader;
    ComPtr<ID3D11InputLayout> input_layout;
    ComPtr<ID3D11BlendState> blend_state;

    struct Shader *vertex_shader;
    struct Shader *fragment_shader;

    uint64_t hash;
    uint8_t num_inputs;
    uint8_t num_floats;
    bool used_textures[2];
    bool used_lightmap;
    bool used_fog;
    bool world_geometry;
};

static struct {
    HMODULE d3d11_module;
    PFN_D3D11_CREATE_DEVICE D3D11CreateDevice;

    HMODULE d3dcompiler_module;
    pD3DCompile D3DCompile;

    D3D_FEATURE_LEVEL feature_level;

    ComPtr<ID3D11Device> device;
    ComPtr<IDXGISwapChain1> swap_chain;
    ComPtr<ID3D11DeviceContext> context;
    ComPtr<ID3D11RenderTargetView> backbuffer_view;
    ComPtr<ID3D11DepthStencilView> depth_stencil_view;
    ComPtr<ID3D11RasterizerState> rasterizer_state;
    ComPtr<ID3D11DepthStencilState> depth_stencil_state;
    ComPtr<ID3D11Buffer> vertex_buffer;

#if DEBUG_D3D
    ComPtr<ID3D11Debug> debug;
#endif

    DXGI_SAMPLE_DESC sample_description;

    struct ShaderProgramD3D11 shader_program_pool[MAX_FRAME_PASSES][CC_MAX_SHADERS];
    u8 shader_program_pool_size[MAX_FRAME_PASSES] = { 0 };
    u8 shader_program_pool_index[MAX_FRAME_PASSES] = { 0 };

    struct ShaderProgramD3D11 post_process_shader_program_pool[MAX_FRAME_PASSES];

    std::vector<struct TextureData> textures;
    int current_tile;
    u32 current_texture_ids[2];

    // Current state

    struct ShaderProgramD3D11 *shader_program;

    u32 current_width, current_height;

    s8 depth_test;
    s8 depth_mask;
    s8 zmode_decal;

    // Previous states (to prevent setting states needlessly)

    struct ShaderProgramD3D11 *last_shader_program = nullptr;
    u32 last_vertex_buffer_stride = 0;
    ComPtr<ID3D11BlendState> last_blend_state = nullptr;
    ComPtr<ID3D11ShaderResourceView> last_resource_views[2] = { nullptr, nullptr };
    ComPtr<ID3D11SamplerState> last_sampler_states[2] = { nullptr, nullptr };
    s8 last_depth_test = -1;
    s8 last_depth_mask = -1;
    s8 last_zmode_decal = -1;
    D3D_PRIMITIVE_TOPOLOGY last_primitive_topology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
} d3d;

static LARGE_INTEGER last_time, accumulated_time, frequency;

float frameCount = 0;

static void create_render_target_views(bool is_resize) {
    DXGI_SWAP_CHAIN_DESC1 desc1;

    if (is_resize) {
        // Release previous stuff (if any)

        d3d.backbuffer_view.Reset();
        d3d.depth_stencil_view.Reset();

        // Resize swap chain buffers

        ThrowIfFailed(d3d.swap_chain->GetDesc1(&desc1));
        ThrowIfFailed(d3d.swap_chain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, desc1.Flags),
                      gfx_window_dxgi_get_h_wnd(), "Failed to resize IDXGISwapChain buffers.");
    }

    // Get new size

    ThrowIfFailed(d3d.swap_chain->GetDesc1(&desc1));

    // Create back buffer

    ComPtr<ID3D11Texture2D> backbuffer_texture;
    ThrowIfFailed(d3d.swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *) backbuffer_texture.GetAddressOf()),
                  gfx_window_dxgi_get_h_wnd(), "Failed to get backbuffer from IDXGISwapChain.");

    ThrowIfFailed(d3d.device->CreateRenderTargetView(backbuffer_texture.Get(), nullptr, d3d.backbuffer_view.GetAddressOf()),
                  gfx_window_dxgi_get_h_wnd(), "Failed to create render target view.");

    // Create depth buffer

    D3D11_TEXTURE2D_DESC depth_stencil_texture_desc;
    ZeroMemory(&depth_stencil_texture_desc, sizeof(D3D11_TEXTURE2D_DESC));

    depth_stencil_texture_desc.Width = desc1.Width;
    depth_stencil_texture_desc.Height = desc1.Height;
    depth_stencil_texture_desc.MipLevels = 1;
    depth_stencil_texture_desc.ArraySize = 1;
    depth_stencil_texture_desc.Format = d3d.feature_level >= D3D_FEATURE_LEVEL_10_0 ?
                                        DXGI_FORMAT_D32_FLOAT : DXGI_FORMAT_D24_UNORM_S8_UINT;
    depth_stencil_texture_desc.SampleDesc = d3d.sample_description;
    depth_stencil_texture_desc.Usage = D3D11_USAGE_DEFAULT;
    depth_stencil_texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depth_stencil_texture_desc.CPUAccessFlags = 0;
    depth_stencil_texture_desc.MiscFlags = 0;

    ComPtr<ID3D11Texture2D> depth_stencil_texture;
    ThrowIfFailed(d3d.device->CreateTexture2D(&depth_stencil_texture_desc, nullptr, depth_stencil_texture.GetAddressOf()));
    ThrowIfFailed(d3d.device->CreateDepthStencilView(depth_stencil_texture.Get(), nullptr, d3d.depth_stencil_view.GetAddressOf()));

    // Save resolution

    d3d.current_width = desc1.Width;
    d3d.current_height = desc1.Height;
}

static void gfx_d3d11_init(void) {
    // Load d3d11.dll
    d3d.d3d11_module = LoadLibraryW(L"d3d11.dll");
    if (d3d.d3d11_module == nullptr) {
        ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()), gfx_window_dxgi_get_h_wnd(), "d3d11.dll could not be loaded");
    }
    d3d.D3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)GetProcAddress(d3d.d3d11_module, "D3D11CreateDevice");

    // Load D3DCompiler_47.dll or D3DCompiler_43.dll
    d3d.d3dcompiler_module = LoadLibraryW(L"D3DCompiler_47.dll");
    if (d3d.d3dcompiler_module == nullptr) {
        d3d.d3dcompiler_module = LoadLibraryW(L"D3DCompiler_43.dll");
        if (d3d.d3dcompiler_module == nullptr) {
            ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()), gfx_window_dxgi_get_h_wnd(), "D3DCompiler_47.dll or D3DCompiler_43.dll could not be loaded");
        }
    }
    d3d.D3DCompile = (pD3DCompile)GetProcAddress(d3d.d3dcompiler_module, "D3DCompile");

    // Create D3D11 device

    gfx_window_dxgi_create_factory_and_device(DEBUG_D3D, 11, [](IDXGIAdapter1 *adapter, bool test_only) {
#if DEBUG_D3D
        UINT device_creation_flags = D3D11_CREATE_DEVICE_DEBUG;
#else
        UINT device_creation_flags = 0;
#endif
        D3D_FEATURE_LEVEL FeatureLevels[] = {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1
        };

        HRESULT res = d3d.D3D11CreateDevice(
            adapter,
            D3D_DRIVER_TYPE_UNKNOWN, // since we use a specific adapter
            nullptr,
            device_creation_flags,
            FeatureLevels,
            ARRAYSIZE(FeatureLevels),
            D3D11_SDK_VERSION,
            test_only ? nullptr : d3d.device.GetAddressOf(),
            &d3d.feature_level,
            test_only ? nullptr : d3d.context.GetAddressOf());

        if (test_only) {
            return SUCCEEDED(res);
        } else {
            ThrowIfFailed(res, gfx_window_dxgi_get_h_wnd(), "Failed to create D3D11 device.");
            return true;
        }
    });

    // Sample description to be used in back buffer and depth buffer

    d3d.sample_description.Count = 1;
    d3d.sample_description.Quality = 0;

    // Create the swap chain
    d3d.swap_chain = gfx_window_dxgi_create_swap_chain(d3d.device.Get());

    // Create D3D Debug device if in debug mode

#if DEBUG_D3D
    ThrowIfFailed(d3d.device->QueryInterface(__uuidof(ID3D11Debug), (void **) d3d.debug.GetAddressOf()),
                  gfx_window_dxgi_get_h_wnd(), "Failed to get ID3D11Debug device.");
#endif

    // Create views

    create_render_target_views(false);

    // Create main vertex buffer

    D3D11_BUFFER_DESC vertex_buffer_desc;
    ZeroMemory(&vertex_buffer_desc, sizeof(D3D11_BUFFER_DESC));

    vertex_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    vertex_buffer_desc.ByteWidth = VERTEX_STRIDE * sizeof(float); // Same as buf_vbo stride size in gfx_pc
    vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertex_buffer_desc.MiscFlags = 0;

    ThrowIfFailed(d3d.device->CreateBuffer(&vertex_buffer_desc, nullptr, d3d.vertex_buffer.GetAddressOf()),
                  gfx_window_dxgi_get_h_wnd(), "Failed to create vertex buffer.");

    controller_bind_init();
}

static bool gfx_d3d11_z_is_from_0_to_1(void) {
    return true;
}

static void gfx_d3d11_unload_shader(struct ShaderProgram *old_prg) {
}

static void gfx_d3d11_load_shader(struct ShaderProgram *new_prg) {
    d3d.shader_program = (struct ShaderProgramD3D11 *)new_prg;
}

static void gfx_d3d11_remove_shaders(void) {
    for (int i = 0; i < MAX_FRAME_PASSES; i++) {
        for (int j = 0; j < CC_MAX_SHADERS; j++) {
            gfx_destroy_shader(d3d.shader_program_pool[i][j].vertex_shader);
            gfx_destroy_shader(d3d.shader_program_pool[i][j].fragment_shader);
            d3d.shader_program_pool[i][j] = { 0 };
        }
        d3d.shader_program_pool_index[i] = 0;
        d3d.shader_program_pool_size[i] = 0;
        gfx_destroy_shader(d3d.post_process_shader_program_pool[i].vertex_shader);
        gfx_destroy_shader(d3d.post_process_shader_program_pool[i].fragment_shader);
        d3d.post_process_shader_program_pool[i] = { 0 };
    }

    d3d.shader_program = nullptr;
    d3d.last_shader_program = nullptr;
}

static struct ShaderProgram *gfx_d3d11_create_and_load_new_shader(struct ColorCombiner* cc) {
    CCFeatures cc_features = { 0 };
    gfx_cc_get_features(cc, &cc_features);

    struct Shader *vertexShader = (struct Shader *)calloc(1, sizeof(struct Shader));
    struct Shader *fragmentShader = (struct Shader *)calloc(1, sizeof(struct Shader));
    if (!vertexShader || !fragmentShader) {
        sys_fatal("Failed to allocate shaders, ran out of memory!");
    }

    gfx_generate_vertex_and_fragment_shader_from_cc(vertexShader, fragmentShader, cc, nullptr, nullptr);

    char *vs_hlsl = nullptr;
    char *ps_hlsl = nullptr;

    gfx_convert_spirv_to_hlsl(&vs_hlsl, vertexShader);
    gfx_convert_spirv_to_hlsl(&ps_hlsl, fragmentShader);

    ComPtr<ID3DBlob> vs, ps;
    ComPtr<ID3DBlob> error_blob;

#if DEBUG_D3D
    UINT compile_flags = D3DCOMPILE_DEBUG;
#else
    UINT compile_flags = D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    HRESULT hr = d3d.D3DCompile(vs_hlsl, strlen(vs_hlsl), nullptr, nullptr, nullptr, "main", "vs_5_0", compile_flags, 0, vs.GetAddressOf(), error_blob.GetAddressOf());

    if (FAILED(hr)) {
        MessageBox(gfx_window_dxgi_get_h_wnd(), (char *)error_blob->GetBufferPointer(), "Vertex Shader Error", MB_OK | MB_ICONERROR);
        free(vs_hlsl);
        free(ps_hlsl);
        throw hr;
    }

    hr = d3d.D3DCompile(ps_hlsl, strlen(ps_hlsl), nullptr, nullptr, nullptr, "main", "ps_5_0", compile_flags, 0, ps.GetAddressOf(), error_blob.GetAddressOf());

    if (FAILED(hr)) {
        MessageBox(gfx_window_dxgi_get_h_wnd(), (char *)error_blob->GetBufferPointer(), "Pixel Shader Error", MB_OK | MB_ICONERROR);
        free(vs_hlsl);
        free(ps_hlsl);
        throw hr;
    }

    free(vs_hlsl);
    free(ps_hlsl);

    int framePassIndex = gCurrentFramePassIndex + 1;

    struct ShaderProgramD3D11 *prg = &d3d.shader_program_pool[framePassIndex][d3d.shader_program_pool_index[framePassIndex]];
    d3d.shader_program_pool_index[framePassIndex] = (d3d.shader_program_pool_index[framePassIndex] + 1) % CC_MAX_SHADERS;
    if (d3d.shader_program_pool_size[framePassIndex] < CC_MAX_SHADERS) { d3d.shader_program_pool_size[framePassIndex]++; }

    ThrowIfFailed(d3d.device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, prg->dx_vertex_shader.GetAddressOf()));
    ThrowIfFailed(d3d.device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, prg->dx_pixel_shader.GetAddressOf()));

    // Input Layout

    D3D11_INPUT_ELEMENT_DESC ied[16];
    uint8_t ied_index = 0;
    // iterate through saved inputs
    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        // make sure it's not empty
        if (gShaderInputs[i].size == 0) { continue; }

        int loc = vertexShader->shaderInputs[i].location;
        int size = vertexShader->shaderInputs[i].size;

        DXGI_FORMAT element_format = DXGI_FORMAT_R32G32B32A32_FLOAT;

        switch (vertexShader->shaderInputs[i].size) {
            case 1: element_format = DXGI_FORMAT_R32_FLOAT; break;
            case 2: element_format = DXGI_FORMAT_R32G32_FLOAT; break;
            case 3: element_format = DXGI_FORMAT_R32G32B32_FLOAT; break;
            case 4: element_format = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
        }

        // SPIR-V sets inputs to TEXCOORD, so use that here
        ied[ied_index++] = {
            "TEXCOORD",
            (UINT)loc,
            element_format,
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        };
    }

    if (ied_index > 0) {
        ThrowIfFailed(d3d.device->CreateInputLayout(
            ied,
            ied_index,
            vs->GetBufferPointer(),
            vs->GetBufferSize(),
            prg->input_layout.GetAddressOf()
        ), gfx_window_dxgi_get_h_wnd(), "Failed to create shader input layout.");
    } else {
        prg->input_layout = nullptr;
    }

    // Blend state

    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));

    if (cc->cm.use_alpha) {
        blend_desc.RenderTarget[0].BlendEnable = true;
        blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    } else {
        blend_desc.RenderTarget[0].BlendEnable = false;
        blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    }

    ThrowIfFailed(d3d.device->CreateBlendState(&blend_desc, prg->blend_state.GetAddressOf()));

    // Save some values

    size_t cnt = 0;
    size_t num_floats = 0;

    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        if (gShaderInputs[i].size == 0) { continue; }
        num_floats += gShaderInputs[i].size;
        cnt++;
    }

    prg->hash = cc->hash;
    prg->num_inputs = cc_features.num_inputs;
    prg->num_floats = num_floats;
    prg->used_textures[0] = cc_features.used_textures[0];
    prg->used_textures[1] = cc_features.used_textures[1];
    prg->used_lightmap = cc->cm.light_map;
    prg->used_fog = cc->cm.use_fog;
    prg->vertex_shader = vertexShader;
    prg->fragment_shader = fragmentShader;
    prg->world_geometry = cc->cm.world_geometry;

    return (struct ShaderProgram *)(d3d.shader_program = prg);
}

static struct ShaderProgram *gfx_d3d11_create_or_load_post_process_shader(void) {
    int framePassIndex = gCurrentFramePassIndex + 1;
    struct ShaderProgramD3D11 *prg = &d3d.post_process_shader_program_pool[framePassIndex];

    // check and load from cache
    if (prg->dx_vertex_shader != nullptr) {
        d3d.shader_program = prg;
        return (struct ShaderProgram *)prg;
    }

    struct Shader *vertexShader = (struct Shader *)calloc(1, sizeof(struct Shader));
    struct Shader *fragmentShader = (struct Shader *)calloc(1, sizeof(struct Shader));
    if (!vertexShader || !fragmentShader) {
        sys_fatal("Failed to allocate shaders, ran out of memory!");
    }

    gfx_generate_post_process_vertex_and_fragment_shader(vertexShader, fragmentShader, nullptr, nullptr);

    // get hlsl shader from spirv
    char *vs_hlsl = nullptr;
    char *ps_hlsl = nullptr;
    gfx_convert_spirv_to_hlsl(&vs_hlsl, vertexShader);
    gfx_convert_spirv_to_hlsl(&ps_hlsl, fragmentShader);

    ComPtr<ID3DBlob> vs, ps;
    ComPtr<ID3DBlob> error_blob;

#if DEBUG_D3D
    UINT compile_flags = D3DCOMPILE_DEBUG;
#else
    UINT compile_flags = D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    HRESULT hr = d3d.D3DCompile(vs_hlsl, strlen(vs_hlsl), nullptr, nullptr, nullptr, "main", "vs_5_0", compile_flags, 0, vs.GetAddressOf(), error_blob.GetAddressOf());
    if (FAILED(hr)) {
        MessageBox(gfx_window_dxgi_get_h_wnd(), (char *)error_blob->GetBufferPointer(), "Post-Process VS Error", MB_OK | MB_ICONERROR);
        free(vs_hlsl);
        free(ps_hlsl);
        throw hr;
    }

    hr = d3d.D3DCompile(ps_hlsl, strlen(ps_hlsl), nullptr, nullptr, nullptr, "main", "ps_5_0", compile_flags, 0, ps.GetAddressOf(), error_blob.GetAddressOf());
    if (FAILED(hr)) {
        MessageBox(gfx_window_dxgi_get_h_wnd(), (char *)error_blob->GetBufferPointer(), "Post-Process PS Error", MB_OK | MB_ICONERROR);
        free(vs_hlsl);
        free(ps_hlsl);
        throw hr;
    }

    free(vs_hlsl);
    free(ps_hlsl);

    ThrowIfFailed(d3d.device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, prg->dx_vertex_shader.GetAddressOf()));
    ThrowIfFailed(d3d.device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, prg->dx_pixel_shader.GetAddressOf()));

    // generate input layout
    D3D11_INPUT_ELEMENT_DESC ied[MAX_SHADER_INPUTS];
    uint8_t ied_index = 0;
    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        if (gPostProcessShaderInputs[i].size == 0) { continue; }

        int loc = vertexShader->shaderInputs[i].location;
        DXGI_FORMAT element_format = DXGI_FORMAT_R32G32B32A32_FLOAT;

        switch (vertexShader->shaderInputs[i].size) {
            case 1: element_format = DXGI_FORMAT_R32_FLOAT; break;
            case 2: element_format = DXGI_FORMAT_R32G32_FLOAT; break;
            case 3: element_format = DXGI_FORMAT_R32G32B32_FLOAT; break;
            case 4: element_format = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
        }

        // SPIR-V sets inputs to TEXCOORD, so use that here
        ied[ied_index++] = {
            "TEXCOORD",
            (UINT)loc,
            element_format,
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        };
    }

    if (ied_index > 0) {
        ThrowIfFailed(d3d.device->CreateInputLayout(ied, ied_index, vs->GetBufferPointer(), vs->GetBufferSize(), prg->input_layout.GetAddressOf()));
    } else {
        prg->input_layout = nullptr;
    }

    // disable blending
    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));
    blend_desc.RenderTarget[0].BlendEnable = false;
    blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    ThrowIfFailed(d3d.device->CreateBlendState(&blend_desc, prg->blend_state.GetAddressOf()));

    // get vertex shader stride
    size_t num_floats = 0;
    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        num_floats += gPostProcessShaderInputs[i].size;
    }

    prg->hash = framePassIndex;
    prg->num_inputs = ied_index;
    prg->num_floats = num_floats;
    prg->used_textures[0] = true;
    prg->used_textures[1] = false;
    prg->used_lightmap = false;
    prg->used_fog = false;
    prg->vertex_shader = vertexShader;
    prg->fragment_shader = fragmentShader;
    prg->world_geometry = false;

    d3d.shader_program = prg;
    return (struct ShaderProgram *)prg;
}

static struct ShaderProgram *gfx_d3d11_lookup_shader(struct ColorCombiner* cc) {
    int framePassIndex = gCurrentFramePassIndex + 1;
    if (framePassIndex < 0 || framePassIndex >= MAX_FRAME_PASSES) { return nullptr; }
    for (size_t i = 0; i < d3d.shader_program_pool_size[framePassIndex]; i++) {
        if (d3d.shader_program_pool[framePassIndex][i].hash == cc->hash) {
            return (struct ShaderProgram *)&d3d.shader_program_pool[framePassIndex][i];
        }
    }
    return nullptr;
}

static struct ShaderProgram *gfx_d3d11_lookup_shader_using_index(u8 shaderIndex, u8 framePassIndex) {
    framePassIndex++;
    if (shaderIndex >= d3d.shader_program_pool_size[framePassIndex]) { return nullptr; }
    return (struct ShaderProgram *)&d3d.shader_program_pool[framePassIndex][shaderIndex];
}

static void gfx_d3d11_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    struct ShaderProgramD3D11 *p = (struct ShaderProgramD3D11 *)prg;

    *num_inputs = p->num_inputs;
    used_textures[0] = p->used_textures[0];
    used_textures[1] = p->used_textures[1];
}

static void gfx_d3d11_delete_framebuffer(struct FramePass *framePass);

static void gfx_d3d11_create_framebuffer(struct FramePass *framePass) {
    u32 viewportWidth;
    u32 viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(framePass, &viewportWidth, &viewportHeight);

    // create frame pass texture
    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.Width = viewportWidth;
    texDesc.Height = viewportHeight;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    texDesc.CPUAccessFlags = 0;
    texDesc.MiscFlags = 0;

    ID3D11Texture2D *colorTexture = nullptr;
    HRESULT hr = d3d.device->CreateTexture2D(&texDesc, nullptr, &colorTexture);
    if (FAILED(hr)) { return; }

    hr = d3d.device->CreateRenderTargetView(colorTexture, nullptr, (ID3D11RenderTargetView**)&framePass->d3dRtv);
    if (FAILED(hr)) { gfx_d3d11_delete_framebuffer(framePass); return; }
    hr = d3d.device->CreateShaderResourceView(colorTexture, nullptr, (ID3D11ShaderResourceView**)&framePass->d3dSrv);
    if (FAILED(hr)) { gfx_d3d11_delete_framebuffer(framePass); return; }
    framePass->passTexture = (u64)framePass->d3dSrv;

    colorTexture->Release();

    // create depth texture
    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = viewportWidth;
    depthDesc.Height = viewportHeight;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.SampleDesc.Quality = 0;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthDesc.CPUAccessFlags = 0;
    depthDesc.MiscFlags = 0;

    ID3D11Texture2D *depthTexture = nullptr;
    hr = d3d.device->CreateTexture2D(&depthDesc, nullptr, &depthTexture);
    if (SUCCEEDED(hr)) {
        hr = d3d.device->CreateDepthStencilView(depthTexture, nullptr, (ID3D11DepthStencilView**)&framePass->d3dDsv);
        depthTexture->Release();
    }

    // fbo is created so mark it as such
    framePass->fbo = 1;
}

static void gfx_d3d11_delete_framebuffer(struct FramePass *framePass) {
    if (framePass->d3dRtv) { ((ID3D11RenderTargetView*)framePass->d3dRtv)->Release(); framePass->d3dRtv = nullptr; }
    if (framePass->d3dSrv) { ((ID3D11ShaderResourceView*)framePass->d3dSrv)->Release(); framePass->d3dSrv = nullptr; }
    if (framePass->d3dDsv) { ((ID3D11DepthStencilView*)framePass->d3dDsv)->Release(); framePass->d3dDsv = nullptr; }
    framePass->fbo = 0;
}

static void gfx_d3d11_set_framebuffer(struct FramePass *framePass) {
    u32 viewportWidth;
    u32 viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(framePass, &viewportWidth, &viewportHeight);

    ID3D11RenderTargetView *rtv = (ID3D11RenderTargetView*)framePass->d3dRtv;
    ID3D11DepthStencilView *dsv = (ID3D11DepthStencilView*)framePass->d3dDsv;

    // set render target
    d3d.context->OMSetRenderTargets(1, &rtv, dsv);

    // setup viewport
    D3D11_VIEWPORT vp;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 0.0f;
    vp.Width = (float)viewportWidth;
    vp.Height = (float)viewportHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    d3d.context->RSSetViewports(1, &vp);

    // reset scissor
    D3D11_RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = viewportWidth;
    rect.bottom = viewportHeight;
    d3d.context->RSSetScissorRects(1, &rect);
}

static void gfx_d3d11_reset_framebuffer(void) {
    // get current window dimensions
    u32 windowWidth, windowHeight;
    gfx_get_dimensions(&windowWidth, &windowHeight);

    // set render target
    ID3D11RenderTargetView *rtv = d3d.backbuffer_view.Get();
    ID3D11DepthStencilView *dsv = d3d.depth_stencil_view.Get();
    d3d.context->OMSetRenderTargets(1, &rtv, dsv);

    // setup viewport
    D3D11_VIEWPORT vp;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 0.0f;
    vp.Width = (float)windowWidth;
    vp.Height = (float)windowHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    d3d.context->RSSetViewports(1, &vp);

    // reset scissor
    D3D11_RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = windowWidth;
    rect.bottom = windowHeight;
    d3d.context->RSSetScissorRects(1, &rect);
}

size_t gfx_d3d11_get_uniform_buffer_size(enum ShaderStage stage, int bufferIndex) {
    if (bufferIndex < 0 || bufferIndex >= MAX_UNIFORM_BLOCKS) { return 0; }

    struct Shader *shader = NULL;
    if (stage == SHADER_STAGE_VERTEX) {
        shader = d3d.shader_program->vertex_shader;
    } else if (stage == SHADER_STAGE_FRAGMENT) {
        shader = d3d.shader_program->fragment_shader;
    } else {
        return 0;
    }

    return shader->uniformBlocks[bufferIndex].size;
}

void gfx_d3d11_set_uniform_buffer(enum ShaderStage stage, const char *name) {
    struct Shader *shader = NULL;
    int *destination = NULL;
    if (stage == SHADER_STAGE_VERTEX) {
        shader = d3d.shader_program->vertex_shader;
        destination = &gSelectedVertexUniformBuffer;
    } else if (stage == SHADER_STAGE_FRAGMENT) {
        shader = d3d.shader_program->fragment_shader;
        destination = &gSelectedFragmentUniformBuffer;
    } else {
        return;
    }

    for (int i = 0; i < MAX_UNIFORM_BLOCKS; i++) {
        struct ShaderUniformBlock *uniformBlock = &shader->uniformBlocks[i];

        if (strcmp(uniformBlock->name, name) == 0) {
            *destination = i;
        }
    }
}

static void gfx_d3d11_set_uniform_for_specific_shader(struct ShaderUniformBlock *uniformBlock, const char *name, ShaderUniformType type, const void *data, uint32_t numElements) {
    for (int i = 0; i < MAX_SHADER_UNIFORMS; i++) {
        struct ShaderUniform *uniform = &uniformBlock->uniforms[i];
        if (uniform->size == 0) { break; }

        if (strcmp(uniform->name, name) == 0) {
            // get starting location of pointer
            u8 *dst = uniformBlock->buffer;
            // increment pointer by our uniform location
            dst += uniform->location;

            if (uniform->arrayLength > 1) {
                const u8 *src = (const u8 *)data;
                u32 count = MIN(numElements, uniform->arrayLength); // don't let numElements write to garbage data
                for (u32 j = 0; j < count; j++) {
                    memcpy(dst + j * uniform->arrayStride, src + j * uniform->elementSize, uniform->elementSize);
                }
            } else {
                memcpy(dst, data, uniform->size);
            }

            return;
        }
    }
}

void gfx_d3d11_set_uniform(struct ShaderProgram *prg, const char *name, ShaderUniformType type, const void *data, uint32_t numElements) {
    struct ShaderProgramD3D11 *d3d11_prg = (struct ShaderProgramD3D11 *)prg;
    if (d3d11_prg == NULL) {
        if (d3d.shader_program == NULL) { return; }
        d3d11_prg = d3d.shader_program;
    }

    if (gfx_shader_stage_is(SHADER_STAGE_VERTEX)) {
        gfx_d3d11_set_uniform_for_specific_shader(&d3d11_prg->vertex_shader->uniformBlocks[gSelectedVertexUniformBuffer], name, type, data, numElements);
    }
    if (gfx_shader_stage_is(SHADER_STAGE_FRAGMENT)) {
        gfx_d3d11_set_uniform_for_specific_shader(&d3d11_prg->fragment_shader->uniformBlocks[gSelectedFragmentUniformBuffer], name, type, data, numElements);
    }
}

static uint32_t gfx_d3d11_new_texture(void) {
    d3d.textures.resize(d3d.textures.size() + 1);
    return (uint32_t)(d3d.textures.size() - 1);
}

static void gfx_d3d11_select_texture(int tile, uint32_t texture_id) {
    d3d.current_tile = tile;
    d3d.current_texture_ids[tile] = texture_id;
}

static void gfx_d3d11_bind_texture_raw(int tile, u64 texture_id) {
    ID3D11ShaderResourceView *srv = (ID3D11ShaderResourceView *)texture_id;
    d3d.context->PSSetShaderResources(tile, 1, &srv);
    if (tile < MAX_TEXTURES) {
        d3d.last_resource_views[tile] = srv;
    } else {
        // find our frame pass from our texture id
        struct FramePass *currentFramePass = NULL;

        for (int i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
            struct FramePass *framePass = &gFramePasses[i];
            if (!framePass->active) { continue; }
            if (framePass->passTexture != texture_id) { continue; }
            currentFramePass = framePass;
            break;
        }

        if (currentFramePass == NULL) {
            // we have to be the geo pass
            currentFramePass = &gDefaultGeoFramePass;
        }

        ComPtr<ID3D11SamplerState> textureSampler;

        D3D11_SAMPLER_DESC desc = {};
        desc.Filter = currentFramePass->passFilter == PASS_FILTER_LINEAR ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_POINT;
        desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        desc.MinLOD = 0.0f;
        desc.MaxLOD = D3D11_FLOAT32_MAX;
        desc.MaxAnisotropy = 1;
        desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

        ThrowIfFailed(d3d.device->CreateSamplerState(&desc, textureSampler.GetAddressOf()));

        // set sampler
        ID3D11SamplerState *sampler = textureSampler.Get();
        d3d.context->PSSetSamplers(tile, 1, &sampler);
    }
}

static D3D11_TEXTURE_ADDRESS_MODE gfx_cm_to_d3d11(uint32_t val) {
    if (val & G_TX_CLAMP) {
        return D3D11_TEXTURE_ADDRESS_CLAMP;
    }
    return (val & G_TX_MIRROR) ? D3D11_TEXTURE_ADDRESS_MIRROR : D3D11_TEXTURE_ADDRESS_WRAP;
}

static void gfx_d3d11_upload_texture(const uint8_t *rgba32_buf, int width, int height) {
    // Create texture

    D3D11_TEXTURE2D_DESC texture_desc;
    ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));

    texture_desc.Width = width;
    texture_desc.Height = height;
    texture_desc.Usage = D3D11_USAGE_IMMUTABLE;
    texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texture_desc.CPUAccessFlags = 0;
    texture_desc.MiscFlags = 0; // D3D11_RESOURCE_MISC_GENERATE_MIPS ?
    texture_desc.ArraySize = 1;
    texture_desc.MipLevels = 1;
    texture_desc.SampleDesc.Count = 1;
    texture_desc.SampleDesc.Quality = 0;

    D3D11_SUBRESOURCE_DATA resource_data;
    resource_data.pSysMem = rgba32_buf;
    resource_data.SysMemPitch = width * 4;
    resource_data.SysMemSlicePitch = resource_data.SysMemPitch * height;

    ComPtr<ID3D11Texture2D> texture;
    ThrowIfFailed(d3d.device->CreateTexture2D(&texture_desc, &resource_data, texture.GetAddressOf()));

    // Create shader resource view from texture

    D3D11_SHADER_RESOURCE_VIEW_DESC resource_view_desc;
    ZeroMemory(&resource_view_desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

    resource_view_desc.Format = texture_desc.Format;
    resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    resource_view_desc.Texture2D.MostDetailedMip = 0;
    resource_view_desc.Texture2D.MipLevels = -1;

    TextureData *texture_data = &d3d.textures[d3d.current_texture_ids[d3d.current_tile]];
    texture_data->width = width;
    texture_data->height = height;

    if (texture_data->resource_view.Get() != nullptr) {
        // Free the previous texture in this slot
        texture_data->resource_view.Reset();
    }

    ThrowIfFailed(d3d.device->CreateShaderResourceView(texture.Get(), &resource_view_desc, texture_data->resource_view.GetAddressOf()));
}

static void gfx_d3d11_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt) {
    D3D11_SAMPLER_DESC sampler_desc;
    ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));

    sampler_desc.Filter = linear_filter ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_POINT;
    sampler_desc.AddressU = gfx_cm_to_d3d11(cms);
    sampler_desc.AddressV = gfx_cm_to_d3d11(cmt);
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.MinLOD = 0;
    sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

    TextureData *texture_data = &d3d.textures[d3d.current_texture_ids[tile]];
    texture_data->linear_filtering = linear_filter;

    // This function is called twice per texture, the first one only to set default values.
    // Maybe that could be skipped? Anyway, make sure to release the first default sampler
    // state before setting the actual one.
    texture_data->sampler_state.Reset();

    ThrowIfFailed(d3d.device->CreateSamplerState(&sampler_desc, texture_data->sampler_state.GetAddressOf()));
}

static void gfx_d3d11_set_depth_test(bool depth_test) {
    d3d.depth_test = depth_test;
}

static void gfx_d3d11_set_depth_mask(bool depth_mask) {
    d3d.depth_mask = depth_mask;
}

static void gfx_d3d11_set_zmode_decal(bool zmode_decal) {
    d3d.zmode_decal = zmode_decal;
}

static void gfx_d3d11_set_viewport(int x, int y, int width, int height) {
    struct FramePass *framePass = gfx_get_current_frame_pass();
    u32 viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(framePass, NULL, &viewportHeight);
    D3D11_VIEWPORT viewport;
    viewport.TopLeftX = x;
    viewport.TopLeftY = viewportHeight - y - height;
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    d3d.context->RSSetViewports(1, &viewport);
}

static void gfx_d3d11_set_scissor(int x, int y, int width, int height) {
    struct FramePass *framePass = gfx_get_current_frame_pass();
    u32 viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(framePass, NULL, &viewportHeight);
    D3D11_RECT rect;
    rect.left = x;
    rect.top = viewportHeight - y - height;
    rect.right = x + width;
    rect.bottom = viewportHeight - y;

    d3d.context->RSSetScissorRects(1, &rect);
}

static void gfx_d3d11_set_use_alpha(bool use_alpha) {
    // Already part of the pipeline state from shader info
}

static void gfx_d3d11_set_vsync(bool enabled) {
}

static void upload_uniform_buffers_for_shader(struct Shader *shader) {
    for (int i = 0; i < shader->uniformBlockCount; i++) {
        struct ShaderUniformBlock *uniformBlock = &shader->uniformBlocks[i];
        if (uniformBlock->size > 0 && uniformBlock->dxConstantBuffer != NULL) {
            D3D11_MAPPED_SUBRESOURCE ms;
            ZeroMemory(&ms, sizeof(D3D11_MAPPED_SUBRESOURCE));

            HRESULT hr = d3d.context->Map(uniformBlock->dxConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
            if (SUCCEEDED(hr)) {
                memcpy(ms.pData, uniformBlock->buffer, uniformBlock->size);
                d3d.context->Unmap(uniformBlock->dxConstantBuffer, 0);
            }

            if (shader->stage == SHADER_STAGE_VERTEX) {
                d3d.context->VSSetConstantBuffers(uniformBlock->location, 1, &uniformBlock->dxConstantBuffer);
            } else if (shader->stage == SHADER_STAGE_FRAGMENT) {
                d3d.context->PSSetConstantBuffers(uniformBlock->location, 1, &uniformBlock->dxConstantBuffer);
            }
        }
    }
}

static void gfx_d3d11_draw_triangles(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {
    if (d3d.last_depth_test != d3d.depth_test || d3d.last_depth_mask != d3d.depth_mask) {
        d3d.last_depth_test = d3d.depth_test;
        d3d.last_depth_mask = d3d.depth_mask;

        d3d.depth_stencil_state.Reset();

        D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
        ZeroMemory(&depth_stencil_desc, sizeof(D3D11_DEPTH_STENCIL_DESC));

        depth_stencil_desc.DepthEnable = d3d.depth_test;
        depth_stencil_desc.DepthWriteMask = d3d.depth_mask ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
        depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
        depth_stencil_desc.StencilEnable = false;

        ThrowIfFailed(d3d.device->CreateDepthStencilState(&depth_stencil_desc, d3d.depth_stencil_state.GetAddressOf()));
        d3d.context->OMSetDepthStencilState(d3d.depth_stencil_state.Get(), 0);
    }

    if (d3d.last_zmode_decal != d3d.zmode_decal) {
        d3d.last_zmode_decal = d3d.zmode_decal;

        d3d.rasterizer_state.Reset();

        D3D11_RASTERIZER_DESC rasterizer_desc;
        ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

        rasterizer_desc.FillMode = D3D11_FILL_SOLID;
        rasterizer_desc.CullMode = D3D11_CULL_NONE;
        rasterizer_desc.FrontCounterClockwise = true;
        rasterizer_desc.DepthBias = 0;
        rasterizer_desc.SlopeScaledDepthBias = d3d.zmode_decal ? -2.0f : 0.0f;
        rasterizer_desc.DepthBiasClamp = 0.0f;
        rasterizer_desc.DepthClipEnable = true;
        rasterizer_desc.ScissorEnable = true;
        rasterizer_desc.MultisampleEnable = false;
        rasterizer_desc.AntialiasedLineEnable = false;

        ThrowIfFailed(d3d.device->CreateRasterizerState(&rasterizer_desc, d3d.rasterizer_state.GetAddressOf()));
        d3d.context->RSSetState(d3d.rasterizer_state.Get());
    }

    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (d3d.shader_program->used_textures[i]) {
            TextureData &texture_data = d3d.textures[d3d.current_texture_ids[i]];
            bool resource_changed = d3d.last_resource_views[i].Get() != texture_data.resource_view.Get();
            bool sampler_changed = d3d.last_sampler_states[i].Get() != texture_data.sampler_state.Get();

            if (resource_changed) {
                d3d.last_resource_views[i] = texture_data.resource_view.Get();
                d3d.context->PSSetShaderResources(i, 1, texture_data.resource_view.GetAddressOf());
            }

            if (sampler_changed) {
                d3d.last_sampler_states[i] = texture_data.sampler_state.Get();
                d3d.context->PSSetSamplers(i, 1, texture_data.sampler_state.GetAddressOf());
            }

            if (resource_changed || sampler_changed) {
                char sizeUniformName[MAX_SHADER_VARIABLE_NAME];
                snprintf(sizeUniformName, sizeof(sizeUniformName), "uTex%dSize", i);
                float texSize[2] = { (float)texture_data.width, (float)texture_data.height };

                gfx_d3d11_set_uniform(NULL, sizeUniformName, SHADER_UNIFORM_TYPE_VEC2, texSize, 1);

                char filterUniformName[MAX_SHADER_VARIABLE_NAME];
                snprintf(filterUniformName, sizeof(filterUniformName), "uTex%dFilter", i);
                u32 isLinear = texture_data.linear_filtering ? 1 : 0;

                gfx_d3d11_set_uniform(NULL, filterUniformName, SHADER_UNIFORM_TYPE_INT, &isLinear, 1);
            }
        }
    }

    gfx_update_matrices();
    if (d3d.shader_program->used_fog) {
        gfx_update_fog_uniforms();
    }
    smlua_call_event_hooks(HOOK_ON_DRAW_TRIANGLE);

    upload_uniform_buffers_for_shader(d3d.shader_program->vertex_shader);
    upload_uniform_buffers_for_shader(d3d.shader_program->fragment_shader);

    // Set vertex buffer data

    D3D11_MAPPED_SUBRESOURCE ms;
    ZeroMemory(&ms, sizeof(D3D11_MAPPED_SUBRESOURCE));
    d3d.context->Map(d3d.vertex_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    memcpy(ms.pData, buf_vbo, buf_vbo_len * sizeof(float));
    d3d.context->Unmap(d3d.vertex_buffer.Get(), 0);

    uint32_t stride = d3d.shader_program->num_floats * sizeof(float);
    uint32_t offset = 0;

    if (d3d.last_vertex_buffer_stride != stride) {
        d3d.last_vertex_buffer_stride = stride;
        d3d.context->IASetVertexBuffers(0, 1, d3d.vertex_buffer.GetAddressOf(), &stride, &offset);
    }

    if (d3d.last_shader_program != d3d.shader_program) {
        d3d.last_shader_program = d3d.shader_program;
        d3d.context->IASetInputLayout(d3d.shader_program->input_layout.Get());
        d3d.context->VSSetShader(d3d.shader_program->dx_vertex_shader.Get(), 0, 0);
        d3d.context->PSSetShader(d3d.shader_program->dx_pixel_shader.Get(), 0, 0);

        if (d3d.last_blend_state.Get() != d3d.shader_program->blend_state.Get()) {
            d3d.last_blend_state = d3d.shader_program->blend_state.Get();
            d3d.context->OMSetBlendState(d3d.shader_program->blend_state.Get(), 0, 0xFFFFFFFF);
        }
    }

    if (d3d.last_primitive_topology != D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST) {
        d3d.last_primitive_topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        d3d.context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    ID3D11VertexShader* currentVS = nullptr;
    ID3D11PixelShader* currentPS = nullptr;
    ID3D11InputLayout* currentLayout = nullptr;

    d3d.context->VSGetShader(&currentVS, nullptr, nullptr);
    d3d.context->PSGetShader(&currentPS, nullptr, nullptr);
    d3d.context->IAGetInputLayout(&currentLayout);

    // Safely release the local query references
    if(currentVS) currentVS->Release();
    if(currentPS) currentPS->Release();
    if(currentLayout) currentLayout->Release();

    d3d.context->Draw(buf_vbo_num_tris * 3, 0);
}

static void gfx_d3d11_on_resize(void) {
    for (int i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
        struct FramePass *framePass = &gFramePasses[i];
        if (!framePass->active) { continue; }

        if (framePass->width == 0 || framePass->height == 0) {
            // needs to be recreated to redo viewport size
            gfx_d3d11_delete_framebuffer(framePass);
        }
    }
    create_render_target_views(true);
}

static void gfx_d3d11_start_frame(void) {
    struct FramePass *framePass = gfx_get_current_frame_pass();

    // get current render targets for clearing
    ID3D11RenderTargetView *currentRtv = nullptr;
    ID3D11DepthStencilView *currentDsv = nullptr;

    d3d.context->OMGetRenderTargets(1, &currentRtv, &currentDsv);

    // Prepare clear colors
    float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    if (framePass) {
        clearColor[0] = framePass->clearColor[0] / 255.0f;
        clearColor[1] = framePass->clearColor[1] / 255.0f;
        clearColor[2] = framePass->clearColor[2] / 255.0f;
        clearColor[3] = framePass->clearColor[3] / 255.0f;
    }

    // clear render targets
    d3d.context->ClearRenderTargetView(currentRtv, clearColor);
    d3d.context->ClearDepthStencilView(currentDsv, D3D11_CLEAR_DEPTH, 1.0f, 0);

    currentRtv->Release();
    currentDsv->Release();

    frameCount++;
}

static void gfx_d3d11_end_frame(void) {
}

static const char *gfx_d3d11_get_name(void) {
    return "DirectX 11";
}

static bool gfx_d3d11_is_legacy(void) {
    return false;
}

static void gfx_d3d11_finish_render(void) {
}

} // namespace

struct GfxRenderingAPI gfx_direct3d11_api = {
    gfx_d3d11_z_is_from_0_to_1,
    gfx_d3d11_unload_shader,
    gfx_d3d11_load_shader,
    gfx_d3d11_remove_shaders,
    gfx_d3d11_create_and_load_new_shader,
    gfx_d3d11_create_or_load_post_process_shader,
    gfx_d3d11_lookup_shader,
    gfx_d3d11_lookup_shader_using_index,
    gfx_d3d11_shader_get_info,
    gfx_d3d11_create_framebuffer,
    gfx_d3d11_delete_framebuffer,
    gfx_d3d11_set_framebuffer,
    gfx_d3d11_reset_framebuffer,
    gfx_d3d11_get_uniform_buffer_size,
    gfx_d3d11_set_uniform_buffer,
    gfx_d3d11_set_uniform,
    gfx_d3d11_new_texture,
    gfx_d3d11_select_texture,
    gfx_d3d11_bind_texture_raw,
    gfx_d3d11_upload_texture,
    gfx_d3d11_set_sampler_parameters,
    gfx_d3d11_set_depth_test,
    gfx_d3d11_set_depth_mask,
    gfx_d3d11_set_zmode_decal,
    gfx_d3d11_set_viewport,
    gfx_d3d11_set_scissor,
    gfx_d3d11_set_use_alpha,
    gfx_d3d11_set_vsync,
    gfx_d3d11_draw_triangles,
    gfx_d3d11_init,
    gfx_d3d11_on_resize,
    gfx_d3d11_start_frame,
    gfx_d3d11_end_frame,
    gfx_d3d11_finish_render,
    gfx_d3d11_get_name,
    gfx_d3d11_is_legacy,
};

extern "C" void d3d11_create_buffer_for_block(struct ShaderUniformBlock *block) {
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.ByteWidth = block->size;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    HRESULT hr = d3d.device->CreateBuffer(&bufferDesc, NULL, &block->dxConstantBuffer);
    if (FAILED(hr)) {
        sys_fatal("Failed to allocate d3d constant buffer for %s", block->name);
    }
}

#endif
