#include "macros.h"
#include "gfx_vulkan_debug.h"

#if defined(DEVELOPMENT)

// Opens a named debug label region on cmd, visible in GPU debugger event browsers.
void gfx_vulkan_debug_begin_label(VkCommandBuffer cmd, const char *name) {
    if (!vkCmdBeginDebugUtilsLabelEXT) {
        return; // VK_EXT_debug_utils wasn't enabled (no validation layer available)
    }
    VkDebugUtilsLabelEXT label = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
        .pLabelName = name,
    };
    vkCmdBeginDebugUtilsLabelEXT(cmd, &label);
}

// Closes the label region opened by gfx_vulkan_debug_begin_label.
void gfx_vulkan_debug_end_label(VkCommandBuffer cmd) {
    if (!vkCmdEndDebugUtilsLabelEXT) {
        return;
    }
    vkCmdEndDebugUtilsLabelEXT(cmd);
}

#else

// No-op outside DEVELOPMENT builds - see gfx_vulkan_debug.h.
void gfx_vulkan_debug_begin_label(UNUSED VkCommandBuffer cmd, UNUSED const char *name) {
}

void gfx_vulkan_debug_end_label(UNUSED VkCommandBuffer cmd) {
}

#endif // DEVELOPMENT
