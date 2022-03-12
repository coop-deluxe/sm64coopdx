#ifdef COOP
#ifndef DYNOS_COOP_C_H
#define DYNOS_COOP_C_H
#ifndef __cplusplus

bool dynos_warp_to_level(s32 aLevel, s32 aArea, s32 aAct);
bool dynos_warp_restart_level(void);
bool dynos_warp_exit_level(s32 aDelay);
bool dynos_warp_to_castle(s32 aLevel);

int dynos_packs_get_count(void);
const char* dynos_packs_get(s32 index);
bool dynos_packs_get_enabled(s32 index);
void dynos_packs_set_enabled(s32 index, bool value);

#endif
#endif
#endif
