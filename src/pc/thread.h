#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>

#include "cliopts.h"
#include "types.h"

// Macros
#define MUTEX_LOCK(handle) if (handle.state != INVALID) { lock_mutex(&handle); }
#define MUTEX_UNLOCK(handle) if (handle.state != INVALID) { unlock_mutex(&handle); }

// Types
enum ThreadState : uint8_t {
    INVALID = 0,
    STOPPED = 1,
    IDLE = 2,
    RUNNING = 4
};

struct ThreadHandle {
    pthread_t thread;
    pthread_mutex_t mutex;
    enum ThreadState state;
};

// Functions
//// Thread Handle
int init_thread_handle(struct ThreadHandle *handle, void *(*entry)(void *), void *arg, void *sp, size_t sp_size);
void cleanup_thread_handle(struct ThreadHandle *handle);

//// Thread
int init_thread(struct ThreadHandle *handle, void *(*entry)(void *), void *arg, void *sp, size_t sp_size);
void start_thread(struct ThreadHandle *handle);
void detach_thread(struct ThreadHandle *handle);
void exit_thread();
int stop_thread(struct ThreadHandle *handle);

//// Mutex
int init_mutex(struct ThreadHandle *handle);
int destroy_mutex(struct ThreadHandle *handle);
void lock_mutex(struct ThreadHandle *handle);
void unlock_mutex(struct ThreadHandle *handle);

#endif // THREADING_H
