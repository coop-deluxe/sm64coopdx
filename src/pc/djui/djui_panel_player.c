#include <stdio.h>
#include <stdlib.h>
#include "djui.h"
#include "pc/configfile.h"
#include "pc/network/network_player.h"
#include "game/level_update.h"
#include "game/area.h"

#define PALETTE_CUSTOM PALETTE_PRESET_MAX

static unsigned int sPalettePresetIndex = PALETTE_CUSTOM;
static unsigned int sCurrentPlayerPart  = SHIRT;
static unsigned int sSliderChannels[3]  = {0};

static struct DjuiSelectionbox* sPalettePresetSelection;

static struct DjuiSelectionbox* sPartSelection;
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
    char* sPartStrings[PLAYER_PART_MAX] = { "Overalls", "Shirt", "Gloves", "Shoes", "Hair", "Skin", "Cap" };

    f32 bodyHeight = 32 * 5 + 64 * 1 + 16 * 5;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\P\\#1be700\\A\\#00b3ff\\L\\#ffef00\\E\\#ff0800\\T\\#1be700\\T\\#00b3ff\\E");

    // Set current palette to custom when clicking on Edit Palette
    sPalettePresetIndex = PALETTE_CUSTOM;
    configPlayerPalette = configCustomPalette;
    djui_panel_player_edit_palette_update_palette_display();

    // A bit of a gross hack to send out palette changes and update the palette preset selection box on unpause AND
    // pressing the Back button
    sSavedDestroy = panel->base.destroy;
    panel->base.destroy = djui_panel_player_edit_palette_destroy;

    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        sCurrentPlayerPart = SHIRT;
        sPartSelection = djui_selectionbox_create(&body->base, "Part", sPartStrings, PLAYER_PART_MAX, &sCurrentPlayerPart);
        djui_base_set_size_type(&sPartSelection->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sPartSelection->base, 1.0f, 32);
        djui_interactable_hook_value_change(&sPartSelection->base, djui_panel_player_edit_palette_part_changed);

        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 32);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, "Hex Code");
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.485f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            sHexColorTextBox = djui_inputbox_create(&rect1->base, 7);
            djui_base_set_size_type(&sHexColorTextBox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&sHexColorTextBox->base, 0.5f, 32);
            djui_base_set_alignment(&sHexColorTextBox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_panel_player_edit_palette_update_hex_code_box();
            djui_interactable_hook_value_change(&sHexColorTextBox->base, djui_panel_player_edit_palette_hex_code_changed);
        }

        for (int i = 0; i < 3; i++) sSliderChannels[i] = configCustomPalette.parts[SHIRT][i];

        sSliderR = djui_slider_create(&body->base, "Red", &sSliderChannels[0], 0, 255);
        djui_base_set_size_type(&sSliderR->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&sSliderR->base, djui_panel_player_edit_palette_red_changed);
        djui_base_set_size(&sSliderR->base, 1.0f, 32);

        sSliderG = djui_slider_create(&body->base, "Green", &sSliderChannels[1], 0, 255);
        djui_base_set_size_type(&sSliderG->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&sSliderG->base, djui_panel_player_edit_palette_green_changed);
        djui_base_set_size(&sSliderG->base, 1.0f, 32);

        sSliderB = djui_slider_create(&body->base, "Blue", &sSliderChannels[2], 0, 255);
        djui_base_set_size_type(&sSliderB->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_interactable_hook_value_change(&sSliderB->base, djui_panel_player_edit_palette_blue_changed);
        djui_base_set_size(&sSliderB->base, 1.0f, 32);

        struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_button_set_style(button6, 1);
        djui_interactable_hook_click(&button6->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}

static bool djui_panel_player_name_valid(char* buffer) {
    if (buffer[0] == '\0') { return false; }
    while (*buffer != '\0') {
        if (*buffer >= '!' && *buffer <= '~') {
            buffer++;
            continue;
        }
        return false;
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
        djui_inputbox_set_text(inputbox1, "Player");
    }
    snprintf(configPlayerName, 20, "%s", inputbox1->buffer);
    djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);

    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }
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
        return;
    }

    if (inPlayerMenu) {
        inPlayerMenu = false;
        djui_panel_menu_back(NULL);
    } else {
        inPlayerMenu = true;
    }
}

void djui_panel_player_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 3 + 64 * 2 + 16 * 5;

    djui_panel_player_prevent_demo(NULL);

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\P\\#1be700\\L\\#00b3ff\\A\\#ffef00\\Y\\#ff0800\\E\\#1be700\\R");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 32);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, "Name");
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.485f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 20);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.5f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            if (djui_panel_player_name_valid(configPlayerName)) {
                djui_inputbox_set_text(inputbox1, configPlayerName);
            } else {
                djui_inputbox_set_text(inputbox1, "Player");
            }
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_player_name_text_change);
            djui_interactable_hook_focus(&inputbox1->base, NULL, NULL, djui_panel_player_name_on_focus_end);
        }

        char* modelChoices[CT_MAX] = { 0 };
        for (int i = 0; i < CT_MAX; i++) {
            modelChoices[i] = gCharacters[i].name;
        }
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Model", modelChoices, CT_MAX, &configPlayerModel);
        djui_base_set_size_type(&selectionbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox1->base, 1.0f, 32);
        djui_interactable_hook_value_change(&selectionbox1->base, djui_panel_player_value_changed);

        char* paletteChoices[PALETTE_PRESET_MAX+1] = {
            "Mario",
            "Luigi",
            "Waluigi",
            "Wario",
            "Chuckya",
            "Goomba",
            "Clover",
            "Cobalt",
            "Fury",
            "Hot Pink",
            "Nice Pink",
            "Seafoam",
            "Lilac",
            "Copper",
            "Azure",
            "Burgundy",
            "Mint",
            "Eggplant",
            "Orange",
            "Arctic",
            "Fire Mario",
            "Fire Luigi",
            "Fire Waluigi",
            "Fire Wario",
            "Busy Bee",
            "Fortress",
            "Battlements",
            "Blueberry Pie",
            "Raspberry",
            "Bubblegum",
            "Ice Mario",
            "Ice Luigi",
            "Custom",
        };

        for (int i = 0; i < PALETTE_PRESET_MAX; i++) {
            if (memcmp(&gNetworkPlayers[0].palette, &gPalettePresets[i], sizeof(struct PlayerPalette)) == 0) {
                sPalettePresetIndex = i;
                break;
            }
        }

        sPalettePresetSelection = djui_selectionbox_create(&body->base, "Palette Preset", paletteChoices, PALETTE_PRESET_MAX+1, &sPalettePresetIndex);
        djui_base_set_size_type(&sPalettePresetSelection->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sPalettePresetSelection->base, 1.0f, 32);
        djui_interactable_hook_value_change(&sPalettePresetSelection->base, djui_panel_player_value_changed);

        struct DjuiButton* editPaletteButton = djui_button_create(&body->base, "Edit Palette");
        djui_base_set_size_type(&editPaletteButton->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&editPaletteButton->base, 1.0f, 64);
        djui_interactable_hook_click(&editPaletteButton->base, djui_panel_player_edit_palette_create);

        struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_button_set_style(button6, 1);
        djui_interactable_hook_click(&button6->base, djui_panel_player_prevent_demo);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
