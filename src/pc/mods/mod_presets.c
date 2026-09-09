#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "mods.h"
#include "mods_utils.h"
#include "mod_presets.h"
#include "mod_options.h"
#include "pc/configfile.h"
#include "pc/debuglog.h"
#include "pc/fs/fs.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/network/network.h"

#define MOD_PRESET_LINE_MAX 4608
#define MOD_PRESET_LABEL_SIZE 256

struct ModPreset gModPresets[MAX_MOD_PRESETS] = { 0 };
u16 gModPresetCount = 0;

static const char* sSettingTypeNames[MOD_PRESET_SETTING_MAX] = {
    "checkbox",
    "slider",
    "inputbox"
};

  /////////////
 // helpers //
/////////////

// tabs and newlines are the preset file's structure, they can never appear inside a field
static void mod_preset_sanitize(char* destination, size_t size, const char* source) {
    if (size == 0) { return; }
    if (source == NULL) { destination[0] = '\0'; return; }

    size_t i = 0;
    for (; source[i] != '\0' && i < size - 1; i++) {
        char c = source[i];
        destination[i] = (c == '\t' || c == '\r' || c == '\n') ? ' ' : c;
    }
    destination[i] = '\0';
}

// must survive the file system and the config file's whitespace tokeniser
bool mod_preset_name_valid(const char* name) {
    if (name == NULL) { return false; }
    if (name[0] == '\0') { return false; }

    size_t length = strlen(name);
    if (length > MOD_PRESET_NAME_MAX_LENGTH) { return false; }
    if (name[0] == ' ' || name[length - 1] == ' ') { return false; }
    if (name[0] == '.') { return false; }

    u16 words = 1;
    for (const char* c = name; *c != '\0'; c++) {
        if (*c < ' ' || *c > '~') { return false; }
        switch (*c) {
            case '/': case '\\': case '<': case '>':
            case ':': case '"': case '|': case '?': case '*':
                return false;
            case ' ':
                // runs of spaces would come back as a single space
                if (c[1] == ' ') { return false; }
                words++;
                break;
            default: break;
        }
    }
    if (words > MOD_PRESET_NAME_MAX_WORDS) { return false; }

    return true;
}

// case insensitive: "race.preset" and "Race.preset" are one file on Windows
s32 mod_presets_find(const char* name) {
    if (name == NULL || name[0] == '\0') { return -1; }

    for (u16 i = 0; i < gModPresetCount; i++) {
        if (!sys_strcasecmp(gModPresets[i].name, name)) { return (s32)i; }
    }

    return -1;
}

struct ModPreset* mod_presets_get_active(void) {
    s32 index = mod_presets_find(configModPreset);
    return (index < 0) ? NULL : &gModPresets[index];
}

void mod_presets_set_active(const char* name) {
    snprintf(configModPreset, MAX_CONFIG_STRING, "%s", name ? name : "");
}

u8 mod_presets_setting_type_from_element(u8 element) {
    switch (element) {
        case MOD_MENU_ELEMENT_CHECKBOX: return MOD_PRESET_SETTING_CHECKBOX;
        case MOD_MENU_ELEMENT_SLIDER:   return MOD_PRESET_SETTING_SLIDER;
        case MOD_MENU_ELEMENT_INPUTBOX: return MOD_PRESET_SETTING_INPUTBOX;
        default: break;
    }

    return MOD_PRESET_SETTING_MAX;
}

// where this element sits in the list of elements its own mod registered
u16 mod_presets_element_index(int hookedIndex) {
    struct Mod* mod = gHookedModMenuElements[hookedIndex].mod;
    u16 elementIndex = 0;

    for (int i = 0; i < hookedIndex; i++) {
        if (gHookedModMenuElements[i].mod == mod) { elementIndex++; }
    }

    return elementIndex;
}

static struct ModPresetSetting* mod_preset_find_setting(struct ModPreset* preset, const char* modRelativePath, u16 elementIndex) {
    if (preset == NULL) { return NULL; }

    for (u16 i = 0; i < preset->settingCount; i++) {
        struct ModPresetSetting* setting = &preset->settings[i];
        if (setting->elementIndex != elementIndex) { continue; }
        if (strcmp(setting->modRelativePath, modRelativePath)) { continue; }
        return setting;
    }

    return NULL;
}

// is there a mod menu element loaded right now that owns this setting?
static bool mod_preset_setting_is_live(const char* modRelativePath, u16 elementIndex) {
    for (int i = 0; i < gHookedModMenuElementsCount; i++) {
        struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
        if (hooked->mod == NULL) { continue; }
        if (mod_presets_setting_type_from_element(hooked->element) >= MOD_PRESET_SETTING_MAX) { continue; }
        if (mod_presets_element_index(i) != elementIndex) { continue; }
        if (strcmp(hooked->mod->relativePath, modRelativePath)) { continue; }
        return true;
    }

    return false;
}

static bool mod_preset_mod_is_enabled(const char* relativePath) {
    for (u16 i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        if (!mod->enabled) { continue; }
        if (!strcmp(mod->relativePath, relativePath)) { return true; }
    }

    return false;
}

  //////////////
 // lifetime //
//////////////

static void mod_preset_clear(struct ModPreset* preset) {
    if (preset->modPaths != NULL) {
        for (u16 i = 0; i < preset->modCount; i++) { free(preset->modPaths[i]); }
        free(preset->modPaths);
        preset->modPaths = NULL;
    }
    preset->modCount = 0;

    if (preset->settings != NULL) {
        for (u16 i = 0; i < preset->settingCount; i++) {
            free(preset->settings[i].modRelativePath);
            free(preset->settings[i].label);
            free(preset->settings[i].stringValue);
        }
        free(preset->settings);
        preset->settings = NULL;
    }
    preset->settingCount = 0;

    preset->name[0] = '\0';
}

static void mod_presets_clear(void) {
    for (u16 i = 0; i < gModPresetCount; i++) { mod_preset_clear(&gModPresets[i]); }
    gModPresetCount = 0;
}

void mod_presets_shutdown(void) {
    mod_presets_clear();
}

  /////////////
 // reading //
/////////////

static void mod_preset_add_mod_path(struct ModPreset* preset, const char* relativePath) {
    if (relativePath[0] == '\0') { return; }

    // ignore duplicates
    for (u16 i = 0; i < preset->modCount; i++) {
        if (!strcmp(preset->modPaths[i], relativePath)) { return; }
    }

    char** modPaths = realloc(preset->modPaths, sizeof(char*) * (preset->modCount + 1));
    if (modPaths == NULL) { return; }
    preset->modPaths = modPaths;

    char* copy = sys_strdup(relativePath);
    if (copy == NULL) { return; }
    preset->modPaths[preset->modCount] = copy;
    preset->modCount++;
}

static void mod_preset_add_setting(struct ModPreset* preset, u8 type, const char* modRelativePath, u16 elementIndex, const char* label, const char* value) {
    if (type >= MOD_PRESET_SETTING_MAX) { return; }
    if (modRelativePath[0] == '\0') { return; }

    // a repeated key replaces the previous one
    struct ModPresetSetting* setting = mod_preset_find_setting(preset, modRelativePath, elementIndex);
    if (setting == NULL) {
        struct ModPresetSetting* settings = realloc(preset->settings, sizeof(struct ModPresetSetting) * (preset->settingCount + 1));
        if (settings == NULL) { return; }
        preset->settings = settings;

        setting = &preset->settings[preset->settingCount];
        memset(setting, 0, sizeof(struct ModPresetSetting));
        setting->modRelativePath = sys_strdup(modRelativePath);
        if (setting->modRelativePath == NULL) { return; }
        setting->elementIndex = elementIndex;
        preset->settingCount++;
    }

    free(setting->label);
    setting->label = sys_strdup(label);
    setting->type = type;
    setting->boolValue = false;
    setting->uintValue = 0;
    free(setting->stringValue);
    setting->stringValue = NULL;

    switch (type) {
        case MOD_PRESET_SETTING_CHECKBOX: setting->boolValue = (value[0] == '1'); break;
        case MOD_PRESET_SETTING_SLIDER:   setting->uintValue = (u32)strtoul(value, NULL, 10); break;
        case MOD_PRESET_SETTING_INPUTBOX: setting->stringValue = sys_strdup(value); break;
        default: break;
    }
}

static void mod_preset_parse_line(struct ModPreset* preset, char* line) {
    if (line[0] == '#' || line[0] == '\0') { return; }

    char* rest = NULL;
    char* command = strtok_r(line, "\t", &rest);
    if (command == NULL) { return; }

    if (!strcmp(command, "mod")) {
        char* relativePath = strtok_r(NULL, "\t", &rest);
        if (relativePath == NULL) { return; }
        mod_preset_add_mod_path(preset, relativePath);
        return;
    }

    if (!strcmp(command, "cfg")) {
        char* typeName = strtok_r(NULL, "\t", &rest);
        char* relativePath = strtok_r(NULL, "\t", &rest);
        char* elementIndex = strtok_r(NULL, "\t", &rest);
        char* label = strtok_r(NULL, "\t", &rest);
        if (typeName == NULL || relativePath == NULL || elementIndex == NULL || label == NULL) { return; }

        // whatever is left over is the value, it may legitimately be empty
        const char* value = (rest != NULL) ? rest : "";

        for (u8 type = 0; type < MOD_PRESET_SETTING_MAX; type++) {
            if (strcmp(typeName, sSettingTypeNames[type])) { continue; }
            mod_preset_add_setting(preset, type, relativePath, (u16)strtoul(elementIndex, NULL, 10), label, value);
            return;
        }
    }
}

static bool mod_preset_read(struct ModPreset* preset, const char* path, const char* name) {
    FILE* file = fopen(path, "r");
    if (file == NULL) { return false; }

    snprintf(preset->name, MOD_PRESET_NAME_SIZE, "%s", name);

    char line[MOD_PRESET_LINE_MAX] = { 0 };
    while (fgets(line, MOD_PRESET_LINE_MAX, file) != NULL) {
        size_t length = strlen(line);
        while (length > 0 && (line[length - 1] == '\n' || line[length - 1] == '\r')) {
            line[--length] = '\0';
        }
        mod_preset_parse_line(preset, line);
    }

    fclose(file);
    return true;
}

static void mod_presets_sort(void) {
    for (u16 i = 1; i < gModPresetCount; i++) {
        struct ModPreset preset = gModPresets[i];
        s32 j = (s32)i - 1;
        while (j >= 0 && strcmp(gModPresets[j].name, preset.name) > 0) {
            gModPresets[j + 1] = gModPresets[j];
            j--;
        }
        gModPresets[j + 1] = preset;
    }
}

void mod_presets_refresh(void) {
    mod_presets_clear();

    char presetsPath[SYS_MAX_PATH] = { 0 };
    snprintf(presetsPath, SYS_MAX_PATH, "%s", fs_get_write_path(MOD_PRESETS_DIRECTORY));

    DIR* d = opendir(presetsPath);
    if (!d) { return; }

    struct dirent* dir = NULL;
    char path[SYS_MAX_PATH] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        if (gModPresetCount >= MAX_MOD_PRESETS) { break; }
        if (!directory_sanity_check(dir, presetsPath, path)) { continue; }
        if (!str_ends_with(dir->d_name, MOD_PRESET_EXTENSION)) { continue; }

        // strip the extension to get the preset's name
        char name[MOD_PRESET_NAME_SIZE] = { 0 };
        size_t nameLength = strlen(dir->d_name) - strlen(MOD_PRESET_EXTENSION);
        if (nameLength == 0 || nameLength >= MOD_PRESET_NAME_SIZE) { continue; }
        snprintf(name, nameLength + 1, "%s", dir->d_name);

        if (mod_presets_find(name) >= 0) { continue; }

        struct ModPreset* preset = &gModPresets[gModPresetCount];
        mod_preset_clear(preset);
        if (!mod_preset_read(preset, path, name)) {
            LOG_ERROR("Failed to load mod preset '%s'", name);
            mod_preset_clear(preset);
            continue;
        }

        LOG_INFO("Loaded mod preset '%s'", name);
        gModPresetCount++;
    }

    closedir(d);

    mod_presets_sort();
}

  /////////////
 // writing //
/////////////

static void mod_preset_write_setting(FILE* file, u8 type, const char* modRelativePath, u16 elementIndex, const char* label, bool boolValue, u32 uintValue, const char* stringValue) {
    char modField[SYS_MAX_PATH] = { 0 };
    char labelField[MOD_PRESET_LABEL_SIZE] = { 0 };

    mod_preset_sanitize(modField, sizeof(modField), modRelativePath);
    mod_preset_sanitize(labelField, sizeof(labelField), label);

    // an empty field would collapse the tab separators around it
    if (labelField[0] == '\0') { snprintf(labelField, sizeof(labelField), "-"); }

    switch (type) {
        case MOD_PRESET_SETTING_CHECKBOX:
            fprintf(file, "cfg\t%s\t%s\t%u\t%s\t%d\n", sSettingTypeNames[type], modField, elementIndex, labelField, boolValue ? 1 : 0);
            break;
        case MOD_PRESET_SETTING_SLIDER:
            fprintf(file, "cfg\t%s\t%s\t%u\t%s\t%u\n", sSettingTypeNames[type], modField, elementIndex, labelField, uintValue);
            break;
        case MOD_PRESET_SETTING_INPUTBOX: {
            char valueField[MOD_PRESET_LABEL_SIZE] = { 0 };
            mod_preset_sanitize(valueField, sizeof(valueField), stringValue);
            fprintf(file, "cfg\t%s\t%s\t%u\t%s\t%s\n", sSettingTypeNames[type], modField, elementIndex, labelField, valueField);
            break;
        }
        default: break;
    }
}

bool mod_preset_save(const char* inName) {
    if (!mod_preset_name_valid(inName)) { return false; }

    // keep the spelling already on disk, so a case-only difference can't orphan the file
    s32 index = mod_presets_find(inName);
    char name[MOD_PRESET_NAME_SIZE] = { 0 };
    snprintf(name, MOD_PRESET_NAME_SIZE, "%s", (index >= 0) ? gModPresets[index].name : inName);

    // fs_get_write_path() hands back a shared static buffer, take a copy of it
    char presetsPath[SYS_MAX_PATH] = { 0 };
    snprintf(presetsPath, SYS_MAX_PATH, "%s", fs_get_write_path(MOD_PRESETS_DIRECTORY));
    if (!fs_sys_dir_exists(presetsPath)) { fs_sys_mkdir(presetsPath); }

    char path[SYS_MAX_PATH] = { 0 };
    snprintf(path, SYS_MAX_PATH, "%s/%s%s", presetsPath, name, MOD_PRESET_EXTENSION);

    FILE* file = fopen(path, "w");
    if (file == NULL) {
        LOG_ERROR("Unable to create mod preset '%s'!", name);
        return false;
    }

    fprintf(file, "# sm64coopdx mod preset\n");

    // the mods this preset turns on
    char modField[SYS_MAX_PATH] = { 0 };
    for (u16 i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        if (!mod->enabled) { continue; }
        mod_preset_sanitize(modField, sizeof(modField), mod->relativePath);
        fprintf(file, "mod\t%s\n", modField);
    }

    // how the mods that are loaded right now are configured
    for (int i = 0; i < gHookedModMenuElementsCount; i++) {
        struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
        if (hooked->mod == NULL || !hooked->mod->enabled) { continue; }

        u8 type = mod_presets_setting_type_from_element(hooked->element);
        if (type >= MOD_PRESET_SETTING_MAX) { continue; }

        mod_preset_write_setting(file, type, hooked->mod->relativePath, mod_presets_element_index(i), hooked->name,
                                 hooked->boolValue, hooked->uintValue, hooked->stringValue);
    }

    // mods that aren't loaded: recorded options first, then whatever the preset already held
    for (u16 i = 0; i < gModOptionsCount; i++) {
        struct ModOptions* modOptions = &gModOptions[i];
        if (!mod_preset_mod_is_enabled(modOptions->modRelativePath)) { continue; }

        for (u16 j = 0; j < modOptions->count; j++) {
            struct ModOption* option = &modOptions->options[j];
            if (option->type >= MOD_PRESET_SETTING_MAX) { continue; }
            if (mod_preset_setting_is_live(modOptions->modRelativePath, option->index)) { continue; }

            mod_preset_write_setting(file, option->type, modOptions->modRelativePath, option->index, option->label,
                                     option->boolValue, option->uintValue, option->stringValue);
        }
    }

    if (index >= 0) {
        struct ModPreset* preset = &gModPresets[index];
        for (u16 i = 0; i < preset->settingCount; i++) {
            struct ModPresetSetting* setting = &preset->settings[i];
            if (setting->type >= MOD_PRESET_SETTING_MAX) { continue; }
            if (!mod_preset_mod_is_enabled(setting->modRelativePath)) { continue; }
            if (mod_preset_setting_is_live(setting->modRelativePath, setting->elementIndex)) { continue; }

            // already written from the recorded options above
            struct ModOptions* modOptions = mod_options_find(setting->modRelativePath);
            if (mod_options_find_option(modOptions, setting->elementIndex) != NULL) { continue; }

            mod_preset_write_setting(file, setting->type, setting->modRelativePath, setting->elementIndex, setting->label,
                                     setting->boolValue, setting->uintValue, setting->stringValue);
        }
    }

    fclose(file);
    LOG_INFO("Saving mod preset as '%s%s'", name, MOD_PRESET_EXTENSION);

    mod_presets_refresh();
    mod_presets_set_active(name);
    return true;
}

// not name_valid(): a hand-placed preset can carry a name this build wouldn't create
bool mod_preset_delete(const char* name) {
    s32 index = mod_presets_find(name);
    if (index < 0) { return false; }

    char path[SYS_MAX_PATH] = { 0 };
    snprintf(path, SYS_MAX_PATH, "%s/%s%s", fs_get_write_path(MOD_PRESETS_DIRECTORY), gModPresets[index].name, MOD_PRESET_EXTENSION);

    if (remove(path) != 0) { return false; }
    LOG_INFO("Deleting mod preset '%s%s'", name, MOD_PRESET_EXTENSION);

    if (!sys_strcasecmp(configModPreset, name)) { mod_presets_set_active(NULL); }
    mod_presets_refresh();
    return true;
}

  //////////////
 // applying //
//////////////

bool mod_preset_matches_enabled_mods(struct ModPreset* preset) {
    if (preset == NULL) { return false; }
    if (mods_get_enabled_count() != preset->modCount) { return false; }

    for (u16 i = 0; i < preset->modCount; i++) {
        if (!mod_preset_mod_is_enabled(preset->modPaths[i])) { return false; }
    }

    return true;
}

// editing an element the preset doesn't own must leave the preset selected
bool mod_presets_active_owns_element(int hookedIndex) {
    if (gNetworkType == NT_CLIENT) { return false; }
    if (hookedIndex < 0 || hookedIndex >= gHookedModMenuElementsCount) { return false; }

    struct ModPreset* preset = mod_presets_get_active();
    if (preset == NULL) { return false; }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[hookedIndex];
    if (hooked->mod == NULL) { return false; }

    return mod_preset_find_setting(preset, hooked->mod->relativePath, mod_presets_element_index(hookedIndex)) != NULL;
}

// the same question for a recorded option, which the gear panel edits with no mods loaded to
// index into. the client guard is for parity with the calls around it, a client never gets here
bool mod_presets_active_owns_option(const char* modRelativePath, u16 elementIndex) {
    if (gNetworkType == NT_CLIENT) { return false; }
    if (modRelativePath == NULL || modRelativePath[0] == '\0') { return false; }

    return mod_preset_find_setting(mod_presets_get_active(), modRelativePath, elementIndex) != NULL;
}

void mod_presets_apply_active_settings(void) {
    // the mods a client runs come from the host, a local preset has no business reconfiguring them
    if (gNetworkType == NT_CLIENT) { return; }

    struct ModPreset* preset = mod_presets_get_active();
    if (preset == NULL) { return; }

    for (int i = 0; i < gHookedModMenuElementsCount; i++) {
        struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
        if (hooked->mod == NULL) { continue; }

        struct ModPresetSetting* setting = mod_preset_find_setting(preset, hooked->mod->relativePath, mod_presets_element_index(i));
        if (setting == NULL) { continue; }

        bool changed = false;
        switch (hooked->element) {
            case MOD_MENU_ELEMENT_CHECKBOX: {
                if (setting->type != MOD_PRESET_SETTING_CHECKBOX) { break; }
                if (hooked->boolValue == setting->boolValue) { break; }
                hooked->boolValue = setting->boolValue;
                changed = true;
                break;
            }
            case MOD_MENU_ELEMENT_SLIDER: {
                if (setting->type != MOD_PRESET_SETTING_SLIDER) { break; }
                u32 value = setting->uintValue;
                if (value < hooked->sliderMin) { value = hooked->sliderMin; }
                if (value > hooked->sliderMax) { value = hooked->sliderMax; }
                if (hooked->uintValue == value) { break; }
                hooked->uintValue = value;
                changed = true;
                break;
            }
            case MOD_MENU_ELEMENT_INPUTBOX: {
                if (setting->type != MOD_PRESET_SETTING_INPUTBOX) { break; }
                const char* value = setting->stringValue ? setting->stringValue : "";
                if (!strcmp(hooked->stringValue, value)) { break; }
                snprintf(hooked->stringValue, sizeof(hooked->stringValue), "%s", value);
                changed = true;
                break;
            }
            default: break;
        }

        if (changed) { smlua_call_mod_menu_element_hook(hooked, i); }
    }
}

void mod_preset_apply(struct ModPreset* preset) {
    if (preset == NULL) { return; }

    mods_disable_all();
    for (u16 i = 0; i < preset->modCount; i++) {
        mods_enable(preset->modPaths[i]);
    }
    mods_update_selectable();

    mod_presets_set_active(preset->name);

    // the gear panel and a later save should both reflect what this preset holds
    mod_options_seed_from_preset(preset);

    // if the mods are already running, reconfigure them right away
    mod_presets_apply_active_settings();
}
