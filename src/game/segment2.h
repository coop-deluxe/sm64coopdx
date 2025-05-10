#ifndef SEGMENT2_H
#define SEGMENT2_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "dialog_ids.h"

extern u8* seg2_course_name_table[];
extern u8* seg2_course_name_table_original[];
extern u8* seg2_act_name_table[];
extern u8* seg2_act_name_table_original[];
extern const Gfx dl_rgba16_text_begin[];
extern const Gfx dl_rgba16_text_end[];
extern const Gfx dl_ia_text_begin[];
extern const Gfx dl_ia_text_end[];
extern Texture texture_transition_star_half[];
extern Texture texture_transition_circle_half[];
extern Texture texture_transition_mario[];
extern Texture texture_transition_bowser_half[];
extern Texture texture_waterbox_water[];
extern Texture texture_waterbox_mist[];
extern Texture texture_waterbox_jrb_water[];
extern Texture texture_waterbox_unknown_water[];
extern Texture texture_waterbox_lava[];
extern const Gfx dl_proj_mtx_fullscreen[];
extern const Gfx dl_draw_quad_verts_0123[];
extern const Gfx dl_screen_transition_end[];
extern const Gfx dl_transition_draw_filled_region[];
extern const Gfx dl_shadow_circle[];
extern const Gfx dl_shadow_square[];
extern const Gfx dl_shadow_spike_ext[];
extern const Gfx dl_shadow_9_verts[];
extern const Gfx dl_shadow_4_verts[];
extern const Gfx dl_shadow_end[];
extern const Gfx dl_skybox_begin[];
extern const Gfx dl_skybox_tile_tex_settings[];
extern const Gfx dl_skybox_end[];
extern const Gfx dl_waterbox_ia16_begin[];
extern const Gfx dl_waterbox_rgba16_begin[];
extern const Gfx dl_waterbox_end[];
extern const Gfx dl_paintings_draw_ripples[];
extern const Gfx dl_paintings_rippling_begin[];
extern const Gfx dl_paintings_rippling_end[];
extern const Gfx dl_paintings_env_mapped_begin[];
extern const Gfx dl_paintings_env_mapped_end[];
extern u8 seg2_painting_triangle_mesh[];
extern u8 seg2_painting_mesh_neighbor_tris[];
extern u8* main_hud_lut[58];
extern const Gfx dl_hud_img_load_tex_block[];
extern const Gfx dl_hud_img_begin[];
extern const Gfx dl_hud_img_end[];
extern void *main_font_lut[];
extern const Gfx dl_ia_text_tex_settings[];
extern const Gfx dl_rgba16_load_tex_block[];
extern void *main_credits_font_lut[];
extern u8* main_hud_camera_lut[6];
extern const Gfx dl_draw_text_bg_box[];
extern const Gfx dl_draw_triangle[];
extern const u8* seg2_dialog_original[];
extern void *seg2_dialog_table[];
extern const Gfx dl_billboard_num_0[];
extern const Gfx dl_billboard_num_1[];
extern const Gfx dl_billboard_num_2[];
extern const Gfx dl_billboard_num_3[];
extern const Gfx dl_billboard_num_4[];
extern const Gfx dl_billboard_num_5[];
extern const Gfx dl_billboard_num_6[];
extern const Gfx dl_billboard_num_7[];
extern const Gfx dl_billboard_num_8[];
extern const Gfx dl_billboard_num_9[];

#endif // SEGMENT2_H
