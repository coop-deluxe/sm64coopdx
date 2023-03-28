#pragma once
#include "djui.h"

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

u8 djui_font_convert_smcode_to_base(char c);
void djui_font_convert_to_unicode(char* from, char* to, int length, int maxlength);
void djui_font_convert_to_smcode(char* text);
bool djui_font_valid_smcode(char c);
