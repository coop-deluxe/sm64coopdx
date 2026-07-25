
#ifndef SMLUA_INPUT_UTILS_H
#define SMLUA_INPUT_UTILS_H

#define DATABASES_DIRECTORY "databases"

#define MAX_GAMEPADS 256
#define MAX_TOUCHPAD_FINGERS 10

#include "types.h"

#include <stdbool.h>
#include <SDL2/SDL.h>

struct Finger {
    Vec2f pos;
    f32 pressure;
    bool touched;
};

struct Gamepad {
    SDL_GameController *controller; // Shouldn't be exposed, used to check if the controller exists
    const char *name;
    s32 index;
    u8 playerIndex;
    C_ARRAY bool buttons[SDL_CONTROLLER_BUTTON_MAX];
    s16 leftTrigger;
    s16 rightTrigger;
    Vec2s leftStick;
    Vec2s rightStick;
    Vec3f gyro;
    Vec3f accelerometer;
    Vec3f leftGyro;
    Vec3f rightGyro;
    Vec3f leftAccelerometer;
    Vec3f rightAccelerometer;
    struct Finger touchpad[MAX_TOUCHPAD_FINGERS];
    u16 rumbleLowFreq;
    u16 rumbleHighFreq;
    u32 rumbleDurationMs;
    Color ledColor;
};

struct Key {
    bool down;
    bool pressed;
    bool released;
};

extern bool gModHasInputFocus;

extern struct Gamepad gGamepads[MAX_GAMEPADS];
extern struct Key gKeyboard[SDL_NUM_SCANCODES];

/* |description|Returns the current gamepad index in the config file|descriptionEnd| */
u32 get_current_gamepad_index(void);
/* |description|Returns the clipboard text|descriptionEnd| */
const char *get_clipboard_text(void);
/* |description|Sets the clipboard text|descriptionEnd| */
void set_clipboard_text(const char *text);
/* |description|Starts text input and grabs input focus|descriptionEnd| */
void start_text_input(void);
/* |description|Stops text input and loses input focus|descriptionEnd| */
void stop_text_input(void);
/* |description|Checks if text input is active and if you have input focus|descriptionEnd| */
bool is_text_input_active(void);
void clear_gamepad_input_data(void);
void controller_maps_load(const char *mapsPath, bool appendMaps);
#endif