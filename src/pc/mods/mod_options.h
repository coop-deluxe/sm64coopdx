#ifndef MOD_OPTIONS_H
#define MOD_OPTIONS_H

#include <PR/ultratypes.h>
#include "types.h"
#include "pc/platform.h"
#include "mod_presets.h"

#define MOD_OPTIONS_FILE "mod-options.txt"

// a mod only describes its menu while its Lua runs, so record it for the main menu to use
struct ModOption {
    u16 index;      // registration order within the mod, the key presets use
    u8 type;        // enum ModPresetSettingType
    char* label;
    u32 sliderMin;
    u32 sliderMax;
    u32 length;     // inputbox capacity
    bool boolValue;
    u32 uintValue;
    char* stringValue;
    bool pending;   // chosen while the mod was not running, still owed to the live element
};

struct ModOptions {
    char* modRelativePath;
    struct ModOption* options;
    u16 count;
};

extern struct ModOptions* gModOptions;
extern u16 gModOptionsCount;

struct ModOptions* mod_options_find(const char* modRelativePath);
struct ModOption* mod_options_find_option(struct ModOptions* modOptions, u16 index);
bool mod_options_has_any(const char* modRelativePath);

void mod_options_load(void);
void mod_options_save(void);
void mod_options_record_live(void);
void mod_options_mark_pending(const char* modRelativePath, u16 elementIndex);
void mod_options_apply_pending(void);
void mod_options_seed_from_preset(struct ModPreset* preset);
void mod_options_shutdown(void);

#endif
