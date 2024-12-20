#pragma once
#include "djui.h"

struct DjuiPaginated {
    struct DjuiBase base;
    struct DjuiFlowLayout* layout;
    struct DjuiButton* prevButton;
    struct DjuiButton* nextButton;
    struct DjuiText* pageNumText;
    s32 startIndex;
    s32 showCount;
    bool showMaxCount;
};

void djui_paginated_update_page_buttons(struct DjuiPaginated* paginated);
void djui_paginated_calculate_height(struct DjuiPaginated* paginated);
struct DjuiPaginated* djui_paginated_create(struct DjuiBase* parent, u32 showCount);
