#pragma once

#include "gfx_rendering_api.h"
#include "gfx_window_manager.h"

extern struct GfxRenderingAPI gfx_sdl_gpu_api;

bool gfx_sdl_gpu_is_backend_supported(enum GfxWindowBackend backend);
