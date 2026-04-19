#include <stdio.h>
#include <string.h>
#include "djui.h"
#include "djui_lobby_entry.h"

#define VK_ESCAPE 1

static void djui_lobby_entry_update_style(struct DjuiBase* base) {
    struct DjuiLobbyEntry* entry = (struct DjuiLobbyEntry*)base;

    u8 rectElement;
    u8 borderElement;

    if (!entry->base.enabled) {
        rectElement   = DJUI_THEME_ELEMENT_PRIMARY_DISABLED;
        borderElement = DJUI_THEME_ELEMENT_PRIMARY_BORDER_DISABLED;
    } else if (gDjuiCursorDownOn == base) {
        rectElement   = DJUI_THEME_ELEMENT_PRIMARY_DOWN;
        borderElement = DJUI_THEME_ELEMENT_PRIMARY_BORDER_DOWN;
    } else if (gDjuiHovered == base) {
        rectElement   = DJUI_THEME_ELEMENT_PRIMARY_HOVER;
        borderElement = DJUI_THEME_ELEMENT_PRIMARY_BORDER_HOVER;
    } else {
        rectElement   = DJUI_THEME_ELEMENT_PRIMARY;
        borderElement = DJUI_THEME_ELEMENT_PRIMARY_BORDER;
    }

    djui_base_set_color_with_color(&entry->base, configDjuiTheme.elements[rectElement]);
    djui_base_set_border_color_with_color(base, configDjuiTheme.elements[borderElement]);
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

        djui_base_set_color_with_color(&text->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_PRIMARY_TEXT]);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        x += width;
    }

    djui_lobby_entry_update_style(base);

    return lobbyEntry;
}
