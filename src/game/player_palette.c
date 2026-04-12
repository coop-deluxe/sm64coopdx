#include <stdlib.h>
#include <ctype.h>
#include "pc/ini.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "player_palette.h"
#include "pc/lua/smlua.h"

const struct PlayerPalette DEFAULT_MARIO_PALETTE =
//  Overalls              Shirt                 Gloves                Shoes                 Hair                  Skin                  Cap                   Emblem
{ { { 0x00, 0x00, 0xff }, { 0xff, 0x00, 0x00 }, { 0xff, 0xff, 0xff }, { 0x72, 0x1c, 0x0e }, { 0x73, 0x06, 0x00 }, { 0xfe, 0xc1, 0x79 }, { 0xff, 0x00, 0x00 }, { 0xff, 0x00, 0x00 } } };

static ini_t* sPalette = NULL;

struct PresetPalette gPresetPalettes[MAX_PRESET_PALETTES] = { 0 };
u16 gPresetPaletteCount = 0;
struct PresetPalette gModdedPresetPalettes[MAX_MODDED_PRESET_PALETTES] = { 0 };

static bool player_palette_init(const char* palettesPath, char* palette, bool appendPalettes) {
    // free old ini
    if (sPalette != NULL) {
        ini_free(sPalette);
        sPalette = NULL;
    }

    // construct path
    char path[SYS_MAX_PATH] = "";
    if (!palette || palette[0] == '\0') { palette = "Mario"; }
    if (appendPalettes) {
        snprintf(path, SYS_MAX_PATH, "%s/palettes/%s.ini", palettesPath, palette);
    } else {
        snprintf(path, SYS_MAX_PATH, "%s/%s.ini", palettesPath, palette);
    }

    // load
    sPalette = ini_load(path);

    return sPalette != NULL;
}

void player_palettes_reset(void) {
    memset(&gPresetPalettes, 0, sizeof(gPresetPalettes));
    gPresetPaletteCount = 0;
}

void player_modded_palettes_reset(void) {
    memset(&gModdedPresetPalettes, 0, sizeof(gModdedPresetPalettes));
}

static u8 read_value(const char* data) {
    if (data == NULL) { return 0; }
    data = sys_strlwr((char*)data);
    for (size_t i = 0; i < strlen(data); i++) {
        char c = data[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || c == 'x')) {
            return 0;
        }
    }
    return MIN(strtol(data, NULL, 0), 255);
}

static void player_palettes_sort_characters(void) {
    struct PresetPalette charPresetPalettes[MAX_PRESET_PALETTES] = { 0 };
    int charPresetPaletteCount = 0;

    // copy character palettes first
    for (int c = 0; c < CT_COUNT; c++) { // heh, c++
        for (int i = 0; i < gPresetPaletteCount; i++) {
            if (!strcmp(gPresetPalettes[i].name, gOriginalCharacters[c].name)) {
                charPresetPalettes[charPresetPaletteCount++] = gPresetPalettes[i];
            }
        }
    }

    // copy modded palettes
    for (int i = 0; i < MAX_MODDED_PRESET_PALETTES; i++) {
        bool isCharPalette = false;
        for (int c = 0; c < CT_COUNT; c++) { // heh, c++
            if (!strcmp(gModdedPresetPalettes[i].name, gOriginalCharacters[c].name)) {
                isCharPalette = true;
                break;
            }
        }
        if (!isCharPalette && gModdedPresetPalettes[i].active) {
            charPresetPalettes[charPresetPaletteCount++] = gModdedPresetPalettes[i];
        }
    }

    // copy remaining palettes
    for (int i = 0; i < gPresetPaletteCount; i++) {
        bool isCharPalette = false;
        for (int c = 0; c < CT_COUNT; c++) { // heh, c++
            if (!strcmp(gPresetPalettes[i].name, gOriginalCharacters[c].name)) {
                isCharPalette = true;
                break;
            }
        }
        if (!isCharPalette) {
            if (charPresetPaletteCount >= MAX_PRESET_PALETTES) break;
            charPresetPalettes[charPresetPaletteCount++] = gPresetPalettes[i];
        }
    }

    // finally, write to gPresetPalettes
    for (int i = 0; i < charPresetPaletteCount; i++) {
        gPresetPalettes[i] = charPresetPalettes[i];
    }
    gPresetPaletteCount = charPresetPaletteCount;
}

void player_palettes_read(const char* palettesPath, bool appendPalettes) {
    // construct palette path
    char ppath[SYS_MAX_PATH] = "";
    if (appendPalettes) {
        snprintf(ppath, SYS_MAX_PATH, "%s/palettes", palettesPath);
    } else {
        snprintf(ppath, SYS_MAX_PATH, "%s", palettesPath);
    }

    // open directory
    struct dirent* dir = NULL;

    DIR* d = opendir(ppath);
    if (!d) { return; }

    // iterate
    char path[SYS_MAX_PATH] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        // sanity check / fill path[]
        if (!directory_sanity_check(dir, ppath, path)) { continue; }
        snprintf(path, SYS_MAX_PATH, "%s", dir->d_name);

        // strip the name before the .
        char* c = path;
        while (*c != '\0') {
            if (*c == '.') { *c = '\0'; break; }
            c++;
        }
        if (strlen(path) == 0) { continue; }

        if (!player_palette_init(palettesPath, path, appendPalettes)) {
#ifdef DEVELOPMENT
            printf("Failed to load palette '%s.ini'\n", path);
#endif
            continue;
        }

        struct PlayerPalette palette = {{
            { read_value(ini_get(sPalette, "PALETTE", "PANTS_R")), read_value(ini_get(sPalette, "PALETTE", "PANTS_G")), read_value(ini_get(sPalette, "PALETTE", "PANTS_B")) },
            { read_value(ini_get(sPalette, "PALETTE", "SHIRT_R")), read_value(ini_get(sPalette, "PALETTE", "SHIRT_G")), read_value(ini_get(sPalette, "PALETTE", "SHIRT_B")) },
            { read_value(ini_get(sPalette, "PALETTE", "GLOVES_R")), read_value(ini_get(sPalette, "PALETTE", "GLOVES_G")), read_value(ini_get(sPalette, "PALETTE", "GLOVES_B")) },
            { read_value(ini_get(sPalette, "PALETTE", "SHOES_R")), read_value(ini_get(sPalette, "PALETTE", "SHOES_G")), read_value(ini_get(sPalette, "PALETTE", "SHOES_B")) },
            { read_value(ini_get(sPalette, "PALETTE", "HAIR_R")), read_value(ini_get(sPalette, "PALETTE", "HAIR_G")), read_value(ini_get(sPalette, "PALETTE", "HAIR_B")) },
            { read_value(ini_get(sPalette, "PALETTE", "SKIN_R")), read_value(ini_get(sPalette, "PALETTE", "SKIN_G")), read_value(ini_get(sPalette, "PALETTE", "SKIN_B")) },
            { read_value(ini_get(sPalette, "PALETTE", "CAP_R")), read_value(ini_get(sPalette, "PALETTE", "CAP_G")), read_value(ini_get(sPalette, "PALETTE", "CAP_B")) },
            { read_value(ini_get(sPalette, "PALETTE", "EMBLEM_R")), read_value(ini_get(sPalette, "PALETTE", "EMBLEM_G")), read_value(ini_get(sPalette, "PALETTE", "EMBLEM_B")) }
        }};
        // free
        ini_free(sPalette);
        sPalette = NULL;
        snprintf(gPresetPalettes[gPresetPaletteCount].name, 64, "%s", path);
        gPresetPalettes[gPresetPaletteCount].palette = palette;
        gPresetPaletteCount++;
#ifdef DEVELOPMENT
        printf("Loaded palette '%s.ini'\n", path);
#endif
        if (gPresetPaletteCount >= MAX_NORMAL_PRESET_PALETTES) { break; }
    }

    closedir(d);

    // this should mean we are in the exe path's palette dir
    if (appendPalettes) {
        player_palettes_sort_characters();
    }
}

void player_palette_export(char* name) {
    // construct palette path
    const char* palettesPath = fs_get_write_path(PALETTES_DIRECTORY);
    char ppath[SYS_MAX_PATH] = "";
    snprintf(ppath, SYS_MAX_PATH, "%s/%s.ini", palettesPath, name);
    fs_sys_mkdir(palettesPath);

    printf("Saving palette as '%s.ini'\n", name);
    FILE* file = fopen(ppath, "w");
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

bool player_palette_delete(const char* palettesPath, char* name, bool appendPalettes) {
    // construct palette path
    char ppath[SYS_MAX_PATH] = "";
    if (appendPalettes) {
        snprintf(ppath, SYS_MAX_PATH, "%s/palettes/%s.ini", palettesPath, name);
    } else {
        snprintf(ppath, SYS_MAX_PATH, "%s/%s.ini", palettesPath, name);
    }

    if (remove(ppath) == 0) {
        printf("Deleting palette '%s.ini'\n", name);
        return true;
    }
    return false;
}

static struct PresetPalette* modded_preset_palette_get_first_inactive() {
    for (int i = 0; i < MAX_MODDED_PRESET_PALETTES; i++) {
        if (!gModdedPresetPalettes[i].active) {
            return &gModdedPresetPalettes[i];
        }
    }
    return NULL;
}

struct PresetPalette* preset_palette_allocate(const char* name) {
    // -6 to allow for (Mod) text appended to name
    if (strlen(name) >= MAX_PALETTE_NAME - 6) {
        LOG_LUA_LINE("preset_palette_allocate: Failed to allocate palette, name %s is too large! Name can only be %u characters", name, MAX_PALETTE_NAME - 7);
        return NULL;
    }
    struct PresetPalette* palette = modded_preset_palette_get_first_inactive();
    if (palette == NULL) {
        LOG_LUA_LINE("preset_palette_allocate: Ran out of slots to get new palette!");
        return NULL;
    }
    snprintf(palette->name, sizeof(palette->name), "%s (Mod)", name);
    palette->active = true;
    return palette;
}

void preset_palette_set_name(struct PresetPalette* palette, const char* name) {
    // -6 to allow for (Mod) text appended to name
    if (strlen(name) >= MAX_PALETTE_NAME - 6) {
        LOG_LUA_LINE("preset_palette_set_name: Failed to set name, name %s is too large! Name can only be %u characters", name, MAX_PALETTE_NAME - 7);
        return;
    }
    if (palette == NULL) { return; }
    snprintf(palette->name, sizeof(palette->name), "%s (Mod)", name);;
}

void preset_palette_set_color_of_part(struct PresetPalette* palette, u8 playerPart, u8 r, u8 g, u8 b) {
    if (palette == NULL) { return; }
    if (playerPart < 0 || playerPart >= PLAYER_PART_MAX) { return; }
    palette->palette.parts[playerPart][0] = r;
    palette->palette.parts[playerPart][1] = g;
    palette->palette.parts[playerPart][2] = b;
}