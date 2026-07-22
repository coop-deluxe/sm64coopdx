#if defined(ENABLE_VULKAN)

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include "gfx_vulkan_context.h"
#include "gfx_vulkan_memory.h"
#include "gfx_vulkan_swapchain.h"
#include "../../configfile.h"

VkSwapchainKHR gfxVkSwapchain = VK_NULL_HANDLE;
VkFormat gfxVkSwapchainFormat = VK_FORMAT_UNDEFINED;
VkExtent2D gfxVkSwapchainExtent = { 0, 0 };
VkImage *gfxVkSwapchainImages = NULL;
VkImageView *gfxVkSwapchainImageViews = NULL;
uint32_t gfxVkSwapchainImageCount = 0;

VkImage gfxVkDepthImage = VK_NULL_HANDLE;
VkImageView gfxVkDepthImageView = VK_NULL_HANDLE;
VkFormat gfxVkDepthFormat = VK_FORMAT_UNDEFINED;
static GfxVulkanImage sDepthImage;

// Picks a supported pure-depth format, preferring the highest precision.
static VkFormat choose_depth_format(void) {
    VkFormat candidates[] = { VK_FORMAT_D32_SFLOAT, VK_FORMAT_X8_D24_UNORM_PACK32 };
    for (size_t i = 0; i < sizeof(candidates) / sizeof(candidates[0]); i++) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(gfxVkPhysicalDevice, candidates[i], &props);
        if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
            return candidates[i];
        }
    }
    return VK_FORMAT_D32_SFLOAT; // one of the two above is spec-mandatory on any conformant device
}

// Safe to call even if no depth image exists yet (no-op).
static void destroy_depth_image(void) {
    gfx_vulkan_memory_destroy_image(&sDepthImage);
    gfxVkDepthImage = VK_NULL_HANDLE;
    gfxVkDepthImageView = VK_NULL_HANDLE;
}

// Allocates the depth image/view at `extent`, picking gfxVkDepthFormat once
// and reusing it on every later call.
static bool create_depth_image(VkExtent2D extent) {
    if (gfxVkDepthFormat == VK_FORMAT_UNDEFINED) {
        gfxVkDepthFormat = choose_depth_format();
    }
    if (!gfx_vulkan_memory_create_image(extent.width, extent.height, gfxVkDepthFormat,
                                         VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                                         VK_IMAGE_ASPECT_DEPTH_BIT, &sDepthImage)) {
        return false;
    }
    gfxVkDepthImage = sDepthImage.image;
    gfxVkDepthImageView = sDepthImage.view;
    return true;
}

// Picks BGRA8_UNORM/SRGB_NONLINEAR if the surface supports it, else the
// surface's first reported format.
static VkSurfaceFormatKHR choose_surface_format(void) {
    uint32_t count = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(gfxVkPhysicalDevice, gfxVkSurface, &count, NULL);

    VkSurfaceFormatKHR chosen = { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    if (count == 0) {
        return chosen;
    }

    VkSurfaceFormatKHR *formats = malloc(count * sizeof(VkSurfaceFormatKHR));
    if (!formats) {
        return chosen;
    }
    vkGetPhysicalDeviceSurfaceFormatsKHR(gfxVkPhysicalDevice, gfxVkSurface, &count, formats);

    chosen = formats[0];
    for (uint32_t i = 0; i < count; i++) {
        if (formats[i].format == VK_FORMAT_B8G8R8A8_UNORM &&
            formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            chosen = formats[i];
            break;
        }
    }

    free(formats);
    return chosen;
}

// FIFO when vsync is on (always available, blocks like classic double
// buffering). Otherwise prefers MAILBOX, falls back to IMMEDIATE, and
// defaults to FIFO if neither is reported.
static VkPresentModeKHR choose_present_mode(void) {
    if (configWindow.vsync) {
        return VK_PRESENT_MODE_FIFO_KHR; // always guaranteed to be available
    }

    uint32_t count = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(gfxVkPhysicalDevice, gfxVkSurface, &count, NULL);
    if (count == 0) {
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkPresentModeKHR *modes = malloc(count * sizeof(VkPresentModeKHR));
    if (!modes) {
        return VK_PRESENT_MODE_FIFO_KHR;
    }
    vkGetPhysicalDeviceSurfacePresentModesKHR(gfxVkPhysicalDevice, gfxVkSurface, &count, modes);

    VkPresentModeKHR chosen = VK_PRESENT_MODE_FIFO_KHR;
    for (uint32_t i = 0; i < count; i++) {
        if (modes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
            chosen = VK_PRESENT_MODE_MAILBOX_KHR;
            break;
        }
        if (modes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            chosen = VK_PRESENT_MODE_IMMEDIATE_KHR;
        }
    }

    free(modes);
    return chosen;
}

// Resolves the swapchain extent from surface capabilities, falling back to
// the drawable size (clamped to the surface's min/max) when the surface
// doesn't dictate a fixed extent.
static VkExtent2D choose_extent(struct SDL_Window *window, const VkSurfaceCapabilitiesKHR *caps) {
    if (caps->currentExtent.width != UINT32_MAX) {
        return caps->currentExtent;
    }

    int w = 0, h = 0;
    SDL_Vulkan_GetDrawableSize((SDL_Window *)window, &w, &h);

    VkExtent2D extent = { (uint32_t)w, (uint32_t)h };
    if (extent.width < caps->minImageExtent.width) { extent.width = caps->minImageExtent.width; }
    if (extent.width > caps->maxImageExtent.width) { extent.width = caps->maxImageExtent.width; }
    if (extent.height < caps->minImageExtent.height) { extent.height = caps->minImageExtent.height; }
    if (extent.height > caps->maxImageExtent.height) { extent.height = caps->maxImageExtent.height; }
    return extent;
}

// Frees gfxVkSwapchainImageViews/gfxVkSwapchainImages. Safe to call when
// they're already NULL (no-op).
static void destroy_image_views(void) {
    if (gfxVkSwapchainImageViews) {
        for (uint32_t i = 0; i < gfxVkSwapchainImageCount; i++) {
            if (gfxVkSwapchainImageViews[i] != VK_NULL_HANDLE) {
                vkDestroyImageView(gfxVkDevice, gfxVkSwapchainImageViews[i], NULL);
            }
        }
        free(gfxVkSwapchainImageViews);
        gfxVkSwapchainImageViews = NULL;
    }
    if (gfxVkSwapchainImages) {
        free(gfxVkSwapchainImages);
        gfxVkSwapchainImages = NULL;
    }
    gfxVkSwapchainImageCount = 0;
}

// Destroys the depth image, image views, and swapchain itself, in that order.
void gfx_vulkan_swapchain_destroy(void) {
    destroy_depth_image();
    destroy_image_views();
    if (gfxVkSwapchain != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(gfxVkDevice, gfxVkSwapchain, NULL);
        gfxVkSwapchain = VK_NULL_HANDLE;
    }
}

// Queries surface capabilities/format/present mode, then (re)builds the
// swapchain, its color image views, and the depth image at the resolved
// extent. See gfx_vulkan_swapchain.h for the failure-mode contract.
bool gfx_vulkan_swapchain_create(struct SDL_Window *window) {
    VkSurfaceCapabilitiesKHR caps;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gfxVkPhysicalDevice, gfxVkSurface, &caps) != VK_SUCCESS) {
        return false;
    }

    VkSurfaceFormatKHR surfaceFormat = choose_surface_format();
    VkPresentModeKHR presentMode = choose_present_mode();
    VkExtent2D extent = choose_extent(window, &caps);

    if (extent.width == 0 || extent.height == 0) {
        return false; // minimized: nothing to present yet
    }

    // FIFO never drops a queued frame, so every extra image beyond
    // minImageCount is an extra frame of input latency the CPU can race ahead
    // by before anything reaches the screen. Stay at minImageCount for FIFO
    // (typically 2, true double buffering) to match GL's roughly-one-frame-
    // deep blocking swap. MAILBOX/IMMEDIATE (vsync off) do need the extra
    // image - MAILBOX in particular degrades toward FIFO-like blocking
    // without a spare image to render into while one is displayed and one
    // sits in the mailbox slot.
    uint32_t imageCount = caps.minImageCount;
    if (presentMode != VK_PRESENT_MODE_FIFO_KHR) {
        imageCount += 1;
    }
    if (caps.maxImageCount > 0 && imageCount > caps.maxImageCount) {
        imageCount = caps.maxImageCount;
    }

    VkSwapchainKHR oldSwapchain = gfxVkSwapchain;

    VkSwapchainCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = gfxVkSurface,
        .minImageCount = imageCount,
        .imageFormat = surfaceFormat.format,
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .preTransform = caps.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = oldSwapchain,
    };

    VkSwapchainKHR newSwapchain = VK_NULL_HANDLE;
    VkResult res = vkCreateSwapchainKHR(gfxVkDevice, &createInfo, NULL, &newSwapchain);

#ifdef VULKAN_DEBUG
    fprintf(stderr, "[vulkan] swapchain_create: extent=%ux%u imageCount=%u presentMode=%d oldSwapchain=%p result=%d\n",
            extent.width, extent.height, imageCount, presentMode, (void *)oldSwapchain, res);
#endif

    if (oldSwapchain != VK_NULL_HANDLE) {
        destroy_image_views();
        vkDestroySwapchainKHR(gfxVkDevice, oldSwapchain, NULL);
    }

    if (res != VK_SUCCESS) {
        gfxVkSwapchain = VK_NULL_HANDLE;
        return false;
    }

    gfxVkSwapchain = newSwapchain;
    gfxVkSwapchainFormat = surfaceFormat.format;
    gfxVkSwapchainExtent = extent;

    vkGetSwapchainImagesKHR(gfxVkDevice, gfxVkSwapchain, &gfxVkSwapchainImageCount, NULL);
    gfxVkSwapchainImages = malloc(gfxVkSwapchainImageCount * sizeof(VkImage));
    if (!gfxVkSwapchainImages) {
        return false;
    }
    vkGetSwapchainImagesKHR(gfxVkDevice, gfxVkSwapchain, &gfxVkSwapchainImageCount, gfxVkSwapchainImages);

    gfxVkSwapchainImageViews = calloc(gfxVkSwapchainImageCount, sizeof(VkImageView));
    if (!gfxVkSwapchainImageViews) {
        return false;
    }

    for (uint32_t i = 0; i < gfxVkSwapchainImageCount; i++) {
        VkImageViewCreateInfo viewInfo = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = gfxVkSwapchainImages[i],
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = gfxVkSwapchainFormat,
            .subresourceRange = {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .levelCount = 1,
                .layerCount = 1,
            },
        };
        if (vkCreateImageView(gfxVkDevice, &viewInfo, NULL, &gfxVkSwapchainImageViews[i]) != VK_SUCCESS) {
            return false;
        }
    }

    // sDepthImage/gfxVkDepthImage* still describe the *previous* extent (if
    // any) at this point - drop them before building the new one, same
    // "destroy old, then create new" order as the color image views.
    destroy_depth_image();
    if (!create_depth_image(extent)) {
        return false;
    }

    return true;
}

#endif // ENABLE_VULKAN
