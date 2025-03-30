#ifndef CONTROLLER_MOUSE_H
#define CONTROLLER_MOUSE_H

#include "controller_sdl.h"
#include <stdbool.h>

extern bool mouse_init_ok;

extern u32 mouse_buttons;
extern s32 mouse_x;
extern s32 mouse_y;

#define MOUSE_BUTTON_1 (1 << 0)
#define MOUSE_BUTTON_2 (1 << 1)
#define MOUSE_BUTTON_3 (1 << 2)
#define MOUSE_BUTTON_4 (1 << 3)
#define MOUSE_BUTTON_5 (1 << 4)

#define L_MOUSE_BUTTON MOUSE_BUTTON_1
#define M_MOUSE_BUTTON MOUSE_BUTTON_2
#define R_MOUSE_BUTTON MOUSE_BUTTON_3

extern u32 mouse_window_buttons;
extern u32 mouse_window_buttons_pressed;
extern u32 mouse_window_buttons_released;
extern s32 mouse_window_x;
extern s32 mouse_window_y;

extern u32 mouse_scroll_timestamp;
extern f32 mouse_scroll_x;
extern f32 mouse_scroll_y;

extern bool mouse_relative_enabled;

void controller_mouse_read_window(void);
void controller_mouse_read_relative(void);

void controller_mouse_enter_relative(void);
void controller_mouse_leave_relative(void);

void mouse_on_scroll(float x, float y);

#endif
