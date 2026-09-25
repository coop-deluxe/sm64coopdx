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

static struct DjuiFlowLayout *sLayout = NULL;
static struct DjuiPaginated *sPaginated = NULL;
static struct DjuiSearchbox *sSearchbox = NULL;
static struct DjuiInputbox *sSearchInputbox = NULL;

// these allocated statically, raise this if needed
static struct DjuiButton *sButtons[8] = { NULL };
static u32 sButtonsCount = 0;
static struct DjuiSelectionbox *sSelectionboxes[8] = { NULL };
static unsigned int sSelectionboxesCount = 0;

static u32 sDjuiFontSelected = 0;
static u32 sDeleteThemeIndex = 0;

  //////////////////////////
 // forward declarations //
//////////////////////////

static void djui_panel_themes_reload_list(UNUSED struct DjuiBase *caller);
void djui_panel_themes_create(UNUSED struct DjuiBase *caller);

static void djui_panel_themes_reset_djui_tree(void) {
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
}

static bool djui_panel_themes_on_back(UNUSED struct DjuiBase *caller) {
    djui_panel_themes_reset_djui_tree();
    return false;
}

static void djui_panel_themes_refresh(void) {
    djui_inputbox_update_style(&sSearchInputbox->base);
    djui_inputbox_reset_text_color(sSearchInputbox);
    djui_base_set_gradient(&sSearchInputbox->base, configDjuiTheme.gradients);

    djui_base_set_color_with_color(&sSearchbox->text->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_TEXT_DISABLED]);
    djui_text_set_font(sSearchbox->text, gDjuiFonts[configDjuiThemeFont]);

    // refresh djui elements
    for (u32 i = 0; i < sButtonsCount; i++) {
        if (!sButtons[i]) { continue; }
        djui_button_update_style(&sButtons[i]->base);
        djui_base_set_gradient(&sButtons[i]->rect->base, configDjuiTheme.gradients);
        djui_text_set_font(sButtons[i]->text, gDjuiFonts[configDjuiThemeFont]);
    }

    for (u32 i = 0; i < sSelectionboxesCount; i++) {
        if (!sSelectionboxes[i]) { continue; }
        djui_selectionbox_update_style(&sSelectionboxes[i]->base);
        djui_selectionbox_update_value(&sSelectionboxes[i]->base);
        djui_base_set_gradient(&sSelectionboxes[i]->rect->base, configDjuiTheme.gradients);
        djui_text_set_font(sSelectionboxes[i]->text, gDjuiFonts[configDjuiThemeFont]);
        djui_text_set_font(sSelectionboxes[i]->rectText, gDjuiFonts[configDjuiThemeFont]);
    }

    djui_panel_themes_reload_list(NULL);
}

static void djui_panel_themes_select(struct DjuiBase *caller) {
    if (caller->tag < 0 || caller->tag >= gDjuiThemes->count || !gDjuiThemes->buffer[caller->tag]) { return; }
    configDjuiTheme = *(struct DjuiTheme *)gDjuiThemes->buffer[caller->tag];
    djui_panel_themes_refresh();
}

static void djui_panel_themes_erase(UNUSED struct DjuiBase *caller) {
    if (sDeleteThemeIndex < DJUI_THEME_COUNT || sDeleteThemeIndex >= gDjuiThemes->count) { return; }
    djui_theme_delete(gDjuiThemes->buffer[sDeleteThemeIndex]);
    sDeleteThemeIndex = 0;
    djui_panel_themes_reset_djui_tree();
}

static void djui_panel_themes_erase_confirm(struct DjuiBase *caller) {
    if (caller->tag < DJUI_THEME_COUNT || caller->tag >= gDjuiThemes->count || !gDjuiThemes->buffer[caller->tag]) { return; }
    sDeleteThemeIndex = caller->tag;
    djui_panel_confirm_create(caller, DLANG(DJUI_THEMES, DELETE_THEME_TITLE), DLANG(DJUI_THEMES, WARN_DELETE_THEME), djui_panel_themes_erase);
}

static void djui_panel_themes_add_themes(struct DjuiBase *base) {
    for (u32 i = 0; i < gDjuiThemes->count; i++) {
        struct DjuiTheme *theme = gDjuiThemes->buffer[i];
        if (!theme) { continue; }

        // filter results
        if (sSearchInputbox != NULL &&
            sSearchInputbox->buffer != NULL &&
            !strstr_lowercased(djui_text_get_uncolored_string(NULL, strlen(theme->name) + 1, theme->name), sSearchInputbox->buffer)
        ) {
            continue;
        }

        struct DjuiRect *rect = djui_rect_container_create(base, 32);
        {
            const char *name = theme->name;
            if (i < DJUI_THEME_COUNT) {
                // get lang entry
                name = djui_language_get("DJUI_THEMES", theme->name);
            }
            struct DjuiButton *buttonSelect = djui_button_create(&rect->base, name, DJUI_BUTTON_STYLE_PRIMARY, djui_panel_themes_select);
            buttonSelect->base.tag = i;
            djui_base_set_size(&buttonSelect->base, 0.6f, 32);
            djui_base_set_enabled(&buttonSelect->base, memcmp(&configDjuiTheme, theme, sizeof(struct DjuiTheme)) != 0);

            struct DjuiButton *buttonDelete = djui_button_create(&rect->base, DLANG(DJUI_THEMES, DELETE_THEME), DJUI_BUTTON_STYLE_PRIMARY, djui_panel_themes_erase_confirm);
            buttonDelete->base.tag = i;
            djui_base_set_size(&buttonDelete->base, 0.19f, 32);
            djui_base_set_alignment(&buttonDelete->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
            djui_base_set_location(&buttonDelete->base, configDjuiThemeCenter ? 127 : buttonSelect->rect->base.width.value + 98, 0);
            djui_base_set_enabled(&buttonDelete->base, (i >= DJUI_THEME_COUNT));

            struct DjuiButton *buttonEdit = djui_button_create(&rect->base, DLANG(DJUI_THEMES, EDIT_THEME), DJUI_BUTTON_STYLE_PRIMARY, djui_panel_theme_editor_create);
            buttonEdit->base.tag = i;
            djui_base_set_size(&buttonEdit->base, 0.19f, 32);
            djui_base_set_alignment(&buttonEdit->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_base_set_enabled(&buttonEdit->base, (i >= DJUI_THEME_COUNT));
        }
    }
}

static void djui_panel_themes_reload_list(UNUSED struct DjuiBase *caller) {
    djui_base_destroy_children(&sLayout->base);
    djui_panel_themes_add_themes(&sLayout->base);
    djui_paginated_calculate_height(sPaginated);
}

static void djui_panel_themes_font_setting_changed(UNUSED struct DjuiBase *caller) {
    u8 djuiFontChoices[4] = {
        FONT_NORMAL,
        FONT_ALIASED,
        FONT_SPECIAL,
        FONT_CLASSIC
    };
    configDjuiThemeFont = djuiFontChoices[sDjuiFontSelected];
    djui_panel_themes_refresh();
}

static bool djui_panel_themes_renderer(struct DjuiBase *base) {
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

void djui_panel_themes_create(UNUSED struct DjuiBase *caller) {
    sButtonsCount = 0;
    sSelectionboxesCount = 0;

    struct DjuiThreePanel *panel = djui_panel_menu_create(DLANG(DJUI_THEMES, THEMES_TITLE), true);
    panel->base.render = djui_panel_themes_renderer;
    struct DjuiBase *body = djui_three_panel_get_body(panel);
    {
        struct DjuiSearchbox *searchbox = djui_searchbox_create(body, djui_panel_themes_reload_list);
        sSearchbox = searchbox;
        sSearchInputbox = searchbox->inputbox;

        struct DjuiPaginated *paginated = djui_paginated_create(body, 8);
        struct DjuiBase *layoutBase = &paginated->layout->base;
        sLayout = paginated->layout;
        djui_panel_themes_add_themes(layoutBase);
        djui_paginated_calculate_height(paginated);
        sPaginated = paginated;

        u8 djuiFontSelectIndexes[FONT_COUNT] = {
            [FONT_NORMAL] = 0,
            [FONT_ALIASED] = 1,
            [FONT_SPECIAL] = 2,
            [FONT_CLASSIC] = 3,
        };
        sDjuiFontSelected = djuiFontSelectIndexes[configDjuiThemeFont];
        char *djuiFontChoices[4] = {
            DLANG(DJUI_THEMES, FONT_NORMAL),
            DLANG(DJUI_THEMES, FONT_ALIASED),
            DLANG(DJUI_THEMES, FONT_SPECIAL),
            DLANG(DJUI_THEMES, FONT_CLASSIC)
        };
        sSelectionboxes[sSelectionboxesCount++] = djui_selectionbox_create(body, DLANG(DJUI_THEMES, DJUI_FONT), djuiFontChoices, 4, &sDjuiFontSelected, djui_panel_themes_font_setting_changed);

        sButtons[sButtonsCount++] = djui_button_create(body, DLANG(DJUI_THEMES, CREATE_THEME), DJUI_BUTTON_STYLE_PRIMARY, djui_panel_theme_editor_create);
        sButtons[sButtonsCount++] = djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_SECONDARY, djui_panel_menu_back);
    }
    panel->on_back = djui_panel_themes_on_back;

    djui_panel_add(caller, panel, NULL);
}
