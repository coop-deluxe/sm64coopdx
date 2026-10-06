#include <stdlib.h>
#include <string.h>
#include "mods.h"
#include "mods_utils.h"
#include "mod_options.h"
#include "pc/debuglog.h"
#include "pc/fs/fs.h"
#include "pc/lua/smlua_hooks.h"

#define MOD_OPTIONS_LINE_MAX 4608
#define MOD_OPTIONS_LABEL_SIZE 256

struct ModOptions* gModOptions = NULL;
u16 gModOptionsCount = 0;

static const char* sOptionTypeNames[MOD_PRESET_SETTING_MAX] = {
    "checkbox",
    "slider",
    "inputbox"
};

  /////////////
 // helpers //
/////////////

// tabs and newlines are the file's structure, they can never appear inside a field
static void mod_options_sanitize(char* destination, size_t size, const char* source) {
    if (size == 0) { return; }
    if (source == NULL) { destination[0] = '\0'; return; }

    size_t i = 0;
    for (; source[i] != '\0' && i < size - 1; i++) {
        char c = source[i];
        destination[i] = (c == '\t' || c == '\r' || c == '\n') ? ' ' : c;
    }
    destination[i] = '\0';
}

struct ModOptions* mod_options_find(const char* modRelativePath) {
    if (modRelativePath == NULL) { return NULL; }

    for (u16 i = 0; i < gModOptionsCount; i++) {
        if (!strcmp(gModOptions[i].modRelativePath, modRelativePath)) { return &gModOptions[i]; }
    }

    return NULL;
}

struct ModOption* mod_options_find_option(struct ModOptions* modOptions, u16 index) {
    if (modOptions == NULL) { return NULL; }

    for (u16 i = 0; i < modOptions->count; i++) {
        if (modOptions->options[i].index == index) { return &modOptions->options[i]; }
    }

    return NULL;
}

bool mod_options_has_any(const char* modRelativePath) {
    struct ModOptions* modOptions = mod_options_find(modRelativePath);
    return modOptions != NULL && modOptions->count > 0;
}

  //////////////
 // lifetime //
//////////////

static void mod_options_clear_one(struct ModOptions* modOptions) {
    for (u16 i = 0; i < modOptions->count; i++) {
        free(modOptions->options[i].label);
        free(modOptions->options[i].stringValue);
    }
    free(modOptions->options);
    free(modOptions->modRelativePath);
    modOptions->options = NULL;
    modOptions->modRelativePath = NULL;
    modOptions->count = 0;
}

static void mod_options_clear(void) {
    for (u16 i = 0; i < gModOptionsCount; i++) { mod_options_clear_one(&gModOptions[i]); }
    free(gModOptions);
    gModOptions = NULL;
    gModOptionsCount = 0;
}

void mod_options_shutdown(void) {
    mod_options_clear();
}

static struct ModOptions* mod_options_get_or_add(const char* modRelativePath) {
    struct ModOptions* modOptions = mod_options_find(modRelativePath);
    if (modOptions != NULL) { return modOptions; }

    struct ModOptions* grown = realloc(gModOptions, sizeof(struct ModOptions) * (gModOptionsCount + 1));
    if (grown == NULL) { return NULL; }
    gModOptions = grown;

    modOptions = &gModOptions[gModOptionsCount];
    memset(modOptions, 0, sizeof(struct ModOptions));
    modOptions->modRelativePath = sys_strdup(modRelativePath);
    if (modOptions->modRelativePath == NULL) { return NULL; }
    gModOptionsCount++;

    return modOptions;
}

static struct ModOption* mod_options_get_or_add_option(struct ModOptions* modOptions, u16 index) {
    struct ModOption* option = mod_options_find_option(modOptions, index);
    if (option != NULL) { return option; }

    struct ModOption* grown = realloc(modOptions->options, sizeof(struct ModOption) * (modOptions->count + 1));
    if (grown == NULL) { return NULL; }
    modOptions->options = grown;

    option = &modOptions->options[modOptions->count];
    memset(option, 0, sizeof(struct ModOption));
    option->index = index;
    modOptions->count++;

    return option;
}

static void mod_option_set_string(struct ModOption* option, const char* value) {
    char* copy = sys_strdup(value ? value : "");
    if (copy == NULL) { return; }
    free(option->stringValue);
    option->stringValue = copy;
}

static void mod_option_set_label(struct ModOption* option, const char* label) {
    char* copy = sys_strdup(label ? label : "");
    if (copy == NULL) { return; }
    free(option->label);
    option->label = copy;
}

  /////////////
 // reading //
/////////////

static void mod_options_parse_line(struct ModOptions** current, char* line) {
    if (line[0] == '#' || line[0] == '\0') { return; }

    char* rest = NULL;
    char* command = strtok_r(line, "\t", &rest);
    if (command == NULL) { return; }

    if (!strcmp(command, "mod")) {
        char* relativePath = strtok_r(NULL, "\t", &rest);
        if (relativePath == NULL || relativePath[0] == '\0') { *current = NULL; return; }
        *current = mod_options_get_or_add(relativePath);
        return;
    }

    if (!strcmp(command, "pend")) {
        if (*current == NULL) { return; }

        char* indexField = strtok_r(NULL, "\t", &rest);
        if (indexField == NULL) { return; }

        struct ModOption* option = mod_options_find_option(*current, (u16)strtoul(indexField, NULL, 10));
        if (option != NULL) { option->pending = true; }
        return;
    }

    if (!strcmp(command, "opt")) {
        if (*current == NULL) { return; }

        char* indexField = strtok_r(NULL, "\t", &rest);
        char* typeName = strtok_r(NULL, "\t", &rest);
        char* minField = strtok_r(NULL, "\t", &rest);
        char* maxField = strtok_r(NULL, "\t", &rest);
        char* lengthField = strtok_r(NULL, "\t", &rest);
        char* label = strtok_r(NULL, "\t", &rest);
        if (indexField == NULL || typeName == NULL || minField == NULL) { return; }
        if (maxField == NULL || lengthField == NULL || label == NULL) { return; }

        // whatever is left over is the value, it may legitimately be empty
        const char* value = (rest != NULL) ? rest : "";

        for (u8 type = 0; type < MOD_PRESET_SETTING_MAX; type++) {
            if (strcmp(typeName, sOptionTypeNames[type])) { continue; }

            struct ModOption* option = mod_options_get_or_add_option(*current, (u16)strtoul(indexField, NULL, 10));
            if (option == NULL) { return; }

            option->type = type;
            option->sliderMin = (u32)strtoul(minField, NULL, 10);
            option->sliderMax = (u32)strtoul(maxField, NULL, 10);
            option->length = (u32)strtoul(lengthField, NULL, 10);
            mod_option_set_label(option, label);

            option->boolValue = false;
            option->uintValue = 0;
            switch (type) {
                case MOD_PRESET_SETTING_CHECKBOX: option->boolValue = (value[0] == '1'); break;
                case MOD_PRESET_SETTING_SLIDER:   option->uintValue = (u32)strtoul(value, NULL, 10); break;
                case MOD_PRESET_SETTING_INPUTBOX: mod_option_set_string(option, value); break;
                default: break;
            }
            return;
        }
    }
}

void mod_options_load(void) {
    mod_options_clear();

    char path[SYS_MAX_PATH] = { 0 };
    snprintf(path, SYS_MAX_PATH, "%s/%s", fs_get_write_path(""), MOD_OPTIONS_FILE);

    FILE* file = fopen(path, "r");
    if (file == NULL) { return; }

    struct ModOptions* current = NULL;
    char line[MOD_OPTIONS_LINE_MAX] = { 0 };
    while (fgets(line, MOD_OPTIONS_LINE_MAX, file) != NULL) {
        size_t length = strlen(line);
        while (length > 0 && (line[length - 1] == '\n' || line[length - 1] == '\r')) {
            line[--length] = '\0';
        }
        mod_options_parse_line(&current, line);
    }

    fclose(file);
}

  /////////////
 // writing //
/////////////

void mod_options_save(void) {
    char path[SYS_MAX_PATH] = { 0 };
    snprintf(path, SYS_MAX_PATH, "%s/%s", fs_get_write_path(""), MOD_OPTIONS_FILE);

    FILE* file = fopen(path, "w");
    if (file == NULL) {
        LOG_ERROR("Unable to write '%s'!", MOD_OPTIONS_FILE);
        return;
    }

    fprintf(file, "# sm64coopdx mod menu options, recorded the last time each mod ran\n");

    char pathField[SYS_MAX_PATH] = { 0 };
    char labelField[MOD_OPTIONS_LABEL_SIZE] = { 0 };
    char valueField[MOD_OPTIONS_LABEL_SIZE] = { 0 };

    for (u16 i = 0; i < gModOptionsCount; i++) {
        struct ModOptions* modOptions = &gModOptions[i];
        if (modOptions->count == 0) { continue; }

        mod_options_sanitize(pathField, sizeof(pathField), modOptions->modRelativePath);
        fprintf(file, "mod\t%s\n", pathField);

        for (u16 j = 0; j < modOptions->count; j++) {
            struct ModOption* option = &modOptions->options[j];
            if (option->type >= MOD_PRESET_SETTING_MAX) { continue; }

            mod_options_sanitize(labelField, sizeof(labelField), option->label);
            // an empty field would collapse the tab separators around it
            if (labelField[0] == '\0') { snprintf(labelField, sizeof(labelField), "-"); }

            fprintf(file, "opt\t%u\t%s\t%u\t%u\t%u\t%s\t",
                    option->index, sOptionTypeNames[option->type],
                    option->sliderMin, option->sliderMax, option->length, labelField);

            switch (option->type) {
                case MOD_PRESET_SETTING_CHECKBOX: fprintf(file, "%d\n", option->boolValue ? 1 : 0); break;
                case MOD_PRESET_SETTING_SLIDER:   fprintf(file, "%u\n", option->uintValue); break;
                case MOD_PRESET_SETTING_INPUTBOX:
                    mod_options_sanitize(valueField, sizeof(valueField), option->stringValue);
                    fprintf(file, "%s\n", valueField);
                    break;
                default: fprintf(file, "\n"); break;
            }

            if (option->pending) { fprintf(file, "pend\t%u\n", option->index); }
        }
    }

    fclose(file);
}

  ///////////////
 // recording //
///////////////

// snapshot the loaded mods' menu elements
void mod_options_record_live(void) {
    // a client runs the host's mods, which may share a path with a different local mod
    if (gNetworkType == NT_CLIENT) { return; }

    bool recorded = false;

    for (int i = 0; i < gHookedModMenuElementsCount; i++) {
        struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
        if (hooked->mod == NULL) { continue; }

        u8 type = mod_presets_setting_type_from_element(hooked->element);
        if (type >= MOD_PRESET_SETTING_MAX) { continue; }

        struct ModOptions* modOptions = mod_options_get_or_add(hooked->mod->relativePath);
        if (modOptions == NULL) { continue; }

        struct ModOption* option = mod_options_get_or_add_option(modOptions, mod_presets_element_index(i));
        if (option == NULL) { continue; }

        option->type = type;
        option->sliderMin = hooked->sliderMin;
        option->sliderMax = hooked->sliderMax;
        option->length = hooked->length;
        mod_option_set_label(option, hooked->name);

        option->boolValue = hooked->boolValue;
        option->uintValue = hooked->uintValue;
        if (type == MOD_PRESET_SETTING_INPUTBOX) { mod_option_set_string(option, hooked->stringValue); }

        recorded = true;
    }

    if (recorded) { mod_options_save(); }
}

static bool mod_options_mod_is_live(const char* modRelativePath) {
    for (int i = 0; i < gHookedModMenuElementsCount; i++) {
        struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
        if (hooked->mod == NULL) { continue; }
        if (!strcmp(hooked->mod->relativePath, modRelativePath)) { return true; }
    }

    return false;
}

void mod_options_mark_pending(const char* modRelativePath, u16 elementIndex) {
    struct ModOption* option = mod_options_find_option(mod_options_find(modRelativePath), elementIndex);
    if (option != NULL) { option->pending = true; }
}

// a value chosen while the mod was not running has to reach the element when it loads, otherwise
// mod_options_record_live immediately records over it and the choice is silently lost
void mod_options_apply_pending(void) {
    if (gNetworkType == NT_CLIENT) { return; }

    for (int i = 0; i < gHookedModMenuElementsCount; i++) {
        struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
        if (hooked->mod == NULL) { continue; }

        u8 type = mod_presets_setting_type_from_element(hooked->element);
        if (type >= MOD_PRESET_SETTING_MAX) { continue; }

        struct ModOptions* modOptions = mod_options_find(hooked->mod->relativePath);
        struct ModOption* option = mod_options_find_option(modOptions, mod_presets_element_index(i));
        if (option == NULL || !option->pending) { continue; }

        // delivered either way, a value this element cannot hold is not owed forever
        option->pending = false;
        if (option->type != type) { continue; }

        bool changed = false;
        switch (type) {
            case MOD_PRESET_SETTING_CHECKBOX: {
                if (hooked->boolValue == option->boolValue) { break; }
                hooked->boolValue = option->boolValue;
                changed = true;
                break;
            }
            case MOD_PRESET_SETTING_SLIDER: {
                u32 value = option->uintValue;
                if (value < hooked->sliderMin) { value = hooked->sliderMin; }
                if (value > hooked->sliderMax) { value = hooked->sliderMax; }
                if (hooked->uintValue == value) { break; }
                hooked->uintValue = value;
                changed = true;
                break;
            }
            case MOD_PRESET_SETTING_INPUTBOX: {
                const char* value = (option->stringValue != NULL) ? option->stringValue : "";
                if (!strcmp(hooked->stringValue, value)) { break; }
                snprintf(hooked->stringValue, sizeof(hooked->stringValue), "%s", value);
                changed = true;
                break;
            }
            default: break;
        }

        if (changed) { smlua_call_mod_menu_element_hook(hooked, i); }
    }

    // a mod that ran is owed nothing more, an element it no longer registers is never coming back
    for (u16 i = 0; i < gModOptionsCount; i++) {
        struct ModOptions* modOptions = &gModOptions[i];
        if (!mod_options_mod_is_live(modOptions->modRelativePath)) { continue; }

        for (u16 j = 0; j < modOptions->count; j++) { modOptions->options[j].pending = false; }
    }
}

// picking a preset makes its values what the gear panel shows
void mod_options_seed_from_preset(struct ModPreset* preset) {
    if (preset == NULL) { return; }

    bool seeded = false;
    for (u16 i = 0; i < preset->settingCount; i++) {
        struct ModPresetSetting* setting = &preset->settings[i];
        if (setting->type >= MOD_PRESET_SETTING_MAX) { continue; }

        // only values for options this install already knows the shape of
        struct ModOptions* modOptions = mod_options_find(setting->modRelativePath);
        struct ModOption* option = mod_options_find_option(modOptions, setting->elementIndex);
        if (option == NULL || option->type != setting->type) { continue; }

        option->boolValue = setting->boolValue;
        option->uintValue = setting->uintValue;
        if (setting->type == MOD_PRESET_SETTING_INPUTBOX) { mod_option_set_string(option, setting->stringValue); }
        seeded = true;
    }

    if (seeded) { mod_options_save(); }
}
