#ifdef __APPLE__

#include <SDL3/SDL.h>

#include <stdio.h>
#include <unistd.h>

#include "gfx_window_manager.h"
#include "gfx_screen_config.h"
#include "../pc_main.h"
#include "../configfile.h"
#include "../cliopts.h"

#include "pc/controller/controller_keyboard.h"
#include "pc/controller/controller_sdl.h"
#include "pc/controller/controller_bind_mapping.h"
#include "pc/utils/misc.h"
#include "pc/mods/mod_import.h"
#include "pc/rom_checker.h"
#include "pc/debuglog.h"

static SDL_Window *sSdlWindow;
static bool sAppliedVsync = false;

static inline void gfx_window_metal_set_vsync(const bool enabled) {
    gfx_metal_api.set_vsync(enabled);
    sAppliedVsync = enabled;
}

static void gfx_window_metal_set_fullscreen(void) {
}

static void gfx_window_metal_init(const char *window_title) {
    int xpos = (configWindow.x == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.x;
    int ypos = (configWindow.y == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.y;

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, window_title);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, xpos);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, ypos);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, configWindow.w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, configWindow.h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    sSdlWindow = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);

    gfx_wm_set_window(sSdlWindow);
    gfx_window_metal_set_vsync(configWindow.vsync);
}

static void gfx_window_metal_handle_events(SDL_Event event) {
    if (configWindow.settings_changed) {
        gfx_window_metal_set_vsync(configWindow.vsync);
        gfx_metal_api.on_resize();
    }

    if (event.window.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
        gfx_metal_api.on_resize();
    }
}

static bool gfx_window_metal_start_frame(void) {
    if (sAppliedVsync != configWindow.vsync) {
        gfx_window_metal_set_vsync(configWindow.vsync);
    }
    return true;
}

static void gfx_window_metal_swap_buffers_begin(void) {
}

static void gfx_window_metal_swap_buffers_end(void) {
}

static double gfx_window_metal_get_time(void) {
    return 0.0;
}

static int gfx_window_metal_get_max_msaa(void) {
    return 0;
}

struct GfxWindowBackendAPI gfx_window_metal = {
    gfx_window_metal_init,
    gfx_window_metal_set_fullscreen,
    gfx_window_metal_handle_events,
    gfx_window_metal_start_frame,
    gfx_window_metal_swap_buffers_begin,
    gfx_window_metal_swap_buffers_end,
    gfx_window_metal_get_time,
    gfx_window_metal_get_max_msaa,
};

#endif
