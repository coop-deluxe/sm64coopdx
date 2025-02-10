#include "djui.h"
#include "pc/pc_main.h"

struct DjuiFpsDisplay {
    struct DjuiText *text;
    struct DjuiBase base;
};

struct DjuiFpsDisplay *sFpsDisplay = NULL;

void djui_fps_display_update(u16 fps) {
    if (configShowFPS && sFpsDisplay != NULL) {
        char fpsText[30] = "";
        snprintf(fpsText, 30, "\\#dcdcdc\\FPS: \\#ffffff\\%d", fps);
        djui_text_set_text(sFpsDisplay->text, fpsText);
    }
}

void djui_fps_display_render(void) {
    if (configShowFPS && sFpsDisplay != NULL) {
        djui_rect_render(&sFpsDisplay->base);
        djui_base_render(&sFpsDisplay->base);
    }
}

void djui_fps_display_on_destroy(UNUSED struct DjuiBase* base) {
    free(sFpsDisplay);
}

void djui_fps_display_create(void) {
    struct DjuiFpsDisplay *fpsDisplay = calloc(1, sizeof(struct DjuiFpsDisplay));
    struct DjuiBase* base = &fpsDisplay->base;
    djui_base_init(NULL, base, NULL, djui_fps_display_on_destroy);
    djui_base_set_size(base, 150, 50);
    djui_base_set_color(base, 0, 0, 0, 200);
    djui_base_set_border_color(base, 0, 0, 0, 160);
    djui_base_set_border_width(base, 4);
    djui_base_set_padding(base, 16, 16, 16, 16);

    {
        // FPS text
        struct DjuiText *text = djui_text_create(base, "");
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, text->fontScale * 2);
        djui_base_set_location(&text->base, 0, -text->fontScale / 3.0f);

        fpsDisplay->text = text;
    }

    sFpsDisplay = fpsDisplay;
}

void djui_fps_display_destroy(void) {
    if (sFpsDisplay) {
        djui_base_destroy(&sFpsDisplay->base);
    }
}
