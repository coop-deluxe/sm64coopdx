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
        "if (typeof FS !== 'undefined' && FS.syncfs) {"
        "  FS.syncfs(false, function(err) {"
        "    if (err) console.error('[Web] FS.syncfs save failed:', err);"
        "    else console.log('[Web] FS.syncfs save complete.');"
        "  });"
        "}"
    );
}

EM_JS(void, web_mount_idbfs, (), {
    var dir = "/sm64coopdx";
    try { FS.mkdir(dir); } catch (e) { /* may exist */ }
    FS.mount(IDBFS, {}, dir);
    // Synchronously wait for IndexedDB data to load using Asyncify
    return Asyncify.handleSleep(function(wakeUp) {
        FS.syncfs(true, function(err) {
            if (err) console.error("[Web] IDBFS load failed:", err);
            else console.log("[Web] IDBFS loaded from IndexedDB.");
            wakeUp();
        });
    });
});

void web_fs_init(void) {
    web_mount_idbfs();
    printf("[Web] IDBFS mount on /sm64coopdx initialized.\n");
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

#endif /* TARGET_WEB */
