#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_host_mods.h"
#include "djui_panel_mod_options.h"
#include "pc/mods/mods.h"
#include "pc/mods/mod_options.h"

#define MOD_OPTIONS_PER_PAGE 6

// widgets point straight at the recorded options, which nothing reallocates while this is up
static char sOptionsModPath[SYS_MAX_PATH] = { 0 };

static char* to_uppercase(const char* str) {
    char* buffer = strdup(str);
    if (buffer == NULL) { return NULL; }
    for (int i = 0; buffer[i] != '\0'; i++) { buffer[i] = toupper((unsigned char)buffer[i]); }
    return buffer;
}

static struct ModOption* djui_panel_mod_options_get(struct DjuiBase* caller) {
    struct ModOptions* modOptions = mod_options_find(sOptionsModPath);
    return mod_options_find_option(modOptions, (u16)caller->tag);
}

  /////////////
 // changes //
/////////////

// hand editing a value the preset owns deselects it, like toggling a mod does
static void djui_panel_mod_options_setting_changed(struct DjuiBase* caller) {
    if (mod_presets_active_owns_option(sOptionsModPath, (u16)caller->tag)) { mod_presets_set_active(NULL); }
    mod_options_mark_pending(sOptionsModPath, (u16)caller->tag);

    // reachable in-game through the pause menu, so hand it to the mod now if it is running
    mod_options_apply_pending();
    mod_options_save();
}

static void djui_panel_mod_options_inputbox_changed(struct DjuiBase* caller) {
    struct ModOption* option = djui_panel_mod_options_get(caller);
    if (option == NULL) { return; }

    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)caller;
    free(option->stringValue);
    option->stringValue = sys_strdup(inputbox->buffer);
    djui_panel_mod_options_setting_changed(caller);
}

  /////////////
 // widgets //
/////////////

static void djui_panel_mod_options_add_option(struct DjuiBase* layoutBase, struct ModOption* option) {
    const char* label = (option->label != NULL && option->label[0] != '\0') ? option->label : "-";

    switch (option->type) {
        case MOD_PRESET_SETTING_CHECKBOX: {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(layoutBase, label, &option->boolValue, djui_panel_mod_options_setting_changed);
            checkbox->base.tag = option->index;
            break;
        }
        case MOD_PRESET_SETTING_SLIDER: {
            struct DjuiSlider* slider = djui_slider_create(layoutBase, label, &option->uintValue, option->sliderMin, option->sliderMax, djui_panel_mod_options_setting_changed);
            slider->base.tag = option->index;
            break;
        }
        case MOD_PRESET_SETTING_INPUTBOX: {
            struct DjuiRect* rect = djui_rect_container_create(layoutBase, 32);
            {
                struct DjuiText* text = djui_text_create(&rect->base, label);
                djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_color(&text->base, 220, 220, 220, 255);
                djui_base_set_size(&text->base, 0.585f, 64);
                djui_base_set_alignment(&text->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
                djui_text_set_drop_shadow(text, 64, 64, 64, 100);

                u16 capacity = (option->length > 0 && option->length <= 256) ? (u16)option->length : 256;
                struct DjuiInputbox* inputbox = djui_inputbox_create(&rect->base, capacity);
                djui_base_set_size_type(&inputbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_size(&inputbox->base, 0.45f, 32);
                djui_base_set_alignment(&inputbox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
                djui_inputbox_set_text(inputbox, option->stringValue ? option->stringValue : "");
                djui_interactable_hook_value_change(&inputbox->base, djui_panel_mod_options_inputbox_changed);
                inputbox->base.tag = option->index;
            }
            break;
        }
        default: break;
    }
}

  ///////////
 // panel //
///////////

void djui_panel_mod_options_create(struct DjuiBase* caller) {
    if (caller->tag < 0 || caller->tag >= gLocalMods.entryCount) { return; }
    struct Mod* mod = gLocalMods.entries[caller->tag];

    struct ModOptions* modOptions = mod_options_find(mod->relativePath);
    if (modOptions == NULL || modOptions->count == 0) { return; }
    snprintf(sOptionsModPath, SYS_MAX_PATH, "%s", mod->relativePath);

    // the gear's hover left the option list in the side pane, put the description back
    djui_panel_host_mods_describe_mod(caller->tag);

    char uncolored[MOD_NAME_SIZE] = { 0 };
    djui_text_get_uncolored_string(uncolored, MOD_NAME_SIZE, mod->name);
    char* title = to_uppercase(uncolored);
    struct DjuiThreePanel* panel = djui_panel_menu_create(title ? title : mod->name, true);
    free(title);

    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, MOD_OPTIONS_PER_PAGE);
        struct DjuiBase* layoutBase = &paginated->layout->base;
        for (u16 i = 0; i < modOptions->count; i++) {
            djui_panel_mod_options_add_option(layoutBase, &modOptions->options[i]);
        }
        djui_paginated_calculate_height(paginated);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        djui_three_panel_recalculate_body_size(panel);
    }

    djui_panel_add(caller, panel, NULL);
}
