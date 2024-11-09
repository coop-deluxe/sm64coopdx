#ifndef CONTROLLER_MOUSE_H
#define CONTROLLER_MOUSE_H

#include "controller_sdl.h"
#include <stdbool.h>

extern bool mouse_init_ok;

extern u32 mouse_buttons;
extern s32 mouse_x;
extern s32 mouse_y;

extern u32 mouse_window_buttons;
extern s32 mouse_window_x;
extern s32 mouse_window_y;

extern bool mouse_relative_enabled;

void controller_mouse_read_window(void);
void controller_mouse_read_relative(void);

void controller_mouse_enter_relative(void);
void controller_mouse_leave_relative(void);

#endif
