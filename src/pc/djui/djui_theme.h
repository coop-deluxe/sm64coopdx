#pragma once
#include "djui.h"

#define DJUI_THEME_CENTERED_WIDTH 1.3f
#define DJUI_THEME_CENTERED_HEIGHT 0.9f

enum DjuiThemeType {
    DJUI_THEME_LIGHT,
    DJUI_THEME_DARK,
    DJUI_THEME_FILE_SELECT,
    DJUI_THEME_MARIO,
    DJUI_THEME_ODYSSEY,
    DJUI_THEME_MAX
};

struct DjuiInteractableTheme {
    struct DjuiColor textColor;

    struct DjuiColor defaultRectColor;
    struct DjuiColor cursorDownRectColor;
    struct DjuiColor hoveredRectColor;

    struct DjuiColor defaultBorderColor;
    struct DjuiColor cursorDownBorderColor;
    struct DjuiColor hoveredBorderColor;
};

struct DjuiThreePanelTheme {
    struct DjuiColor rectColor;
    struct DjuiColor borderColor;
};

struct DjuiPanelTheme {
    bool hudFontHeader;
};

struct DjuiTheme {
    const char* id;
    const char* name;
    struct DjuiInteractableTheme interactables;
    struct DjuiThreePanelTheme threePanels;
    struct DjuiPanelTheme panels;
};

extern struct DjuiTheme* gDjuiThemes[];

struct DjuiColor djui_theme_shade_color(struct DjuiColor color, f32 mult);
void djui_themes_init(void);
