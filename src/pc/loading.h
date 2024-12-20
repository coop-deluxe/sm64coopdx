#ifndef LOADING_HEADER
#define LOADING_HEADER

#if !defined(WAPI_DUMMY)
#define LOADING_SCREEN_SUPPORTED
#endif

#ifdef LOADING_SCREEN_SUPPORTED

#include "src/pc/thread.h"
#include "djui/djui_hud_utils.h"

struct LoadingSegment {
    char str[256];
    f32 percentage;
};

extern struct LoadingSegment gCurrLoadingSegment;

#define LOADING_SCREEN_MUTEX(...) \
    if (!gCLIOpts.hideLoadingScreen && gLoadingThread.state == RUNNING) { \
        pthread_mutex_lock(&gLoadingThread.mutex); \
        __VA_ARGS__; \
        pthread_mutex_unlock(&gLoadingThread.mutex); \
    }

extern struct ThreadHandle gLoadingThread;

void loading_screen_set_segment_text(const char* text);
void loading_screen_reset_progress_bar(void);
void render_loading_screen(void);
void loading_screen_reset(void);
void render_rom_setup_screen(void);

#else // LOADING_SCREEN_SUPPORTED

#define LOADING_SCREEN_MUTEX(...)

#endif // LOADING_SCREEN_SUPPORTED

#endif
