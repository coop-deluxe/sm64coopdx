#include <string.h>

#include "gfx_vulkan_context.h"
#include "gfx_vulkan_memory.h"

#include <volk.h>
#include <vk_mem_alloc.h>

static VmaAllocator sAllocator = VK_NULL_HANDLE;

// Creates the VMA allocator, loading Vulkan entry points through volk instead
// of linking libvulkan directly (VMA_DYNAMIC_VULKAN_FUNCTIONS).
bool gfx_vulkan_memory_init(void) {
    VmaVulkanFunctions vulkanFunctions = { 0 };
    vulkanFunctions.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
    vulkanFunctions.vkGetDeviceProcAddr = vkGetDeviceProcAddr;

    VmaAllocatorCreateInfo createInfo = { 0 };
    createInfo.vulkanApiVersion = VK_API_VERSION_1_3;
    createInfo.physicalDevice = gfxVkPhysicalDevice;
    createInfo.device = gfxVkDevice;
    createInfo.instance = gfxVkInstance;
    createInfo.pVulkanFunctions = &vulkanFunctions;

    return vmaCreateAllocator(&createInfo, &sAllocator) == VK_SUCCESS;
}

// Safe to call even if gfx_vulkan_memory_init() was never called (no-op).
void gfx_vulkan_memory_destroy(void) {
    if (sAllocator != VK_NULL_HANDLE) {
        vmaDestroyAllocator(sAllocator);
        sAllocator = VK_NULL_HANDLE;
    }
}

// Shared implementation behind the two public create_*_buffer helpers below.
static bool create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VmaAllocationCreateFlags allocFlags,
                           VmaMemoryUsage memUsage, GfxVulkanBuffer *out, void **outMappedPtr) {
    VkBufferCreateInfo bufferInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = size,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };
    VmaAllocationCreateInfo allocInfo = { 0 };
    allocInfo.usage = memUsage;
    allocInfo.flags = allocFlags;

    VkBuffer buffer = VK_NULL_HANDLE;
    VmaAllocation allocation = VK_NULL_HANDLE;
    VmaAllocationInfo allocationInfo;
    if (vmaCreateBuffer(sAllocator, &bufferInfo, &allocInfo, &buffer, &allocation, &allocationInfo) != VK_SUCCESS) {
        return false;
    }

    out->buffer = buffer;
    out->allocation = (void *)allocation;
    if (outMappedPtr) {
        *outMappedPtr = allocationInfo.pMappedData;
    }
    return true;
}

// See gfx_vulkan_memory.h.
bool gfx_vulkan_memory_create_device_local_buffer(VkDeviceSize size, VkBufferUsageFlags usage, GfxVulkanBuffer *out) {
    return create_buffer(size, usage, 0, VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE, out, NULL);
}

// See gfx_vulkan_memory.h.
bool gfx_vulkan_memory_create_streaming_buffer(VkDeviceSize size, VkBufferUsageFlags usage, GfxVulkanBuffer *out, void **outMappedPtr) {
    VmaAllocationCreateFlags flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;
    return create_buffer(size, usage, flags, VMA_MEMORY_USAGE_AUTO, out, outMappedPtr);
}

// Safe to call on an already-empty/zeroed GfxVulkanBuffer (no-op).
void gfx_vulkan_memory_destroy_buffer(GfxVulkanBuffer *buf) {
    if (!buf || buf->buffer == VK_NULL_HANDLE) {
        return;
    }
    vmaDestroyBuffer(sAllocator, buf->buffer, (VmaAllocation)buf->allocation);
    buf->buffer = VK_NULL_HANDLE;
    buf->allocation = NULL;
}

// See gfx_vulkan_memory.h.
bool gfx_vulkan_memory_create_image(uint32_t width, uint32_t height, VkFormat format, VkImageUsageFlags usage, VkImageAspectFlags aspect, GfxVulkanImage *out) {
    VkImageCreateInfo imageInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = format,
        .extent = { width, height, 1 },
        .mipLevels = 1,
        .arrayLayers = 1,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    };
    VmaAllocationCreateInfo allocInfo = { 0 };
    allocInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;

    VkImage image = VK_NULL_HANDLE;
    VmaAllocation allocation = VK_NULL_HANDLE;
    if (vmaCreateImage(sAllocator, &imageInfo, &allocInfo, &image, &allocation, NULL) != VK_SUCCESS) {
        return false;
    }

    VkImageViewCreateInfo viewInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = image,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = format,
        .subresourceRange = { aspect, 0, 1, 0, 1 },
    };
    VkImageView view = VK_NULL_HANDLE;
    if (vkCreateImageView(gfxVkDevice, &viewInfo, NULL, &view) != VK_SUCCESS) {
        vmaDestroyImage(sAllocator, image, allocation);
        return false;
    }

    out->image = image;
    out->view = view;
    out->allocation = (void *)allocation;
    return true;
}

// Safe to call on an already-empty/zeroed GfxVulkanImage (no-op).
void gfx_vulkan_memory_destroy_image(GfxVulkanImage *img) {
    if (!img || img->image == VK_NULL_HANDLE) {
        return;
    }
    if (img->view != VK_NULL_HANDLE) {
        vkDestroyImageView(gfxVkDevice, img->view, NULL);
    }
    vmaDestroyImage(sAllocator, img->image, (VmaAllocation)img->allocation);
    memset(img, 0, sizeof(*img));
}
