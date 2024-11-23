#include <stdio.h>
#ifdef HAVE_SDL2
#include <SDL2/SDL.h>
#else
#ifdef HAVE_SDL

#include <SDL/SDL.h>
#endif
#endif

#include "controller_bind_mapping.h"
#include "controller_api.h"
#include "controller_sdl.h"

#if defined(CAPI_SDL1) || defined(CAPI_SDL2)

static int inverted_scancode_table[512];
static SDL_Scancode bind_to_sdl_scancode[512] = { 0 };

const SDL_Scancode windows_scancode_table[] = {
    /*  0                        1                            2                         3                            4                     5                            6                            7  */
    /*  8                        9                            A                         B                            C                     D                            E                            F  */
    SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_ESCAPE,         SDL_SCANCODE_1,           SDL_SCANCODE_2,              SDL_SCANCODE_3,       SDL_SCANCODE_4,              SDL_SCANCODE_5,              SDL_SCANCODE_6,          /* 0 */
    SDL_SCANCODE_7,              SDL_SCANCODE_8,              SDL_SCANCODE_9,           SDL_SCANCODE_0,              SDL_SCANCODE_MINUS,   SDL_SCANCODE_EQUALS,         SDL_SCANCODE_BACKSPACE,      SDL_SCANCODE_TAB,        /* 0 */

    SDL_SCANCODE_Q,              SDL_SCANCODE_W,              SDL_SCANCODE_E,           SDL_SCANCODE_R,              SDL_SCANCODE_T,       SDL_SCANCODE_Y,              SDL_SCANCODE_U,              SDL_SCANCODE_I,          /* 1 */
    SDL_SCANCODE_O,              SDL_SCANCODE_P,              SDL_SCANCODE_LEFTBRACKET, SDL_SCANCODE_RIGHTBRACKET,   SDL_SCANCODE_RETURN,  SDL_SCANCODE_LCTRL,          SDL_SCANCODE_A,              SDL_SCANCODE_S,          /* 1 */

    SDL_SCANCODE_D,              SDL_SCANCODE_F,              SDL_SCANCODE_G,           SDL_SCANCODE_H,              SDL_SCANCODE_J,       SDL_SCANCODE_K,              SDL_SCANCODE_L,              SDL_SCANCODE_SEMICOLON,  /* 2 */
    SDL_SCANCODE_APOSTROPHE,     SDL_SCANCODE_GRAVE,          SDL_SCANCODE_LSHIFT,      SDL_SCANCODE_BACKSLASH,      SDL_SCANCODE_Z,       SDL_SCANCODE_X,              SDL_SCANCODE_C,              SDL_SCANCODE_V,          /* 2 */

    SDL_SCANCODE_B,              SDL_SCANCODE_N,              SDL_SCANCODE_M,           SDL_SCANCODE_COMMA,          SDL_SCANCODE_PERIOD,  SDL_SCANCODE_SLASH,          SDL_SCANCODE_RSHIFT,         SDL_SCANCODE_PRINTSCREEN,/* 3 */
    SDL_SCANCODE_LALT,           SDL_SCANCODE_SPACE,          SDL_SCANCODE_CAPSLOCK,    SDL_SCANCODE_F1,             SDL_SCANCODE_F2,      SDL_SCANCODE_F3,             SDL_SCANCODE_F4,             SDL_SCANCODE_F5,         /* 3 */

    SDL_SCANCODE_F6,             SDL_SCANCODE_F7,             SDL_SCANCODE_F8,          SDL_SCANCODE_F9,             SDL_SCANCODE_F10,     SDL_SCANCODE_NUMLOCKCLEAR,   SDL_SCANCODE_SCROLLLOCK,     SDL_SCANCODE_HOME,       /* 4 */
    SDL_SCANCODE_UP,             SDL_SCANCODE_PAGEUP,         SDL_SCANCODE_KP_MINUS,    SDL_SCANCODE_LEFT,           SDL_SCANCODE_KP_5,    SDL_SCANCODE_RIGHT,          SDL_SCANCODE_KP_PLUS,        SDL_SCANCODE_END,        /* 4 */

    SDL_SCANCODE_DOWN,           SDL_SCANCODE_PAGEDOWN,       SDL_SCANCODE_INSERT,      SDL_SCANCODE_DELETE,         SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_NONUSBACKSLASH, SDL_SCANCODE_F11,        /* 5 */
    SDL_SCANCODE_F12,            SDL_SCANCODE_PAUSE,          SDL_SCANCODE_UNKNOWN,     SDL_SCANCODE_LGUI,           SDL_SCANCODE_RGUI,    SDL_SCANCODE_APPLICATION,    SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN,    /* 5 */

    SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN,     SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_F13,     SDL_SCANCODE_F14,            SDL_SCANCODE_F15,            SDL_SCANCODE_F16,        /* 6 */
    SDL_SCANCODE_F17,            SDL_SCANCODE_F18,            SDL_SCANCODE_F19,         SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN,    /* 6 */

    SDL_SCANCODE_INTERNATIONAL2, SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN,     SDL_SCANCODE_INTERNATIONAL1, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN,    /* 7 */
    SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_INTERNATIONAL4, SDL_SCANCODE_UNKNOWN,     SDL_SCANCODE_INTERNATIONAL5, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_INTERNATIONAL3, SDL_SCANCODE_UNKNOWN,        SDL_SCANCODE_UNKNOWN     /* 7 */
};

const SDL_Scancode scancode_rmapping_extended[][2] = {
    {SDL_SCANCODE_KP_ENTER, SDL_SCANCODE_RETURN},
    {SDL_SCANCODE_RALT, SDL_SCANCODE_LALT},
    {SDL_SCANCODE_RCTRL, SDL_SCANCODE_LCTRL},
    {SDL_SCANCODE_KP_DIVIDE, SDL_SCANCODE_SLASH},
    //{SDL_SCANCODE_KP_PLUS, SDL_SCANCODE_CAPSLOCK}
};

const SDL_Scancode scancode_rmapping_nonextended[][2] = {
    {SDL_SCANCODE_KP_7, SDL_SCANCODE_HOME},
    {SDL_SCANCODE_KP_8, SDL_SCANCODE_UP},
    {SDL_SCANCODE_KP_9, SDL_SCANCODE_PAGEUP},
    {SDL_SCANCODE_KP_4, SDL_SCANCODE_LEFT},
    {SDL_SCANCODE_KP_6, SDL_SCANCODE_RIGHT},
    {SDL_SCANCODE_KP_1, SDL_SCANCODE_END},
    {SDL_SCANCODE_KP_2, SDL_SCANCODE_DOWN},
    {SDL_SCANCODE_KP_3, SDL_SCANCODE_PAGEDOWN},
    {SDL_SCANCODE_KP_0, SDL_SCANCODE_INSERT},
    {SDL_SCANCODE_KP_PERIOD, SDL_SCANCODE_DELETE},
    {SDL_SCANCODE_KP_MULTIPLY, SDL_SCANCODE_PRINTSCREEN}
};

void controller_bind_init(void) {
    for (size_t i = 0; i < sizeof(windows_scancode_table) / sizeof(SDL_Scancode); i++) {
        inverted_scancode_table[windows_scancode_table[i]] = i;
    }

    for (size_t i = 0; i < sizeof(scancode_rmapping_extended) / sizeof(scancode_rmapping_extended[0]); i++) {
        inverted_scancode_table[scancode_rmapping_extended[i][0]] = inverted_scancode_table[scancode_rmapping_extended[i][1]] + 0x100;
    }

    for (size_t i = 0; i < sizeof(scancode_rmapping_nonextended) / sizeof(scancode_rmapping_nonextended[0]); i++) {
        inverted_scancode_table[scancode_rmapping_nonextended[i][0]] = inverted_scancode_table[scancode_rmapping_nonextended[i][1]];
        inverted_scancode_table[scancode_rmapping_nonextended[i][1]] += 0x100;
    }

    for (size_t i = 0; i < 512; i++) {
        if (inverted_scancode_table[i] >= 512) { continue; }
        bind_to_sdl_scancode[inverted_scancode_table[i]] = i;
    }

}

int translate_sdl_scancode(int scancode) {
    if (scancode < 512) {
        return inverted_scancode_table[scancode];
    }
    else {
        return 0;
    }
}

const char* translate_bind_to_name(int bind) {
    static char name[11] = { 0 };
    sprintf(name, "%04X", bind);

    if (bind == VK_INVALID) { return ""; }

    // mouse
    if (bind >= VK_BASE_SDL_MOUSE) {
        int mouse_button = (bind - VK_BASE_SDL_MOUSE);
        if (mouse_button == 1) { return "L Mouse"; }
        if (mouse_button == 2) { return "M Mouse"; }
        if (mouse_button == 3) { return "R Mouse"; }
        snprintf(name, 8, "Mouse %d", bind - VK_BASE_SDL_MOUSE);
        return name;
    }

    // gamepad
    if (bind >= VK_BASE_SDL_GAMEPAD) {
        int gamepad_button = (bind - VK_BASE_SDL_GAMEPAD);
        switch (gamepad_button) {
            case 0: return "[A]";
            case 1: return "[B]";
            case 2: return "[X]";
            case 3: return "[Y]";
            case 4: return "[Back]";
            case 5: return "[Guide]";
            case 6: return "[Start]";
            case 7: return "[L Stick]";
            case 8: return "[R Stick]";
            case 9: return "[L Bump]";
            case 10: return "[R Bump]";
            case 11: return "[DPAD Up]";
            case 12: return "[DPAD Down]";
            case 13: return "[DPAD Left]";
            case 14: return "[DPAD Right]";
            case 0x1A: return "[L Trig]";
            case 0x1B: return "[R Trig]";
            default: return name;
        }
    }

    // keyboard
    if (bind >= 512) { return name; }

    SDL_Scancode sc = bind_to_sdl_scancode[bind];
    if (sc == 0) { return name; }

#ifdef HAVE_SDL2
    const char* sc_name = SDL_GetScancodeName(sc);
    SDL_Keycode kc = SDL_GetKeyFromScancode(sc);
    if (kc != 0) {
        const char* kc_name = SDL_GetKeyName(kc);
        if ((*kc_name & 0x80) == 0) { sc_name = kc_name; }
    }

    if (*sc_name == '\0') { return name; }
    if (strlen(sc_name) <= 9) { return sc_name; }

    char* space = strchr(sc_name, ' ');
    if (space == NULL) { return sc_name; }

    snprintf(name, 10, "%c%s", sc_name[0], (space + 1));
#endif
    return name;
}
#endif
