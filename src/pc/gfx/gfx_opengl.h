#pragma once
#include "gfx_rendering_api.h"
#include "gfx_shader.h"

struct ShaderProgram {
    struct Shader *vertexShader;
    struct Shader *fragmentShader;
    u64 hash;
    u32 programId;
    u8 numInputs;
    bool usedTextures[MAX_SHADER_TEXTURES];
    u8 numFloats;
    u32 attributeLocations[MAX_SHADER_INPUTS];
    u32 uniformLocations[MAX_SHADER_UNIFORMS];
    u8 attributeSizes[MAX_SHADER_INPUTS];
    u8 numAttributes;
    bool usedNoise;
    bool usedLightmap;
    bool usedFog;
    bool worldGeometry;
};

extern struct GfxRenderingAPI gfx_opengl_api;

bool gfx_opengl_check_compatibility(void);
