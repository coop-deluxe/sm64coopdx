#include "djui.h"
#include "../debuglog.h"

static Gfx* sSavedDisplayListHead = NULL;

struct DjuiRoot* gDjuiRoot = NULL;
struct DjuiFlowLayout* buttonContainer;

static void djui_init(void) {
    gDjuiRoot = djui_root_create();

    djui_panel_main_create();
    //djui_panel_debug_create();
    djui_cursor_create();
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
    if (gDjuiRoot == NULL) { djui_init(); }
    sSavedDisplayListHead = gDisplayListHead;
    create_dl_ortho_matrix();

    djui_base_render(&gDjuiRoot->base);

    djui_cursor_update();
    djui_interactable_update();
}
