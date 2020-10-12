#include <stdbool.h>
#include <ultra64.h>
#include <time.h>
#include <string.h>
#include "pc/configfile.h"
#include "controller_api.h"

#ifdef TARGET_WEB
#include "controller_emscripten_keyboard.h"
#endif

#include "../configfile.h"
#include "controller_keyboard.h"
#include "controller_keyboard_debug.h"

#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/pc_main.h"
#include "engine/math_util.h"
#include "menu/file_select.h"
#include "game/chat.h"

// TODO: use some common lookup header
#define SCANCODE_BACKSPACE 0x0E
#define SCANCODE_ESCAPE    0x01
#define SCANCODE_ENTER     0x1C
#define SCANCODE_V         0x2F
#define SCANCODE_INSERT    0x152
#define SCANCODE_CTRL1     0x1D
#define SCANCODE_CTRL2     0x11D
#define SCANCODE_SHIFT1    0x2A
#define SCANCODE_SHIFT2    0x36
#define SCANCODE_ALT1      0x38
#define SCANCODE_ALT2      0x138

static int keyboard_buttons_down;

#define MAX_KEYBINDS 64
static int keyboard_mapping[MAX_KEYBINDS][2];
static int num_keybinds = 0;

static u32 keyboard_lastkey = VK_INVALID;

char gTextInput[MAX_TEXT_INPUT];
static u8 sInTextInput = false;
static u8 sMaxTextInput = 0;
static clock_t sIgnoreTextInput = 0;

u8 held_ctrl, held_shift, held_alt;
static enum TextInputMode sTextInputMode;
void (*textInputOnEscape)(void) = NULL;
void (*textInputOnEnter)(void) = NULL;

static int keyboard_map_scancode(int scancode) {
    int ret = 0;
    for (int i = 0; i < num_keybinds; i++) {
        if (keyboard_mapping[i][0] == scancode) {
            ret |= keyboard_mapping[i][1];
        }
    }
    return ret;
}

static void keyboard_alter_modifier(int scancode, bool down) {
    if (down) {
        switch (scancode) {
            case SCANCODE_CTRL1:  held_ctrl  |= (1 << 0); break;
            case SCANCODE_CTRL2:  held_ctrl  |= (1 << 1); break;
            case SCANCODE_SHIFT1: held_shift |= (1 << 0); break;
            case SCANCODE_SHIFT2: held_shift |= (1 << 1); break;
            case SCANCODE_ALT1:   held_alt   |= (1 << 0); break;
            case SCANCODE_ALT2:   held_alt   |= (1 << 1); break;
        }
    } else {
        switch (scancode) {
            case SCANCODE_CTRL1:  held_ctrl  &= ~(1 << 0); break;
            case SCANCODE_CTRL2:  held_ctrl  &= ~(1 << 1); break;
            case SCANCODE_SHIFT1: held_shift &= ~(1 << 0); break;
            case SCANCODE_SHIFT2: held_shift &= ~(1 << 1); break;
            case SCANCODE_ALT1:   held_alt   &= ~(1 << 0); break;
            case SCANCODE_ALT2:   held_alt   &= ~(1 << 1); break;
        }
    }
}

bool keyboard_on_key_down(int scancode) {
    // alter the held value of modifier keys
    keyboard_alter_modifier(scancode, true);

#ifdef DEBUG
    if (!sInTextInput) {
        debug_keyboard_on_key_down(scancode);
    }
#endif
    if (sInTextInput) {
        // perform text-input-specific actions
        switch (scancode & 0xFF) {
            case SCANCODE_BACKSPACE:
                gTextInput[max(strlen(gTextInput) - 1, 0)] = '\0';
                break;
            case SCANCODE_ESCAPE:
                if (textInputOnEscape != NULL) { textInputOnEscape(); }
                break;
            case SCANCODE_ENTER:
                if (textInputOnEnter != NULL) { textInputOnEnter(); }
                break;
            case SCANCODE_V:
                if (held_ctrl) { keyboard_on_text_input(wm_api->get_clipboard_text()); }
                break;
            case SCANCODE_INSERT:
                if (held_shift) { keyboard_on_text_input(wm_api->get_clipboard_text()); }
                break;
        }

        // ignore any normal key down event if we're in text-input mode
        return FALSE;
    }

    if (!held_alt && (scancode == (int)configKeyChat[0])) {
        if (sSelectedFileNum != 0) {
            sIgnoreTextInput = clock() + CLOCKS_PER_SEC * 0.01f;
            chat_start_input();
        }
    }

    int mapped = keyboard_map_scancode(scancode);
    keyboard_buttons_down |= mapped;
    keyboard_lastkey = scancode;
    return mapped != 0;
}

bool keyboard_on_key_up(int scancode) {
    // alter the held value of modifier keys
    keyboard_alter_modifier(scancode, false);

    if (sInTextInput) {
        // ignore any key up event if we're in text-input mode
        return FALSE;
    }

    int mapped = keyboard_map_scancode(scancode);
    keyboard_buttons_down &= ~mapped;
    if (keyboard_lastkey == (u32) scancode)
        keyboard_lastkey = VK_INVALID;
    return mapped != 0;
}

void keyboard_on_all_keys_up(void) {
    keyboard_buttons_down = 0;
}

char* keyboard_start_text_input(enum TextInputMode inInputMode, u8 inMaxTextInput, void (*onEscape)(void), void (*onEnter)(void)) {
    // set text-input events
    textInputOnEscape = onEscape;
    textInputOnEnter = onEnter;
    sMaxTextInput = inMaxTextInput;

    // clear buffer
    for (int i = 0; i < MAX_TEXT_INPUT; i++) { gTextInput[i] = '\0'; }

    // clear held-value for modifiers
    held_ctrl = 0;
    held_shift = 0;
    held_alt = 0;

    // start allowing text input
    wm_api->start_text_input();
    sTextInputMode = inInputMode;
    sInTextInput = true;
}

void keyboard_stop_text_input(void) {
    // stop allowing text input
    sInTextInput = false;
    wm_api->stop_text_input();
}

bool keyboard_in_text_input(void) { return sInTextInput; }

static bool keyboard_allow_character_input(char c) {
    switch (sTextInputMode) {
        case TIM_IP:
            // IP only allows numbers, periods, and spaces
            return (c >= '0' && c <= '9')
                || (c == '.')
                || (c == ' ');

        case TIM_MULTI_LINE:
            // multi-line allows new-line character
            if (c == '\n') { return true; }
            // intentional fall-through

        case TIM_SINGLE_LINE:
            // allow all characters that we can display in-game
            return (c >= '0' && c <= '9')
                || (c >= 'a' && c <= 'z')
                || (c >= 'A' && c <= 'Z')
                || (c == '\'') || (c == '.')
                || (c == ',') || (c == '-')
                || (c == '(') || (c == ')')
                || (c == '&') || (c == '!')
                || (c == '%') || (c == '?')
                || (c == '"') || (c == '~')
                || (c == '*') || (c == ' ');
    }

    return false;
}

void keyboard_on_text_input(char* text) {
    if (sIgnoreTextInput != 0 && clock() <= sIgnoreTextInput) {
        sIgnoreTextInput = 0;
        return;
    }

    if (!sInTextInput) { return; }
    // sanity check input
    if (text == NULL) { return; }

    int i = strlen(gTextInput);
    while (*text != '\0') {
        // make sure we don't overrun the buffer
        if (i >= MAX_TEXT_INPUT) { break; }
        if (i >= sMaxTextInput)   { break; }

        // copy over character if we're allowed to input it
        if (keyboard_allow_character_input(*text)) {
            gTextInput[i++] = *text;
        }

        text++;
    }
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
    keyboard_add_binds(Z_TRIG,       configKeyZ);
    keyboard_add_binds(U_CBUTTONS,   configKeyCUp);
    keyboard_add_binds(L_CBUTTONS,   configKeyCLeft);
    keyboard_add_binds(D_CBUTTONS,   configKeyCDown);
    keyboard_add_binds(R_CBUTTONS,   configKeyCRight);
    keyboard_add_binds(L_TRIG,       configKeyL);
    keyboard_add_binds(R_TRIG,       configKeyR);
    keyboard_add_binds(START_BUTTON, configKeyStart);
}

static void keyboard_init(void) {
    keyboard_bindkeys();

#ifdef TARGET_WEB
    controller_emscripten_keyboard_init();
#endif
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
