#include "djui.h"
#include "pc/pc_main.h"
#include "pc/gfx/gfx_window_manager_api.h"

static bool djui_root_render(struct DjuiBase* base) {
    // grab window height
    u32 windowWidth, windowHeight;
    gfx_get_dimensions(&windowWidth, &windowHeight);

    // fill the screen
    djui_base_set_location(base, 0, 0);
    djui_base_set_size(base, windowWidth / djui_gfx_get_scale(), windowHeight / djui_gfx_get_scale());

    // compute base
    djui_base_compute(base);
    return true;
}

static void djui_root_destroy(struct DjuiBase* base) {
    struct DjuiRoot* root = (struct DjuiRoot*)base;
    free(root);
    gDjuiRoot = NULL;
}

struct DjuiRoot* djui_root_create(void) {
    struct DjuiRoot* root = calloc(1, sizeof(struct DjuiRoot));
    struct DjuiBase* base = &root->base;

    djui_base_init(NULL, base, djui_root_render, djui_root_destroy);

    djui_base_set_location(base, 0, 0);
    djui_base_set_size(base, 1280, 720);
    djui_base_set_color(base, 0, 0, 0, 0);

    return root;
}
