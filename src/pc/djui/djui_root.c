#include "djui.h"
#include "src/pc/pc_main.h"
#include "src/pc/gfx/gfx_window_manager_api.h"

static void djui_root_render(struct DjuiBase* base) {
    // grab window height
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    // fill the screen
    djui_base_set_location(base, 0, 0);
    djui_base_set_size(base, windowWidth, windowHeight);

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

    djui_base_set_location(base, 0, 0);
    djui_base_set_size(base, windowWidth, windowHeight);
    djui_base_set_color(base, 0, 0, 0, 0);

    return root;
}
