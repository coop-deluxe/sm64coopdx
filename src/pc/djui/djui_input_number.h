#pragma once
#include "djui_inputbox.h"

#define NUMTYPE_SIGNED (1 << 7)
#define NUMTYPE_U(bits) NUMTYPE_U## bits = bits
#define NUMTYPE_S(bits) NUMTYPE_S## bits = bits | NUMTYPE_SIGNED

// Add types as needed
enum InputNumberType {
    NUMTYPE_U(32),
    NUMTYPE_S(32)
};

struct DjuiInputNumber {
    struct DjuiInputbox input;
    enum InputNumberType type;
    u8 digits;
    s64 min, max;
    void *value; s64 saved;
    bool valid;
};

void djui_input_number_text_change(struct DjuiBase *caller);

// Add types as needed
#define djui_input_number_create(parent, value, min, max) _djui_input_number_create(parent, value, \
    _Generic((value), \
        u32 *: NUMTYPE_U32, \
        s32 *: NUMTYPE_S32 \
    ), min, max)

struct DjuiInputNumber *_djui_input_number_create(struct DjuiBase *parent, void *value, enum InputNumberType type, s64 min, s64 max);
