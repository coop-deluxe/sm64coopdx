#ifndef PRINT_H
#define PRINT_H

#include <PR/ultratypes.h>

#define TEXRECT_MIN_X 10
#define TEXRECT_MAX_X 300
#define TEXRECT_MIN_Y 5
#define TEXRECT_MAX_Y 220

#define GLYPH_SPACE           -1
#define GLYPH_U               30
#define GLYPH_EXCLAMATION_PNT 36
#define GLYPH_HASHTAG         37
#define GLYPH_QUESTION_MARK   38
#define GLYPH_AMPERSAND       39
#define GLYPH_PERCENT         40
#define GLYPH_MULTIPLY        41
#define GLYPH_COIN            42
#define GLYPH_COMMA           43
#define GLYPH_STAR            44
#define GLYPH_PERIOD          45
#define GLYPH_KEY             46
#define GLYPH_APOSTROPHE      47
#define GLYPH_DOUBLE_QUOTE    48
#define GLYPH_SLASH           49
#define GLYPH_DASH            50
#define GLYPH_DIVIDE          51
#define GLYPH_PLUS            52
#define GLYPH_MARIO_HEAD      53
#define GLYPH_LUIGI_HEAD      54
#define GLYPH_WARIO_HEAD      55
#define GLYPH_WALUIGI_HEAD    56
#define GLYPH_TOAD_HEAD       57
#define GLYPH_UMLAUT          58

void print_text_fmt_int(s32 x, s32 y, const char *str, s32 n);
void print_text(s32 x, s32 y, const char *str);
void print_text_centered(s32 x, s32 y, const char *str);
void render_text_labels(void);

#endif // PRINT_H
