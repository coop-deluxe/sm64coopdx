#include "controller_mouse.h"

#ifdef WAPI_DXGI
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
extern HWND gfx_dxgi_get_h_wnd(void);
static bool mouse_relative_prev_cursor_state;
#elif defined(CAPI_SDL1)
#include <SDL/SDL.h>
#elif defined(CAPI_SDL2)
#include <SDL2/SDL.h>
#endif

bool mouse_init_ok;

u32 mouse_buttons;
s32 mouse_x;
s32 mouse_y;

u32 mouse_window_buttons;
s32 mouse_window_x;
s32 mouse_window_y;

bool mouse_relative_enabled;

void controller_mouse_read_window(void) {
    if (!mouse_init_ok) { return; }

#if defined(WAPI_DXGI)
    mouse_window_buttons =
        (GetAsyncKeyState(VK_LBUTTON) ? (1 << 0) : 0) |
        (GetAsyncKeyState(VK_MBUTTON) ? (1 << 1) : 0) |
        (GetAsyncKeyState(VK_RBUTTON) ? (1 << 2) : 0);

    POINT p;
    if (GetCursorPos(&p) && ScreenToClient(gfx_dxgi_get_h_wnd(), &p)) {
        mouse_window_x = p.x;
        mouse_window_y = p.y;
    }
#elif defined(CAPI_SDL1) || defined(CAPI_SDL2)
    mouse_window_buttons = SDL_GetMouseState(&mouse_window_x, &mouse_window_y);
#endif
}

void controller_mouse_read_relative(void) {
    if (!mouse_init_ok) { return; }

#if defined(WAPI_DXGI)
    mouse_buttons =
        (GetAsyncKeyState(VK_LBUTTON) ? (1 << 0) : 0) |
        (GetAsyncKeyState(VK_MBUTTON) ? (1 << 1) : 0) |
        (GetAsyncKeyState(VK_RBUTTON) ? (1 << 2) : 0);

    if (mouse_relative_enabled) {
        static POINT p0;
        POINT p1;
        RECT rect;
        if (GetWindowRect(gfx_dxgi_get_h_wnd(), &rect) && GetCursorPos(&p1)) {
            mouse_x = p1.x - p0.x;
            mouse_y = p1.y - p0.y;

            p0.x = rect.left + (rect.right - rect.left) / 2;
            p0.y = rect.top + (rect.bottom - rect.top) / 2;
            SetCursorPos(p0.x, p0.y);
        }
    } else {
        mouse_x = 0;
        mouse_y = 0;
    }

#elif defined(CAPI_SDL1) || defined(CAPI_SDL2)
    mouse_buttons = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
#endif
}

void controller_mouse_enter_relative(void) {
    if (!mouse_relative_enabled) {
        mouse_relative_enabled = true;

#if defined(WAPI_DXGI)
        CURSORINFO ci;
        ci.cbSize = sizeof(CURSORINFO);
        if (GetCursorInfo(&ci)) {
            mouse_relative_prev_cursor_state = (0 != ci.flags);
        } else {
            mouse_relative_prev_cursor_state = false;
        }

        ShowCursor(FALSE);
#elif defined(CAPI_SDL1)
        SDL_WM_GrabInput(SDL_GRAB_ON);
#elif defined(CAPI_SDL2)
        SDL_SetRelativeMouseMode(SDL_TRUE);
#endif
    }
}

void controller_mouse_leave_relative(void) {
    if (mouse_relative_enabled) {
        mouse_relative_enabled = false;

#if defined(WAPI_DXGI)
        ShowCursor(mouse_relative_prev_cursor_state);
#elif defined(CAPI_SDL1)
        SDL_WM_GrabInput(SDL_GRAB_OFF);
#elif defined(CAPI_SDL2)
        SDL_SetRelativeMouseMode(SDL_FALSE);
#endif
    }
}

