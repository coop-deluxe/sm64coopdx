#ifdef RAPI_D3D11

#ifndef GFX_DIRECT3D_COMMON_H
#define GFX_DIRECT3D_COMMON_H

#include <stdint.h>

#include "gfx_cc.h"

void gfx_direct3d_common_build_shader(char buf[4096], size_t& len, size_t& num_floats, struct ColorCombiner& cc, const CCFeatures& cc_features, bool include_root_signature, bool three_point_filtering);

#endif

#endif
