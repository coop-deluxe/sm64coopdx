#include "djui.h"
#include "../pc_main.h"

struct DjuiFpsDisplay {
    struct DjuiText *text;
    struct DjuiBase base;
};

struct DjuiFpsDisplay *sFpsDisplay = NULL;

void djui_fps_display_update(s16 fps) {
    if (configShowFPS) {
        char fpsText[30] = "";
        snprintf(fpsText, 30, "\\#dcdcdc\\FPS \\#ffffff\\%d", fps);
        djui_text_set_text(sFpsDisplay->text, fpsText);
    }
}

void djui_fps_display_render(void) {
    if (configShowFPS) {
        djui_rect_render(&sFpsDisplay->base);
        djui_base_render(&sFpsDisplay->base);
    }
}

void djui_fps_display_create(void) {
    struct DjuiFpsDisplay *fpsDisplay = malloc(sizeof(struct DjuiFpsDisplay));
    struct DjuiBase* base = &fpsDisplay->base;
    djui_base_init(NULL, base, NULL, NULL);
    djui_base_set_size(base, 150, 50);
    djui_base_set_color(base, 0, 0, 0, 240);
    djui_base_set_border_color(base, 0, 0, 0, 200);
    djui_base_set_border_width(base, 8);
    djui_base_set_padding(base, 16, 16, 16, 16);

    {
        // FPS text
        struct DjuiText *text = djui_text_create(base, "");
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, text->fontScale * 2);
        djui_base_set_location(&text->base, 0, -text->fontScale / 2);

        fpsDisplay->text = text;
    }

    sFpsDisplay = fpsDisplay;
}
