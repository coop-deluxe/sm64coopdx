#include "thread.h"

#include <assert.h>
#include <string.h>

int init_thread_handle(struct ThreadHandle *handle, void *(*entry)(void *), void *arg, void *sp, size_t sp_size) {
    int err1 = init_mutex(handle);
    int err2 = init_thread(handle, entry, arg, sp, sp_size);

    return (err1 != 0 || err2 != 0);
}

void free_thread_handle(struct ThreadHandle *handle) {
    assert(handle != NULL);

    //int err = stop_thread(handle);
    //assert(err == 0);

    int err = destroy_mutex(handle);
    assert(err == 0);

    // Reset the memory of the thread handle, We no longer need the thread or mutex.
    memset((void *)handle, 0, sizeof(struct ThreadHandle));
}

// Optimally just call init_thread_handle instead.
int init_thread(struct ThreadHandle *handle, void *(*entry)(void *), void *arg, void *sp, size_t sp_size) {
    assert(handle != NULL);

    // Setup our thread and create it.
    pthread_attr_t thattr = { 0 };

    // Initialize default attributes for a new thread.
    int err = pthread_attr_init(&thattr);
    assert(err == 0);

    // By default, We want the thread to be joinable.
    err = pthread_attr_setdetachstate(&thattr, PTHREAD_CREATE_JOINABLE);
    assert(err == 0);

    // Set the stack if we have one specified, Otherwise we don't care.
    // In truth, This honestly shouldn't be used on PC. But if somebody wants
    // a really managed stack? This is possible.
    if (sp != NULL && sp_size > 0) {
        err = pthread_attr_setstack(&thattr, sp, sp_size);
        assert(err == 0);
    }

    // Create our thread.
    int ret = pthread_create(&handle->thread, &thattr, entry, arg);

    // Destroy the thread attributes, They are no longer needed
    err = pthread_attr_destroy(&thattr);
    assert(err == 0);

    handle->state = RUNNING;

    return ret;
}

int join_thread(struct ThreadHandle *handle) {
    assert(handle != NULL);

    handle->state = STOPPED;

    // Join the thread and wait for it to finish.
    return pthread_join(handle->thread, NULL);
}

int detach_thread(struct ThreadHandle *handle) {
    assert(handle != NULL);

    handle->state = STOPPED;

    // Detach the thread, it will no longer be joinable afterwards.
    return pthread_detach(handle->thread);
}

// Call from inside the thread you wish to
// terminate.
void exit_thread() {
    pthread_exit(NULL);
}

int stop_thread(struct ThreadHandle *handle) {
    assert(handle != NULL);

    handle->state = STOPPED;

    // Stop and or cancel the execution of the thread in question.
    return pthread_cancel(handle->thread);
}

// Optimally just call init_thread_handle instead.
int init_mutex(struct ThreadHandle *handle) {
    assert(handle != NULL);

    pthread_mutexattr_t mtattr;

    int err = pthread_mutexattr_init(&mtattr);
    assert(err == 0);

    err = pthread_mutexattr_settype(&mtattr, PTHREAD_MUTEX_ERRORCHECK);
    assert(err == 0);

    int ret = pthread_mutex_init(&handle->mutex, &mtattr);

    err = pthread_mutexattr_destroy(&mtattr);
    assert(err == 0);

    return ret;
}

int destroy_mutex(struct ThreadHandle *handle) {
    assert(handle != NULL);

    return pthread_mutex_destroy(&handle->mutex);
}

int lock_mutex(struct ThreadHandle *handle) {
    assert(handle != NULL);

    return pthread_mutex_lock(&handle->mutex);
}

int trylock_mutex(struct ThreadHandle *handle) {
    assert(handle != NULL);

    return pthread_mutex_trylock(&handle->mutex);
}

int unlock_mutex(struct ThreadHandle *handle) {
    assert(handle != NULL);

    return pthread_mutex_unlock(&handle->mutex);
}