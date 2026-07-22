#if defined(ENABLE_VULKAN)

#ifndef GFX_VULKAN_MEMORY_H
#define GFX_VULKAN_MEMORY_H

#include <stdbool.h>
#include <stdint.h>
#include <volk.h>

// Thin wrapper over VMA (gfx_vulkan/vma) - the only module allowed to call
// vma* functions directly. Callers get plain Vk handles plus an opaque
// allocation handle, so vk_mem_alloc.h never needs to be included elsewhere.
bool gfx_vulkan_memory_init(void);
void gfx_vulkan_memory_destroy(void);

typedef struct {
    VkBuffer buffer;
    void *allocation; // VmaAllocation, kept opaque here on purpose
} GfxVulkanBuffer;

typedef struct {
    VkImage image;
    VkImageView view;
    void *allocation; // VmaAllocation, kept opaque here on purpose
} GfxVulkanImage;

// Device-local, no CPU access - data written once via a staging buffer and
// read many times by the GPU.
bool gfx_vulkan_memory_create_device_local_buffer(VkDeviceSize size, VkBufferUsageFlags usage, GfxVulkanBuffer *out);

// Host-visible, persistently mapped - for data the CPU writes often (texture
// staging uploads, per-frame vertex streaming). *outMappedPtr stays valid for
// the buffer's lifetime; pass NULL if not needed.
bool gfx_vulkan_memory_create_streaming_buffer(VkDeviceSize size, VkBufferUsageFlags usage, GfxVulkanBuffer *out, void **outMappedPtr);

void gfx_vulkan_memory_destroy_buffer(GfxVulkanBuffer *buf);

// Device-local 2D image + a matching VK_IMAGE_VIEW_TYPE_2D view (aspect mask
// given by `aspect` - COLOR_BIT for textures/color images, DEPTH_BIT for the
// depth buffer) over its full extent, one mip level, one array layer. Starts
// in VK_IMAGE_LAYOUT_UNDEFINED; the caller is responsible for any layout
// transitions.
bool gfx_vulkan_memory_create_image(uint32_t width, uint32_t height, VkFormat format, VkImageUsageFlags usage, VkImageAspectFlags aspect, GfxVulkanImage *out);
void gfx_vulkan_memory_destroy_image(GfxVulkanImage *img);

#endif // GFX_VULKAN_MEMORY_H

#endif // ENABLE_VULKAN
