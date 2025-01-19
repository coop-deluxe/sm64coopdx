#ifndef CONTROLLER_KEYBOARD_H
#define CONTROLLER_KEYBOARD_H

#include <stdbool.h>
#include "controller_api.h"

# define VK_BASE_KEYBOARD 0x0000

#define SCANCODE_ESCAPE          1
#define SCANCODE_BACKSPACE      14
#define SCANCODE_ENTER          28
#define SCANCODE_SHIFT_LEFT     42
#ifdef __APPLE__
    #define SCANCODE_CONTROL_LEFT   91
#else
    #define SCANCODE_CONTROL_LEFT   29
#endif
#define SCANCODE_ALT_LEFT       56
#define SCANCODE_A              30
#define SCANCODE_X              45
#define SCANCODE_C              46
#define SCANCODE_V              47
#define SCANCODE_SHIFT_RIGHT    54
#ifdef __APPLE__
    #define SCANCODE_CONTROL_RIGHT 92
#else
    #define SCANCODE_CONTROL_RIGHT 285
#endif
#define SCANCODE_ALT_RIGHT     312
#define SCANCODE_HOME          327
#define SCANCODE_LEFT          331
#define SCANCODE_RIGHT         333
#define SCANCODE_END           335
#define SCANCODE_INSERT        338
#define SCANCODE_DELETE        339

#ifdef __cplusplus
extern "C" {
#endif

bool keyboard_on_key_down(int scancode);
bool keyboard_on_key_up(int scancode);
void keyboard_on_all_keys_up(void);
void keyboard_on_text_input(char* text);
void keyboard_on_text_editing(char* text, int cursorPos);

#ifdef __cplusplus
}
#endif

extern struct ControllerAPI controller_keyboard;

#endif
