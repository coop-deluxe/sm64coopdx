#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_unicode.h"
#include "djui_panel_main.h"
#include "djui_panel_pause.h"
#include "djui_panel_options.h"
#include "djui_panel_characters.h"
#include "djui_panel_palettes.h"
#include "pc/network/network_player.h"
#include "pc/platform.h"
#include "game/level_update.h"
#include "game/area.h"

void djui_panel_player_create(struct DjuiBase* caller);

  //////////////////
 // player panel //
//////////////////

static char *djui_panel_player_name_default_get(void) {
    char *langName = DLANG(PLAYER, PLAYER);
    if (network_player_name_valid(langName)) {
        return langName;
    }
    static char *name = "Player";
    return name;
}

static void djui_panel_player_name_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
    struct DjuiColor* textColor = &theme->interactables.textColor;
    if (network_player_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text_color(inputbox1, textColor->r, textColor->g, textColor->b, textColor->a);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
}

static void djui_panel_player_name_on_focus_end(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
    struct DjuiColor* textColor = &theme->interactables.textColor;
    if (!network_player_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text(inputbox1, djui_panel_player_name_default_get());
    }
    snprintf(configPlayerName, MAX_CONFIG_STRING, "%s", inputbox1->buffer);
    djui_inputbox_set_text_color(inputbox1, textColor->r, textColor->g, textColor->b, textColor->a);

    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }
    djui_inputbox_on_focus_end(&inputbox1->base);
}


static void djui_panel_player_prevent_demo(struct DjuiBase* caller) {
    if (!gDjuiInMainMenu) {
        if (caller != NULL) {
            djui_panel_menu_back(NULL);
        }
    }
}

static void djui_panel_player_update_camera_cutscene(void) {
    if (gCamera && gCamera->cutscene == 0) {
        gCamera->cutscene = CUTSCENE_PALETTE_EDITOR;
    }
}

static void djui_panel_player_destroy(UNUSED struct DjuiBase* caller) {
    gDjuiInPlayerMenu = false;
}

void djui_panel_player_create(struct DjuiBase* caller) {
    djui_panel_player_prevent_demo(NULL);
    djui_panel_player_update_camera_cutscene();
    gDjuiInPlayerMenu = true;

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(PLAYER, PLAYER_TITLE), true);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(PLAYER, NAME));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 220, 220, 220, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, MAX_CONFIG_STRING);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.45f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            if (network_player_name_valid(configPlayerName)) {
                djui_inputbox_set_text(inputbox1, configPlayerName);
            } else {
                djui_inputbox_set_text(inputbox1, djui_panel_player_name_default_get());
            }
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_player_name_text_change);
            djui_interactable_hook_focus(&inputbox1->base, djui_inputbox_on_focus_begin, NULL, djui_panel_player_name_on_focus_end);
        }

        /*char* palettePresets[MAX_PRESET_PALETTES + 1] = { DLANG(PALETTE, CUSTOM) };
        int presetPaletteCount = gPresetPaletteCount;
        if (presetPaletteCount > 0) {
            if ((int)sPalettePresetIndex >= presetPaletteCount) {
                sPalettePresetIndex = 0;
            }

            for (int i = 0; i < presetPaletteCount; i++) {
                palettePresets[i + 1] = gPresetPalettes[i].name;

                if (memcmp(&configPlayerPalette, &gPresetPalettes[i].palette, sizeof(struct PlayerPalette)) == 0) {
                    sPalettePresetIndex = i + 1;
                }
            }
        }
        sPalettePresetSelection = djui_selectionbox_create(body, DLANG(PLAYER, PALETTE_PRESET), palettePresets, gPresetPaletteCount + 1, &sPalettePresetIndex, NULL);*/

        djui_button_create(body, DLANG(PLAYER, CHARACTERS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_characters_create);
        djui_button_create(body, DLANG(PLAYER, PALETTES), DJUI_BUTTON_STYLE_NORMAL, djui_panel_palettes_create);
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    struct DjuiPanel* p = djui_panel_add(caller, panel, NULL);
    if (!p) { return; }
    p->on_panel_destroy = djui_panel_player_destroy;
}
