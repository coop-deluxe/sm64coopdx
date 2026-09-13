#include "djui.h"
#include "djui_theme.h"
#include "djui_three_panel.h"
#include "djui_panel.h"
#include "djui_panel_confirm.h"
#include "djui_panel_menu.h"
#include "djui_panel_main.h"
#include "djui_panel_options.h"
#include "djui_panel_misc.h"
#include "djui_panel_pause.h"
#include "djui_panel_menu_options.h"
#include "djui_panel_themes.h"
#include "djui_panel_theme_editor.h"
#include "djui_panel_modlist.h"
#include "djui_panel_playerlist.h"
#include "djui_hud_utils.h"
#include "djui_unicode.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/lua/smlua_hooks.h"
#include "game/level_update.h"
#include "seq_ids.h"

static struct DjuiTheme sOldDjuiTheme = { 0 };
static struct DjuiTheme *sDjuiTheme = NULL;
static unsigned int sDjuiHeaderFontSelected = 0;
static unsigned int sElementChoice = 0;
static bool sCreatingTheme = false;
static bool sSaving = false;

static struct {
    u32 r;
    u32 g;
    u32 b;
    u32 a;
} sSliderChannels;
static struct DjuiRect *sColorRect = NULL;
static struct DjuiInputbox *sHexColorTextBox = NULL;
static struct DjuiInputbox *sThemeNameTextBox = NULL;
static struct DjuiSlider *sSliderR = NULL;
static struct DjuiSlider *sSliderG = NULL;
static struct DjuiSlider *sSliderB = NULL;
static struct DjuiSlider *sSliderA = NULL;

static struct DjuiText *sTexts[16] = { NULL };
static unsigned int sTextsCount = 0;
static struct DjuiButton *sButtons[16] = { NULL };
static unsigned int sButtonsCount = 0;
static struct DjuiCheckbox *sCheckboxes[16] = { NULL };
static unsigned int sCheckboxesCount = 0;
static struct DjuiSelectionbox *sSelectionboxes[16] = { NULL };
static unsigned int sSelectionboxesCount = 0;

static char *sDjuiThemeElementKeys[DJUI_THEME_ELEMENT_COUNT] = {
    #define DEFINE_THEME_ELEMENT(name) #name,
    #include "djui_theme_elements.inl"
    #undef DEFINE_THEME_ELEMENT
};

static void djui_panel_theme_editor_reload(UNUSED struct DjuiBase *caller);

static bool djui_panel_theme_editor_on_back(UNUSED struct DjuiBase *caller) {
    // reset config theme to old theme
    configDjuiTheme = sOldDjuiTheme;

    if (!sSaving && sCreatingTheme) {
        growing_array_swap_and_pop(gDjuiThemes, sDjuiTheme); // remove created theme
    }

    if (gDjuiInMainMenu) {
        djui_panel_shutdown();
        gDjuiInMainMenu = true;
        djui_panel_playerlist_create(NULL);
        djui_panel_modlist_create(NULL);
        djui_panel_main_create(NULL);
        djui_panel_options_create(NULL);
        djui_panel_misc_create(NULL);
        djui_panel_main_menu_create(NULL);
        djui_panel_themes_create(NULL);
    } else if (gDjuiPanelPauseCreated) {
        djui_panel_shutdown();
        djui_panel_playerlist_create(NULL);
        djui_panel_modlist_create(NULL);
        djui_panel_pause_create(NULL);
        djui_panel_options_create(NULL);
        djui_panel_misc_create(NULL);
        djui_panel_main_menu_create(NULL);
        djui_panel_themes_create(NULL);

        djui_text_set_font(gDjuiPauseOptions, gDjuiFonts[configDjuiThemeFont]);
        djui_text_set_text(gDjuiPauseOptions, DLANG(MISC, R_BUTTON));

        djui_text_set_font(gDjuiModReload, gDjuiFonts[configDjuiThemeFont]);
        djui_text_set_text(gDjuiModReload, DLANG(MISC, L_BUTTON));
    }

    if (gDjuiChatBox) {
        djui_inputbox_reset_text_color(gDjuiChatBox->chatInput);
    }

    return true;
}

static void djui_panel_theme_editor_header_font_setting_change(UNUSED struct DjuiBase *caller) {
    u8 djuiHeaderFontChoices[7] = {
        FONT_NORMAL,
        FONT_MENU,
        FONT_MENU_DARK,
        FONT_CUSTOM_HUD,
        FONT_ALIASED,
        FONT_SPECIAL,
        FONT_CLASSIC
    };
    configDjuiTheme.headerFont = djuiHeaderFontChoices[sDjuiHeaderFontSelected];
    djui_panel_theme_editor_reload(NULL);
}

static void djui_panel_theme_editor_header_font_set_selected(u8 headerFont) {
    if (headerFont >= FONT_COUNT) return;
    u8 djuiHeaderFontSelectIndexes[FONT_COUNT] = {
        [FONT_NORMAL]     = 0,
        [FONT_MENU]       = 1,
        [FONT_MENU_DARK]  = 2,
        [FONT_CUSTOM_HUD] = 3,
        [FONT_ALIASED]    = 4,
        [FONT_SPECIAL]    = 5,
        [FONT_CLASSIC]    = 6,
    };
    sDjuiHeaderFontSelected = djuiHeaderFontSelectIndexes[headerFont];
}

static void djui_panel_theme_editor_edit_theme_update_hex_code_box(void) {
    char buf[9];
    static const char digitToChar[] = "0123456789abcdef";


    u8 rgba[4] = { 0 };
    rgba[0] = configDjuiTheme.elements[sElementChoice].r;
    rgba[1] = configDjuiTheme.elements[sElementChoice].g;
    rgba[2] = configDjuiTheme.elements[sElementChoice].b;
    rgba[3] = configDjuiTheme.elements[sElementChoice].a;
    for (size_t i = 0; i < 4; i++) {
        buf[2*i]   = digitToChar[rgba[i] >> 4];
        buf[2*i+1] = digitToChar[rgba[i] & 0xF];
    }

    buf[8] = '\0';

    djui_inputbox_set_text(sHexColorTextBox, buf);
}

static void djui_panel_theme_editor_update_color_rect(void) {
    if (sColorRect) {
        djui_base_set_color(&sColorRect->base, sSliderChannels.r, sSliderChannels.g, sSliderChannels.b, sSliderChannels.a);
    }
}

static void djui_panel_theme_editor_edit_theme_update_sliders(void) {
    struct DjuiColor c = configDjuiTheme.elements[sElementChoice];
    sSliderChannels.r = c.r;
    sSliderChannels.g = c.g;
    sSliderChannels.b = c.b;
    sSliderChannels.a = c.a;

    djui_slider_update_value(&sSliderR->base);
    djui_slider_update_style(&sSliderR->base);
    djui_text_set_font(sSliderR->text, gDjuiFonts[configDjuiThemeFont]);
    djui_base_set_color_with_color(&sSliderR->text->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_TEXT]);
    djui_slider_update_value(&sSliderG->base);
    djui_slider_update_style(&sSliderG->base);
    djui_text_set_font(sSliderG->text, gDjuiFonts[configDjuiThemeFont]);
    djui_base_set_color_with_color(&sSliderG->text->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_TEXT]);
    djui_slider_update_value(&sSliderB->base);
    djui_slider_update_style(&sSliderB->base);
    djui_text_set_font(sSliderB->text, gDjuiFonts[configDjuiThemeFont]);
    djui_base_set_color_with_color(&sSliderB->text->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_TEXT]);
    djui_slider_update_value(&sSliderA->base);
    djui_slider_update_style(&sSliderA->base);
    djui_text_set_font(sSliderA->text, gDjuiFonts[configDjuiThemeFont]);
    djui_base_set_color_with_color(&sSliderA->text->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_TEXT]);
    djui_base_set_gradient(&sSliderA->base, configDjuiTheme.gradients);
    djui_base_set_gradient(&sSliderA->rect->base, configDjuiTheme.gradients);
    djui_base_set_gradient(&sSliderA->rectValue->base, configDjuiTheme.gradients);
    djui_panel_theme_editor_update_color_rect();
}

static void djui_panel_theme_editor_edit_theme_slider_changed(UNUSED struct DjuiBase *caller) {
    configDjuiTheme.elements[sElementChoice].r = sSliderChannels.r;
    configDjuiTheme.elements[sElementChoice].g = sSliderChannels.g;
    configDjuiTheme.elements[sElementChoice].b = sSliderChannels.b;
    configDjuiTheme.elements[sElementChoice].a = sSliderChannels.a;

    djui_panel_theme_editor_edit_theme_update_hex_code_box();
    djui_panel_theme_editor_update_color_rect();
    djui_panel_theme_editor_reload(NULL);
}

static s32 char_to_hex_digit(char c) {
    return (c >= '0' && c <= '9') ? c - '0' : c - 'a' + 10;
}

static void djui_panel_theme_editor_edit_theme_hex_code_changed(struct DjuiBase *caller) {
    struct DjuiInputbox *input = (struct DjuiInputbox *) caller;

    for (s32 i = 0; i < 8; i++) {
        char c = input->buffer[i];
        if (c == '\0') { return; }  // all 8 characters must be filled

        if (c >= 'A' && c <= 'Z') {
            input->buffer[i] = c - 'A' + 'a'; // convert all characters to lowercase
        }

        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) { return; }
    }

    u8 rgba[4] = { 0 };
    for (s32 i = 0; i < 4; i++) {
        rgba[i] = (char_to_hex_digit(input->buffer[2 * i]) << 4) | char_to_hex_digit(input->buffer[2 * i + 1]);
    }
    configDjuiTheme.elements[sElementChoice].r = rgba[0];
    configDjuiTheme.elements[sElementChoice].g = rgba[1];
    configDjuiTheme.elements[sElementChoice].b = rgba[2];
    configDjuiTheme.elements[sElementChoice].a = rgba[3];

    djui_panel_theme_editor_edit_theme_update_sliders();
    djui_panel_theme_editor_reload(NULL);
}

static void djui_panel_theme_editor_theme_element_changed(UNUSED struct DjuiBase *caller) {
    sSliderChannels.r = configDjuiTheme.elements[sElementChoice].r;
    sSliderChannels.g = configDjuiTheme.elements[sElementChoice].g;
    sSliderChannels.b = configDjuiTheme.elements[sElementChoice].b;
    sSliderChannels.a = configDjuiTheme.elements[sElementChoice].a;

    djui_panel_theme_editor_edit_theme_update_sliders();
    djui_panel_theme_editor_edit_theme_update_hex_code_box();
    djui_panel_theme_editor_update_color_rect();
}

static bool djui_panel_theme_editor_edit_theme_name_valid(char *buffer) {
    if (buffer[0] == '\0') { return false; }
    char *c = buffer;
    while (*c != '\0') {
        if (*c == '/' || *c == '\\' || *c == ':' || *c == '<' || *c == '>' || *c == '"' || *c == '|' || *c == '?' || *c == '*') { return false; }
        if (!djui_unicode_valid_char(c)) { return false; }
        c = djui_unicode_next_char(c);
    }
    return true;
}

static char *djui_panel_theme_editor_edit_theme_name_get_text(void) {
    return sDjuiTheme->name;
}

static void djui_panel_theme_editor_edit_theme_name_text_change(struct DjuiBase *caller) {
    struct DjuiInputbox *inputbox1 = (struct DjuiInputbox *)caller;
    if (djui_panel_theme_editor_edit_theme_name_valid(inputbox1->buffer)) {
        djui_inputbox_reset_text_color(inputbox1);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
}

static void djui_panel_theme_editor_edit_theme_name_on_focus_end(struct DjuiBase *caller) {
    struct DjuiInputbox *inputbox1 = (struct DjuiInputbox *)caller;
    if (!djui_panel_theme_editor_edit_theme_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text(inputbox1, djui_panel_theme_editor_edit_theme_name_get_text());
    } else {
        djui_inputbox_reset_text_color(inputbox1);
    }

    djui_inputbox_on_focus_end(&inputbox1->base);
}

static void djui_panel_theme_editor_cancel(UNUSED struct  DjuiBase *caller) {
    djui_panel_theme_editor_on_back(NULL);
}

// TODO: Redo saving
static void djui_panel_theme_editor_edit_theme_save(UNUSED struct DjuiBase *caller) {
    if (!djui_panel_theme_editor_edit_theme_name_valid(sThemeNameTextBox->buffer)) { return; }

    sSaving = true;

    // copy the name and path to our configs djui theme
    snprintf(configDjuiTheme.name, MAX_DJUI_THEME_NAME_LEN, "%s", sThemeNameTextBox->buffer);
    snprintf(configDjuiTheme.path, SYS_MAX_PATH, "%s", sDjuiTheme->path);

    // set the djui theme to the config djui theme
    *sDjuiTheme = configDjuiTheme;

    // save current theme
    djui_themes_save(sDjuiTheme);

    // adjustments may be made to the theme struct in save, so set old djui theme to djui theme
    // since config djui theme will be set to this on back
    sOldDjuiTheme = *sDjuiTheme;

    djui_panel_theme_editor_reload(NULL);
    djui_panel_menu_back(NULL);
}

static bool djui_panel_theme_editor_renderer(struct DjuiBase *base) {
    struct DjuiThreePanel *threePanel = (struct DjuiThreePanel *)base;
    djui_base_set_color_with_color(&threePanel->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_THREE_PANEL]);
    djui_base_set_border_color_with_color(&threePanel->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_THREE_PANEL_BORDER]);
    djui_base_set_gradient(&threePanel->base, configDjuiTheme.gradients);
    struct DjuiBase *headerBase = djui_three_panel_get_header(threePanel);
    struct DjuiText *headerText = (struct DjuiText *)headerBase;
    djui_text_set_font(headerText, gDjuiFonts[configDjuiTheme.headerFont]);
    // if only we had unified font sizes and I didn't have to do this hack
    djui_text_set_font_scale(headerText, configDjuiTheme.headerFont == FONT_CUSTOM_HUD ? 96 : 64);
    if (!configDjuiTheme.useRainbowColor) {
        djui_text_set_text(headerText, DLANG(DJUI_THEMES, THEMES_TITLE));
        djui_base_set_color_with_color(headerBase, configDjuiTheme.elements[DJUI_THEME_ELEMENT_PANEL_HEADER_COLOR]);
    } else {
        djui_text_set_text(headerText, generate_rainbow_text(DLANG(DJUI_THEMES, THEMES_TITLE)));
        djui_base_set_color(headerBase, 255, 8, 0, 255);
    }
    return djui_three_panel_render(base);
}

static void djui_panel_theme_editor_reload(UNUSED struct DjuiBase *caller) {
    djui_inputbox_update_style(&sHexColorTextBox->base);
    djui_inputbox_reset_text_color(sHexColorTextBox);
    djui_base_set_gradient(&sHexColorTextBox->base, configDjuiTheme.gradients);

    djui_inputbox_update_style(&sThemeNameTextBox->base);
    djui_inputbox_reset_text_color(sThemeNameTextBox);
    djui_base_set_gradient(&sThemeNameTextBox->base, configDjuiTheme.gradients);

    for (u32 i = 0; i < sTextsCount; i++) {
        if (!sTexts[i]) { continue; }
        djui_base_set_color_with_color(&sTexts[i]->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_TEXT]);
        djui_text_set_font(sTexts[i], gDjuiFonts[configDjuiThemeFont]);
    }

    for (u32 i = 0; i < sButtonsCount; i++) {
        if (!sButtons[i]) { continue; }
        djui_button_update_style(&sButtons[i]->base);
        djui_base_set_gradient(&sButtons[i]->rect->base, configDjuiTheme.gradients);
        djui_text_set_font(sButtons[i]->text, gDjuiFonts[configDjuiThemeFont]);
    }

    for (u32 i = 0; i < sCheckboxesCount; i++) {
        if (!sCheckboxes[i]) { continue; }
        djui_checkbox_update_style(&sCheckboxes[i]->base);
        djui_base_set_gradient(&sCheckboxes[i]->rect->base, configDjuiTheme.gradients);
        djui_base_set_gradient(&sCheckboxes[i]->rectValue->base, configDjuiTheme.gradients);
        djui_text_set_font(sCheckboxes[i]->text, gDjuiFonts[configDjuiThemeFont]);
    }

    for (u32 i = 0; i < sSelectionboxesCount; i++) {
        if (!sSelectionboxes[i]) { continue; }
        djui_selectionbox_update_style(&sSelectionboxes[i]->base);
        djui_selectionbox_update_value(&sSelectionboxes[i]->base);
        djui_base_set_gradient(&sSelectionboxes[i]->rect->base, configDjuiTheme.gradients);
        djui_text_set_font(sSelectionboxes[i]->text, gDjuiFonts[configDjuiThemeFont]);
        djui_text_set_font(sSelectionboxes[i]->rectText, gDjuiFonts[configDjuiThemeFont]);
    }

    djui_panel_theme_editor_edit_theme_update_sliders();
    djui_panel_theme_editor_update_color_rect();
    smlua_call_event_hooks(HOOK_ON_DJUI_THEME_CHANGED);
}

void djui_panel_theme_editor_create(struct DjuiBase *caller) {
    sTextsCount = 0;
    sButtonsCount = 0;
    sCheckboxesCount = 0;
    sSelectionboxesCount = 0;
    sSaving = false;
    if (!caller || caller->tag < DJUI_THEME_COUNT) {
        sCreatingTheme = true;

        // we are creating a new theme, allocate a theme
        sDjuiTheme = growing_array_alloc(gDjuiThemes, sizeof(struct DjuiTheme));
        if (!sDjuiTheme) {
            LOG_ERROR("Failed to allocate new theme, ran out of memory!");
            return; // bail early!
        }

        // set old djui theme to the config theme
        sOldDjuiTheme = configDjuiTheme;

        // set djui theme to our config theme
        *sDjuiTheme = configDjuiTheme;

        // empty out path and name
        sDjuiTheme->path[0] = '\0';
        sDjuiTheme->name[0] = '\0';
        configDjuiTheme.name[0] = '\0';
    } else {
        sCreatingTheme = false;

        // point to theme in buffer
        sDjuiTheme = gDjuiThemes->buffer[caller->tag];

        // set old djui theme to the config theme
        sOldDjuiTheme = configDjuiTheme;

        // set config theme to djui theme
        configDjuiTheme = *sDjuiTheme;
    }
    struct DjuiThreePanel *panel = djui_panel_menu_create(DLANG(DJUI_THEMES, THEMES_TITLE), false);
    panel->base.render = djui_panel_theme_editor_renderer;
    struct DjuiBase *body = djui_three_panel_get_body(panel);
    {
        char *translatedThemeElementChoices[DJUI_THEME_ELEMENT_COUNT];
        for (u32 i = 0; i < DJUI_THEME_ELEMENT_COUNT; i++) {
            translatedThemeElementChoices[i] = djui_language_get("DJUI_THEMES", sDjuiThemeElementKeys[i]);
        }
        struct DjuiSelectionbox *selectionbox = djui_selectionbox_create(body, DLANG(DJUI_THEMES, ELEMENT), translatedThemeElementChoices, DJUI_THEME_ELEMENT_COUNT, &sElementChoice, djui_panel_theme_editor_theme_element_changed);
        djui_base_set_size(&selectionbox->rect->base, 0.65f, 1.0f);
        sSelectionboxes[sSelectionboxesCount++] = selectionbox;

        struct DjuiRect *rect1 = djui_rect_container_create(body, 32);
        {
            struct DjuiText *hexText = djui_text_create(&rect1->base, DLANG(DJUI_THEMES, HEX_CODE));
            djui_base_set_size_type(&hexText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color_with_color(&hexText->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_TEXT]);
            djui_base_set_size(&hexText->base, 0.585f, 64);
            djui_base_set_alignment(&hexText->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(hexText, 64, 64, 64, 100);
            sTexts[sTextsCount++] = hexText;

            sHexColorTextBox = djui_inputbox_create(&rect1->base, 9);
            djui_base_set_size_type(&sHexColorTextBox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&sHexColorTextBox->base, 0.45f, 32);
            djui_base_set_alignment(&sHexColorTextBox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_panel_theme_editor_edit_theme_update_hex_code_box();
            djui_interactable_hook_value_change(&sHexColorTextBox->base, djui_panel_theme_editor_edit_theme_hex_code_changed);
        }

        sSliderR = djui_slider_create(body, DLANG(DJUI_THEMES, RED), (u32 *)&sSliderChannels.r, 0, 255, djui_panel_theme_editor_edit_theme_slider_changed);
        djui_base_set_color(&sSliderR->rectValue->base, 255, 0, 0, 255);
        djui_base_set_gradient(&sSliderR->rectValue->base, false);
        djui_base_set_gradient(&sSliderR->rect->base, false);
        sSliderR->updateRectValueColor = false;
        djui_slider_update_style(&sSliderR->base);
        sSliderG = djui_slider_create(body, DLANG(DJUI_THEMES, GREEN), (u32 *)&sSliderChannels.g, 0, 255, djui_panel_theme_editor_edit_theme_slider_changed);
        djui_base_set_color(&sSliderG->rectValue->base, 0, 255, 0, 255);
        djui_base_set_gradient(&sSliderG->rectValue->base, false);
        djui_base_set_gradient(&sSliderG->rect->base, false);
        sSliderG->updateRectValueColor = false;
        djui_slider_update_style(&sSliderG->base);
        sSliderB = djui_slider_create(body, DLANG(DJUI_THEMES, BLUE), (u32 *)&sSliderChannels.b, 0, 255, djui_panel_theme_editor_edit_theme_slider_changed);
        djui_base_set_color(&sSliderB->rectValue->base, 0, 0, 255, 255);
        djui_base_set_gradient(&sSliderB->rectValue->base, false);
        djui_base_set_gradient(&sSliderB->rect->base, false);
        sSliderB->updateRectValueColor = false;
        djui_slider_update_style(&sSliderB->base);
        sSliderA = djui_slider_create(body, DLANG(DJUI_THEMES, ALPHA), (u32 *)&sSliderChannels.a, 0, 255, djui_panel_theme_editor_edit_theme_slider_changed);
        djui_base_set_color(&sSliderA->rectValue->base, 220, 220, 220, 255);
        djui_slider_update_style(&sSliderA->base);
        djui_panel_theme_editor_edit_theme_update_sliders();

        sColorRect = djui_rect_create(body);
        djui_base_set_size_type(&sColorRect->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sColorRect->base, 1.0f, 32);
        djui_base_set_color(&sColorRect->base, sSliderChannels.r, sSliderChannels.g, sSliderChannels.b, sSliderChannels.a);
        djui_base_set_gradient(&sColorRect->base, false);
        djui_base_set_border_width(&sColorRect->base, 2);
        djui_base_set_border_color(&sColorRect->base, 173, 173, 173, 255);

        djui_panel_theme_editor_header_font_set_selected(configDjuiTheme.headerFont);
        char *djuiHeaderFontChoices[7] = {
            DLANG(DJUI_THEMES, FONT_NORMAL),
            DLANG(DJUI_THEMES, FONT_MENU),
            DLANG(DJUI_THEMES, FONT_MENU_DARK),
            DLANG(DJUI_THEMES, FONT_CUSTOM_HUD),
            DLANG(DJUI_THEMES, FONT_ALIASED),
            DLANG(DJUI_THEMES, FONT_SPECIAL),
            DLANG(DJUI_THEMES, FONT_CLASSIC)
        };
        sSelectionboxes[sSelectionboxesCount++] = djui_selectionbox_create(body, DLANG(DJUI_THEMES, HEADER_FONT), djuiHeaderFontChoices, 7, &sDjuiHeaderFontSelected, djui_panel_theme_editor_header_font_setting_change);

        sCheckboxes[sCheckboxesCount++] = djui_checkbox_create(body, DLANG(DJUI_THEMES, USE_RAINBOW), &configDjuiTheme.useRainbowColor, djui_panel_theme_editor_reload);
        sCheckboxes[sCheckboxesCount++] = djui_checkbox_create(body, DLANG(DJUI_THEMES, GRADIENTS), &configDjuiTheme.gradients, djui_panel_theme_editor_reload);

        struct DjuiRect *rect2 = djui_rect_container_create(body, 32);
        {
            struct DjuiText *text1 = djui_text_create(&rect2->base, DLANG(DJUI_THEMES, THEME_NAME));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color_with_color(&text1->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_TEXT]);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text1, 64, 64, 64, 100);
            sTexts[sTextsCount++] = text1;

            sThemeNameTextBox = djui_inputbox_create(&rect2->base, 32);
            djui_inputbox_set_text(sThemeNameTextBox, djui_panel_theme_editor_edit_theme_name_get_text());
            djui_base_set_size_type(&sThemeNameTextBox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&sThemeNameTextBox->base, 0.45f, 32);
            djui_base_set_alignment(&sThemeNameTextBox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_interactable_hook_value_change(&sThemeNameTextBox->base, djui_panel_theme_editor_edit_theme_name_text_change);
            djui_interactable_hook_focus(&sThemeNameTextBox->base, djui_inputbox_on_focus_begin, NULL, djui_panel_theme_editor_edit_theme_name_on_focus_end);
        }

        struct DjuiRect *rect3 = djui_rect_container_create(body, 64);
        {
            sButtons[sButtonsCount++] = djui_button_left_create(&rect3->base, DLANG(MENU, CANCEL), DJUI_BUTTON_STYLE_SECONDARY, djui_panel_theme_editor_cancel);
            sButtons[sButtonsCount++] = djui_button_right_create(&rect3->base, DLANG(DJUI_THEMES, SAVE_THEME), DJUI_BUTTON_STYLE_PRIMARY, djui_panel_theme_editor_edit_theme_save);
        }
    }
    panel->on_back = djui_panel_theme_editor_on_back;

    djui_panel_add(caller, panel, NULL);
}
