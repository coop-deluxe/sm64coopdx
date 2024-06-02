#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/lua/smlua_hooks.h"

static char* sDjuiPanelModMenuModName = NULL;

static char* to_uppercase(char* str) {
    char* buffer = strdup(str);
    int i = 0;
    while (buffer[i] != '\0') {
        buffer[i] = toupper(buffer[i]);
        i++;
    }
    return buffer;
}

// generic
void djui_panel_mod_menu_mod_element(struct DjuiBase* caller) {
    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[caller->tag];
    smlua_call_mod_menu_element_hook(hooked, caller->tag);
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
        case MOD_MENU_ELEMENT_BUTTON:
            struct DjuiButton* button = djui_button_create(parent, hooked->name, DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_menu_mod_element);
            button->base.tag = i;
            break;
        case MOD_MENU_ELEMENT_CHECKBOX:
            struct DjuiCheckbox* checkbox = djui_checkbox_create(parent, hooked->name, &hooked->boolValue, djui_panel_mod_menu_mod_element);
            checkbox->base.tag = i;
            break;
        case MOD_MENU_ELEMENT_SLIDER:
            struct DjuiSlider* slider = djui_slider_create(parent, hooked->name, &hooked->uintValue, hooked->sliderMin, hooked->sliderMax, djui_panel_mod_menu_mod_element);
            slider->base.tag = i;
            break;
        case MOD_MENU_ELEMENT_INPUTBOX:
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
        case MOD_MENU_ELEMENT_MAX:
    }
}

void djui_panel_mod_menu_mod_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(to_uppercase(sDjuiPanelModMenuModName));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        struct DjuiBase* layoutBase = &paginated->layout->base;
        for (int i = 0; i < gHookedModMenuElementsCount; i++) {
            djui_panel_mod_menu_mod_create_element(layoutBase, i);
        }
        djui_paginated_calculate_height(paginated);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}

void djui_panel_mod_menu_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(PAUSE, MOD_MENU_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        struct DjuiBase* layoutBase = &paginated->layout->base;
        struct Mod* lastMod = NULL;
        for (int i = 0; i < gHookedModMenuElementsCount; i++) {
            struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
            if (lastMod == hooked->mod) { continue; }
            lastMod = hooked->mod;
            sDjuiPanelModMenuModName = lastMod->name;
            djui_button_create(layoutBase, hooked->mod->name, DJUI_BUTTON_STYLE_NORMAL, djui_panel_mod_menu_mod_create);
        }
        djui_paginated_calculate_height(paginated);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
