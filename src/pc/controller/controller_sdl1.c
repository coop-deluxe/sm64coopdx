#ifdef CAPI_SDL1

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#include <SDL/SDL.h>

// Analog camera movement by Pathétique (github.com/vrmiguel), y0shin and Mors
// Contribute or communicate bugs at github.com/vrmiguel/sm64-analog-camera

#include <ultra64.h>

#include "controller_api.h"
#include "controller_sdl.h"
#include "controller_mouse.h"
#include "../configfile.h"
#include "../platform.h"
#include "../fs/fs.h"

#include "game/level_update.h"
#include "game/bettercamera.h"

#include "pc/djui/djui.h"

#define MAX_JOYBINDS 32
#define MAX_MOUSEBUTTONS 8 // arbitrary
#define MAX_JOYBUTTONS 32  // arbitrary; includes virtual keys for triggers
#define AXIS_THRESHOLD (30 * 256)

enum {
    JOY_AXIS_LEFTX,
    JOY_AXIS_LEFTY,
    JOY_AXIS_RIGHTX,
    JOY_AXIS_RIGHTY,
    JOY_AXIS_LTRIG,
    JOY_AXIS_RTRIG,
    MAX_AXES,
};

static bool init_ok;
static SDL_Joystick *sdl_joy;

static u32 num_joy_binds = 0;
static u32 num_mouse_binds = 0;
static u32 joy_binds[MAX_JOYBINDS][2];
static u32 mouse_binds[MAX_JOYBINDS][2];
static int joy_axis_binds[MAX_AXES] = { 0, 1, 2, 3, 4, 5 };

static bool joy_buttons[MAX_JOYBUTTONS] = { false };
static u32 mouse_buttons = 0;
static u32 last_mouse = VK_INVALID;
static u32 last_joybutton = VK_INVALID;

static int num_joy_axes = 0;
static int num_joy_buttons = 0;
static int num_joy_hats = 0;

static inline void controller_add_binds(const u32 mask, const u32 *btns) {
    for (u32 i = 0; i < MAX_BINDS; ++i) {
        if (btns[i] >= VK_BASE_SDL_GAMEPAD && btns[i] <= VK_BASE_SDL_GAMEPAD + VK_SIZE) {
            if (btns[i] >= VK_BASE_SDL_MOUSE && num_joy_binds < MAX_JOYBINDS) {
                mouse_binds[num_mouse_binds][0] = btns[i] - VK_BASE_SDL_MOUSE;
                mouse_binds[num_mouse_binds][1] = mask;
                ++num_mouse_binds;
            } else if (num_mouse_binds < MAX_JOYBINDS) {
                joy_binds[num_joy_binds][0] = btns[i] - VK_BASE_SDL_GAMEPAD;
                joy_binds[num_joy_binds][1] = mask;
                ++num_joy_binds;
            }
        }
    }
}

static void controller_sdl_bind(void) {
    bzero(joy_binds, sizeof(joy_binds));
    bzero(mouse_binds, sizeof(mouse_binds));
    num_joy_binds = 0;
    num_mouse_binds = 0;

    controller_add_binds(A_BUTTON,     configKeyA);
    controller_add_binds(B_BUTTON,     configKeyB);
    controller_add_binds(X_BUTTON,     configKeyX);
    controller_add_binds(Y_BUTTON,     configKeyY);
    controller_add_binds(Z_TRIG,       configKeyZ);
    controller_add_binds(STICK_UP,     configKeyStickUp);
    controller_add_binds(STICK_LEFT,   configKeyStickLeft);
    controller_add_binds(STICK_DOWN,   configKeyStickDown);
    controller_add_binds(STICK_RIGHT,  configKeyStickRight);
    controller_add_binds(U_CBUTTONS,   configKeyCUp);
    controller_add_binds(L_CBUTTONS,   configKeyCLeft);
    controller_add_binds(D_CBUTTONS,   configKeyCDown);
    controller_add_binds(R_CBUTTONS,   configKeyCRight);
    controller_add_binds(L_TRIG,       configKeyL);
    controller_add_binds(R_TRIG,       configKeyR);
    controller_add_binds(START_BUTTON, configKeyStart);
    controller_add_binds(U_JPAD,       configKeyDUp);
    controller_add_binds(D_JPAD,       configKeyDDown);
    controller_add_binds(L_JPAD,       configKeyDLeft);
    controller_add_binds(R_JPAD,       configKeyDRight);
}

static void controller_sdl_init(void) {
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
        return;
    }

    if (SDL_NumJoysticks() > 0)
        sdl_joy = SDL_JoystickOpen(0);

    if (sdl_joy) {
        num_joy_axes = SDL_JoystickNumAxes(sdl_joy);
        num_joy_buttons = SDL_JoystickNumButtons(sdl_joy);
        num_joy_hats = SDL_JoystickNumHats(sdl_joy);

        for (int i = 0; i < MAX_AXES; ++i)
            if (i >= num_joy_axes)
                joy_axis_binds[i] = -1;
    }

    if (gNewCamera.isMouse && gMenuMode == -1 && !gDjuiChatBoxFocus && !gDjuiConsoleFocus) {
        controller_mouse_enter_relative();
    }
    controller_mouse_read_relative();

    controller_sdl_bind();

    init_ok = true;
    mouse_init_ok = true;
}

static inline void update_button(const int i, const bool new) {
    const bool pressed = !joy_buttons[i] && new;
    joy_buttons[i] = new;
    if (pressed) last_joybutton = i;
}

static inline int16_t get_axis(const int i) {
    if (joy_axis_binds[i] >= 0)
        return SDL_JoystickGetAxis(sdl_joy, i);
    else
        return 0;
}

extern s16 gMenuMode;
static void controller_sdl_read(OSContPad *pad) {
    if (!init_ok) return;

    if (gNewCamera.isMouse && gMenuMode == -1 && !gDjuiChatBoxFocus && !gDjuiConsoleFocus) {
        controller_mouse_enter_relative();
    } else {
        controller_mouse_leave_relative();
    }

    u32 mouse_prev = mouse_buttons;
    controller_mouse_read_relative();
    u32 mouse = mouse_buttons;

    if (!gInteractableOverridePad) {
        for (u32 i = 0; i < num_mouse_binds; ++i)
            if (mouse & SDL_BUTTON(mouse_binds[i][0]))
                pad->button |= mouse_binds[i][1];
    }

    // remember buttons that changed from 0 to 1
    last_mouse = (mouse_prev ^ mouse) & mouse;

    if (configDisableGamepads) { return; }
    if (!sdl_joy) return;

    SDL_JoystickUpdate();

    int16_t leftx = get_axis(JOY_AXIS_LEFTX);
    int16_t lefty = get_axis(JOY_AXIS_LEFTY);
    int16_t rightx = get_axis(JOY_AXIS_RIGHTX);
    int16_t righty = get_axis(JOY_AXIS_RIGHTY);

    int16_t ltrig = get_axis(JOY_AXIS_LTRIG);
    int16_t rtrig = get_axis(JOY_AXIS_RTRIG);

    for (int i = 0; i < num_joy_buttons; ++i) {
        const bool new = SDL_JoystickGetButton(sdl_joy, i);
        update_button(i, new);
    }

    update_button(VK_LTRIGGER - VK_BASE_SDL_GAMEPAD, ltrig > AXIS_THRESHOLD);
    update_button(VK_RTRIGGER - VK_BASE_SDL_GAMEPAD, rtrig > AXIS_THRESHOLD);

    u32 buttons_down = 0;
    for (u32 i = 0; i < num_joy_binds; ++i)
        if (joy_buttons[joy_binds[i][0]])
            buttons_down |= joy_binds[i][1];

    pad->button |= buttons_down;

    const u32 xstick = buttons_down & STICK_XMASK;
    const u32 ystick = buttons_down & STICK_YMASK;
    if (xstick == STICK_LEFT)
        pad->stick_x = -128;
    else if (xstick == STICK_RIGHT)
        pad->stick_x = 127;
    if (ystick == STICK_DOWN)
        pad->stick_y = -128;
    else if (ystick == STICK_UP)
        pad->stick_y = 127;

    if (rightx < -0x4000) pad->button |= L_CBUTTONS;
    if (rightx > 0x4000) pad->button |= R_CBUTTONS;
    if (righty < -0x4000) pad->button |= U_CBUTTONS;
    if (righty > 0x4000) pad->button |= D_CBUTTONS;

    uint32_t magnitude_sq = (uint32_t)(leftx * leftx) + (uint32_t)(lefty * lefty);
    uint32_t stickDeadzoneActual = configStickDeadzone * DEADZONE_STEP;
    if (magnitude_sq > (uint32_t)(stickDeadzoneActual * stickDeadzoneActual)) {
        pad->stick_x = leftx / 0x100;
        int stick_y = -lefty / 0x100;
        pad->stick_y = stick_y == 128 ? 127 : stick_y;
    }

    magnitude_sq = (uint32_t)(rightx * rightx) + (uint32_t)(righty * righty);
    stickDeadzoneActual = configStickDeadzone * DEADZONE_STEP;
    if (magnitude_sq > (uint32_t)(stickDeadzoneActual * stickDeadzoneActual)) {
        pad->ext_stick_x = rightx / 0x100;
        int stick_y = -righty / 0x100;
        pad->ext_stick_y = stick_y == 128 ? 127 : stick_y;
    }
}

static void controller_sdl_rumble_play(f32 strength, f32 length) { }

static void controller_sdl_rumble_stop(void) { }

static u32 controller_sdl_rawkey(void) {
    if (last_joybutton != VK_INVALID) {
        const u32 ret = last_joybutton;
        last_joybutton = VK_INVALID;
        return ret;
    }

    for (u32 i = 1; i < MAX_MOUSEBUTTONS; ++i) {
        if (last_mouse & SDL_BUTTON(i)) {
            const u32 ret = VK_OFS_SDL_MOUSE + i;
            last_mouse = 0;
            return ret;
        }
    }
    return VK_INVALID;
}

static void controller_sdl_shutdown(void) {
    if (SDL_WasInit(SDL_INIT_JOYSTICK)) {
        if (sdl_joy) {
            SDL_JoystickClose(sdl_joy);
            sdl_joy = NULL;
        }
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    }

    init_ok = false;
    mouse_init_ok = false;
}

struct ControllerAPI controller_sdl = {
    VK_BASE_SDL_GAMEPAD,
    controller_sdl_init,
    controller_sdl_read,
    controller_sdl_rawkey,
    controller_sdl_rumble_play,
    controller_sdl_rumble_stop,
    controller_sdl_bind,
    controller_sdl_shutdown
};

#endif // CAPI_SDL1
