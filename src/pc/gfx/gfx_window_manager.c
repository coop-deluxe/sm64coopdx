#include <SDL3/SDL.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <unistd.h>

#include "gfx_window_manager.h"
#include "gfx_window_opengl.h"
#include "gfx_window_dxgi.h"
#include "gfx_screen_config.h"

#include "pc/pc_main.h"
#include "pc/configfile.h"
#include "pc/cliopts.h"
#include "pc/controller/controller_keyboard.h"
#include "pc/controller/controller_sdl.h"
#include "pc/controller/controller_bind_mapping.h"
#include "pc/utils/misc.h"
#include "pc/mods/mod_import.h"
#include "pc/rom_checker.h"

static struct GfxWindowBackendAPI *sBackends[GFX_WINDOW_BACKEND_COUNT] = {
    [GFX_WINDOW_BACKEND_OPENGL] = &gfx_window_opengl,
#if defined(_WIN32)
    [GFX_WINDOW_BACKEND_DIRECTX] = &gfx_window_dxgi,
#endif
};

// TODO: figure out how to switch the backend without restarting
// this is currently used to initialize which backend is used
static enum GfxWindowBackend currBackend = GFX_WINDOW_BACKEND_DUMMY;

static SDL_Window *sSdlWindow;

static kb_callback_t kb_key_down = NULL;
static kb_callback_t kb_key_up = NULL;
static void (*kb_all_keys_up)(void) = NULL;
static void (*kb_text_input)(char*) = NULL;
static void (*kb_text_editing)(char*, int) = NULL;

static void (*m_scroll)(float, float) = NULL;

#define IS_FULLSCREEN() ((SDL_GetWindowFlags(sSdlWindow) & SDL_WINDOW_FULLSCREEN) != 0)

// Getter for the current window backend API
static struct GfxWindowBackendAPI *gfx_wm_backend(void) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return &gfx_window_dummy; }
    return sBackends[currBackend];
}

void gfx_wm_set_window(SDL_Window *window) {
    sSdlWindow = window;
}

SDL_Window *gfx_wm_get_window(void) {
    return sSdlWindow;
}

static void gfx_wm_set_fullscreen(void) {
    if (configWindow.reset) {
        configWindow.fullscreen = false;
    }

    if (configWindow.fullscreen == IS_FULLSCREEN()) {
        return;
    }

    if (configWindow.fullscreen) {
        SDL_SetWindowFullscreen(sSdlWindow, true);
    } else {
        SDL_SetWindowFullscreen(sSdlWindow, false);
        SDL_ShowCursor();
        configWindow.exiting_fullscreen = true;
    }
    gfx_wm_backend()->set_fullscreen();
}

static void gfx_wm_reset_dimension_and_pos(void) {
    if (configWindow.exiting_fullscreen) {
        configWindow.exiting_fullscreen = false;
        SDL_HideCursor();
    }

    if (configWindow.reset) {
        configWindow.x = WAPI_WIN_CENTERPOS;
        configWindow.y = WAPI_WIN_CENTERPOS;
        configWindow.w = DESIRED_SCREEN_WIDTH;
        configWindow.h = DESIRED_SCREEN_HEIGHT;
        configWindow.reset = false;
    } else if (!configWindow.settings_changed) {
        return;
    }

    int xpos = (configWindow.x == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.x;
    int ypos = (configWindow.y == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.y;

    SDL_SetWindowSize(sSdlWindow, configWindow.w, configWindow.h);
    SDL_SetWindowPosition(sSdlWindow, xpos, ypos);
}

void gfx_wm_init(const char *window_title) {
    if (gCLIOpts.headless) { return; }
#if defined(_WIN32)
    SetProcessDPIAware();
#endif

    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    SDL_Init(SDL_INIT_VIDEO);

    SDL_StopTextInput(sSdlWindow);

#if defined(_WIN32)
    currBackend = gCLIOpts.backend != GFX_WINDOW_BACKEND_COUNT ? gCLIOpts.backend : configGraphicsBackend;
#else
    currBackend = configGraphicsBackend;
#endif
    if (currBackend != GFX_WINDOW_BACKEND_DUMMY &&
        (currBackend < 0 || currBackend > GFX_WINDOW_BACKEND_MAX)
    ) {
        currBackend = GFX_WINDOW_BACKEND_OPENGL;
    }
    gfx_wm_backend()->init(window_title);

    gfx_wm_set_fullscreen();
    if (configWindow.fullscreen) {
        SDL_HideCursor();
    }

    controller_bind_init();
}

void gfx_wm_main_loop(void (*run_one_game_iter)(void)) {
    run_one_game_iter();
}

void gfx_wm_get_dimensions(uint32_t *width, uint32_t *height) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) {
        if (width) { *width = 320; }
        if (height) { *height = 240; }
        return;
    }
    int w, h;
    SDL_GetWindowSize(sSdlWindow, &w, &h);
    if (width) { *width = w; }
    if (height) { *height = h; }
}

static void gfx_wm_onkeydown(int scancode) {
    const bool *state = SDL_GetKeyboardState(NULL);

    if ((state[SDL_SCANCODE_LALT] || state[SDL_SCANCODE_RALT]) && state[SDL_SCANCODE_RETURN]) {
        configWindow.fullscreen = !configWindow.fullscreen;
        configWindow.settings_changed = true;
        return;
    }

    if (kb_key_down) {
        kb_key_down(translate_sdl_scancode(scancode));
    }
}

static void gfx_wm_onkeyup(int scancode) {
    if (kb_key_up) {
        kb_key_up(translate_sdl_scancode(scancode));
    }
}

static void gfx_wm_onscroll(float x, float y) {
    if (m_scroll) {
        m_scroll(x, y);
    }
}

static void gfx_wm_ondropfile(char* path) {
#ifdef _WIN32
    char portable_path[SYS_MAX_PATH];
    if (sys_windows_short_path_from_mbs(portable_path, SYS_MAX_PATH, path)) {
        if (!gRomIsValid) {
            rom_on_drop_file(portable_path);
        } else if (gGameInited) {
            mod_import_file(portable_path);
        }
    }
#else
    if (!gRomIsValid) {
        rom_on_drop_file(path);
    } else if (gGameInited) {
        mod_import_file(path);
    }
#endif
}

void gfx_wm_handle_events(void) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_TEXT_INPUT:
                if (kb_text_input) { kb_text_input((char *)event.text.text); }
                break;
            case SDL_EVENT_TEXT_EDITING: //IME composition
                if (kb_text_editing) { kb_text_editing((char *)event.edit.text, event.edit.start); }
                break;
            case SDL_EVENT_KEY_DOWN:
                gfx_wm_onkeydown(event.key.scancode);
                break;
            case SDL_EVENT_KEY_UP:
                gfx_wm_onkeyup(event.key.scancode);
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                gfx_wm_onscroll(event.wheel.x, event.wheel.y);
                break;
            case SDL_EVENT_WINDOW_MOVED:
                if (!configWindow.exiting_fullscreen && !IS_FULLSCREEN()) {
                    if (event.window.data1 >= 0) { configWindow.x = event.window.data1; }
                    if (event.window.data2 >= 0) { configWindow.y = event.window.data2; }
                }
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                if (!IS_FULLSCREEN()) {
                    configWindow.w = event.window.data1;
                    configWindow.h = event.window.data2;
                }
                break;
            case SDL_EVENT_DROP_FILE:
                gfx_wm_ondropfile((char *)event.drop.data);
                break;
            case SDL_EVENT_QUIT:
                game_exit();
                break;
        }
        gfx_wm_backend()->handle_events(event);
    }

    if (configWindow.settings_changed) {
        gfx_wm_set_fullscreen();
        gfx_wm_reset_dimension_and_pos();
        configWindow.settings_changed = false;
    }
}

void gfx_wm_set_keyboard_callbacks(kb_callback_t on_key_down, kb_callback_t on_key_up,
    void (*on_all_keys_up)(void), void (*on_text_input)(char*), void (*on_text_editing)(char*, int)) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    kb_key_down = on_key_down;
    kb_key_up = on_key_up;
    kb_all_keys_up = on_all_keys_up;
    kb_text_input = on_text_input;
    kb_text_editing = on_text_editing;
}

void gfx_wm_set_scroll_callback(void (*on_scroll)(float, float)) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    m_scroll = on_scroll;
}

bool gfx_wm_start_frame(void) {
    return gfx_wm_backend()->start_frame();
}

void gfx_wm_swap_buffers_begin(void) {
    gfx_wm_backend()->swap_buffers_begin();
}

void gfx_wm_swap_buffers_end(void) {
    gfx_wm_backend()->swap_buffers_end();
}

double gfx_wm_get_time(void) {
    return gfx_wm_backend()->get_time();
}

void gfx_wm_delay(u32 ms) {
    SDL_Delay(ms);
}

int gfx_wm_get_max_msaa(void) {
    return gfx_wm_backend()->get_max_msaa();
}

void gfx_wm_set_window_title(const char *title) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    SDL_SetWindowTitle(sSdlWindow, title);
}

void gfx_wm_reset_window_title(void) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    SDL_SetWindowTitle(sSdlWindow, TITLE);
}

void gfx_wm_shutdown(void) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    if (SDL_WasInit(0)) {
        SDL_GLContext ctx = SDL_GL_GetCurrentContext();
        if (ctx) { SDL_GL_DestroyContext(ctx); }
        if (sSdlWindow) { SDL_DestroyWindow(sSdlWindow); sSdlWindow = NULL; }
        SDL_Quit();
    }
}

bool gfx_wm_has_focus(void) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return true; }
    return (SDL_GetWindowFlags(sSdlWindow) & SDL_WINDOW_INPUT_FOCUS);
}

void gfx_wm_start_text_input(void) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    SDL_StartTextInput(sSdlWindow);
}

void gfx_wm_stop_text_input(void) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    SDL_StopTextInput(sSdlWindow);
}

char *gfx_wm_get_clipboard_text(void) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return ""; }
    static char sClipboardBuf[WAPI_CLIPBOARD_BUFSIZ];

    char *text = SDL_GetClipboardText();
    snprintf(sClipboardBuf, sizeof(sClipboardBuf), "%s", text);
    SDL_free(text);

    return sClipboardBuf;
}

void gfx_wm_set_clipboard_text(const char *text) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    SDL_SetClipboardText(text);
}

void gfx_wm_set_cursor_visible(bool visible) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    if (visible) {
        SDL_ShowCursor();
    } else {
        SDL_HideCursor();
    }
}
