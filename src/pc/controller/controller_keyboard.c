#include <stdbool.h>
#include <ultra64.h>
#include <time.h>
#include <string.h>
#include "pc/configfile.h"
#include "controller_api.h"

#include "../configfile.h"
#include "controller_keyboard.h"

#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/pc_main.h"
#include "engine/math_util.h"
#include "menu/file_select.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_panel_pause.h"

static int keyboard_buttons_down;

#define MAX_KEYBINDS 64
static int keyboard_mapping[MAX_KEYBINDS][2];
static int num_keybinds = 0;

static u32 keyboard_lastkey = VK_INVALID;

static int keyboard_map_scancode(int scancode) {
    int ret = 0;
    for (int i = 0; i < num_keybinds; i++) {
        if (keyboard_mapping[i][0] == scancode) {
            ret |= keyboard_mapping[i][1];
        }
    }
    return ret;
}

bool keyboard_on_key_down(int scancode) {
    djui_panel_pause_disconnect_key_update(scancode);

    // see if interactable captures this scancode
    if (djui_interactable_on_key_down(scancode)) {
        keyboard_lastkey = scancode;
        return FALSE;
    }

    int mapped = keyboard_map_scancode(scancode);
    keyboard_buttons_down |= mapped;
    keyboard_lastkey = scancode;
    return mapped != 0;
}

bool keyboard_on_key_up(int scancode) {
    djui_interactable_on_key_up(scancode);

    int mapped = keyboard_map_scancode(scancode);
    keyboard_buttons_down &= ~mapped;
    if (keyboard_lastkey == (u32) scancode)
        keyboard_lastkey = VK_INVALID;
    return mapped != 0;
}

void keyboard_on_all_keys_up(void) {
    keyboard_buttons_down = 0;
}

void keyboard_on_text_input(char* text) {
    djui_interactable_on_text_input(text);
}

void keyboard_on_text_editing(char* text, int cursorPos) {
    djui_interactable_on_text_editing(text, cursorPos);
}

static void keyboard_add_binds(int mask, unsigned int *scancode) {
    for (int i = 0; i < MAX_BINDS && num_keybinds < MAX_KEYBINDS; ++i) {
        if (scancode[i] < VK_BASE_KEYBOARD + VK_SIZE) {
            keyboard_mapping[num_keybinds][0] = scancode[i];
            keyboard_mapping[num_keybinds][1] = mask;
            num_keybinds++;
        }
    }
}

static void keyboard_bindkeys(void) {
    bzero(keyboard_mapping, sizeof(keyboard_mapping));
    num_keybinds = 0;

    keyboard_add_binds(STICK_UP,     configKeyStickUp);
    keyboard_add_binds(STICK_LEFT,   configKeyStickLeft);
    keyboard_add_binds(STICK_DOWN,   configKeyStickDown);
    keyboard_add_binds(STICK_RIGHT,  configKeyStickRight);
    keyboard_add_binds(A_BUTTON,     configKeyA);
    keyboard_add_binds(B_BUTTON,     configKeyB);
    keyboard_add_binds(X_BUTTON,     configKeyX);
    keyboard_add_binds(Y_BUTTON,     configKeyY);
    keyboard_add_binds(Z_TRIG,       configKeyZ);
    keyboard_add_binds(U_CBUTTONS,   configKeyCUp);
    keyboard_add_binds(L_CBUTTONS,   configKeyCLeft);
    keyboard_add_binds(D_CBUTTONS,   configKeyCDown);
    keyboard_add_binds(R_CBUTTONS,   configKeyCRight);
    keyboard_add_binds(L_TRIG,       configKeyL);
    keyboard_add_binds(R_TRIG,       configKeyR);
    keyboard_add_binds(START_BUTTON, configKeyStart);
    keyboard_add_binds(U_JPAD,       configKeyDUp);
    keyboard_add_binds(D_JPAD,       configKeyDDown);
    keyboard_add_binds(L_JPAD,       configKeyDLeft);
    keyboard_add_binds(R_JPAD,       configKeyDRight);    
}

static void keyboard_init(void) {
    keyboard_bindkeys();
}

static void keyboard_read(OSContPad *pad) {
    pad->button |= keyboard_buttons_down;
    const u32 xstick = keyboard_buttons_down & STICK_XMASK;
    const u32 ystick = keyboard_buttons_down & STICK_YMASK;
    if (xstick == STICK_LEFT)
        pad->stick_x = -128;
    else if (xstick == STICK_RIGHT)
        pad->stick_x = 127;
    if (ystick == STICK_DOWN)
        pad->stick_y = -128;
    else if (ystick == STICK_UP)
        pad->stick_y = 127;
}

static u32 keyboard_rawkey(void) {
    const u32 ret = keyboard_lastkey;
    keyboard_lastkey = VK_INVALID;
    return ret;
}

static void keyboard_shutdown(void) {
}

struct ControllerAPI controller_keyboard = {
    VK_BASE_KEYBOARD,
    keyboard_init,
    keyboard_read,
    keyboard_rawkey,
    NULL,
    NULL,
    keyboard_bindkeys,
    keyboard_shutdown
};
