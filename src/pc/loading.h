#ifndef LOADING_HEADER
#define LOADING_HEADER

#include <pthread.h>

struct LoadingSegment {
    char str[256];
    f32 percentage;
};

extern struct LoadingSegment gCurrLoadingSegment;

extern bool gIsThreaded;

#define REFRESH_MUTEX(...) \
if (gIsThreaded) { \
    pthread_mutex_lock(&gLoadingThreadMutex); \
    __VA_ARGS__; \
    pthread_mutex_unlock(&gLoadingThreadMutex); \
} \

extern pthread_t gLoadingThreadId;
extern pthread_mutex_t gLoadingThreadMutex;

void render_loading_screen(void);

#endif
