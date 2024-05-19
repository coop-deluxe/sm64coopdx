#include <stdlib.h>
#include "pc/ini.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/os/os.h"
#include "player_palette.h"

const struct PlayerPalette DEFAULT_MARIO_PALETTE =
//  Overalls              Shirt                 Gloves                Shoes                 Hair                  Skin                  Cap                   Emblem
{ { { 0x00, 0x00, 0xff }, { 0xff, 0x00, 0x00 }, { 0xff, 0xff, 0xff }, { 0x72, 0x1c, 0x0e }, { 0x73, 0x06, 0x00 }, { 0xfe, 0xc1, 0x79 }, { 0xff, 0x00, 0x00 }, { 0xff, 0x00, 0x00 } } };

static ini_t* sPalette = NULL;

struct PresetPalette gPresetPalettes[MAX_PRESET_PALETTES] = { 0 };
u16 gPresetPaletteCount = 0;

static bool player_palette_init(const char* palettesPath, char* palette) {
    // free old ini
    if (sPalette != NULL) {
        ini_free(sPalette);
        sPalette = NULL;
    }

    // construct path
    char path[SYS_MAX_PATH] = "";
    if (!palette || palette[0] == '\0') { palette = "Mario"; }
    if (strstr(palettesPath, PALETTES_DIRECTORY)) {
        snprintf(path, SYS_MAX_PATH, "%s/%s.ini", palettesPath, palette);
    } else {
        snprintf(path, SYS_MAX_PATH, "%s/palettes/%s.ini", palettesPath, palette);
    }

    // load
    sPalette = ini_load(path);

    return sPalette != NULL;
}

void player_palettes_reset(void) {
    memset(&gPresetPalettes, 0, sizeof(gPresetPalettes));
    gPresetPaletteCount = 0;
}

static u8 read(const char* data) {
    if (data == NULL) { return 0; }
    for (size_t i = 0; i < strlen(data); i++) {
        char c = data[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || c == 'x')) {
            return 0;
        }
    }
    return strtol(data, NULL, 0);
}

void player_palettes_read(const char* palettesPath) {
    // construct lang path
    char lpath[SYS_MAX_PATH] = "";
    if (strstr(palettesPath, PALETTES_DIRECTORY)) {
        strncpy(lpath, palettesPath, SYS_MAX_PATH);
    } else {
        snprintf(lpath, SYS_MAX_PATH, "%s/palettes", palettesPath);
    }

    // open directory
    os_dirent* dir = NULL;

    OS_DIR* d = os_opendir(lpath);
    if (!d) { return; }

    // iterate
    char path[SYS_MAX_PATH] = { 0 };
    while ((dir = os_readdir(d)) != NULL) {
        // sanity check / fill path[]
        //if (!directory_sanity_check(dir, lpath, path)) { continue; }
        snprintf(path, SYS_MAX_PATH, "%s", os_get_dir_name(dir));

        // strip the name before the .
        char* c = path;
        while (*c != '\0') {
            if (*c == '.') { *c = '\0'; break; }
            c++;
        }
        if (strlen(path) == 0) { continue; }

        if (!player_palette_init(palettesPath, path)) { continue; }

        struct PlayerPalette palette = {{
            { read(ini_get(sPalette, "PALETTE", "PANTS_R")), read(ini_get(sPalette, "PALETTE", "PANTS_G")), read(ini_get(sPalette, "PALETTE", "PANTS_B")) },
            { read(ini_get(sPalette, "PALETTE", "SHIRT_R")), read(ini_get(sPalette, "PALETTE", "SHIRT_G")), read(ini_get(sPalette, "PALETTE", "SHIRT_B")) },
            { read(ini_get(sPalette, "PALETTE", "GLOVES_R")), read(ini_get(sPalette, "PALETTE", "GLOVES_G")), read(ini_get(sPalette, "PALETTE", "GLOVES_B")) },
            { read(ini_get(sPalette, "PALETTE", "SHOES_R")), read(ini_get(sPalette, "PALETTE", "SHOES_G")), read(ini_get(sPalette, "PALETTE", "SHOES_B")) },
            { read(ini_get(sPalette, "PALETTE", "HAIR_R")), read(ini_get(sPalette, "PALETTE", "HAIR_G")), read(ini_get(sPalette, "PALETTE", "HAIR_B")) },
            { read(ini_get(sPalette, "PALETTE", "SKIN_R")), read(ini_get(sPalette, "PALETTE", "SKIN_G")), read(ini_get(sPalette, "PALETTE", "SKIN_B")) },
            { read(ini_get(sPalette, "PALETTE", "CAP_R")), read(ini_get(sPalette, "PALETTE", "CAP_G")), read(ini_get(sPalette, "PALETTE", "CAP_B")) },
            { read(ini_get(sPalette, "PALETTE", "EMBLEM_R")), read(ini_get(sPalette, "PALETTE", "EMBLEM_G")), read(ini_get(sPalette, "PALETTE", "EMBLEM_B")) }
        }};
        // free
        ini_free(sPalette);
        sPalette = NULL;
        strncpy(gPresetPalettes[gPresetPaletteCount].name, path, 4096);
        gPresetPalettes[gPresetPaletteCount].palette = palette;
        gPresetPaletteCount++;
        if (gPresetPaletteCount >= MAX_PRESET_PALETTES) { break; }
    }

    os_closedir(d);
}

void player_palette_export(char* name) {
    // construct lang path
    const char* palettesPath = fs_get_write_path(PALETTES_DIRECTORY);
    char lpath[SYS_MAX_PATH] = "";
    snprintf(lpath, SYS_MAX_PATH, "%s/%s.ini", palettesPath, name);
    fs_sys_mkdir(palettesPath);

    printf("Saving palette as '%s.ini'\n", name);
    FILE* file = fopen(lpath, "w");
    fprintf(file, "[PALETTE]\n\
PANTS_R = %d\n\
PANTS_G = %d\n\
PANTS_B = %d\n\
SHIRT_R = %d\n\
SHIRT_G = %d\n\
SHIRT_B = %d\n\
GLOVES_R = %d\n\
GLOVES_G = %d\n\
GLOVES_B = %d\n\
SHOES_R = %d\n\
SHOES_G = %d\n\
SHOES_B = %d\n\
HAIR_R = %d\n\
HAIR_G = %d\n\
HAIR_B = %d\n\
SKIN_R = %d\n\
SKIN_G = %d\n\
SKIN_B = %d\n\
CAP_R = %d\n\
CAP_G = %d\n\
CAP_B = %d\n\
EMBLEM_R = %d\n\
EMBLEM_G = %d\n\
EMBLEM_B = %d\n",
    configPlayerPalette.parts[PANTS][0],
    configPlayerPalette.parts[PANTS][1],
    configPlayerPalette.parts[PANTS][2],
    configPlayerPalette.parts[SHIRT][0],
    configPlayerPalette.parts[SHIRT][1],
    configPlayerPalette.parts[SHIRT][2],
    configPlayerPalette.parts[GLOVES][0],
    configPlayerPalette.parts[GLOVES][1],
    configPlayerPalette.parts[GLOVES][2],
    configPlayerPalette.parts[SHOES][0],
    configPlayerPalette.parts[SHOES][1],
    configPlayerPalette.parts[SHOES][2],
    configPlayerPalette.parts[HAIR][0],
    configPlayerPalette.parts[HAIR][1],
    configPlayerPalette.parts[HAIR][2],
    configPlayerPalette.parts[SKIN][0],
    configPlayerPalette.parts[SKIN][1],
    configPlayerPalette.parts[SKIN][2],
    configPlayerPalette.parts[CAP][0],
    configPlayerPalette.parts[CAP][1],
    configPlayerPalette.parts[CAP][2],
    configPlayerPalette.parts[EMBLEM][0],
    configPlayerPalette.parts[EMBLEM][1],
    configPlayerPalette.parts[EMBLEM][2]);
    fclose(file);
}

bool player_palette_delete(const char* palettesPath, char* name) {
    // construct lang path
    char lpath[SYS_MAX_PATH] = "";
    if (strstr(palettesPath, PALETTES_DIRECTORY)) {
        snprintf(lpath, SYS_MAX_PATH, "%s/%s.ini", palettesPath, name);
    } else {
        snprintf(lpath, SYS_MAX_PATH, "%s/palettes/%s.ini", palettesPath, name);
    }

    if (remove(lpath) == 0) {
        printf("Deleting palette '%s.ini'\n", name);
        return true;
    }
    return false;
}
