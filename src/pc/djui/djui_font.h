#pragma once
#include "djui.h"

struct DjuiFont {
    f32 charWidth;
    f32 charHeight;
    f32 lineHeight;
    f32 xOffset;
    f32 yOffset;
    f32 defaultFontScale;
    u8 textureBitSize;
    const Gfx* textBeginDisplayList;
    void (*render_char)(char*);
    f32 (*char_width)(char*);
};

extern const struct DjuiFont* gDjuiFonts[];
