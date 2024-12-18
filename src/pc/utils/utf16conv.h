//encoding madness (github.com/Davipb/utf8-utf16-converter/blob/master/converter/include/converter.h)
#pragma once
#include <stdint.h>
#include <stddef.h>

typedef uint8_t utf8_t; // The type of a single UTF-8 character
typedef uint16_t utf16_t; // The type of a single UTF-16 character

size_t utf8_to_utf16(
    utf8_t const* utf8, size_t utf8_len, 
    utf16_t* utf16,     size_t utf16_len
);

size_t utf16_to_utf8(
    utf16_t const* utf16, size_t utf16_len, 
    utf8_t* utf8,         size_t utf8_len
);