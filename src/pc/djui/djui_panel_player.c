#include <stdio.h>
#include <stdlib.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_unicode.h"
#include "pc/configfile.h"
#include "pc/network/network_player.h"
#include "game/level_update.h"
#include "game/area.h"

#define PALETTE_CUSTOM PALETTE_PRESET_MAX

static unsigned int sPalettePresetIndex = PALETTE_CUSTOM;
static unsigned int sCurrentPlayerPart  = SHIRT;
static unsigned int sSliderChannels[3]  = {0};

static struct DjuiSelectionbox* sPalettePresetSelection;

static struct DjuiInputbox* sHexColorTextBox;
static struct DjuiSlider *sSliderR, *sSliderG, *sSliderB;

static void djui_panel_player_edit_palette_update_hex_code_box() {
    char buf[7];
    static const char digitToChar[] = "0123456789abcdef";

    for (size_t i = 0; i < 3; i++) {
        buf[2*i]   = digitToChar[configCustomPalette.parts[sCurrentPlayerPart][i] >> 4];
        buf[2*i+1] = digitToChar[configCustomPalette.parts[sCurrentPlayerPart][i] & 0xF];
    }

    buf[6] = '\0';

    djui_inputbox_set_text(sHexColorTextBox, buf);
}

static void djui_panel_player_edit_palette_update_palette_display() {
    if (memcmp(&gNetworkPlayers[0].overridePalette, &gNetworkPlayers[0].palette, sizeof(struct PlayerPalette)) == 0) {
        gNetworkPlayers[0].overridePalette = configPlayerPalette;
    }

    gNetworkPlayers[0].palette = configPlayerPalette;
}

static void djui_panel_player_edit_palette_update_sliders() {
    for (int i = 0; i < 3; i++) sSliderChannels[i] = configCustomPalette.parts[sCurrentPlayerPart][i];

    djui_slider_update_value(&sSliderR->base);
    djui_slider_update_value(&sSliderG->base);
    djui_slider_update_value(&sSliderB->base);
}

static void djui_panel_player_edit_palette_part_changed(UNUSED struct DjuiBase* caller) {
    djui_panel_player_edit_palette_update_sliders();
    djui_panel_player_edit_palette_update_hex_code_box();
}

static int char_to_hex_digit(char c) {
    return (c >= '0' && c <= '9') ? c - '0' : c - 'a' + 10;
}

static void djui_panel_player_edit_palette_hex_code_changed(struct DjuiBase* caller) {
    struct DjuiInputbox* input = (struct DjuiInputbox*) caller;

    for (int i = 0; i < 6; i++) {
        char c = input->buffer[i];
        if (c == '\0') return;  // all 6 characters must be filled

        if (c >= 'A' && c <= 'Z') {
            input->buffer[i] = c - 'A' + 'a'; // convert all characters to lowercase
        }

        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) return;
    }

    for (int i = 0; i < 3; i++) {
        configCustomPalette.parts[sCurrentPlayerPart][i] = (char_to_hex_digit(input->buffer[2 * i]) << 4) |
                                                           char_to_hex_digit(input->buffer[2 * i + 1]);
    }
    configPlayerPalette = configCustomPalette;

    djui_panel_player_edit_palette_update_sliders();
    djui_panel_player_edit_palette_update_palette_display();
    sPalettePresetIndex = PALETTE_CUSTOM;
}

static void djui_panel_player_edit_palette_slider_changed(UNUSED struct DjuiBase* caller, size_t index) {
    configCustomPalette.parts[sCurrentPlayerPart][index] = sSliderChannels[index];
    configPlayerPalette = configCustomPalette;

    djui_panel_player_edit_palette_update_hex_code_box();
    djui_panel_player_edit_palette_update_palette_display();
    sPalettePresetIndex = PALETTE_CUSTOM;
}

static void djui_panel_player_edit_palette_red_changed(UNUSED struct DjuiBase* caller) {
    djui_panel_player_edit_palette_slider_changed(caller, 0);
}

static void djui_panel_player_edit_palette_green_changed(UNUSED struct DjuiBase* caller) {
    djui_panel_player_edit_palette_slider_changed(caller, 1);
}

static void djui_panel_player_edit_palette_blue_changed(UNUSED struct DjuiBase* caller) {
    djui_panel_player_edit_palette_slider_changed(caller, 2);
}

static void (*sSavedDestroy)(struct DjuiBase*);
void djui_panel_player_edit_palette_destroy(struct DjuiBase* caller) {
    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }

    djui_selectionbox_update_value(&sPalettePresetSelection->base); // since editing palette values can change it

    (*sSavedDestroy)(caller);
}

static void djui_panel_player_edit_palette_create(struct DjuiBase* caller) {
    char* sPartStrings[PLAYER_PART_MAX] = { DLANG(PLAYER, OVERALLS), DLANG(PLAYER, SHIRT), DLANG(PLAYER, GLOVES), DLANG(PLAYER, SHOES), DLANG(PLAYER, HAIR), DLANG(PLAYER, SKIN), DLANG(PLAYER, CAP) };

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(PLAYER, PALETTE));

    // Set current palette to custom when clicking on Edit Palette
    sPalettePresetIndex = PALETTE_CUSTOM;
    configPlayerPalette = configCustomPalette;
    djui_panel_player_edit_palette_update_palette_display();

    // A bit of a gross hack to send out palette changes and update the palette preset selection box on unpause AND
    // pressing the Back button
    sSavedDestroy = panel->base.destroy;
    panel->base.destroy = djui_panel_player_edit_palette_destroy;

    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        sCurrentPlayerPart = SHIRT;
        djui_selectionbox_create(body, DLANG(PLAYER, PART), sPartStrings, PLAYER_PART_MAX, &sCurrentPlayerPart, djui_panel_player_edit_palette_part_changed);

        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(PLAYER, HEX_CODE));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            sHexColorTextBox = djui_inputbox_create(&rect1->base, 7);
            djui_base_set_size_type(&sHexColorTextBox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&sHexColorTextBox->base, 0.4f, 32);
            djui_base_set_alignment(&sHexColorTextBox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_panel_player_edit_palette_update_hex_code_box();
            djui_interactable_hook_value_change(&sHexColorTextBox->base, djui_panel_player_edit_palette_hex_code_changed);
        }

        for (int i = 0; i < 3; i++) sSliderChannels[i] = configCustomPalette.parts[SHIRT][i];

        sSliderR = djui_slider_create(body, DLANG(PLAYER, RED), &sSliderChannels[0], 0, 255, djui_panel_player_edit_palette_red_changed);
        sSliderG = djui_slider_create(body, DLANG(PLAYER, GREEN), &sSliderChannels[1], 0, 255, djui_panel_player_edit_palette_green_changed);
        sSliderB = djui_slider_create(body, DLANG(PLAYER, BLUE), &sSliderChannels[2], 0, 255, djui_panel_player_edit_palette_blue_changed);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}

static bool djui_panel_player_name_valid(char* buffer) {
    if (buffer[0] == '\0') { return false; }
    char* c = buffer;
    while (*c != '\0') {
        if (*c == ' ') { return false; }
        if (!djui_unicode_valid_char(c)) { return false; }
        c = djui_unicode_next_char(c);
    }
    return true;
}

static void djui_panel_player_name_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (djui_panel_player_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
}

static void djui_panel_player_name_on_focus_end(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (!djui_panel_player_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text(inputbox1, DLANG(PLAYER, PLAYER));
    }
    snprintf(configPlayerName, MAX_PLAYER_STRING, "%s", inputbox1->buffer);
    djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);

    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }
    djui_inputbox_on_focus_end(&inputbox1->base);
}

static void djui_panel_player_value_changed(UNUSED struct DjuiBase* caller) {
    if (sPalettePresetIndex != PALETTE_CUSTOM) {
        configPlayerPalette = gPalettePresets[sPalettePresetIndex];
    } else {
        configPlayerPalette = configCustomPalette;
    }
    djui_panel_player_edit_palette_update_palette_display();

    if (configPlayerModel >= CT_MAX) { configPlayerModel = 0; }
    if (gNetworkPlayers[0].overrideModelIndex == gNetworkPlayers[0].modelIndex) { gNetworkPlayers[0].overrideModelIndex = configPlayerModel; }

    gNetworkPlayers[0].modelIndex = configPlayerModel;
    network_player_update_model(0);

    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }
}

static void djui_panel_player_prevent_demo(struct DjuiBase* caller) {
    if (!gDjuiInMainMenu) {
        if (caller != NULL) {
            djui_panel_menu_back(NULL);
        }
    }
}

static void djui_panel_player_destroy(UNUSED struct DjuiBase* caller) {
    gInPlayerMenu = false;
}

void djui_panel_player_create(struct DjuiBase* caller) {
    djui_panel_player_prevent_demo(NULL);
    gInPlayerMenu = true;

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(PLAYER, PLAYER_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(PLAYER, NAME));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, MAX_PLAYER_STRING);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.4f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            if (djui_panel_player_name_valid(configPlayerName)) {
                djui_inputbox_set_text(inputbox1, configPlayerName);
            } else {
                djui_inputbox_set_text(inputbox1, DLANG(PLAYER, PLAYER));
            }
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_player_name_text_change);
            djui_interactable_hook_focus(&inputbox1->base, djui_inputbox_on_focus_begin, NULL, djui_panel_player_name_on_focus_end);
        }

        char* modelChoices[CT_MAX] = { 0 };
        for (int i = 0; i < CT_MAX; i++) {
            modelChoices[i] = gCharacters[i].name;
        }
        djui_selectionbox_create(body, DLANG(PLAYER, MODEL), modelChoices, CT_MAX, &configPlayerModel, djui_panel_player_value_changed);

        char* paletteChoices[PALETTE_PRESET_MAX+1] = {
            DLANG(PALETTE, MARIO),
            DLANG(PALETTE, LUIGI),
            DLANG(PALETTE, WALUIGI),
            DLANG(PALETTE, WARIO),
            DLANG(PALETTE, CHUCKYA),
            DLANG(PALETTE, GOOMBA),
            DLANG(PALETTE, CLOVER),
            DLANG(PALETTE, COBALT),
            DLANG(PALETTE, FURY),
            DLANG(PALETTE, HOT_PINK),
            DLANG(PALETTE, NICE_PINK),
            DLANG(PALETTE, SEAFOAM),
            DLANG(PALETTE, LILAC),
            DLANG(PALETTE, COPPER),
            DLANG(PALETTE, AZURE),
            DLANG(PALETTE, BURGUNDY),
            DLANG(PALETTE, MINT),
            DLANG(PALETTE, EGGPLANT),
            DLANG(PALETTE, ORANGE),
            DLANG(PALETTE, ARCTIC),
            DLANG(PALETTE, FIRE_MARIO),
            DLANG(PALETTE, FIRE_LUIGI),
            DLANG(PALETTE, FIRE_WALUIGI),
            DLANG(PALETTE, FIRE_WARIO),
            DLANG(PALETTE, BUSY_BEE),
            DLANG(PALETTE, FORTRESS),
            DLANG(PALETTE, BATTLEMENTS),
            DLANG(PALETTE, BLUEBERRY_PIE),
            DLANG(PALETTE, RASPBERRY),
            DLANG(PALETTE, BUBBLEGUM),
            DLANG(PALETTE, ICE_MARIO),
            DLANG(PALETTE, ICE_LUIGI),
            DLANG(PALETTE, TOAD),
            DLANG(PALETTE, CUSTOM),
        };

        for (int i = 0; i < PALETTE_PRESET_MAX; i++) {
            if (memcmp(&gNetworkPlayers[0].palette, &gPalettePresets[i], sizeof(struct PlayerPalette)) == 0) {
                sPalettePresetIndex = i;
                break;
            }
        }

        sPalettePresetSelection = djui_selectionbox_create(body, DLANG(PLAYER, PALETTE_PRESET), paletteChoices, PALETTE_PRESET_MAX+1, &sPalettePresetIndex, djui_panel_player_value_changed);

        djui_button_create(body, DLANG(PLAYER, EDIT_PALETTE), DJUI_BUTTON_STYLE_NORMAL, djui_panel_player_edit_palette_create);
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    struct DjuiPanel* p = djui_panel_add(caller, panel, NULL);
    p->on_panel_destroy = djui_panel_player_destroy;
}
