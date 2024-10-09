#ifndef RUMBLE_INIT_H
#define RUMBLE_INIT_H

extern s32 gRumblePakTimer;

void init_rumble_pak_scheduler_queue(void);
void block_until_rumble_pak_free(void);
void release_rumble_pak_control(void);
void queue_rumble_data(s16 a0, s16 a1);
void queue_rumble_data_object(struct Object* object, s16 a0, s16 a1);
void queue_rumble_data_mario(struct MarioState* m, s16 a0, s16 a1);
void func_sh_8024C89C(s16 a0);
u8 is_rumble_finished_and_queue_empty(void);
void reset_rumble_timers(struct MarioState* m);
void reset_rumble_timers_2(struct MarioState* m, s32 a0);
void func_sh_8024CA04(void);
void cancel_rumble(void);
void create_thread_6(void);
void rumble_thread_update_vi(void);
void thread6_rumble_loop(void *a0);

#endif // RUMBLE_INIT_H
