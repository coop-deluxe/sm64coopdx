#include <ctype.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_mod_menu.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/mods/mods.h"

static u32 sModActive = 0;
static s32 sPanelsEntered = 0;
static const char *sCurrentPanelId = NULL;
static const char *sPanelHeaderTitle = NULL;
static bool sPanelHideBackButton = false;

void mod_menu_push_panel(const char *panelId, OPTIONAL const char *headerTitle, OPTIONAL bool hideBackButton) {
    if (sPanelsEntered > 0 && (u32)gLuaActiveMod->index == sModActive) {
        sCurrentPanelId = panelId;
        sPanelHeaderTitle = headerTitle;
        sPanelHideBackButton = hideBackButton;
        djui_panel_mod_menu_mod_create(NULL);
        sCurrentPanelId = NULL;
        sPanelHeaderTitle = NULL;
        sPanelHideBackButton = false;
    }
}

void mod_menu_pop_panel(void) {
    if (sPanelsEntered > 0  && (u32)gLuaActiveMod->index == sModActive) {
        djui_panel_back();
    }
}

static char *to_uppercase(char *str) {
    char *buffer = strdup(str);
    int i = 0;
    while (buffer[i] != '\0') {
        buffer[i] = toupper(buffer[i]);
        i++;
    }
    return buffer;
}

void djui_panel_mod_menu_mod_button(struct DjuiBase *caller) {
    struct LuaHookedModMenuElement *modMenuElement = gHookedModMenuElements->buffer[caller->tag];
    smlua_call_mod_menu_element_hook(modMenuElement, caller->tag);
    struct DjuiButton *button = (struct DjuiButton *)caller;
    if (gHookedModMenuElements->count == 1) {
        char buffer[256] = { 0 };
        snprintf(buffer, 256, "%s - %s", modMenuElement->mod->name, modMenuElement->name);
        djui_text_set_text(button->text, buffer);
    } else {
        djui_text_set_text(button->text, modMenuElement->name);
    }
}

static void djui_panel_mod_menu_mod_checkbox(struct DjuiBase *caller) {
    struct LuaHookedModMenuElement *modMenuElement = gHookedModMenuElements->buffer[caller->tag];
    smlua_call_mod_menu_element_hook(modMenuElement, caller->tag);
    struct DjuiCheckbox *checkbox = (struct DjuiCheckbox *)caller;
    djui_text_set_text(checkbox->text, modMenuElement->name);
}

static void djui_panel_mod_menu_mod_slider(struct DjuiBase *caller) {
    struct LuaHookedModMenuElement *modMenuElement = gHookedModMenuElements->buffer[caller->tag];
    smlua_call_mod_menu_element_hook(modMenuElement, caller->tag);
    struct DjuiSlider *slider = (struct DjuiSlider *)caller;
    djui_text_set_text(slider->text, modMenuElement->name);
}

static void djui_panel_mod_menu_mod_inputbox(struct DjuiBase *caller) {
    struct DjuiInputbox *inputbox = (struct DjuiInputbox *)caller;
    struct LuaHookedModMenuElement *modMenuElement = gHookedModMenuElements->buffer[caller->tag];
    snprintf(modMenuElement->stringValue, sizeof(modMenuElement->stringValue), "%s", inputbox->buffer);
    smlua_call_mod_menu_element_hook(modMenuElement, caller->tag);
}

static void djui_panel_mod_menu_mod_selectionbox(struct DjuiBase *caller) {
    struct LuaHookedModMenuElement *modMenuElement = gHookedModMenuElements->buffer[caller->tag];
    smlua_call_mod_menu_element_hook(modMenuElement, caller->tag);
    struct DjuiSelectionbox *selectionbox = (struct DjuiSelectionbox *)caller;
    djui_text_set_text(selectionbox->text, modMenuElement->name);
}

static void djui_panel_mod_menu_mod_create_element(struct DjuiBase *parent, int i) {
    struct LuaHookedModMenuElement *modMenuElement = gHookedModMenuElements->buffer[i];
    switch (modMenuElement->element) {
        case MOD_MENU_ELEMENT_TEXT: {
            struct DjuiText *text = djui_text_create(parent, modMenuElement->name);
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text->base, 220, 220, 220, 255);
            djui_base_set_size(&text->base, 1.0f, 64);
            djui_base_set_alignment(&text->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text, 64, 64, 64, 100);
            text->base.tag = i;
            break;
        }
        case MOD_MENU_ELEMENT_BUTTON: {
            struct DjuiButton *button = djui_button_create(parent, modMenuElement->name, DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_menu_mod_button);
            button->base.tag = i;
            break;
        }
        case MOD_MENU_ELEMENT_CHECKBOX: {
            struct DjuiCheckbox *checkbox = djui_checkbox_create(parent, modMenuElement->name, &modMenuElement->boolValue, djui_panel_mod_menu_mod_checkbox);
            checkbox->base.tag = i;
            break;
        }
        case MOD_MENU_ELEMENT_SLIDER: {
            struct DjuiSlider *slider = djui_slider_create(parent, modMenuElement->name, &modMenuElement->uintValue, modMenuElement->sliderMin, modMenuElement->sliderMax, djui_panel_mod_menu_mod_slider);
            slider->base.tag = i;
            break;
        }
        case MOD_MENU_ELEMENT_INPUTBOX: {
            struct DjuiRect *rect = djui_rect_container_create(parent, 32);
            {
                struct DjuiText *text1 = djui_text_create(&rect->base, modMenuElement->name);
                djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_color(&text1->base, 220, 220, 220, 255);
                djui_base_set_size(&text1->base, 0.585f, 64);
                djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
                djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

                struct DjuiInputbox *inputbox = djui_inputbox_create(&rect->base, modMenuElement->length);
                djui_base_set_size_type(&inputbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_size(&inputbox->base, 0.45f, 32);
                djui_base_set_alignment(&inputbox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
                djui_inputbox_set_text(inputbox, modMenuElement->stringValue);
                djui_interactable_hook_value_change(&inputbox->base, djui_panel_mod_menu_mod_inputbox);
                inputbox->base.tag = i;
            }
            break;
        }
        case MOD_MENU_ELEMENT_SELECTIONBOX: {
            char *choices[MAX_MOD_MENU_ELEMENT_CHOICES];
            for (u32 i = 0; i < modMenuElement->choicesCount; i++) {
                choices[i] = modMenuElement->choices[i];
            }
            struct DjuiSelectionbox *selectionbox = djui_selectionbox_create(parent, modMenuElement->name, choices, modMenuElement->choicesCount, &modMenuElement->uintValue, djui_panel_mod_menu_mod_selectionbox);
            selectionbox->base.tag = i;
            break;
        }
        case MOD_MENU_ELEMENT_MAX: {
            break;
        }
    }
}

void djui_panel_mod_menu_mod_destroy(struct DjuiBase *base) {
    struct DjuiThreePanel *threePanel = (struct DjuiThreePanel *)base;
    free(threePanel);

    sPanelsEntered--;
    sCurrentPanelId = NULL;
}

void djui_panel_mod_menu_mod_create(struct DjuiBase *caller) {
    sPanelsEntered++;

    struct Mod *mod = NULL;
    if (caller) {
        for (int i = 0; i < gActiveMods.entryCount; i++) {
            if (gActiveMods.entries[i]->index == caller->tag) {
                mod = gActiveMods.entries[i];
                sModActive = i;
            }
        }
    } else {
        if (sModActive < 0 || sModActive >= gActiveMods.entryCount) { return; }
        mod = gActiveMods.entries[sModActive];
    }
    if (mod == NULL) { return; }

    char *headerTitle = NULL;
    if (sPanelHeaderTitle != NULL) {
        headerTitle = strdup(sPanelHeaderTitle);
    } else {
        headerTitle = to_uppercase(mod->name);
    }
    struct DjuiThreePanel *panel = djui_panel_menu_create(headerTitle, false);
    struct DjuiBase *body = djui_three_panel_get_body(panel);
    {
        // TODO: Implement scrolling so we don't need to paginate these elements.
        // This is currently extremely obnoxious
        struct DjuiPaginated *paginated = djui_paginated_create(body, 8);
        struct DjuiBase *layoutBase = &paginated->layout->base;
        for (u32 i = 0; i < gHookedModMenuElements->count; i++) {
            struct LuaHookedModMenuElement *modMenuElement = gHookedModMenuElements->buffer[i];
            if (modMenuElement->mod == mod && strcmp(modMenuElement->panelId, sCurrentPanelId != NULL ? sCurrentPanelId : "") == 0) {
                djui_panel_mod_menu_mod_create_element(layoutBase, i);
            }
        }
        djui_paginated_calculate_height(paginated);
        djui_base_set_size(layoutBase, layoutBase->width.value, 700);

        if (!sPanelHideBackButton) {
            djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
        }
    }

    panel->base.destroy = djui_panel_mod_menu_mod_destroy;
    djui_panel_add(caller, panel, NULL);
    free(headerTitle);
}

void djui_panel_mod_menu_create(struct DjuiBase *caller) {
    struct DjuiThreePanel *panel = djui_panel_menu_create(DLANG(PAUSE, MOD_MENU_TITLE), false);
    struct DjuiBase *body = djui_three_panel_get_body(panel);
    {
        struct DjuiPaginated *paginated = djui_paginated_create(body, 6);
        struct DjuiBase *layoutBase = &paginated->layout->base;
        struct Mod **addedMods = calloc(1, sizeof(struct Mod) * gHookedModMenuElements->count);
        int modCount = 0;
        growing_array_for_each_(gHookedModMenuElements, struct LuaHookedModMenuElement, modMenuElement) {
            bool shouldContinue = false;
            for (u32 i = 0; i < gHookedModMenuElements->count; i++) {
                if (addedMods[i] == NULL) { break; }
                if (addedMods[i] == modMenuElement->mod) {
                    shouldContinue = true;
                    break;
                }
            }
            if (shouldContinue) { continue; }

            struct DjuiButton *button = djui_button_create(layoutBase, modMenuElement->mod->name, DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_menu_mod_create);
            button->base.tag = modMenuElement->mod->index;
            addedMods[modCount++] = modMenuElement->mod;
        }
        free(addedMods);
        djui_paginated_calculate_height(paginated);
        djui_base_set_size(layoutBase, layoutBase->width.value, 700);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
