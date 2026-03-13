#ifdef TARGET_WEB

#include <stdio.h>
#include <emscripten.h>
#include <emscripten/html5.h>

#include "web_main.h"

#include <stdbool.h>

// Stubs for excluded modules (update_checker, mumble)
bool gUpdateMessage = false;
void check_for_updates(void) {}
void show_update_popup(void) {}
void mumble_init(void) {}
void mumble_update(void) {}

static int s_rom_loaded = 0;

EMSCRIPTEN_KEEPALIVE
void web_rom_loaded(void) {
    s_rom_loaded = 1;
    printf("[Web] ROM loaded into virtual filesystem.\n");
}

EMSCRIPTEN_KEEPALIVE
int web_get_rom_status(void) {
    return s_rom_loaded;
}

EMSCRIPTEN_KEEPALIVE
void web_save_to_idb(void) {
    emscripten_run_script(
        "try {"
        "  var data = FS.readFile('/sm64coopdx/sm64config.txt', {encoding:'utf8'});"
        "  localStorage.setItem('sm64coopdx_config', data);"
        "  console.log('[Web] Config saved to localStorage (' + data.length + ' bytes)');"
        "} catch(e) {"
        "  console.error('[Web] Failed to save config to localStorage:', e);"
        "}"
    );
}

EMSCRIPTEN_KEEPALIVE
void web_save_savefile(void) {
    emscripten_run_script(
        "try {"
        "  var data = FS.readFile('/sm64coopdx/sm64_save_file.bin');"
        "  var bin = '';"
        "  for (var i = 0; i < data.length; i++) bin += String.fromCharCode(data[i]);"
        "  var b64 = btoa(bin);"
        "  localStorage.setItem('sm64coopdx_save', b64);"
        "  console.log('[Web] Save file persisted to localStorage (' + data.length + ' bytes)');"
        "} catch(e) {"
        "  console.error('[Web] Failed to save save-file to localStorage:', e);"
        "}"
    );
}

// Config is restored from localStorage in shell.html preRun (before main).
void web_fs_init(void) {
    printf("[Web] Config persistence via localStorage.\n");
}

// --- URL parameter auto-join/host ---

// Read a URL search parameter. Returns empty string if not found.
EM_JS(const char*, web_get_url_param, (const char* key), {
    var keyStr = UTF8ToString(key);
    var params = new URLSearchParams(window.location.search);
    var val = params.get(keyStr);
    if (!val) val = "";
    var len = lengthBytesUTF8(val) + 1;
    var buf = _malloc(len);
    stringToUTF8(val, buf, len);
    return buf;
});

int web_check_url_params(void) {
    // Check for ?join=HOST:PORT
    char* joinParam = (char*)web_get_url_param("join");
    if (joinParam && joinParam[0] != '\0') {
        printf("[Web] URL param: join=%s\n", joinParam);
        free(joinParam);
        return 1; // join
    }
    free(joinParam);

    // Check for ?host=PORT
    char* hostParam = (char*)web_get_url_param("host");
    if (hostParam && hostParam[0] != '\0') {
        printf("[Web] URL param: host=%s\n", hostParam);
        free(hostParam);
        return 2; // host
    }
    free(hostParam);

    return 0; // neither
}

// --- Mod management API for web overlay ---

#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"

EMSCRIPTEN_KEEPALIVE
void web_mods_refresh(void) {
    mods_refresh_local();
    mods_update_selectable();
    printf("[Web] Mods refreshed: %d mods found\n", gLocalMods.entryCount);
}

EMSCRIPTEN_KEEPALIVE
int web_mods_get_count(void) {
    return gLocalMods.entryCount;
}

EMSCRIPTEN_KEEPALIVE
const char* web_mods_get_name(int index) {
    if (index < 0 || index >= gLocalMods.entryCount) return "";
    return gLocalMods.entries[index]->name;
}

EMSCRIPTEN_KEEPALIVE
const char* web_mods_get_description(int index) {
    if (index < 0 || index >= gLocalMods.entryCount) return "";
    return gLocalMods.entries[index]->description ? gLocalMods.entries[index]->description : "";
}

EMSCRIPTEN_KEEPALIVE
int web_mods_get_enabled(int index) {
    if (index < 0 || index >= gLocalMods.entryCount) return 0;
    return gLocalMods.entries[index]->enabled ? 1 : 0;
}

EMSCRIPTEN_KEEPALIVE
void web_mods_set_enabled(int index, int enabled) {
    if (index < 0 || index >= gLocalMods.entryCount) return;
    gLocalMods.entries[index]->enabled = enabled ? true : false;
    mods_update_selectable();
}

EMSCRIPTEN_KEEPALIVE
const char* web_mods_get_relative_path(int index) {
    if (index < 0 || index >= gLocalMods.entryCount) return "";
    return gLocalMods.entries[index]->relativePath;
}

#endif /* TARGET_WEB */
