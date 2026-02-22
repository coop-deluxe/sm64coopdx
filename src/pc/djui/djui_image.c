#include "djui.h"
#include "game/segment2.h"
#include "pc/network/network.h"

  ////////////
 // events //
////////////

static bool djui_image_render(struct DjuiBase* base) {
    struct DjuiImage* image   = (struct DjuiImage*)base;
    struct DjuiBaseRect* comp = &base->comp;

    // translate position
    f32 translatedX = comp->x;
    f32 translatedY = comp->y;
    djui_gfx_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, 0);

    // translate size
    f32 translatedWidth  = comp->width;
    f32 translatedHeight = comp->height;
    djui_gfx_scale_translate(&translatedWidth, &translatedHeight);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedWidth, translatedHeight, 1.0f);

    // render
    if (!djui_gfx_add_clipping(base)) {
        const struct TextureInfo *info = &image->textureInfo;
        gDPSetEnvColor(gDisplayListHead++, base->color.r, base->color.g, base->color.b, base->color.a);
        djui_gfx_render_texture(info->texture, info->width, info->height, info->format, info->size, false);
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    return true;
}

static void djui_image_destroy(struct DjuiBase* base) {
    struct DjuiImage* image = (struct DjuiImage*)base;
    free(image);
}

struct DjuiImage* djui_image_create(struct DjuiBase* parent, const Texture* texture, u16 width, u16 height, u8 fmt, u8 siz) {
    struct DjuiImage* image = calloc(1, sizeof(struct DjuiImage));
    struct DjuiBase* base   = &image->base;

    djui_base_init(parent, base, djui_image_render, djui_image_destroy);

    image->textureInfo.texture = texture;
    image->textureInfo.width = width;
    image->textureInfo.height = height;
    image->textureInfo.format = fmt;
    image->textureInfo.size = siz;

    return image;
}
