#include "djui.h"
#include "game/segment2.h"
#include "src/pc/network/network.h"

  ////////////////
 // properties //
////////////////

void djui_image_set_image(struct DjuiImage* image, const u8* texture, u16 textureWidth, u16 textureHeight, u16 textureBitSize) {
    image->texture = texture;
    image->textureWidth = textureWidth;
    image->textureHeight = textureHeight;
    image->textureBitSize = textureBitSize;
}

  ////////////
 // events //
////////////

static void djui_image_render(struct DjuiBase* base) {
    struct DjuiImage* image   = (struct DjuiImage*)base;
    struct DjuiBaseRect* comp = &base->comp;
    struct DjuiBaseRect* clip = &base->clip;

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
        gDPSetEnvColor(gDisplayListHead++, base->color.r, base->color.g, base->color.b, base->color.a);
        djui_gfx_render_texture(image->texture, image->textureWidth, image->textureHeight, image->textureBitSize);
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

static void djui_image_destroy(struct DjuiBase* base) {
    struct DjuiImage* image = (struct DjuiImage*)base;
    free(image);
}

struct DjuiImage* djui_image_create(struct DjuiBase* parent, const u8* texture, u16 textureWidth, u16 textureHeight, u16 textureBitSize) {
    struct DjuiImage* image = malloc(sizeof(struct DjuiImage));
    struct DjuiBase* base   = &image->base;

    djui_base_init(parent, base, djui_image_render, djui_image_destroy);

    djui_image_set_image(image, texture, textureWidth, textureHeight, textureBitSize);

    return image;
}
