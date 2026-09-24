#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/mods/mod_presets.h"
#include "pc/mods/mod_options.h"
#include "djui_panel_main.h"
#include "djui_panel_host.h"
#include "djui_panel_host_mods.h"
#include "djui_panel_mod_presets.h"
#include "djui_panel_mod_options.h"
#include "djui_panel_pause.h"
#include "pc/thread.h"

#define DJUI_MOD_PANEL_WIDTH (410.0f + (16 * 2.0f))

#define DJUI_MOD_ICON_SIZE 22
#define DJUI_MOD_GEAR_SIZE 18
#define DJUI_MOD_ICON_HIT_WIDTH 26
#define DJUI_MOD_PRESET_LIST_MAX 12
#define DJUI_MOD_OPTION_LIST_MAX 12
#define DJUI_MOD_OPTION_LINE_MAX 34
#define DJUI_MOD_OPTION_VALUE_MAX 12

extern ALIGNED8 const Texture texture_hud_char_star[];
extern ALIGNED8 const Texture texture_gear_icon[];

struct ModCategory {
    const char* langKey;
    const char* category;
};

struct ModCategory sCategories[] = {
#define MOD_CATEGORY_DEF(key) { #key, NULL },
#define MOD_CATEGORY(key, category) { #key, category },
#include "mod_categories.inl"
#undef MOD_CATEGORY_DEF
#undef MOD_CATEGORY
};

enum ModCategories {
#define MOD_CATEGORY_DEF(key) MOD_CATEGORY_ ## key,
#define MOD_CATEGORY(key, category)
#include "mod_categories.inl"
#undef MOD_CATEGORY_DEF
#undef MOD_CATEGORY

    MOD_CATEGORY_START,
    MOD_CATEGORY_COUNT = ARRAY_COUNT(sCategories)
};

static struct DjuiFlowLayout* sModLayout = NULL;
static struct DjuiThreePanel* sDescriptionPanel = NULL;
static struct DjuiText* sTooltip = NULL;
static struct DjuiPaginated* sModPaginated = NULL;
static struct DjuiButton* sBackButton = NULL;
static struct DjuiButton* sRefreshButton = NULL;
static struct DjuiButton* sPresetButton = NULL;
static struct DjuiInputbox* sSearchInputbox = NULL;
static unsigned int sSelectedCategory = MOD_CATEGORY_ALL;
static bool sWarned = false;

struct ThreadHandle gModRefreshThread = { 0 };

void djui_panel_host_mods_create(struct DjuiBase* caller);

static void djui_panel_host_mods_description_create(void) {
    f32 bodyHeight = 1000;

    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    struct DjuiThreePanelTheme theme = gDjuiThemes[configDjuiTheme]->threePanels;

    djui_base_set_alignment(&panel->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, DJUI_MOD_PANEL_WIDTH, 1.0f);
    djui_base_set_color(&panel->base, theme.rectColor.r, theme.rectColor.g, theme.rectColor.b, theme.rectColor.a);
    djui_base_set_border_color(&panel->base, theme.borderColor.r, theme.borderColor.g, theme.borderColor.b, theme.borderColor.a);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    {
        struct DjuiFlowLayout* body = djui_flow_layout_create(&panel->base);
        djui_base_set_alignment(&body->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&body->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&body->base, 1.0f, 1.0f);
        djui_base_set_color(&body->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(body, 16);
        djui_flow_layout_set_flow_direction(body, DJUI_FLOW_DIR_DOWN);

        struct DjuiText* description = djui_text_create(&panel->base, "");
        djui_base_set_size_type(&description->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&description->base, 1.0f, 1.0f);
        djui_base_set_color(&description->base, 222, 222, 222, 255);
        djui_text_set_alignment(description, DJUI_HALIGN_LEFT, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(description, 64, 64, 64, 100);
        sTooltip = description;
    }
    sDescriptionPanel = panel;
}

static struct Mod* djui_panel_host_mods_find(const char* relativePath) {
    for (u16 i = 0; i < gLocalMods.entryCount; i++) {
        if (!strcmp(gLocalMods.entries[i]->relativePath, relativePath)) { return gLocalMods.entries[i]; }
    }

    return NULL;
}

// names a preset in the description panel and lists what it holds. NULL falls back to the
// preset that is currently picked, which is what shows with nothing hovered.
void djui_panel_host_mods_preview_preset(struct ModPreset* preset) {
    if (sTooltip == NULL) { return; }

    if (preset == NULL) { preset = mod_presets_get_active(); }
    if (preset == NULL) {
        djui_text_set_text(sTooltip, "");
        return;
    }

    bool active = !sys_strcasecmp(configModPreset, preset->name);
    char text[1024] = { 0 };
    djui_language_replace(active ? DLANG(MOD_PRESETS, PRESET_TITLE_SELECTED) : DLANG(MOD_PRESETS, PRESET_TITLE),
                          text, sizeof(text), '@', preset->name);

    char uncolored[MOD_NAME_SIZE] = { 0 };
    char line[MOD_NAME_SIZE + 64] = { 0 };
    size_t length = strlen(text);

    for (u16 i = 0; i < preset->modCount; i++) {
        const char* separator = (i == 0) ? "\n\n" : "\n";

        if (i >= DJUI_MOD_PRESET_LIST_MAX) {
            char count[16] = { 0 };
            snprintf(count, sizeof(count), "%d", preset->modCount - i);
            djui_language_replace(DLANG(MOD_PRESETS, MORE_MODS), line, sizeof(line), '@', count);
            snprintf(text + length, sizeof(text) - length, "%s\\#909090\\%s", separator, line);
            break;
        }

        // by name where the mod is installed, colour codes stripped so the list reads evenly
        struct Mod* mod = djui_panel_host_mods_find(preset->modPaths[i]);
        int written;
        if (mod != NULL) {
            djui_text_get_uncolored_string(uncolored, MOD_NAME_SIZE, mod->name);
            written = snprintf(text + length, sizeof(text) - length, "%s\\#c8c8c8\\%s", separator, uncolored);
        } else {
            written = snprintf(text + length, sizeof(text) - length, "%s\\#d09090\\%s %s",
                               separator, preset->modPaths[i], DLANG(MOD_PRESETS, MOD_MISSING));
        }

        if (written < 0) { break; }
        length += (size_t)written;
        if (length >= sizeof(text) - 1) { break; }
    }

    djui_text_set_text(sTooltip, text);
}

// also used by the options panel, which keeps the mod's description up while it is open
void djui_panel_host_mods_describe_mod(s64 index) {
    if (sTooltip == NULL) { return; }

    char* description = "";
    if (index >= 0 && index < gLocalMods.entryCount) {
        struct Mod* mod = gLocalMods.entries[index];
        char* d = mod->description;
        if (d != NULL) {
            description = mod->description;
        }
    }
    djui_text_set_text(sTooltip, description);
}

static void djui_mod_checkbox_on_hover(struct DjuiBase* base) {
    djui_panel_host_mods_describe_mod(base->tag);
}

static void djui_mod_checkbox_on_hover_end(UNUSED struct DjuiBase* base) {
    djui_panel_host_mods_preview_preset(NULL);
}

static void djui_panel_host_mods_update_selectable_rows(void) {
    if (sModLayout == NULL) { return; }

    struct DjuiBaseChild* node = sModLayout->base.child;
    while (node != NULL) {
        struct DjuiBase* rowBase = node->base;
        if (rowBase->tag >= 0 && rowBase->tag < gLocalMods.entryCount) {
            struct Mod* mod = gLocalMods.entries[rowBase->tag];

            // bTag marks the row's enable checkbox
            struct DjuiBaseChild* rowNode = rowBase->child;
            while (rowNode != NULL) {
                if (rowNode->base->bTag) {
                    djui_base_set_enabled(rowNode->base, mod->selectable);
                }
                rowNode = rowNode->next;
            }
        }

        // iterate
        node = node->next;
    }
}

static void djui_mod_checkbox_on_value_change(UNUSED struct DjuiBase* base) {
    mods_update_selectable();

    // the enabled mods no longer describe the preset that was picked
    struct ModPreset* preset = mod_presets_get_active();
    if (preset != NULL && !mod_preset_matches_enabled_mods(preset)) {
        mod_presets_set_active(NULL);
        djui_panel_host_mods_preview_preset(NULL);
    }

    if (mods_get_enabled_count() >= 10) {
        if (!sWarned) {
            sWarned = true;
            djui_popup_create(DLANG(HOST_MODS, WARNING), 3);
        }
    } else {
        sWarned = false;
    }

    // under the enabled filter the row no longer belongs in the list, same as unfavoriting does
    // under the favorites filter
    if (sSelectedCategory == MOD_CATEGORY_ENABLED) {
        djui_panel_host_mods_rebuild_list();
        return;
    }

    djui_panel_host_mods_update_selectable_rows();
}

  ///////////////
 // row icons //
///////////////

// bare image on a transparent hit area, so no button box is drawn around it
static struct DjuiBase* djui_mod_icon_image(struct DjuiBase* base) {
    return (base->child != NULL) ? base->child->base : NULL;
}

static bool djui_mod_icon_highlighted(struct DjuiBase* base) {
    return gDjuiHovered == base || gDjuiCursorDownOn == base;
}

static void djui_mod_favorite_update_style(struct DjuiBase* base) {
    struct DjuiBase* image = djui_mod_icon_image(base);
    if (image == NULL) { return; }
    if (base->tag < 0 || base->tag >= gLocalMods.entryCount) { return; }

    // the star texture is already gold, a white tint shows its own colour
    if (gLocalMods.entries[base->tag]->favorited) {
        djui_base_set_color(image, 255, 255, 255, 255);
    } else if (djui_mod_icon_highlighted(base)) {
        djui_base_set_color(image, 150, 200, 255, 210);
    } else {
        djui_base_set_color(image, 90, 145, 235, 140);
    }
}

// the gear shows for any mod that hooks menu elements, but there is nothing to edit until the
// mod has run once and listed them, so until then it sits dimmed and inert
static bool djui_mod_options_recorded(struct DjuiBase* base) {
    if (base->tag < 0 || base->tag >= gLocalMods.entryCount) { return false; }
    return mod_options_has_any(gLocalMods.entries[base->tag]->relativePath);
}

static void djui_mod_options_update_style(struct DjuiBase* base) {
    struct DjuiBase* image = djui_mod_icon_image(base);
    if (image == NULL) { return; }

    if (!djui_mod_options_recorded(base)) {
        djui_base_set_color(image, 165, 165, 165, 128);
        return;
    }

    u8 v = djui_mod_icon_highlighted(base) ? 240 : 165;
    djui_base_set_color(image, v, v, v, 255);
}

static void djui_mod_options_on_click(struct DjuiBase* base) {
    if (!djui_mod_options_recorded(base)) { return; }
    djui_panel_mod_options_create(base);
}

// the description panel clips rather than wraps, so each line is cut to fit its width
static void djui_mod_option_clamp(char* destination, size_t capacity, const char* source, size_t maxLength) {
    if (strlen(source) <= maxLength) {
        snprintf(destination, capacity, "%s", source);
        return;
    }
    snprintf(destination, capacity, "%.*s...", (int)(maxLength - 3), source);
}

// reads the recorded options out in the description panel, values only
static void djui_mod_options_on_hover(struct DjuiBase* base) {
    if (sTooltip == NULL) { return; }
    if (base->tag < 0 || base->tag >= gLocalMods.entryCount) { return; }
    struct Mod* mod = gLocalMods.entries[base->tag];

    char name[MOD_NAME_SIZE] = { 0 };
    djui_text_get_uncolored_string(name, MOD_NAME_SIZE, mod->name);

    char text[1024] = { 0 };
    djui_language_replace(DLANG(MOD_OPTIONS, OPTIONS_TITLE), text, sizeof(text), '@', name);
    size_t length = strlen(text);

    struct ModOptions* modOptions = mod_options_find(mod->relativePath);
    if (modOptions == NULL || modOptions->count == 0) {
        snprintf(text + length, sizeof(text) - length, "\n\n%s", DLANG(MOD_OPTIONS, NOT_RECORDED));
        djui_text_set_text(sTooltip, text);
        return;
    }

    char value[64] = { 0 };
    for (u16 i = 0; i < modOptions->count; i++) {
        const char* separator = (i == 0) ? "\n\n" : "\n";

        if (i >= DJUI_MOD_OPTION_LIST_MAX) {
            char count[16] = { 0 };
            char line[64] = { 0 };
            snprintf(count, sizeof(count), "%d", modOptions->count - i);
            djui_language_replace(DLANG(MOD_OPTIONS, MORE_OPTIONS), line, sizeof(line), '@', count);
            snprintf(text + length, sizeof(text) - length, "%s\\#909090\\%s", separator, line);
            break;
        }

        struct ModOption* option = &modOptions->options[i];
        char raw[256] = { 0 };
        switch (option->type) {
            case MOD_PRESET_SETTING_CHECKBOX:
                snprintf(raw, sizeof(raw), "%s", option->boolValue ? DLANG(MOD_OPTIONS, ON) : DLANG(MOD_OPTIONS, OFF));
                break;
            case MOD_PRESET_SETTING_SLIDER:
                snprintf(raw, sizeof(raw), "%u", option->uintValue);
                break;
            case MOD_PRESET_SETTING_INPUTBOX:
                snprintf(raw, sizeof(raw), "%s", (option->stringValue != NULL) ? option->stringValue : "");
                break;
            default: continue;
        }
        djui_mod_option_clamp(value, sizeof(value), raw, DJUI_MOD_OPTION_VALUE_MAX);

        char label[128] = { 0 };
        djui_text_get_uncolored_string(raw, sizeof(raw), (option->label != NULL) ? option->label : "-");
        djui_mod_option_clamp(label, sizeof(label), raw, DJUI_MOD_OPTION_LINE_MAX - 2 - strlen(value));

        int written = snprintf(text + length, sizeof(text) - length, "%s\\#c8c8c8\\%s  \\#ffffff\\%s",
                               separator, label, value);
        if (written < 0) { break; }
        length += (size_t)written;
        if (length >= sizeof(text) - 1) { break; }
    }

    djui_text_set_text(sTooltip, text);
}

static struct DjuiRect* djui_mod_icon_create(struct DjuiBase* parent, const Texture* texture, f32 iconSize, s64 tag,
                                             void (*update_style)(struct DjuiBase*),
                                             void (*on_click)(struct DjuiBase*)) {
    struct DjuiRect* hit = djui_rect_create(parent);
    djui_base_set_size_type(&hit->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&hit->base, DJUI_MOD_ICON_HIT_WIDTH, 32);
    djui_base_set_color(&hit->base, 0, 0, 0, 0);
    hit->base.tag = tag;

    struct DjuiImage* image = djui_image_create(&hit->base, texture, 16, 16, G_IM_FMT_RGBA, G_IM_SIZ_16b);
    djui_base_set_size_type(&image->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&image->base, iconSize, iconSize);
    djui_base_set_alignment(&image->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

    djui_interactable_create(&hit->base, update_style);
    djui_interactable_hook_click(&hit->base, on_click);
    update_style(&hit->base);

    return hit;
}

static void djui_mod_favorite_on_click(struct DjuiBase* base) {
    if (base->tag < 0 || base->tag >= gLocalMods.entryCount) { return; }

    struct Mod* mod = gLocalMods.entries[base->tag];
    mod->favorited = !mod->favorited;

    // under the favorites filter the row no longer belongs in the list at all. anywhere else it
    // is left in place on purpose, rows shouldn't move out from under the cursor
    if (sSelectedCategory == MOD_CATEGORY_FAVORITES) {
        djui_panel_host_mods_rebuild_list();
        return;
    }

    djui_mod_favorite_update_style(base);
}

static void djui_panel_host_mods_destroy(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;
    free(threePanel);

    if (sDescriptionPanel != NULL) {
        djui_base_destroy(&sDescriptionPanel->base);
        sDescriptionPanel = NULL;
    }
    sModLayout = NULL;
    sModPaginated = NULL;
    sSearchInputbox = NULL;
    sBackButton = NULL;
    sRefreshButton = NULL;
    sPresetButton = NULL;
    sTooltip = NULL;
}

bool should_add_mod_to_list(struct Mod* mod, const char* category) {
    switch (sSelectedCategory) {
        case MOD_CATEGORY_ALL: { return true; }
        case MOD_CATEGORY_ENABLED: { return mod->enabled; }
        case MOD_CATEGORY_FAVORITES: { return mod->favorited; }
        case MOD_CATEGORY_MISC: {
            if (category) {
                for (int i = MOD_CATEGORY_START; i < MOD_CATEGORY_COUNT; i++) {
                    if (strstr(category, sCategories[i].category)) {
                        return false;
                    }
                }
            }
            return true;
        }
        default: {
            return category && strstr(category, sCategories[sSelectedCategory].category);
        }
    }
}

static void djui_panel_host_mods_add_mod_row(struct DjuiBase* layoutBase, int index) {
    struct Mod* mod = gLocalMods.entries[index];
    bool hasOptions = mod->hasModMenu || mod_options_has_any(mod->relativePath);

    struct DjuiRect* row = djui_rect_container_create(layoutBase, 32);
    row->base.tag = index;
    {
        struct DjuiRect* favorite = djui_mod_icon_create(&row->base, texture_hud_char_star, DJUI_MOD_ICON_SIZE, index,
                                                         djui_mod_favorite_update_style, djui_mod_favorite_on_click);
        djui_base_set_alignment(&favorite->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_CENTER);
        djui_interactable_hook_hover(&favorite->base, djui_mod_checkbox_on_hover, djui_mod_checkbox_on_hover_end);

        struct DjuiCheckbox* checkbox = djui_checkbox_create(&row->base, mod->name, &mod->enabled, djui_mod_checkbox_on_value_change);
        djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox->base, 0.925f, 32);
        djui_base_set_alignment(&checkbox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
        checkbox->base.tag = index;
        checkbox->base.bTag = true;
        djui_base_set_enabled(&checkbox->base, mod->selectable);
        djui_interactable_hook_hover(&checkbox->base, djui_mod_checkbox_on_hover, djui_mod_checkbox_on_hover_end);

        // keep long mod names clear of the gear
        if (hasOptions) { djui_base_set_size(&checkbox->text->base, 0.82f, 1.0f); }

        // after the checkbox, so it wins the cursor where they overlap
        if (hasOptions) {
            struct DjuiRect* options = djui_mod_icon_create(&row->base, texture_gear_icon, DJUI_MOD_GEAR_SIZE, index,
                                                            djui_mod_options_update_style, djui_mod_options_on_click);
            djui_base_set_alignment(&options->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
            djui_base_set_location(&options->base, DJUI_MOD_ICON_HIT_WIDTH + 10, 0);
            djui_interactable_hook_hover(&options->base, djui_mod_options_on_hover, djui_mod_checkbox_on_hover_end);
        }
    }
}

void djui_panel_host_mods_add_mods(struct DjuiBase* layoutBase) {
    bool foundAny = false;

    // favorited mods are listed first
    for (int pass = 0; pass < 2; pass++) {
        for (int i = 0; i < gLocalMods.entryCount; i++) {
            struct Mod* mod = gLocalMods.entries[i];
            if (mod->favorited != (pass == 0)) { continue; }

            char* category = mod->category != NULL ? mod->category : mod->incompatible;
            if (category != NULL) {
                category = !strcmp(category, "cs") ? "character" : category;
            }

            if (!should_add_mod_to_list(mod, category)) { continue; }

            // filter results
            if (sSearchInputbox != NULL &&
                sSearchInputbox->buffer != NULL &&
                !strstr_lowercased(djui_text_get_uncolored_string(NULL, strlen(mod->name) + 1, mod->name), sSearchInputbox->buffer)
            ) {
                continue;
            }

            djui_panel_host_mods_add_mod_row(layoutBase, i);
            foundAny = true;
        }
    }

    if (!foundAny) {
        struct DjuiText* text = djui_text_create(layoutBase, DLANG(HOST_MODS, NO_MODS_FOUND));
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&text->base, 1, 1);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    }
}

static void djui_panel_rebuild_mods_list(UNUSED struct DjuiBase* caller) {
    if (sModLayout == NULL) { return; }
    if (gModRefreshThread.state == RUNNING) { return; }
    djui_base_destroy_children(&sModLayout->base);
    djui_panel_host_mods_add_mods(&sModLayout->base);
    djui_paginated_calculate_height(sModPaginated);
}

void djui_panel_host_mods_rebuild_list(void) {
    djui_panel_rebuild_mods_list(NULL);
    djui_panel_host_mods_preview_preset(NULL);
}

static void* threaded_mod_refresh(UNUSED void* unused) {
    mods_refresh_local();

    if (gModRefreshThread.state == RUNNING) { join_thread(&gModRefreshThread); }

    mods_update_selectable();
    djui_panel_host_mods_add_mods(&sModLayout->base);
    djui_paginated_calculate_height(sModPaginated);

    djui_text_set_text(sRefreshButton->text, DLANG(LOBBIES, REFRESH));
    djui_base_set_enabled(&sRefreshButton->base, true);
    djui_base_set_enabled(&sBackButton->base, true);
    if (sPresetButton != NULL) { djui_base_set_enabled(&sPresetButton->base, true); }
    gDjuiPanelDisableBack = false;

    return NULL;
}

static void djui_panel_menu_refresh(UNUSED struct DjuiBase* base) {
    djui_base_destroy_children(&sModLayout->base);
    if (init_thread_handle(&gModRefreshThread, threaded_mod_refresh, NULL, NULL, 0) == 0) {
        djui_text_set_text(sRefreshButton->text, DLANG(LOBBIES, REFRESHING));
        djui_base_set_enabled(&sRefreshButton->base, false);
        djui_base_set_enabled(&sBackButton->base, false);
        // applying or saving a preset walks gLocalMods, which the worker thread is freeing
        if (sPresetButton != NULL) { djui_base_set_enabled(&sPresetButton->base, false); }
        gDjuiPanelDisableBack = true;
    } else {
        threaded_mod_refresh(NULL);
    }
}

static void djui_mod_website_open(UNUSED struct DjuiBase* caller) {
    open_url("https://mods.sm64coopdx.com/mods/");
}

static void djui_mod_folder_open(UNUSED struct DjuiBase* caller) {
    open_folder(fs_get_write_path("/mods"));
}

void djui_panel_host_mods_create(struct DjuiBase* caller) {

    mods_update_selectable();
    djui_panel_host_mods_description_create();
    djui_panel_host_mods_preview_preset(NULL);

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(HOST_MODS, MODS), true);

    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiSearchbox* searchbox = djui_searchbox_create(body, djui_panel_rebuild_mods_list);
        sSearchInputbox = searchbox->inputbox;

        char* categoryChoices[MOD_CATEGORY_COUNT];
        for (int i = 0; i < MOD_CATEGORY_COUNT; i++) {
            categoryChoices[i] = djui_language_get("HOST_MOD_CATEGORIES", sCategories[i].langKey);
        }
        djui_selectionbox_create(body, DLANG(HOST_MODS, CATEGORIES), categoryChoices, MOD_CATEGORY_COUNT, &sSelectedCategory, djui_panel_rebuild_mods_list);

        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        paginated->showMaxCount = true;
        sModLayout = paginated->layout;
        djui_panel_host_mods_add_mods(&paginated->layout->base);
        djui_paginated_calculate_height(paginated);
        sModPaginated = paginated;

        if (gNetworkType == NT_NONE) {
            struct DjuiRect* rect1 = djui_rect_container_create(body, 45);
            struct DjuiRect* rect2 = djui_rect_container_create(body, 45);
            {
                sBackButton = djui_button_left_create(&rect1->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
                sPresetButton = djui_button_create(&rect1->base, DLANG(MOD_PRESETS, PRESETS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_presets_create);
                sRefreshButton = djui_button_right_create(&rect1->base, DLANG(LOBBIES, REFRESH), DJUI_BUTTON_STYLE_NORMAL, djui_panel_menu_refresh);
                djui_base_set_size(&sBackButton->base, 0.32f, 45);
                djui_base_set_size(&sPresetButton->base, 0.32f, 45);
                djui_base_set_alignment(&sPresetButton->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
                djui_base_set_size(&sRefreshButton->base, 0.32f, 45);

                struct DjuiButton* button1 = djui_button_left_create(&rect2->base, DLANG(HOST_MODS, BROWSE_MODS), DJUI_BUTTON_STYLE_NORMAL, djui_mod_website_open);
                struct DjuiButton* button2 = djui_button_right_create(&rect2->base, DLANG(HOST_MODS, OPEN_MOD_FOLDER), DJUI_BUTTON_STYLE_NORMAL, djui_mod_folder_open);
                djui_base_set_size(&button1->base, 0.485f, 45);
                djui_base_set_size(&button2->base, 0.485f, 45);
            }
        } else {
            struct DjuiRect* rect1 = djui_rect_container_create(body, 45);
            {
                sBackButton = djui_button_left_create(&rect1->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
                sPresetButton = djui_button_right_create(&rect1->base, DLANG(MOD_PRESETS, PRESETS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_presets_create);
                djui_base_set_size(&sBackButton->base, 0.485f, 45);
                djui_base_set_size(&sPresetButton->base, 0.485f, 45);
            }
        }

        djui_three_panel_recalculate_body_size(panel);
    }

    panel->base.destroy = djui_panel_host_mods_destroy;

    djui_panel_add(caller, panel, NULL);
}
