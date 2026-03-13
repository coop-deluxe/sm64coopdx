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
 * Persists config to localStorage.
 */
void web_save_to_idb(void);

/**
 * Persists save file (sm64_save_file.bin) to localStorage.
 */
void web_save_savefile(void);

/**
 * Initializes IDBFS mounts at /save, /mods, /config and loads persisted data
 * from IndexedDB.
 */
void web_fs_init(void);

/**
 * Check URL parameters for auto-join/host:
 *   ?join=HOST:PORT  - auto-join a server
 *   ?host=PORT       - auto-host on a port
 * Returns: 1 if auto-join was initiated, 2 if auto-host, 0 if neither.
 */
int web_check_url_params(void);

/**
 * Player list API for web overlay.
 */
int web_get_player_count(void);
int web_get_player_connected(int index);
const char* web_get_player_name(int index);
const char* web_get_player_location(int index);
int web_get_local_player_index(void);
int web_is_in_game(void);
void web_teleport_to_player(int index);

#endif /* TARGET_WEB */

#endif /* WEB_MAIN_H */
