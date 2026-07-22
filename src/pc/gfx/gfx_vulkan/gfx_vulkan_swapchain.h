#if defined(ENABLE_VULKAN)

#ifndef GFX_VULKAN_SWAPCHAIN_H
#define GFX_VULKAN_SWAPCHAIN_H

#include <stdbool.h>
#include <volk.h>

struct SDL_Window;

// Builds the VkSwapchainKHR + VkImageView[] on top of the surface/device
// owned by gfx_vulkan_context.c. Safe to call again on an existing swapchain
// (e.g. on resize) - destroys the previous one first.
//
// NOTE: this can fail after the previous swapchain has already been torn
// down (vkCreateSwapchainKHR itself failing leaves gfxVkSwapchain ==
// VK_NULL_HANDLE; a VkImageView/depth image failing to create instead leaves
// gfxVkSwapchain valid but gfxVkSwapchainImageViews/gfxVkDepthImage
// incomplete). Callers must not assume a false return leaves the previous
// state untouched - see gfx_vulkan_frame.c's recreate_swapchain(), which
// re-arms its dirty flag on failure so the next frame retries instead of
// using this half-built state.
bool gfx_vulkan_swapchain_create(struct SDL_Window *window);
void gfx_vulkan_swapchain_destroy(void);

extern VkSwapchainKHR gfxVkSwapchain;
extern VkFormat gfxVkSwapchainFormat;
extern VkExtent2D gfxVkSwapchainExtent;
extern VkImage *gfxVkSwapchainImages;
extern VkImageView *gfxVkSwapchainImageViews;
extern uint32_t gfxVkSwapchainImageCount;

// Depth buffer, recreated alongside the color swapchain images on every
// gfx_vulkan_swapchain_create() call (same extent, same lifetime).
// gfxVkDepthFormat is a pure-depth (no stencil) format - VK_FORMAT_D32_SFLOAT
// or VK_FORMAT_X8_D24_UNORM_PACK32, at least one of which the Vulkan spec
// mandates DEPTH_STENCIL_ATTACHMENT_BIT support for with optimal tiling on
// every conformant device - so gfx_vulkan_pipeline.c can bake it into every
// pipeline's VkPipelineRenderingCreateInfo unconditionally.
extern VkImage gfxVkDepthImage;
extern VkImageView gfxVkDepthImageView;
extern VkFormat gfxVkDepthFormat;

#endif // GFX_VULKAN_SWAPCHAIN_H

#endif // ENABLE_VULKAN
