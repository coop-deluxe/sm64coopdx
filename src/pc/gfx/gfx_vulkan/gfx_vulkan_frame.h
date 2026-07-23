#ifndef GFX_VULKAN_FRAME_H
#define GFX_VULKAN_FRAME_H

#include <stdbool.h>
#include <volk.h>

struct SDL_Window;

// Number of frame-in-flight slots (command pool/buffer, semaphores, and one
// slice each of the per-frame UBO and the vertex streaming arena). Anything
// sized per-slot and only written while that slot is "current" is
// automatically safe from the CPU overwriting data the GPU hasn't read yet,
// since gfx_vulkan_frame_start() already waits on a slot's previous
// submission before reusing it.
#define GFX_VULKAN_FRAMES_IN_FLIGHT 2

bool gfx_vulkan_frame_init(struct SDL_Window *window);
void gfx_vulkan_frame_destroy(void);

// Called on SDL_WINDOWEVENT_SIZE_CHANGED: defers the actual swapchain rebuild
// to the next gfx_vulkan_frame_start, since resizing mid-frame would need a
// device-idle wait that shouldn't happen on the event thread.
void gfx_vulkan_frame_notify_resize(void);

// Acquires the next swapchain image. Returns false to tell the caller to drop
// this frame (matches GfxWindowManagerAPI::start_frame's contract) - e.g. the
// swapchain just got recreated, or the window is currently minimized.
bool gfx_vulkan_frame_start(void);
void gfx_vulkan_frame_begin_rendering(void);
void gfx_vulkan_frame_end_and_submit(void);
// Presents the acquired image. Returns false if the swapchain needs a rebuild
// (marks it dirty for the next gfx_vulkan_frame_start; not fatal).
bool gfx_vulkan_frame_present(void);

// Index in [0, GFX_VULKAN_FRAMES_IN_FLIGHT) of the slot currently being
// recorded (valid between gfx_vulkan_frame_start() and the matching
// gfx_vulkan_frame_present()).
uint32_t gfx_vulkan_frame_get_current_slot(void);

extern VkCommandBuffer gfxVkCurrentCommandBuffer;

#endif // GFX_VULKAN_FRAME_H
