#ifndef GFX_PC_H
#define GFX_PC_H

#include "types.h"
#include "pc/gfx/gfx.h"
#include "pc/gfx/gfx_cc.h"
#include "pc/gfx/gfx_shader.h"

enum PassFilter {
    PASS_FILTER_LINEAR,
    PASS_FILTER_NEAREST,
    PASS_FILTER_COUNT
};

enum ShaderFlag {
    SHADER_FLAG_HUE,
    SHADER_FLAG_SATURATION,
    SHADER_FLAG_BRIGHTNESS,
    SHADER_FLAG_CONTRAST,
    SHADER_FLAG_EXPOSURE,
    SHADER_FLAG_DITHERING,
    SHADER_FLAG_POSTERIZATION,
    SHADER_FLAG_SCANLINES,
    SHADER_FLAG_MAX
};

struct GfxRenderingAPI;

#define MAX_CUSTOM_FRAME_PASSES 64
#define MAX_FRAME_PASSES MAX_CUSTOM_FRAME_PASSES + 1

struct RSP {
    ALIGNED16 Mat4 MVP_matrix;
    ALIGNED16 Mat4 M_matrix;
    ALIGNED16 Mat4 V_matrix;
    ALIGNED16 Mat4 P_matrix;
    ALIGNED16 Mat4 modelview_matrix_stack[MAX_MATRIX_STACK_SIZE];
    uint32_t modelview_matrix_stack_size;

    uint32_t geometry_mode;
    int16_t fog_mul, fog_offset;
    int16_t fresnel_scale, fresnel_offset;

    struct {
        // U0.16
        uint16_t s, t;
    } texture_scaling_factor;

    bool lights_changed;
    uint8_t current_num_lights; // includes ambient light
    Vec3f current_lights_coeffs[MAX_LIGHTS];
    Vec3f current_lookat_coeffs[2]; // lookat_x, lookat_y
    Light_t current_lights[MAX_LIGHTS + 1];

    struct GfxVertex loaded_vertices[MAX_VERTICES + 4];
};

struct FramePass {
    // opengl
    u32 fbo;
    u32 depthBuffer;
    u64 passTexture;

    // d3d/metal specific stuff
    void *d3dSrv;
    union {
        void *d3dRtv;
        void *mtlColorTex;
    };
    union {
        void *d3dDsv;
        void *mtlDepthTex;
    };

    // global
    u32 width;
    u32 height;
    u32 lastWidth;
    u32 lastHeight;
    bool active;
    bool drawWorldGeometry;
    ColorRGBA clearColor;
    enum PassFilter passFilter;
};

extern struct RSP rsp;
extern struct FramePass gDefaultGeoFramePass;
extern struct FramePass gFramePasses[MAX_CUSTOM_FRAME_PASSES];
extern int gCurrentFramePassIndex;

extern Vec3f gLightingDir;
extern Color gLightingColor[2];
extern Color gVertexColor;
extern Color gFogColor;
extern f32 gFogIntensity;
extern bool gCullingEnabled;

extern bool gFullbright;

extern int gShaderFlags[SHADER_FLAG_MAX];
extern f32 gDefaultShaderFlagValues[SHADER_FLAG_MAX];
extern f32 gShaderFlagValues[SHADER_FLAG_MAX];
extern bool gShaderFlagsEnabled;

extern int gSelectedVertexUniformBuffer;
extern int gSelectedFragmentUniformBuffer;
extern enum ShaderStage gSelectedShaderStage;

#ifdef __cplusplus
extern "C" {
#endif

void gfx_init(struct GfxRenderingAPI *rapi, const char *window_title);
struct GfxRenderingAPI *gfx_get_current_rendering_api(void);
bool gfx_shader_stage_is(enum ShaderStage stage);
void gfx_start_frame(void);
void gfx_get_frame_pass_viewport_dimensions(struct FramePass *framePass, u32 *width, u32 *height);
struct FramePass *gfx_get_current_frame_pass(void);
//void gfx_run_basic(Gfx *commands);
void gfx_run(Gfx *commands);
void gfx_end_frame_render(void);
void gfx_display_frame(void);
void gfx_end_frame(void);
void gfx_shutdown(void);
void gfx_update_fog_uniforms(void);
void gfx_update_matrices(void);
void gfx_set_builtin_uniforms(void);
void gfx_remove_all_color_combiners(void);
void gfx_pc_precomp_shader(uint32_t rgb1, uint32_t alpha1, uint32_t rgb2, uint32_t alpha2, uint32_t flags);

#ifdef __cplusplus
}
#endif

#endif
