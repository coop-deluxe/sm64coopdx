#include "gfx_dimensions.h"
#include "game/segment2.h"

#include "djui/djui.h"
#include "pc/djui/djui_unicode.h"

#include "pc_main.h"
#include "loading.h"
#include "pc/utils/misc.h"
#include "pc/cliopts.h"

extern ALIGNED8 u8 texture_coopdx_logo[];

struct LoadingSegment gCurrLoadingSegment = { "", 0 };

struct LoadingScreen {
    struct DjuiBase base;
    struct DjuiImage* splashImage;
    struct DjuiText* loadingDesc;
    struct DjuiProgressBar *loadingBar;
};

struct LoadingScreen* sLoading = NULL;
pthread_t gLoadingThreadId;
pthread_mutex_t gLoadingThreadMutex = PTHREAD_MUTEX_INITIALIZER;

bool gIsThreaded = false;

extern Vp D_8032CF00;

static void loading_screen_produce_one_frame(void) {
    // start frame
    gfx_start_frame();
    config_gfx_pool();
    init_render_image();
    create_dl_ortho_matrix();
    djui_gfx_displaylist_begin();

    // fix scaling issues
    gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&D_8032CF00));
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, BORDER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BORDER_HEIGHT);

    // clear screen
    create_dl_translation_matrix(MENU_MTX_PUSH, GFX_DIMENSIONS_FROM_LEFT_EDGE(0), 240.f, 0.f);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, (GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT) / 130.f, 3.f, 1.f);
    gDPSetEnvColor(gDisplayListHead++, 0x00, 0x00, 0x00, 0xFF);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    // render loading screen elements
    if (sLoading && !gCLIOpts.hideLoadingScreen) { djui_base_render(&sLoading->base); }

    // render frame
    djui_gfx_displaylist_end();
    end_master_display_list();
    alloc_display_list(0);
    gfx_run((Gfx*) gGfxSPTask->task.t.data_ptr); // send_display_list
    display_and_vsync();
    gfx_end_frame();
}

static bool loading_screen_on_render(struct DjuiBase* base) {
    pthread_mutex_lock(&gLoadingThreadMutex);

    u32 windowWidth, windowHeight;
    WAPI.get_dimensions(&windowWidth, &windowHeight);
    f32 scale = djui_gfx_get_scale();
    windowWidth /= scale;
    windowHeight /= scale;

    // fill the screen
    djui_base_set_size(base, windowWidth, windowHeight);

    {
        // loading text description
        char buffer[256] = "";
        u32 length = strlen(gCurrLoadingSegment.str);
        if (length > 0) {
            if (gCurrLoadingSegment.percentage > 0) {
                snprintf(buffer, 256, "%s\n\\#c8c8c8\\%d%%", gCurrLoadingSegment.str, (u8)floor(gCurrLoadingSegment.percentage * 100));
            } else {
                snprintf(buffer, 256, "%s...", gCurrLoadingSegment.str);
            }

            sys_swap_backslashes(buffer);
        }
        djui_text_set_text(sLoading->loadingDesc, buffer);
        djui_base_set_location(&sLoading->loadingDesc->base, 0, windowHeight - 250);
    }

    // loading bar
    djui_base_set_location(&sLoading->loadingBar->base, windowWidth / 4, windowHeight - 100);
    djui_base_set_visible(&sLoading->loadingBar->base, gCurrLoadingSegment.percentage > 0 && strlen(gCurrLoadingSegment.str) > 0);

    djui_base_compute(base);

    pthread_mutex_unlock(&gLoadingThreadMutex);

    return true;
}

static void loading_screen_destroy(struct DjuiBase* base) {
    struct LoadingScreen* load = (struct LoadingScreen*)base;
    free(load);
    sLoading = NULL;
}

void render_loading_screen(void) {
    struct LoadingScreen* load = malloc(sizeof(struct LoadingScreen));
    struct DjuiBase* base = &load->base;

    djui_base_init(NULL, base, loading_screen_on_render, loading_screen_destroy);

    {
        // splash image
        struct DjuiImage* splashImage = djui_image_create(base, texture_coopdx_logo, 2048, 1024, 32);
        djui_base_set_size(&splashImage->base, 740.0f, 364.0f);
        djui_base_set_alignment(&splashImage->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_location(&splashImage->base, 0, -100);

        load->splashImage = splashImage;
    }

    {
        // current loading stage text
        struct DjuiText *text = djui_text_create(base, "");
        djui_base_set_location_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_location(&text->base, 0, 0);

        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, gDjuiFonts[0]->defaultFontScale * 4.0f);
        djui_base_set_color(&text->base, 200, 200, 200, 255);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_text_set_font(text, gDjuiFonts[0]);
        djui_text_set_font_scale(text, gDjuiFonts[0]->defaultFontScale * 1.5f);

        load->loadingDesc = text;
    }

    {
        // loading bar
        struct DjuiProgressBar *progressBar = djui_progress_bar_create(base, &gCurrLoadingSegment.percentage, 0.0f, 1.0f, false);
        djui_base_set_location_type(&progressBar->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_location(&progressBar->base, 0, 0);
        djui_base_set_visible(&progressBar->base, false);
        progressBar->base.width.value = 0.5;

        load->loadingBar = progressBar;
    }

    sLoading = load;

    // loading screen loop
    while (!gGameInited) {
        WAPI.main_loop(loading_screen_produce_one_frame);
    }

    pthread_join(gLoadingThreadId, NULL);

    // reset some things after rendering the loading screen
    reset_djui();
    alloc_display_list_reset();
    gDisplayListHead = NULL;
    djui_init();
    djui_unicode_init();
    rendering_init();
    configWindow.settings_changed = true;
}
