#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_main.h"
#include "djui_panel_join_message.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"

#define DJUI_JOIN_MESSAGE_ELAPSE 60
bool gDjuiPanelJoinMessageVisible = false;
float gDownloadProgress = 0;
float gDownloadProgressInf = 0;
char gDownloadEstimate[DOWNLOAD_ESTIMATE_LENGTH] = "";

static struct DjuiText* sPanelText = NULL;
static bool sDisplayingError = false;


void djui_panel_join_message_error(char* message) {
    djui_panel_join_message_create(NULL);
    sDisplayingError = true;
    djui_text_set_text(sPanelText, message);
}

void djui_panel_join_message_cancel(struct DjuiBase* caller) {
    if (network_is_reconnecting()) { return; }
    network_reset_reconnect_and_rehost();
    network_shutdown(true, false, false, false);
    djui_panel_menu_back(caller);
}

bool djui_panel_join_message_back(struct DjuiBase* caller) {
    djui_panel_join_message_cancel(caller);
    return true;
}

void djui_panel_join_message_render_pre(struct DjuiBase* base, UNUSED bool* unused) {
    if (sDisplayingError) { return; }
    struct DjuiText* text1 = (struct DjuiText*)base;
    u16 lastElapse = (base->tag / DJUI_JOIN_MESSAGE_ELAPSE);
    base->tag = (base->tag + 1) % (DJUI_JOIN_MESSAGE_ELAPSE * 3);
    u16 elapse = (base->tag / DJUI_JOIN_MESSAGE_ELAPSE);
    if (lastElapse != elapse) {
        char tmp[DOWNLOAD_ESTIMATE_LENGTH + 4] = "";
        switch (base->tag / DJUI_JOIN_MESSAGE_ELAPSE) {
            case 0:  snprintf(tmp, DOWNLOAD_ESTIMATE_LENGTH + 4, "%s\n...", gDownloadEstimate); break;
            case 1:  snprintf(tmp, DOWNLOAD_ESTIMATE_LENGTH + 4, "%s\n.",   gDownloadEstimate); break;
            default: snprintf(tmp, DOWNLOAD_ESTIMATE_LENGTH + 4, "%s\n..",  gDownloadEstimate); break;
        }
        djui_text_set_text(text1, tmp);
    }
}

void djui_panel_join_message_create(struct DjuiBase* caller) {
    // make sure main panel was created
    if (!gDjuiPanelMainCreated) { djui_panel_main_create(caller); }

    // don't recreate panel if it's already visible
    if (gDjuiPanelJoinMessageVisible) { return; }

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(JOIN_MESSAGE, JOINING), true);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        snprintf(gDownloadEstimate, 32, " ");
        struct DjuiText* text1 = djui_text_create(body, "\n...");
        djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text1->base, 1.0f, 32 * 4);
        djui_base_set_color(&text1->base, 220, 220, 220, 255);
        djui_text_set_alignment(text1, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        text1->base.tag = 0;
        text1->base.on_render_pre = djui_panel_join_message_render_pre;
        sPanelText = text1;

        gDownloadProgressInf = 0;
        djui_progress_bar_create(body, &gDownloadProgressInf, 0.0f, 1.0f, true);

        gDownloadProgress = 0;
        djui_progress_bar_create(body, &gDownloadProgress, 0.0f, 1.0f, false);

        djui_button_create(body, DLANG(MENU, CANCEL), DJUI_BUTTON_STYLE_BACK, djui_panel_join_message_cancel);
    }
    panel->on_back = djui_panel_join_message_back;

    djui_panel_add(caller, panel, NULL);
    gDjuiPanelJoinMessageVisible = true;
    sDisplayingError = false;
}
