#include <PR/ultratypes.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "data/dynos_cmap.cpp.h"

#define SPRITE_INDEX_START_CHAR '!'

struct SmCodeGlyph {
    char unicode[3];
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

    { "æ", 'a', 0.5000f, 0 },
    { "Æ", 'a', 0.6000f, 0 },
    { "œ", 'o', 0.5000f, 0 },
    { "Œ", 'o', 0.5000f, 0 },
    { "ð", 'd', 0, 0 },
    { "Ð", 'D', 0.4375f, 0 },
    { "ø", 'o', 0, 0 },
    { "Ø", 'O', 0, 0 },
    { "ß", 'S', 0, 0 },

    { "¡", '!', 0, 0 },
    { "¿", '?', 0, 0 },
};

static void* sCharMap = NULL;
static void* sCharIter = NULL;

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
        text++;
    }
    return value;
}

void djui_unicode_init(void) {
    sCharMap = hmap_create();
    sCharIter = hmap_iter(sCharMap);

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

f32 djui_unicode_get_sprite_width(char* text, const f32 font_widths[]) {
    // check for ASCI
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
            return glyph->width;
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
    u64 key = convert_unicode_char_to_u64(text);
    struct SmCodeGlyph* glyph = hmap_get(sCharMap, key);
    return (glyph != NULL) ? glyph->base : '?';
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
