#pragma once

#define MAX_SHADER_VARIABLE_NAME 128
#define MAX_SHADER_TEXTURES 2
#define MAX_SHADER_INPUTS 512
#define MAX_SHADER_OUTPUTS 512
#define MAX_SHADER_UNIFORMS 1024
#define MAX_SHADER_BINDINGS 64

#ifdef _WIN32
#define COBJMACROS
#include <windows.h>
#include <d3d11.h>

// stupid windows crap
#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif
#endif

#include <glslang/Include/glslang_c_interface.h>
#include <glslang/Public/resource_limits_c.h>
#include <spirv_cross/spirv_cross_c.h>

#include "gfx_cc.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UNIFORM_BINDING_SLOT_OFFSET 1
#define MAX_UNIFORM_BLOCKS 8

typedef struct {
    u32 *words; // SPIR-V words
    int size; // number of words in SPIR-V shader
} SpirVShader;

enum ShaderStage {
    SHADER_STAGE_VERTEX,
    SHADER_STAGE_FRAGMENT,
    SHADER_STAGE_ANY,
    SHADER_STAGE_COUNT
};

typedef enum ShaderUniformType {
    SHADER_UNIFORM_TYPE_BOOL,
    SHADER_UNIFORM_TYPE_INT,
    SHADER_UNIFORM_TYPE_FLOAT,
    SHADER_UNIFORM_TYPE_VEC2,
    SHADER_UNIFORM_TYPE_VEC3,
    SHADER_UNIFORM_TYPE_VEC4,
    SHADER_UNIFORM_TYPE_MAT4
} ShaderUniformType;

struct ShaderBinding {
    char name[MAX_SHADER_VARIABLE_NAME];
    int binding;
};

struct ShaderUniform {
    char name[MAX_SHADER_VARIABLE_NAME];
    int location;
    int size;
    int arrayStride;
    int elementSize;
    int arrayLength;
    int blockIndex;
};

struct ShaderUniformBlock {
    char name[MAX_SHADER_VARIABLE_NAME];
    u32 size;
    u32 location;
    u8 *buffer;
    struct ShaderUniform uniforms[MAX_SHADER_UNIFORMS];
    int uniformCount;
    bool isGlobalBlock;
#ifdef _WIN32
    ID3D11Buffer *dxConstantBuffer; // dx11 doesn't use buffer, it uses a d3d11buffer
#endif
    unsigned int glBufferId; // opengl uses a buffer id
};

struct ShaderInput {
    char name[MAX_SHADER_VARIABLE_NAME];
    int location;
    int size;
};

struct ShaderOutput {
    char name[MAX_SHADER_VARIABLE_NAME];
    int location;
};

struct Shader {
    enum ShaderStage stage;
    SpirVShader spirVShader;
    struct ShaderInput shaderInputs[MAX_SHADER_INPUTS];
    struct ShaderOutput shaderOutputs[MAX_SHADER_OUTPUTS];
    struct ShaderBinding shaderBindings[MAX_SHADER_BINDINGS];
    struct ShaderUniformBlock uniformBlocks[MAX_UNIFORM_BLOCKS];
    int uniformBlockCount;
};

extern struct ShaderInput *gShaderInputs;
extern struct ShaderInput *gPostProcessShaderInputs;
extern struct ShaderBinding *gShaderBindings;
extern struct ShaderBinding *gPostProcessShaderBindings;

extern const char *gDefaultPostProcessVertexShader;
extern const char *gDefaultPostProcessFragmentShader;

char *gfx_get_default_vertex_shader_from_cc(UNUSED struct ColorCombiner *cc);
char *gfx_get_default_fragment_shader_from_cc(struct ColorCombiner *cc);
void gfx_init_shaders();
struct Shader *gfx_create_shader(const char *shaderCode);
bool gfx_compile_shader_to_spirv(glslang_stage_t stage, const char *shaderCode, struct Shader *shader);
void gfx_convert_spirv_to_glsl_410(char **shaderCode, struct Shader *shader);
void gfx_convert_spirv_to_hlsl(char **shaderCode, struct Shader *shader);
void gfx_convert_spirv_to_msl(char **shaderCode, struct Shader *shader);
bool gfx_generate_vertex_and_fragment_shader_from_cc(struct Shader *vertexShader, struct Shader *fragmentShader, struct ColorCombiner *cc, char **outVertShader, char **outFragShader);
bool gfx_generate_post_process_vertex_and_fragment_shader(struct Shader *vertexShader, struct Shader *fragmentShader, char **outVertShader, char **outFragShader);
void gfx_destroy_shader_contents(struct Shader *shader);
void gfx_destroy_shader(struct Shader *shader);

#ifdef __cplusplus
}
#endif
