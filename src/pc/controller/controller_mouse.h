#ifndef CONTROLLER_MOUSE_H
#define CONTROLLER_MOUSE_H

#include "controller_api.h"

extern int mouse_x;
extern int mouse_y;

extern int mouse_window_buttons;
extern int mouse_window_x;
extern int mouse_window_y;


#define VK_BASE_MOUSE 0x2000

extern struct ControllerAPI controller_mouse;

#endif
