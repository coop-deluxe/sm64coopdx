
#ifndef SMLUA_INPUT_UTILS_H
#define SMLUA_INPUT_UTILS_H

#define DATABASES_DIRECTORY "databases"

#define MAX_GAMEPADS 256
#define MAX_TOUCHPAD_FINGERS 10

#if defined(CAPI_SDL1) || defined(CAPI_SDL2)

#include "types.h"

#include <stdbool.h>
#include <SDL2/SDL.h>

struct Finger {
    Vec2f pos;
    f32 pressure;
    bool touched;
};

struct Gamepad {

    /* Misc Data */

    SDL_GameController *controller; // Shouldn't be exposed, used to check if the controller exists

    const char *name;
    s32 index;
    u8 playerIndex; // Used specifically for player LEDs, 0 by default, can also be used to assign controllers to players

    /* Buttons */

    bool buttons[SDL_CONTROLLER_BUTTON_MAX];
    
    /* Triggers */

    s16 leftTrigger;
    s16 rightTrigger;

    /* Sticks */
    
    Vec2s leftStick;
    Vec2s rightStick;
    
    /* Sensors */

    Vec3f gyro;
    Vec3f accelerometer;

    // These are used for controllers that may have more than one of a sensor, like joycons

    Vec3f leftGyro;
    Vec3f rightGyro;
    Vec3f leftAccelerometer;
    Vec3f rightAccelerometer;

    /* Touchpad */

    struct Finger touchpad[MAX_TOUCHPAD_FINGERS];

    /* Rumble */

    u16 rumbleLowFreq;
    u16 rumbleHighFreq;
    u32 rumbleDurationMs;

    /* LED Color */

    Color ledColor;

};

struct Key {

    /* Scancodes */

    bool down;
    bool pressed;
    bool released;

};

extern struct Gamepad gGamepads[MAX_GAMEPADS];
extern struct Key gKeyboard[SDL_NUM_SCANCODES];

/* |description|Returns the current gamepad index in the config file|descriptionEnd| */
u32 get_current_gamepad_index(void);
/* |description|Returns the clipboard text|descriptionEnd| */
const char* get_clipboard_text(void);
/* |description|Sets the clipboard text|descriptionEnd| */
void set_clipboard_text(const char* text);
void clear_gamepad_input_data(void);
void controller_maps_load(const char* mapsPath, bool appendMaps);

#endif
#endif