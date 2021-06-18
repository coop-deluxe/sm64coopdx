#pragma once
#include "djui.h"

#pragma pack(1)
struct DjuiColor {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

enum DjuiScreenValueType { DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE };

#pragma pack(1)
struct DjuiScreenValue {
    enum DjuiScreenValueType type;
    f32 value;
};

enum DjuiHAlign { DJUI_HALIGN_LEFT, DJUI_HALIGN_CENTER, DJUI_HALIGN_RIGHT };
enum DjuiVAlign { DJUI_VALIGN_TOP, DJUI_VALIGN_CENTER, DJUI_VALIGN_BOTTOM };
