#include "djui.h"
#include <errno.h>

#define S32_MAX_SIZE 12 // -2147483647|

// Add types as needed
static s32 djui_input_number_get_value(struct DjuiInputNumber *number) {
    switch (number->type) {
        case NUMTYPE_U32: return *(u32 *)number->value;
        case NUMTYPE_S32: return *(s32 *)number->value;
    }
}

static void djui_input_number_on_text_input(struct DjuiBase *base, char *text) {
    struct DjuiInputNumber *number = (struct DjuiInputNumber *)base;
    u16 *sel = number->input.selection;
    char *msg = number->input.buffer;

    if (*text == '-') {
        if (number->type & NUMTYPE_SIGNED && *msg != '-' && number->min < 0) {
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
    struct DjuiInputNumber *number = (struct DjuiInputNumber *)caller;
    struct DjuiInputbox *input = &number->input;
    char *end, *text = input->buffer;

    input->bufferSize = number->digits + (*text == '-' ? 2 : 1);

    errno = 0;
    s64 value = strtol(text, &end, 10);
    number->valid = text != end && errno != ERANGE && (
        (number->type & NUMTYPE_SIGNED)
            ? number->min <= value && value <= number->max
            : ((u32)number->min <= (u32)value && (u32)value <= (u32)number->max)
        );

    if (number->valid) {
        struct DjuiColor *textColor = &gDjuiThemes[configDjuiTheme]->interactables.textColor;
        djui_inputbox_set_text_color(input, textColor->r, textColor->g, textColor->b, textColor->a);
        number->saved = value;
        switch (number->type) { // Add types as needed
            case NUMTYPE_U32: *(u32 *)number->value = value; break;
            case NUMTYPE_S32: *(s32 *)number->value = value; break;
        }
    } else {
        djui_inputbox_set_text_color(input, 255, 0, 0, 255);
    }
}

static void djui_input_number_render_pre(struct DjuiBase *base, UNUSED bool *unused) {
    struct DjuiInputNumber *number = (struct DjuiInputNumber *)base;
    s32 value = djui_input_number_get_value(number);
    if (value != number->saved) {
        number->saved = value;
        number->input.bufferSize = S32_MAX_SIZE;
        djui_inputbox_set_number(&number->input, number->saved);
        djui_input_number_text_change(base);
    }
}

struct DjuiInputNumber *_djui_input_number_create(struct DjuiBase *parent, void *value, enum InputNumberType type, s32 min, s32 max) {
    struct DjuiInputNumber *number = calloc(1, sizeof(struct DjuiInputNumber));
    struct DjuiInputbox *input = &number->input;
    struct DjuiBase *base = &input->base;
    djui_inputbox_init(parent, input, S32_MAX_SIZE);
    djui_interactable_hook_text_input(base, djui_input_number_on_text_input);
    djui_interactable_hook_value_change(base, djui_input_number_text_change);
    base->on_render_pre = djui_input_number_render_pre;
    number->min = min; number->max = max;
    number->value = value; number->type = type;
    char *text = input->buffer;
    djui_inputbox_set_number(input, max);
    number->digits = strlen(text + (*text == '-'));
    djui_inputbox_set_number(input, min);
    number->digits = MAX(number->digits, strlen(text + (*text == '-')));

    djui_inputbox_set_number(input, number->saved = djui_input_number_get_value(number));
    djui_input_number_text_change(base);
    return number;
}
