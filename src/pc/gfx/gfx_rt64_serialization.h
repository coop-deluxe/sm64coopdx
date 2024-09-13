#ifndef GFX_RT64_SERIALIZATION_H
#define GFX_RT64_SERIALIZATION_H

#include <string>
#include <stdint.h>

extern uint64_t gfx_rt64_get_texture_name_hash(const std::string &name);
extern void gfx_rt64_default_level_lights();
extern void gfx_rt64_load_level_lights();
extern void gfx_rt64_save_level_lights();
extern void gfx_rt64_load_geo_layout_mods();
extern void gfx_rt64_save_geo_layout_mods();
extern void gfx_rt64_load_texture_mods();
extern void gfx_rt64_save_texture_mods();

#endif
