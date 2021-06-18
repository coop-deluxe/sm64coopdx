#include "djui.h"
#include "src/pc/pc_main.h"
#include "src/pc/gfx/gfx_window_manager_api.h"

static void djui_root_render(struct DjuiBase* base) {
    // grab window height
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    // fill the screen
    base->x      = 0;
    base->y      = 0;
    base->width  = windowWidth;
    base->height = windowHeight;

    // compute base
    djui_base_compute(base);
}

static void djui_root_destroy(struct DjuiBase* base) {
    struct DjuiRoot* root = (struct DjuiRoot*)base;
    free(root);
    gDjuiRoot = NULL;
}

struct DjuiRoot* djui_root_create(void) {
    struct DjuiRoot* root = malloc(sizeof(struct DjuiRoot));
    struct DjuiBase* base = &root->base;

    djui_base_init(NULL, base, djui_root_render, djui_root_destroy);

    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    base->x = 0;
    base->y = 0;
    base->width = windowWidth;
    base->height = windowHeight;
    base->color.a = 0;

    return root;
}
