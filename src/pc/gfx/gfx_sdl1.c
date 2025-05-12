#ifndef HAVE_SDL1
#define STUB_ONLY

// Wir brauchen den Header für die Struktur-Definition
#include "gfx_window_manager_api.h"

// Stub-Implementierung
struct GfxWindowManagerAPI gfx_sdl1 = { 0 };

#else
// Original-Implementierung
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Schutzklausel: Stelle sicher, dass SDL2 und SDL1 nicht gleichzeitig eingebunden werden
#define DYNOS_SDL_INCLUDED

// Nur SDL1 Header importieren, nicht beide Versionen
#include <SDL/SDL.h>

#ifdef __MINGW32__
#define FOR_WINDOWS 1
#else
#define FOR_WINDOWS 0
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include <unistd.h>

#include "gfx_screen_config.h"
#include "../pc_main.h"
#include "../configfile.h"
#include "../cliopts.h"
#include "../platform.h"

#include "pc/controller/controller_keyboard.h"
#include "pc/controller/controller_bind_mapping.h"

// TODO: figure out if this shit even works
#ifdef VERSION_EU
# define FRAMERATE 25
#else
# define FRAMERATE 30
#endif

static kb_callback_t kb_key_down = NULL;
static kb_callback_t kb_key_up = NULL;
static void (*kb_all_keys_up)(void) = NULL;

// time between consequtive game frames
static const int frame_time = 1000 / FRAMERATE;

static int desktop_w = 640;
static int desktop_h = 480;
static int desktop_bpp = 24;

static int window_w = 0;
static int window_h = 0;

static void gfx_sdl_set_mode(void) {
    if (configWindow.exiting_fullscreen)
        configWindow.exiting_fullscreen = false;

    if (configWindow.reset) {
        configWindow.fullscreen = false;
        configWindow.x = WAPI_WIN_CENTERPOS;
        configWindow.y = WAPI_WIN_CENTERPOS;
        configWindow.w = DESIRED_SCREEN_WIDTH;
        configWindow.h = DESIRED_SCREEN_HEIGHT;
        configWindow.reset = false;
    }

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    uint32_t flags = SDL_OPENGL;
    if (configWindow.fullscreen)
        flags |= SDL_FULLSCREEN;
    else
        flags |= SDL_RESIZABLE;

    if (!SDL_VideoModeOK(configWindow.w, configWindow.h, desktop_bpp, flags)) {
        printf(
            "video mode [%dx%d fullscreen %d] not available, falling back to default\n",
            configWindow.w, configWindow.h, configWindow.fullscreen
        );
        configWindow.w = DESIRED_SCREEN_WIDTH;
        configWindow.h = DESIRED_SCREEN_HEIGHT;
        configWindow.fullscreen = false;
        flags = SDL_OPENGL | SDL_RESIZABLE;
    }

    if (!SDL_SetVideoMode(configWindow.w, configWindow.h, desktop_bpp, flags)) {
        sys_fatal(
            "could not set video mode [%dx%d fullscreen %d]: %s\n",
            configWindow.w, configWindow.h, configWindow.fullscreen, SDL_GetError()
        );
    }

    window_w = configWindow.w;
    window_h = configWindow.h;
}

static void gfx_sdl_init(const char *window_title) {
#if defined(_WIN32) || defined(_WIN64)
    SetProcessDPIAware();
#endif

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        sys_fatal("Could not init SDL1 video: %s\n", SDL_GetError());

    const SDL_VideoInfo *vinfo = SDL_GetVideoInfo();
    desktop_w = vinfo->current_w;
    desktop_h = vinfo->current_h;
    desktop_bpp = vinfo->vfmt->BitsPerPixel;

    SDL_WM_SetCaption(window_title, NULL);

    // set actual desired video mode

    gfx_sdl_set_mode();

    if (configWindow.fullscreen) {
        SDL_ShowCursor(0);
    }

    controller_bind_init();
}

static void gfx_sdl_main_loop(void (*run_one_game_iter)(void)) {
    run_one_game_iter();
}

static void gfx_sdl_get_dimensions(uint32_t *width, uint32_t *height) {
    if (width) *width = window_w;
    if (height) *height = window_h;
}

static void gfx_sdl_onkeydown(int scancode) {
    if (kb_key_down) {
        const char* keyname = translate_bind_to_name(scancode);
        if (keyname) {
            kb_key_down(scancode);
        }
    }
}

static void gfx_sdl_onkeyup(int scancode) {
    if (kb_key_up) {
        const char* keyname = translate_bind_to_name(scancode);
        if (keyname) {
            kb_key_up(scancode);
        }
    }
}

static void gfx_sdl_handle_events(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                gfx_sdl_onkeydown(event.key.keysym.sym);
                // ALT+F4 in case the OS doesn't do it (SDL1 doesn't seem to do it on my machine)
                if (event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod & (KMOD_LALT | KMOD_RALT)))
                    game_exit();
                break;
            case SDL_KEYUP:
                gfx_sdl_onkeyup(event.key.keysym.sym);
                break;
            case SDL_VIDEORESIZE:
                window_w = configWindow.w = event.resize.w;
                window_h = configWindow.h = event.resize.h;
                break;
            case SDL_QUIT:
                game_exit();
                break;
        }
    }
}

static void gfx_sdl_set_keyboard_callbacks(kb_callback_t on_key_down, kb_callback_t on_key_up, void (*on_all_keys_up)(void)) {
    kb_key_down = on_key_down;
    kb_key_up = on_key_up;
    kb_all_keys_up = on_all_keys_up;
}

static bool gfx_sdl_start_frame(void) {
    return true;
}

static void gfx_sdl_swap_buffers_begin(void) {
    SDL_GL_SwapBuffers();
}

static void gfx_sdl_swap_buffers_end(void) {
}

static double gfx_sdl_get_time(void) {
    return 0.0;
}

static void gfx_sdl_delay(u32 ms) {
    SDL_Delay(ms);
}

static int gfx_sdl_get_max_msaa(void) {
    return 0;
}

static void gfx_sdl_set_window_title(const char* title) {
    SDL_WM_SetCaption(title, NULL);
}

static void gfx_sdl_reset_window_title(void) {
    SDL_WM_SetCaption(TITLE, NULL);
}

static void gfx_sdl_shutdown(void) {
    if (SDL_WasInit(0))
        SDL_Quit();
}

static bool gfx_sdl_has_focus(void) {
    return SDL_GetAppState() & SDL_APPINPUTFOCUS;
}

static void gfx_sdl_start_text_input(void) { return; }
static void gfx_sdl_stop_text_input(void) { return; }
static char* gfx_sdl_get_clipboard_text(void) { return ""; }
static void gfx_sdl_set_clipboard_text(UNUSED const char* text) { return; }
static void gfx_sdl_set_cursor_visible(bool visible) { SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE); }

// Wrapper-Funktionen für die korrekte Signatur
static void gfx_sdl_main_loop_wrapper(void (*run_one_game_iter)(void)) {
    gfx_sdl_main_loop(run_one_game_iter);
}

static bool gfx_sdl_start_frame_wrapper(void) {
    return gfx_sdl_start_frame();
}

static void gfx_sdl_swap_buffers_begin_wrapper(void) {
    gfx_sdl_swap_buffers_begin();
}

static void gfx_sdl_swap_buffers_end_wrapper(void) {
    gfx_sdl_swap_buffers_end();
}

static double gfx_sdl_get_time_wrapper(void) {
    return gfx_sdl_get_time();
}

static void gfx_sdl_shutdown_wrapper(void) {
    gfx_sdl_shutdown();
}

static void gfx_sdl_set_keyboard_callbacks_wrapper(bool (*key_down)(int scancode), bool (*key_up)(int scancode), void (*all_keys_up)(void), void (*on_text_input)(char *text), void (*on_text_motion)(char *text, int count)) {
    gfx_sdl_set_keyboard_callbacks(key_down, key_up, all_keys_up);
}

static void gfx_sdl_handle_events_wrapper(void) {
    gfx_sdl_handle_events();
}

static void gfx_sdl_get_dimensions_wrapper(uint32_t *width, uint32_t *height) {
    gfx_sdl_get_dimensions(width, height);
}

static void gfx_sdl_set_cursor_visible_wrapper(bool visible) {
    gfx_sdl_set_cursor_visible(visible);
}

static void gfx_sdl_start_text_input_wrapper(void) {
    gfx_sdl_start_text_input();
}

static void gfx_sdl_stop_text_input_wrapper(void) {
    gfx_sdl_stop_text_input();
}

static char* gfx_sdl_get_clipboard_text_wrapper(void) {
    return gfx_sdl_get_clipboard_text();
}

static void gfx_sdl_set_clipboard_text_wrapper(const char* text) {
    gfx_sdl_set_clipboard_text(text);
}

static void gfx_sdl_delay_wrapper(uint32_t ms) {
    gfx_sdl_delay(ms);
}

static int gfx_sdl_get_max_msaa_wrapper(void) {
    return gfx_sdl_get_max_msaa();
}

static void gfx_sdl_set_window_title_wrapper(const char* title) {
    gfx_sdl_set_window_title(title);
}

static void gfx_sdl_reset_window_title_wrapper(void) {
    gfx_sdl_reset_window_title();
}

static bool gfx_sdl_has_focus_wrapper(void) {
    return gfx_sdl_has_focus();
}

// Add a missing function for scroll callback
static void gfx_sdl_set_scroll_callback(void (*on_scroll)(float, float)) {
    // SDL1 doesn't support scroll callback, so do nothing
}

struct GfxWindowManagerAPI gfx_sdl1 = {
    gfx_sdl_init,
    gfx_sdl_set_keyboard_callbacks_wrapper,
    gfx_sdl_set_scroll_callback,
    gfx_sdl_main_loop_wrapper,
    gfx_sdl_get_dimensions_wrapper,
    gfx_sdl_handle_events_wrapper,
    gfx_sdl_start_frame_wrapper,
    gfx_sdl_swap_buffers_begin_wrapper,
    gfx_sdl_swap_buffers_end_wrapper,
    gfx_sdl_get_time_wrapper,
    gfx_sdl_shutdown_wrapper,
    gfx_sdl_start_text_input_wrapper,
    gfx_sdl_stop_text_input_wrapper,
    gfx_sdl_get_clipboard_text_wrapper,
    gfx_sdl_set_clipboard_text_wrapper,
    gfx_sdl_set_cursor_visible_wrapper,
    gfx_sdl_delay_wrapper,
    gfx_sdl_get_max_msaa_wrapper,
    gfx_sdl_set_window_title_wrapper,
    gfx_sdl_reset_window_title_wrapper,
    gfx_sdl_has_focus_wrapper
};

#endif // HAVE_SDL1
