#if defined(ENABLE_VULKAN)

#ifndef GFX_VULKAN_DEBUG_H
#define GFX_VULKAN_DEBUG_H

#include <volk.h>

// DEVELOPMENT-only debug labels (VK_EXT_debug_utils) for GPU debuggers such as
// RenderDoc. Declared unconditionally so call sites never need their own
// #ifdef DEVELOPMENT: outside DEVELOPMENT builds these compile to no-ops.
// Callers that build a label string (snprintf etc.) should still guard that
// construction with #ifdef DEVELOPMENT to avoid the cost in release builds.
//
// VK_EXT_debug_utils itself is only requested when the validation layer is
// also present (see gfx_vulkan_context.c), so these labels are silent no-ops
// on machines without VK_LAYER_KHRONOS_validation installed, same as the
// debug messenger.
void gfx_vulkan_debug_begin_label(VkCommandBuffer cmd, const char *name);
void gfx_vulkan_debug_end_label(VkCommandBuffer cmd);

#endif // GFX_VULKAN_DEBUG_H

#endif // ENABLE_VULKAN
