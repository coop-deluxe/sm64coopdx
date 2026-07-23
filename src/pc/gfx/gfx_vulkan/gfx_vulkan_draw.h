#ifndef GFX_VULKAN_DRAW_H
#define GFX_VULKAN_DRAW_H

#include <stdbool.h>
#include <stddef.h>

struct ShaderProgram;

// Vertex streaming: one persistently-mapped, host-visible arena per
// frame-in-flight slot. Every draw_triangles call this frame bump-allocates
// its buf_vbo copy forward through the current slot's arena;
// gfx_vulkan_frame_start() already waits out a slot's previous submission
// before it's reused, so by the time a slot's arena is written again the GPU
// is guaranteed done reading the previous frame's contents from it - no
// ring-buffer wraparound bookkeeping needed within a single frame.
bool gfx_vulkan_draw_init(void);
void gfx_vulkan_draw_destroy(void);

// Rewinds the current frame-in-flight slot's arena to its start. Call once
// per frame, before the first draw_triangles.
void gfx_vulkan_draw_begin_frame(void);

// GfxRenderingAPI functions implemented here. draw_triangles takes the
// currently-loaded ShaderProgram explicitly (gfx_vulkan.c tracks it across
// load_shader calls) rather than querying it itself, to keep this module
// independent of gfx_vulkan_shader.c's shader-selection bookkeeping.
void gfx_vulkan_draw_triangles(const struct ShaderProgram *prg, float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris);
void gfx_vulkan_draw_set_depth_test(bool depth_test);
void gfx_vulkan_draw_set_depth_mask(bool z_upd);
void gfx_vulkan_draw_set_zmode_decal(bool zmode_decal);
void gfx_vulkan_draw_set_viewport(int x, int y, int width, int height);
void gfx_vulkan_draw_set_scissor(int x, int y, int width, int height);
void gfx_vulkan_draw_set_use_alpha(bool use_alpha);

#endif // GFX_VULKAN_DRAW_H
