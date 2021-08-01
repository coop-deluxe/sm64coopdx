#include <stdio.h>
#include "djui.h"
#include "game/save_file.h"
#include "pc/configfile.h"

static struct DjuiBase* sSaveButtonCaller = NULL;
static struct DjuiButton* sSaveButtons[4] = { NULL };
static s32 sEraseButtonTag = 0;

static void djui_panel_host_save_update_button(struct DjuiButton* button, int slot) {
    char starString[32] = { 0 };
    snprintf(starString, 32, "%c x%d", '~' + 1, save_file_get_total_star_count(slot, 0, 24));
    djui_text_set_text(button->text, starString);
}

static void djui_panel_host_save_button_click(struct DjuiBase* caller) {
    configHostSaveSlot = caller->tag + 1;
    djui_panel_host_save_update_button((struct DjuiButton*)sSaveButtonCaller, configHostSaveSlot - 1);
    djui_panel_menu_back(caller);
}

static void djui_panel_host_save_erase_yes(struct DjuiBase* caller) {
    save_file_erase(sEraseButtonTag);
    djui_panel_host_save_update_button(sSaveButtons[sEraseButtonTag], sEraseButtonTag);
    djui_panel_menu_back(caller);
}

static void djui_panel_host_save_erase(struct DjuiBase* caller) {
    sEraseButtonTag = caller->tag;
    djui_panel_confirm_create(caller,
                              "\\#ff0800\\E\\#1be700\\R\\#00b3ff\\A\\#ffef00\\S\\#ff0800\\E",
                              "Are you sure you want to erase this save slot?",
                              djui_panel_host_save_erase_yes);
}

void djui_panel_host_save_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 4 + 64 * 1 + 16 * 5;
    sSaveButtonCaller = caller;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\S\\#1be700\\A\\#00b3ff\\V\\#ffef00\\E");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        for (int i = 0; i < 4; i++) {
            struct DjuiRect* rect1 = djui_rect_create(&body->base);
            djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&rect1->base, 1.0f, 32);
            djui_base_set_color(&rect1->base, 0, 0, 0, 0);
            {
                struct DjuiButton* button1 = djui_button_create(&rect1->base, "");
                djui_panel_host_save_update_button(button1, i);
                djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_size(&button1->base, 0.74f, 32);
                djui_interactable_hook_click(&button1->base, djui_panel_host_save_button_click);
                button1->base.tag = i;
                if (i == (int)(configHostSaveSlot - 1)) { defaultBase = &button1->base; }
                sSaveButtons[i] = button1;

                struct DjuiButton* button2 = djui_button_create(&rect1->base, "erase");
                button2->base.tag = i;
                djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_size(&button2->base, 0.24f, 32);
                djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
                djui_interactable_hook_click(&button2->base, djui_panel_host_save_erase);
            }
        }
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
