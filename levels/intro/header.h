#ifndef INTRO_HEADER_H
#define INTRO_HEADER_H

#include "types.h"

// geo
extern const GeoLayout intro_geo_0002D0[];
extern const GeoLayout intro_geo_mario_head_regular[];
extern const GeoLayout intro_geo_mario_head_dizzy[];
extern const GeoLayout intro_geo_000414[];

// leveldata
extern const Gfx intro_seg7_dl_0700B3A0[];
extern const Gfx intro_seg7_dl_0700C6A0[];
extern const f32 intro_seg7_table_0700C790[];
extern const f32 intro_seg7_table_0700C880[];

// script
extern const LevelScript level_intro_splash_screen[];
extern const LevelScript level_intro_mario_head_regular[];
extern const LevelScript level_intro_mario_head_dizzy[];
extern const LevelScript level_intro_debug_level_select[];
extern const LevelScript level_intro_goto_file_select[];
extern const LevelScript level_intro_goto_debug_level_select[];
extern const LevelScript level_intro_goto_main_scripts_stop_music[];
extern const LevelScript level_intro_goto_main_scripts[];
extern const LevelScript level_intro_goto_splash_screen[];

#endif
