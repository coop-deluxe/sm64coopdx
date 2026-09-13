#include "rom_setup.h"

#include <assert.h>

#include "djui/djui.h"
#include "pc/djui/djui_unicode.h"

#include "pc_main.h"
#include "pc/utils/misc.h"
#include "pc/cliopts.h"
#include "rom_checker.h"

#define MAX_ROM_SETUP_MESSAGE_LEN 256

extern ALIGNED8 u8 texture_coopdx_logo[];

struct RomSetupScreen {
    struct DjuiBase base;
    struct DjuiImage *splashImage;
    struct DjuiText *splashText;
    struct DjuiText *setupText;
    char message[MAX_ROM_SETUP_MESSAGE_LEN];
};

static struct RomSetupScreen* sRomhackSetupScreen = NULL;

void append_to_rom_setup_text(const char *message) {
    strncat(sRomhackSetupScreen->message, message, MAX_ROM_SETUP_MESSAGE_LEN - strlen(message) - 1);
}

static void romhack_setup_screen_produce_frame_callback(void) {
    if (sRomhackSetupScreen) { djui_base_render(&sRomhackSetupScreen->base); }
}

static void romhack_setup_screen_produce_one_frame(void) {
    produce_one_dummy_frame(romhack_setup_screen_produce_frame_callback, 0x00, 0x00, 0x00);
}

static bool rom_setup_screen_on_render(struct DjuiBase* base) {
    u32 windowWidth, windowHeight;
    gfx_get_dimensions(&windowWidth, &windowHeight);
    f32 scale = djui_gfx_get_scale();
    windowWidth /= scale;
    windowHeight /= scale;

    f32 setupTextY = windowHeight * 0.5f - sRomhackSetupScreen->setupText->base.height.value * 0.5f;

    // fill the screen
    djui_base_set_size(base, windowWidth, windowHeight);

    // splash logo
    if (configExCoopTheme) {
        djui_base_set_location(&sRomhackSetupScreen->splashText->base, 0, setupTextY - sRomhackSetupScreen->splashText->base.height.value);
    } else {
        djui_base_set_location(&sRomhackSetupScreen->splashImage->base, 0, setupTextY - sRomhackSetupScreen->splashImage->base.height.value);
    }

    {
        // romhack setup text description
        djui_text_set_text(sRomhackSetupScreen->setupText, sRomhackSetupScreen->message);
        djui_base_set_location(&sRomhackSetupScreen->setupText->base, 0, setupTextY);
    }

    djui_base_compute(base);

    return true;
}

static void rom_setup_screen_destroy(struct DjuiBase *base) {
    struct RomSetupScreen *romSetupScreen = (struct RomSetupScreen *)base;
    free(romSetupScreen);
    sRomhackSetupScreen = NULL;
}

static void init_rom_setup_screen(void) {
    struct RomSetupScreen *romSetupScreen = calloc(1, sizeof(struct RomSetupScreen));
    struct DjuiBase *base = &romSetupScreen->base;

    djui_base_init(NULL, base, rom_setup_screen_on_render, rom_setup_screen_destroy);

    // splash text (easter egg)
    if (configExCoopTheme) {
        struct DjuiText* splashDjuiText = djui_text_create(base, "\\#ff0800\\SM\\#1be700\\64\\#00b3ff\\EX\n\\#ffef00\\COOP");
        djui_base_set_location_type(&splashDjuiText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_location(&splashDjuiText->base, 0, 0);
        djui_text_set_font(splashDjuiText, gDjuiFonts[1]);
        djui_text_set_font_scale(splashDjuiText, gDjuiFonts[1]->defaultFontScale);
        djui_text_set_alignment(splashDjuiText, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&splashDjuiText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&splashDjuiText->base, 1.0f, gDjuiFonts[1]->defaultFontScale * 3.0f);

        romSetupScreen->splashText = splashDjuiText;

    // splash image
    } else {
        struct DjuiImage* splashImage = djui_image_create(base, texture_coopdx_logo, 2048, 1024, G_IM_FMT_RGBA, G_IM_SIZ_32b);
        djui_base_set_location_type(&splashImage->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_alignment(&splashImage->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_location(&splashImage->base, 0, -100);
        djui_base_set_size(&splashImage->base, 512, 256);

        romSetupScreen->splashImage = splashImage;
    }

    {
        // current rom setup text
        struct DjuiText *text = djui_text_create(base, "");
        djui_base_set_location_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_location(&text->base, 0, 0);

        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, gDjuiFonts[0]->defaultFontScale * 3.0f);
        djui_base_set_color(&text->base, 220, 220, 220, 255);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_text_set_font(text, gDjuiFonts[0]);
        djui_text_set_font_scale(text, gDjuiFonts[0]->defaultFontScale);

        romSetupScreen->setupText = text;
    }

    sRomhackSetupScreen = romSetupScreen;
}

void render_rom_setup_screen(void) {
    if (!sRomhackSetupScreen) { init_rom_setup_screen(); }

    snprintf(sRomhackSetupScreen->message, MAX_ROM_SETUP_MESSAGE_LEN, "No rom detected, drag & drop Super Mario 64 (U) [!].z64 on to this screen");

    while (!gRomIsValid) {
        gfx_wm_main_loop(romhack_setup_screen_produce_one_frame);
    }
}
