#ifndef GFX_VULKAN_H
#define GFX_VULKAN_H

#include <stdbool.h>

#include "gfx_rendering_api.h"

// Implements GfxRenderingAPI for the Vulkan backend.
extern struct GfxRenderingAPI gfx_vulkan_api;

// Lightweight support probe: creates a temporary VkInstance, checks that at
// least one physical device supports VK_KHR_swapchain +
// VK_EXT_extended_dynamic_state3 (plus the Vulkan 1.3/1.2 features this
// backend actually needs), then tears everything down without creating a
// VkDevice or a window. Safe to call before committing to this backend.
bool gfx_vulkan_probe_support(void);

// Called from gfx_window_vulkan.c's GfxWindowBackendAPI::start_frame -
// acquires the next swapchain image, returning false if this frame should be
// dropped (matches that contract's semantics; see gfx_vulkan_frame.c).
bool gfx_vulkan_start_frame(void);

#endif // GFX_VULKAN_H
