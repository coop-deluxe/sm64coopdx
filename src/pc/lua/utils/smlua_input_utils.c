#if defined(CAPI_SDL1) || defined(CAPI_SDL2)

#include "types.h"

#include "pc/controller/controller_sdl.h"
#include "pc/controller/controller_keyboard.h"
#include "smlua_input_utils.h"

#include "pc/configfile.h"

struct Gamepad gGamepads[MAX_GAMEPADS];
struct Keyboard gKeyboard[SDL_NUM_SCANCODES];

u32 get_current_gamepad_index(void) {
    return configGamepadNumber;
}

#endif