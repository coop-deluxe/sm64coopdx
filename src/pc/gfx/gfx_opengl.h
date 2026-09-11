#pragma once
#include "gfx_rendering_api.h"
#include "gfx_shader.h"

struct ShaderProgram {
    struct Shader *vertexShader;
    struct Shader *fragmentShader;
    u64 hash;
    u32 opengl_program_id;
    u8 num_inputs;
    bool used_textures[MAX_SHADER_TEXTURES];
    u8 num_floats;
    u32 attrib_locations[MAX_SHADER_INPUTS];
    u32 uniform_locations[MAX_SHADER_UNIFORMS];
    u8 attrib_sizes[MAX_SHADER_INPUTS];
    u8 num_attribs;
    bool used_noise;
    bool used_lightmap;
    bool used_fog;
    bool world_geometry;
};

extern struct GfxRenderingAPI gfx_opengl_api;

bool gfx_opengl_check_compatibility(void);
