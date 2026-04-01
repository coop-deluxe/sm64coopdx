#ifndef GFX_OPENGL_H
#define GFX_OPENGL_H

#include "gfx_rendering_api.h"

#define MAX_SHADER_TEXTURES 2
#define MAX_SHADER_ATTRIBUTES 24
#define MAX_SHADER_UNIFORMS 24

struct ShaderProgram {
    u64 hash;
    u32 opengl_program_id;
    u8 num_inputs;
    bool used_textures[MAX_SHADER_TEXTURES];
    u8 num_floats;
    u32 attrib_locations[MAX_SHADER_ATTRIBUTES];
    u32 uniform_locations[MAX_SHADER_UNIFORMS];
    u8 attrib_sizes[MAX_SHADER_ATTRIBUTES];
    u8 num_attribs;
    bool used_noise;
    bool used_lightmap;
};

extern struct GfxRenderingAPI gfx_opengl_api;

#endif
