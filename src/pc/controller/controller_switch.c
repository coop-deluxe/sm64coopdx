#ifdef CAPI_SWITCH

#include <stdlib.h>
#include <ultra64.h>
#include <switch.h>

#include <sm64.h>
#include "../../game/level_update.h"

#include "controller_switch.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_base.h"
#include "pc/djui/djui_interactable.h"
#include "pc/djui/djui_panel_pause.h"

// Buttons & Sticks
static HidAnalogStickState stickStates[2] = { 0 };
static PadState padState = { 0 };
static u64 padBtnsPressed = 0;
static u64 padBtnsDown = 0;
static u64 padBtnsUp = 0;

// Motion Controls
static bool isSixAxis = false;
static HidSixAxisSensorHandle sixAxisHandles[4] = { 0 };

// Rumble
static HidVibrationDeviceHandle VibrationDeviceHandles[2][2] = { 0 };

// Switch Keyboard
static bool kbdInited = false;
static bool kbdShown = false;
static SwkbdInline kbd = { 0 };
static SwkbdAppearArg kbdAppearArg = { 0 };

static void enter_cb(const char *str, SwkbdDecidedEnterArg *arg) {
    djui_interactable_on_text_input((char *)str);
    djui_interactable_set_input_focus(NULL);
}

static void cancel_cb(void) {
    djui_interactable_set_input_focus(NULL);
}

static void changed_string(const char *str, SwkbdChangedStringArg *arg) {
    djui_interactable_on_text_editing((char *)str, arg->cursorPos);
}

static void moved_cursor(const char *str, SwkbdMovedCursorArg *arg) {
    djui_interactable_on_text_editing((char *)str, arg->cursorPos);
}

static void start_swkb(void) {
    if (kbdInited) { return; }
    
    Result rc = swkbdInlineCreate(&kbd);
    if (!R_SUCCEEDED(rc)) { return; }
    
    rc = swkbdInlineLaunchForLibraryApplet(&kbd, SwkbdInlineMode_AppletDisplay, 0);
    if (!R_SUCCEEDED(rc)) { return; }
    
    swkbdInlineSetDecidedEnterCallback(&kbd, enter_cb);
    swkbdInlineSetDecidedCancelCallback(&kbd, cancel_cb);
    swkbdInlineSetChangedStringCallback(&kbd, changed_string);
    swkbdInlineSetMovedCursorCallback(&kbd, moved_cursor);
    swkbdInlineMakeAppearArg(&kbdAppearArg, SwkbdType_All);
    swkbdInlineAppearArgSetOkButtonText(&kbdAppearArg, "Submit");
    kbdAppearArg.dicFlag = 1;
    kbdAppearArg.returnButtonFlag = 1;
    kbdInited = true;
}

void show_swkb(char *text) {
    if (!kbdInited) { return; }
    
    swkbdInlineSetInputText(&kbd, text);
    swkbdInlineSetCursorPos(&kbd, strlen(text));
    swkbdInlineAppear(&kbd, &kbdAppearArg);
    kbdShown = true;
    
    djui_interactable_on_text_editing("\0", 0);
}

void hide_swkb(void) {
    if (!kbdInited) { return; }

    swkbdInlineDisappear(&kbd);
    kbdShown = false;
}

void poll_swkb(void) {
    if (!kbdInited) { return; }
    swkbdInlineUpdate(&kbd, NULL);
}

static void quit_swkb(void) {
    if (!kbdInited) { return; }
    
    swkbdInlineClose(&kbd);
    kbdInited = false;
}

static void start_six_axis() {
    isSixAxis = true;
    for (int i = 0; i < 4; i++) {
        hidStartSixAxisSensor(sixAxisHandles[i]);
    }
}

static void stop_six_axis() {
    isSixAxis = false;
    for (int i = 0; i < 4; i++) {
        hidStopSixAxisSensor(sixAxisHandles[i]);
    }
}

static s32 gyro_to_stick(float f) {
    s32 tmp = f * -255;
    if (tmp < -80) tmp = -80;
    else if (tmp > 80) tmp = 80;
    return tmp;
}

static void update_button_djui(u8 flag, u64 hid) {
    bool down = padBtnsDown & hid;
    bool up = padBtnsUp & hid;
    bool held = (padBtnsPressed & hid) && (!down && !up);
    
    if (down) {
        djui_interactable_on_button_down(flag);
    }
    if (up) {
        djui_interactable_on_button_up(flag);
    }
    if (held) {
        djui_interactable_on_button_held(flag);
    }
}

static void update_button_game(OSContPad *pad, u32 button, u64 hid) {
    if (padBtnsPressed & hid) {
        pad->button |= button;
    }
}

static void update_button(OSContPad *pad, u32 button, u8 flag, u64 hid) {
    update_button_djui(flag, hid); 
    update_button_game(pad, button, hid);
}

static void update_buttons(OSContPad *pad) {
    update_button_game(pad, START_BUTTON, HidNpadButton_Plus);
    update_button_djui(DJUI_BTN_SELECT, HidNpadButton_Minus);

    update_button_game(pad, B_BUTTON, HidNpadButton_B);
    update_button_game(pad, A_BUTTON, HidNpadButton_A);
    update_button_game(pad, Y_BUTTON, HidNpadButton_Y);
    update_button_game(pad, X_BUTTON, HidNpadButton_X);

    update_button_game(pad, L_TRIG, HidNpadButton_L);
    update_button_game(pad, R_TRIG, HidNpadButton_ZL);
    update_button_game(pad, R_TRIG, HidNpadButton_R);
    update_button_game(pad, Z_TRIG, HidNpadButton_ZR);
    
    update_button_game(pad, U_JPAD, HidNpadButton_Up);
    update_button_game(pad, L_JPAD, HidNpadButton_Left);
    update_button_game(pad, D_JPAD, HidNpadButton_Down);
    update_button_game(pad, R_JPAD, HidNpadButton_Right);
    
    // Bind the C stick to the C buttons.
    update_button(pad, R_CBUTTONS, DJUI_BTN_CRIGHT, HidNpadButton_StickRRight);
    update_button(pad, L_CBUTTONS, DJUI_BTN_CLEFT, HidNpadButton_StickRLeft);
    update_button(pad, U_CBUTTONS, DJUI_BTN_CUP, HidNpadButton_StickRUp);
    update_button(pad, D_CBUTTONS, DJUI_BTN_CDOWN, HidNpadButton_StickRDown);
}

static void update_sticks(OSContPad *pad) {
    s32 leftX  = stickStates[0].x / 409;
    s32 leftY  = stickStates[0].y / 409;
    s32 rightX = stickStates[1].x / 409;
    s32 rightY = stickStates[1].y / 409;
    
    if (isSixAxis && abs(leftX) < 20 && abs(leftY) < 20) {
        HidSixAxisSensorState sixAxis;

        u64 style_set = padGetStyleSet(&padState);
        if (style_set & HidNpadStyleTag_NpadHandheld) {
            hidGetSixAxisSensorStates(sixAxisHandles[0], &sixAxis, 1);
        } else if (style_set & HidNpadStyleTag_NpadFullKey) {
            hidGetSixAxisSensorStates(sixAxisHandles[1], &sixAxis, 1);
        } else if (style_set & HidNpadStyleTag_NpadJoyDual) {
            // For JoyDual, read from either the Left or Right Joy-Con depending on which is/are connected
            u64 attrib = padGetAttributes(&padState);
            if (attrib & HidNpadAttribute_IsRightConnected) {
                hidGetSixAxisSensorStates(sixAxisHandles[3], &sixAxis, 1);
            } else if (attrib & HidNpadAttribute_IsLeftConnected) {
                hidGetSixAxisSensorStates(sixAxisHandles[2], &sixAxis, 1);
            }
        }

        leftX = gyro_to_stick(sixAxis.angular_velocity.y); //Gyroscope Y-Axis (Controller X)
        leftY = gyro_to_stick(sixAxis.angular_velocity.x); //Gyroscope X-Axis (Controller Y)
    }
    
    pad->stick_x = leftX;
    pad->stick_y = leftY;
    pad->ext_stick_x = rightX;
    pad->ext_stick_y = rightY;
}

static void controller_switch_nx_init(void) {
    padConfigureInput(1, HidNpadStyleSet_NpadFullCtrl);
    padInitializeDefault(&padState);

    hidInitializeVibrationDevices(VibrationDeviceHandles[0], 2, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
    hidInitializeVibrationDevices(VibrationDeviceHandles[1], 2, HidNpadIdType_No1, HidNpadStyleTag_NpadJoyDual);
    //Initiating the SixAxis, needs to be done for all options; Obviously no GC Controller.
    hidGetSixAxisSensorHandles(&sixAxisHandles[0], 1, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
    hidGetSixAxisSensorHandles(&sixAxisHandles[1], 1, HidNpadIdType_No1,      HidNpadStyleTag_NpadFullKey);
    hidGetSixAxisSensorHandles(&sixAxisHandles[2], 2, HidNpadIdType_No1,      HidNpadStyleTag_NpadJoyDual);
    
    djui_interactable_set_buttons_only(true);
    start_swkb();
}

static void controller_switch_nx_read(OSContPad *pad) {
    switch (gMarioState->action) {
        case ACT_IN_CANNON:
        case ACT_FIRST_PERSON:
            if (!isSixAxis) start_six_axis();
            break;
        default:
            if (isSixAxis) stop_six_axis();
    }
    
    padUpdate(&padState);
    
    padBtnsPressed = padGetButtons(&padState);
    padBtnsDown = padGetButtonsDown(&padState);
    padBtnsUp = padGetButtonsUp(&padState);
    stickStates[0] = padGetStickPos(&padState, 0);
    stickStates[1] = padGetStickPos(&padState, 1);
    
    update_buttons(pad);
    update_sticks(pad);
    poll_swkb();
}

static u32 controller_switch_nx_rawkey(void)  {
    return VK_INVALID;
}

static void controller_switch_nx_rumble_play(f32 strength, UNUSED f32 length) {
    HidVibrationValue VibrationValues[2];
    HidVibrationValue VibrationValue = {0};

    VibrationValue.freq_high = VibrationValue.freq_low = strength * 1.26f;
    VibrationValue.amp_high = VibrationValue.amp_low = 1.0f;

    memcpy(&VibrationValues[0], &VibrationValue, sizeof(HidVibrationValue));
    memcpy(&VibrationValues[1], &VibrationValue, sizeof(HidVibrationValue));

    padUpdate(&padState);
    u32 target_device = padIsHandheld(&padState) ? 0 : 1;
    hidSendVibrationValues(VibrationDeviceHandles[target_device], VibrationValues, 2);
}

static void controller_switch_nx_rumble_stop(void) {
    HidVibrationValue VibrationValues[2];
    HidVibrationValue VibrationValue_stop = {0};

    VibrationValue_stop.freq_low  = 160.0f;
    VibrationValue_stop.freq_high = 320.0f;

    memcpy(&VibrationValues[0], &VibrationValue_stop, sizeof(HidVibrationValue));
    memcpy(&VibrationValues[1], &VibrationValue_stop, sizeof(HidVibrationValue));

    hidSendVibrationValues(VibrationDeviceHandles[0], VibrationValues, 2);        
    hidSendVibrationValues(VibrationDeviceHandles[1], VibrationValues, 2);
}

static void controller_switch_nx_shutdown(void) {
    djui_interactable_set_buttons_only(false);
    quit_swkb();
}

struct ControllerAPI controller_switch = {
    VK_INVALID,
    controller_switch_nx_init,
    controller_switch_nx_read,
    controller_switch_nx_rawkey,
    controller_switch_nx_rumble_play,
    controller_switch_nx_rumble_stop,
    NULL, // no rebinding
    controller_switch_nx_shutdown
};

#endif
