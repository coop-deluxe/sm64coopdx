#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_join_lobbies.h"
#include "djui_panel_join_private.h"
#include "djui_panel_join_direct.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"

#ifdef COOPNET

static struct DjuiInputbox* sInputboxPassword = NULL;

static void djui_panel_join_private_lobbies(struct DjuiBase* caller) {
    djui_panel_join_lobbies_create(caller, sInputboxPassword->buffer);
}

void djui_panel_join_private_create(struct DjuiBase* caller) {
    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(LOBBIES, PRIVATE_LOBBIES), true);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiText* text1 = djui_text_create(body, DLANG(LOBBIES, ENTER_PASSWORD));
        djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text1->base, 1.0f, 100);
        djui_base_compute_tree(&text1->base);
        u16 directLines = djui_text_count_lines(text1, 12);
        f32 directTextHeight = 32 * 0.8125f * directLines + 8;
        djui_base_set_size(&text1->base, 1.0f, directTextHeight);
        djui_base_set_color(&text1->base, 220, 220, 220, 255);

        struct DjuiInputbox* inputbox1 = djui_inputbox_create(body, 256);
        inputbox1->passwordChar[0] = '#';
        djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&inputbox1->base, 1.0f, 32.0f);
        sInputboxPassword = inputbox1;

        struct DjuiRect* rect2 = djui_rect_container_create(body, 64);
        {
            struct DjuiButton* button1 = djui_button_create(&rect2->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiButton* button2 = djui_button_create(&rect2->base, DLANG(LOBBIES, SEARCH), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_private_lobbies);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            defaultBase = &button2->base;
        }
    }

    djui_panel_add(caller, panel, defaultBase);
}

#endif