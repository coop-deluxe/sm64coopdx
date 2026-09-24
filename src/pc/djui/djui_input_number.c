#include "djui.h"

static void djui_input_number_render_pre(struct DjuiBase* base, UNUSED bool* unused) {
    struct DjuiInputNumber *number = (struct DjuiInputNumber*)base;
    if (*number->value != number->saved) {
        number->saved = *number->value;
        snprintf(number->input.buffer, number->input.bufferSize, "%d", number->saved);
    }
}

static void djui_input_number_on_text_input(struct DjuiBase *base, char *text) {
    struct DjuiInputNumber *number = (struct DjuiInputNumber*)base;
    struct DjuiInputbox *inputbox = &number->input;
    if (*text == '-') {
        if (*inputbox->buffer != '-' && number->min < 0) {
            u16 sel[2];
            sel[0] = ++inputbox->selection[0];
            sel[1] = ++inputbox->selection[1];
            djui_inputbox_move_cursor_to_position(inputbox, 0);
            djui_inputbox_on_text_input(base, "-");
            inputbox->selection[0] = sel[0];
            inputbox->selection[1] = sel[1];
        }

        text++;
    } else if (*text == '+') {
        if (*inputbox->buffer == '-') {
            u16 sel[2];
            sel[0] = --inputbox->selection[0];
            sel[1] = --inputbox->selection[1];
            inputbox->selection[0] = 1;
            inputbox->selection[1] = 0;
            djui_inputbox_on_text_input(base, "");
            inputbox->selection[0] = sel[0];
            inputbox->selection[1] = sel[1];
        }

        text++;
    }

    char *tinput = text;
    while (*tinput != '\0') {
        if (*tinput < '0' || *tinput > '9') {
            *tinput = '\0';
        } else {
            tinput++;
        }
    }

    if (*text != '\0') {
        djui_inputbox_on_text_input(base, text);
    }
}

void djui_input_number_text_change(struct DjuiBase *caller) {
    struct DjuiInputNumber *number = (struct DjuiInputNumber*)caller;
    struct DjuiTheme *theme = gDjuiThemes[configDjuiTheme];
    struct DjuiColor *textColor = &theme->interactables.textColor;
    int value = atoi(number->input.buffer);
    number->valid = value >= number->min && value <= number->max;
    if (number->valid) {
        djui_inputbox_set_text_color(&number->input, textColor->r, textColor->g, textColor->b, textColor->a);
        *number->value = number->saved = value;
    } else {
        djui_inputbox_set_text_color(&number->input, 255, 0, 0, 255);
    }
}

struct DjuiInputNumber *djui_input_number_create(struct DjuiBase *parent, int *value, int min, int max) {
    struct DjuiInputNumber *number = (struct DjuiInputNumber*)djui_inputbox_init(parent, calloc(1, sizeof(struct DjuiInputNumber)), 20);
    number->value = value;
    number->saved = *value;
    number->min = min;
    number->max = max;
    number->valid = true;
    djui_interactable_hook_text_input(&number->input.base, djui_input_number_on_text_input);
    djui_interactable_hook_value_change(&number->input.base, djui_input_number_text_change);
    number->input.base.on_render_pre = djui_input_number_render_pre;
    
    djui_inputbox_set_number(&number->input, *value);
    return number;
}
