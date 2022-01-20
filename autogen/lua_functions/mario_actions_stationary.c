s32 check_common_idle_cancels(struct MarioState *m);
s32 check_common_hold_idle_cancels(struct MarioState *m);
void play_anim_sound(struct MarioState *m, u32 actionState, s32 animFrame, u32 sound);
void stopping_step(struct MarioState *m, s32 animID, u32 action);
s32 landing_step(struct MarioState *m, s32 arg1, u32 action);
s32 check_common_landing_cancels(struct MarioState *m, u32 action);
s32 check_common_stationary_cancels(struct MarioState *m);
s32 mario_execute_stationary_action(struct MarioState *m);
