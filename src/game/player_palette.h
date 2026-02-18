#ifndef PLAYER_PALETTE_H
#define PLAYER_PALETTE_H

#include "types.h"

#define PALETTES_DIRECTORY "palettes"
#define MAX_PALETTE_NAME 64
#define MAX_PRESET_PALETTES 256
#define MAX_NORMAL_PRESET_PALETTES 128
#define MAX_MODDED_PRESET_PALETTES 128

enum PlayerPart {
    PANTS, SHIRT, GLOVES, SHOES, HAIR, SKIN, CAP, EMBLEM, PLAYER_PART_MAX, METAL = CAP
};

#pragma pack(1)
struct PlayerPalette {
    //rgb
    Color parts[PLAYER_PART_MAX];
};
#pragma pack()

struct PresetPalette {
    char name[MAX_PALETTE_NAME];
    struct PlayerPalette palette;
    bool active;
};

extern const struct PlayerPalette DEFAULT_MARIO_PALETTE;

extern struct PresetPalette gPresetPalettes[MAX_PRESET_PALETTES];
extern u16 gPresetPaletteCount;
extern struct PresetPalette gModdedPresetPalettes[MAX_MODDED_PRESET_PALETTES];
extern u16 gModdedPresetPalettesCount;

void player_palettes_reset(void);
void player_modded_palettes_reset(void);
void player_palettes_read(const char* palettePath, bool appendPalettes);
void player_palette_export(char* name);
bool player_palette_delete(const char* palettesPath, char* name, bool appendPalettes);
struct PresetPalette* preset_palette_allocate(const char* name);
void preset_palette_set_name(struct PresetPalette* palette, const char* name);
void preset_palette_set_color_of_part(struct PresetPalette* palette, u8 playerPart, u8 r, u8 g, u8 b);

#endif
