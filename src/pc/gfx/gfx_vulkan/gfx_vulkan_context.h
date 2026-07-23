#ifndef GFX_VULKAN_CONTEXT_H
#define GFX_VULKAN_CONTEXT_H

#include <stdbool.h>
#include <volk.h>

struct SDL_Window;

// Owns VkInstance/VkSurfaceKHR/VkPhysicalDevice/VkDevice/VkQueue for the
// lifetime of the Vulkan backend. The surface is created here (not in
// gfx_vulkan_swapchain.c) because physical device selection needs it to
// verify presentation support before a VkDevice exists; gfx_vulkan_swapchain.c
// only owns the VkSwapchainKHR/VkImageView[] built on top of it.
bool gfx_vulkan_context_init(struct SDL_Window *window);
void gfx_vulkan_context_destroy(void);

extern VkInstance gfxVkInstance;
extern VkSurfaceKHR gfxVkSurface;
extern VkPhysicalDevice gfxVkPhysicalDevice;
extern VkDevice gfxVkDevice;
extern VkQueue gfxVkQueue;
extern uint32_t gfxVkQueueFamily;

#endif // GFX_VULKAN_CONTEXT_H
