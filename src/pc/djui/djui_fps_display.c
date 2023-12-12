#include "djui.h"
#include "../pc_main.h"

struct DjuiFpsDisplay {
    struct DjuiText *text;
    struct DjuiBase base;
};

struct DjuiFpsDisplay *sFpsDisplay = NULL;

void djui_fps_display_update(s16 fps) {
    if (configDisplayFPS > 0) {
        char fpsText[60] = "";
        snprintf(fpsText, 60, "\\#dcdcdc\\FPS: \\#ffffff\\%d", fps);
        djui_text_set_text(sFpsDisplay->text, fpsText);
    }
}

void djui_fps_display_render(void) {
    if (configDisplayFPS > 0) {
        djui_base_set_size(&sFpsDisplay->base, (configDisplayFPS <= 1 ? 150 : 128), (configDisplayFPS <= 1 ? 50 : 32));
        djui_base_set_color(&sFpsDisplay->base, 0, 0, 0, (configDisplayFPS <= 1 ? 240 : (configDisplayFPS <= 2 ? 0 : (configDisplayFPS <= 3 ? 60 : (configDisplayFPS <= 4 ? 120 : (configDisplayFPS <= 5 ? 180 : 240))))));

        djui_base_set_border_color(&sFpsDisplay->base, 0, 0, 0, (configDisplayFPS <= 1 ? 200 : 1));
        djui_base_set_border_width(&sFpsDisplay->base, (configDisplayFPS <= 1 ? 8 : 0));
        djui_base_set_padding(&sFpsDisplay->base, 16, 16, 16, (configDisplayFPS <= 1 ? 16 : 6));

        djui_rect_render(&sFpsDisplay->base);
        djui_base_render(&sFpsDisplay->base);
    }
}

void djui_fps_display_create(void) {
    struct DjuiFpsDisplay *fpsDisplay = malloc(sizeof(struct DjuiFpsDisplay));
    struct DjuiBase* base = &fpsDisplay->base;

    djui_base_init(NULL, base, NULL, NULL);

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
