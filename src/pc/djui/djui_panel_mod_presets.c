#include <stdio.h>
#include <string.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_confirm.h"
#include "djui_panel_host_mods.h"
#include "djui_panel_mod_presets.h"
#include "pc/configfile.h"
#include "pc/network/network.h"
#include "pc/mods/mod_presets.h"

#define MOD_PRESETS_PER_PAGE 6

static struct DjuiPanel* sPresetPanel = NULL;
static struct DjuiFlowLayout* sPresetLayout = NULL;
static struct DjuiPaginated* sPresetPaginated = NULL;
static struct DjuiInputbox* sPresetNameTextBox = NULL;
static struct DjuiButton* sSaveButton = NULL;
static char sPendingDeleteName[MOD_PRESET_NAME_SIZE] = { 0 };

static void djui_panel_mod_presets_add_presets(struct DjuiBase* layoutBase);

static void djui_panel_mod_presets_rebuild(void) {
    if (sPresetLayout == NULL) { return; }

    // the panel remembers the row that opened the confirm, and we are about to free it
    if (sPresetPanel != NULL) { sPresetPanel->defaultElementBase = NULL; }

    djui_base_destroy_children(&sPresetLayout->base);
    djui_panel_mod_presets_add_presets(&sPresetLayout->base);
    djui_paginated_calculate_height(sPresetPaginated);

    // the save button outlives every rebuild
    if (sPresetPanel != NULL && sSaveButton != NULL) {
        sPresetPanel->defaultElementBase = &sSaveButton->base;
    }
}

  /////////////
 // actions //
/////////////

static void djui_panel_mod_presets_apply(struct DjuiBase* caller) {
    if (caller->tag < 0 || caller->tag >= gModPresetCount) { return; }

    mod_preset_apply(&gModPresets[caller->tag]);
    djui_panel_host_mods_rebuild_list();
    djui_panel_menu_back(caller);
}

static void djui_panel_mod_presets_delete_yes(struct DjuiBase* caller) {
    mod_preset_delete(sPendingDeleteName);
    sPendingDeleteName[0] = '\0';
    djui_panel_mod_presets_rebuild();
    djui_panel_host_mods_rebuild_list();
    djui_panel_menu_back(caller);
}

static void djui_panel_mod_presets_delete(struct DjuiBase* caller) {
    if (caller->tag < 0 || caller->tag >= gModPresetCount) { return; }

    snprintf(sPendingDeleteName, MOD_PRESET_NAME_SIZE, "%s", gModPresets[caller->tag].name);

    char message[256] = { 0 };
    djui_language_replace(DLANG(MOD_PRESETS, DELETE_CONFIRM), message, 256, '@', sPendingDeleteName);
    djui_panel_confirm_create(caller, DLANG(MOD_PRESETS, DELETE_PRESET), message, djui_panel_mod_presets_delete_yes);
}

static void djui_panel_mod_presets_save(UNUSED struct DjuiBase* caller) {
    if (sPresetNameTextBox == NULL) { return; }
    if (!mod_preset_name_valid(sPresetNameTextBox->buffer)) {
        djui_interactable_set_input_focus(&sPresetNameTextBox->base);
        djui_inputbox_select_all(sPresetNameTextBox);
        return;
    }

    if (!mod_preset_save(sPresetNameTextBox->buffer)) {
        djui_popup_create(DLANG(MOD_PRESETS, SAVE_FAILED), 1);
        return;
    }

    char message[256] = { 0 };
    djui_language_replace(DLANG(MOD_PRESETS, SAVED), message, 256, '@', sPresetNameTextBox->buffer);
    djui_popup_create(message, 2);

    djui_panel_mod_presets_rebuild();
    djui_panel_host_mods_rebuild_list();
}

  ////////////////
 // preset row //
////////////////

// the side panel previews whichever preset the cursor is over
static void djui_panel_mod_presets_row_hover(struct DjuiBase* base) {
    if (base->tag < 0 || base->tag >= gModPresetCount) { return; }
    djui_panel_host_mods_preview_preset(&gModPresets[base->tag]);
}

static void djui_panel_mod_presets_row_hover_end(UNUSED struct DjuiBase* base) {
    djui_panel_host_mods_preview_preset(NULL);
}

static void djui_panel_mod_presets_add_presets(struct DjuiBase* layoutBase) {
    if (gModPresetCount == 0) {
        struct DjuiText* text = djui_text_create(layoutBase, DLANG(MOD_PRESETS, NO_PRESETS_FOUND));
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, 32);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        return;
    }

    for (u16 i = 0; i < gModPresetCount; i++) {
        struct ModPreset* preset = &gModPresets[i];
        bool active = !sys_strcasecmp(configModPreset, preset->name);

        char label[MOD_PRESET_NAME_SIZE + 32] = { 0 };
        if (active) {
            snprintf(label, sizeof(label), "\\#ffe060\\%s", preset->name);
        } else {
            snprintf(label, sizeof(label), "%s", preset->name);
        }

        struct DjuiRect* row = djui_rect_container_create(layoutBase, 32);
        {
            struct DjuiButton* applyButton = djui_button_create(&row->base, label, DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_presets_apply);
            // a client's mods come from the host, so there is nothing here for a preset to apply
            if (gNetworkType == NT_CLIENT) { djui_base_set_enabled(&applyButton->base, false); }
            djui_base_set_size(&applyButton->base, 0.76f, 32);
            djui_base_set_alignment(&applyButton->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            applyButton->base.tag = i;
            djui_interactable_hook_hover(&applyButton->base, djui_panel_mod_presets_row_hover, djui_panel_mod_presets_row_hover_end);

            struct DjuiButton* deleteButton = djui_button_create(&row->base, DLANG(MOD_PRESETS, DELETE), DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_presets_delete);
            djui_base_set_size(&deleteButton->base, 0.22f, 32);
            djui_base_set_alignment(&deleteButton->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            deleteButton->base.tag = i;
            djui_interactable_hook_hover(&deleteButton->base, djui_panel_mod_presets_row_hover, djui_panel_mod_presets_row_hover_end);
        }
    }
}

  ////////////////
 // name field //
////////////////

static void djui_panel_mod_presets_name_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)caller;
    struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
    struct DjuiColor* textColor = &theme->interactables.textColor;
    if (mod_preset_name_valid(inputbox->buffer)) {
        djui_inputbox_set_text_color(inputbox, textColor->r, textColor->g, textColor->b, textColor->a);
    } else {
        djui_inputbox_set_text_color(inputbox, 255, 0, 0, 255);
    }
}

  ///////////
 // panel //
///////////

static void djui_panel_mod_presets_destroy(UNUSED struct DjuiBase* caller) {
    sPresetPanel = NULL;
    sPresetLayout = NULL;
    sPresetPaginated = NULL;
    sPresetNameTextBox = NULL;
    sSaveButton = NULL;
}

void djui_panel_mod_presets_create(struct DjuiBase* caller) {
    mod_presets_refresh();

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MOD_PRESETS, MOD_PRESETS), true);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, MOD_PRESETS_PER_PAGE);
        paginated->showMaxCount = true;
        sPresetLayout = paginated->layout;
        sPresetPaginated = paginated;
        djui_panel_mod_presets_add_presets(&paginated->layout->base);
        djui_paginated_calculate_height(paginated);

        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(MOD_PRESETS, PRESET_NAME));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 220, 220, 220, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, MOD_PRESET_NAME_SIZE);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.45f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_inputbox_set_text(inputbox1, configModPreset);
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_mod_presets_name_text_change);
            sPresetNameTextBox = inputbox1;
            djui_panel_mod_presets_name_text_change(&inputbox1->base);
        }

        struct DjuiRect* rect2 = djui_rect_container_create(body, 45);
        {
            sSaveButton = djui_button_create(&rect2->base, DLANG(MOD_PRESETS, SAVE_PRESET), DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_presets_save);
            djui_base_set_size(&sSaveButton->base, 1.0f, 45);
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        djui_three_panel_recalculate_body_size(panel);
    }

    // the focus picker only skips elements whose interactable is disabled, so point it away
    // from the apply buttons that are greyed out for a client
    struct DjuiBase* defaultElement = (gNetworkType == NT_CLIENT) ? &sSaveButton->base : NULL;
    struct DjuiPanel* p = djui_panel_add(caller, panel, defaultElement);
    if (!p) { return; }
    p->on_panel_destroy = djui_panel_mod_presets_destroy;
    sPresetPanel = p;
}
