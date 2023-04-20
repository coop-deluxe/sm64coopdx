#ifdef CAPI_SDL2

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#include <SDL2/SDL.h>

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
#include "pc/lua/utils/smlua_misc_utils.h"

#include "pc/djui/djui.h"
#include "pc/djui/djui_hud_utils.h"

#define MAX_JOYBINDS 32
#define MAX_MOUSEBUTTONS 8 // arbitrary
#define MAX_JOYBUTTONS 32  // arbitrary; includes virtual keys for triggers
#define AXIS_THRESHOLD (30 * 256)

#ifdef BETTERCAMERA
extern u8 newcam_mouse;
#endif

static bool init_ok = false;
static bool haptics_enabled = false;
static SDL_GameController *sdl_cntrl = NULL;
static SDL_Haptic *sdl_haptic = NULL;

static bool sBackgroundGamepad = false;

static u32 num_joy_binds = 0;
static u32 num_mouse_binds = 0;
static u32 joy_binds[MAX_JOYBINDS][2] = { 0 };
static u32 mouse_binds[MAX_JOYBINDS][2] = { 0 };

static bool joy_buttons[MAX_JOYBUTTONS] = { false };
static u32 mouse_buttons = 0;
static u32 last_mouse = VK_INVALID;
static u32 last_joybutton = VK_INVALID;
static u32 last_gamepad = 0;

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
    // Allows game to be controlled by gamepad when not in focus
    if (configBackgroundGamepad) {
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    }
    sBackgroundGamepad = configBackgroundGamepad;

    if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
        return;
    }

    haptics_enabled = (SDL_InitSubSystem(SDL_INIT_HAPTIC) == 0);

    // try loading an external gamecontroller mapping file
    uint64_t gcsize = 0;
    void *gcdata = fs_load_file("gamecontrollerdb.txt", &gcsize);
    if (gcdata && gcsize) {
        SDL_RWops *rw = SDL_RWFromConstMem(gcdata, gcsize);
        if (rw) {
            int nummaps = SDL_GameControllerAddMappingsFromRW(rw, SDL_TRUE);
            if (nummaps >= 0)
                printf("loaded %d controller mappings from 'gamecontrollerdb.txt'\n", nummaps);
        }
        free(gcdata);
    }

#ifdef BETTERCAMERA
    if (newcam_mouse == 1)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
#endif

    controller_sdl_bind();

    init_ok = true;
}

static SDL_Haptic *controller_sdl_init_haptics(const int joy) {
    if (!haptics_enabled) return NULL;

    SDL_Haptic *hap = SDL_HapticOpen(joy);
    if (!hap) return NULL;

    if (SDL_HapticRumbleSupported(hap) != SDL_TRUE) {
        SDL_HapticClose(hap);
        return NULL;
    }

    if (SDL_HapticRumbleInit(hap) != 0) {
        SDL_HapticClose(hap);
        return NULL;
    }

    printf("controller %s has haptics support, rumble enabled\n", SDL_JoystickNameForIndex(joy));
    return hap;
}

static inline void update_button(const int i, const bool new) {
    const bool pressed = !joy_buttons[i] && new;
    const bool unpressed = joy_buttons[i] && !new;
    joy_buttons[i] = new;
    if (pressed) {
        last_joybutton = i;
        djui_interactable_on_key_down(VK_BASE_SDL_GAMEPAD + i);
    }
    if (unpressed) {
        djui_interactable_on_key_up(VK_BASE_SDL_GAMEPAD + i);
    }
}

u8 ignore_lock = FALSE;
static void controller_sdl_read(OSContPad *pad) {
    if (!init_ok) {
        return;
    }

#ifdef BETTERCAMERA
    if (!gDjuiHudLockMouse) {
        if (newcam_mouse == 1 && (!is_game_paused() || sCurrPlayMode != 2) && !gDjuiInMainMenu) {
            SDL_SetRelativeMouseMode(SDL_TRUE);
            ignore_lock = true;
        } else {
            SDL_SetRelativeMouseMode(SDL_FALSE);
            ignore_lock = false;
        }
    }

    u32 mouse = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);

    if (!gInteractableOverridePad) {
        for (u32 i = 0; i < num_mouse_binds; ++i)
            if (mouse & SDL_BUTTON(mouse_binds[i][0]))
                pad->button |= mouse_binds[i][1];
    }
    // remember buttons that changed from 0 to 1
    last_mouse = (mouse_buttons ^ mouse) & mouse;
    mouse_buttons = mouse;
#endif
    if (!ignore_lock && (!is_game_paused() || sCurrPlayMode != 2) && !gDjuiInMainMenu) {
        SDL_SetRelativeMouseMode(gDjuiHudLockMouse ? SDL_TRUE : SDL_FALSE);

#ifndef BETTERCAMERA
        u32 mouse = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);

        if (!gInteractableOverridePad) {
            for (u32 i = 0; i < num_mouse_binds; ++i)
                if (mouse & SDL_BUTTON(mouse_binds[i][0]))
                    pad->button |= mouse_binds[i][1];
        }
        // remember buttons that changed from 0 to 1
        last_mouse = (mouse_buttons ^ mouse) & mouse;
        mouse_buttons = mouse;
#endif
    }

    if (configBackgroundGamepad != sBackgroundGamepad) {
        sBackgroundGamepad = configBackgroundGamepad;
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, sBackgroundGamepad ? "1" : "0");
    }


    SDL_GameControllerUpdate();

    if (sdl_cntrl != NULL && !SDL_GameControllerGetAttached(sdl_cntrl)) {
        SDL_HapticClose(sdl_haptic);
        SDL_GameControllerClose(sdl_cntrl);
        sdl_cntrl = NULL;
        sdl_haptic = NULL;
    }

    if (sdl_cntrl == NULL || last_gamepad != configGamepadNumber) {
        if (SDL_IsGameController(configGamepadNumber)) {
            sdl_cntrl = SDL_GameControllerOpen(configGamepadNumber);
            if (sdl_cntrl != NULL) {
                sdl_haptic = controller_sdl_init_haptics(configGamepadNumber);
                last_gamepad = configGamepadNumber;
            }
            if (sdl_cntrl == NULL) {
                return;
            }
        } else {
            sdl_cntrl = NULL;
            return;
        }
    }
    
    int16_t leftx = SDL_GameControllerGetAxis(sdl_cntrl, SDL_CONTROLLER_AXIS_LEFTX);
    int16_t lefty = SDL_GameControllerGetAxis(sdl_cntrl, SDL_CONTROLLER_AXIS_LEFTY);
    int16_t rightx = SDL_GameControllerGetAxis(sdl_cntrl, SDL_CONTROLLER_AXIS_RIGHTX);
    int16_t righty = SDL_GameControllerGetAxis(sdl_cntrl, SDL_CONTROLLER_AXIS_RIGHTY);

    int16_t ltrig = SDL_GameControllerGetAxis(sdl_cntrl, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    int16_t rtrig = SDL_GameControllerGetAxis(sdl_cntrl, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

    for (u32 i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i) {
        const bool new = SDL_GameControllerGetButton(sdl_cntrl, i);
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

void controller_sdl_read_mouse_window(void) {
    if (!init_ok) { return; }

#if defined(_WIN32) && (defined(RAPI_D3D12) || defined(RAPI_D3D11))
    mouse_window_buttons = 0;
    mouse_window_buttons |= (GetAsyncKeyState(VK_LBUTTON) ? (1 << 0) : 0);
    mouse_window_buttons |= (GetAsyncKeyState(VK_RBUTTON) ? (1 << 1) : 0);
    POINT p;
    if (GetCursorPos(&p) && ScreenToClient(GetActiveWindow(), &p))
    {
        mouse_window_x = p.x;
        mouse_window_y = p.y;
    }
#else
    mouse_window_buttons = SDL_GetMouseState(&mouse_window_x, &mouse_window_y);
#endif
}

static void controller_sdl_rumble_play(f32 strength, f32 length) {
    if (sdl_haptic)
        SDL_HapticRumblePlay(sdl_haptic, strength, (u32)(length * 1000.0f));
}

static void controller_sdl_rumble_stop(void) {
    if (sdl_haptic)
        SDL_HapticRumbleStop(sdl_haptic);
}

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
    if (SDL_WasInit(SDL_INIT_GAMECONTROLLER)) {
        if (sdl_cntrl) {
            SDL_GameControllerClose(sdl_cntrl);
            sdl_cntrl = NULL;
        }
        SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
    }

    if (SDL_WasInit(SDL_INIT_HAPTIC)) {
        if (sdl_haptic) {
            SDL_HapticClose(sdl_haptic);
            sdl_haptic = NULL;
        }
        SDL_QuitSubSystem(SDL_INIT_HAPTIC);
    }

    haptics_enabled = false;
    init_ok = false;
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

#endif // CAPI_SDL2
