#ifndef RUMBLE_INIT_H
#define RUMBLE_INIT_H

// this file is very scarcely documented

extern s32 gRumblePakTimer;

void init_rumble_pak_scheduler_queue(void);
void block_until_rumble_pak_free(void);
void release_rumble_pak_control(void);
/* |description|Queues rumble data with `time` and `level`|descriptionEnd| */
void queue_rumble_data(s16 time, s16 level);
/* |description|Queues rumble data for object with `time` and `level`, factoring in its distance from Mario|descriptionEnd| */
void queue_rumble_data_object(struct Object* object, s16 time, s16 level);
/* |description|Queues rumble data with `time` and `level` only if `m` is the local Mario|descriptionEnd| */
void queue_rumble_data_mario(struct MarioState* m, s16 time, s16 level);
/* |description|Queues rumble `decay`|descriptionEnd| */
void queue_rumble_decay(s16 decay);
/* |description|Checks if rumble is finished and there is no rumble queued|descriptionEnd| */
u8 is_rumble_finished_and_queue_empty(void);
/* |description|Resets rumble timers only if `m` is the local Mario|descriptionEnd| */
void reset_rumble_timers(struct MarioState* m);
/* |description|Resets rumble timers and sets vibrate based on `level`|descriptionEnd| */
void reset_rumble_timers_vibrate(struct MarioState* m, s32 level);
/* |description|Queues rumble data for submerged actions|descriptionEnd| */
void queue_rumble_submerged(void);
/* |description|Cancels all currently queued rumble data|descriptionEnd| */
void cancel_rumble(void);
void create_thread_6(void);
void rumble_thread_update_vi(void);
void thread6_rumble_loop(UNUSED void *a0);

#endif // RUMBLE_INIT_H
