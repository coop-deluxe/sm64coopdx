#include "djui.h"
#include "../debuglog.h"
#include "pc/cliopts.h"

static Gfx* sSavedDisplayListHead = NULL;

struct DjuiRoot* gDjuiRoot = NULL;
struct DjuiText* gDjuiPauseOptions = NULL;

void djui_init(void) {
    gDjuiRoot = djui_root_create();

    gDjuiPauseOptions = djui_text_create(&gDjuiRoot->base, "R Button - Options");
    djui_base_set_size_type(&gDjuiPauseOptions->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&gDjuiPauseOptions->base, 1.0f, 32);
    djui_base_set_location(&gDjuiPauseOptions->base, 0, 16);
    djui_text_set_drop_shadow(gDjuiPauseOptions, 0, 0, 0, 255);
    djui_text_set_alignment(gDjuiPauseOptions, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_visible(&gDjuiPauseOptions->base, false);

    if (gCLIOpts.Network != NT_SERVER) {
        djui_panel_main_create(NULL);
        //djui_panel_debug_create();
    }

    djui_cursor_create();
}

void djui_connect_menu_open(void) {
    djui_panel_shutdown();
    djui_panel_main_create(NULL);
    djui_panel_join_create(NULL);
    djui_panel_join_message_create(NULL);
}

void djui_render_patch(void) {
    // reset the head and re-render DJUI
    if (sSavedDisplayListHead == NULL) { return; }
    gDisplayListHead = sSavedDisplayListHead;
    djui_render();
    gDPFullSync(gDisplayListHead++);
    gSPEndDisplayList(gDisplayListHead++);
}

void djui_render(void) {
    sSavedDisplayListHead = gDisplayListHead;
    create_dl_ortho_matrix();

    djui_panel_update();
    djui_popup_update();

    djui_base_render(&gDjuiRoot->base);

    djui_cursor_update();
    djui_interactable_update();
}
