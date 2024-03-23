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

extern bool gIsThreaded;

void loading_screen_set_segment_text(const char *text);
void render_loading_screen();
void render_rom_setup_screen();

#endif
