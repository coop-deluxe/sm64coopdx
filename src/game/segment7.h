#ifndef SEGMENT7_H
#define SEGMENT7_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

// from main menu segment 7
extern const Gfx dl_menu_idle_hand[];
extern const Gfx dl_menu_grabbing_hand[];
extern const Gfx menu_hud_lut[];
extern const Gfx menu_font_lut[];
extern const Gfx dl_menu_ia8_text_begin[];
extern const Gfx dl_menu_ia8_text_end[];
extern const Gfx dl_menu_rgba16_wood_course[];
#ifdef VERSION_EU
extern const Gfx dl_menu_rgba16_wood_course_end[];
extern const Gfx dl_menu_texture_course_upper[];
extern const Gfx dl_menu_texture_niveau_upper[];
extern const Gfx dl_menu_texture_kurs_upper[];

extern const Gfx eu_course_strings_en_table[];
extern const Gfx eu_course_strings_fr_table[];
extern const Gfx eu_course_strings_de_table[];
#endif

// from intro_segment7
extern const Gfx intro_seg7_dl_0700B3A0[];
extern const Gfx intro_seg7_dl_0700C6A0[];
extern f32 intro_seg7_table_0700C790[];
extern f32 intro_seg7_table_0700C880[];

#endif // SEGMENT7_H
