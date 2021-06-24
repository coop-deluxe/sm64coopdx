#include "djui.h"
#include "game/segment2.h"

  ///////////////////////////////////
 // font 0 (built-in normal font) //
///////////////////////////////////

static Vtx djui_font_normal_vertices[] = {
    {{{ 0, -1, 0}, 0, {   0, 256}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0.5f, -1, 0}, 0, {   0,   0}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0.5f,  0, 0}, 0, { 512,   0}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0,   0, 0}, 0, { 512, 256}, { 0xff, 0xff, 0xff, 0xff }}},
};

static const Gfx djui_font_normal_text_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

static const Gfx djui_font_normal_text_settings[] = {
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, ((16 * 8 + G_IM_SIZ_4b_INCR) >> G_IM_SIZ_4b_SHIFT) - 1, CALC_DXT(16, G_IM_SIZ_4b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(djui_font_normal_vertices, 4, 0),
    gsSPExecuteDjui(G_TEXCLIP_DJUI),
    gsSP2Triangles(0,  1,  2, 0x0, 0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

static void djui_font_normal_render_char(char c) {
    void** fontLUT;
    void* packedTexture;

    u8 d = str_ascii_char_to_dialog(c);
    fontLUT = segmented_to_virtual(main_font_lut);
    packedTexture = segmented_to_virtual(fontLUT[d]);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, VIRTUAL_TO_PHYSICAL(packedTexture));
    gSPDisplayList(gDisplayListHead++, djui_font_normal_text_settings);
}

static f32 djui_font_normal_char_width(char c) {
    u8 d = str_ascii_char_to_dialog(c);
    return gDialogCharWidths[d] / 16.0f;
}

static const struct DjuiFont sDjuiFontNormal = {
    .charWidth            = 0.5f,
    .charHeight           = 1.0f,
    .lineHeight           = 0.8f,
    .defaultFontScale     = 32.0f,
    .rotatedUV            = true,
    .textBeginDisplayList = djui_font_normal_text_begin,
    .render_char          = djui_font_normal_render_char,
    .char_width           = djui_font_normal_char_width,
};

  ////////////////////////////////
 // font 1 (custom title font) //
////////////////////////////////

static f32 sDjuiFontTitleCharWidths[] = {
/*      !      "      #      $      %      &      '      (      )      *      +      ,      -      .      /      */
    0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
/*      0      1      2      3      4      5      6      7      8      9      */
    0.45f, 0.35f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f,
/*      :      ;      <      =      >      ?      @      */
    0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
/*      A      B      C      D      E      F      G      H      I      J      K      L      M      N      O      P      Q      R      S      T      U      V      W      X      Y      Z      */
    0.55f, 0.50f, 0.50f, 0.50f, 0.45f, 0.45f, 0.50f, 0.55f, 0.28f, 0.60f, 0.50f, 0.45f, 0.55f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.55f, 0.50f, 0.50f, 0.50f, 0.60f, 0.52f, 0.60f, 0.45f,
/*      [      \      ]      ^      _      `      */
    0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
/*      a      b      c      d      e      f      g      h      i      j      k      l      m      n      o      p      q      r      s      t      u      v      w      x      y      z      */
    0.45f, 0.45f, 0.40f, 0.40f, 0.45f, 0.37f, 0.40f, 0.40f, 0.20f, 0.45f, 0.40f, 0.30f, 0.50f, 0.40f, 0.40f, 0.40f, 0.45f, 0.40f, 0.50f, 0.45f, 0.50f, 0.40f, 0.50f, 0.50f, 0.45f, 0.45f,
/*      {      |      }      ~      !      */
    0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
};

static void djui_font_title_render_char(char c) {
    extern const u8* const font_title_chars[];
    djui_gfx_render_texture(font_title_chars[c - '!'], 64, 64, 32);
}

static f32 djui_font_title_char_width(char c) {
    if (c == ' ') { return 0.30f; }
    return sDjuiFontTitleCharWidths[c - '!'];
}

static const struct DjuiFont sDjuiFontTitle = {
    .charWidth            = 1.0f,
    .charHeight           = 0.9f,
    .lineHeight           = 0.7f,
    .defaultFontScale     = 64.0f,
    .rotatedUV            = false,
    .textBeginDisplayList = NULL,
    .render_char          = djui_font_title_render_char,
    .char_width           = djui_font_title_char_width,
};

  ///////////////
 // font list //
///////////////

struct DjuiFont gDjuiFonts[] = {
    sDjuiFontNormal,
    sDjuiFontTitle,
};