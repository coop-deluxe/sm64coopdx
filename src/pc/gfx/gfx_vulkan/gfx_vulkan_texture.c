#include <stdlib.h>
#include <string.h>

#include <PR/gbi.h>

#include "../../platform.h"
#include "gfx_vulkan_context.h"
#include "gfx_vulkan_memory.h"
#include "gfx_vulkan_texture.h"

// Exact combinatorial max of (linear_filter x cms x cmt): G_TX_CLAMP/
// G_TX_MIRROR are two independent bits per axis, so 2 * 4 * 4 = 32 possible
// VkSamplers can ever be requested - the cache never needs to grow.
#define GFX_VULKAN_SAMPLER_CACHE_MAX 32
#define GFX_VULKAN_TEX_CACHE_STEP 256

typedef struct {
    GfxVulkanImage image;
    VkSampler sampler; // VK_NULL_HANDLE until set_sampler_parameters is called
    uint32_t width, height;
    bool linearFilter; // last value passed to set_sampler_parameters
} GfxVulkanTextureEntry;

typedef struct {
    bool linearFilter;
    uint32_t cms, cmt;
    VkSampler sampler;
} GfxVulkanSamplerCacheEntry;

static GfxVulkanTextureEntry *sTextures = NULL;
static uint32_t sTextureCount = 0;
static uint32_t sTextureCapacity = 0;

static uint32_t sBoundTexture[2] = { UINT32_MAX, UINT32_MAX };
static int sCurrentTile = 0;

static GfxVulkanSamplerCacheEntry sSamplerCache[GFX_VULKAN_SAMPLER_CACHE_MAX];
static uint32_t sSamplerCacheCount = 0;

static VkCommandPool sTransferPool = VK_NULL_HANDLE;

// Creates the transient command pool used for one-shot texture upload commands.
bool gfx_vulkan_texture_init(void) {
    VkCommandPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
        .queueFamilyIndex = gfxVkQueueFamily,
    };
    return vkCreateCommandPool(gfxVkDevice, &poolInfo, NULL, &sTransferPool) == VK_SUCCESS;
}

// Frees every texture image, every cached sampler, and the transfer pool.
void gfx_vulkan_texture_destroy(void) {
    for (uint32_t i = 0; i < sTextureCount; i++) {
        gfx_vulkan_memory_destroy_image(&sTextures[i].image);
    }
    free(sTextures);
    sTextures = NULL;
    sTextureCount = 0;
    sTextureCapacity = 0;
    sBoundTexture[0] = sBoundTexture[1] = UINT32_MAX;

    for (uint32_t i = 0; i < sSamplerCacheCount; i++) {
        vkDestroySampler(gfxVkDevice, sSamplerCache[i].sampler, NULL);
    }
    sSamplerCacheCount = 0;

    if (sTransferPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(gfxVkDevice, sTransferPool, NULL);
        sTransferPool = VK_NULL_HANDLE;
    }
}

// Reserves a new, empty texture slot and returns its id.
uint32_t gfx_vulkan_texture_new(void) {
    if (sTextureCount >= sTextureCapacity) {
        sTextureCapacity += GFX_VULKAN_TEX_CACHE_STEP;
        GfxVulkanTextureEntry *grown = realloc(sTextures, sTextureCapacity * sizeof(GfxVulkanTextureEntry));
        if (!grown) {
            sys_fatal("out of memory allocating vulkan texture cache");
        }
        sTextures = grown;
    }
    memset(&sTextures[sTextureCount], 0, sizeof(GfxVulkanTextureEntry));
    return sTextureCount++;
}

// Binds texture_id to the given RDP tile (0 or 1) for subsequent upload/draw calls.
void gfx_vulkan_texture_select(int tile, uint32_t texture_id) {
    sBoundTexture[tile] = texture_id;
    sCurrentTile = tile;
}

// Allocates and begins a one-time-submit command buffer from sTransferPool.
static VkCommandBuffer begin_immediate_commands(void) {
    VkCommandBufferAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = sTransferPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1,
    };
    VkCommandBuffer cmd = VK_NULL_HANDLE;
    if (vkAllocateCommandBuffers(gfxVkDevice, &allocInfo, &cmd) != VK_SUCCESS) {
        return VK_NULL_HANDLE;
    }

    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    vkBeginCommandBuffer(cmd, &beginInfo);
    return cmd;
}

// Submits cmd and blocks until the GPU finishes. Fine for the once-per-
// texture-load pattern this backend uses today; would need to become
// asynchronous if uploads ever had to happen every frame.
static void end_immediate_commands(VkCommandBuffer cmd) {
    vkEndCommandBuffer(cmd);

    VkCommandBufferSubmitInfo cmdInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
        .commandBuffer = cmd,
    };
    VkSubmitInfo2 submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .commandBufferInfoCount = 1,
        .pCommandBufferInfos = &cmdInfo,
    };

    VkFenceCreateInfo fenceInfo = { .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
    VkFence fence = VK_NULL_HANDLE;
    if (vkCreateFence(gfxVkDevice, &fenceInfo, NULL, &fence) == VK_SUCCESS) {
        if (vkQueueSubmit2(gfxVkQueue, 1, &submitInfo, fence) == VK_SUCCESS) {
            vkWaitForFences(gfxVkDevice, 1, &fence, VK_TRUE, UINT64_MAX);
        }
        vkDestroyFence(gfxVkDevice, fence, NULL);
    }
    vkFreeCommandBuffers(gfxVkDevice, sTransferPool, 1, &cmd);
}

// Uploads RGBA8 pixels to the texture currently bound on the current tile:
// staging buffer -> vkCmdCopyBufferToImage2, with UNDEFINED -> TRANSFER_DST ->
// SHADER_READ_ONLY layout transitions around the copy.
void gfx_vulkan_texture_upload(const uint8_t *rgba32_buf, int width, int height) {
    uint32_t id = sBoundTexture[sCurrentTile];
    if (id == UINT32_MAX || id >= sTextureCount) {
        return;
    }
    GfxVulkanTextureEntry *tex = &sTextures[id];

    if (tex->image.image != VK_NULL_HANDLE) {
        // Re-upload (e.g. a texture slot got reused): the old image might
        // still be referenced by an in-flight command buffer, so wait it out
        // before freeing. Simple and correct, not optimized - revisit if this
        // path ever becomes hot.
        vkDeviceWaitIdle(gfxVkDevice);
        gfx_vulkan_memory_destroy_image(&tex->image);
    }

    VkDeviceSize size = (VkDeviceSize)width * (VkDeviceSize)height * 4;
    GfxVulkanBuffer staging = { 0 };
    void *mapped = NULL;
    if (!gfx_vulkan_memory_create_streaming_buffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, &staging, &mapped)) {
        return;
    }
    memcpy(mapped, rgba32_buf, size);

    if (!gfx_vulkan_memory_create_image((uint32_t)width, (uint32_t)height, VK_FORMAT_R8G8B8A8_UNORM,
                                         VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                                         VK_IMAGE_ASPECT_COLOR_BIT, &tex->image)) {
        gfx_vulkan_memory_destroy_buffer(&staging);
        return;
    }

    VkCommandBuffer cmd = begin_immediate_commands();
    if (cmd != VK_NULL_HANDLE) {
        VkImageMemoryBarrier2 toTransferDst = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .srcStageMask = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT,
            .srcAccessMask = VK_ACCESS_2_NONE,
            .dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
            .dstAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT,
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = tex->image.image,
            .subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 },
        };
        VkDependencyInfo dep1 = {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .imageMemoryBarrierCount = 1,
            .pImageMemoryBarriers = &toTransferDst,
        };
        vkCmdPipelineBarrier2(cmd, &dep1);

        VkBufferImageCopy2 region = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2,
            .imageSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 },
            .imageExtent = { (uint32_t)width, (uint32_t)height, 1 },
        };
        VkCopyBufferToImageInfo2 copyInfo = {
            .sType = VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2,
            .srcBuffer = staging.buffer,
            .dstImage = tex->image.image,
            .dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            .regionCount = 1,
            .pRegions = &region,
        };
        vkCmdCopyBufferToImage2(cmd, &copyInfo);

        VkImageMemoryBarrier2 toShaderRead = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .srcStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
            .srcAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT,
            .dstAccessMask = VK_ACCESS_2_SHADER_READ_BIT,
            .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            .newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = tex->image.image,
            .subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 },
        };
        VkDependencyInfo dep2 = {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .imageMemoryBarrierCount = 1,
            .pImageMemoryBarriers = &toShaderRead,
        };
        vkCmdPipelineBarrier2(cmd, &dep2);

        end_immediate_commands(cmd);
    }

    gfx_vulkan_memory_destroy_buffer(&staging);

    tex->width = (uint32_t)width;
    tex->height = (uint32_t)height;
}

// Maps an RDP texture-tile wrap mode (G_TX_CLAMP/G_TX_MIRROR bits) to its
// closest VkSamplerAddressMode.
static VkSamplerAddressMode cm_to_vk_address_mode(uint32_t val) {
    if (val & G_TX_CLAMP) {
        return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    }
    return (val & G_TX_MIRROR) ? VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT : VK_SAMPLER_ADDRESS_MODE_REPEAT;
}

// Returns a cached VkSampler for this exact (filter, wrap) combination,
// creating and caching one if this is the first time it's requested.
static VkSampler get_or_create_sampler(bool linearFilter, uint32_t cms, uint32_t cmt) {
    for (uint32_t i = 0; i < sSamplerCacheCount; i++) {
        GfxVulkanSamplerCacheEntry *entry = &sSamplerCache[i];
        if (entry->linearFilter == linearFilter && entry->cms == cms && entry->cmt == cmt) {
            return entry->sampler;
        }
    }

    VkFilter filter = linearFilter ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
    VkSamplerCreateInfo samplerInfo = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filter,
        .minFilter = filter,
        .addressModeU = cm_to_vk_address_mode(cms),
        .addressModeV = cm_to_vk_address_mode(cmt),
        .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .maxLod = VK_LOD_CLAMP_NONE,
    };

    VkSampler sampler = VK_NULL_HANDLE;
    if (vkCreateSampler(gfxVkDevice, &samplerInfo, NULL, &sampler) != VK_SUCCESS) {
        return VK_NULL_HANDLE;
    }

    if (sSamplerCacheCount < GFX_VULKAN_SAMPLER_CACHE_MAX) {
        sSamplerCache[sSamplerCacheCount++] = (GfxVulkanSamplerCacheEntry){ linearFilter, cms, cmt, sampler };
    }
    return sampler;
}

// Assigns a (cached) sampler matching these filter/wrap settings to the
// texture currently bound on `tile`.
void gfx_vulkan_texture_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt) {
    uint32_t id = sBoundTexture[tile];
    if (id == UINT32_MAX || id >= sTextureCount) {
        return;
    }
    sTextures[id].sampler = get_or_create_sampler(linear_filter, cms, cmt);
    sTextures[id].linearFilter = linear_filter;
}

// See gfx_vulkan_texture.h.
bool gfx_vulkan_texture_get_bound(int tile, VkImageView *outView, VkSampler *outSampler) {
    uint32_t id = sBoundTexture[tile];
    if (id == UINT32_MAX || id >= sTextureCount) {
        return false;
    }
    GfxVulkanTextureEntry *tex = &sTextures[id];
    if (tex->image.view == VK_NULL_HANDLE || tex->sampler == VK_NULL_HANDLE) {
        return false;
    }
    *outView = tex->image.view;
    *outSampler = tex->sampler;
    return true;
}

// See gfx_vulkan_texture.h.
bool gfx_vulkan_texture_get_bound_info(int tile, float outSize[2], bool *outLinearFilter) {
    uint32_t id = sBoundTexture[tile];
    if (id == UINT32_MAX || id >= sTextureCount) {
        return false;
    }
    GfxVulkanTextureEntry *tex = &sTextures[id];
    outSize[0] = (float)tex->width;
    outSize[1] = (float)tex->height;
    *outLinearFilter = tex->linearFilter;
    return true;
}
