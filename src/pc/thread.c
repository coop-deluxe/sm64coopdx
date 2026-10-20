#include "thread.h"

#include <assert.h>
#include <string.h>
#include "pc/debuglog.h"

#define MAX_QUEUED_THREAD_CALLBACKS 32

static void (*sThreadCallbacks[MAX_QUEUED_THREAD_CALLBACKS])(void) = { 0 };
static u32 sThreadCallbackCount = 0;

static pthread_mutex_t sThreadCallbackMutex = PTHREAD_MUTEX_INITIALIZER;

int init_thread_handle(struct ThreadHandle *handle, void *(*entry)(void *), void *arg, void *sp, size_t sp_size) {
    int err1 = init_mutex(handle);
    if (err1 != 0) {
        return err1;
    }

    int err2 = init_thread(handle, entry, arg, sp, sp_size);
    if (err2 != 0) {
        destroy_mutex(handle);
        return err2;
    }

    return 0;
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

    if (ret != 0) { return ret; }

    handle->state = THREAD_STATE_RUNNING;

    return ret;
}

int join_thread(struct ThreadHandle *handle) {
    assert(handle != NULL);

    if (handle->state != THREAD_STATE_RUNNING) {
        return 0;
    }

    // Join the thread and wait for it to finish.
    int ret = pthread_join(handle->thread, NULL);
    if (ret == 0) {
        handle->state = THREAD_STATE_STOPPED;
    } else {
        LOG_ERROR("Failed to join thread, error: %d", ret);
    }

    return ret;
}

int detach_thread(struct ThreadHandle *handle) {
    assert(handle != NULL);

    if (handle->state != THREAD_STATE_RUNNING) {
        return 0;
    }

    // Detach the thread, it will no longer be joinable afterwards.
    int ret = pthread_detach(handle->thread);
    if (ret == 0) {
        handle->state = THREAD_STATE_STOPPED;
    }

    return ret;
}

// Call from inside the thread you wish to
// terminate.
void exit_thread() {
    pthread_exit(NULL);
}

int stop_thread(struct ThreadHandle *handle) {
    assert(handle != NULL);

    if (handle->state != THREAD_STATE_RUNNING) {
        return 0;
    }

    // Stop and or cancel the execution of the thread in question.
    int ret = pthread_cancel(handle->thread);
    if (ret == 0) {
        handle->state = THREAD_STATE_STOPPED;
    }

    return ret;
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

    handle->mutexInited = (ret == 0);

    return ret;
}

int destroy_mutex(struct ThreadHandle *handle) {
    assert(handle != NULL);

    if (!handle->mutexInited) {
        return 0;
    }

    int ret = pthread_mutex_destroy(&handle->mutex);
    if (ret == 0) {
        handle->mutexInited = false;
    }

    return ret;
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

/**
 * Queues a thread callback for run
 * Uses the `callback` function pointer defined in `ThreadHandle`
 * All queued callbacks are ran at the start of the main loop in the main thread
 *
 * Returns `true` in the event the callback is added to the queue
 * Returns `false` in the event the queue is full or the callback is `NULL`
 */
bool queue_thread_callback_call(struct ThreadHandle *handle) {
    if (handle->callback == NULL) { return false; }

    pthread_mutex_lock(&sThreadCallbackMutex);
    if (sThreadCallbackCount >= MAX_QUEUED_THREAD_CALLBACKS) {
        pthread_mutex_unlock(&sThreadCallbackMutex);
        return false;
    }

    sThreadCallbacks[sThreadCallbackCount++] = handle->callback;
    pthread_mutex_unlock(&sThreadCallbackMutex);

    return true;
}

/**
 * Calls queued thread callbacks from `queue_thread_callback_call`
 * The callback count is reset to 0 on completion
 */
void call_queued_thread_callbacks(void) {
    pthread_mutex_lock(&sThreadCallbackMutex);

    for (u32 i = 0; i < sThreadCallbackCount; i++) {
        sThreadCallbacks[i]();
    }
    sThreadCallbackCount = 0;

    pthread_mutex_unlock(&sThreadCallbackMutex);
}
