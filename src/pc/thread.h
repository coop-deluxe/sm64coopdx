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
    INVALID = 0,
    STOPPED = 1,
    RUNNING = 2
};

struct ThreadHandle {
    pthread_t thread;
    pthread_mutex_t mutex;
    enum ThreadState state;
    bool mutexInited;
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

#endif // THREADING_H
