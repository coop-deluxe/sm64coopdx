#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "gfx_shader.h"

struct ShaderProgram;
struct ColorCombiner;
struct FramePass;

struct GfxRenderingAPI {
    bool (*z_is_from_0_to_1)(void);
    void (*unload_shader)(struct ShaderProgram *old_prg);
    void (*load_shader)(struct ShaderProgram *new_prg);
    void (*remove_shaders)(void);
    struct ShaderProgram *(*create_and_load_new_shader)(struct ColorCombiner* cc);
    struct ShaderProgram *(*create_or_load_post_process_shader)(void);
    struct ShaderProgram *(*lookup_shader)(struct ColorCombiner* cc);
    struct ShaderProgram *(*lookup_shader_using_index)(uint8_t shaderIndex, uint8_t framePassIndex);
    void (*shader_get_info)(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]);
    void (*create_framebuffer)(struct FramePass *framePass);
    void (*delete_framebuffer)(struct FramePass *framePass);
    void (*set_framebuffer)(struct FramePass *framePass);
    void (*reset_framebuffer)(void);
    size_t (*get_uniform_buffer_size)(enum ShaderStage stage, int bufferIndex);
    void (*set_uniform_buffer)(enum ShaderStage stage, const char *name);
    void (*set_uniform)(struct ShaderProgram *prg, const char *name, ShaderUniformType type, const void *data, uint32_t numElements);
    uint32_t (*new_texture)(void);
    void (*select_texture)(int tile, uint32_t texture_id);
    void (*bind_texture_raw)(int tile, uint64_t texture_id);
    void (*upload_texture)(const uint8_t *rgba32_buf, int width, int height);
    void (*set_sampler_parameters)(int sampler, bool linear_filter, uint32_t cms, uint32_t cmt);
    void (*set_depth_test)(bool depth_test);
    void (*set_depth_mask)(bool z_upd);
    void (*set_zmode_decal)(bool zmode_decal);
    void (*set_viewport)(int x, int y, int width, int height);
    void (*set_scissor)(int x, int y, int width, int height);
    void (*set_use_alpha)(bool use_alpha);
    void (*set_vsync)(bool enabled);
    void (*draw_triangles)(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris);
    void (*init)(void);
    void (*on_resize)(void);
    void (*start_frame)(void);
    void (*end_frame)(void);
    void (*finish_render)(void);
    const char *(*get_name)(void);
    bool (*is_legacy)(void);
    void (*shutdown)(void);
};
