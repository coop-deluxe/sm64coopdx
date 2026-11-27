#pragma once
#include "djui_inputbox.h"

// NUMTYPE(type, bits, flag)
// #define TYPE_NEGATIVE (1 << 5)
#define TYPE_FLOAT (1 << 5)
#define TYPE_SIGNED (1 << 4)
#define NUMTYPE_U(bits) NUMTYPE(u##bits, bits, 0)
#define NUMTYPE_S(bits) NUMTYPE(s##bits, bits, TYPE_SIGNED)
#define NUMTYPE_F(bits) NUMTYPE(f##bits, bits, TYPE_FLOAT)

typedef union {
    #define NUMTYPE(type, _1, _2) \
    type as_##type;
    #include "djui_input_types.inl"
    #undef NUMTYPE  
} InputNumber;

enum InputNumberType {
    #define NUMTYPE(type, bits, flag) \
    NUMTYPE_##type = (bits >> 3) | flag,
    #include "djui_input_types.inl"
    #undef NUMTYPE
};

struct DjuiInputNumber {
    struct DjuiInputbox input;
    u8 type, digits, decimals;
    InputNumber min, max, saved;
    void *value;
    bool valid;
};

void djui_input_number_text_change(struct DjuiBase *caller);

struct DjuiInputNumber *djui_input_number_create(struct DjuiBase *parent, void *value, u8 type, InputNumber min, InputNumber max, u8 decimals);

#define NUMTYPE(type, _1, _2) \
struct DjuiInputNumber *djui_input_##type##_create(struct DjuiBase *parent, type *value, type min, type max);
#undef NUMTYPE_F
#define NUMTYPE_F(bits) \
struct DjuiInputNumber *djui_input_f##bits##_create(struct DjuiBase *parent, f##bits *value, f##bits min, f##bits max, u8 decimals);
#include "djui_input_types.inl"
#undef NUMTYPE
#undef NUMTYPE_F
#define NUMTYPE_F(bits) NUMTYPE(f##bits, bits, TYPE_FLOAT)