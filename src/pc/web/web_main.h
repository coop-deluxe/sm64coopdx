#ifndef WEB_MAIN_H
#define WEB_MAIN_H

#ifdef TARGET_WEB

/**
 * Called from JavaScript when the ROM has been written to the Emscripten FS.
 */
void web_rom_loaded(void);

/**
 * Returns 1 if the ROM is loaded and available, 0 otherwise.
 */
int web_get_rom_status(void);

/**
 * Triggers FS.syncfs() to persist IDBFS data (saves, config, mods) to IndexedDB.
 */
void web_save_to_idb(void);

/**
 * Initializes IDBFS mounts at /save, /mods, /config and loads persisted data
 * from IndexedDB.
 */
void web_fs_init(void);

#endif /* TARGET_WEB */

#endif /* WEB_MAIN_H */
