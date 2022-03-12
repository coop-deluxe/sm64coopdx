#include "types.h"

#include "data/dynos_coop.c.h"
#include "game/hud.h"
#include "pc/lua/smlua.h"
#include "smlua_misc_utils.h"
#include "pc/debuglog.h"

u32 get_network_area_timer(void) {
    return gNetworkAreaTimer;
}

void hud_hide(void) {
    gOverrideHideHud = 1;
}

void hud_show(void) {
    gOverrideHideHud = 0;
}

bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct) {
    return dynos_warp_to_level(aLevel, aArea, aAct);
}

bool warp_restart_level(void) {
    return dynos_warp_restart_level();
}

bool warp_exit_level(s32 aDelay) {
    return dynos_warp_exit_level(aDelay);
}

bool warp_to_castle(s32 aLevel) {
    return dynos_warp_to_castle(aLevel);
}
