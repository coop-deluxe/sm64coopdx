#include <stdio.h>
#include <string.h>
#include "djui.h"
#include "djui_lobby_entry.h"

#define VK_ESCAPE 1

static void djui_lobby_entry_update_style(struct DjuiBase* base) {
    struct DjuiLobbyEntry* entry = (struct DjuiLobbyEntry*)base;
    struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];

    if (!entry->base.enabled) {
        struct DjuiColor bc = djui_theme_shade_color(theme->interactables.defaultBorderColor, 0.3f);
        struct DjuiColor rc = djui_theme_shade_color(theme->interactables.defaultRectColor, 0.3f);

        djui_base_set_border_color(base, bc.r, bc.g, bc.b, bc.a);
        djui_base_set_color(&entry->base, rc.r, rc.g, rc.b, rc.a);
        //djui_base_set_location(&entry->text->base, 0.0f, 0.0f);
    } else if (gDjuiCursorDownOn == base) {
        struct DjuiColor bc = theme->interactables.cursorDownBorderColor;
        struct DjuiColor rc = theme->interactables.cursorDownRectColor;

        djui_base_set_border_color(base, bc.r, bc.g, bc.b, bc.a);
        djui_base_set_color(&entry->base, rc.r, rc.g, rc.b, rc.a);
        //djui_base_set_location(&entry->text->base, 1.0f, 1.0f);
    } else if (gDjuiHovered == base) {
        struct DjuiColor bc = theme->interactables.hoveredBorderColor;
        struct DjuiColor rc = theme->interactables.hoveredRectColor;

        djui_base_set_border_color(base, bc.r, bc.g, bc.b, bc.a);
        djui_base_set_color(&entry->base, rc.r, rc.g, rc.b, rc.a);
        //djui_base_set_location(&entry->text->base, -1.0f, -1.0f);
    } else {
        struct DjuiColor bc = theme->interactables.defaultBorderColor;
        struct DjuiColor rc = theme->interactables.defaultRectColor;

        djui_base_set_border_color(base, bc.r, bc.g, bc.b, bc.a);
        djui_base_set_color(&entry->base, rc.r, rc.g, rc.b, rc.a);
        //djui_base_set_location(&entry->text->base, 0.0f, 0.0f);
    }
}

static void djui_lobby_entry_destroy(struct DjuiBase* base) {
    struct DjuiLobbyEntry* lobbyEntry = (struct DjuiLobbyEntry*)base;
    if (lobbyEntry->description) { free((char*)lobbyEntry->description); }
    free(lobbyEntry);
}

struct DjuiLobbyEntry* djui_lobby_entry_create(struct DjuiBase* parent, char* host, char* mode, char* players, char* description, bool disabled, void (*on_click)(struct DjuiBase*), void (*on_hover)(struct DjuiBase*), void (*on_hover_end)(struct DjuiBase*)) {
    struct DjuiLobbyEntry* lobbyEntry = calloc(1, sizeof(struct DjuiLobbyEntry));
    struct DjuiBase* base = &lobbyEntry->base;

    lobbyEntry->description = strdup(description);

    djui_base_init(parent, base, djui_rect_render, djui_lobby_entry_destroy);
    djui_base_set_size_type(&lobbyEntry->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&lobbyEntry->base, 1.0f, 32);
    djui_base_set_color(&lobbyEntry->base, 255, 255, 255, 128);
    djui_base_set_border_color(&lobbyEntry->base, 128, 128, 128, 255);
    djui_base_set_border_width(&lobbyEntry->base, 2);
    djui_base_set_border_width_type(&lobbyEntry->base, DJUI_SVT_ABSOLUTE);
    djui_base_set_enabled(&lobbyEntry->base, !disabled);
    djui_interactable_create(base, djui_lobby_entry_update_style);
    djui_interactable_hook_click(base, on_click);
    djui_interactable_hook_hover(base, on_hover, on_hover_end);

    u8 numColumns = 3;
    f32 x = 0;
    for (int i = 0; i < numColumns; i++) {
        char* msg = NULL;
        f32 width = 0;
        switch (i) {
            case 0: msg = host; width = 0.4f; break;
            case 1: msg = mode; width = 0.45f; break;
            case 2: msg = players;  width = 0.15f; break;
        }
        struct DjuiText* text = djui_text_create(&lobbyEntry->base, msg);

        djui_base_set_alignment(&text->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_CENTER);

        djui_base_set_location_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_location(&text->base, x, 0.0f);

        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&text->base, width, 1.0f);

        struct DjuiColor tc = gDjuiThemes[configDjuiTheme]->interactables.textColor;
        djui_base_set_color(&text->base, tc.r, tc.g, tc.b, tc.a);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        x += width;
    }

    djui_lobby_entry_update_style(base);

    return lobbyEntry;
}
