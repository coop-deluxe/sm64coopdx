#ifdef __MINGW32__
#define FOR_WINDOWS 1
#else
#define FOR_WINDOWS 0
#endif

#include <SDL2/SDL.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#if FOR_WINDOWS
#define GLEW_STATIC
#include <GL/glew.h>

#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengl.h>
#else
#define GL_GLEXT_PROTOTYPES 1

#ifdef OSX_BUILD
#include <SDL2/SDL_opengl.h>
#else
#include <SDL2/SDL_opengles2.h>
#endif

#endif // End of OS-Specific GL defines

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

#ifndef GL_MAX_SAMPLES
#define GL_MAX_SAMPLES 0x8D57
#endif

static SDL_Window *sSdlWindow;
static SDL_GLContext sGlContext = NULL;

static inline void gfx_window_opengl_set_vsync(const bool enabled) {
    SDL_GL_SetSwapInterval(enabled);
}

static void gfx_window_opengl_set_fullscreen(void) {
}

static void gfx_window_opengl_reset_dimension_and_pos(void) {
    gfx_window_opengl_set_vsync(configWindow.vsync);
}

static void gfx_window_opengl_init(const char *window_title) {
    if (configWindow.msaa > 0) {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, configWindow.msaa);
    } else {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
    }

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#ifdef USE_GLES
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);  // These attributes allow for hardware acceleration on RPis.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif

    int xpos = (configWindow.x == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.x;
    int ypos = (configWindow.y == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.y;

    sSdlWindow = SDL_CreateWindow(
        window_title,
        xpos, ypos, configWindow.w, configWindow.h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    sGlContext = SDL_GL_CreateContext(sSdlWindow);

    gfx_wm_set_window(sSdlWindow);
    gfx_window_opengl_set_vsync(configWindow.vsync);
}

bool gfx_window_opengl_check_compatibility(void) {
    if (!(SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO)) {
        if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
            return false;
        }
    }

    // hidden window
    SDL_Window *window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1, 1,
        SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN
    );

    if (!window) {
        return false;
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(window);

    if (!ctx) {
        SDL_DestroyWindow(window);
        return false;
    }

    SDL_GL_MakeCurrent(window, ctx);
    bool validVersion = gfx_opengl_check_compatibility();

    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(window);

    return validVersion;
}

static void gfx_window_opengl_handle_events(UNUSED SDL_Event event) {
    if (configWindow.settings_changed) {
        gfx_window_opengl_reset_dimension_and_pos();
    }
}

static bool gfx_window_opengl_start_frame(void) {
    return true;
}

static void gfx_window_opengl_swap_buffers_begin(void) {
    SDL_GL_SwapWindow(sSdlWindow);
}

static void gfx_window_opengl_swap_buffers_end(void) {
}

static double gfx_window_opengl_get_time(void) {
    return 0.0;
}

static int gfx_window_opengl_get_max_msaa(void) {
    int maxSamples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
    if (maxSamples > 16) { maxSamples = 16; }
    return maxSamples;
}

struct GfxWindowBackendAPI gfx_window_opengl = {
    gfx_window_opengl_init,
    gfx_window_opengl_set_fullscreen,
    gfx_window_opengl_handle_events,
    gfx_window_opengl_start_frame,
    gfx_window_opengl_swap_buffers_begin,
    gfx_window_opengl_swap_buffers_end,
    gfx_window_opengl_get_time,
    gfx_window_opengl_get_max_msaa,
};
