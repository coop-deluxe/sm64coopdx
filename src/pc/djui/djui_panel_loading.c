#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/pc_main.h"

static struct DjuiBase *sPanelCaller = NULL;
static void (*sCallbackFunc)(struct DjuiBase *) = NULL;

static bool djui_panel_loading_on_loading_text_change(struct DjuiBase *caller) {
    struct DjuiText *text = (struct DjuiText *)caller;
    djui_text_set_text(text, gLoadingMessage);
    return false;
}

static bool djui_panel_loading_on_game_init(UNUSED struct DjuiBase *caller) {
    djui_panel_back_no_transition();
    if (sCallbackFunc) { sCallbackFunc(sPanelCaller); }
    sPanelCaller = NULL;
    sCallbackFunc = NULL;
    return true;
}

static bool djui_panel_loading_on_back(UNUSED struct DjuiBase *caller) {
    sPanelCaller = NULL;
    sCallbackFunc = NULL;
    return false;
}

void djui_panel_loading_create(struct DjuiBase *caller, void (*callback)(struct DjuiBase *)) {
    if (gGameInited) {
        if (callback) { callback(caller); }
        return;
    }

    sPanelCaller = caller;
    sCallbackFunc = callback;

    struct DjuiThreePanel *panel = djui_panel_menu_create(DLANG(LOADING, LOADING), true);
    struct DjuiBase *body = djui_three_panel_get_body(panel);
    {
        struct DjuiText *loadingText = djui_text_create(body, gLoadingMessage);
        djui_base_set_size_type(&loadingText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&loadingText->base, 1.0f, 32 * 4);
        djui_base_set_color(&loadingText->base, 220, 220, 220, 255);
        djui_text_set_alignment(loadingText, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_hook_on_changed(&loadingText->base, &gLoadingMessage, sizeof(gLoadingMessage), djui_panel_loading_on_loading_text_change);
        djui_base_hook_on_changed(&loadingText->base, &gGameInited, sizeof(gGameInited), djui_panel_loading_on_game_init);

        struct DjuiProgressBar *loadingProgressBar = djui_progress_bar_create(body, &gLoadingPercent, 0.0f, 1.0f, false);
        loadingProgressBar->smoothenHigh = 0.75f;
        loadingProgressBar->smoothenLow = 0.25f;

        djui_button_create(body, DLANG(MENU, CANCEL), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }
    panel->on_back = djui_panel_loading_on_back;

    djui_panel_add(caller, panel, NULL);
}
