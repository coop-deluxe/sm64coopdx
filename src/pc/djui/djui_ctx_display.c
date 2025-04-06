#include "djui_ctx_display.h"

#include "djui.h"
#include "pc/pc_main.h"
#include "pc/debug_context.h"

#ifdef DEVELOPMENT

static char* sDebugContextNames[] = {
    "NONE",
    "TOTAL",
    "NET",
    "INTERP",
    "GAME",
    "SMLUA",
    "AUDIO",
    "RENDER",
    "LEVEL",
    "HOOK",
    "LIGHTING",
    "OTHER",
    "MAX",
};

#endif

struct DjuiCtxEntry {
    struct DjuiText *name;
    struct DjuiText *timing;
};

struct DjuiCtxDisplay {
    struct DjuiCtxEntry topEntry;
    struct DjuiCtxEntry entries[CTX_MAX];
    struct DjuiBase base;
};


struct DjuiCtxDisplay *sCtxDisplay = NULL;

void djui_ctx_display_update(void) {
#ifdef DEVELOPMENT
    if (!configCtxProfiler || sCtxDisplay == NULL) { return; }

    // Time we have for a indivdual frame. If we exceed it. We are in the red.
    f64 frameTime = 1.0 / 30.0;
    s32 frameTimeMs = (s32)(frameTime * 1000000.0);

    struct DjuiCtxEntry *topEntry = &sCtxDisplay->topEntry;

    // If we've exceeded our available frame time. Make the top entry timing red - For dramatic effect.
    // Otherwise. It's green!
    if (debug_context_get_time(CTX_TOTAL) > frameTime) {
        djui_base_set_color(&topEntry->timing->base, 255, 69, 0, 240);
    } else {
        djui_base_set_color(&topEntry->timing->base, 124, 252, 0, 240);
    }

    djui_text_set_text(topEntry->name, "FRAME");
    char timing[32];
    snprintf(timing, 32, "%05d", frameTimeMs);
    djui_text_set_text(topEntry->timing, timing);

    // Draw the counters.
    for (s32 i = CTX_TOTAL; i < CTX_MAX; i++) {
        struct DjuiCtxEntry *entry = &sCtxDisplay->entries[i];

        const char *name = sDebugContextNames[i];
        djui_text_set_text(entry->name, name);

        // The timing is in microseconds.
        s32 counterMs = (s32)(debug_context_get_time(i) * 1000000.0);
        char timing[32];
        snprintf(timing, 32, "%05d", counterMs);
        djui_text_set_text(entry->timing, timing);
    }
#endif
}

void djui_ctx_display_render(void) {
#ifdef DEVELOPMENT
    if (!configCtxProfiler || sCtxDisplay == NULL) { return; }

    djui_rect_render(&sCtxDisplay->base);
    djui_base_render(&sCtxDisplay->base);
#endif
}

void djui_ctx_display_on_destroy(UNUSED struct DjuiBase* base) {
    free(sCtxDisplay);
}

void djui_ctx_display_initialize_entry(struct DjuiBase *base, struct DjuiCtxEntry *entry, f64 offset) {
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

void djui_ctx_display_create(void) {
    struct DjuiCtxDisplay *ctxDisplay = calloc(1, sizeof(struct DjuiCtxDisplay));
    struct DjuiBase *base = &ctxDisplay->base;
    djui_base_init(NULL, base, NULL, djui_ctx_display_on_destroy);
    djui_base_set_size(base, 220.0f, 39.0f + ((CTX_MAX - 2) * 26.0f));
    djui_base_set_color(base, 0, 0, 0, 240);
    djui_base_set_border_color(base, 0, 0, 0, 200);
    djui_base_set_border_width(base, 4);
    djui_base_set_padding(base, 4, 4, 4, 4);
    djui_base_set_location(base, 0, 52.0f);

    {
        f64 offset = 4.0;

        djui_ctx_display_initialize_entry(base, &ctxDisplay->topEntry, offset);
        offset += 35.0;

        for (s32 i = CTX_TOTAL; i < CTX_MAX; i++) {
            djui_ctx_display_initialize_entry(base, &ctxDisplay->entries[i], offset);
            offset += 22.0;
        }
    }

    sCtxDisplay = ctxDisplay;
}

void djui_ctx_display_destroy(void) {
    if (sCtxDisplay) {
        djui_base_destroy(&sCtxDisplay->base);
    }
}