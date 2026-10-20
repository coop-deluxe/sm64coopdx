#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>
#include <stdbool.h>

#include "cliopts.h"
#include "types.h"

// Macros
#define MUTEX_LOCK(handle) do { if ((handle).mutexInited) { lock_mutex(&(handle)); } } while (0)
#define MUTEX_UNLOCK(handle) do { if ((handle).mutexInited) { unlock_mutex(&(handle)); } } while (0)

// Types
enum ThreadState {
    THREAD_STATE_INVALID = 0,
    THREAD_STATE_STOPPED = 1,
    THREAD_STATE_RUNNING = 2
};

struct ThreadHandle {
    pthread_t thread;
    pthread_mutex_t mutex;
    enum ThreadState state;
    bool mutexInited;
    void (*callback)(void);
};

// Functions
//// Thread Handle
int init_thread_handle(struct ThreadHandle *handle, void *(*entry)(void *), void *arg, void *sp, size_t sp_size);
void free_thread_handle(struct ThreadHandle *handle);

//// Thread
int init_thread(struct ThreadHandle *handle, void *(*entry)(void *), void *arg, void *sp, size_t sp_size);
int join_thread(struct ThreadHandle *handle);
int detach_thread(struct ThreadHandle *handle);
void exit_thread();
int stop_thread(struct ThreadHandle *handle);

//// Mutex
int init_mutex(struct ThreadHandle *handle);
int destroy_mutex(struct ThreadHandle *handle);
int lock_mutex(struct ThreadHandle *handle);
int trylock_mutex(struct ThreadHandle *handle);
int unlock_mutex(struct ThreadHandle *handle);

//// Callbacks
bool queue_thread_callback_call(struct ThreadHandle *handle);
void call_queued_thread_callbacks(void);

#endif // THREADING_H
