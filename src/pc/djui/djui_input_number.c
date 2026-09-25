#include "djui.h"
#include <errno.h>

static void djui_input_number_on_text_input(struct DjuiBase *base, char *text) {
    struct DjuiInputNumber *number = (struct DjuiInputNumber*)base;
    u16 *sel = number->input.selection;
    char *msg = number->input.buffer;

    if (*text == '-') {
        if (*msg != '-' && number->min < 0) {
            memmove(msg + 1, msg, strlen(msg) + 1);
            *msg = '-'; sel[0]++; sel[1]++;
            djui_input_number_text_change(base);
        }

        text++;
    } else if (*text == '+') {
        if (*msg == '-') {
            memmove(msg, msg + 1, strlen(msg));
            if (sel[0] > 0) { sel[0]--; }
            if (sel[1] > 0) { sel[1]--; }
            djui_input_number_text_change(base);
        }

        text++;
    }

    if (*msg == '-' && sel[0] == 0 && sel[1] == 0) {
        sel[0] = sel[1] = 1;
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
    struct DjuiInputbox *input = &number->input;
    char *text = input->buffer;

    input->bufferSize = *text == '-' ? 12 : 11;

    errno = 0; long value = strtol(text, NULL, 10);
    number->valid =
        !(*text == '\0' || (*text == '-' && text[1] == '\0'))
        && errno != ERANGE && value >= number->min && value <= number->max;

    if (number->valid) {
        struct DjuiColor *textColor = &gDjuiThemes[configDjuiTheme]->interactables.textColor;
        djui_inputbox_set_text_color(input, textColor->r, textColor->g, textColor->b, textColor->a);
        *number->value = number->saved = value;
    } else {
        djui_inputbox_set_text_color(input, 255, 0, 0, 255);
    }
}

static void djui_input_number_render_pre(struct DjuiBase* base, UNUSED bool* unused) {
    struct DjuiInputNumber *number = (struct DjuiInputNumber*)base;
    if (*number->value != number->saved) {
        number->saved = *number->value;
        number->input.bufferSize = 12;
        djui_inputbox_set_number(&number->input, number->saved);
        djui_input_number_text_change(base);
    }
}

struct DjuiInputNumber *djui_input_number_create(struct DjuiBase *parent, int *value, int min, int max) {
    struct DjuiInputNumber *number = calloc(1, sizeof(struct DjuiInputNumber));
    struct DjuiBase *base = &number->input.base;
    djui_inputbox_init(parent, &number->input, 12);
    djui_interactable_hook_text_input(base, djui_input_number_on_text_input);
    djui_interactable_hook_value_change(base, djui_input_number_text_change);
    base->on_render_pre = djui_input_number_render_pre;
    number->value = value; number->saved = *value;
    number->min = min; number->max = max;
    
    djui_inputbox_set_number(&number->input, *value);
    djui_input_number_text_change(base);
    return number;
}
