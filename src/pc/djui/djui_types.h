#pragma once
#include "djui.h"

// forward declaration
struct DjuiBase;

struct DjuiColor {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

enum DjuiScreenValueType { DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE, DJUI_SVT_ASPECT_RATIO };
enum DjuiFlowDirection { DJUI_FLOW_DIR_DOWN, DJUI_FLOW_DIR_UP, DJUI_FLOW_DIR_RIGHT, DJUI_FLOW_DIR_LEFT };

struct DjuiScreenValue {
    enum DjuiScreenValueType type;
    f32 value;
};

enum DjuiHAlign { DJUI_HALIGN_LEFT, DJUI_HALIGN_CENTER, DJUI_HALIGN_RIGHT };
enum DjuiVAlign { DJUI_VALIGN_TOP, DJUI_VALIGN_CENTER, DJUI_VALIGN_BOTTOM };

struct DjuiHookSlice {
    void *ptr;
    size_t size;
    bool (*on_changed)(struct DjuiBase *);
};
