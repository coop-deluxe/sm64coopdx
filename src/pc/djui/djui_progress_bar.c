#include "djui.h"

void djui_progress_bar_render_pre(struct DjuiBase* base, UNUSED bool* unused) {
    struct DjuiProgressBar* progress = (struct DjuiProgressBar*)base;
    progress->smoothValue = progress->smoothValue * progress->smoothenHigh + *progress->value * progress->smoothenLow;
    float min = progress->min;
    float max = progress->max;
    djui_base_set_size(&progress->rectValue->base, ((f32)progress->smoothValue - min) / ((f32)max - min), 1.0f);
}

void djui_progress_bar_render_pre_infinite(struct DjuiBase* base, UNUSED bool* unused) {
    struct DjuiProgressBar* progress = (struct DjuiProgressBar*)base;
    float min = progress->min;
    float max = progress->max;

    progress->smoothValue = progress->smoothValue * progress->smoothenHigh + *progress->value * progress->smoothenLow;
    float modValue = progress->smoothValue - ((int)progress->smoothValue);
    float x = (modValue - min - 0.25f) / (max - min - 0.25f);
    float w = 0.25f;
    if (x + w > 1.0f) { w = 1.0f - x; }

    djui_base_set_location(&progress->rectValue->base, x, 0);
    djui_base_set_size(&progress->rectValue->base, w, 1.0f);
}

static void djui_progress_bar_set_default_style(struct DjuiBase* base) {
    struct DjuiProgressBar* progress = (struct DjuiProgressBar*)base;
    djui_base_set_border_color(&progress->rect->base, 173, 173, 173, 255);
    djui_base_set_color(&progress->rect->base, 0, 0, 0, 0);
    djui_base_set_color(&progress->rectValue->base, 220, 220, 220, 255);
}

static void djui_progress_bar_destroy(struct DjuiBase* base) {
    struct DjuiProgressBar* progress = (struct DjuiProgressBar*)base;
    free(progress);
}

struct DjuiProgressBar* djui_progress_bar_create(struct DjuiBase* parent, float* value, float min, float max, bool infinite) {
    struct DjuiProgressBar* progress = calloc(1, sizeof(struct DjuiProgressBar));
    struct DjuiBase* base = &progress->base;

    progress->value = value;
    progress->smoothValue = *value;
    progress->min = min;
    progress->max = max;
    progress->smoothenHigh = 0.95f;
    progress->smoothenLow = 0.05f;

    djui_base_init(parent, base, NULL, djui_progress_bar_destroy);
    djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 1.0f, 16);
    base->on_render_pre = infinite ? djui_progress_bar_render_pre_infinite : djui_progress_bar_render_pre;

    struct DjuiRect* rect = djui_rect_create(&progress->base);
    djui_base_set_size_type(&rect->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&rect->base, 1.0f, 1.0f);
    djui_base_set_color(&rect->base, 0, 0, 0, 0);
    djui_base_set_border_width(&rect->base, 2);
    progress->rect = rect;

    struct DjuiRect* rectValue = djui_rect_create(&rect->base);
    djui_base_set_size_type(&rectValue->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    progress->rectValue = rectValue;

    if (infinite) {
        djui_base_set_location_type(&progress->rectValue->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size_type(&progress->rectValue->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    }

    djui_progress_bar_set_default_style(base);

    return progress;
}
