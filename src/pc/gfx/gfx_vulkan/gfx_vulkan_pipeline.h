#ifndef GFX_VULKAN_PIPELINE_H
#define GFX_VULKAN_PIPELINE_H

#include <stdbool.h>
#include <stdint.h>
#include <volk.h>

struct ShaderProgram;

// Pushed once per draw_triangles call: size/filter of whichever of the up to
// 2 textures the active ColorCombiner samples. Layout must match
// `PushConstants` in the generated fragment shader (gfx_vulkan_shader.c) -
// push_constant blocks use std430 rules implicitly, hence the explicit pad.
typedef struct {
    float tex0Size[2];
    int32_t tex0Filter;
    float _pad0;
    float tex1Size[2];
    int32_t tex1Filter;
} GfxVulkanDrawPushConstants;

// Owns the state shared by every Color Combiner pipeline: the one
// VkPipelineLayout, its two descriptor set layouts (set 0 = per-frame UBO,
// regular/dynamic-offset; set 1 = up to 2 textures, push descriptor), the
// frame UBO's backing buffer, and the VkPipelineCache every
// gfx_vulkan_pipeline_create() call feeds into.
bool gfx_vulkan_pipeline_init(void);
void gfx_vulkan_pipeline_destroy(void);

// Builds a VkPipeline for one Color Combiner's shader modules, baked vertex
// layout (prg->num_floats/attrib_sizes), and fixed dynamic state (no
// culling - handled on CPU; no MSAA; fixed blend equation). Caller destroys
// the shader modules once this returns - a VkPipeline doesn't keep them
// alive. Returns VK_NULL_HANDLE on failure (logs why via stderr).
VkPipeline gfx_vulkan_pipeline_create(VkShaderModule vertModule, VkShaderModule fragModule, const struct ShaderProgram *prg);

// Writes this frame's UBO slice (frame count/lightmap color/shader flags/
// filter) into the current frame-in-flight's region of the persistently-
// mapped frame UBO buffer, and binds descriptor set 0 (dynamic offset into
// that region) on the current command buffer. Call once per frame, before
// any draw_triangles.
void gfx_vulkan_pipeline_update_frame_ubo(uint32_t frameCount);

// Pushes descriptor set 1 for whatever textures gfx_vulkan_texture.c
// currently has bound on tiles 0/1 (only the tiles `usedTextures` marks
// true), then the per-draw push constants - both against the shared layout,
// on the current command buffer.
void gfx_vulkan_pipeline_bind_textures(const bool usedTextures[2]);
void gfx_vulkan_pipeline_push_draw_constants(const GfxVulkanDrawPushConstants *pc);

extern VkPipelineLayout gfxVkPipelineLayout;

#endif // GFX_VULKAN_PIPELINE_H
