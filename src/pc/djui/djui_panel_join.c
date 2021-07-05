#include "djui.h"
#include "src/pc/network/network.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

#ifdef DISCORD_SDK
static char* sJoiningDiscord = "\
To join a \\#d0d0ff\\Discord\\#c8c8c8\\ lobby:\n\n\
Keep the game open and click the join button on the invite.\n\n\
If the invite says that the game has ended, click the name of the person that sent the invite to refresh it.\
";
#endif

static char* sJoiningDirect = "\
Enter \\#d0d0ff\\direct connection\\#c8c8c8\\ IP and port:\
";

void djui_panel_join_do_join(struct DjuiBase* caller) {
    network_set_system(NS_SOCKET);
    network_init(NT_CLIENT);
    djui_panel_join_message_create(caller);
}

void djui_panel_join_create(struct DjuiBase* caller) {
    f32 bodyHeight = 2 + 32 + 16 * 2 + 64;

    u16 directLines = 1;
    f32 directTextHeight = 32 * 0.8125f * directLines + 8;
    bodyHeight += directTextHeight + 16;

#ifdef DISCORD_SDK
    u16 discordLines = 8;
    f32 discordTextHeight = 32 * 0.8125f * discordLines + 8;
    bodyHeight += discordTextHeight + 16;
#endif

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\J\\#1be700\\O\\#00b3ff\\I\\#ffef00\\N");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
#ifdef DISCORD_SDK
        struct DjuiText* text1 = djui_text_create(&body->base, sJoiningDiscord);
        djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text1->base, 1.0f, discordTextHeight);
        djui_base_set_color(&text1->base, 200, 200, 200, 255);
#endif
        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 2);
        djui_base_set_color(&rect1->base, 150, 150, 150, 255);

        struct DjuiText* text2 = djui_text_create(&body->base, sJoiningDirect);
        djui_base_set_size_type(&text2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text2->base, 1.0f, directTextHeight);
        djui_base_set_color(&text2->base, 200, 200, 200, 255);

        struct DjuiInputbox* inputbox1 = djui_inputbox_create(&body->base, 256);
        djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&inputbox1->base, 1.0f, 32.0f);
        djui_inputbox_set_text(inputbox1, configJoinIp);
        djui_inputbox_select_all(inputbox1);

        struct DjuiRect* rect2 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect2->base, 1.0f, 64);
        djui_base_set_color(&rect2->base, 0, 0, 0, 0);
        {
            struct DjuiButton* button1 = djui_button_create(&rect2->base, "Back");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_button_set_style(button1, 1);
            djui_interactable_hook_click(&button1->base, djui_panel_menu_back);

            struct DjuiButton* button2 = djui_button_create(&rect2->base, "Join");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_interactable_hook_click(&button2->base, djui_panel_join_do_join);
            defaultBase = &button2->base;
        }
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
