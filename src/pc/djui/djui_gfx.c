#include <ultra64.h>
#include "sm64.h"
#include "djui.h"
#include "game/ingame_menu.h"
#include "game/segment2.h"
#include "pc/pc_main.h"
#include "pc/gfx/gfx_window_manager_api.h"
#include "gfx_dimensions.h"
#include "djui_gfx.h"
#include "pc/debuglog.h"

const Gfx dl_djui_display_list_begin[] = {
    gsSPTextureAddrDjui(1),
    gsSPEndDisplayList(),
};

const Gfx dl_djui_display_list_end[] = {
    gsSPTextureAddrDjui(0),
    gsSPEndDisplayList(),
};

void djui_gfx_displaylist_begin(void) {
    gSPDisplayList(gDisplayListHead++, dl_djui_display_list_begin);
}

void djui_gfx_displaylist_end(void) {
    gSPDisplayList(gDisplayListHead++, dl_djui_display_list_end);
}

static const Vtx vertex_djui_simple_rect[] = {
    {{{ 0, -1, 0 }, 0, { 0, 0 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 1, -1, 0 }, 0, { 0, 0 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 1,  0, 0 }, 0, { 0, 0 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0,  0, 0 }, 0, { 0, 0 }, { 0xff, 0xff, 0xff, 0xff }}},
};

const Gfx dl_djui_simple_rect[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADE, G_CC_FADE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPVertexNonGlobal(vertex_djui_simple_rect, 4, 0),
    gsSP2Triangles(0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

f32 djui_gfx_get_scale(void) {
    if (configDjuiScale == 0) { // auto
        u32 windowWidth, windowHeight;
        wm_api->get_dimensions(&windowWidth, &windowHeight);
        if (windowHeight < 768) {
            return 0.5f;
        } else if (windowHeight < 1440) {
            return 1.0f;
        } else {
            return 1.5f;
        }
    } else {
        switch (configDjuiScale) {
            case 1:  return 0.5f;
            case 2:  return 0.85f;
            case 3:  return 1.0f;
            case 4:  return 1.5f;
            default: return 1.0f;
        }
    }
}

/////////////////////////////////////////////

static const Vtx vertex_djui_image[] = {
    {{{ 0, -1, 0 }, 0, {   0,  2048 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 1, -1, 0 }, 0, { 2048, 2048 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 1,  0, 0 }, 0, { 2048,    0 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0,  0, 0 }, 0, { 0,       0 }, { 0xff, 0xff, 0xff, 0xff }}},
};

const Gfx dl_djui_image[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(NULL, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0),
    gsSPExecuteDjui(G_TEXOVERRIDE_DJUI),
    gsSPVertexNonGlobal(vertex_djui_image, 4, 0),
    // gsSPExecuteDjui(G_TEXCLIP_DJUI),
    gsSP2Triangles(0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

static u8 djui_gfx_power_of_two(u32 value) {
    switch (value) {
        case 2:    return 1;
        case 4:    return 2;
        case 8:    return 3;
        case 16:   return 4;
        case 32:   return 5;
        case 64:   return 6;
        case 128:  return 7;
        case 256:  return 8;
        case 512:  return 9;
        case 1024: return 10;
        default:   return 11;
    }
}

void djui_gfx_render_texture(const u8* texture, u32 w, u32 h, u32 bitSize, bool filter) {
    gDPSetTextureFilter(gDisplayListHead++, filter ? G_TF_BILERP : G_TF_POINT);
    gDPSetTextureOverrideDjui(gDisplayListHead++, texture, djui_gfx_power_of_two(w), djui_gfx_power_of_two(h), bitSize);
    gSPDisplayList(gDisplayListHead++, dl_djui_image);
}

void djui_gfx_render_texture_tile(const u8* texture, u32 w, u32 h, u32 bitSize, u32 tileX, u32 tileY, u32 tileW, u32 tileH, bool filter, bool font) {
    if (!gDisplayListHead) {
        LOG_ERROR("Retrieved a null displaylist head");
        return;
    }

    if (!texture) {
        LOG_ERROR("Attempted to render null texture");
        return;
    }

    Vtx *vtx = alloc_display_list(sizeof(Vtx) * 4);
    if (!vtx) {
        LOG_ERROR("Failed to allocate vertices");
        return;
    }

    f32 aspect = tileH ? ((f32)tileW / (f32)tileH) : 1;

    // I don't know why adding 1 to all of the UVs seems to fix rendering, but it does...
    // this should be tested carefully. it definitely fixes some stuff, but what does it break?
    f32 offsetX = font ? -1024.0f / (f32)w : 1;
    f32 offsetY = font ? -1024.0f / (f32)h : 1;
    vtx[0] = (Vtx) {{{ 0,          -1, 0 }, 0, { ( tileX          * 2048.0f) / (f32)w + offsetX, ((tileY + tileH) * 2048.0f) / (f32)h + offsetY }, { 0xff, 0xff, 0xff, 0xff }}};
    vtx[2] = (Vtx) {{{ 1 * aspect,  0, 0 }, 0, { ((tileX + tileW) * 2048.0f) / (f32)w + offsetX, ( tileY          * 2048.0f) / (f32)h + offsetY }, { 0xff, 0xff, 0xff, 0xff }}};
    vtx[1] = (Vtx) {{{ 1 * aspect, -1, 0 }, 0, { ((tileX + tileW) * 2048.0f) / (f32)w + offsetX, ((tileY + tileH) * 2048.0f) / (f32)h + offsetY }, { 0xff, 0xff, 0xff, 0xff }}};
    vtx[3] = (Vtx) {{{ 0,           0, 0 }, 0, { ( tileX          * 2048.0f) / (f32)w + offsetX, ( tileY          * 2048.0f) / (f32)h + offsetY }, { 0xff, 0xff, 0xff, 0xff }}};

    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gDPSetCombineMode(gDisplayListHead++, G_CC_FADEA, G_CC_FADEA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTextureFilter(gDisplayListHead++, filter ? G_TF_BILERP : G_TF_POINT);

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    gDPSetTextureOverrideDjui(gDisplayListHead++, texture, djui_gfx_power_of_two(w), djui_gfx_power_of_two(h), bitSize);
	gDPLoadTextureBlockWithoutTexture(gDisplayListHead++, NULL, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);

    *(gDisplayListHead++) = (Gfx) gsSPExecuteDjui(G_TEXOVERRIDE_DJUI);

    gSPVertexNonGlobal(gDisplayListHead++, vtx, 4, 0);
    *(gDisplayListHead++) = (Gfx) gsSPExecuteDjui(G_TEXCLIP_DJUI);
    gSP2TrianglesDjui(gDisplayListHead++, 0,  1,  2, 0x0,  0,  2,  3, 0x0);

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
}

/////////////////////////////////////////////

void djui_gfx_position_translate(f32* x, f32* y) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);
    *x = GFX_DIMENSIONS_FROM_LEFT_EDGE(0) + *x * ((f32)SCREEN_HEIGHT / (f32)windowHeight) * djui_gfx_get_scale();
    *y = SCREEN_HEIGHT - *y * ((f32)SCREEN_HEIGHT / (f32)windowHeight) * djui_gfx_get_scale();
}

void djui_gfx_scale_translate(f32* width, f32* height) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    *width  = *width * ((f32)SCREEN_HEIGHT / (f32)windowHeight) * djui_gfx_get_scale();
    *height = *height * ((f32)SCREEN_HEIGHT / (f32)windowHeight) * djui_gfx_get_scale();
}

void djui_gfx_size_translate(f32* size) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    *size = *size * ((f32)SCREEN_HEIGHT / (f32)windowHeight) * djui_gfx_get_scale();
}

bool djui_gfx_add_clipping_specific(struct DjuiBase* base, f32 dX, f32 dY, f32 dW, f32 dH) {
    struct DjuiBaseRect* clip = &base->clip;

    f32 clipX2 = clip->x + clip->width;
    f32 clipY2 = clip->y + clip->height;

    f32 dX2 = dX + dW;
    f32 dY2 = dY + dH;

    // completely clipped
    if (dX2 < clip->x) { return true; }
    if (dX  > clipX2)  { return true; }
    if (dY2 < clip->y) { return true; }
    if (dY  > clipY2)  { return true; }

    f32 dClipX1 = fmax((clip->x - dX) / dW, 0);
    f32 dClipY1 = fmax((clip->y - dY) / dH, 0);
    f32 dClipX2 = fmax((dX - (clipX2 - dW)) / dW, 0);
    f32 dClipY2 = fmax((dY - (clipY2 - dH)) / dH, 0);

    if ((dClipX1 != 0) || (dClipY1 != 0) || (dClipX2 != 0) || (dClipY2 != 0)) {
        gDPSetTextureClippingDjui(gDisplayListHead++, (u8)(dClipX1 * 255), (u8)(dClipY1 * 255), (u8)(dClipX2 * 255), (u8)(dClipY2 * 255));
    }

    return false;
}

bool djui_gfx_add_clipping(struct DjuiBase* base) {
    struct DjuiBaseRect* comp = &base->comp;
    return djui_gfx_add_clipping_specific(base, comp->x, comp->y, comp->width, comp->height);
}
