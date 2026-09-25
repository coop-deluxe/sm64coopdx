#include <stdint.h>
#include <stdbool.h>

#ifndef _LANGUAGE_C
# define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#ifdef __MINGW32__
# define FOR_WINDOWS 1
#else
# define FOR_WINDOWS 0
#endif

#if FOR_WINDOWS || defined(OSX_BUILD)
# define GLEW_STATIC
# include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1

#include <SDL2/SDL.h>
#ifdef USE_GLES
#include <SDL2/SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#ifdef __linux__
#include <GL/glext.h>
#endif
#endif

#include "../platform.h"
#include "../configfile.h"
#include "pc/pc_main.h"
#include "gfx_cc.h"
#include "gfx_rendering_api.h"
#include "gfx_shader.h"
#include "gfx_pc.h"
#include "gfx_opengl.h"
#include "pc/lua/smlua.h"
#include "game/rendering_graph_node.h"

#define TEX_CACHE_STEP 512

struct GLTexture {
    GLuint gltex;
    GLfloat size[2];
    bool filter;
};

static struct ShaderProgram shader_program_pool[MAX_FRAME_PASSES][CC_MAX_SHADERS];
static uint8_t shader_program_pool_size[MAX_FRAME_PASSES] = { 0 };
static uint8_t shader_program_pool_index[MAX_FRAME_PASSES] = { 0 };

static struct ShaderProgram post_process_shader_program_pool[MAX_FRAME_PASSES];

static GLuint opengl_vbo;
static GLuint opengl_vao;

static int tex_cache_size = 0;
static int num_textures = 0;
static struct GLTexture *tex_cache = NULL;

static struct ShaderProgram *opengl_prg = NULL;
static struct GLTexture *opengl_tex[2];
static GLint opengl_max_texture_units = 0;
static int opengl_curtex = 0;

static bool gfx_opengl_is_legacy(void);

static bool gfx_opengl_z_is_from_0_to_1(void) {
    return !gfx_opengl_is_legacy();
}

static void gfx_opengl_vertex_array_set_attribs(struct ShaderProgram *prg) {
    size_t num_floats = prg->num_floats;
    size_t pos = 0;

    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        glDisableVertexAttribArray(i);
    }

    for (int i = 0; i < prg->num_attribs; i++) {
        glEnableVertexAttribArray(prg->attrib_locations[i]);
        glVertexAttribPointer(prg->attrib_locations[i], prg->attrib_sizes[i], GL_FLOAT, GL_FALSE, num_floats * sizeof(float), (void *) (pos * sizeof(float)));
        pos += prg->attrib_sizes[i];
    }
}

static inline void gfx_opengl_set_texture_uniforms(struct ShaderProgram *prg, const int tile) {
    if (!prg) return;
    if (opengl_tex[tile]) {
        glUniform2f(prg->uniform_locations[tile * 2 + 0], opengl_tex[tile]->size[0], opengl_tex[tile]->size[1]);
        glUniform1i(prg->uniform_locations[tile * 2 + 1], opengl_tex[tile]->filter);
    }
}

static void gfx_opengl_unload_shader(struct ShaderProgram *old_prg) {
    if (old_prg != NULL) {
        for (int i = 0; i < old_prg->num_attribs; i++) {
            glDisableVertexAttribArray(old_prg->attrib_locations[i]);
        }

        if (old_prg == opengl_prg) {
            opengl_prg = NULL;
        }
    } else {
        opengl_prg = NULL;
    }
}

static void gfx_opengl_load_shader(struct ShaderProgram *new_prg) {
    opengl_prg = new_prg;
    glUseProgram(new_prg->opengl_program_id);
    gfx_opengl_vertex_array_set_attribs(new_prg);
    gfx_opengl_set_texture_uniforms(new_prg, 0);
    gfx_opengl_set_texture_uniforms(new_prg, 1);
}

static void gfx_opengl_remove_shaders(void) {
    for (int i = 0; i < MAX_FRAME_PASSES; i++) {
        for (int j = 0; j < CC_MAX_SHADERS; j++) {
            gfx_opengl_unload_shader(&shader_program_pool[i][j]);
            gfx_destroy_shader(shader_program_pool[i][j].vertexShader);
            gfx_destroy_shader(shader_program_pool[i][j].fragmentShader);
            memset(&shader_program_pool[i][j], 0, sizeof(shader_program_pool[i][j]));
        }

        gfx_opengl_unload_shader(&post_process_shader_program_pool[i]);
        gfx_destroy_shader(post_process_shader_program_pool[i].vertexShader);
        gfx_destroy_shader(post_process_shader_program_pool[i].fragmentShader);
        memset(&post_process_shader_program_pool[i], 0, sizeof(post_process_shader_program_pool[i]));

        shader_program_pool_index[i] = 0;
        shader_program_pool_size[i] = 0;
    }
}

static void bind_uniform_block_for_shader(u32 programId, struct Shader *shader) {
    for (int i = 0; i < shader->uniformBlockCount; i++) {
        struct ShaderUniformBlock *block = &shader->uniformBlocks[i];

        GLuint blockIndex = glGetUniformBlockIndex(programId, block->name);
        if (blockIndex != GL_INVALID_INDEX) {
            glUniformBlockBinding(programId, blockIndex, block->location);
        }
    }
}

static struct ShaderProgram *gfx_opengl_create_and_load_new_shader(struct ColorCombiner *cc) {
    struct CCFeatures ccf = { 0 };
    gfx_cc_get_features(cc, &ccf);

    bool opt_alpha = cc->cm.use_alpha;
    bool opt_light_map = cc->cm.light_map;
    bool world_geometry = cc->cm.world_geometry;
    bool opt_dither = cc->cm.use_dither;
    bool opt_fog = cc->cm.use_fog;

    struct Shader *vertexShader = calloc(1, sizeof(struct Shader));
    struct Shader *fragmentShader = calloc(1, sizeof(struct Shader));
    if (!vertexShader || !fragmentShader) {
        sys_fatal("Failed to allocate shaders, ran out of memory!");
    }

    gfx_generate_vertex_and_fragment_shader_from_cc(vertexShader, fragmentShader, cc, NULL, NULL);

    char *vsShaderCode = NULL;
    char *fsShaderCode = NULL;
    gfx_convert_spirv_to_glsl_410(&vsShaderCode, vertexShader);
    gfx_convert_spirv_to_glsl_410(&fsShaderCode, fragmentShader);

    const GLchar *sources[2] = { vsShaderCode, fsShaderCode };
    GLint lengths[2] = { strlen(vsShaderCode), strlen(fsShaderCode) };
    GLint success;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &sources[0], &lengths[0]);
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
    glShaderSource(fragment_shader, 1, &sources[1], &lengths[1]);
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

    int framePassIndex = gCurrentFramePassIndex + 1;

    struct ShaderProgram *prg = &shader_program_pool[framePassIndex][shader_program_pool_index[framePassIndex]];
    shader_program_pool_index[framePassIndex] = (shader_program_pool_index[framePassIndex] + 1) % CC_MAX_SHADERS;
    if (shader_program_pool_size[framePassIndex] < CC_MAX_SHADERS) { shader_program_pool_size[framePassIndex]++; }

    size_t cnt = 0;
    size_t num_floats = 0;

    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        if (gShaderInputs[i].size == 0) { continue; }
        prg->attrib_locations[i] = glGetAttribLocation(shader_program, gShaderInputs[i].name);
        prg->attrib_sizes[i] = gShaderInputs[i].size;
        num_floats += gShaderInputs[i].size;
        cnt++;
    }

    prg->hash = cc->hash;
    prg->opengl_program_id = shader_program;
    prg->num_inputs = ccf.num_inputs;
    prg->used_textures[0] = ccf.used_textures[0];
    prg->used_textures[1] = ccf.used_textures[1];
    prg->num_floats = num_floats;
    prg->num_attribs = cnt;

    glUseProgram(shader_program);

    bind_uniform_block_for_shader(shader_program, vertexShader);
    bind_uniform_block_for_shader(shader_program, fragmentShader);

    for (int t = 0; t < 2; t++) {
        char name[16];
        sprintf(name, "uTex%d", t);
        GLint sampler_location = glGetUniformLocation(shader_program, name);
        sprintf(name, "uTex%dSize", t);
        prg->uniform_locations[t * 2] = glGetUniformLocation(shader_program, name);
        sprintf(name, "uTex%dFilter", t);
        prg->uniform_locations[t * 2 + 1] = glGetUniformLocation(shader_program, name);
        glUniform1i(sampler_location, t);
    }

    if ((opt_alpha && opt_dither) || ccf.do_noise) {
        prg->used_noise = true;
    } else {
        prg->used_noise = false;
    }

    prg->used_lightmap = opt_light_map;
    prg->world_geometry = world_geometry;
    prg->used_fog = opt_fog;

    GLint passTexLoc = glGetUniformLocation(shader_program, "uPassTex");
    if (passTexLoc != -1) {
        glUniform1i(passTexLoc, 10);
    }

    char uniformName[16];
    for (int i = 0; i < MIN(MAX_CUSTOM_FRAME_PASSES, opengl_max_texture_units - 10); i++) {
        snprintf(uniformName, sizeof(uniformName), "uPassTex%d", i);
        GLint loc = glGetUniformLocation(shader_program, uniformName);
        if (loc != -1) {
            glUniform1i(loc, 10 + i);
        }
    }

    prg->vertexShader = vertexShader;
    prg->fragmentShader = fragmentShader;

    gfx_opengl_load_shader(prg);

    free(vsShaderCode);
    free(fsShaderCode);

    return prg;
}

static struct ShaderProgram *gfx_opengl_create_or_load_post_process_shader(void) {
    int framePassIndex = gCurrentFramePassIndex + 1;
    // if a shader already exists, use that instead
    if (post_process_shader_program_pool[framePassIndex].opengl_program_id != 0) {
        gfx_opengl_load_shader(&post_process_shader_program_pool[framePassIndex]);
        return &post_process_shader_program_pool[framePassIndex];
    }

    struct Shader *vertexShader = calloc(1, sizeof(struct Shader));
    struct Shader *fragmentShader = calloc(1, sizeof(struct Shader));
    if (!vertexShader || !fragmentShader) {
        sys_fatal("Failed to allocate shaders, ran out of memory!");
    }

    gfx_generate_post_process_vertex_and_fragment_shader(vertexShader, fragmentShader, NULL, NULL);

    char *vsShaderCode = NULL;
    char *fsShaderCode = NULL;
    gfx_convert_spirv_to_glsl_410(&vsShaderCode, vertexShader);
    gfx_convert_spirv_to_glsl_410(&fsShaderCode, fragmentShader);

    const GLchar *sources[2] = { vsShaderCode, fsShaderCode };
    GLint lengths[2] = { strlen(vsShaderCode), strlen(fsShaderCode) };
    GLint success;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &sources[0], &lengths[0]);
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
    glShaderSource(fragment_shader, 1, &sources[1], &lengths[1]);
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

    size_t cnt = 0;
    size_t num_floats = 0;

    struct ShaderProgram *prg = &post_process_shader_program_pool[framePassIndex];

    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        if (gPostProcessShaderInputs[i].size == 0) continue;
        prg->attrib_locations[i] = glGetAttribLocation(shader_program, gPostProcessShaderInputs[i].name);
        prg->attrib_sizes[i] = gPostProcessShaderInputs[i].size;
        num_floats += gPostProcessShaderInputs[i].size;
        cnt++;
    }

    prg->hash = framePassIndex;
    prg->opengl_program_id = shader_program;
    prg->num_floats = num_floats;
    prg->num_attribs = cnt;

    glUseProgram(shader_program);

    bind_uniform_block_for_shader(shader_program, vertexShader);
    bind_uniform_block_for_shader(shader_program, fragmentShader);

    prg->vertexShader = vertexShader;
    prg->fragmentShader = fragmentShader;

    gfx_opengl_load_shader(prg);

    for (int t = 0; t < 2; t++) {
        char name[16];
        sprintf(name, "uTex%d", t);
        GLint sampler_location = glGetUniformLocation(shader_program, name);
        sprintf(name, "uTex%dSize", t);
        prg->uniform_locations[t * 2] = glGetUniformLocation(shader_program, name);
        sprintf(name, "uTex%dFilter", t);
        prg->uniform_locations[t * 2 + 1] = glGetUniformLocation(shader_program, name);
        glUniform1i(sampler_location, t);
    }

    GLint passTexLoc = glGetUniformLocation(shader_program, "uPassTex");
    if (passTexLoc != -1) {
        glUniform1i(passTexLoc, 10);
    }

    char uniformName[16];
    for (int i = 0; i < MIN(MAX_CUSTOM_FRAME_PASSES, opengl_max_texture_units - 10); i++) {
        snprintf(uniformName, sizeof(uniformName), "uPassTex%d", i);
        GLint loc = glGetUniformLocation(shader_program, uniformName);
        if (loc != -1) {
            glUniform1i(loc, 10 + i);
        }
    }

    free(vsShaderCode);
    free(fsShaderCode);

    gfx_opengl_load_shader(prg);

    return prg;
}

static struct ShaderProgram *gfx_opengl_lookup_shader(struct ColorCombiner *cc) {
    int framePassIndex = gCurrentFramePassIndex + 1;
    if (framePassIndex < 0 || framePassIndex >= MAX_FRAME_PASSES) { return NULL; }
    for (size_t i = 0; i < shader_program_pool_size[framePassIndex]; i++) {
        if (shader_program_pool[framePassIndex][i].hash == cc->hash) {
            return &shader_program_pool[framePassIndex][i];
        }
    }
    return NULL;
}

static struct ShaderProgram* gfx_opengl_lookup_shader_using_index(uint8_t shaderIndex, uint8_t framePassIndex) {
    framePassIndex++;
    if (shaderIndex >= shader_program_pool_size[framePassIndex]) return NULL;
    return &shader_program_pool[framePassIndex][shaderIndex];
}

static void gfx_opengl_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    *num_inputs = prg->num_inputs;
    used_textures[0] = prg->used_textures[0];
    used_textures[1] = prg->used_textures[1];
}

static void gfx_opengl_create_framebuffer(struct FramePass *framePass) {
    glGenFramebuffers(1, &framePass->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, framePass->fbo);

    u32 viewportWidth;
    u32 viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(framePass, &viewportWidth, &viewportHeight);

    glGenTextures(1, (GLuint *)&framePass->passTexture);
    glBindTexture(GL_TEXTURE_2D, framePass->passTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, viewportWidth, viewportHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    GLint filter = framePass->passFilter == PASS_FILTER_LINEAR ? GL_LINEAR : GL_NEAREST;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framePass->passTexture, 0);

    // create depth buffer
    glGenRenderbuffers(1, &framePass->depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, framePass->depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, viewportWidth, viewportHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, framePass->depthBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG_ERROR("Framebuffer is not complete!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

static void gfx_opengl_delete_framebuffer(struct FramePass *framePass) {
    if (framePass->fbo > 0) { glDeleteFramebuffers(1, &framePass->fbo); framePass->fbo = 0; }
    if (framePass->depthBuffer > 0) { glDeleteRenderbuffers(1, &framePass->depthBuffer); framePass->depthBuffer = 0; }
    if (framePass->passTexture > 0) { glDeleteTextures(1, (GLuint *)&framePass->passTexture); framePass->passTexture = 0; }
}

static void gfx_opengl_set_framebuffer(struct FramePass *framePass) {
    u32 viewportWidth, viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(framePass, &viewportWidth, &viewportHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, framePass->fbo);
    glViewport(0, 0, viewportWidth, viewportHeight);
    glScissor(0, 0, viewportWidth, viewportHeight);
}

static void gfx_opengl_reset_framebuffer(void) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    u32 windowWidth, windowHeight;
    gfx_get_dimensions(&windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glScissor(0, 0, windowWidth, windowHeight);
}

size_t gfx_opengl_get_uniform_buffer_size(enum ShaderStage stage, int bufferIndex) {
    if (bufferIndex < 0 || bufferIndex >= MAX_UNIFORM_BLOCKS) { return 0; }

    struct Shader *shader = NULL;
    if (stage == SHADER_STAGE_VERTEX) {
        shader = opengl_prg->vertexShader;
    } else if (stage == SHADER_STAGE_FRAGMENT) {
        shader = opengl_prg->fragmentShader;
    } else {
        return 0;
    }

    return shader->uniformBlocks[bufferIndex].size;
}

void gfx_opengl_set_uniform_buffer(enum ShaderStage stage, const char *name) {
    struct Shader *shader = NULL;
    int *destination = NULL;
    if (stage == SHADER_STAGE_VERTEX) {
        shader = opengl_prg->vertexShader;
        destination = &gSelectedVertexUniformBuffer;
    } else if (stage == SHADER_STAGE_FRAGMENT) {
        shader = opengl_prg->fragmentShader;
        destination = &gSelectedFragmentUniformBuffer;
    } else {
        return;
    }

    for (int i = 0; i < MAX_UNIFORM_BLOCKS; i++) {
        struct ShaderUniformBlock *uniformBlock = &shader->uniformBlocks[i];

        if (strcmp(uniformBlock->name, name) == 0) {
            *destination = i;
            return;
        }
    }
}

static void gfx_opengl_set_uniform_for_specific_shader(struct ShaderUniformBlock *uniformBlock, const char *name, const void *data, uint32_t numElements) {
    for (int i = 0; i < MAX_SHADER_UNIFORMS; i++) {
        struct ShaderUniform *uniform = &uniformBlock->uniforms[i];
        if (uniform->size == 0) { break; }

        if (strcmp(uniform->name, name) == 0) {
            u8 *dst = uniformBlock->buffer;
            dst += uniform->location;

            if (uniform->arrayLength > 1) {
                const u8 *src = (const u8 *)data;
                u32 count = MIN((int)numElements, uniform->arrayLength);
                for (u32 j = 0; j < count; j++) {
                    memcpy(dst + j * uniform->arrayStride, src + j * uniform->elementSize, uniform->elementSize);
                }
            } else {
                memcpy(dst, data, uniform->size);
            }
            return;
        }
    }
}

void gfx_opengl_set_uniform(struct ShaderProgram *prg, const char *name, UNUSED ShaderUniformType type, const void *data, uint32_t numElements) {
    if (prg == NULL) {
        if (opengl_prg == NULL) { return; }
        prg = opengl_prg;
    }

    if (gfx_shader_stage_is(SHADER_STAGE_VERTEX)) {
        gfx_opengl_set_uniform_for_specific_shader(&prg->vertexShader->uniformBlocks[gSelectedVertexUniformBuffer], name, data, numElements);
    }
    if (gfx_shader_stage_is(SHADER_STAGE_FRAGMENT)) {
        gfx_opengl_set_uniform_for_specific_shader(&prg->fragmentShader->uniformBlocks[gSelectedFragmentUniformBuffer], name, data, numElements);
    }
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
    gfx_opengl_set_texture_uniforms(opengl_prg, tile);
}

static void gfx_opengl_bind_texture_raw(int tile, uint64_t texture_id) {
    if (tile >= opengl_max_texture_units) { return; }
    glActiveTexture(GL_TEXTURE0 + tile);
    glBindTexture(GL_TEXTURE_2D, (GLuint)texture_id);
}

static void gfx_opengl_upload_texture(const uint8_t *rgba32_buf, int width, int height) {
    if (width <= 0 || height <= 0) { sys_fatal("Texture dimensions are invalid!"); }
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
        gfx_opengl_set_texture_uniforms(opengl_prg, tile);
    }
}

static void gfx_opengl_set_depth_test(bool depth_test) {
    if (depth_test) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

static void gfx_opengl_set_depth_mask(bool z_upd) {
    glDepthMask(z_upd ? GL_TRUE : GL_FALSE);
}

static void gfx_opengl_set_zmode_decal(bool zmode_decal) {
    if (zmode_decal) {
        glPolygonOffset(-2, -2);
        glEnable(GL_POLYGON_OFFSET_FILL);
    } else {
        glPolygonOffset(0, 0);
        glDisable(GL_POLYGON_OFFSET_FILL);
    }
}

static void gfx_opengl_set_viewport(int x, int y, int width, int height) {
    int adjustedY = y;
    if (!gfx_opengl_is_legacy()) {
        struct FramePass *framePass = gfx_get_current_frame_pass();
        u32 viewportHeight;
        gfx_get_frame_pass_viewport_dimensions(framePass, NULL, &viewportHeight);
        adjustedY = viewportHeight - y - height;
    }
    glViewport(x, adjustedY, width, height);
}

static void gfx_opengl_set_scissor(int x, int y, int width, int height) {
    int adjustedY = y;
    if (!gfx_opengl_is_legacy()) {
        struct FramePass *framePass = gfx_get_current_frame_pass();
        u32 viewportHeight;
        gfx_get_frame_pass_viewport_dimensions(framePass, NULL, &viewportHeight);
        adjustedY = viewportHeight - y - height;
    }
    glScissor(x, adjustedY, width, height);
}

static void gfx_opengl_set_use_alpha(bool use_alpha) {
    if (use_alpha) {
        glEnable(GL_BLEND);
    } else {
        glDisable(GL_BLEND);
    }
}

static void gfx_opengl_set_vsync(UNUSED bool enabled) {
}

static void upload_opengl_uniform_buffers(struct Shader *shader) {
    for (int i = 0; i < shader->uniformBlockCount; i++) {
        struct ShaderUniformBlock *uniformBlock = &shader->uniformBlocks[i];

        if (uniformBlock->size == 0 || uniformBlock->glBufferId == 0) {
            continue;
        }

        glBindBuffer(GL_UNIFORM_BUFFER, uniformBlock->glBufferId);
        glBufferData(GL_UNIFORM_BUFFER, uniformBlock->size, NULL, GL_STREAM_DRAW); // orphan
        glBufferSubData(GL_UNIFORM_BUFFER, 0, uniformBlock->size, uniformBlock->buffer);
        glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlock->location, uniformBlock->glBufferId);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static void gfx_opengl_draw_triangles(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {
    //printf("flushing %d tris\n", buf_vbo_num_tris);
    gfx_update_matrices();
    if (opengl_prg->used_fog) {
        gfx_update_fog_uniforms();
    }
    smlua_call_event_hooks(HOOK_ON_DRAW_TRIANGLE);
    upload_opengl_uniform_buffers(opengl_prg->vertexShader);
    upload_opengl_uniform_buffers(opengl_prg->fragmentShader);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buf_vbo_len, buf_vbo, GL_STREAM_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 3 * buf_vbo_num_tris);
}

static inline bool gl_version_is_supported(int major, int minor, bool is_es) {
    if (is_es) {
        return major >= 2;
    }
    return (major > 4) || (major == 4 && minor >= 1);
}

static inline bool gl_get_version(int *major, int *minor, bool *is_es) {
    const char *vstr = (const char *)glGetString(GL_VERSION);
    if (!vstr || !vstr[0]) return false;

    if (!strncmp(vstr, "OpenGL ES ", 10)) {
        vstr += 10;
        *is_es = true;
    } else if (!strncmp(vstr, "OpenGL ES-CM ", 13)) {
        vstr += 13;
        *is_es = true;
    }

    return (sscanf(vstr, "%d.%d", major, minor) == 2);
}

static void gfx_opengl_init(void) {
#if FOR_WINDOWS || defined(OSX_BUILD)
    GLenum err;
    if ((err = glewInit()) != GLEW_OK) {
        sys_fatal("could not init GLEW:\n%s", glewGetErrorString(err));
    }
#endif

    tex_cache_size = TEX_CACHE_STEP;
    tex_cache = calloc(tex_cache_size, sizeof(struct GLTexture));
    if (!tex_cache) { sys_fatal("out of memory allocating texture cache"); }

    // check GL version
    int vmajor = 0;
    int vminor = 0;
    bool is_es = false;
    if (!gl_get_version(&vmajor, &vminor, &is_es) || !gl_version_is_supported(vmajor, vminor, is_es)) {
        sys_fatal("OpenGL 4.1+ is required.\nReported version: %s%d.%d", is_es ? "ES" : "", vmajor, vminor);
    }

    glGenBuffers(1, &opengl_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, opengl_vbo);

    if (vmajor >= 3 && !is_es) {
        glGenVertexArrays(1, &opengl_vao);
        glBindVertexArray(opengl_vao);
    }

    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!gfx_opengl_is_legacy()) {
        // force opengl to use modern clip space (0, 1) and upper left like modern renderers
        glClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);
    }

    // query max texture units
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &opengl_max_texture_units);
    if (opengl_max_texture_units < MAX_CUSTOM_FRAME_PASSES + 10) {
        LOG_INFO("Your GPU in OpenGL supports %d texture slots! The maximum that may be used is %d. Some shaders may fail, but most should work fine", opengl_max_texture_units, MAX_CUSTOM_FRAME_PASSES + 10);
    }
}

bool gfx_opengl_check_compatibility(void) {
    // check GL version
    int vmajor = 0;
    int vminor = 0;
    bool is_es = false;
    if (!gl_get_version(&vmajor, &vminor, &is_es)) {
        return false;
    }
    return gl_version_is_supported(vmajor, vminor, is_es);
}

static void gfx_opengl_on_resize(void) {
    for (int i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
        struct FramePass *framePass = &gFramePasses[i];
        if (!framePass->active) { continue; }

        if (framePass->width == 0 || framePass->height == 0) {
            // needs to be recreated to redo viewport size
            gfx_opengl_delete_framebuffer(framePass);
        }
    }
}

static void gfx_opengl_start_frame(void) {
    glDisable(GL_SCISSOR_TEST);
    glDepthMask(GL_TRUE); // Must be set to clear Z-buffer

    struct FramePass *framePass = gfx_get_current_frame_pass();
    glClearColor(
        framePass->clearColor[0] / 255.0f,
        framePass->clearColor[1] / 255.0f,
        framePass->clearColor[2] / 255.0f,
        framePass->clearColor[3] / 255.0f
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);
}

static void gfx_opengl_end_frame(void) {
}

static void gfx_opengl_finish_render(void) {
}

static const char *gfx_opengl_get_name(void) {
    return gfx_opengl_is_legacy() ? "OpenGL (Legacy)" : "OpenGL";
}

static bool gfx_opengl_is_legacy(void) {
    if (gRenderApi != &gfx_opengl_api) { return false; }
    int vmajor = 0;
    int vminor = 0;
    bool is_es = false;
    if (!gl_get_version(&vmajor, &vminor, &is_es)) {
        return true;
    }
    if (is_es) {
        return true;
    }
    return (vmajor < 4) || (vmajor == 4 && vminor < 5);
}

static void gfx_opengl_shutdown(void) {
}

struct GfxRenderingAPI gfx_opengl_api = {
    gfx_opengl_z_is_from_0_to_1,
    gfx_opengl_unload_shader,
    gfx_opengl_load_shader,
    gfx_opengl_remove_shaders,
    gfx_opengl_create_and_load_new_shader,
    gfx_opengl_create_or_load_post_process_shader,
    gfx_opengl_lookup_shader,
    gfx_opengl_lookup_shader_using_index,
    gfx_opengl_shader_get_info,
    gfx_opengl_create_framebuffer,
    gfx_opengl_delete_framebuffer,
    gfx_opengl_set_framebuffer,
    gfx_opengl_reset_framebuffer,
    gfx_opengl_get_uniform_buffer_size,
    gfx_opengl_set_uniform_buffer,
    gfx_opengl_set_uniform,
    gfx_opengl_new_texture,
    gfx_opengl_select_texture,
    gfx_opengl_bind_texture_raw,
    gfx_opengl_upload_texture,
    gfx_opengl_set_sampler_parameters,
    gfx_opengl_set_depth_test,
    gfx_opengl_set_depth_mask,
    gfx_opengl_set_zmode_decal,
    gfx_opengl_set_viewport,
    gfx_opengl_set_scissor,
    gfx_opengl_set_use_alpha,
    gfx_opengl_set_vsync,
    gfx_opengl_draw_triangles,
    gfx_opengl_init,
    gfx_opengl_on_resize,
    gfx_opengl_start_frame,
    gfx_opengl_end_frame,
    gfx_opengl_finish_render,
    gfx_opengl_get_name,
    gfx_opengl_is_legacy,
    gfx_opengl_shutdown
};
