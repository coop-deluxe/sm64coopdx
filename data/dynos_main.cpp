#include "dynos.cpp.h"
extern "C" {
#include "level_commands.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
}

//
// Update
//

static bool sDynosIsLevelEntry = false;
void *DynOS_SwapCmd(void *aCmd) {
    return DynOS_Lvl_Override(aCmd);
}

void *DynOS_UpdateCmd(void *aCmd) {
    if (!aCmd) { return NULL; }

    static const uintptr_t sCmdLevelEntry[] = { CALL(0, lvl_init_or_update) };
    sDynosIsLevelEntry |= (((uintptr_t*)aCmd)[0] == sCmdLevelEntry[0] && ((uintptr_t*)aCmd)[1] == sCmdLevelEntry[1]);
    return DynOS_Warp_Update(aCmd, sDynosIsLevelEntry);
}

void DynOS_UpdateGfx() {
    DynOS_Mod_Update();
    DynOS_Tex_Update();
}

bool DynOS_IsTransitionActive() {
    return gWarpTransition.isActive;
}

//
// Misc
//
static bool sDynosModShutdown = false;

void DynOS_Mod_Update() {
    if (sDynosModShutdown) {
        sDynosModShutdown = false;
        DynOS_Actor_ModShutdown();
        DynOS_Col_ModShutdown();
        DynOS_Lvl_ModShutdown();
        DynOS_Bhv_ModShutdown();
        DynOS_MovtexQC_ModShutdown();
        DynOS_Tex_ModShutdown();
    }
}

void DynOS_Mod_Shutdown() {
    sDynosModShutdown = true;
}
