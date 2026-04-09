#include "controller_mouse.h"
#include "pc/gfx/gfx_pc.h"
#include "pc/djui/djui.h"

#include <SDL2/SDL.h>

#ifdef ENABLE_D3D11
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
extern HWND gfx_dxgi_get_h_wnd(void);
static bool mouse_relative_prev_cursor_state;
#endif

bool mouse_init_ok;

u32 mouse_buttons;
s32 mouse_x;
s32 mouse_y;

u32 mouse_window_buttons;
u32 mouse_window_buttons_pressed;
u32 mouse_window_buttons_released;
s32 mouse_window_x;
s32 mouse_window_y;

u32 mouse_scroll_timestamp;
f32 mouse_scroll_x;
f32 mouse_scroll_y;

bool mouse_relative_enabled;

#ifdef ENABLE_D3D11
u32 mouse_relative_buttons_held_on_focus;
u32 mouse_window_buttons_held_on_focus;
bool mouse_dxgi_prev_focus;

static u32 controller_mouse_dxgi_button_state(u32* mouse_held, bool has_focus) {
    u32 mouse =
        ((GetKeyState(VK_LBUTTON ) < 0) ? MOUSE_BUTTON_1 : 0) |
        ((GetKeyState(VK_MBUTTON ) < 0) ? MOUSE_BUTTON_2 : 0) |
        ((GetKeyState(VK_RBUTTON ) < 0) ? MOUSE_BUTTON_3 : 0) |
        ((GetKeyState(VK_XBUTTON1) < 0) ? MOUSE_BUTTON_4 : 0) |
        ((GetKeyState(VK_XBUTTON2) < 0) ? MOUSE_BUTTON_5 : 0);

    bool prev_focus = mouse_dxgi_prev_focus;
    mouse_dxgi_prev_focus = has_focus;

    // Ignore mouse clicks when game window doesn't have focus.
    if (!has_focus) { return 0; }
    if (mouse_held == NULL) { return mouse; }

    // Window just received input focus, ignore any held down mouse buttons.
    if (!prev_focus && has_focus) {
        *mouse_held = mouse;
        return 0;
    }

    // Wait for a mouse button held down (e.g. while clicking on the window)
    // to be released and pressed again.
    *mouse_held = (*mouse_held) & mouse;
    return ~(*mouse_held) & mouse;
}
#endif // ENABLE_D3D11

void controller_mouse_read_window(void) {
    if (!mouse_init_ok) { return; }

#if defined(ENABLE_D3D11)
    if (gWindowApi == &gfx_dxgi) {
        HWND game_window = gfx_dxgi_get_h_wnd();

        mouse_window_buttons = controller_mouse_dxgi_button_state(
            &mouse_window_buttons_held_on_focus,
            GetFocus() == game_window);

        POINT p;
        if (GetCursorPos(&p) && ScreenToClient(game_window, &p)) {
            mouse_window_x = p.x - gfx_current_dimensions.x_adjust_4by3;
            mouse_window_y = p.y;
        }
    } else
#endif
    {
        mouse_window_buttons = SDL_GetMouseState(&mouse_window_x, &mouse_window_y);
        mouse_window_x -= gfx_current_dimensions.x_adjust_4by3;
    }
}

void controller_mouse_read_relative(void) {
    if (!mouse_init_ok) { return; }

#if defined(ENABLE_D3D11)
    if (gWindowApi == &gfx_dxgi) {
        HWND game_window = gfx_dxgi_get_h_wnd();

        // Always get the buttons state, regardless if the relative mode is enabled.
        mouse_buttons = controller_mouse_dxgi_button_state(
            &mouse_relative_buttons_held_on_focus,
            GetFocus() == game_window);

        if (mouse_relative_enabled) {
            static POINT p0;
            POINT p1;
            RECT rect;
            if (GetWindowRect(game_window, &rect) && GetCursorPos(&p1)) {
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
    } else
#endif
    {
        mouse_buttons = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
    }

    if (mouse_scroll_y > 0) {
        mouse_buttons |= MWHEELUP;
    } else if (mouse_scroll_y < 0) {
        mouse_buttons |= MWHEELDOWN;
    }
}

void controller_mouse_enter_relative(void) {
    if (!mouse_relative_enabled) {
        mouse_relative_enabled = true;

#if defined(ENABLE_D3D11)
        if (gWindowApi == &gfx_dxgi) {
            CURSORINFO ci;
            ci.cbSize = sizeof(CURSORINFO);
            if (GetCursorInfo(&ci)) {
                mouse_relative_prev_cursor_state = (0 != ci.flags);
            } else {
                mouse_relative_prev_cursor_state = false;
            }

            ShowCursor(FALSE);
        } else
#endif
        {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
    }
}

void controller_mouse_leave_relative(void) {
    if (mouse_relative_enabled) {
        mouse_relative_enabled = false;

#if defined(ENABLE_D3D11)
        if (gWindowApi == &gfx_dxgi) {
            ShowCursor(mouse_relative_prev_cursor_state);
        } else
#endif
        {
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }
    }
}

void mouse_on_scroll(float x, float y) {
    djui_interactable_on_scroll(x, y);
    mouse_scroll_timestamp = gGlobalTimer;
    mouse_scroll_x += x;
    mouse_scroll_y += y;
}