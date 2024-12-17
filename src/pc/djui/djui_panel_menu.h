#pragma once
#include "djui.h"

enum DjuiRainbowColor {
    DJUI_RAINBOW_COLOR_RED,
    DJUI_RAINBOW_COLOR_GREEN,
    DJUI_RAINBOW_COLOR_BLUE,
    DJUI_RAINBOW_COLOR_YELLOW
};

/* |description|Gets the header hex color code from a `DJUI_RAINBOW_COLOR_*` constant|descriptionEnd| */
char* djui_menu_get_rainbow_string_color(enum DjuiRainbowColor color);
void djui_panel_menu_back(struct DjuiBase* base);
struct DjuiThreePanel* djui_panel_menu_create(char* headerText, bool forcedLeftSide);
