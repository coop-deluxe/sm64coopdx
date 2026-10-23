#include "smlua_input_utils.h"
#include "engine/math_util.h"
#include "pc/configfile.h"
#include "pc/pc_main.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/debuglog.h"

bool gModHasInputFocus = false;

struct Gamepad gGamepads[MAX_GAMEPADS];
struct Key gKeyboard[SDL_SCANCODE_COUNT];

u32 smlua_input_util_get_current_gamepad(void) {
    s32 joystickCount = 0;
    SDL_JoystickID *joysticks = SDL_GetJoysticks(&joystickCount);
    if (!joystickCount) {
        SDL_free(joysticks);
        return MAX_GAMEPADS;
    }

    bool isGamepad = SDL_IsGamepad(joysticks[configGamepadNumber]);
    u32 index = MAX_GAMEPADS;
    if (isGamepad) {
        SDL_Gamepad *sdlGamepad = SDL_OpenGamepad(joysticks[configGamepadNumber]);
        for (s32 i = 0; i < MAX_GAMEPADS; i++) {
            if (sdlGamepad == gGamepads[i].pad) {
                index = gGamepads[i].index;
            }
        }
    }
    SDL_free(joysticks);
    return index;
}

void smlua_input_util_start_text_input(void) {
    gModHasInputFocus = true;
    gfx_wm_start_text_input();
}

void smlua_input_util_stop_text_input(void) {
    gModHasInputFocus = false;
}

bool smlua_input_util_text_input_active(void) {
    return gfx_wm_text_input_active() && gModHasInputFocus;
}

void smlua_input_util_clear(void) {
    for (s32 i = 0; i < MAX_GAMEPADS; ++i) {
        free((void *)gGamepads[i].name);
    }
    memset(gGamepads, 0, sizeof(gGamepads));
}

void smlua_input_util_controller_maps_load(const char *mapsPath, bool appendMaps) {
    // construct databases path
    char dbpath[SYS_MAX_PATH] = "";
    if (appendMaps) {
        snprintf(dbpath, SYS_MAX_PATH, "%s/databases", mapsPath);
    } else {
        snprintf(dbpath, SYS_MAX_PATH, "%s", mapsPath);
    }

    // open directory
    struct dirent *dir = NULL;

    DIR *d = opendir(dbpath);
    if (!d) { return; }

    // iterate
    char path[SYS_MAX_PATH] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        // sanity check / fill path[]
        if (!directory_sanity_check(dir, dbpath, path)) { continue; }
        snprintf(path, SYS_MAX_PATH, "%s", dir->d_name);

        // ensure the name of the path isn't nothing
        if (path[0] == 0) { continue; }

        // only allow files ending with `.db`
        if (!path_ends_with(path, ".db")) { continue; }

        // get the fullpath
        char fullpath[SYS_MAX_PATH] = "";
        snprintf(fullpath, SYS_MAX_PATH, "%s/%s", dbpath, path);

        // load map
        int loadedMaps = SDL_AddGamepadMappingsFromFile(fullpath);

        if (loadedMaps >= 0) {
            LOG_INFO("smlua_input_util_controller_maps_load: Loaded %d controller mapping(s) from '%s'\n", loadedMaps, path);
        } else {
            LOG_ERROR("smlua_input_util_controller_maps_load: Failed to load controller map from '%s'\n", path);
        }
    }

    closedir(d);
}
