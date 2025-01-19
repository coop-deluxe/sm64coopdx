#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_confirm.h"
#include "game/level_update.h"
#include "game/save_file.h"
#include "pc/configfile.h"

static struct DjuiInputbox* sSaveNameInputBox = NULL;
static struct DjuiBase* sSaveButtonCaller = NULL;
static struct DjuiButton* sSaveButtons[NUM_SAVE_FILES] = { NULL };
static s32 sButtonTag = 0;

static char* sSaveLetters[NUM_SAVE_FILES] = { "A", "B", "C", "D" };

static void djui_panel_host_save_update_button(struct DjuiButton* button, int slot);

static void djui_panel_host_save_save_name_change(UNUSED struct DjuiBase* caller) {
    snprintf(configSaveNames[sButtonTag], MAX_SAVE_NAME_STRING, "%s", sSaveNameInputBox->buffer);
    if (strlen(sSaveNameInputBox->buffer) >= 64) {
        djui_inputbox_set_text(sSaveNameInputBox, configSaveNames[sButtonTag]);
    }
}

static bool djui_panel_edit_back(UNUSED struct DjuiBase* caller) {
    if (configSaveNames[sButtonTag][0] == '\0') {
        snprintf(configSaveNames[sButtonTag], MAX_SAVE_NAME_STRING, "SM64");
    }
    djui_panel_host_save_update_button(sSaveButtons[sButtonTag], sButtonTag);
    return false;
}

static void djui_panel_edit_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(HOST_SAVE, EDIT_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            char buffer[64] = { 0 };
            djui_language_replace(DLANG(HOST_SAVE, EDIT_NAME), buffer, 64, '@', sSaveLetters[sButtonTag]);
            struct DjuiText* text = djui_text_create(&rect1->base, buffer);
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text->base, 220, 220, 220, 255);
            djui_base_set_size(&text->base, 0.585f, 64);
            djui_base_set_alignment(&text->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text, 64, 64, 64, 100);

            sSaveNameInputBox = djui_inputbox_create(&rect1->base, MAX_SAVE_NAME_STRING);
            djui_base_set_size_type(&sSaveNameInputBox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&sSaveNameInputBox->base, 0.45f, 32);
            djui_base_set_alignment(&sSaveNameInputBox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            char saveName[MAX_SAVE_NAME_STRING] = { 0 };
            snprintf(saveName, MAX_SAVE_NAME_STRING, "%s", configSaveNames[sButtonTag]);
            djui_inputbox_set_text(sSaveNameInputBox, saveName);
            djui_interactable_hook_value_change(&sSaveNameInputBox->base, djui_panel_host_save_save_name_change);
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    panel->on_back = djui_panel_edit_back;
    djui_panel_add(caller, panel, NULL);
}

static void djui_panel_host_save_update_button(struct DjuiButton* button, int slot) {
    char starString[64] = { 0 };
    snprintf(starString, 64, "%c x%d - %s", '~' + 1, save_file_get_total_star_count(slot, 0, 24), configSaveNames[slot]);
    djui_text_set_text(button->text, starString);
}

static void djui_panel_host_save_button_click(struct DjuiBase* caller) {
    configHostSaveSlot = caller->tag + 1;
    djui_panel_host_save_update_button((struct DjuiButton*)sSaveButtonCaller, configHostSaveSlot - 1);
    djui_panel_menu_back(caller);
}

static void djui_panel_host_save_erase_yes(struct DjuiBase* caller) {
    save_file_erase(sButtonTag);
    play_character_sound(gMarioState, CHAR_SOUND_WAAAOOOW);
    djui_panel_host_save_update_button(sSaveButtons[sButtonTag], sButtonTag);
    djui_panel_menu_back(caller);
}

static void djui_panel_host_save_erase(struct DjuiBase* caller) {
    sButtonTag = caller->tag;
    djui_panel_confirm_create(caller,
                              DLANG(HOST_SAVE, ERASE_TITLE),
                              DLANG(HOST_SAVE, CONFIRM),
                              djui_panel_host_save_erase_yes);
}

static void djui_panel_host_save_edit(struct DjuiBase* caller) {
    sButtonTag = caller->tag;
    djui_panel_edit_create(caller);
}

void djui_panel_host_save_create(struct DjuiBase* caller) {
    sSaveButtonCaller = caller;

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(HOST_SAVE, SAVE_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        for (int i = 0; i < NUM_SAVE_FILES; i++) {
            struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
            {
                struct DjuiButton* button1 = djui_button_create(&rect1->base, "", DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_save_button_click);
                djui_panel_host_save_update_button(button1, i);
                djui_base_set_size(&button1->base, 0.6f, 32);
                button1->base.tag = i;
                sSaveButtons[i] = button1;

                struct DjuiButton* button2 = djui_button_create(&rect1->base, DLANG(HOST_SAVE, ERASE), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_save_erase);
                button2->base.tag = i;
                djui_base_set_size(&button2->base, 0.19f, 32);
                djui_base_set_alignment(&button2->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
                djui_base_set_location(&button2->base, configDjuiThemeCenter ? 127 : button1->rect->base.width.value + 98, 0);
                djui_base_set_enabled(&button2->base, gDjuiInMainMenu || gCurrSaveFileNum - 1 != i);

                struct DjuiButton* button3 = djui_button_create(&rect1->base, DLANG(HOST_SAVE, EDIT), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_save_edit);
                button3->base.tag = i;
                djui_base_set_size(&button3->base, 0.19f, 32);
                djui_base_set_alignment(&button3->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            }
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_NORMAL, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
