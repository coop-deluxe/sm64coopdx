#ifdef RAPI_GL

#include <stdint.h>
#include <stdbool.h>

#ifdef __SWITCH__
#include <switch.h>
#endif

#ifndef _LANGUAGE_C
# define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#if defined(__MINGW32__) && !defined(__SWITCH__)
# define FOR_WINDOWS 1
#else
# define FOR_WINDOWS 0
#endif

#if FOR_WINDOWS || defined(OSX_BUILD)
# define GLEW_STATIC
# include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1

#ifdef WAPI_SDL2
# include <SDL2/SDL.h>
# if defined(USE_GLES)
#  define USE_FRAMEBUFFER 0
#  include <SDL2/SDL_opengles2.h>
# else
#  define USE_FRAMEBUFFER 0
#  include <SDL2/SDL_opengl.h>
# endif
#elif defined(WAPI_SDL1)
# include <SDL/SDL.h>
# define USE_FRAMEBUFFER 0
# ifndef GLEW_STATIC
#  include <SDL/SDL_opengl.h>
# endif
#endif

#include "../platform.h"
#include "../configfile.h"
#include "gfx_cc.h"
#include "gfx_rendering_api.h"
#include "gfx_pc.h"

#define FRAMEBUFFER_WIDTH 320
#define FRAMEBUFFER_HEIGHT 240
#define TEX_CACHE_STEP 512

static const char *rt_vertex_shader =
#ifdef USE_GLES
    "#version 100\n"
#else
    "#version 120\n"
#endif
    "attribute vec2 a_position;\n"
    "attribute vec2 a_uv;\n"
    "varying vec2 v_uv;\n"
    "void main() {\n"
    "    gl_Position = vec4(a_position.x, a_position.y, 0.0, 1.0);\n"
    "    v_uv = a_uv;\n"
    "}\n";

static const char *rt_fragment_shader =
#ifdef USE_GLES
    "#version 100\n"
    "precision mediump float;\n"
#else
    "#version 120\n"
#endif
    "varying vec2 v_uv;\n"
    "uniform sampler2D u_texture;"
    "void main() {\n"
    "    gl_FragColor = vec4(texture2D(u_texture, v_uv).rgb, 1);\n"
    "}\n";

struct ShaderProgram {
    uint64_t hash;
    GLuint opengl_program_id;
    uint8_t num_inputs;
    bool used_textures[2];
    uint8_t num_floats;
    GLint attrib_locations[7];
    GLint uniform_locations[7];
    uint8_t attrib_sizes[7];
    uint8_t num_attribs;
    bool used_noise;
    bool used_lightmap;
};

struct GLTexture {
    GLuint gltex;
    GLfloat size[2];
    bool filter;
};

struct RenderTarget {
    GLuint framebuffer_id;
    GLuint color_texture_id;
    GLuint depth_renderbuffer_id;

    uint32_t width;
    uint32_t height;
};

static struct {
    int32_t viewport_x, viewport_y, viewport_width, viewport_height;
    int32_t scissor_x, scissor_y, scissor_width, scissor_height;
    int8_t depth_test, depth_mask;
    int8_t zmode_decal;

    uint8_t active_texture;
    GLuint bound_framebuffer;
} gl_state = { 0 };

static struct RenderTarget main_rt;
static struct RenderTarget framebuffer_rt;

static struct ShaderProgram shader_program_pool[CC_MAX_SHADERS];
static struct ShaderProgram *current_shader_program = NULL;
static uint8_t shader_program_pool_size = 0;
static uint8_t shader_program_pool_index = 0;
static GLuint opengl_vbo;
static GLuint opengl_vao;

static int tex_cache_size = 0;
static int num_textures = 0;
static struct GLTexture *tex_cache = NULL;

static struct ShaderProgram rt_shader_program;
static struct GLTexture *opengl_tex[2];
static int opengl_curtex = 0;

static uint32_t current_width;
static uint32_t current_height;

static int8_t current_depth_test, current_depth_mask;
static int8_t current_zmode_decal;

static int32_t current_viewport_x, current_viewport_y, current_viewport_width, current_viewport_height;
static int32_t current_scissor_x, current_scissor_y, current_scissor_width, current_scissor_height;

static uint32_t frame_count;

static void gfx_opengl_set_depth_test(bool depth_test);
static void gfx_opengl_set_depth_mask(bool z_upd);
static void gfx_opengl_set_zmode_decal(bool zmode_decal);
static void gfx_opengl_set_viewport(int32_t x, int32_t y, int32_t width, int32_t height);
static void gfx_opengl_set_scissor(int32_t x, int32_t y, int32_t width, int32_t height);

static void gfx_opengl_set_active_texture(uint8_t active_texture) {
    if (gl_state.active_texture == active_texture) {
        return;
    }

    gl_state.active_texture = active_texture;

    glActiveTexture(GL_TEXTURE0 + active_texture);
}

static void gfx_opengl_set_vertex_buffer(float buffer[], size_t buffer_length) {
    glBufferData(GL_ARRAY_BUFFER, buffer_length, buffer, GL_STREAM_DRAW);
}

static void gfx_opengl_bind_render_target(const struct RenderTarget *render_target) {
    GLuint id = render_target == NULL ? 0 : render_target->framebuffer_id;

    if (gl_state.bound_framebuffer != id) {
        gl_state.bound_framebuffer = id;
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }
}

static void gfx_opengl_create_render_target(uint32_t width, uint32_t height, bool is_resizing, bool has_depth_buffer, struct RenderTarget *render_target) {
    // Create color texture and buffers

    if (!is_resizing) {
        glGenTextures(1, &render_target->color_texture_id);
        if (has_depth_buffer) {
            glGenRenderbuffers(1, &render_target->depth_renderbuffer_id);
        }
        glGenFramebuffers(1, &render_target->framebuffer_id);
    }

    // Configure color texture

    glBindTexture(GL_TEXTURE_2D, render_target->color_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Configure the depth buffer

    if (has_depth_buffer) {
        glBindRenderbuffer(GL_RENDERBUFFER, render_target->depth_renderbuffer_id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    }

    // Bind color and depth to the framebuffer

    if (!is_resizing) {
        gfx_opengl_bind_render_target(render_target);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_target->color_texture_id, 0);
        if (has_depth_buffer) {
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_target->depth_renderbuffer_id);
        }
    }

    render_target->width = width;
    render_target->height = height;
}

// function only used when USE_FRAMEBUFFER is defined
static void gfx_opengl_draw_render_target(const struct RenderTarget *dst_render_target, const struct RenderTarget *src_render_target, bool clear_before_drawing) {
    // Set render target

    uint32_t dst_width, dst_height;

    gfx_opengl_bind_render_target(dst_render_target);

    if (dst_render_target == NULL) {
        dst_width = current_width;
        dst_height = current_height;
    } else {
        dst_width = dst_render_target->width;
        dst_height = dst_render_target->height;
    }

    // Set some states and clear after that

    gfx_opengl_set_depth_test(false);
    gfx_opengl_set_depth_mask(false);
    gfx_opengl_set_zmode_decal(false);
    gfx_opengl_set_viewport(0, 0, dst_width, dst_height);
    gfx_opengl_set_scissor(0, 0, dst_width, dst_height);

    if (clear_before_drawing) {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Set color texture

    gfx_opengl_set_active_texture(0);
    glBindTexture(GL_TEXTURE_2D, src_render_target->color_texture_id);

    // Set vertex buffer data

    float dst_aspect = (float) dst_width / (float) dst_height;
    float src_aspect = (float) src_render_target->width / (float) src_render_target->height;
    float w = src_aspect / dst_aspect;

    float buf_vbo[] = {
        -w, +1.0, 0.0, 1.0,
        -w, -1.0, 0.0, 0.0,
        +w, +1.0, 1.0, 1.0,
        +w, -1.0, 1.0, 0.0
    };

    uint32_t stride = 2 * 2 * sizeof(float);
    gfx_opengl_set_vertex_buffer(buf_vbo, 4 * stride);

    // Draw the quad

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

static void gfx_opengl_create_render_target_views(bool is_resize) {
    if (!is_resize) {
        // Initialize the framebuffer only the first time.
        gfx_opengl_create_render_target(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, false, false, &framebuffer_rt);
    }

    // Create the main render target where contents will be rendered.
    gfx_opengl_create_render_target(current_width, current_height, is_resize, true, &main_rt);
}

static bool gfx_opengl_z_is_from_0_to_1(void) {
    return false;
}

static void gfx_opengl_vertex_array_set_attribs(struct ShaderProgram *prg) {
    size_t num_floats = prg->num_floats;
    size_t pos = 0;

    for (int i = 0; i < prg->num_attribs; i++) {
        glEnableVertexAttribArray(prg->attrib_locations[i]);
        glVertexAttribPointer(prg->attrib_locations[i], prg->attrib_sizes[i], GL_FLOAT, GL_FALSE, num_floats * sizeof(float), (void *) (pos * sizeof(float)));
        pos += prg->attrib_sizes[i];
    }
}

static inline void gfx_opengl_set_shader_uniforms(struct ShaderProgram *prg) {
    if (prg->used_noise) { glUniform1f(prg->uniform_locations[4], (float)frame_count); }
    if (prg->used_lightmap) { glUniform3f(prg->uniform_locations[5], gVertexColor[0] / 255.0f, gVertexColor[1] / 255.0f, gVertexColor[2] / 255.0f); }
    glUniform1i(prg->uniform_locations[6], configFiltering);
}

static inline void gfx_opengl_set_texture_uniforms(struct ShaderProgram *prg, const int tile) {
    if (prg->used_textures[tile] && opengl_tex[tile]) {
        glUniform2f(prg->uniform_locations[tile*2 + 0], opengl_tex[tile]->size[0], opengl_tex[tile]->size[1]);
        glUniform1i(prg->uniform_locations[tile*2 + 1], opengl_tex[tile]->filter);
    }
}

static GLuint gfx_opengl_compile_shader(const char *vertex_shader_raw, const char *fragment_shader_raw) {
    GLint success;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    if (!vertex_shader) {
        fprintf(stderr, "Failed to create vertex shader!\n");
        return -1;
    }
    glShaderSource(vertex_shader, 1, &vertex_shader_raw, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint max_length = 0;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);
        char error_log[1024];
        fprintf(stderr, "Vertex shader compilation failed\n");
        glGetShaderInfoLog(vertex_shader, max_length, &max_length, &error_log[0]);
        fprintf(stderr, "%s\n", &error_log[0]);
        sys_fatal("vertex shader compilation failed (see terminal)");
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragment_shader) {
        fprintf(stderr, "Failed to create fragment shader!\n");
        return -1;
    }
    glShaderSource(fragment_shader, 1, &fragment_shader_raw, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint max_length = 0;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);
        char error_log[1024];
        fprintf(stderr, "Fragment shader compilation failed\n");
        glGetShaderInfoLog(fragment_shader, max_length, &max_length, &error_log[0]);
        fprintf(stderr, "%s\n", &error_log[0]);
        sys_fatal("fragment shader compilation failed (see terminal)");
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    
    glDetachShader(shader_program, vertex_shader);
    glDetachShader(shader_program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    return shader_program;
}

static void gfx_opengl_unload_shader(struct ShaderProgram *old_prg) {
    if (old_prg != NULL) {
        for (int i = 0; i < old_prg->num_attribs; i++)
            glDisableVertexAttribArray(old_prg->attrib_locations[i]);
        if (old_prg == current_shader_program)
            current_shader_program = NULL;
    } else {
        current_shader_program = NULL;
    }
}

static void gfx_opengl_load_shader(struct ShaderProgram *new_prg) {
    current_shader_program = new_prg;
    glUseProgram(new_prg->opengl_program_id);
    gfx_opengl_vertex_array_set_attribs(new_prg);
    gfx_opengl_set_shader_uniforms(new_prg);
    gfx_opengl_set_texture_uniforms(new_prg, 0);
    gfx_opengl_set_texture_uniforms(new_prg, 1);
}

static void append_str(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
}

static void append_line(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
    buf[(*len)++] = '\n';
}

static const char *shader_item_to_str(uint32_t item, bool with_alpha, bool only_alpha, bool inputs_have_alpha, bool hint_single_element) {
    if (!only_alpha) {
        switch (item) {
            case SHADER_0:
                return with_alpha ? "vec4(0.0, 0.0, 0.0, 0.0)" : "vec3(0.0, 0.0, 0.0)";
            case SHADER_1:
                return with_alpha ? "vec4(1.0, 1.0, 1.0, 1.0)" : "vec3(1.0, 1.0, 1.0)";
            case SHADER_INPUT_1:
                return with_alpha || !inputs_have_alpha ? "vInput1" : "vInput1.rgb";
            case SHADER_INPUT_2:
                return with_alpha || !inputs_have_alpha ? "vInput2" : "vInput2.rgb";
            case SHADER_INPUT_3:
                return with_alpha || !inputs_have_alpha ? "vInput3" : "vInput3.rgb";
            case SHADER_INPUT_4:
                return with_alpha || !inputs_have_alpha ? "vInput4" : "vInput4.rgb";
            case SHADER_INPUT_5:
                return with_alpha || !inputs_have_alpha ? "vInput5" : "vInput5.rgb";
            case SHADER_INPUT_6:
                return with_alpha || !inputs_have_alpha ? "vInput6" : "vInput6.rgb";
            case SHADER_INPUT_7:
                return with_alpha || !inputs_have_alpha ? "vInput7" : "vInput7.rgb";
            case SHADER_INPUT_8:
                return with_alpha || !inputs_have_alpha ? "vInput8" : "vInput8.rgb";
            case SHADER_TEXEL0:
                return with_alpha ? "texVal0" : "texVal0.rgb";
            case SHADER_TEXEL0A:
                return hint_single_element ? "texVal0.a" :
                    (with_alpha ? "vec4(texelVal0.a, texelVal0.a, texelVal0.a, texelVal0.a)" : "vec3(texelVal0.a, texelVal0.a, texelVal0.a)");
            case SHADER_TEXEL1:
                return with_alpha ? "texVal1" : "texVal1.rgb";
            case SHADER_TEXEL1A:
                return hint_single_element ? "texVal1.a" :
                    (with_alpha ? "vec4(texelVal1.a, texelVal1.a, texelVal1.a, texelVal1.a)" : "vec3(texelVal1.a, texelVal1.a, texelVal1.a)");
            case SHADER_COMBINED:
                return with_alpha ? "texel" : "texel.rgb";
            case SHADER_COMBINEDA:
                return hint_single_element ? "texel.a" :
                    (with_alpha ? "vec4(texel.a, texel.a, texel.a, texel.a)" : "vec3(texel.a, texel.a, texel.a)");
            case SHADER_NOISE:
                return with_alpha ? "vec4(noise)" : "vec3(noise)";
        }
    } else {
        switch (item) {
            case SHADER_0:
                return "0.0";
            case SHADER_1:
                return "1.0";
            case SHADER_INPUT_1:
                return "vInput1.a";
            case SHADER_INPUT_2:
                return "vInput2.a";
            case SHADER_INPUT_3:
                return "vInput3.a";
            case SHADER_INPUT_4:
                return "vInput4.a";
            case SHADER_INPUT_5:
                return "vInput5.a";
            case SHADER_INPUT_6:
                return "vInput6.a";
            case SHADER_INPUT_7:
                return "vInput7.a";
            case SHADER_INPUT_8:
                return "vInput8.a";
            case SHADER_TEXEL0:
                return "texVal0.a";
            case SHADER_TEXEL0A:
                return "texVal0.a";
            case SHADER_TEXEL1:
                return "texVal1.a";
            case SHADER_TEXEL1A:
                return "texVal1.a";
            case SHADER_COMBINED:
                return "texel.a";
            case SHADER_COMBINEDA:
                return "texel.a";
            case SHADER_NOISE:
                return "noise.a";
        }
    }
    return "unknown";
}

static void append_formula(char *buf, size_t *len, uint8_t* cmd, bool do_single, bool do_multiply, bool do_mix, bool with_alpha, bool only_alpha, bool opt_alpha) {
    if (do_single) {
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 3], with_alpha, only_alpha, opt_alpha, false));
    } else if (do_multiply) {
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " * ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
    } else if (do_mix) {
        append_str(buf, len, "mix(");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, ")");
    } else {
        append_str(buf, len, "(");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " - ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ") * ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, " + ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 3], with_alpha, only_alpha, opt_alpha, false));
    }
}

static struct ShaderProgram *gfx_opengl_create_and_load_new_shader(struct ColorCombiner* cc) {
    struct CCFeatures ccf = { 0 };
    gfx_cc_get_features(cc, &ccf);

    bool opt_alpha = cc->cm.use_alpha;
    bool opt_fog = cc->cm.use_fog;
    bool opt_texture_edge = cc->cm.texture_edge;
    bool opt_2cycle = cc->cm.use_2cycle;
    bool opt_light_map = cc->cm.light_map;

#if defined(USE_GLES)
    bool opt_dither = false;
#else
    bool opt_dither = cc->cm.use_dither;
#endif

    char vs_buf[1024];
    char fs_buf[2048];
    size_t vs_len = 0;
    size_t fs_len = 0;
    size_t num_floats = 4;

    // Vertex shader
#if defined(USE_GLES)
    append_line(vs_buf, &vs_len, "#version 100");
#else
    append_line(vs_buf, &vs_len, "#version 120");
#endif
    append_line(vs_buf, &vs_len, "attribute vec4 aVtxPos;");
    if (ccf.used_textures[0] || ccf.used_textures[1]) {
        append_line(vs_buf, &vs_len, "attribute vec2 aTexCoord;");
        append_line(vs_buf, &vs_len, "varying vec2 vTexCoord;");
        num_floats += 2;
    }
    if (opt_fog) {
        append_line(vs_buf, &vs_len, "attribute vec4 aFog;");
        append_line(vs_buf, &vs_len, "varying vec4 vFog;");
        num_floats += 4;
    }
    if (opt_light_map) {
        append_line(vs_buf, &vs_len, "attribute vec2 aLightMap;");
        append_line(vs_buf, &vs_len, "varying vec2 vLightMap;");
        num_floats += 2;
    }
    for (int i = 0; i < ccf.num_inputs; i++) {
        vs_len += sprintf(vs_buf + vs_len, "attribute vec%d aInput%d;\n", opt_alpha ? 4 : 3, i + 1);
        vs_len += sprintf(vs_buf + vs_len, "varying vec%d vInput%d;\n", opt_alpha ? 4 : 3, i + 1);
        num_floats += opt_alpha ? 4 : 3;
    }
    append_line(vs_buf, &vs_len, "void main() {");
    if (ccf.used_textures[0] || ccf.used_textures[1]) {
        append_line(vs_buf, &vs_len, "vTexCoord = aTexCoord;");
    }
    if (opt_fog) {
        append_line(vs_buf, &vs_len, "vFog = aFog;");
    }
    if (opt_light_map) {
        append_line(vs_buf, &vs_len, "vLightMap = aLightMap;");
    }
    for (int i = 0; i < ccf.num_inputs; i++) {
        vs_len += sprintf(vs_buf + vs_len, "vInput%d = aInput%d;\n", i + 1, i + 1);
    }
    append_line(vs_buf, &vs_len, "gl_Position = aVtxPos;");
    append_line(vs_buf, &vs_len, "}");

    // Fragment shader
#if defined(USE_GLES)
    append_line(fs_buf, &fs_len, "#version 100");
    append_line(fs_buf, &fs_len, "precision mediump float;");
#else
    append_line(fs_buf, &fs_len, "#version 120");
#endif

    if (ccf.used_textures[0] || ccf.used_textures[1]) {
        append_line(fs_buf, &fs_len, "varying vec2 vTexCoord;");
    }
    if (opt_fog) {
        append_line(fs_buf, &fs_len, "varying vec4 vFog;");
    }
    if (opt_light_map) {
        append_line(fs_buf, &fs_len, "varying vec2 vLightMap;");
    }
    for (int i = 0; i < ccf.num_inputs; i++) {
        fs_len += sprintf(fs_buf + fs_len, "varying vec%d vInput%d;\n", opt_alpha ? 4 : 3, i + 1);
    }
    if (ccf.used_textures[0]) {
        append_line(fs_buf, &fs_len, "uniform sampler2D uTex0;");
        append_line(fs_buf, &fs_len, "uniform vec2 uTex0Size;");
        append_line(fs_buf, &fs_len, "uniform bool uTex0Filter;");
    }
    if (ccf.used_textures[1]) {
        append_line(fs_buf, &fs_len, "uniform sampler2D uTex1;");
        append_line(fs_buf, &fs_len, "uniform vec2 uTex1Size;");
        append_line(fs_buf, &fs_len, "uniform bool uTex1Filter;");
    }

    // 3 point texture filtering
    // Original author: ArthurCarvalho
    // Modified GLSL implementation by twinaphex, mupen64plus-libretro project.
    if (ccf.used_textures[0] || ccf.used_textures[1]) {
        append_line(fs_buf, &fs_len, "#define TEX_OFFSET(off) texture2D(tex, texCoord - (off)/texSize)");
        append_line(fs_buf, &fs_len, "vec4 filter3point(in sampler2D tex, in vec2 texCoord, in vec2 texSize) {");
        append_line(fs_buf, &fs_len, "    vec2 offset = fract(texCoord*texSize - vec2(0.5));");
        append_line(fs_buf, &fs_len, "    offset -= step(1.0, offset.x + offset.y);");
        append_line(fs_buf, &fs_len, "    vec4 c0 = TEX_OFFSET(offset);");
        append_line(fs_buf, &fs_len, "    vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));");
        append_line(fs_buf, &fs_len, "    vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));");
        append_line(fs_buf, &fs_len, "    return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);");
        append_line(fs_buf, &fs_len, "}");
        append_line(fs_buf, &fs_len, "vec4 sampleTex(in sampler2D tex, in vec2 uv, in vec2 texSize, in bool dofilter, in int filter) {");
        append_line(fs_buf, &fs_len, "    if (dofilter && filter == 2)");
        append_line(fs_buf, &fs_len, "        return filter3point(tex, uv, texSize);");
        append_line(fs_buf, &fs_len, "    else");
        append_line(fs_buf, &fs_len, "        return texture2D(tex, uv);");
        append_line(fs_buf, &fs_len, "}");
    }

    if ((opt_alpha && opt_dither) || ccf.do_noise) {
        append_line(fs_buf, &fs_len, "uniform float uFrameCount;");

        append_line(fs_buf, &fs_len, "float random(in vec3 value) {");
        append_line(fs_buf, &fs_len, "    float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));");
#ifdef USE_GLES
        append_line(fs_buf, &fs_len, "    return fract(sin(random) * 143.7585453);");
#else
        append_line(fs_buf, &fs_len, "    return fract(sin(random) * 143758.5453);");
#endif
        append_line(fs_buf, &fs_len, "}");
    }

    if (opt_light_map) {
        append_line(fs_buf, &fs_len, "uniform vec3 uLightmapColor;");
    }

    append_line(fs_buf, &fs_len, "uniform int uFilter;");

    append_line(fs_buf, &fs_len, "void main() {");

    if ((opt_alpha && opt_dither) || ccf.do_noise) {
        append_line(fs_buf, &fs_len, "float noise = floor(random(floor(vec3(gl_FragCoord.xy, uFrameCount))) + 0.5);");
    }

    if (ccf.used_textures[0]) {
        append_line(fs_buf, &fs_len, "vec4 texVal0 = sampleTex(uTex0, vTexCoord, uTex0Size, uTex0Filter, uFilter);");
    }
    if (ccf.used_textures[1]) {
        if (opt_light_map) {
            append_line(fs_buf, &fs_len, "vec4 texVal1 = sampleTex(uTex1, vLightMap, uTex1Size, uTex1Filter, uFilter);");
            append_line(fs_buf, &fs_len, "texVal0.rgb *= uLightmapColor.rgb;");
            append_line(fs_buf, &fs_len, "texVal1.rgb = texVal1.rgb * texVal1.rgb + texVal1.rgb;");
        } else {
            append_line(fs_buf, &fs_len, "vec4 texVal1 = sampleTex(uTex1, vTexCoord, uTex1Size, uTex1Filter, uFilter);");
        }
    }

    append_str(fs_buf, &fs_len, (opt_alpha) ? "vec4 texel = " : "vec3 texel = ");
    for (int i = 0; i < (opt_2cycle + 1); i++) {
        u8* cmd = &cc->shader_commands[i * 8];
        if (!ccf.color_alpha_same[i] && opt_alpha) {
            append_str(fs_buf, &fs_len, "vec4(");
            append_formula(fs_buf, &fs_len, cmd, ccf.do_single[i*2+0], ccf.do_multiply[i*2+0], ccf.do_mix[i*2+0], false, false, true);
            append_str(fs_buf, &fs_len, ", ");
            append_formula(fs_buf, &fs_len, cmd, ccf.do_single[i*2+1], ccf.do_multiply[i*2+1], ccf.do_mix[i*2+1], true, true, true);
            append_str(fs_buf, &fs_len, ")");
        } else {
            append_formula(fs_buf, &fs_len, cmd, ccf.do_single[i*2+0], ccf.do_multiply[i*2+0], ccf.do_mix[i*2+0], opt_alpha, false, opt_alpha);
        }
        append_line(fs_buf, &fs_len, ";");

        if (i == 0 && opt_2cycle) {
            append_str(fs_buf, &fs_len, "texel = ");
        }
    }

    if (opt_texture_edge && opt_alpha) {
        append_line(fs_buf, &fs_len, "if (texel.a > 0.3) texel.a = 1.0; else discard;");
    }

    // TODO discard if alpha is 0?

    if (opt_fog) {
        if (opt_alpha) {
            append_line(fs_buf, &fs_len, "texel = vec4(mix(texel.rgb, vFog.rgb, vFog.a), texel.a);");
        } else {
            append_line(fs_buf, &fs_len, "texel = mix(texel, vFog.rgb, vFog.a);");
        }
    }

    if (opt_alpha && opt_dither) {
        append_line(fs_buf, &fs_len, "texel.a *= noise;");
    }

    if (opt_alpha) {
        append_line(fs_buf, &fs_len, "gl_FragColor = texel;");
    } else {
        append_line(fs_buf, &fs_len, "gl_FragColor = vec4(texel, 1.0);");
    }
    append_line(fs_buf, &fs_len, "}");

    vs_buf[vs_len] = '\0';
    fs_buf[fs_len] = '\0';

    /*puts("Vertex shader:");
    puts(vs_buf);
    puts("Fragment shader:");
    puts(fs_buf);
    puts("End");*/

    GLuint shader_program = gfx_opengl_compile_shader(vs_buf, fs_buf);

    size_t cnt = 0;

    struct ShaderProgram *prg = &shader_program_pool[shader_program_pool_index];
    shader_program_pool_index = (shader_program_pool_index + 1) % CC_MAX_SHADERS;
    if (shader_program_pool_size < CC_MAX_SHADERS) { shader_program_pool_size++; }

    prg->attrib_locations[cnt] = glGetAttribLocation(shader_program, "aVtxPos");
    prg->attrib_sizes[cnt] = 4;
    ++cnt;

    if (ccf.used_textures[0] || ccf.used_textures[1]) {
        prg->attrib_locations[cnt] = glGetAttribLocation(shader_program, "aTexCoord");
        prg->attrib_sizes[cnt] = 2;
        ++cnt;
    }

    if (opt_fog) {
        prg->attrib_locations[cnt] = glGetAttribLocation(shader_program, "aFog");
        prg->attrib_sizes[cnt] = 4;
        ++cnt;
    }

    if (opt_light_map) {
        prg->attrib_locations[cnt] = glGetAttribLocation(shader_program, "aLightMap");
        prg->attrib_sizes[cnt] = 2;
        ++cnt;
    }

    for (int i = 0; i < ccf.num_inputs; i++) {
        char name[16];
        sprintf(name, "aInput%d", i + 1);
        prg->attrib_locations[cnt] = glGetAttribLocation(shader_program, name);
        prg->attrib_sizes[cnt] = opt_alpha ? 4 : 3;
        ++cnt;
    }

    prg->hash = cc->hash;
    prg->opengl_program_id = shader_program;
    prg->num_inputs = ccf.num_inputs;
    prg->used_textures[0] = ccf.used_textures[0];
    prg->used_textures[1] = ccf.used_textures[1];
    prg->num_floats = num_floats;
    prg->num_attribs = cnt;

    gfx_opengl_load_shader(prg);

    if (ccf.used_textures[0]) {
        GLint sampler_location = glGetUniformLocation(shader_program, "uTex0");
        prg->uniform_locations[0] = glGetUniformLocation(shader_program, "uTex0Size");
        prg->uniform_locations[1] = glGetUniformLocation(shader_program, "uTex0Filter");
        glUniform1i(sampler_location, 0);
    }
    if (ccf.used_textures[1]) {
        GLint sampler_location = glGetUniformLocation(shader_program, "uTex1");
        prg->uniform_locations[2] = glGetUniformLocation(shader_program, "uTex1Size");
        prg->uniform_locations[3] = glGetUniformLocation(shader_program, "uTex1Filter");
        glUniform1i(sampler_location, 1);
    }

    if ((opt_alpha && opt_dither) || ccf.do_noise) {
        prg->uniform_locations[4] = glGetUniformLocation(shader_program, "uFrameCount");
        prg->used_noise = true;
    } else {
        prg->used_noise = false;
    }

    if (opt_light_map) {
        prg->uniform_locations[5] = glGetUniformLocation(shader_program, "uLightmapColor");
        prg->used_lightmap = true;
    } else {
        prg->used_lightmap = false;
    }
    
    prg->uniform_locations[6] = glGetUniformLocation(shader_program, "uFilter");

    return prg;
}

static struct ShaderProgram *gfx_opengl_lookup_shader(struct ColorCombiner* cc) {
    for (size_t i = 0; i < shader_program_pool_size; i++) {
        if (shader_program_pool[i].hash == cc->hash) {
            return &shader_program_pool[i];
        }
    }
    return NULL;
}

static void gfx_opengl_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    *num_inputs = prg->num_inputs;
    used_textures[0] = prg->used_textures[0];
    used_textures[1] = prg->used_textures[1];
}

static GLuint gfx_opengl_new_texture(void) {
    if (num_textures >= tex_cache_size) {
        tex_cache_size += TEX_CACHE_STEP;
        tex_cache = realloc(tex_cache, sizeof(struct GLTexture) * tex_cache_size);
        if (!tex_cache) sys_fatal("out of memory allocating texture cache");
        // invalidate these because they might be pointing to garbage now
        opengl_tex[0] = NULL;
        opengl_tex[1] = NULL;
    }
    glGenTextures(1, &tex_cache[num_textures].gltex);
    return num_textures++;
}

static void gfx_opengl_select_texture(int tile, GLuint texture_id) {
     opengl_tex[tile] = tex_cache + texture_id;
     opengl_curtex = tile;
     glActiveTexture(GL_TEXTURE0 + tile);
     glBindTexture(GL_TEXTURE_2D, opengl_tex[tile]->gltex);
     gfx_opengl_set_texture_uniforms(current_shader_program, tile);
}

static void gfx_opengl_upload_texture(const uint8_t *rgba32_buf, int width, int height) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba32_buf);
    opengl_tex[opengl_curtex]->size[0] = width;
    opengl_tex[opengl_curtex]->size[1] = height;
}

static uint32_t gfx_cm_to_opengl(uint32_t val) {
    if (val & G_TX_CLAMP) {
        return GL_CLAMP_TO_EDGE;
    }
    return (val & G_TX_MIRROR) ? GL_MIRRORED_REPEAT : GL_REPEAT;
}

static void gfx_opengl_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt) {
    const GLenum filter = linear_filter ? GL_LINEAR : GL_NEAREST;
    glActiveTexture(GL_TEXTURE0 + tile);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gfx_cm_to_opengl(cms));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gfx_cm_to_opengl(cmt));
    opengl_curtex = tile;
    if (opengl_tex[tile]) {
        opengl_tex[tile]->filter = linear_filter;
        gfx_opengl_set_texture_uniforms(current_shader_program, tile);
    }
}

static void gfx_opengl_set_depth_test(bool depth_test) {
    if (gl_state.depth_test == depth_test) {
        return;
    }

    gl_state.depth_test = depth_test;

    if (depth_test) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

static void gfx_opengl_set_depth_mask(bool z_upd) {
    if (gl_state.depth_mask == z_upd) {
        return;
    }

    gl_state.depth_mask = z_upd;

    glDepthMask(z_upd ? GL_TRUE : GL_FALSE);
}

static void gfx_opengl_set_zmode_decal(bool zmode_decal) {
    if (gl_state.zmode_decal == zmode_decal) {
        return;
    }

    gl_state.zmode_decal = zmode_decal;

    if (zmode_decal) {
        glPolygonOffset(-2, -2);
        glEnable(GL_POLYGON_OFFSET_FILL);
    } else {
        glPolygonOffset(0, 0);
        glDisable(GL_POLYGON_OFFSET_FILL);
    }
}
static void gfx_opengl_set_viewport(int32_t x, int32_t y, int32_t width, int32_t height) {
    if (gl_state.viewport_x == x && gl_state.viewport_y == y && gl_state.viewport_width == width && gl_state.viewport_height == height) {
        return;
    }

    gl_state.viewport_x = x;
    gl_state.viewport_y = y;
    gl_state.viewport_width = width;
    gl_state.viewport_height = height;

    glViewport(x, y, width, height);
}

static void gfx_opengl_set_scissor(int32_t x, int32_t y, int32_t width, int32_t height) {
    if (gl_state.scissor_x == x && gl_state.scissor_y == y && gl_state.scissor_width == width && gl_state.scissor_height == height) {
        return;
    }

    gl_state.scissor_x = x;
    gl_state.scissor_y = y;
    gl_state.scissor_width = width;
    gl_state.scissor_height = height;

    glScissor(x, y, width, height);
}

static void gfx_opengl_set_use_alpha(bool use_alpha) {
    if (use_alpha) {
        glEnable(GL_BLEND);
    } else {
        glDisable(GL_BLEND);
    }
}

static void gfx_opengl_draw_triangles(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {
    // Depth

    gfx_opengl_set_depth_test(current_depth_test);
    gfx_opengl_set_depth_mask(current_depth_mask);
    gfx_opengl_set_zmode_decal(current_zmode_decal);

    // Viewport and Scissor

    gfx_opengl_set_viewport(current_viewport_x, current_viewport_y, current_viewport_width, current_viewport_height);
    gfx_opengl_set_scissor(current_scissor_x, current_scissor_y, current_scissor_width, current_scissor_height);

    // Draw vertex buffer
    
    gfx_opengl_set_vertex_buffer(buf_vbo, buf_vbo_len * sizeof(float));
    glDrawArrays(GL_TRIANGLES, 0, 3 * buf_vbo_num_tris);
}

static inline bool gl_get_version(int *major, int *minor, bool *is_es) {
    const char *vstr = (const char *)glGetString(GL_VERSION);
    if (!vstr || !vstr[0]) {
        
        return false;
    }

    if (!strncmp(vstr, "OpenGL ES ", 10)) {
        vstr += 10;
        *is_es = true;
    } else if (!strncmp(vstr, "OpenGL ES-CM ", 13)) {
        vstr += 13;
        *is_es = true;
    }

    return (sscanf(vstr, "%d.%d", major, minor) == 2);
}

static void gfx_opengl_get_framebuffer(uint16_t *buffer) {
    if (USE_FRAMEBUFFER)  {
        gfx_opengl_bind_render_target(&framebuffer_rt);

        uint8_t pixels[FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT * 4];
        glReadPixels(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        uint32_t bi = 0;
        for (int32_t y = FRAMEBUFFER_HEIGHT - 1; y >= 0; y--) {
            for (int32_t x = 0; x < FRAMEBUFFER_WIDTH; x++) {
                uint32_t fb_pixel = (y * FRAMEBUFFER_WIDTH + x) * 4;

                uint8_t r = pixels[fb_pixel + 0] >> 3;
                uint8_t g = pixels[fb_pixel + 1] >> 3;
                uint8_t b = pixels[fb_pixel + 2] >> 3;
                uint8_t a = 1; //pixels[fb_pixel + 3] / 255;

                buffer[bi] = (r << 11) | (g << 6) | (b << 1) | a;
                bi++;
            }
        }
    }
}

static void gfx_opengl_init(void) {
#if FOR_WINDOWS || defined(OSX_BUILD)
    GLenum err;
    if ((err = glewInit()) != GLEW_OK)
        sys_fatal("could not init GLEW:\n%s", glewGetErrorString(err));
#endif
    tex_cache_size = TEX_CACHE_STEP;
    tex_cache = calloc(tex_cache_size, sizeof(struct GLTexture));
    if (!tex_cache) {
        printf("Ran out of memory allocating texture cache!");
        return;
    }

    // Check GL version
    int vmajor = 0;
    int vminor = 0;
    bool is_es = false;
    gl_get_version(&vmajor, &vminor, &is_es);
    if (vmajor < 2 && vminor < 1 && !is_es) {
        printf("GL: OpenGL 2.1+ is required.\nGL: Reported version: %s%d.%d\n", is_es ? "ES" : "", vmajor, vminor);
        return;
    }
    
    printf("GL: OpenGL loaded:\n");
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
    printf("Using:    OpenGL %s%d.%d\n", is_es ? "ES " : " ", vmajor, vminor);
    
    // Initialize resolution before drawing first frame
    
    if (current_width != gfx_current_dimensions.width || current_height != gfx_current_dimensions.height) {
        current_width = gfx_current_dimensions.width;
        current_height = gfx_current_dimensions.height;
    }
    
    // Initialize render targets

    if (USE_FRAMEBUFFER) {
        gfx_opengl_create_render_target_views(false);

        // Create the render target shader, used to draw into fullscreen quads

        rt_shader_program.opengl_program_id = gfx_opengl_compile_shader(rt_vertex_shader, rt_fragment_shader);
        rt_shader_program.attrib_locations[0] = glGetAttribLocation(rt_shader_program.opengl_program_id, "a_position");
        rt_shader_program.attrib_sizes[0] = 2;
        rt_shader_program.attrib_locations[1] = glGetAttribLocation(rt_shader_program.opengl_program_id, "a_uv");
        rt_shader_program.attrib_sizes[1] = 2;
        rt_shader_program.num_attribs = 2;
        rt_shader_program.num_floats = 4;
        rt_shader_program.used_textures[0] = true;
        rt_shader_program.used_textures[1] = false;
        rt_shader_program.num_inputs = 0;     // Unused in this case
        rt_shader_program.used_noise = false; // Unused in this case
        rt_shader_program.used_lightmap = false; // Unused in this case

        glUseProgram(rt_shader_program.opengl_program_id);
        GLint sampler_location = glGetUniformLocation(rt_shader_program.opengl_program_id, "u_texture");
        glUniform1i(sampler_location, 0);
    }

    glGenBuffers(1, &opengl_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, opengl_vbo);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#if !defined(__SWITCH__)
    if (vmajor >= 3 && !is_es) {
        glGenVertexArrays(1, &opengl_vao);
        glBindVertexArray(opengl_vao);
    }
#endif
    
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void gfx_opengl_on_resize(void) {
}

static void gfx_opengl_start_frame(void) {
    frame_count++;
    
    if (USE_FRAMEBUFFER) {
        if (current_width != gfx_current_dimensions.width || current_height != gfx_current_dimensions.height) {
            current_width = gfx_current_dimensions.width;
            current_height = gfx_current_dimensions.height;
            gfx_opengl_create_render_target_views(true);
        }
    }

    gfx_opengl_bind_render_target(&main_rt);

    glDisable(GL_SCISSOR_TEST);
    glDepthMask(GL_TRUE); // Must be set to clear Z-buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);
}

static void gfx_opengl_end_frame(void) {
    if (USE_FRAMEBUFFER) {
        // Set the shader and vertex attribs for quad rendering

        glUseProgram(rt_shader_program.opengl_program_id);
        gfx_opengl_vertex_array_set_attribs(&rt_shader_program);

        // Draw quad with main render target into the other render targets

        gfx_opengl_draw_render_target(NULL, &main_rt, false);
        gfx_opengl_draw_render_target(&framebuffer_rt, &main_rt, true);

        // Set again the last shader used before drawing render targets.
        // Not doing so can lead to rendering issues on the first drawcalls
        // of the next frame, if they use the same shader as the ones before.

        gfx_opengl_load_shader(current_shader_program);
    }
}

static void gfx_opengl_finish_render(void) {
}

static void gfx_opengl_shutdown(void) {
}

static void gfx_opengl_set_current_depth_test(bool depth_test) {
    current_depth_test = depth_test;
}

static void gfx_opengl_set_current_depth_mask(bool z_upd) {
    current_depth_mask = z_upd;
}

static void gfx_opengl_set_current_zmode_decal(bool zmode_decal) {
    current_zmode_decal = zmode_decal;
}

static void gfx_opengl_set_current_viewport(int x, int y, int width, int height) {
    current_viewport_x = x;
    current_viewport_y = y;
    current_viewport_width = width;
    current_viewport_height = height;
}

static void gfx_opengl_set_current_scissor(int x, int y, int width, int height) {
    current_scissor_x = x;
    current_scissor_y = y;
    current_scissor_width = width;
    current_scissor_height = height;
}

struct GfxRenderingAPI gfx_opengl_api = {
    gfx_opengl_z_is_from_0_to_1,
    gfx_opengl_unload_shader,
    gfx_opengl_load_shader,
    gfx_opengl_create_and_load_new_shader,
    gfx_opengl_lookup_shader,
    gfx_opengl_shader_get_info,
    gfx_opengl_new_texture,
    gfx_opengl_select_texture,
    gfx_opengl_upload_texture,
    gfx_opengl_set_sampler_parameters,
    gfx_opengl_set_current_depth_test,
    gfx_opengl_set_current_depth_mask,
    gfx_opengl_set_current_zmode_decal,
    gfx_opengl_set_current_viewport,
    gfx_opengl_set_current_scissor,
    gfx_opengl_set_use_alpha,
    gfx_opengl_draw_triangles,
    gfx_opengl_init,
    gfx_opengl_on_resize,
    gfx_opengl_start_frame,
    gfx_opengl_end_frame,
    gfx_opengl_finish_render,
    gfx_opengl_shutdown
};

#endif // RAPI_GL
