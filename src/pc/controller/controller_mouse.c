#include "controller_mouse.h"
#include "pc/gfx/gfx_pc.h"
#include "pc/djui/djui.h"
#include "pc/pc_main.h"

#include <SDL2/SDL.h>

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

void controller_mouse_read_window(void) {
    if (!mouse_init_ok) { return; }

    mouse_window_buttons = SDL_GetMouseState(&mouse_window_x, &mouse_window_y);
    mouse_window_x -= gfx_current_dimensions.x_adjust_4by3;
}

void controller_mouse_read_relative(void) {
    if (!mouse_init_ok) { return; }

    mouse_buttons = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);

    if (mouse_scroll_y > 0) {
        mouse_buttons |= MWHEELUP;
    } else if (mouse_scroll_y < 0) {
        mouse_buttons |= MWHEELDOWN;
    }
}

void controller_mouse_enter_relative(void) {
    if (!mouse_relative_enabled) {
        mouse_relative_enabled = true;
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
}

void controller_mouse_leave_relative(void) {
    if (mouse_relative_enabled) {
        mouse_relative_enabled = false;
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

void mouse_on_scroll(float x, float y) {
    djui_interactable_on_scroll(x, y);
    mouse_scroll_timestamp = gGlobalTimer;
    mouse_scroll_x += x;
    mouse_scroll_y += y;
}