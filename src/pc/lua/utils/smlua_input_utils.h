
#ifndef smlua_input_util_H
#define smlua_input_util_H

#define DATABASES_DIRECTORY "databases"

#define MAX_GAMEPADS 256
#define MAX_TOUCHPAD_FINGERS 10

#include "types.h"

#include <stdbool.h>
#include <SDL3/SDL.h>

struct Finger {
    Vec2f pos;
    f32 pressure;
    bool touched;
};

struct Gamepad {
    SDL_Gamepad *pad; // Shouldn't be exposed, used to check if the gamepad exists
    const char *name;
    s32 index;
    u8 playerIndex;
    C_ARRAY bool buttons[SDL_GAMEPAD_BUTTON_COUNT];
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
extern struct Key gKeyboard[SDL_SCANCODE_COUNT];

/* |description|Returns the current gamepad index in the config file|descriptionEnd| */
u32 smlua_input_util_get_current_gamepad(void);
/* |description|Starts text input and grabs input focus|descriptionEnd| */
void smlua_input_util_start_text_input(void);
/* |description|Stops text input and loses input focus|descriptionEnd| */
void smlua_input_util_stop_text_input(void);
/* |description|Checks if text input is active and if you have input focus|descriptionEnd| */
bool smlua_input_util_text_input_active(void);
void smlua_input_util_clear(void);
void smlua_input_util_controller_maps_load(const char *mapsPath, bool appendMaps);
#endif