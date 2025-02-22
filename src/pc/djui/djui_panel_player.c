#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_unicode.h"
#include "djui_panel_main.h"
#include "djui_panel_pause.h"
#include "djui_panel_options.h"
#include "pc/network/network_player.h"
#include "pc/platform.h"
#include "game/level_update.h"
#include "game/area.h"

static unsigned int sPalettePresetIndex = 0;
static unsigned int sCurrentPlayerPart = PANTS;
static unsigned int sSliderChannels[3] = { 0 };
static bool sReloadPalettePresetSelection = false;

static struct DjuiSelectionbox* sPalettePresetSelection = NULL;

static struct DjuiInputbox* sHexColorTextBox = NULL;
static struct DjuiSlider *sSliderR = NULL;
static struct DjuiSlider *sSliderG = NULL;
static struct DjuiSlider *sSliderB = NULL;
static struct DjuiInputbox* sPalettePresetNameTextBox = NULL;

static struct DjuiRect *sColorRect = NULL;

struct DjuiText* gDjuiPaletteToggle = NULL;

void djui_panel_player_create(struct DjuiBase* caller);

  ////////////////////////
 // edit palette panel //
////////////////////////

static unsigned int djui_panel_player_edit_palette_get_palette_index(struct PlayerPalette palette) {
    for (int i = 0; i < gPresetPaletteCount; i++) {
        if (memcmp(&palette, &gPresetPalettes[i].palette, sizeof(struct PlayerPalette)) == 0) {
            return i + 1;
        }
    }
    return 0;
}

static void djui_panel_player_edit_palette_update_hex_code_box(void) {
    char buf[7];
    static const char digitToChar[] = "0123456789abcdef";

    for (size_t i = 0; i < 3; i++) {
        buf[2*i]   = digitToChar[configPlayerPalette.parts[sCurrentPlayerPart][i] >> 4];
        buf[2*i+1] = digitToChar[configPlayerPalette.parts[sCurrentPlayerPart][i] & 0xF];
    }

    buf[6] = '\0';

    djui_inputbox_set_text(sHexColorTextBox, buf);
}

static void djui_panel_player_edit_palette_update_palette_display(void) {
    if (memcmp(&gNetworkPlayers[0].overridePalette, &gNetworkPlayers[0].palette, sizeof(struct PlayerPalette)) == 0) {
        gNetworkPlayers[0].overridePalette = configPlayerPalette;
    }

    gNetworkPlayers[0].palette = configPlayerPalette;
}

static void djui_panel_player_update_color_rect(void) {
    if (sColorRect) {
        djui_base_set_color(&sColorRect->base, sSliderChannels[0], sSliderChannels[1], sSliderChannels[2], 0xFF);
    }
}

static void djui_panel_player_edit_palette_update_sliders(void) {
    for (int i = 0; i < 3; i++) sSliderChannels[i] = configPlayerPalette.parts[sCurrentPlayerPart][i];

    djui_slider_update_value(&sSliderR->base);
    djui_slider_update_value(&sSliderG->base);
    djui_slider_update_value(&sSliderB->base);
    djui_panel_player_update_color_rect();
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
        configPlayerPalette.parts[sCurrentPlayerPart][i] = (char_to_hex_digit(input->buffer[2 * i]) << 4) |
                                                           char_to_hex_digit(input->buffer[2 * i + 1]);
    }

    djui_panel_player_edit_palette_update_sliders();
    djui_panel_player_edit_palette_update_palette_display();
}

static void djui_panel_player_edit_palette_slider_changed(UNUSED struct DjuiBase* caller, size_t index) {
    configPlayerPalette.parts[sCurrentPlayerPart][index] = sSliderChannels[index];

    djui_panel_player_edit_palette_update_hex_code_box();
    djui_panel_player_edit_palette_update_palette_display();
    djui_panel_player_update_color_rect();
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

static bool djui_panel_player_edit_palette_preset_name_valid(char* buffer) {
    if (buffer[0] == '\0') { return false; }
    char* c = buffer;
    while (*c != '\0') {
#if defined(_WIN32) || defined(_WIN64)
        if (*c == '/' || *c == '\\' || *c == ':' || *c == '<' || *c == '>' || *c == '"' || *c == '|' || *c == '?' || *c == '*') { return false; }
#else
        if (*c == '/' || *c == '\\') { return false; }
#endif
        if (!djui_unicode_valid_char(c)) { return false; }
        c = djui_unicode_next_char(c);
    }
    return true;
}

static char* djui_panel_player_edit_palette_preset_name_get_text(void) {
    char* name = "Unnamed";
    if (gPresetPaletteCount > 0) {
        for (int i = 0; i < gPresetPaletteCount; i++) {
            if (memcmp(&configPlayerPalette, &gPresetPalettes[i].palette, sizeof(struct PlayerPalette)) == 0) {
                name = gPresetPalettes[i].name;
            }
        }
    }
    return name;
}

static void djui_panel_player_edit_palette_preset_name_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (djui_panel_player_edit_palette_preset_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
}

static void djui_panel_player_edit_palette_preset_name_on_focus_end(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (!djui_panel_player_edit_palette_preset_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text(inputbox1, djui_panel_player_edit_palette_preset_name_get_text());
    }
    djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);

    djui_inputbox_on_focus_end(&inputbox1->base);
}

static void djui_panel_player_edit_palette_delete(UNUSED struct DjuiBase* caller) {
    // if (!player_palette_delete(fs_get_write_path(PALETTES_DIRECTORY), sPalettePresetNameTextBox->buffer)) {
    //     player_palette_delete(sys_exe_path(), sPalettePresetNameTextBox->buffer);
    // }
    player_palette_delete(fs_get_write_path(PALETTES_DIRECTORY), sPalettePresetNameTextBox->buffer, false);
    sReloadPalettePresetSelection = true;
}

static void djui_panel_player_edit_palette_export(UNUSED struct DjuiBase* caller) {
    player_palette_export(sPalettePresetNameTextBox->buffer);
    sReloadPalettePresetSelection = true;
}

static void (*sSavedDestroy)(struct DjuiBase*);
static void djui_panel_player_edit_palette_destroy(struct DjuiBase* caller) {
    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }

    sColorRect = NULL;

    if (sPalettePresetSelection) {
        sPalettePresetIndex = djui_panel_player_edit_palette_get_palette_index(configPlayerPalette);
        djui_selectionbox_update_value(&sPalettePresetSelection->base);
    }

    if (sReloadPalettePresetSelection) {
        sReloadPalettePresetSelection = false;
        if (gDjuiInMainMenu) {
            djui_panel_shutdown();
            gDjuiInMainMenu = true;
            djui_panel_main_create(NULL);
            djui_panel_options_create(NULL);
            djui_panel_player_create(NULL);
        } else if (gDjuiPanelPauseCreated) {
            djui_panel_shutdown();
            djui_panel_pause_create(NULL);
            djui_panel_player_create(NULL);
        }
        return;
    }

    (*sSavedDestroy)(caller);
}

static void djui_panel_player_edit_palette_create(struct DjuiBase* caller) {
    gDjuiInPlayerMenu = true;

    char* sPartStrings[PLAYER_PART_MAX] = { DLANG(PLAYER, OVERALLS), DLANG(PLAYER, SHIRT), DLANG(PLAYER, GLOVES), DLANG(PLAYER, SHOES), DLANG(PLAYER, HAIR), DLANG(PLAYER, SKIN), DLANG(PLAYER, CAP), DLANG(PLAYER, EMBLEM) };

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(PLAYER, PALETTE), true);

    // A bit of a gross hack to send out palette changes and update the palette preset selection box on unpause AND
    // pressing the Back button
    sSavedDestroy = panel->base.destroy;
    panel->base.destroy = djui_panel_player_edit_palette_destroy;

    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        sCurrentPlayerPart = PANTS;
        djui_selectionbox_create(body, DLANG(PLAYER, PART), sPartStrings, PLAYER_PART_MAX, &sCurrentPlayerPart, djui_panel_player_edit_palette_part_changed);

        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(PLAYER, HEX_CODE));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 220, 220, 220, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

            sHexColorTextBox = djui_inputbox_create(&rect1->base, 7);
            djui_base_set_size_type(&sHexColorTextBox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&sHexColorTextBox->base, 0.45f, 32);
            djui_base_set_alignment(&sHexColorTextBox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_panel_player_edit_palette_update_hex_code_box();
            djui_interactable_hook_value_change(&sHexColorTextBox->base, djui_panel_player_edit_palette_hex_code_changed);
        }

        for (int i = 0; i < 3; i++) sSliderChannels[i] = configPlayerPalette.parts[PANTS][i];

        sSliderR = djui_slider_create(body, DLANG(PLAYER, RED), &sSliderChannels[0], 0, 255, djui_panel_player_edit_palette_red_changed);
        djui_base_set_color(&sSliderR->rectValue->base, 255, 0, 0, 255);
        sSliderR->updateRectValueColor = false;
        sSliderG = djui_slider_create(body, DLANG(PLAYER, GREEN), &sSliderChannels[1], 0, 255, djui_panel_player_edit_palette_green_changed);
        djui_base_set_color(&sSliderG->rectValue->base, 0, 255, 0, 255);
        sSliderG->updateRectValueColor = false;
        sSliderB = djui_slider_create(body, DLANG(PLAYER, BLUE), &sSliderChannels[2], 0, 255, djui_panel_player_edit_palette_blue_changed);
        djui_base_set_color(&sSliderB->rectValue->base, 0, 0, 255, 255);
        sSliderB->updateRectValueColor = false;

        struct DjuiRect* space = djui_rect_create(body);
        djui_base_set_alignment(&space->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_size_type(&space->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&space->base, 0.95f, 32);
        djui_base_set_color(&space->base, 0, 0, 0, 0);
        djui_base_set_border_width(&space->base, 2);
        djui_base_set_border_color(&space->base, 173, 173, 173, 255);

        struct DjuiRect* rectValue = djui_rect_create(&space->base);
        djui_base_set_size_type(&rectValue->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_color(&rectValue->base, sSliderChannels[0], sSliderChannels[1], sSliderChannels[2], 255);
        sColorRect = rectValue;

        struct DjuiRect* rect2 = djui_rect_container_create(body, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect2->base, DLANG(PLAYER, PRESET_NAME));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 220, 220, 220, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

            sPalettePresetNameTextBox = djui_inputbox_create(&rect2->base, 32);
            djui_inputbox_set_text(sPalettePresetNameTextBox, djui_panel_player_edit_palette_preset_name_get_text());
            djui_base_set_size_type(&sPalettePresetNameTextBox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&sPalettePresetNameTextBox->base, 0.45f, 32);
            djui_base_set_alignment(&sPalettePresetNameTextBox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_interactable_hook_value_change(&sPalettePresetNameTextBox->base, djui_panel_player_edit_palette_preset_name_text_change);
            djui_interactable_hook_focus(&sPalettePresetNameTextBox->base, djui_inputbox_on_focus_begin, NULL, djui_panel_player_edit_palette_preset_name_on_focus_end);
        }

        struct DjuiRect* rect3 = djui_rect_container_create(body, 32);
        {
            struct DjuiButton* button1 = djui_button_left_create(&rect3->base, DLANG(PLAYER, DELETE_PRESET), DJUI_BUTTON_STYLE_NORMAL, djui_panel_player_edit_palette_delete);
            djui_base_set_size(&button1->base, 0.485f, 32);
            struct DjuiButton* button2 = djui_button_right_create(&rect3->base, DLANG(PLAYER, SAVE_PRESET), DJUI_BUTTON_STYLE_NORMAL, djui_panel_player_edit_palette_export);
            djui_base_set_size(&button2->base, 0.485f, 32);
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        {
            struct DjuiText *text = djui_text_create(body, DLANG(PLAYER, CAP_TOGGLE));
            djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&text->base, 1.0f, 64);
            gDjuiPaletteToggle = text;
        }
    }

    djui_panel_add(caller, panel, NULL);
}


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
    if (network_player_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
}

static void djui_panel_player_name_on_focus_end(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (!network_player_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text(inputbox1, djui_panel_player_name_default_get());
    }
    snprintf(configPlayerName, MAX_CONFIG_STRING, "%s", inputbox1->buffer);
    djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);

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

static void djui_panel_player_value_changed(UNUSED struct DjuiBase* caller) {
    djui_panel_player_edit_palette_update_palette_display();

    if (configPlayerModel >= CT_MAX) { configPlayerModel = CT_MARIO; }
    if (gNetworkPlayers[0].overrideModelIndex == gNetworkPlayers[0].modelIndex) { gNetworkPlayers[0].overrideModelIndex = configPlayerModel; }

    gNetworkPlayers[0].modelIndex = configPlayerModel;
    network_player_update_model(0);

    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }
}

static void djui_panel_player_update_preset_palette(UNUSED struct DjuiBase* caller) {
    if (sPalettePresetIndex < 1) { return; }
    configPlayerPalette = gPresetPalettes[sPalettePresetIndex - 1].palette;
    djui_panel_player_edit_palette_update_palette_display();

    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
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

        char* characterChoices[CT_MAX] = { 0 };
        for (int i = 0; i < CT_MAX; i++) {
            characterChoices[i] = gCharacters[i].name;
        }
        djui_selectionbox_create(body, DLANG(PLAYER, MODEL), characterChoices, CT_MAX, &configPlayerModel, djui_panel_player_value_changed);

        player_palettes_reset();
        player_palettes_read(sys_resource_path(), true);
        player_palettes_read(fs_get_write_path(PALETTES_DIRECTORY), false);

        char* palettePresets[MAX_PRESET_PALETTES + 1] = { DLANG(PALETTE, CUSTOM) };
        if (gPresetPaletteCount > 0) {
            if (sPalettePresetIndex >= gPresetPaletteCount) {
                sPalettePresetIndex = 0;
            }

            for (int i = 0; i < gPresetPaletteCount; i++) {
                palettePresets[i + 1] = gPresetPalettes[i].name;

                if (memcmp(&configPlayerPalette, &gPresetPalettes[i].palette, sizeof(struct PlayerPalette)) == 0) {
                    sPalettePresetIndex = i + 1;
                }
            }
        }
        sPalettePresetSelection = djui_selectionbox_create(body, DLANG(PLAYER, PALETTE_PRESET), palettePresets, gPresetPaletteCount + 1, &sPalettePresetIndex, djui_panel_player_update_preset_palette);

        djui_button_create(body, DLANG(PLAYER, EDIT_PALETTE), DJUI_BUTTON_STYLE_NORMAL, djui_panel_player_edit_palette_create);
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        {
            struct DjuiText *text = djui_text_create(body, DLANG(PLAYER, CAP_TOGGLE));
            djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&text->base, 1.0f, 64);
            gDjuiPaletteToggle = text;
        }
    }

    struct DjuiPanel* p = djui_panel_add(caller, panel, NULL);
    p->on_panel_destroy = djui_panel_player_destroy;
}
