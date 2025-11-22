#pragma once
#include "djui.h"

struct DjuiSlider;

typedef void (*DjuiSliderFormatCallback)(struct DjuiSlider* slider, char* buf, int bufSize);

struct DjuiSlider {
    struct DjuiBase base;
    struct DjuiRect* rect;
    struct DjuiRect* rectValue;
    struct DjuiText* text;
    struct DjuiText* valueText;
    unsigned int* value;
    unsigned int min;
    unsigned int max;
    bool updateRectValueColor;
    DjuiSliderFormatCallback formatCallback;
};

struct DjuiSlider* djui_slider_create(struct DjuiBase* parent, const char* message, unsigned int* value, unsigned int min, unsigned int max, void (*on_value_change)(struct DjuiBase*));
void djui_slider_update_value(struct DjuiBase* base);

// Optional: eigenes Format für den Wert (z.B. "100%", "10s").
void djui_slider_set_format_callback(struct DjuiSlider* slider, DjuiSliderFormatCallback cb);

// Zugriff auf das mittige Value-Label, um z.B. Farben anzupassen.
struct DjuiText* djui_slider_get_value_text(struct DjuiSlider* slider);
