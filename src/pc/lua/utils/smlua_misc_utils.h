#ifndef SMLUA_MISC_UTILS_H
#define SMLUA_MISC_UTILS_H

u32 get_network_area_timer(void);

s32* get_temp_s32_pointer(s32 initialValue);
s32 deref_s32_pointer(s32* pointer);

void hud_hide(void);
void hud_show(void);

bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct);
bool warp_restart_level(void);
bool warp_exit_level(s32 aDelay);
bool warp_to_castle(s32 aLevel);

u32 allocate_mario_action(u32 actFlags);

f32 get_hand_foot_pos_x(struct MarioState* m, u8 index);
f32 get_hand_foot_pos_y(struct MarioState* m, u8 index);
f32 get_hand_foot_pos_z(struct MarioState* m, u8 index);

s16 get_current_save_file_num(void);

LevelScript* smlua_level_util_get(const char* name);

f32 get_environment_region(u8 index);
void set_environment_region(u8 index, s32 value);

#endif
