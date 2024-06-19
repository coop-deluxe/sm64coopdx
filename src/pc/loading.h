#ifndef LOADING_HEADER
#define LOADING_HEADER

#include <pthread.h>

#include "cliopts.h"

struct LoadingSegment {
    char str[256];
    f32 percentage;
};

extern struct LoadingSegment gCurrLoadingSegment;

extern bool gIsThreaded;

#if !defined(WAPI_DXGI) && !defined(WAPI_DUMMY)
#define LOADING_SCREEN_SUPPORTED
#endif

#ifdef LOADING_SCREEN_SUPPORTED
#define LOADING_SCREEN_MUTEX(...) if (!gCLIOpts.hideLoadingScreen && gIsThreaded) { \
    pthread_mutex_lock(&gLoadingThreadMutex); \
    __VA_ARGS__; \
    pthread_mutex_unlock(&gLoadingThreadMutex); \
}
#else
#define LOADING_SCREEN_MUTEX(...)
#endif

extern pthread_t gLoadingThreadId;
extern pthread_mutex_t gLoadingThreadMutex;

extern bool gIsThreaded;

void loading_screen_set_segment_text(const char *text);
void render_loading_screen(void);
void render_rom_setup_screen(void);

#endif
