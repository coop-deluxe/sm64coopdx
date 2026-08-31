#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_confirm.h"
#include "game/level_update.h"
#include "game/save_file.h"
#include "pc/configfile.h"
#include "pc/utils/misc.h"

static struct DjuiFlowLayout* sSaveLayout = NULL;
static struct DjuiPaginated* sSavePaginated = NULL;
static struct DjuiInputbox* sSaveNameInputBox = NULL;
static struct DjuiBase* sSaveButtonCaller = NULL;
static struct DjuiButton* sSaveButtons[NUM_SAVE_FILES] = { NULL };
static struct DjuiInputbox* sSearchInputbox = NULL;
static char sSaveName[MAX_SAVE_NAME_STRING] = { 0 };
static s32 sButtonTag = 0;
static bool sEditing = true;

static void djui_panel_host_save_update_button(struct DjuiButton* button, int slot);
static void djui_panel_host_save_add_saves(struct DjuiBase* base);

static void djui_panel_host_reload_saves() {
    djui_base_destroy_children(&sSaveLayout->base);
    djui_panel_host_save_add_saves(&sSaveLayout->base);
    djui_paginated_calculate_height(sSavePaginated);
}

static void djui_panel_host_save_update_save_name() {
    save_file_rename_file(sButtonTag, sSaveName);
    djui_panel_host_reload_saves();
}

static bool is_save_name_input_valid() {
    if (sSaveName[0] == '\0'
        || strstr(sSaveName, ".")
        || strstr(sSaveName, "/")
        || strstr(sSaveName, "\\")) {
        return false;
    }

    return true;
}

static void djui_panel_host_save_save_name_change(UNUSED struct DjuiBase* caller) {
    snprintf(sSaveName, MAX_SAVE_NAME_STRING, "%s", sSaveNameInputBox->buffer);
    if (strlen(sSaveNameInputBox->buffer) >= 64) {
        djui_inputbox_set_text(sSaveNameInputBox, sSaveName);
    }

    struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
    struct DjuiColor* textColor = &theme->interactables.textColor;

    if (sSaveName[0] != '\0' && !is_save_name_input_valid()) {
        djui_inputbox_set_text_color(sSaveNameInputBox, 255, 0, 0, 255);
    } else {
        djui_inputbox_set_text_color(sSaveNameInputBox, textColor->r, textColor->g, textColor->b, textColor->a);
    }
}

static void djui_panel_create_create(struct DjuiBase* caller) {
    if (!is_save_name_input_valid()) {
        djui_inputbox_set_text(sSaveNameInputBox, sSaveName);
        return;
    }
    if (!fs_sys_dir_exists(fs_get_write_path(SAVE_DIRECTORY))) {
        fs_sys_mkdir(fs_get_write_path(SAVE_DIRECTORY));
    }
    char filePath[SYS_MAX_PATH];
    save_file_get_dir(sButtonTag, filePath, SYS_MAX_PATH, sSaveName);
    if (fs_sys_file_exists(fs_get_write_path(filePath))) { return; }
    u8 content[EEPROM_SIZE] = { 0 };
    FILE *fp = fopen(fs_get_write_path(filePath), "wb");
    if (fp == NULL) { return; }
    fwrite(content, 1, EEPROM_SIZE, fp);
    fclose(fp);
    djui_panel_host_reload_saves();
    djui_panel_menu_back(caller);
}

static void djui_panel_edit_save(UNUSED struct DjuiBase* caller) {
    if (!is_save_name_input_valid()) {
        snprintf(sSaveName, MAX_SAVE_NAME_STRING, "SM64");
        djui_panel_menu_back(caller);
        return;
    }
    djui_panel_host_save_update_save_name();
    djui_panel_host_save_update_button(sSaveButtons[sButtonTag], sButtonTag);
    djui_panel_menu_back(caller);
}

static void djui_panel_edit_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(sEditing ? DLANG(HOST_SAVE, EDIT_TITLE) : DLANG(HOST_SAVE, CREATE_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            char buffer[64] = { 0 };
            char slotBuffer[4];
            snprintf(slotBuffer, sizeof(slotBuffer), "%d", sButtonTag + 1);
            djui_language_replace(sEditing ? DLANG(HOST_SAVE, EDIT_NAME) : DLANG(HOST_SAVE, CREATE_NAME), buffer, 64, '@', slotBuffer);
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
            save_file_get_filename_at_index(sButtonTag, sSaveName);
            djui_inputbox_set_text(sSaveNameInputBox, sSaveName);
            djui_interactable_hook_value_change(&sSaveNameInputBox->base, djui_panel_host_save_save_name_change);
        }

        struct DjuiRect* rect = djui_rect_container_create(body, 64);
        {
            djui_button_left_create(&rect->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
            if (!sEditing) {
                djui_button_right_create(&rect->base, DLANG(HOST_SAVE, CREATE), DJUI_BUTTON_STYLE_NORMAL, djui_panel_create_create);
            } else {
                djui_button_right_create(&rect->base, DLANG(HOST_SAVE, APPLY), DJUI_BUTTON_STYLE_NORMAL, djui_panel_edit_save);
            }
        }
    }

    djui_panel_add(caller, panel, NULL);
}

static void djui_panel_save_create(struct DjuiBase* caller) {
    sEditing = false;
    sButtonTag = save_file_get_first_available_index();
    if (sButtonTag >= NUM_SAVE_FILES) return;
    djui_panel_edit_create(caller);
}

static void djui_panel_host_save_edit(struct DjuiBase* caller) {
    sEditing = true;
    sButtonTag = caller->tag;
    djui_panel_edit_create(caller);
}

static char *get_save_name(int slot) {
    static char sStarString[64] = { 0 };
    char name[MAX_SAVE_NAME_STRING] = { 0 };
    save_file_get_filename_at_index(slot, name);
    snprintf(sStarString, 64, "%c x%d - %s", '~' + 1, save_file_get_total_star_count(slot, 0, 24), name);
    return sStarString;
}

static void djui_panel_host_save_update_button(struct DjuiButton* button, int slot) {
    if (!button || !button->text) { return; }
    djui_text_set_text(button->text, get_save_name(slot));
}

static bool djui_panel_host_save_back(UNUSED struct DjuiBase* caller) {
    djui_panel_host_save_update_button((struct DjuiButton*)sSaveButtonCaller, configHostSaveSlot - 1);
    return false;
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
    djui_panel_host_reload_saves();
    djui_panel_menu_back(caller);
}

static void djui_panel_host_save_erase(struct DjuiBase* caller) {
    sButtonTag = caller->tag;
    djui_panel_confirm_create(caller, DLANG(HOST_SAVE, ERASE_TITLE), DLANG(HOST_SAVE, CONFIRM), djui_panel_host_save_erase_yes);
}

void djui_panel_host_save_add_saves(struct DjuiBase* base) {
    if (!fs_sys_dir_exists(fs_get_write_path(SAVE_DIRECTORY))) { return; }
    for (int i = 0; i < NUM_SAVE_FILES; i++) {
        char filepath[SYS_MAX_PATH];
        save_file_get_dir(i, filepath, SYS_MAX_PATH, NULL);
        if (!fs_sys_file_exists(fs_get_write_path(filepath))) { continue; }

        char *saveName = get_save_name(i);

        // filter results
        if (sSearchInputbox != NULL &&
            sSearchInputbox->buffer != NULL &&
            !strstr_lowercased(djui_text_get_uncolored_string(NULL, strlen(saveName) + 1, saveName), sSearchInputbox->buffer)
        ) {
            continue;
        }

        struct DjuiRect* rect1 = djui_rect_container_create(base, 32);
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
}

static void djui_panel_host_save_rebuild_save_list(UNUSED struct DjuiBase* caller) {
    djui_base_destroy_children(&sSaveLayout->base);
    djui_panel_host_save_add_saves(&sSaveLayout->base);
    djui_paginated_calculate_height(sSavePaginated);
}

void djui_panel_host_save_create(struct DjuiBase* caller) {
    sSaveButtonCaller = caller;

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(HOST_SAVE, SAVE_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiSearchbox* searchbox = djui_searchbox_create(body, djui_panel_host_save_rebuild_save_list);
        sSearchInputbox = searchbox->inputbox;

        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        paginated->showMaxCount = true;
        sSaveLayout = paginated->layout;
        djui_panel_host_save_add_saves(&paginated->layout->base);
        djui_paginated_calculate_height(paginated);
        sSavePaginated = paginated;

        djui_button_create(body, DLANG(HOST_SAVE, CREATE_SAVE), DJUI_BUTTON_STYLE_NORMAL, djui_panel_save_create);
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_NORMAL, djui_panel_menu_back);
    }

    panel->on_back = djui_panel_host_save_back;
    djui_panel_add(caller, panel, NULL);
}
