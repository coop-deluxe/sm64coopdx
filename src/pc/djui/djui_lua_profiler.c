#include "djui_lua_profiler.h"

#include "djui.h"
#include "pc/pc_main.h"
#include "pc/mods/mod.h"
#include "pc/mods/mods.h"

#define MAX_PROFILED_MODS 16
#define REFRESH_RATE 30

struct DjuiPrfCounter {
    f64 start;
    f64 end;
    f64 sum;
    f64 display;
};

struct DjuiPrfEntry {
    struct DjuiText *name;
    struct DjuiText *timing;
    struct DjuiPrfCounter counter;
};

struct DjuiPrfDisplay {
    struct DjuiPrfEntry entries[MAX_PROFILED_MODS];
    struct DjuiBase base;
};

static struct DjuiPrfDisplay *sPrfDisplay = NULL;
static u8 sPrfDisplayCount = 0;

void lua_profiler_start_counter(UNUSED struct Mod *mod) {
    if (!configLuaProfiler || sPrfDisplay == NULL) { return; }

#ifndef WAPI_DUMMY
    for (s32 i = 0; i != MIN(MAX_PROFILED_MODS, gActiveMods.entryCount); ++i) {
        if (gActiveMods.entries[i] == mod) {
            f64 freq = SDL_GetPerformanceFrequency();
            f64 curr = SDL_GetPerformanceCounter();
            sPrfDisplay->entries[i].counter.start = curr / freq;
            return;
        }
    }
#endif
}

void lua_profiler_stop_counter(UNUSED struct Mod *mod) {
    if (!configLuaProfiler || sPrfDisplay == NULL) { return; }

#ifndef WAPI_DUMMY
    for (s32 i = 0; i != MIN(MAX_PROFILED_MODS, gActiveMods.entryCount); ++i) {
        if (gActiveMods.entries[i] == mod) {
            f64 freq = SDL_GetPerformanceFrequency();
            f64 curr = SDL_GetPerformanceCounter();

            struct DjuiPrfCounter *counter = &sPrfDisplay->entries[i].counter;
            counter->end = curr / freq;
            counter->sum += counter->end - counter->start;
            return;
        }
    }
#endif
}

void djui_lua_profiler_initialize_entry(struct DjuiBase *base, struct DjuiPrfEntry *entry, f64 offset) {
    struct DjuiText *name = djui_text_create(base, "");
    djui_text_set_alignment(name, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    djui_base_set_size_type(&name->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&name->base, 1.0f, name->fontScale * 2);
    djui_base_set_location(&name->base, 0, -name->fontScale / 3.0f + offset);
    djui_base_set_color(&name->base, 255, 255, 255, 240);

    struct DjuiText *timing = djui_text_create(base, "");
    djui_text_set_alignment(timing, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
    djui_base_set_size_type(&timing->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&timing->base, 1.0f, timing->fontScale * 2);
    djui_base_set_location(&timing->base, 0, -timing->fontScale / 3.0f + offset);
    djui_base_set_color(&timing->base, 255, 255, 255, 240);

    entry->name = name;
    entry->timing = timing;
}

void djui_lua_profiler_update(void) {
    if (!configLuaProfiler || sPrfDisplay == NULL) { return; }

    if (sPrfDisplayCount != gActiveMods.entryCount) {
        for (s32 i = 0; i < MAX(sPrfDisplayCount, gActiveMods.entryCount); i++) {
            struct DjuiPrfEntry *entry = &sPrfDisplay->entries[i];
            if (i >= sPrfDisplayCount) {
                djui_lua_profiler_initialize_entry(&sPrfDisplay->base, entry, 4.0 + (i * 22.0));
            }
            if (i >= gActiveMods.entryCount) {
                djui_base_destroy(&entry->name->base);
                djui_base_destroy(&entry->timing->base);
                entry->name = NULL;
                entry->timing = NULL;
            }
        }
        sPrfDisplayCount = gActiveMods.entryCount;
    }

    // Draw the counters.
    for (s32 i = 0; i < MIN(MAX_PROFILED_MODS, gActiveMods.entryCount); i++) {
        struct DjuiPrfEntry *entry = &sPrfDisplay->entries[i];
        struct DjuiPrfCounter *counter = &entry->counter;

        if (gGlobalTimer % REFRESH_RATE == 0) {
            counter->display = counter->sum / (f64) REFRESH_RATE;
            counter->sum = 0;
        }

        char name[256];
        memset(name, 0, 256);
        const char *modName = gActiveMods.entries[i]->relativePath;
        memcpy(name, modName, MIN(16, strlen(modName) - (gActiveMods.entries[i]->isDirectory ? 0 : 4)));
        for (s32 j = 0; j != 16; ++j) {
            char c = name[j];
            if (c >= 'a' && c <= 'z') c -= ('a' - 'A');
            if ((c < '0' || c > '9') && (c < 'A' || c > 'Z')) c = ' ';
            name[j] = c;
        }
        djui_text_set_text(entry->name, name);

        // The timing is in microseconds.
        s32 counterMs = (s32)(counter->display * 1000000.0);
        char timing[32];
        snprintf(timing, 32, "%05d", counterMs);
        djui_text_set_text(entry->timing, timing);
    }
}

void djui_lua_profiler_render(void) {
    if (!configLuaProfiler || sPrfDisplay == NULL) { return; }

    djui_rect_render(&sPrfDisplay->base);
    djui_base_render(&sPrfDisplay->base);
}

void djui_lua_profiler_on_destroy(UNUSED struct DjuiBase* base) {
    free(sPrfDisplay);
}

void djui_lua_profiler_create(void) {
    struct DjuiPrfDisplay *prfDisplay = calloc(1, sizeof(struct DjuiPrfDisplay));
    struct DjuiBase *base = &prfDisplay->base;
    djui_base_init(NULL, base, NULL, djui_lua_profiler_on_destroy);
    djui_base_set_size(base, 290.0f, MAX_PROFILED_MODS * 26.0f);
    djui_base_set_color(base, 0, 0, 0, 240);
    djui_base_set_border_color(base, 0, 0, 0, 200);
    djui_base_set_border_width(base, 4);
    djui_base_set_padding(base, 4, 4, 4, 4);
    djui_base_set_location(base, 0, 300.0f);

    sPrfDisplay = prfDisplay;
}

void djui_lua_profiler_destroy(void) {
    if (sPrfDisplay) {
        djui_base_destroy(&sPrfDisplay->base);
    }
}