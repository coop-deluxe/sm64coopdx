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
    var dirs = ["/save", "/mods", "/config"];
    for (var i = 0; i < dirs.length; i++) {
        try { FS.mkdir(dirs[i]); } catch (e) { /* may exist */ }
        FS.mount(IDBFS, {}, dirs[i]);
    }
    FS.syncfs(true, function(err) {
        if (err) console.error("[Web] IDBFS load failed:", err);
        else console.log("[Web] IDBFS loaded.");
    });
});

void web_fs_init(void) {
    web_mount_idbfs();
    printf("[Web] IDBFS mounts initialized for /save, /mods, /config.\n");
}

#endif /* TARGET_WEB */
