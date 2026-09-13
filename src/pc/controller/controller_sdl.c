#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#include <SDL3/SDL.h>

#include <ultra64.h>

#include "controller_api.h"
#include "controller_sdl.h"
#include "controller_mouse.h"
#include "pc/pc_main.h"
#include "pc/configfile.h"
#include "pc/platform.h"
#include "pc/fs/fs.h"

#include "game/level_update.h"
#include "game/first_person_cam.h"
#include "game/bettercamera.h"
#include "pc/lua/utils/smlua_misc_utils.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_panel_pause.h"
#include "pc/djui/djui_hud_utils.h"

#define MAX_JOYBINDS 32
#define MAX_MOUSEBUTTONS 8 // arbitrary
#define MAX_JOYBUTTONS 32  // arbitrary; includes virtual keys for triggers
#define AXIS_THRESHOLD (30 * 256)

static bool sInitOk = false;
static bool sHapticsEnabled = false;
static SDL_Gamepad *sSdlGamepad = NULL;
static SDL_Joystick *sSdlJoystick = NULL;
static SDL_Haptic *sSdlHaptic = NULL;

static bool sExtendedReports = false;
static bool sBackgroundGamepad = false;

static u32 sSelectedGamepad = 0;

static u32 sNumJoyBinds = 0;
static u32 sNumMouseBinds = 0;
static u32 sJoyBinds[MAX_JOYBINDS][2] = { 0 };
static u32 sMouseBinds[MAX_JOYBINDS][2] = { 0 };

static bool sJoyButtons[MAX_JOYBUTTONS] = { false };
static u32 sLastMouse = VK_INVALID;
static u32 sLastJoyButton = VK_INVALID;
static u32 sLastGamepad = 0;

static s16 invert_s16(s16 val) {
    if (val == -0x8000) return 0x7FFF;
    return (s16)(-(s32)val);
}

static inline void controller_add_binds(const u32 mask, const u32 *btns) {
    for (u32 i = 0; i < MAX_BINDS; ++i) {
        if (btns[i] >= VK_BASE_SDL_GAMEPAD && btns[i] <= VK_BASE_SDL_GAMEPAD + VK_SIZE) {
            if (btns[i] >= VK_BASE_SDL_MOUSE && sNumMouseBinds < MAX_JOYBINDS) {
                sMouseBinds[sNumMouseBinds][0] = btns[i] - VK_BASE_SDL_MOUSE;
                sMouseBinds[sNumMouseBinds][1] = mask;
                ++sNumMouseBinds;
            } else if (sNumJoyBinds < MAX_JOYBINDS) {
                sJoyBinds[sNumJoyBinds][0] = btns[i] - VK_BASE_SDL_GAMEPAD;
                sJoyBinds[sNumJoyBinds][1] = mask;
                ++sNumJoyBinds;
            }
        }
    }
}

static void controller_sdl_bind(void) {
    bzero(sJoyBinds, sizeof(sJoyBinds));
    bzero(sMouseBinds, sizeof(sMouseBinds));
    sNumJoyBinds = 0;
    sNumMouseBinds = 0;

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
    // Allows extended reports on PS4 and PS5 controllers
    if (configExtendedReports) {
        SDL_SetHint(SDL_HINT_JOYSTICK_ENHANCED_REPORTS, "1");
    }
    sExtendedReports = configExtendedReports;

    // Allows game to be controlled by gamepad when not in focus
    if (configBackgroundGamepad) {
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    }
    sBackgroundGamepad = configBackgroundGamepad;

    if (!SDL_Init(SDL_INIT_GAMEPAD | SDL_INIT_EVENTS)) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return;
    }

#if defined(_WIN32)
    extern void WIN_UpdateKeymap(void);
    WIN_UpdateKeymap();
#endif

    sHapticsEnabled = SDL_InitSubSystem(SDL_INIT_HAPTIC);

    // try loading an external gamecontroller mapping file
    uint64_t gcsize = 0;
    void *gcdata = fs_load_file("gamecontrollerdb.txt", &gcsize);
    if (gcdata && gcsize) {
        SDL_IOStream *src = SDL_IOFromConstMem(gcdata, gcsize);
        if (src) {
            int numMaps = SDL_AddGamepadMappingsFromIO(src, true);
            if (numMaps >= 0) {
                LOG_INFO("loaded %d controller mappings from 'gamecontrollerdb.txt'\n", numMaps);
            }
        }
        free(gcdata);
    }

    if (gNewCamera.isMouse) { controller_mouse_enter_relative(); }
    controller_mouse_read_relative();

    controller_sdl_bind();

    sInitOk = true;
    mouse_init_ok = true;
}

static SDL_Haptic *controller_sdl_init_haptics(void) {
    if (!sHapticsEnabled) { return NULL; }

    SDL_Haptic *hap = SDL_OpenHapticFromJoystick(sSdlJoystick);
    if (!hap) { return NULL; }

    if (!SDL_HapticRumbleSupported(hap)) {
        SDL_CloseHaptic(hap);
        return NULL;
    }

    if (!SDL_InitHapticRumble(hap)) {
        SDL_CloseHaptic(hap);
        return NULL;
    }

    return hap;
}

static inline void update_button(const int i, const bool new) {
    const bool pressed = !sJoyButtons[i] && new;
    const bool unpressed = sJoyButtons[i] && !new;
    sJoyButtons[i] = new;
    if (pressed) {
        sLastJoyButton = i;
        djui_panel_pause_disconnect_key_update(VK_BASE_SDL_GAMEPAD + i);
        djui_interactable_on_key_down(VK_BASE_SDL_GAMEPAD + i);
    }
    if (unpressed) {
        djui_interactable_on_key_up(VK_BASE_SDL_GAMEPAD + i);
    }
}

static inline void update_analog_stick(s8 *stick_x, s8 *stick_y, int16_t input_x, int16_t input_y) {
    float magnitude_sq = (float)(input_x * input_x) + (float)(input_y * input_y);
    float deadzone = configStickDeadzone * DEADZONE_STEP;

    if (magnitude_sq > (deadzone * deadzone)) {
        float magnitude = sqrtf(magnitude_sq);
        float dir_x = (float)input_x / magnitude;
        float dir_y = (float)input_y / magnitude;
        float scale = 1.f / fmaxf(fabsf(dir_x), fabsf(dir_y));
        float max_magnitude = 0x8000 * scale;

        magnitude -= deadzone;
        magnitude *= max_magnitude / (max_magnitude - deadzone);
        magnitude /= 0x100;
        magnitude = fminf(magnitude, scale * 127.f);

        *stick_x = dir_x * magnitude;
        *stick_y = -dir_y * magnitude;
    }
}

extern s16 gMenuMode;
static void controller_sdl_read(OSContPad *pad) {
    if (!sInitOk) { return; }

    if ((gNewCamera.isMouse || get_first_person_enabled() || gDjuiHudLockMouse) && !is_game_paused() && !gDjuiPanelPauseCreated && !gDjuiInMainMenu && !gDjuiChatBoxFocus && !gDjuiConsoleFocus && gfx_wm_has_focus()) {
        controller_mouse_enter_relative();
    } else {
        controller_mouse_leave_relative();
    }

    u32 mouse_prev = mouse_buttons;
    controller_mouse_read_relative();
    u32 mouse = mouse_buttons;

    u32 buttons_down = 0;
    if (!gInteractableOverridePad) {
        for (u32 i = 0; i < sNumMouseBinds; ++i) {
            if (mouse & SDL_BUTTON_MASK(sMouseBinds[i][0])) {
                buttons_down |= sMouseBinds[i][1];
            }
        }
    }
    pad->button |= buttons_down;
    // remember buttons that changed from 0 to 1
    sLastMouse = (mouse_prev ^ mouse) & mouse;

    if (configExtendedReports != sExtendedReports) {
        sExtendedReports = configExtendedReports;
        char* hint = sExtendedReports ? "1" : "0";
        SDL_SetHint(SDL_HINT_JOYSTICK_ENHANCED_REPORTS, hint);
    }

    if (configBackgroundGamepad != sBackgroundGamepad) {
        sBackgroundGamepad = configBackgroundGamepad;
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, sBackgroundGamepad ? "1" : "0");
    }

    if (configDisableGamepads) { return; }

    SDL_UpdateGamepads();

    if (sSdlGamepad != NULL && !SDL_GamepadConnected(sSdlGamepad)) {
        if (sSdlHaptic) { SDL_CloseHaptic(sSdlHaptic); sSdlHaptic = NULL; }
        SDL_CloseGamepad(sSdlGamepad);
        sSdlGamepad = NULL;
    }

    if ((!sSdlGamepad && !sSdlJoystick) || sLastGamepad != sSelectedGamepad) {
        int numJoysticks;
        SDL_JoystickID *ids = SDL_GetJoysticks(&numJoysticks);
        if ((int)configGamepadNumber >= numJoysticks) { configGamepadNumber = numJoysticks; }
        sSelectedGamepad = ids[configGamepadNumber];
        SDL_free(ids);

        if (sSdlHaptic) { SDL_CloseHaptic(sSdlHaptic); sSdlHaptic = NULL; }
        if (sSdlGamepad) { SDL_CloseGamepad(sSdlGamepad); sSdlGamepad = NULL; }
        if (sSdlJoystick) { SDL_CloseJoystick(sSdlJoystick); sSdlJoystick = NULL; }
        sLastGamepad = sSelectedGamepad;
        if (SDL_IsGamepad(sSelectedGamepad)) {
            sSdlGamepad = SDL_OpenGamepad(sSelectedGamepad);
            if (sSdlGamepad != NULL) {
                sSdlHaptic = controller_sdl_init_haptics();
            }
        } else {
            sSdlJoystick = SDL_OpenJoystick(sSelectedGamepad);
            if (!sSdlJoystick) { return; }
        }
    }

    int16_t leftx = 0, lefty = 0, rightx = 0, righty = 0;
    int16_t ltrig = 0, rtrig = 0;
    if (sSdlGamepad) {
        leftx = SDL_GetGamepadAxis(sSdlGamepad, SDL_GAMEPAD_AXIS_LEFTX);
        lefty = SDL_GetGamepadAxis(sSdlGamepad, SDL_GAMEPAD_AXIS_LEFTY);
        rightx = SDL_GetGamepadAxis(sSdlGamepad, SDL_GAMEPAD_AXIS_RIGHTX);
        righty = SDL_GetGamepadAxis(sSdlGamepad, SDL_GAMEPAD_AXIS_RIGHTY);
        ltrig = SDL_GetGamepadAxis(sSdlGamepad, SDL_GAMEPAD_AXIS_LEFT_TRIGGER);
        rtrig = SDL_GetGamepadAxis(sSdlGamepad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER);
        for (u32 i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; ++i) {
            const bool new = SDL_GetGamepadButton(sSdlGamepad, i);
            update_button(i, new);
        }
    } else if (sSdlJoystick) {
        int axis_count = SDL_GetNumJoystickAxes(sSdlJoystick);
        if (axis_count >= 2) {
            leftx = SDL_GetJoystickAxis(sSdlJoystick, 0);
            lefty = SDL_GetJoystickAxis(sSdlJoystick, 1);
        }
        if (axis_count >= 4) {
            rightx = SDL_GetJoystickAxis(sSdlJoystick, 2);
            righty = SDL_GetJoystickAxis(sSdlJoystick, 5); // Specific to N64 controller
        }
        if (axis_count >= 6) {
            ltrig = SDL_GetJoystickAxis(sSdlJoystick, 3);
            rtrig = SDL_GetJoystickAxis(sSdlJoystick, 4);
        }

        int button_count = SDL_GetNumJoystickButtons(sSdlJoystick);
        for (int i = 0; i < button_count && i < MAX_JOYBUTTONS; ++i) {
            update_button(i, SDL_GetJoystickButton(sSdlJoystick, i));
        }
    }

    if (configStick.rotateLeft) {
        s16 tmp = leftx;
        leftx = invert_s16(lefty);
        lefty = tmp;
    }
    if (configStick.rotateRight) {
        s16 tmp = rightx;
        rightx = invert_s16(righty);
        righty = tmp;
    }
    if (configStick.invertLeftX) { leftx = invert_s16(leftx); }
    if (configStick.invertLeftY) { lefty = invert_s16(lefty); }
    if (configStick.invertRightX) { rightx = invert_s16(rightx); }
    if (configStick.invertRightY) { righty = invert_s16(righty); }

    update_button(VK_LTRIGGER - VK_BASE_SDL_GAMEPAD, ltrig > AXIS_THRESHOLD);
    update_button(VK_RTRIGGER - VK_BASE_SDL_GAMEPAD, rtrig > AXIS_THRESHOLD);

    for (u32 i = 0; i < sNumJoyBinds; ++i) {
        if (sJoyButtons[sJoyBinds[i][0]]) {
            buttons_down |= sJoyBinds[i][1];
        }
    }

    pad->button |= buttons_down;

    const u32 xstick = buttons_down & STICK_XMASK;
    const u32 ystick = buttons_down & STICK_YMASK;

    if (xstick == STICK_LEFT) {
        pad->stick_x = -128;
    } else if (xstick == STICK_RIGHT) {
        pad->stick_x = 127;
    } if (ystick == STICK_DOWN) {
        pad->stick_y = -128;
    } else if (ystick == STICK_UP) {
        pad->stick_y = 127;
    }

    if (rightx < -0x4000) { pad->button |= L_CBUTTONS; }
    if (rightx > 0x4000) { pad->button |= R_CBUTTONS; }
    if (righty < -0x4000) { pad->button |= U_CBUTTONS; }
    if (righty > 0x4000) { pad->button |= D_CBUTTONS; }

    update_analog_stick(&pad->stick_x, &pad->stick_y, leftx, lefty);
    update_analog_stick(&pad->ext_stick_x, &pad->ext_stick_y, rightx, righty);
}

static void controller_sdl_rumble_play(f32 strength, f32 length) {
    if (strength < 0 || strength > 1) { return; } // make sure strengh is between 0 and 1
    if (sSdlHaptic) {
        // play rumble haptics
        SDL_PlayHapticRumble(sSdlHaptic, strength, (u32)(length * 1000.0f));
    } else {
        if (SDL_GetBooleanProperty(SDL_GetGamepadProperties(sSdlGamepad), SDL_PROP_GAMEPAD_CAP_RUMBLE_BOOLEAN, false)) {
            // scale strength to be in between 0 and 65535
            u16 scaledStrength = (u16)(strength * 65535);
            // rumble!!!
            SDL_RumbleGamepad(sSdlGamepad, scaledStrength, scaledStrength, (u32)(length * 1000.0f));
        }
    }
}

static void controller_sdl_rumble_stop(void) {
    if (sSdlHaptic) {
        SDL_StopHapticRumble(sSdlHaptic);
    } else {
        if (SDL_GetBooleanProperty(SDL_GetGamepadProperties(sSdlGamepad), SDL_PROP_GAMEPAD_CAP_RUMBLE_BOOLEAN, false)) {
            SDL_RumbleGamepad(sSdlGamepad, 0, 0, 0);
        }
    }
}

static u32 controller_sdl_rawkey(void) {
    if (sLastJoyButton != VK_INVALID) {
        const u32 ret = sLastJoyButton;
        sLastJoyButton = VK_INVALID;
        return ret;
    }

    for (u32 i = 1; i < MAX_MOUSEBUTTONS; ++i) {
        if (sLastMouse & SDL_BUTTON_MASK(i)) {
            const u32 ret = VK_OFS_SDL_MOUSE + i;
            sLastMouse = 0;
            return ret;
        }
    }
    return VK_INVALID;
}

static void controller_sdl_shutdown(void) {
    if (SDL_WasInit(SDL_INIT_GAMEPAD)) {
        if (sSdlGamepad) {
            SDL_CloseGamepad(sSdlGamepad);
            sSdlGamepad = NULL;
        }
        if (sSdlJoystick) {
            SDL_CloseJoystick(sSdlJoystick);
            sSdlJoystick = NULL;
        }
        SDL_QuitSubSystem(SDL_INIT_GAMEPAD);
    }

    if (SDL_WasInit(SDL_INIT_HAPTIC)) {
        if (sSdlHaptic) {
            SDL_CloseHaptic(sSdlHaptic);
            sSdlHaptic = NULL;
        }
        SDL_QuitSubSystem(SDL_INIT_HAPTIC);
    }

    sHapticsEnabled = false;
    sInitOk = false;
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
