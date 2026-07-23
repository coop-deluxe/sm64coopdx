#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../configfile.h"
#include "../../fs/fs.h"
#include "../gfx_pc.h"
#include "gfx_vulkan_context.h"
#include "gfx_vulkan_swapchain.h"
#include "gfx_vulkan_frame.h"
#include "gfx_vulkan_memory.h"
#include "gfx_vulkan_texture.h"
#include "gfx_vulkan_shader.h"
#include "gfx_vulkan_pipeline.h"

#include <volk.h>

// Mirrors the `FrameUBO` block gfx_vulkan_shader.c emits into every fragment
// shader (layout(std140, set = 0, binding = 0)). std140 rounds vec3 up to a
// 16-byte slot and gives every array element its own 16-byte slot regardless
// of the element's own size - hence the explicit padding/[4] arrays below;
// only index [i][0] of the array members is ever written.
typedef struct {
    float uFrameCount;
    float _pad0[3];
    float uLightmapColor[3];
    float _pad1;
    int32_t uShaderFlags[SHADER_FLAG_MAX][4];
    float uShaderFlagValues[SHADER_FLAG_MAX][4];
    int32_t uFilter;
    float _pad2[3];
} GfxVulkanFrameUBO;

static VkDescriptorSetLayout sFrameSetLayout = VK_NULL_HANDLE;   // set 0: UBO, dynamic offset
static VkDescriptorSetLayout sTextureSetLayout = VK_NULL_HANDLE; // set 1: push descriptor, 2 samplers
static VkDescriptorPool sDescriptorPool = VK_NULL_HANDLE;
static VkDescriptorSet sFrameDescriptorSet = VK_NULL_HANDLE;
VkPipelineLayout gfxVkPipelineLayout = VK_NULL_HANDLE;
static VkPipelineCache sPipelineCache = VK_NULL_HANDLE;

static GfxVulkanBuffer sFrameUboBuffer;
static uint8_t *sFrameUboMapped = NULL;
static VkDeviceSize sFrameUboSliceStride = 0; // sizeof(GfxVulkanFrameUBO) rounded up to minUniformBufferOffsetAlignment

// Creates the two shared descriptor set layouts: set 0 (frame UBO) and set 1
// (push-descriptor textures).
static bool create_set_layouts(void) {
    VkDescriptorSetLayoutBinding frameBinding = {
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
    };
    VkDescriptorSetLayoutCreateInfo frameInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = &frameBinding,
    };
    if (vkCreateDescriptorSetLayout(gfxVkDevice, &frameInfo, NULL, &sFrameSetLayout) != VK_SUCCESS) {
        return false;
    }

    VkDescriptorSetLayoutBinding texBindings[2] = {
        { .binding = 0, .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, .descriptorCount = 1, .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT },
        { .binding = 1, .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, .descriptorCount = 1, .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT },
    };
    VkDescriptorSetLayoutCreateInfo texInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR,
        .bindingCount = 2,
        .pBindings = texBindings,
    };
    return vkCreateDescriptorSetLayout(gfxVkDevice, &texInfo, NULL, &sTextureSetLayout) == VK_SUCCESS;
}

// Creates gfxVkPipelineLayout from the two set layouts plus the draw push constant range.
static bool create_pipeline_layout(void) {
    VkDescriptorSetLayout setLayouts[2] = { sFrameSetLayout, sTextureSetLayout };
    VkPushConstantRange pushRange = {
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
        .offset = 0,
        .size = sizeof(GfxVulkanDrawPushConstants),
    };
    VkPipelineLayoutCreateInfo layoutInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 2,
        .pSetLayouts = setLayouts,
        .pushConstantRangeCount = 1,
        .pPushConstantRanges = &pushRange,
    };
    return vkCreatePipelineLayout(gfxVkDevice, &layoutInfo, NULL, &gfxVkPipelineLayout) == VK_SUCCESS;
}

// Rounds value up to the next multiple of alignment (alignment must be a power of two).
static VkDeviceSize align_up(VkDeviceSize value, VkDeviceSize alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}

// Allocates the persistently-mapped frame UBO buffer: one slice per
// frame-in-flight slot, each padded to the device's uniform buffer offset
// alignment.
static bool create_frame_ubo(void) {
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(gfxVkPhysicalDevice, &props);
    VkDeviceSize alignment = props.limits.minUniformBufferOffsetAlignment;
    if (alignment == 0) { alignment = 1; }

    sFrameUboSliceStride = align_up(sizeof(GfxVulkanFrameUBO), alignment);

    void *mapped = NULL;
    if (!gfx_vulkan_memory_create_streaming_buffer(sFrameUboSliceStride * GFX_VULKAN_FRAMES_IN_FLIGHT,
                                                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &sFrameUboBuffer, &mapped)) {
        return false;
    }
    sFrameUboMapped = (uint8_t *)mapped;
    return true;
}

// Allocates the single descriptor set for the frame UBO (set 0) and points
// it at sFrameUboBuffer.
static bool create_descriptor_set(void) {
    VkDescriptorPoolSize poolSize = {
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        .descriptorCount = 1,
    };
    VkDescriptorPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = 1,
        .poolSizeCount = 1,
        .pPoolSizes = &poolSize,
    };
    if (vkCreateDescriptorPool(gfxVkDevice, &poolInfo, NULL, &sDescriptorPool) != VK_SUCCESS) {
        return false;
    }

    VkDescriptorSetAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = sDescriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &sFrameSetLayout,
    };
    if (vkAllocateDescriptorSets(gfxVkDevice, &allocInfo, &sFrameDescriptorSet) != VK_SUCCESS) {
        return false;
    }

    VkDescriptorBufferInfo bufferInfo = {
        .buffer = sFrameUboBuffer.buffer,
        .offset = 0,
        .range = sizeof(GfxVulkanFrameUBO),
    };
    VkWriteDescriptorSet write = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = sFrameDescriptorSet,
        .dstBinding = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        .pBufferInfo = &bufferInfo,
    };
    vkUpdateDescriptorSets(gfxVkDevice, 1, &write, 0, NULL);
    return true;
}

#define GFX_VULKAN_PIPELINE_CACHE_FILE "vulkan_pipeline_cache.bin"

// Same convention configfile.c uses for sm64config.txt: fopen() directly on
// fs_get_write_path(), bypassing the read-only virtual/mounted asset
// filesystem in fs.c (that one is for mods/dynos packs, not per-install
// cache blobs). A stale/incompatible blob (different GPU, driver version,
// etc.) is safe to hand to vkCreatePipelineCache unconditionally: the spec
// requires the driver to silently discard initial data whose header doesn't
// match the current device instead of failing, so no manual validation of
// vendorID/deviceID/pipelineCacheUUID is needed here.
static void *load_pipeline_cache_blob(size_t *outSize) {
    FILE *f = fopen(fs_get_write_path(GFX_VULKAN_PIPELINE_CACHE_FILE), "rb");
    if (!f) {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size <= 0) {
        fclose(f);
        return NULL;
    }
    fseek(f, 0, SEEK_SET);

    void *buf = malloc((size_t)size);
    if (!buf) {
        fclose(f);
        return NULL;
    }
    size_t rd = fread(buf, 1, (size_t)size, f);
    fclose(f);
    if (rd != (size_t)size) {
        free(buf);
        return NULL;
    }

    *outSize = (size_t)size;
    return buf;
}

// Writes the current VkPipelineCache contents to disk; a no-op if the cache is empty.
static void save_pipeline_cache_blob(void) {
    size_t size = 0;
    if (vkGetPipelineCacheData(gfxVkDevice, sPipelineCache, &size, NULL) != VK_SUCCESS || size == 0) {
        return;
    }
    void *data = malloc(size);
    if (!data) {
        return;
    }
    if (vkGetPipelineCacheData(gfxVkDevice, sPipelineCache, &size, data) == VK_SUCCESS) {
        FILE *f = fopen(fs_get_write_path(GFX_VULKAN_PIPELINE_CACHE_FILE), "wb");
        if (f) {
            fwrite(data, 1, size, f);
            fclose(f);
        }
    }
    free(data);
}

// Loads the on-disk pipeline cache (if any), then creates the shared
// descriptor set layouts, pipeline layout, frame UBO, and descriptor set.
bool gfx_vulkan_pipeline_init(void) {
    size_t blobSize = 0;
    void *blob = load_pipeline_cache_blob(&blobSize);

    VkPipelineCacheCreateInfo cacheInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO,
        .initialDataSize = blobSize,
        .pInitialData = blob,
    };
    VkResult res = vkCreatePipelineCache(gfxVkDevice, &cacheInfo, NULL, &sPipelineCache);
    free(blob);
    if (res != VK_SUCCESS) {
        return false;
    }

    return create_set_layouts() && create_pipeline_layout() && create_frame_ubo() && create_descriptor_set();
}

// Persists the pipeline cache to disk, then frees every resource this module owns.
void gfx_vulkan_pipeline_destroy(void) {
    if (sDescriptorPool != VK_NULL_HANDLE) {
        vkDestroyDescriptorPool(gfxVkDevice, sDescriptorPool, NULL);
        sDescriptorPool = VK_NULL_HANDLE;
        sFrameDescriptorSet = VK_NULL_HANDLE;
    }
    gfx_vulkan_memory_destroy_buffer(&sFrameUboBuffer);
    sFrameUboMapped = NULL;

    if (gfxVkPipelineLayout != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(gfxVkDevice, gfxVkPipelineLayout, NULL);
        gfxVkPipelineLayout = VK_NULL_HANDLE;
    }
    if (sTextureSetLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(gfxVkDevice, sTextureSetLayout, NULL);
        sTextureSetLayout = VK_NULL_HANDLE;
    }
    if (sFrameSetLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(gfxVkDevice, sFrameSetLayout, NULL);
        sFrameSetLayout = VK_NULL_HANDLE;
    }
    if (sPipelineCache != VK_NULL_HANDLE) {
        save_pipeline_cache_blob();
        vkDestroyPipelineCache(gfxVkDevice, sPipelineCache, NULL);
        sPipelineCache = VK_NULL_HANDLE;
    }
}

// Maps a vertex attribute's width (in floats) to the matching VkFormat.
static VkFormat vk_format_for_attrib_size(uint8_t sizeInFloats) {
    switch (sizeInFloats) {
        case 2: return VK_FORMAT_R32G32_SFLOAT;
        case 3: return VK_FORMAT_R32G32B32_SFLOAT;
        default: return VK_FORMAT_R32G32B32A32_SFLOAT;
    }
}

// Builds one VkPipeline: vertex input derived from prg's baked attribute
// layout, fixed rasterization/blend state, and viewport/scissor/depth-test/
// depth-write/depth-bias/blend-enable left as dynamic state (set per-frame by
// gfx_vulkan_draw.c, not baked per pipeline).
VkPipeline gfx_vulkan_pipeline_create(VkShaderModule vertModule, VkShaderModule fragModule, const struct ShaderProgram *prg) {
    VkVertexInputBindingDescription binding = {
        .binding = 0,
        .stride = (uint32_t)prg->num_floats * sizeof(float),
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
    };
    VkVertexInputAttributeDescription attrs[GFX_VULKAN_MAX_ATTRIBS];
    uint32_t offsetFloats = 0;
    for (uint8_t i = 0; i < prg->num_attribs; i++) {
        attrs[i] = (VkVertexInputAttributeDescription){
            .location = i,
            .binding = 0,
            .format = vk_format_for_attrib_size(prg->attrib_sizes[i]),
            .offset = offsetFloats * (uint32_t)sizeof(float),
        };
        offsetFloats += prg->attrib_sizes[i];
    }
    VkPipelineVertexInputStateCreateInfo vertexInput = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &binding,
        .vertexAttributeDescriptionCount = prg->num_attribs,
        .pVertexAttributeDescriptions = attrs,
    };

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, // batched, non-indexed
    };
    VkPipelineViewportStateCreateInfo viewportState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount = 1,
    };
    VkPipelineRasterizationStateCreateInfo rasterization = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_NONE, // culling always happens on CPU
        .lineWidth = 1.0f,
    };
    VkPipelineMultisampleStateCreateInfo multisample = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT, // no MSAA, same precedent as the D3D11 backend
    };
    // depthCompareOp matches gfx_opengl_init's glDepthFunc(GL_LEQUAL); test/
    // write/bias-enable are dynamic state (gfx_vulkan_draw.c's
    // set_depth_test/set_depth_mask/set_zmode_decal).
    VkPipelineDepthStencilStateCreateInfo depthStencil = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
    };
    // Fixed blend equation - only the enable bit is dynamic
    // (VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT, set_use_alpha).
    VkPipelineColorBlendAttachmentState blendAttachment = {
        .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp = VK_BLEND_OP_ADD,
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                           VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    };
    VkPipelineColorBlendStateCreateInfo colorBlend = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = &blendAttachment,
    };

    VkDynamicState dynamicStates[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
        VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE,
        VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE,
        VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE,
        VK_DYNAMIC_STATE_DEPTH_BIAS,
        VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT,
    };
    VkPipelineDynamicStateCreateInfo dynamicState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = (uint32_t)(sizeof(dynamicStates) / sizeof(dynamicStates[0])),
        .pDynamicStates = dynamicStates,
    };

    VkPipelineShaderStageCreateInfo stages[2] = {
        { .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, .stage = VK_SHADER_STAGE_VERTEX_BIT, .module = vertModule, .pName = "main" },
        { .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, .stage = VK_SHADER_STAGE_FRAGMENT_BIT, .module = fragModule, .pName = "main" },
    };
    VkPipelineRenderingCreateInfo renderingInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
        .colorAttachmentCount = 1,
        .pColorAttachmentFormats = &gfxVkSwapchainFormat,
        .depthAttachmentFormat = gfxVkDepthFormat,
    };
    VkGraphicsPipelineCreateInfo pipelineInfo = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext = &renderingInfo,
        .stageCount = 2,
        .pStages = stages,
        .pVertexInputState = &vertexInput,
        .pInputAssemblyState = &inputAssembly,
        .pViewportState = &viewportState,
        .pRasterizationState = &rasterization,
        .pMultisampleState = &multisample,
        .pDepthStencilState = &depthStencil,
        .pColorBlendState = &colorBlend,
        .pDynamicState = &dynamicState,
        .layout = gfxVkPipelineLayout,
    };

    VkPipeline pipeline = VK_NULL_HANDLE;
    VkResult res = vkCreateGraphicsPipelines(gfxVkDevice, sPipelineCache, 1, &pipelineInfo, NULL, &pipeline);
    if (res != VK_SUCCESS) {
        fprintf(stderr, "[vulkan] vkCreateGraphicsPipelines failed: %d\n", res);
        return VK_NULL_HANDLE;
    }
    return pipeline;
}

// See gfx_vulkan_pipeline.h.
void gfx_vulkan_pipeline_update_frame_ubo(uint32_t frameCount) {
    uint32_t slot = gfx_vulkan_frame_get_current_slot();
    uint8_t *dst = sFrameUboMapped + slot * sFrameUboSliceStride;

    GfxVulkanFrameUBO ubo = { 0 };
    ubo.uFrameCount = (float)frameCount;
    ubo.uLightmapColor[0] = gVertexColor[0] / 255.0f;
    ubo.uLightmapColor[1] = gVertexColor[1] / 255.0f;
    ubo.uLightmapColor[2] = gVertexColor[2] / 255.0f;
    for (int i = 0; i < SHADER_FLAG_MAX; i++) {
        ubo.uShaderFlags[i][0] = gShaderFlags[i];
        ubo.uShaderFlagValues[i][0] = gShaderFlagValues[i];
    }
    ubo.uFilter = (int32_t)configFiltering;

    memcpy(dst, &ubo, sizeof(ubo));

    uint32_t dynamicOffset = slot * (uint32_t)sFrameUboSliceStride;
    vkCmdBindDescriptorSets(gfxVkCurrentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, gfxVkPipelineLayout,
                             0, 1, &sFrameDescriptorSet, 1, &dynamicOffset);
}

// See gfx_vulkan_pipeline.h.
void gfx_vulkan_pipeline_bind_textures(const bool usedTextures[2]) {
    VkWriteDescriptorSet writes[2];
    VkDescriptorImageInfo imageInfos[2];
    uint32_t writeCount = 0;

    for (int tile = 0; tile < 2; tile++) {
        if (!usedTextures[tile]) { continue; }
        VkImageView view;
        VkSampler sampler;
        if (!gfx_vulkan_texture_get_bound(tile, &view, &sampler)) { continue; }

        imageInfos[writeCount] = (VkDescriptorImageInfo){
            .sampler = sampler,
            .imageView = view,
            .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        };
        writes[writeCount] = (VkWriteDescriptorSet){
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstBinding = (uint32_t)tile,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .pImageInfo = &imageInfos[writeCount],
        };
        writeCount++;
    }

    if (writeCount > 0) {
        vkCmdPushDescriptorSetKHR(gfxVkCurrentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, gfxVkPipelineLayout,
                                   1, writeCount, writes);
    }
}

// See gfx_vulkan_pipeline.h.
void gfx_vulkan_pipeline_push_draw_constants(const GfxVulkanDrawPushConstants *pc) {
    vkCmdPushConstants(gfxVkCurrentCommandBuffer, gfxVkPipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(*pc), pc);
}
