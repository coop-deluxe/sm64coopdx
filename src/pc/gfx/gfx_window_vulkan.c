#if defined(ENABLE_VULKAN)

#include <SDL2/SDL.h>

#include "gfx_window_manager.h"
#include "gfx_vulkan.h"
#include "gfx_pc.h"
#include "gfx_rendering_api.h"
#include "../pc_main.h"
#include "../configfile.h"

// Implements GfxWindowBackendAPI for the Vulkan backend: an SDL2 window
// created with SDL_WINDOW_VULKAN, with presentation itself handled by
// gfx_vulkan_renderer_finish_render() rather than any SDL/GL "swap" call.

static SDL_Window *sSdlWindow;

#define IS_FULLSCREEN() ((SDL_GetWindowFlags(sSdlWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)

// GfxWindowBackendAPI::set_fullscreen - no-op: fullscreen toggling isn't
// implemented for this backend yet.
static void gfx_window_vulkan_set_fullscreen(void) {
}

// GfxWindowBackendAPI::init - creates the SDL2 window with SDL_WINDOW_VULKAN.
static void gfx_window_vulkan_init(const char *window_title) {
    int xpos = (configWindow.x == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.x;
    int ypos = (configWindow.y == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.y;

    sSdlWindow = SDL_CreateWindow(
        window_title,
        xpos, ypos, configWindow.w, configWindow.h,
        SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    gfx_wm_set_window(sSdlWindow);
}

// GfxWindowBackendAPI::handle_events
static void gfx_window_vulkan_handle_events(SDL_Event event) {
    if (event.type == SDL_WINDOWEVENT) {
        if (!IS_FULLSCREEN()) {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                // No-op for GL/D3D11's own handlers; rebuilds the swapchain
                // for Vulkan (mirrors gfx_window_dxgi.cpp's on_resize).
                gfx_get_current_rendering_api()->on_resize();
            }
        }
    }
}

// GfxWindowBackendAPI::start_frame
static bool gfx_window_vulkan_start_frame(void) {
    return gfx_vulkan_start_frame();
}

// GfxWindowBackendAPI::swap_buffers_begin - no-op: Vulkan presents from
// gfx_vulkan_renderer_finish_render() instead, since its swapchain isn't
// tied to an SDL/GL "swap" call.
static void gfx_window_vulkan_swap_buffers_begin(void) {
}

// GfxWindowBackendAPI::swap_buffers_end - no-op, see swap_buffers_begin above.
static void gfx_window_vulkan_swap_buffers_end(void) {
}

// GfxWindowBackendAPI::get_time - unused by this backend.
static double gfx_window_vulkan_get_time(void) {
    return 0.0;
}

// GfxWindowBackendAPI::get_max_msaa - no MSAA in the Vulkan backend.
static int gfx_window_vulkan_get_max_msaa(void) {
    return 0;
}

struct GfxWindowBackendAPI gfx_window_vulkan = {
    gfx_window_vulkan_init,
    gfx_window_vulkan_set_fullscreen,
    gfx_window_vulkan_handle_events,
    gfx_window_vulkan_start_frame,
    gfx_window_vulkan_swap_buffers_begin,
    gfx_window_vulkan_swap_buffers_end,
    gfx_window_vulkan_get_time,
    gfx_window_vulkan_get_max_msaa,
};

#endif // ENABLE_VULKAN
