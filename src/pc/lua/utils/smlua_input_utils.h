#define MAX_GAMEPADS 256
#define MAX_TOUCHPAD_FINGERS 10

#if defined(CAPI_SDL1) || defined(CAPI_SDL2)

#include <stdbool.h>
#include <SDL2/SDL.h>

struct Touchpad {
    Vec2f pos;
    f32 pressure;
    bool touched;
};

struct Gamepad {

    /* Misc Data */

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

    struct Touchpad touchpad[MAX_TOUCHPAD_FINGERS];

    /* Rumble */

    u16 loRumble;
    u16 hiRumble;

    /* LED Color */

    Color ledColor;

};

struct Keyboard {

    /* Scancodes */

    bool keyDown;
    bool keyPressed;
    bool keyReleased;

};

extern struct Gamepad gGamepads[MAX_GAMEPADS];
extern struct Keyboard gKeyboard[SDL_NUM_SCANCODES];

/* |description|Returns the current gamepad index in the config file|descriptionEnd| */
u32 get_current_gamepad_index(void);

#endif