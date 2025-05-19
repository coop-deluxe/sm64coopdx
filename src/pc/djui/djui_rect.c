#include "djui.h"

  ////////////
 // events //
////////////

bool djui_rect_render(struct DjuiBase* base) {
    struct DjuiBaseRect* clip = &base->clip;

    // translate position
    f32 translatedX = clip->x;
    f32 translatedY = clip->y;
    djui_gfx_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, 0);

    // translate size
    f32 translatedWidth  = clip->width;
    f32 translatedHeight = clip->height;
    djui_gfx_scale_translate(&translatedWidth, &translatedHeight);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedWidth, translatedHeight, 1.0f);

    // render
    gDPSetEnvColor(gDisplayListHead++, base->color.r, base->color.g, base->color.b, base->color.a);
    gSPDisplayList(gDisplayListHead++, base->gradient ? dl_djui_menu_rect : dl_djui_simple_rect);

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    return true;
}

static void djui_rect_destroy(struct DjuiBase* base) {
    struct DjuiRect* rect = (struct DjuiRect*)base;
    free(rect);
}

struct DjuiRect* djui_rect_create(struct DjuiBase* parent) {
    struct DjuiRect* rect = calloc(1, sizeof(struct DjuiRect));
    struct DjuiBase* base = &rect->base;

    djui_base_init(parent, base, djui_rect_render, djui_rect_destroy);

    return rect;
}

struct DjuiRect* djui_rect_container_create(struct DjuiBase* parent, f32 height) {
    struct DjuiRect* rect = djui_rect_create(parent);
    djui_base_set_size_type(&rect->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&rect->base, 1.0f, height);
    djui_base_set_color(&rect->base, 0, 0, 0, 0);
    return rect;
}
