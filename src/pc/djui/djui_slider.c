#include "djui.h"

void djui_slider_update_style(struct DjuiBase* base) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    f32 x = slider->rect->base.elem.x;
    bool activeRegion = (gCursorX >= x);

    enum DjuiThemeElements borderElement;
    enum DjuiThemeElements rectValueElement;
    enum DjuiThemeElements textElement;

    if (!slider->base.enabled) {
        borderElement = DJUI_THEME_ELEMENT_SLIDER_BORDER_DISABLED;
        rectValueElement = DJUI_THEME_ELEMENT_SLIDER_DISABLED;
        textElement = DJUI_THEME_ELEMENT_TEXT_DISABLED;
    } else if (gInteractableFocus == base) {
        borderElement = DJUI_THEME_ELEMENT_SLIDER_BORDER_DOWN;
        rectValueElement = DJUI_THEME_ELEMENT_SLIDER_DOWN;
        textElement = DJUI_THEME_ELEMENT_TEXT;
    } else if (gDjuiCursorDownOn == base && activeRegion) {
        borderElement = DJUI_THEME_ELEMENT_SLIDER_BORDER_DOWN;
        rectValueElement = DJUI_THEME_ELEMENT_SLIDER_DOWN;
        textElement = DJUI_THEME_ELEMENT_TEXT;
    } else if (gDjuiHovered == base && activeRegion) {
        borderElement = DJUI_THEME_ELEMENT_SLIDER_BORDER_HOVER;
        rectValueElement = DJUI_THEME_ELEMENT_SLIDER_HOVER;
        textElement = DJUI_THEME_ELEMENT_TEXT;
    } else {
        borderElement = DJUI_THEME_ELEMENT_SLIDER_BORDER;
        rectValueElement = DJUI_THEME_ELEMENT_SLIDER;
        textElement = DJUI_THEME_ELEMENT_TEXT;
    }

    djui_base_set_border_color_with_color(&slider->rect->base, configDjuiTheme.elements[borderElement]);
    djui_base_set_color(&slider->rect->base, 0, 0, 0, 0);
    djui_base_set_color_with_color(&slider->text->base, configDjuiTheme.elements[textElement]);
    if (slider->updateRectValueColor) {
        djui_base_set_color_with_color(&slider->rectValue->base, configDjuiTheme.elements[rectValueElement]);
    }
}

void djui_slider_update_value(struct DjuiBase* base) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    u32  min   = slider->min;
    u32  max   = slider->max;
    u32* value = slider->value;
    if (slider->rectValue != NULL && value != NULL) {
        djui_base_set_size(&slider->rectValue->base, ((f32)*value - min) / ((f32)max - min), 1.0f);
    }
}

static void djui_slider_get_cursor_hover_location(struct DjuiBase* base, f32* x, f32* y) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    struct DjuiBase* rectBase = &slider->rect->base;
    *x = (rectBase->elem.x + rectBase->elem.width  * 3.0f / 4.0f);
    *y = (rectBase->elem.y + rectBase->elem.height * 3.0f / 4.0f);
}

static void djui_slider_on_cursor_down(struct DjuiBase* base) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    u32  min   = slider->min;
    u32  max   = slider->max;
    u32* value = slider->value;
    f32 x = slider->rect->base.elem.x;
    f32 w = slider->rect->base.elem.width;
    f32 cursorX = gCursorX;
    cursorX = fmax(cursorX, x);
    cursorX = fmin(cursorX, x + w);
    *value = ((cursorX - x) / w) * (max - min) + min;
    if (base != NULL && base->interactable != NULL && base->interactable->on_value_change != NULL) {
        base->interactable->on_value_change(base);
    }
    djui_slider_update_value(base);
}

static void djui_slider_on_cursor_down_begin(struct DjuiBase* base, bool inputCursor) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    f32 x = slider->rect->base.elem.x;
    if (gCursorX >= x) {
        if (inputCursor) {
            djui_interactable_set_input_focus(base);
        } else {
            slider->base.interactable->on_cursor_down = djui_slider_on_cursor_down;
        }
    } else {
        slider->base.interactable->on_cursor_down = NULL;
    }
}

static void djui_slider_on_cursor_down_end(struct DjuiBase* base) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    slider->base.interactable->on_cursor_down = NULL;
}

static void djui_slider_on_focus(struct DjuiBase* base, OSContPad* pad) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    if (abs(pad->stick_x) < 32) { return; }
    int value = *slider->value;
    value += (pad->stick_x > 0) ? 1 : -1;
    value = fmin(value, (int)slider->max);
    value = fmax(value, (int)slider->min);
    *slider->value = value;
    if (base != NULL && base->interactable != NULL && base->interactable->on_value_change != NULL) {
        base->interactable->on_value_change(base);
    }
    djui_slider_update_value(base);
}

static void djui_slider_destroy(struct DjuiBase* base) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    free(slider);
}

struct DjuiSlider* djui_slider_create(struct DjuiBase* parent, const char* message, unsigned int* value, unsigned int min, unsigned int max, void (*on_value_change)(struct DjuiBase*)) {
    struct DjuiSlider* slider = calloc(1, sizeof(struct DjuiSlider));
    struct DjuiBase* base     = &slider->base;

    slider->value = value;
    slider->min = min;
    slider->max = max;

    slider->updateRectValueColor = true;

    djui_base_init(parent, base, NULL, djui_slider_destroy);
    djui_interactable_create(base, djui_slider_update_style);
    djui_interactable_hook_cursor_down(base, djui_slider_on_cursor_down_begin, NULL, djui_slider_on_cursor_down_end);
    djui_interactable_hook_focus(base, NULL, djui_slider_on_focus, NULL);

    struct DjuiText* text = djui_text_create(&slider->base, message);
    djui_base_set_alignment(&text->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&text->base, 0.6f, 1.0f);
    djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    slider->text = text;

    struct DjuiRect* rect = djui_rect_create(&slider->base);
    djui_base_set_alignment(&rect->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&rect->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&rect->base, 0.45f, 1.0f);
    djui_base_set_color(&rect->base, 0, 0, 0, 0);
    djui_base_set_border_width(&rect->base, 2);
    slider->rect = rect;

    struct DjuiRect* rectValue = djui_rect_create(&rect->base);
    djui_base_set_size_type(&rectValue->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    slider->rectValue = rectValue;

    djui_slider_update_value(base);
    djui_slider_update_style(base);

    base->get_cursor_hover_location = djui_slider_get_cursor_hover_location;

    djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_interactable_hook_value_change(base, on_value_change);
    djui_base_set_size(base, 1.0f, 32);

    return slider;
}
