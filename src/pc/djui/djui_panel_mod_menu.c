#include <ctype.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/mods/mods.h"

static char* to_uppercase(char* str) {
    char* buffer = strdup(str);
    int i = 0;
    while (buffer[i] != '\0') {
        buffer[i] = toupper(buffer[i]);
        i++;
    }
    return buffer;
}

void djui_panel_mod_menu_mod_button(struct DjuiBase* caller) {
    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[caller->tag];
    smlua_call_mod_menu_element_hook(hooked, caller->tag);
    struct DjuiButton* button = (struct DjuiButton*)caller;
    if (gHookedModMenuElementsCount == 1) {
        char buffer[256] = { 0 };
        snprintf(buffer, 256, "%s - %s", hooked->mod->name, hooked->name);
        djui_text_set_text(button->text, buffer);
    } else {
        djui_text_set_text(button->text, hooked->name);
    }
}

static void djui_panel_mod_menu_mod_checkbox(struct DjuiBase* caller) {
    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[caller->tag];
    smlua_call_mod_menu_element_hook(hooked, caller->tag);
    struct DjuiCheckbox* checkbox = (struct DjuiCheckbox*)caller;
    djui_text_set_text(checkbox->text, hooked->name);
}

static void djui_panel_mod_menu_mod_slider(struct DjuiBase* caller) {
    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[caller->tag];
    smlua_call_mod_menu_element_hook(hooked, caller->tag);
    struct DjuiSlider* slider = (struct DjuiSlider*)caller;
    djui_text_set_text(slider->text, hooked->name);
}

static void djui_panel_mod_menu_mod_inputbox(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)caller;
    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[caller->tag];
    snprintf(hooked->stringValue, 256, "%s", inputbox->buffer);
    smlua_call_mod_menu_element_hook(hooked, caller->tag);
}

static void djui_panel_mod_menu_mod_create_element(struct DjuiBase* parent, int i) {
    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
    switch (hooked->element) {
        case MOD_MENU_ELEMENT_TEXT: {
            struct DjuiText* text = djui_text_create(parent, hooked->name);
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
            struct DjuiButton* button = djui_button_create(parent, hooked->name, DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_menu_mod_button);
            button->base.tag = i;
            break;
        }
        case MOD_MENU_ELEMENT_CHECKBOX: {
            struct DjuiCheckbox* checkbox = djui_checkbox_create(parent, hooked->name, &hooked->boolValue, djui_panel_mod_menu_mod_checkbox);
            checkbox->base.tag = i;
            break;
        }
        case MOD_MENU_ELEMENT_SLIDER: {
            struct DjuiSlider* slider = djui_slider_create(parent, hooked->name, &hooked->uintValue, hooked->sliderMin, hooked->sliderMax, djui_panel_mod_menu_mod_slider);
            slider->base.tag = i;
            break;
        }
        case MOD_MENU_ELEMENT_INPUTBOX: {
            struct DjuiRect* rect = djui_rect_container_create(parent, 32);
            {
                struct DjuiText* text1 = djui_text_create(&rect->base, hooked->name);
                djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_color(&text1->base, 220, 220, 220, 255);
                djui_base_set_size(&text1->base, 0.585f, 64);
                djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
                djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

                struct DjuiInputbox* inputbox = djui_inputbox_create(&rect->base, hooked->length);
                djui_base_set_size_type(&inputbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_size(&inputbox->base, 0.45f, 32);
                djui_base_set_alignment(&inputbox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
                djui_inputbox_set_text(inputbox, hooked->stringValue);
                djui_interactable_hook_value_change(&inputbox->base, djui_panel_mod_menu_mod_inputbox);
                inputbox->base.tag = i;
            }
            break;
        }
        case MOD_MENU_ELEMENT_MAX: {
            break;
        }
    }
}

void djui_panel_mod_menu_mod_create(struct DjuiBase* caller) {
    struct Mod* mod = NULL;
    for (int i = 0; i < gActiveMods.entryCount; i++) {
        if (gActiveMods.entries[i]->index == caller->tag) {
            mod = gActiveMods.entries[i];
        }
    }
    if (mod == NULL) { return; }

    struct DjuiThreePanel* panel = djui_panel_menu_create(to_uppercase(mod->name), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        struct DjuiBase* layoutBase = &paginated->layout->base;
        s32 count = 0;
        for (int i = 0; i < gHookedModMenuElementsCount; i++) {
            if (gHookedModMenuElements[i].mod == mod) {
                djui_panel_mod_menu_mod_create_element(layoutBase, i);
                count++;
            }
        }
        djui_paginated_calculate_height(paginated);
        djui_base_set_size(layoutBase, layoutBase->width.value, 650);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}

void djui_panel_mod_menu_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(PAUSE, MOD_MENU_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        struct DjuiBase* layoutBase = &paginated->layout->base;
        struct Mod* addedMods[MAX_HOOKED_MOD_MENU_ELEMENTS] = { 0 };
        int modCount = 0;
        for (int i = 0; i < gHookedModMenuElementsCount; i++) {
            struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
            bool shouldContinue = false;
            for (int i = 0; i < MAX_HOOKED_MOD_MENU_ELEMENTS; i++) {
                if (addedMods[i] == NULL) { break; }
                if (addedMods[i] == hooked->mod) {
                    shouldContinue = true;
                    break;
                }
            }
            if (shouldContinue) { continue; }

            struct DjuiButton* button = djui_button_create(layoutBase, hooked->mod->name, DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_menu_mod_create);
            button->base.tag = hooked->mod->index;
            addedMods[modCount++] = hooked->mod;
        }
        djui_paginated_calculate_height(paginated);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
