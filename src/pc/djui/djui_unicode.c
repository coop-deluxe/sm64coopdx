#include <PR/ultratypes.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "data/dynos_cmap.cpp.h"

#define SPRITE_INDEX_START_CHAR '!'

struct SmCodeGlyph {
    char unicode[4];
    char base;
    f32 width;
    u32 spriteIndex;
};

struct SmCodeGlyph sSmCodeGlyphs[] = {
    { "Á", 'A', 0, 0 },
    { "Å", 'A', 0, 0 },
    { "Â", 'A', 0, 0 },
    { "À", 'A', 0, 0 },
    { "Ã", 'A', 0, 0 },
    { "Ä", 'A', 0, 0 },
    { "Ç", 'C', 0, 0 },
    { "É", 'E', 0, 0 },
    { "Ê", 'E', 0, 0 },
    { "È", 'E', 0, 0 },
    { "Ë", 'E', 0, 0 },
    { "Í", 'I', 0, 0 },
    { "Î", 'I', 0, 0 },
    { "Ì", 'I', 0, 0 },
    { "Ï", 'I', 0, 0 },
    { "Ñ", 'N', 0, 0 },
    { "Ó", 'O', 0, 0 },
    { "Ô", 'O', 0, 0 },
    { "Ò", 'O', 0, 0 },
    { "Õ", 'O', 0, 0 },
    { "Ö", 'O', 0, 0 },
    { "Ú", 'U', 0, 0 },
    { "Û", 'U', 0, 0 },
    { "Ù", 'U', 0, 0 },
    { "Ü", 'U', 0, 0 },
    { "Ý", 'Y', 0, 0 },
    { "Ÿ", 'Y', 0, 0 },

    { "á", 'a', 0, 0 },
    { "å", 'a', 0, 0 },
    { "â", 'a', 0, 0 },
    { "à", 'a', 0, 0 },
    { "ã", 'a', 0, 0 },
    { "ä", 'a', 0, 0 },
    { "ç", 'c', 0, 0 },
    { "é", 'e', 0, 0 },
    { "ê", 'e', 0, 0 },
    { "è", 'e', 0, 0 },
    { "ë", 'e', 0, 0 },
    { "í", 'i', 0, 0 },
    { "î", 'i', 0, 0 },
    { "ì", 'i', 0, 0 },
    { "ï", 'i', 0, 0 },
    { "ñ", 'n', 0, 0 },
    { "ó", 'o', 0, 0 },
    { "ô", 'o', 0, 0 },
    { "ò", 'o', 0, 0 },
    { "õ", 'o', 0, 0 },
    { "ö", 'o', 0, 0 },
    { "ú", 'u', 0, 0 },
    { "û", 'u', 0, 0 },
    { "ù", 'u', 0, 0 },
    { "ü", 'u', 0, 0 },
    { "ý", 'y', 0, 0 },
    { "ÿ", 'y', 0, 0 },

    { "æ", 'a', 15, 0 },
    { "Æ", 'a', 16, 0 },
    { "œ", 'o', 15, 0 },
    { "Œ", 'o', 16, 0 },
    { "ð", 'd', 0, 0 },
    { "Ð", 'D', 14, 0 },
    { "ø", 'o', 0, 0 },
    { "Ø", 'O', 0, 0 },
    { "ß", 'S', 0, 0 },

    { "¡", '!', 0, 0 },
    { "¿", '?', 0, 0 },

    { "Б", 15, 0, 0 },
    { "Г", 14, 0, 0 },
    { "Д", 17, 0, 0 },
    { "Ж", 17, 0, 0 },
    { "З", 13, 0, 0 },
    { "И", 15, 0, 0 },
    { "Й", 15, 0, 0 },
    { "Л", 13, 0, 0 },
    { "П", 14, 0, 0 },
    { "У", 12, 0, 0 },
    { "Ф", 17, 0, 0 },
    { "Ц", 14, 0, 0 },
    { "Ч", 11, 0, 0 },
    { "Ш", 17, 0, 0 },
    { "Щ", 17, 0, 0 },
    { "Ъ", 13, 0, 0 },
    { "Ы", 17, 0, 0 },
    { "Ь", 12, 0, 0 },
    { "Ѣ", 14, 0, 0 },
    { "Э", 13, 0, 0 },
    { "Ю", 17, 0, 0 },
    { "Я", 13, 0, 0 },
    { "Є", 12, 0, 0 },

    { "а", 13, 0, 0 },
    { "б", 11, 0, 0 },
    { "в", 11, 0, 0 },
    { "г", 10, 0, 0 },
    { "д", 12, 0, 0 },
    { "ж", 15, 0, 0 },
    { "з", 13, 0, 0 },
    { "и", 12, 0, 0 },
    { "й", 12, 0, 0 },
    { "к",  9, 0, 0 },
    { "л", 10, 0, 0 },
    { "м", 11, 0, 0 },
    { "н", 11, 0, 0 },
    { "п", 11, 0, 0 },
    { "т", 11, 0, 0 },
    { "ф", 14, 0, 0 },
    { "ц", 11, 0, 0 },
    { "ч",  9, 0, 0 },
    { "ш", 17, 0, 0 },
    { "щ", 17, 0, 0 },
    { "ъ", 14, 0, 0 },
    { "ы", 17, 0, 0 },
    { "ь", 12, 0, 0 },
    { "ѣ", 13, 0, 0 },
    { "э", 12, 0, 0 },
    { "ю", 16, 0, 0 },
    { "я", 12, 0, 0 },
    { "є", 12, 0, 0 },

    { "Č", 'C', 0, 0 },
    { "č", 'c', 0, 0 },
    { "Ě", 'E', 0, 0 },
    { "ě", 'e', 0, 0 },
    { "Š", 'S', 0, 0 },
    { "š", 's', 0, 0 },
    { "Ř", 'R', 0, 0 },
    { "ř", 'r', 0, 0 },
    { "Ž", 'Z', 0, 0 },
    { "ž", 'z', 0, 0 },
    { "Ů", 'U', 0, 0 },
    { "ů", 'u', 0, 0 },
    { "Ď", 'D', 0, 0 },
    { "ď", 'd', 0, 0 },
    { "Ň", 'N', 0, 0 },
    { "ň", 'n', 0, 0 },
    { "Ť", 'T', 0, 0 },
    { "ť", 13, 0, 0 },

    { "ę", 'e', 0, 0 },
    { "ń", 'n', 0, 0 },
    { "ś", 's', 0, 0 },
    { "ć", 'c', 0, 0 },
    { "ź", 'z', 0, 0 },
    { "ż", 'z', 0, 0 },
    { "ł", 'l', 0, 0 },
    { "Ę", 'E', 0, 0 },
    { "Ń", 'N', 0, 0 },
    { "Ś", 'S', 0, 0 },
    { "Ć", 'C', 0, 0 },
    { "Ź", 'Z', 0, 0 },
    { "Ż", 'Z', 0, 0 },
    { "Ł", 'L', 0, 0 },
    { "Ą", 'A', 0, 0 },
    { "ą", 'a', 0, 0 },
    { "Ї", 'l', 0, 0 },
    { "ї", 'l', 0, 0 },
    { "Ґ", 'R', 0, 0 },
    { "ґ", 'R', 0, 0 },
};

struct SmCodeGlyph sSmCodeGlyphs_JP[] = {
#include "jp_glyphs.h"
};

struct SmCodeGlyph sSmCodeDuplicateGlyphs[] = {
    { "А", 'A', 0, 0 },
    { "В", 'B', 0, 0 },
    { "Е", 'E', 0, 0 },
    { "К", 'K', 0, 0 },
    { "М", 'M', 0, 0 },
    { "Н", 'H', 0, 0 },
    { "О", 'O', 0, 0 },
    { "Р", 'P', 0, 0 },
    { "С", 'C', 0, 0 },
    { "Т", 'T', 0, 0 },
    { "Х", 'X', 0, 0 },
    { "е", 'e', 0, 0 },
    { "о", 'o', 0, 0 },
    { "р", 'p', 0, 0 },
    { "с", 'c', 0, 0 },
    { "у", 'y', 0, 0 },
    { "х", 'x', 0, 0 },
};

static void* sCharMap = NULL;

static s32 count_bytes_for_char(char* text) {
    s32 bytes = 0;
    u8 mask = (1 << 7);
    while (*text & mask) {
        bytes++;
        mask >>= 1;
    }
    return bytes ? bytes : 1;
}

static u64 convert_unicode_char_to_u64(char* text) {
    s32 bytes = count_bytes_for_char(text);
    u64 value = (u8)*text;

    // HACK: we only support up to 4 bytes per character
    if (bytes > 4) { return 0; }

    bytes--;
    while (bytes > 0) {
        value <<= 8;
        value |= (u8)*(++text);
        bytes--;
    }
    return value;
}

void djui_unicode_init(void) {
    sCharMap = hmap_create(true);

    size_t glyphCount = sizeof(sSmCodeGlyphs) / sizeof(sSmCodeGlyphs[0]);
    for (size_t i = 0; i < glyphCount; i++) {
        struct SmCodeGlyph* glyph = &sSmCodeGlyphs[i];
        glyph->spriteIndex = (128 + i) - SPRITE_INDEX_START_CHAR;

        u64 key = convert_unicode_char_to_u64(glyph->unicode);
        s32 bytes = count_bytes_for_char(glyph->unicode);
        assert(bytes >= 2 && bytes <= 4);
        assert(key > 127);
        hmap_put(sCharMap, key, glyph);
    }
    
    //add japanese glyphs
    size_t jpCount = sizeof(sSmCodeGlyphs_JP) / sizeof(sSmCodeGlyphs_JP[0]);
    for (size_t i = 0; i < jpCount; i++) {
        struct SmCodeGlyph* glyph = &sSmCodeGlyphs_JP[i];
        glyph->spriteIndex = 0x010000 + i;
        u64 key = convert_unicode_char_to_u64(glyph->unicode);
        s32 bytes = count_bytes_for_char(glyph->unicode);
        assert(bytes >= 2 && bytes <= 4);
        assert(key > 127);
        hmap_put(sCharMap, key, glyph);
    }

    // add duplicate glyphs
    size_t dupCount = sizeof(sSmCodeDuplicateGlyphs) / sizeof(sSmCodeDuplicateGlyphs[0]);
    for (size_t i = 0; i < dupCount; i++) {
        struct SmCodeGlyph* glyph = &sSmCodeDuplicateGlyphs[i];
        assert((u32)glyph->base < 128);
        assert((u32)glyph->base > SPRITE_INDEX_START_CHAR);
        glyph->spriteIndex = ((u32)glyph->base) - SPRITE_INDEX_START_CHAR;

        u64 key = convert_unicode_char_to_u64(glyph->unicode);
        s32 bytes = count_bytes_for_char(glyph->unicode);
        assert(bytes >= 2 && bytes <= 4);
        assert(key > 127);
        hmap_put(sCharMap, key, glyph);
    }
}

u32 djui_unicode_get_sprite_index(char* text) {
    // check for ASCI
    if ((u8)*text < 128) {
        // make sure it's in the valid range
        if ((u8)*text < SPRITE_INDEX_START_CHAR) {
            return (u8)'?' - SPRITE_INDEX_START_CHAR;
        }

        // output the ASCII index
        return (u8)*text - SPRITE_INDEX_START_CHAR;
    }

    // retrieve the character
    u64 key = convert_unicode_char_to_u64(text);

    // retrieve the sprite glyph
    struct SmCodeGlyph* glyph = hmap_get(sCharMap, key);
    if (glyph) {
        return glyph->spriteIndex;
    }

    // return default value
    return (u8)'?' - SPRITE_INDEX_START_CHAR;
}

f32 djui_unicode_get_sprite_width(char* text, const f32 font_widths[], f32 unicodeScale) {
    if (!text) { return 0; }

    // check for ASCII
    if ((u8)*text < 128) {
        // make sure it's in the valid range
        if ((u8)*text < SPRITE_INDEX_START_CHAR) {
            return font_widths[(u8)'?' - SPRITE_INDEX_START_CHAR];
        }

        // output the ASCII width
        return font_widths[(u8)*text - SPRITE_INDEX_START_CHAR];
    }

    // retrieve the character
    u64 key = convert_unicode_char_to_u64(text);

    // retrieve the glyph
    struct SmCodeGlyph* glyph = hmap_get(sCharMap, key);
    if (glyph) {
        if (glyph->width) {
            // use the custom width
            return glyph->width / unicodeScale;
        }
        if ((u8)glyph->base < (u8)'!') {
            return glyph->base / unicodeScale;
        }
        // use the base width
        return font_widths[(u8)glyph->base - SPRITE_INDEX_START_CHAR];
    }

    // return default value
    return font_widths[(u8)'?' - SPRITE_INDEX_START_CHAR];
}

char* djui_unicode_next_char(char* text) {
    s32 bytes = count_bytes_for_char(text);
    while (bytes-- > 0) {
        if (*text == '\0') { return text; }
        text++;
    }
    return text;
}

char* djui_unicode_at_index(char* text, s32 index) {
    while (index-- > 0) {
        text = djui_unicode_next_char(text);
    }
    return text;
}

size_t djui_unicode_len(char* text) {
    size_t len = 0;
    while (*text) {
        text = djui_unicode_next_char(text);
        len++;
    }
    return len;
}

bool djui_unicode_valid_char(char* text) {
    if ((u8)*text < 128) {
        return ((u8)*text >= ' ');
    }
    u64 key = convert_unicode_char_to_u64(text);
    struct SmCodeGlyph* glyph = hmap_get(sCharMap, key);
    return glyph != NULL;
}

void djui_unicode_cleanup_end(char* text) {
    s32 slen = strlen(text);
    s32 idx = strlen(text);
    bool foundMulti = false;
    if (idx < 2) { return; }
    idx--;

    // look for the start of a byte sequence
    while (idx >= 0 && text[idx] & (1 << 7)) {
        foundMulti = true;
        if ((text[idx] & 192) == 192) {
            break;
        }
        idx--;
    }

    if (!foundMulti) { return; }
    if (idx < 0) { return; }

    s32 bytes = count_bytes_for_char(&text[idx]);
    if (bytes <= 1) {
        text[idx] = '\0';
        return;
    }

    if ((slen - idx) != bytes) {
        text[idx] = '\0';
    }
}

char djui_unicode_get_base_char(char* text) {
    if ((u8)*text < ' ') { return '?'; }
    if ((u8)*text < 128) { return *text; }
    if (!sCharMap) { return '?'; }
    u64 key = convert_unicode_char_to_u64(text);
    struct SmCodeGlyph* glyph = hmap_get(sCharMap, key);
    return (glyph == NULL) ? '?' : glyph->base;
}

void djui_unicode_get_char(char* text, char* output) {
    s32 bytes = count_bytes_for_char(text);
    while (bytes-- > 0) {
        *output = *text;
        output++;
        text++;
    }
    *output = '\0';
}
