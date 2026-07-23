#ifndef GFX_VULKAN_SHADER_H
#define GFX_VULKAN_SHADER_H

#include <stdbool.h>
#include <stdint.h>
#include <volk.h>

struct ColorCombiner;

// Vertex attribute count upper bound: 1 (position) + 2 (texcoords) + 1 (fog)
// + 1 (light map) + 2 (up to 2 CC inputs, gfx_cc.c never generates more - see
// gfx_opengl.c's identically-sized attrib_sizes array).
#define GFX_VULKAN_MAX_ATTRIBS 7

// Concrete definition of the opaque `struct ShaderProgram*` the
// GfxRenderingAPI contract passes around. Mirrors gfx_opengl.c's own struct
// ShaderProgram field-for-field where the concept carries over, swapping GL
// program/attrib-location state for the VkPipeline this ColorCombiner
// compiled to.
struct ShaderProgram {
    uint64_t hash;
    VkPipeline pipeline; // owned by gfx_vulkan_pipeline.c

    uint8_t num_inputs;
    bool used_textures[2];
    bool opt_alpha;
    bool used_noise;
    bool used_lightmap;
    bool world_geometry;

    uint8_t num_floats; // vertex stride, in floats
    uint8_t num_attribs;
    uint8_t attrib_sizes[GFX_VULKAN_MAX_ATTRIBS]; // in floats, cumulative offset = running sum
};

// Owns the vendored-glslang lifecycle (glslang_initialize_process/
// glslang_finalize_process) and the ShaderProgram pool (mirrors
// gfx_opengl.c's shader_program_pool[CC_MAX_SHADERS], same ring-buffer reuse
// policy - see gfx_cc.h's CC_MAX_SHADERS).
bool gfx_vulkan_shader_init(void);
void gfx_vulkan_shader_destroy(void);

// GfxRenderingAPI shader functions.
struct ShaderProgram *gfx_vulkan_shader_create_and_load(struct ColorCombiner *cc);
struct ShaderProgram *gfx_vulkan_shader_lookup(struct ColorCombiner *cc);
void gfx_vulkan_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]);

#endif // GFX_VULKAN_SHADER_H
