#ifndef GFX_PC_H
#define GFX_PC_H

#include "types.h"
#include "gfx_rendering_api_config.h"

struct GfxRenderingAPI;
struct GfxWindowManagerAPI;

struct GfxDimensions {
    uint32_t width, height;
    float aspect_ratio;
};

extern struct GfxDimensions gfx_current_dimensions;

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
void gfx_start_frame();
void gfx_run(Gfx *commands);
void gfx_end_frame(void);
void gfx_shutdown(void);
void gfx_pc_precomp_shader(uint32_t rgb1, uint32_t alpha1, uint32_t rgb2, uint32_t alpha2, uint32_t flags);

void gfx_set_skybox(uint8_t skybox_id, float diffuse_color[3]);

#ifdef GFX_SEPARATE_PROJECTIONS
#include <stdbool.h>
void gfx_set_camera_perspective(float fov_degrees, float near_dist, float far_dist, bool can_interpolate);
void gfx_set_camera_matrix(float mat[4][4]);
#endif

#ifdef GFX_ENABLE_GRAPH_NODE_MODS
typedef struct {
    u32 UID;
    void *graphNodeMod;
} GraphNodeGfxInfo;

void gfx_register_layout_graph_node(void *geo_layout, void *graph_node);
void *gfx_build_graph_node_mod(void *graph_node, float modelview_matrix[4][4], uint32_t uid);
#endif

#ifdef __cplusplus
}
#endif

#endif
