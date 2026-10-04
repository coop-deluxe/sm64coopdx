#include "types.h"

#include "pc_main.h"
#include "thread.h"

#include "pc/debuglog.h"

struct ThreadHandle gRenderThread = { 0 };

static Gfx *sCurrentDlCommands = NULL;
static Gfx *sNextDlCommands = NULL;

bool render_thread_processing_dl(Gfx *dlCommands) {
    if (gRenderThread.state == INVALID) { return false; }

    MUTEX_LOCK(gRenderThread);

    if (sCurrentDlCommands == dlCommands) {
        MUTEX_UNLOCK(gRenderThread);
        return true;
    }

    MUTEX_UNLOCK(gRenderThread);
    return false;
}

void set_dl_for_render_thread(Gfx *dlCommands) {
    if (gRenderThread.state == INVALID) { return; }
    if (!dlCommands) { return; }
    MUTEX_LOCK(gRenderThread);
    sNextDlCommands = dlCommands;
    MUTEX_UNLOCK(gRenderThread);
}

void *render_thread_init(UNUSED void *dummy) {
    while (1) {
        MUTEX_LOCK(gRenderThread);
        if (sNextDlCommands != NULL) {
            sCurrentDlCommands = sNextDlCommands;
            sNextDlCommands = NULL;
        }
        MUTEX_UNLOCK(gRenderThread);

        if (sCurrentDlCommands != NULL) {
            produce_interpolation_frames_and_delay(sCurrentDlCommands, false);
        } else {
            gfx_wm_delay(1); // don't use 100% cpu usage
        }
    }

    return NULL;
}
