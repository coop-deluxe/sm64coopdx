#pragma once
#include "djui.h"

enum DjuiThemeType {
    DJUI_THEME_LIGHT,
    DJUI_THEME_DARK,
    DJUI_THEME_LIGHT_CENTERED,
    DJUI_THEME_DARK_CENTERED,
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

    struct DjuiColor darkRectColor;
    struct DjuiColor darkBorderColor;
};

struct DjuiThreePanelTheme {
    struct DjuiColor rectColor;
    struct DjuiColor borderColor;
};

struct DjuiPanelTheme {
    f32 widthMultiplier;
    f32 heightMultiplier;
    bool center;
};

struct DjuiTheme {
    const char* id;
    const char* name;
    struct DjuiInteractableTheme interactables;
    struct DjuiThreePanelTheme threePanels;
    struct DjuiPanelTheme panels;
};

extern struct DjuiTheme* gDjuiThemes[];

void djui_themes_init(void);
