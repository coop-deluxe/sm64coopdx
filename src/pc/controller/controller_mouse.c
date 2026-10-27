#include "controller_mouse.h"
#include "pc/gfx/gfx_pc.h"
#include "pc/gfx/gfx_window_manager.h"
#include "pc/djui/djui.h"
#include "pc/pc_main.h"

#include <SDL3/SDL.h>

bool mouse_init_ok;

u32 mouse_buttons;
f32 mouse_x;
f32 mouse_y;

u32 mouse_window_buttons;
u32 mouse_window_buttons_pressed;
u32 mouse_window_buttons_released;
f32 mouse_window_x;
f32 mouse_window_y;

u32 mouse_scroll_timestamp;
f32 mouse_scroll_x;
f32 mouse_scroll_y;

bool mouse_relative_enabled;

void controller_mouse_read_window(void) {
    if (!mouse_init_ok) { return; }

    // SDL_GetMouseState for some reason grabs the coordinates in window scale, not drawable scale
    // Thanks to the folks at SDL, for some reason no function is provided to get the mouse coordinates in
    // "drawable space" which isn't exactly convenient. So to calculate the scale manually, we need to
    // apply a scale to the mouse coordinates to convert from window scale to drawable scale
    u32 windowSizeX;
    u32 windowSizeY;
    u32 drawableX;
    u32 drawableY;
    gfx_wm_get_window_size(&windowSizeX, &windowSizeY);
    gfx_wm_get_drawable_size(&drawableX, &drawableY);

    if (windowSizeX == 0 || windowSizeY == 0) { return; }

    f32 scaleX = (f32)drawableX / (f32)windowSizeX;
    f32 scaleY = (f32)drawableY / (f32)windowSizeY;

    // grab mouse coords
    mouse_window_buttons = SDL_GetMouseState(&mouse_window_x, &mouse_window_y);

    // account for scaling
    mouse_window_x *= scaleX;
    mouse_window_y *= scaleY;

    // account for 4:3 usage
    mouse_window_x -= gfx_current_dimensions.x_adjust_4by3;
    mouse_window_y -= gfx_current_dimensions.y_adjust_4by3;
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
        SDL_SetWindowRelativeMouseMode(gfx_wm_get_window(), true);
    }
}

void controller_mouse_leave_relative(void) {
    if (mouse_relative_enabled) {
        mouse_relative_enabled = false;
        SDL_SetWindowRelativeMouseMode(gfx_wm_get_window(), false);
    }
}

void mouse_on_scroll(float x, float y) {
    djui_interactable_on_scroll(x, y);
    mouse_scroll_timestamp = gGlobalTimer;
    mouse_scroll_x += x;
    mouse_scroll_y += y;
}
