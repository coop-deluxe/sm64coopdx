#if defined(CAPI_SDL1) || defined(CAPI_SDL2)

#include "smlua_input_utils.h"

#include "engine/math_util.h"

#include "pc/configfile.h"
#include "pc/pc_main.h"

#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"

struct Gamepad gGamepads[MAX_GAMEPADS];
struct Key gKeyboard[SDL_NUM_SCANCODES];

u32 get_current_gamepad_index(void) {
    return configGamepadNumber;
}

const char* get_clipboard_text(void) {
    return wm_api->get_clipboard_text();
}

void set_clipboard_text(const char* text) {
    wm_api->set_clipboard_text(text);
}

void clear_gamepad_input_data(void) {
    for (int i = 0; i < MAX_GAMEPADS; ++i) {
        for (int j = 0; j < SDL_CONTROLLER_BUTTON_MAX; ++j) {
            gGamepads[i].buttons[j] = false;
        }
        vec2s_set(gGamepads[i].leftStick, 0, 0);
        vec2s_set(gGamepads[i].rightStick, 0, 0);
        gGamepads[i].leftTrigger = 0;
        gGamepads[i].rightTrigger = 0;
        vec3f_set(gGamepads[i].accelerometer, 0.0f, 0.0f, 0.0f);
        vec3f_set(gGamepads[i].gyro, 0.0f, 0.0f, 0.0f);
        vec3f_set(gGamepads[i].leftAccelerometer, 0.0f, 0.0f, 0.0f);
        vec3f_set(gGamepads[i].leftGyro, 0.0f, 0.0f, 0.0f);
        vec3f_set(gGamepads[i].rightAccelerometer, 0.0f, 0.0f, 0.0f);
        vec3f_set(gGamepads[i].rightGyro, 0.0f, 0.0f, 0.0f);
        gGamepads[i].rumbleLowFreq = 0;
        gGamepads[i].rumbleHighFreq = 0;
        gGamepads[i].rumbleDurationMs = 0;
        for (int j = 0; j < MAX_TOUCHPAD_FINGERS; ++j) {
            vec2f_set(gGamepads[i].touchpad[j].pos, 0.0f, 0.0f);
            gGamepads[i].touchpad[j].pressure = 0.0f;
            gGamepads[i].touchpad[j].touched = false;
        }
        gGamepads[i].ledColor[0] = 0x0;
        gGamepads[i].ledColor[1] = 0x0;
        gGamepads[i].ledColor[2] = 0x0;
    }
}

void controller_maps_load(const char* mapsPath, bool appendMaps) {
    // construct databases path
    char dbpath[SYS_MAX_PATH] = "";
    if (appendMaps) {
        snprintf(dbpath, SYS_MAX_PATH, "%s/databases", mapsPath);
    } else {
        snprintf(dbpath, SYS_MAX_PATH, "%s", mapsPath);
    }

    // open directory
    struct dirent* dir = NULL;

    DIR* d = opendir(dbpath);
    if (!d) { return; }

    // iterate
    char path[SYS_MAX_PATH] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        // sanity check / fill path[]
        if (!directory_sanity_check(dir, dbpath, path)) { continue; }

        snprintf(path, SYS_MAX_PATH, "%s", dir->d_name);

        // strip the name before the .
        char* c = path;
        while (*c != '\0') {
            if (*c == '.') { *c = '\0'; break; }
            c++;
        }
        if (strlen(path) == 0) { continue; }

        // get the fullpath
        char fullpath[SYS_MAX_PATH] = "";
        snprintf(fullpath, SYS_MAX_PATH, "%s/%s.db", dbpath, path);

        // open file
        FILE* f = fopen(fullpath, "rb");
        if (!f) {
#ifdef DEVELOPMENT
            printf("Failed to load controller map '%s.db'\n", path);
#endif
            continue;
        }

        // get file size
        fseek(f, 0, SEEK_END);
        int64_t size = ftell(f);
        fseek(f, 0, SEEK_SET);

        if (size <= 0) {
#ifdef DEVELOPMENT
            printf("Controller map empty or invalid: '%s.db'\n", path);
#endif
            fclose(f);
            continue;
        }

        void* data = malloc(size);
        if (!data) {
            fclose(f);
            continue;
        }

        if (fread(data, 1, size, f) != (size_t)size) {
            free(data);
            fclose(f);
            continue;
        }

        fclose(f);

        // SDL_RWFromConstMem uses int size
        if (size > INT_MAX) {
#ifdef DEVELOPMENT
            printf("Controller map too large: '%s.db'\n", path);
#endif
            free(data);
            continue;
        }

        SDL_RWops* rw = SDL_RWFromConstMem(data, (int)size);
        if (!rw) {
#ifdef DEVELOPMENT
            printf("SDL_RWFromConstMem failed for '%s.db'\n", path);
#endif
            free(data);
            continue;
        }

        // Load into SDL
        int loadedMaps = SDL_GameControllerAddMappingsFromRW(rw, SDL_FALSE);

        SDL_RWclose(rw);
        free(data);

        if (loadedMaps >= 0) {
#ifdef DEVELOPMENT
            printf("Controller Database: Loaded %d controller mapping(s) from '%s.db'\n", loadedMaps, path);
        } else {
            printf("Controller Database: Failed to load controller map from '%s.db'\n", path);
#endif
        }
    }

    closedir(d);
}

#endif