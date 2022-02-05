#pragma once
#include "djui.h"

struct DjuiSlider {
    struct DjuiBase base;
    struct DjuiRect* rect;
    struct DjuiRect* rectValue;
    struct DjuiText* text;
    unsigned int* value;
    unsigned int min;
    unsigned int max;
};

struct DjuiSlider* djui_slider_create(struct DjuiBase* parent, const char* message, unsigned int* value, unsigned int min, unsigned int max);
