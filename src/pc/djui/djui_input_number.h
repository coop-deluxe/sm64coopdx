#pragma once
#include "djui_inputbox.h"

struct DjuiInputNumber {
    struct DjuiInputbox input;
    int min, max;
    int *value;
    int saved;
    bool valid;
};

void djui_input_number_text_change(struct DjuiBase *caller);

struct DjuiInputNumber* djui_input_number_create(struct DjuiBase* parent, int *value, int min, int max);
