#pragma once
#include "djui.h"

struct DjuiFont {
    f32 charWidth;
    f32 charHeight;
    f32 lineHeight;
    f32 xOffset;
    f32 yOffset;
    f32 defaultFontScale;
    const Gfx* textBeginDisplayList;
    void (*render_begin)();
    void (*render_char)(const char*);
    void (*render_end)();
    f32 (*char_width)(const char*);
};

extern const struct DjuiFont* gDjuiFonts[];
