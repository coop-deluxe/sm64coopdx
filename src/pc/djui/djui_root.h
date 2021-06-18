#pragma once
#include "djui.h"

#pragma pack(1)
struct DjuiRoot {
    struct DjuiBase base;
};

struct DjuiRoot* djui_root_create(void);
