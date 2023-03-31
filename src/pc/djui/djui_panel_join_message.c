#include "djui.h"
#include "src/pc/network/network.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

#define DJUI_JOIN_MESSAGE_ELAPSE 60
bool gDjuiPanelJoinMessageVisible = false;
static struct DjuiText* sPanelText = NULL;
static bool sDisplayingError = false;
float gDownloadProgress = 0;

void djui_panel_join_message_error(char* message) {
    djui_panel_join_message_create(NULL);
    sDisplayingError = true;
    djui_text_set_text(sPanelText, message);
}

void djui_panel_join_message_cancel(struct DjuiBase* caller) {
    if (network_is_reconnecting()) { return; }
    network_reset_reconnect_and_rehost();
    network_shutdown(true, false, false);
    djui_panel_menu_back(caller);
}

void djui_panel_join_message_render_pre(struct DjuiBase* base, UNUSED bool* unused) {
    if (sDisplayingError) { return; }
    struct DjuiText* text1 = (struct DjuiText*)base;
    u16 lastElapse = (base->tag / DJUI_JOIN_MESSAGE_ELAPSE);
    base->tag = (base->tag + 1) % (DJUI_JOIN_MESSAGE_ELAPSE * 3);
    u16 elapse = (base->tag / DJUI_JOIN_MESSAGE_ELAPSE);
    if (lastElapse != elapse) {
        switch (base->tag / DJUI_JOIN_MESSAGE_ELAPSE) {
            case 0:  djui_text_set_text(text1, "..."); break;
            case 1:  djui_text_set_text(text1, ".");   break;
            default: djui_text_set_text(text1, "..");  break;
        }
    }
}

void djui_panel_join_message_create(struct DjuiBase* caller) {
    // make sure main panel was created
    if (!gDjuiPanelMainCreated) { djui_panel_main_create(caller); }

    // don't recreate panel if it's already visible
    if (gDjuiPanelJoinMessageVisible) { return; }

    u16 directLines = 8;
    f32 directTextHeight = 32 * 0.8125f * directLines + 8;

    struct DjuiThreePanel* panel = djui_panel_menu_create("JOINING");
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiText* text1 = djui_text_create(body, "...");
        djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text1->base, 1.0f, directTextHeight);
        djui_base_set_color(&text1->base, 200, 200, 200, 255);
        djui_text_set_alignment(text1, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        text1->base.tag = 0;
        text1->base.on_render_pre = djui_panel_join_message_render_pre;
        sPanelText = text1;

        gDownloadProgress = 0;
        djui_progress_bar_create(body, &gDownloadProgress, 0.0f, 1.0f);

        djui_button_create(body, "Cancel", DJUI_BUTTON_STYLE_BACK, djui_panel_join_message_cancel);
    }

    djui_panel_add(caller, panel, NULL);
    gDjuiPanelJoinMessageVisible = true;
    sDisplayingError = false;
}
