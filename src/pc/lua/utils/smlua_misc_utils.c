#include "types.h"

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

