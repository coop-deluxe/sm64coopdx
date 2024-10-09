#include <stdio.h>
#include <string.h>
#include "djui.h"
#include "pc/controller/controller_api.h"
#include "pc/controller/controller_bind_mapping.h"
#include "sounds.h"
#include "audio/external.h"

#define VK_ESCAPE 1

static void djui_bind_button_on_click(struct DjuiBase* caller) {
    struct DjuiButton* button = (struct DjuiButton*)caller;
    djui_text_set_text(button->text, "...");
    controller_get_raw_key(); // consume lingering controller button press
    djui_interactable_set_binding(caller);
}

static void djui_bind_button_on_bind(struct DjuiBase* caller) {
    struct DjuiButton* button = (struct DjuiButton*)caller;
    struct DjuiBind* bind = (struct DjuiBind*) caller->parent->parent;

    // get key
    u32 key = controller_get_raw_key();
    if (key == VK_INVALID) { return; }

    // invalidate key
    for (int i = 0; i < MAX_BINDS; i++) {
        if (i == button->base.tag) { continue; }
        if (bind->configKey[i] == key) {
            key = VK_INVALID;
        }
    }

    // set key
    bind->configKey[button->base.tag] = key;
#if defined(CAPI_SDL1) || defined(CAPI_SDL2)
    djui_text_set_text(button->text, translate_bind_to_name(key));
#else
    djui_text_set_text(button->text, "???");
#endif
    djui_interactable_set_binding(NULL);
    play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
    controller_reconfigure();
}

static void djui_bind_destroy(struct DjuiBase* base) {
    struct DjuiBind* bind = (struct DjuiBind*)base;
    free(bind);
}

struct DjuiBind* djui_bind_create(struct DjuiBase* parent, const char* message, unsigned int configKey[]) {
    struct DjuiBind* bind = calloc(1, sizeof(struct DjuiBind));
    struct DjuiBase* base     = &bind->base;

    bind->configKey = configKey;

    djui_base_init(parent, base, NULL, djui_bind_destroy);
    djui_base_set_size_type(&bind->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&bind->base, 1.0f, 28);
    djui_base_set_color(&bind->base, 0, 0, 0, 0);

    struct DjuiText* text = djui_text_create(&bind->base, message);
    djui_base_set_alignment(&text->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&text->base, 0.3f, 1.0f);
    djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    djui_base_set_color(&text->base, 220, 220, 220, 255);
    bind->text = text;

    struct DjuiRect* rect = djui_rect_create(&bind->base);
    djui_base_set_alignment(&rect->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&rect->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&rect->base, 0.7f, 1.0f);
    djui_base_set_color(&rect->base, 0, 0, 0, 0);
    bind->rect = rect;

    for (int i = 0; i < MAX_BINDS; i++) {
#if defined(CAPI_SDL1) || defined(CAPI_SDL2)
        unsigned int key = configKey[i];
        struct DjuiButton* button = djui_button_create(&rect->base, translate_bind_to_name(key), DJUI_BUTTON_STYLE_NORMAL, djui_bind_button_on_click);
#else
        struct DjuiButton* button = djui_button_create(&rect->base, "???", DJUI_BUTTON_STYLE_NORMAL, djui_bind_button_on_click);
#endif
        djui_base_set_size_type(&button->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&button->base, 0.33f, 1.0f);
        button->base.tag = i;
        djui_interactable_hook_bind(&button->base, djui_bind_button_on_bind);

        enum DjuiHAlign hAlign = DJUI_HALIGN_LEFT;
        if (i > 0) { hAlign = (i == 1) ? DJUI_HALIGN_CENTER : DJUI_HALIGN_RIGHT; }
        djui_base_set_alignment(&button->base, hAlign, DJUI_VALIGN_CENTER);

        bind->buttons[i] = button;
    }

    return bind;
}
