#ifndef SMLUA_MISC_UTILS_H
#define SMLUA_MISC_UTILS_H

u32 get_network_area_timer(void);

void hud_hide(void);
void hud_show(void);

bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct);
bool warp_restart_level(void);
bool warp_exit_level(s32 aDelay);
bool warp_to_castle(s32 aLevel);

#endif
