#ifdef TARGET_WEB

#include <stdio.h>
#include <string.h>
#include <emscripten.h>
#include <emscripten/html5.h>

#include "web_main.h"

#include <stdbool.h>
#include "pc/network/network.h"
#include "pc/network/network_player.h"
#include "game/level_update.h"
#include "game/level_info.h"
#include "game/area.h"
#include "game/mario.h"

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

// --- Player list and teleport API for web overlay ---

EMSCRIPTEN_KEEPALIVE
int web_get_player_count(void) {
    return MAX_PLAYERS;
}

EMSCRIPTEN_KEEPALIVE
int web_get_player_connected(int index) {
    if (index < 0 || index >= MAX_PLAYERS) return 0;
    return gNetworkPlayers[index].connected ? 1 : 0;
}

EMSCRIPTEN_KEEPALIVE
const char* web_get_player_name(int index) {
    if (index < 0 || index >= MAX_PLAYERS) return "";
    if (!gNetworkPlayers[index].connected) return "";
    return gNetworkPlayers[index].name;
}

EMSCRIPTEN_KEEPALIVE
const char* web_get_player_location(int index) {
    if (index < 0 || index >= MAX_PLAYERS) return "";
    if (!gNetworkPlayers[index].connected) return "";
    struct NetworkPlayer *np = &gNetworkPlayers[index];
    if (np->overrideLocation[0] != '\0') return np->overrideLocation;
    return get_level_name(np->currCourseNum, np->currLevelNum, np->currAreaIndex);
}

EMSCRIPTEN_KEEPALIVE
int web_get_local_player_index(void) {
    if (gNetworkPlayerLocal) return gNetworkPlayerLocal->localIndex;
    return 0;
}

EMSCRIPTEN_KEEPALIVE
int web_is_in_game(void) {
    return (gNetworkType != NT_NONE) ? 1 : 0;
}

EMSCRIPTEN_KEEPALIVE
void web_teleport_to_player(int index) {
    if (index < 0 || index >= MAX_PLAYERS) return;
    struct NetworkPlayer *np = &gNetworkPlayers[index];
    if (!np->connected) return;

    // Don't teleport to self
    if (gNetworkPlayerLocal && np->localIndex == gNetworkPlayerLocal->localIndex) return;

    s16 targetLevel = np->currLevelNum;
    s16 targetArea  = np->currAreaIndex;

    printf("[Web] Teleporting to player %d (%s) at level %d area %d\n",
           index, np->name, targetLevel, targetArea);

    // If same level and area, just move Mario's position
    if (gCurrLevelNum == targetLevel && gCurrAreaIndex == targetArea) {
        struct MarioState *targetMario = &gMarioStates[index];
        gMarioStates[0].pos[0] = targetMario->pos[0];
        gMarioStates[0].pos[1] = targetMario->pos[1];
        gMarioStates[0].pos[2] = targetMario->pos[2];
        printf("[Web] Moved to position (%.0f, %.0f, %.0f)\n",
               targetMario->pos[0], targetMario->pos[1], targetMario->pos[2]);
    } else {
        // Different level — warp there
        // Use warp node 0x0A (default entry) with area index
        initiate_warp(targetLevel, targetArea, 0x0A, 0);
        printf("[Web] Warping to level %d area %d\n", targetLevel, targetArea);
    }
}

#endif /* TARGET_WEB */
