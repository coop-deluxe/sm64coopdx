#pragma once
#include "djui.h"

#define SPANISH_UNICODE_START -61
#define SPANISH_UNICODE_LOWER_N -79   // ñ
#define SPANISH_UNICODE_UPPER_N -111  // Ñ
#define SPANISH_SMCODE_LOWER_N ((s8)('~' + 2))
#define SPANISH_SMCODE_UPPER_N ((s8)('~' + 3))

struct DjuiFont {
    f32 charWidth;
    f32 charHeight;
    f32 lineHeight;
    f32 defaultFontScale;
    u8 textureBitSize;
    bool rotatedUV;
    const Gfx* textBeginDisplayList;
    void (*render_char)(char);
    f32 (*char_width)(char);
};

extern const struct DjuiFont* gDjuiFonts[];