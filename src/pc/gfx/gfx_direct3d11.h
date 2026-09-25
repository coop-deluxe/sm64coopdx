#if defined(_WIN32)

#ifndef GFX_DIRECT3D11_H
#define GFX_DIRECT3D11_H

#include "gfx_rendering_api.h"

extern struct GfxRenderingAPI gfx_direct3d11_api;

#ifdef __cplusplus
extern "C" {
#endif

void d3d11_create_buffer_for_block(struct ShaderUniformBlock *block);

#ifdef __cplusplus
}
#endif

#endif

#endif
