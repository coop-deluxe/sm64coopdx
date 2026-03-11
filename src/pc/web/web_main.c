#ifdef TARGET_WEB

#include <stdio.h>
#include <emscripten.h>
#include <emscripten/html5.h>

#include "web_main.h"

static int s_rom_loaded = 0;

/**
 * Called from JavaScript when the ROM has been written to the Emscripten FS.
 * Sets the internal flag so the engine knows the ROM is available.
 */
EMSCRIPTEN_KEEPALIVE
void web_rom_loaded(void) {
    s_rom_loaded = 1;
    printf("[Web] ROM loaded into virtual filesystem.\n");
}

/**
 * Returns whether the ROM file has been loaded and is available in the FS.
 * Can be polled from C or called from JS.
 */
EMSCRIPTEN_KEEPALIVE
int web_get_rom_status(void) {
    return s_rom_loaded;
}

/**
 * Triggers FS.syncfs() to persist IDBFS-backed directories to IndexedDB.
 * Call this after writing save files, config, etc.
 */
EMSCRIPTEN_KEEPALIVE
void web_save_to_idb(void) {
    EM_ASM({
        if (typeof FS !== 'undefined' && FS.syncfs) {
            FS.syncfs(false, function(err) {
                if (err) {
                    console.error('[Web] FS.syncfs save failed:', err);
                } else {
                    console.log('[Web] FS.syncfs save complete.');
                }
            });
        }
    });
}

/**
 * Initializes IDBFS mounts for persistent storage directories.
 * Creates /save, /mods, and /config, mounts them with IDBFS,
 * then calls FS.syncfs(true, ...) to populate them from IndexedDB.
 */
void web_fs_init(void) {
    EM_ASM({
        var dirs = ['/save', '/mods', '/config'];
        for (var i = 0; i < dirs.length; i++) {
            try {
                FS.mkdir(dirs[i]);
            } catch (e) {
                // Directory may already exist
            }
            FS.mount(IDBFS, {}, dirs[i]);
        }

        // Populate from IndexedDB (true = load from persistent source)
        FS.syncfs(true, function(err) {
            if (err) {
                console.error('[Web] FS.syncfs initial load failed:', err);
            } else {
                console.log('[Web] FS.syncfs initial load complete. Persistent data restored.');
            }
        });
    });

    printf("[Web] IDBFS mounts initialized for /save, /mods, /config.\n");
}

#endif /* TARGET_WEB */
