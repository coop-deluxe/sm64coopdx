#if defined(ENABLE_VULKAN)

#ifndef GFX_VULKAN_TEXTURE_H
#define GFX_VULKAN_TEXTURE_H

#include <stdbool.h>
#include <stdint.h>
#include <volk.h>

// Backs the texture-related GfxRenderingAPI functions (new_texture/
// select_texture/upload_texture/set_sampler_parameters). texture_id is an
// index into an internal growable table, the same convention gfx_opengl.c
// uses for its GLuint-indexed texture cache.
bool gfx_vulkan_texture_init(void);
void gfx_vulkan_texture_destroy(void);

uint32_t gfx_vulkan_texture_new(void);
void gfx_vulkan_texture_select(int tile, uint32_t texture_id);
void gfx_vulkan_texture_upload(const uint8_t *rgba32_buf, int width, int height);
void gfx_vulkan_texture_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt);

// Read-only lookup for gfx_vulkan_pipeline.c to bind whatever texture is
// currently selected on a tile.
bool gfx_vulkan_texture_get_bound(int tile, VkImageView *outView, VkSampler *outSampler);

// Size (in texels) and linear-filter flag of whatever texture is currently
// selected on a tile, fed to the Color Combiner shader as push constants.
// linear_filter is the flag set_sampler_parameters was last called with for
// this texture (not the VkSampler's own filter mode) - it only gates the
// shader's 3-point-filter codepath, mirroring gfx_opengl.c's uTexNFilter
// uniform.
bool gfx_vulkan_texture_get_bound_info(int tile, float outSize[2], bool *outLinearFilter);

#endif // GFX_VULKAN_TEXTURE_H

#endif // ENABLE_VULKAN
