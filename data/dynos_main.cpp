#include "dynos.cpp.h"
extern "C" {
#include "sm64.h"
#include "level_commands.h"
#include "game/level_update.h"
#include "game/options_menu.h"
#include "game/object_list_processor.h"
extern s16 gMenuMode;
extern s8 gDialogBoxState;
#ifdef OMM_DEFINES_H
extern void omm_opt_init();
#endif
}

//
// Main Menu
//

void DynOS_ReturnToMainMenu() {
    optmenu_toggle();
    level_set_transition(0, NULL);
    gDialogBoxState = 0;
    gMenuMode = -1;
    fade_into_special_warp(-2, 0);
}

//
// Init
//

DYNOS_AT_STARTUP void DynOS_Init() {
#ifdef OMM_DEFINES_H
    omm_opt_init();
#endif
    DynOS_Opt_Init();
}

//
// Update
//

static bool sDynosIsLevelEntry = false;
void DynOS_UpdateOpt(void *aPad) {
    if (sDynosIsLevelEntry) {
        DynOS_Warp_SetParam(gCurrLevelNum, -1);
        sDynosIsLevelEntry = false;
    }
    DynOS_Opt_Update((OSContPad *) aPad);
    gPrevFrameObjectCount = 0;
}

void *DynOS_UpdateCmd(void *aCmd) {
    static const uintptr_t sCmdLevelEntry[] = { CALL(0, lvl_init_or_update) };
    sDynosIsLevelEntry |= (memcmp(aCmd, sCmdLevelEntry, sizeof(sCmdLevelEntry)) == 0);
    return DynOS_Warp_Update(aCmd, sDynosIsLevelEntry);
}

void DynOS_UpdateGfx() {
    DynOS_Gfx_Update();
}

bool DynOS_IsTransitionActive() {
    return gWarpTransition.isActive;
}
