#include "gfx_dimensions.h"
#include "game/segment2.h"

#include "djui/djui.h"
#include "pc/djui/djui_unicode.h"

#include "controller/controller_keyboard.h"

#include "pc_main.h"
#include "loading.h"
#include "pc/utils/misc.h"

struct LoadingSegment gCurrLoadingSegment = { "", 0 };

struct LoadingScreen {
    struct DjuiBase base;
    struct DjuiText* splashText;
    struct DjuiText* loadingText;
    struct DjuiText* loadingDesc;
    struct DjuiProgressBar *loadingBar;
};

struct LoadingScreen* sLoading = NULL;
pthread_t gLoadingThreadId;
pthread_mutex_t gLoadingThreadMutex = PTHREAD_MUTEX_INITIALIZER;

bool gIsThreaded = false;

extern Vp D_8032CF00;
extern u8 gRenderingInterpolated;

static void loading_screen_produce_one_frame() {

    // Start frame
    gfx_start_frame();
    config_gfx_pool();
    init_render_image();
    create_dl_ortho_matrix();
    djui_gfx_displaylist_begin();

    // Fix scaling issues
    gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&D_8032CF00));
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, BORDER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BORDER_HEIGHT);

    // Clear screen
    create_dl_translation_matrix(MENU_MTX_PUSH, GFX_DIMENSIONS_FROM_LEFT_EDGE(0), 240.f, 0.f);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, (GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT) / 130.f, 3.f, 1.f);
    gDPSetEnvColor(gDisplayListHead++, 0x00, 0x00, 0x00, 0xFF);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    // Render loading screen elements
    if (sLoading) { djui_base_render(&sLoading->base); }

    // Render frame
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

    // Fill the screen
    djui_base_set_size(base, windowWidth, windowHeight);

    // Splash text
    djui_base_set_location(&sLoading->splashText->base, (windowWidth / 2) - 416, 0);

    {
        // Loading... text
        char* loadingStr = DLANG(LOADING_SCREEN, LOADING);
        char tmp[20] = "";
        switch ((u8) floor(clock_elapsed()) % 3) {
            case 0:  snprintf(tmp, 20, "%s...", loadingStr); break;
            case 1:  snprintf(tmp, 20, "%s.",   loadingStr); break;
            default: snprintf(tmp, 20, "%s..",  loadingStr); break;
        }
        djui_text_set_text(sLoading->loadingText, tmp);
        djui_base_set_visible(&sLoading->loadingText->base, sLoading->loadingText->base.y.value + 50 < sLoading->loadingDesc->base.y.value);
    }

    {
        // Loading text description
        char buffer[256] = "";
        if (strlen(gCurrLoadingSegment.str) > 0) {
            if (gCurrLoadingSegment.percentage > 0) {
                snprintf(buffer, 256, "%s... %d%%", gCurrLoadingSegment.str, (u8) floor(gCurrLoadingSegment.percentage * 100));
            } else {
                snprintf(buffer, 256, "%s...", gCurrLoadingSegment.str);
            }
        }
        djui_text_set_text(sLoading->loadingDesc, buffer);
        djui_base_set_location(&sLoading->loadingDesc->base, 0, windowHeight - 250);
    }

    // Loading bar
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

void render_loading_screen() {
    struct LoadingScreen* load = malloc(sizeof(struct LoadingScreen));
    struct DjuiBase* base = &load->base;

    djui_base_init(NULL, base, loading_screen_on_render, loading_screen_destroy);

    {
        // Splash text
        struct DjuiText* splashDjuiText = djui_text_create(base, "\\#ff0800\\SM\\#1be700\\64\\#00b3ff\\EX\\#ffef00\\COOP");
        djui_text_set_font(splashDjuiText, gDjuiFonts[1]);
        djui_text_set_font_scale(splashDjuiText, gDjuiFonts[1]->defaultFontScale * 4);
        djui_text_set_alignment(splashDjuiText, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_size(&splashDjuiText->base, 800, 800);

        load->splashText = splashDjuiText;
    }

    {
        // "Loading..." text
        struct DjuiText *text = djui_text_create(base, "");
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, 32 * 4);
        djui_base_set_color(&text->base, 200, 200, 200, 255);
        djui_base_set_location(&text->base, 0, 400);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_font(text, gDjuiFonts[0]);
        djui_text_set_font_scale(text, gDjuiFonts[0]->defaultFontScale * 2);

        load->loadingText = text;
    }

    {
        // Current loading stage text
        struct DjuiText *text = djui_text_create(base, "");
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, 32 * 4);
        djui_base_set_color(&text->base, 200, 200, 200, 255);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_text_set_font(text, gDjuiFonts[0]);
        djui_text_set_font_scale(text, gDjuiFonts[0]->defaultFontScale * 2);

        load->loadingDesc = text;
    }

    {
        // Loading bar
        struct DjuiProgressBar *progressBar = djui_progress_bar_create(base, &gCurrLoadingSegment.percentage, 0.0f, 1.0f, false);
        djui_base_set_visible(&progressBar->base, false);
        progressBar->base.width.value = 0.5;

        load->loadingBar = progressBar;
    }

    sLoading = load;

    // Loading screen loop
    while (!gGameInited) {
        WAPI.main_loop(loading_screen_produce_one_frame);
    }

    pthread_join(gLoadingThreadId, NULL);

    // Reset some things after rendering the loading screen
    reset_djui();
    alloc_display_list_reset();
    gDisplayListHead = NULL;
    djui_init();
    djui_unicode_init();
    rendering_init();
    configWindow.settings_changed = true;
}
