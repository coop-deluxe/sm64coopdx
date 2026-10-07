#pragma once

#include "PR/gbi.h"
#include "thread.h"
#include "game/camera.h"

struct RenderData {
    Gfx *dlCommands;
    u32 gfxPoolIndex;
    f64 frameStartTime;
    bool ready;
};

extern struct RenderData gRenderData;
extern struct RenderData gNextRenderData;
extern struct ThreadHandle gRenderThread;

bool render_thread_processing_dl(Gfx *dlCommands);
void set_dl_for_render_thread(Gfx *dlCommands, f64 frameStartTime);
void *render_thread_init(UNUSED void *dummy);
