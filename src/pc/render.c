#include "types.h"

#include "pc_main.h"
#include "debuglog.h"
#include "render.h"
#include "thread.h"
#include "buffers/buffers.h"

struct RenderData gRenderData = { 0 };
struct RenderData gNextRenderData = { 0 };

struct ThreadHandle gRenderThread = { 0 };

bool render_thread_processing_dl(Gfx *dlCommands) {
    if (gRenderThread.state == INVALID) { return false; }

    MUTEX_LOCK(gRenderThread);

    if (gRenderData.dlCommands == dlCommands) {
        MUTEX_UNLOCK(gRenderThread);
        return true;
    }

    MUTEX_UNLOCK(gRenderThread);
    return false;
}

void set_dl_for_render_thread(Gfx *dlCommands, f64 frameStartTime) {
    if (gRenderThread.state == INVALID) { return; }
    if (!dlCommands) { return; }
    MUTEX_LOCK(gRenderThread);
    gNextRenderData.dlCommands = dlCommands;
    gNextRenderData.gfxPoolIndex = gGfxPoolIndex;
    gNextRenderData.frameStartTime = frameStartTime;
    gNextRenderData.ready = true;
    MUTEX_UNLOCK(gRenderThread);
}

void *render_thread_init(UNUSED void *dummy) {
    while (1) {
        MUTEX_LOCK(gRenderThread);
        if (gNextRenderData.ready) {
            gRenderData = gNextRenderData;
            gNextRenderData.ready = false;
        }
        MUTEX_UNLOCK(gRenderThread);

        if (gRenderData.dlCommands != NULL) {
            produce_interpolation_frames_and_delay(&gRenderData);
        } else {
            gfx_wm_delay(1); // don't use 100% cpu usage
        }
    }

    return NULL;
}
