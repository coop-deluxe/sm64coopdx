#ifndef PLAYER_PALETTE_H
#define PLAYER_PALETTE_H

#include "types.h"

#define PALETTES_DIRECTORY "palettes"
#define MAX_PRESET_PALETTES 128

enum PlayerPart {
    PANTS, SHIRT, GLOVES, SHOES, HAIR, SKIN, CAP, EMBLEM, PLAYER_PART_MAX, METAL = CAP
};

#pragma pack(1)
struct PlayerPalette {
    //rgb
    u8 parts[PLAYER_PART_MAX][3];
};
#pragma pack()

struct PresetPalette {
    char name[64];
    struct PlayerPalette palette;
};

extern const struct PlayerPalette DEFAULT_MARIO_PALETTE;

extern struct PresetPalette gPresetPalettes[MAX_PRESET_PALETTES];
extern u16 gPresetPaletteCount;

void player_palettes_reset(void);
void player_palettes_read(const char* palettePath, bool appendPalettes);
void player_palette_export(char* name);
bool player_palette_delete(const char* palettesPath, char* name, bool appendPalettes);

#endif
