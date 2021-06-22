#include "djui.h"
#include "../debuglog.h"

#include "src/pc/controller/controller_sdl.h"
#include "src/pc/controller/controller_mouse.h"

ALIGNED8 static u8 texture_hand_open[] = {
#include "textures/intro_raw/hand_open.rgba16.inc.c"
};

ALIGNED8 static u8 texture_hand_closed[] = {
#include "textures/intro_raw/hand_closed.rgba16.inc.c"
};

static Gfx* sSavedDisplayListHead = NULL;

struct DjuiRoot* gDjuiRoot = NULL;
static struct DjuiImage* sMouseCursor = NULL;
struct DjuiFlowLayout* buttonContainer;

static void djui_init(void) {
    gDjuiRoot = djui_root_create();

    sMouseCursor = djui_image_create(NULL, texture_hand_open, 32, 32, 16);
    djui_base_set_location(&sMouseCursor->base, 0, 0);
    djui_base_set_size(&sMouseCursor->base, 64, 64);

    djui_panel_main_create();
    //djui_panel_debug_create();
}

static void djui_mouse_update(void) {
#if defined(CAPI_SDL2) || defined(CAPI_SDL1)
    controller_sdl_read_mouse_window();

    djui_interactable_update();

    // adjust mouse cursor
    djui_base_set_location(&sMouseCursor->base, mouse_window_x - 13, mouse_window_y - 13);

    if (mouse_window_buttons & 0b0001) {
        djui_image_set_image(sMouseCursor, texture_hand_closed, 32, 32, 16);
    } else {
        djui_image_set_image(sMouseCursor, texture_hand_open, 32, 32, 16);
    }
#endif
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

    djui_mouse_update();

    djui_base_render(&gDjuiRoot->base);
    djui_base_render(&sMouseCursor->base);
}
