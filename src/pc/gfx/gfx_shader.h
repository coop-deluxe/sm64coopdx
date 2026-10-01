#pragma once

#include <glslang/Include/glslang_c_interface.h>
#include <glslang/Public/resource_limits_c.h>
#include <spirv_cross/spirv_cross_c.h>

#include "gfx_cc.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SHADER_VARIABLE_NAME 512
#define MAX_SHADER_TEXTURES 2
#define MAX_SHADER_INPUTS 512
#define MAX_SHADER_OUTPUTS 512
#define MAX_SHADER_UNIFORMS 1024
#define MAX_SHADER_SAMPLERS 64

#define UNIFORM_BINDING_SLOT_OFFSET 0
#define MAX_UNIFORM_BLOCKS 8

struct SpirVShader {
    u32 *words; // SPIR-V words
    int size; // number of words in SPIR-V shader
};

enum ShaderStage {
    SHADER_STAGE_VERTEX,
    SHADER_STAGE_FRAGMENT,
    SHADER_STAGE_ANY,
    SHADER_STAGE_COUNT
};

struct ShaderSampler {
    char *name;
    int binding;
};

struct ShaderUniform {
    char *name;
    spvc_basetype baseType;
    int location;
    int size;
    int arrayStride;
    int elementSize;
    int arrayLength;
    int blockIndex;
};

struct ShaderUniformBlock {
    char *name;
    u32 size;
    u32 location;
    u8 *buffer;
    struct ShaderUniform uniforms[MAX_SHADER_UNIFORMS];
    int uniformCount;
    bool isGlobalBlock;
    bool hasChanged;
    unsigned int glBufferId; // opengl uses a buffer id
};

struct ShaderInput {
    char *name;
    int location;
    int size;
};

struct ShaderOutput {
    char *name;
    int location;
};

struct Shader {
    enum ShaderStage stage;
    struct SpirVShader spirVShader;
    struct ShaderInput shaderInputs[MAX_SHADER_INPUTS];
    struct ShaderOutput shaderOutputs[MAX_SHADER_OUTPUTS];
    struct ShaderSampler shaderSamplers[MAX_SHADER_SAMPLERS];
    struct ShaderUniformBlock uniformBlocks[MAX_UNIFORM_BLOCKS];
    int uniformBlockCount;
    int samplerCount;
};

extern struct ShaderInput gShaderInputs[MAX_SHADER_INPUTS];
extern struct ShaderInput gPostProcessShaderInputs[MAX_SHADER_INPUTS];

extern const char *gDefaultPostProcessVertexShader;
extern const char *gDefaultPostProcessFragmentShader;

char *gfx_get_default_vertex_shader_from_cc(UNUSED struct ColorCombiner *cc);
char *gfx_get_default_fragment_shader_from_cc(struct ColorCombiner *cc);
void gfx_init_shaders();
struct Shader *gfx_create_shader(const char *shaderCode);
bool gfx_compile_shader_to_spirv(glslang_stage_t stage, const char *shaderCode, struct Shader *shader);
void gfx_convert_spirv_to_glsl_410(char **shaderCode, struct Shader *shader);
void gfx_convert_spirv_to_hlsl(char **shaderCode, struct Shader *shader, u32 shaderModel);
void gfx_convert_spirv_to_msl(char **shaderCode, struct Shader *shader);
void gfx_process_spirv(struct Shader *shader);
bool gfx_generate_vertex_and_fragment_shader_from_cc(struct Shader *vertexShader, struct Shader *fragmentShader, struct ColorCombiner *cc, char **outVertShader, char **outFragShader);
bool gfx_generate_post_process_vertex_and_fragment_shader(struct Shader *vertexShader, struct Shader *fragmentShader, char **outVertShader, char **outFragShader);
void gfx_destroy_shader_contents(struct Shader *shader);
void gfx_destroy_shader(struct Shader *shader);

#ifdef __cplusplus
}
#endif
