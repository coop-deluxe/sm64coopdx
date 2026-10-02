#include "splash_screen.h"

#include "pc/djui/djui.h"
#include "pc_main.h"

extern ALIGNED8 u8 texture_coopdx_logo[];

struct SplashScreen {
    struct DjuiBase base;
    struct DjuiText *splashText;
    struct DjuiImage *splashImage;
};

static struct SplashScreen *sSplashScreen = NULL;

static void splash_screen_produce_frame_callback(void) {
    if (sSplashScreen) { djui_base_render(&sSplashScreen->base); }
}

static void splash_screen_produce_one_frame(void) {
    produce_one_dummy_frame(splash_screen_produce_frame_callback, 0x00, 0x00, 0x00);
}

static bool splash_screen_on_render(struct DjuiBase *base) {
    u32 windowWidth, windowHeight;
    gfx_get_dimensions(&windowWidth, &windowHeight);
    f32 scale = djui_gfx_get_scale();
    windowWidth /= scale;
    windowHeight /= scale;

    // fill the window
    djui_base_set_size(base, windowWidth, windowHeight);

    djui_base_compute(base);

    return true;
}

static void splash_screen_destroy(struct DjuiBase *base) {
    struct SplashScreen *splashScreen = (struct SplashScreen *)base;
    free(splashScreen);
    sSplashScreen = NULL;
}

static void init_splash_screen(void) {
    struct SplashScreen *splashScreen = calloc(1, sizeof(struct SplashScreen));
    struct DjuiBase *base = &splashScreen->base;

    djui_base_init(NULL, base, splash_screen_on_render, splash_screen_destroy);

    // splash text (easter egg)
    if (configExCoopTheme) {
        struct DjuiText *splashDjuiText = djui_text_create(base, "\\#ff0800\\SM\\#1be700\\64\\#00b3ff\\EX\n\\#ffef00\\COOP");
        djui_text_set_font(splashDjuiText, gDjuiFonts[1]);
        djui_text_set_font_scale(splashDjuiText, gDjuiFonts[1]->defaultFontScale);
        djui_text_set_alignment(splashDjuiText, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&splashDjuiText->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&splashDjuiText->base, 1.0f, 1.0f);
        djui_base_set_location(&splashDjuiText->base, 0, -100);

        splashScreen->splashText = splashDjuiText;
    } else {
        // splash image
        struct DjuiImage *splashImage = djui_image_create(base, texture_coopdx_logo, 2048, 1024, G_IM_FMT_RGBA, G_IM_SIZ_32b);
        djui_base_set_alignment(&splashImage->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size(&splashImage->base, 512, 256);
        djui_base_set_location(&splashImage->base, 0, -100);

        splashScreen->splashImage = splashImage;
    }

    sSplashScreen = splashScreen;
}

void render_splash_screen(void) {
    if (!sSplashScreen) { init_splash_screen(); }

    gfx_wm_main_loop(splash_screen_produce_one_frame);
}
