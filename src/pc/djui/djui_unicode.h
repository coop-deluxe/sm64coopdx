#pragma once

#include <PR/ultratypes.h>
#include <stdbool.h>

void djui_unicode_init(void);
u32 djui_unicode_get_sprite_index(const char* text);
f32 djui_unicode_get_sprite_width(const char* text, const f32 font_widths[], f32 unicodeScale);
char* djui_unicode_next_char(char* text);
char* djui_unicode_at_index(char* text, s32 index);
size_t djui_unicode_len(char* text);
bool djui_unicode_valid_char(const char* text);
void djui_unicode_cleanup_end(char* text);
char djui_unicode_get_base_char(const char* text);
void djui_unicode_get_char(const char* text, char* output);
