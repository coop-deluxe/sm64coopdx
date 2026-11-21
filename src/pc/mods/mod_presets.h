#ifndef MOD_PRESETS_H
#define MOD_PRESETS_H

#include <PR/ultratypes.h>
#include "types.h"
#include "pc/platform.h"

#define MOD_PRESETS_DIRECTORY "mod-presets"
#define MOD_PRESET_EXTENSION ".preset"

#define MOD_PRESET_NAME_MAX_LENGTH 63
#define MOD_PRESET_NAME_SIZE (MOD_PRESET_NAME_MAX_LENGTH + 1)
// the config file tokenises a line into at most 20 words, one of which is "mod-preset:"
#define MOD_PRESET_NAME_MAX_WORDS 19
#define MAX_MOD_PRESETS 128

// the mod menu element types a preset is able to restore
enum ModPresetSettingType {
    MOD_PRESET_SETTING_CHECKBOX,
    MOD_PRESET_SETTING_SLIDER,
    MOD_PRESET_SETTING_INPUTBOX,
    MOD_PRESET_SETTING_MAX
};

struct ModPresetSetting {
    char* modRelativePath;
    u16 elementIndex;   // keyed by registration order, mods rename their elements at runtime
    char* label;
    u8 type;
    bool boolValue;
    u32 uintValue;
    char* stringValue;
};

struct ModPreset {
    char name[MOD_PRESET_NAME_SIZE];
    char** modPaths;
    u16 modCount;
    struct ModPresetSetting* settings;
    u16 settingCount;
};

extern struct ModPreset gModPresets[MAX_MOD_PRESETS];
extern u16 gModPresetCount;

u16  mod_presets_element_index(int hookedIndex);
u8   mod_presets_setting_type_from_element(u8 element);
bool mod_preset_name_valid(const char* name);
s32  mod_presets_find(const char* name);
struct ModPreset* mod_presets_get_active(void);
void mod_presets_set_active(const char* name);
void mod_presets_refresh(void);
bool mod_preset_save(const char* name);
bool mod_preset_delete(const char* name);
void mod_preset_apply(struct ModPreset* preset);
bool mod_preset_matches_enabled_mods(struct ModPreset* preset);
bool mod_presets_active_owns_element(int hookedIndex);
bool mod_presets_active_owns_option(const char* modRelativePath, u16 elementIndex);
void mod_presets_apply_active_settings(void);
void mod_presets_shutdown(void);

#endif
