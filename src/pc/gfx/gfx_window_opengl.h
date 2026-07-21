#pragma once

#include "gfx_window_manager.h"

extern struct GfxWindowBackendAPI gfx_window_opengl;

bool gfx_window_opengl_check_compatibility(void);