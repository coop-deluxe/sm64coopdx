#include <SDL2/SDL.h>

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
    [GFX_WINDOW_BACKEND_DUMMY] = &gfx_window_dummy,
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

#define IS_FULLSCREEN() ((SDL_GetWindowFlags(sSdlWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)

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
        SDL_SetWindowFullscreen(sSdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(sSdlWindow, 0);
        SDL_ShowCursor(1);
        configWindow.exiting_fullscreen = true;
    }
    sBackends[currBackend]->set_fullscreen();
}

static void gfx_wm_reset_dimension_and_pos(void) {
    if (configWindow.exiting_fullscreen) {
        configWindow.exiting_fullscreen = false;
        SDL_ShowCursor(0);
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

#if defined(_WIN32)
    currBackend = gCLIOpts.backend != GFX_WINDOW_BACKEND_COUNT ? gCLIOpts.backend : configGraphicsBackend;
#else
    currBackend = configGraphicsBackend;
#endif
    sBackends[currBackend]->init(window_title);

    gfx_wm_set_fullscreen();
    if (configWindow.fullscreen) {
        SDL_ShowCursor(SDL_DISABLE);
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
    const Uint8 *state = SDL_GetKeyboardState(NULL);

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
            case SDL_TEXTINPUT:
                if (kb_text_input) { kb_text_input(event.text.text); }
                break;
            case SDL_TEXTEDITING: //IME composition
                if (kb_text_editing) { kb_text_editing(event.edit.text,event.edit.start); }
                break;
            case SDL_KEYDOWN:
                gfx_wm_onkeydown(event.key.keysym.scancode);
                break;
            case SDL_KEYUP:
                gfx_wm_onkeyup(event.key.keysym.scancode);
                break;
            case SDL_MOUSEWHEEL:
                gfx_wm_onscroll(event.wheel.preciseX, event.wheel.preciseY);
                break;
            case SDL_WINDOWEVENT:
                if (!IS_FULLSCREEN()) {
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_MOVED:
                            if (!configWindow.exiting_fullscreen) {
                                if (event.window.data1 >= 0) { configWindow.x = event.window.data1; }
                                if (event.window.data2 >= 0) { configWindow.y = event.window.data2; }
                            }
                            break;
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            configWindow.w = event.window.data1;
                            configWindow.h = event.window.data2;
                            break;
                    }
                }
                break;
            case SDL_DROPFILE:
                gfx_wm_ondropfile(event.drop.file);
                break;
            case SDL_QUIT:
                game_exit();
                break;
        }
        sBackends[currBackend]->handle_events(event);
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
    return sBackends[currBackend]->start_frame();
}

void gfx_wm_swap_buffers_begin(void) {
    sBackends[currBackend]->swap_buffers_begin();
}

void gfx_wm_swap_buffers_end(void) {
    sBackends[currBackend]->swap_buffers_end();
}

double gfx_wm_get_time(void) {
    return sBackends[currBackend]->get_time();
}

void gfx_wm_delay(u32 ms) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    SDL_Delay(ms);
}

int gfx_wm_get_max_msaa(void) {
    return sBackends[currBackend]->get_max_msaa();
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
        if (ctx) { SDL_GL_DeleteContext(ctx); }
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
    SDL_StartTextInput();
}

void gfx_wm_stop_text_input(void) {
    if (currBackend == GFX_WINDOW_BACKEND_DUMMY) { return; }
    SDL_StopTextInput();
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
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}