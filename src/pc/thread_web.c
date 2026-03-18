#ifdef TARGET_WEB

#include <string.h>
#include "thread.h"

int init_thread_handle(struct ThreadHandle *handle, void *(*entry)(void *), void *arg, void *sp, size_t sp_size) {
    init_mutex(handle);
    entry(arg);
    return 0;
}

void cleanup_thread_handle(struct ThreadHandle *handle) {
    memset(handle, 0, sizeof(struct ThreadHandle));
}

int init_thread(struct ThreadHandle *handle, void *(*entry)(void *), void *arg, void *sp, size_t sp_size) {
    entry(arg);
    handle->state = RUNNING;
    return 0;
}

int join_thread(struct ThreadHandle *handle) {
    handle->state = STOPPED;
    return 0;
}

int detach_thread(struct ThreadHandle *handle) {
    handle->state = STOPPED;
    return 0;
}

void exit_thread() {
}

int stop_thread(struct ThreadHandle *handle) {
    handle->state = STOPPED;
    return 0;
}

int init_mutex(struct ThreadHandle *handle) {
    return 0;
}

int destroy_mutex(struct ThreadHandle *handle) {
    return 0;
}

int lock_mutex(struct ThreadHandle *handle) {
    return 0;
}

int trylock_mutex(struct ThreadHandle *handle) {
    return 0;
}

int unlock_mutex(struct ThreadHandle *handle) {
    return 0;
}

#endif // TARGET_WEB
