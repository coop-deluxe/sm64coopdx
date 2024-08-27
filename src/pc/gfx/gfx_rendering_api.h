#ifndef GFX_RENDERING_API_H
#define GFX_RENDERING_API_H

#include "gfx_rendering_api_config.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

struct ShaderProgram;
struct ColorCombiner;

struct GfxRenderingAPI {
    bool (*z_is_from_0_to_1)(void);
    void (*unload_shader)(struct ShaderProgram *old_prg);
    void (*load_shader)(struct ShaderProgram *new_prg);
    struct ShaderProgram *(*create_and_load_new_shader)(struct ColorCombiner* cc);
    struct ShaderProgram *(*lookup_shader)(struct ColorCombiner* cc);
    void (*shader_get_info)(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]);
    uint32_t (*new_texture)(void);
    void (*select_texture)(int tile, uint32_t texture_id);
    void (*upload_texture)(const uint8_t *rgba32_buf, int width, int height);
#ifdef GFX_UPLOAD_TEXTURE_FILE
    void (*upload_texture_file)(const char *file_path, const uint8_t *file_buf, uint64_t file_buf_size);
#endif
    void (*set_sampler_parameters)(int sampler, bool linear_filter, uint32_t cms, uint32_t cmt);
    void (*set_depth_test)(bool depth_test);
    void (*set_depth_mask)(bool z_upd);
    void (*set_zmode_decal)(bool zmode_decal);
    void (*set_viewport)(int x, int y, int width, int height);
    void (*set_scissor)(int x, int y, int width, int height);
    void (*set_use_alpha)(bool use_alpha);
#ifdef GFX_SEPARATE_FOG
    void (*set_fog)(uint8_t fog_r, uint8_t fog_g, uint8_t fog_b, int16_t fog_mul, int16_t fog_offset);
#endif
#ifndef GFX_SEPARATE_PROJECTIONS
    void (*draw_triangles)(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris);
#else
    void (*set_camera_perspective)(float fov_degrees, float near_dist, float far_dist, bool can_interpolate);
    void (*set_camera_matrix)(float matrix[4][4]);
    void (*draw_triangles_ortho)(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris, bool double_sided, uint32_t uid);
    void (*draw_triangles_persp)(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris, float transform_affine[4][4], bool double_sided, uint32_t uid);
#endif
#ifdef GFX_ENABLE_GRAPH_NODE_MODS
    void (*set_graph_node_mod)(void *graph_node_mod);
#endif
    void (*init)(void);
    void (*on_resize)(void);
    void (*start_frame)(void);
    void (*end_frame)(void);
    void (*finish_render)(void);
    void (*shutdown)(void);
};

#endif
