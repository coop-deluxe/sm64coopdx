#ifndef GFX_PC_H
#define GFX_PC_H

#include "types.h"
#include "pc/gfx/gfx.h"

struct GfxRenderingAPI;
struct GfxWindowManagerAPI;

struct RSP {
    ALIGNED16 Mat4 MP_matrix;
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

extern struct RSP rsp;

extern Vec3f gLightingDir;
extern Color gLightingColor[2];
extern Color gVertexColor;
extern Color gFogColor;
extern f32 gFogIntensity;

#ifdef __cplusplus
extern "C" {
#endif

void gfx_init(struct GfxWindowManagerAPI *wapi, struct GfxRenderingAPI *rapi, const char *window_title);
struct GfxRenderingAPI *gfx_get_current_rendering_api(void);
void gfx_start_frame(void);
void gfx_run(Gfx *commands);
void gfx_end_frame_render(void);
void gfx_display_frame(void);
void gfx_end_frame(void);
void gfx_shutdown(void);
void gfx_remove_all_color_combiners(void);
void gfx_pc_precomp_shader(uint32_t rgb1, uint32_t alpha1, uint32_t rgb2, uint32_t alpha2, uint32_t flags);

#ifdef __cplusplus
}
#endif

#endif
