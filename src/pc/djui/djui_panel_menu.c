#include "djui.h"
#include "djui_panel.h"
#include "djui_unicode.h"
#include "djui_panel_menu.h"
#include "djui_hud_utils.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"

#define RAINBOW_TEXT_LEN 300

char* sRainbowColors[] = {
    "\\#ff3030\\",
    "\\#40e740\\",
    "\\#40b0ff\\",
    "\\#ffef40\\",
};

char* sExCoopRainbowColors[] = {
    "\\#ff0800\\",
    "\\#1be700\\",
    "\\#00b3ff\\",
    "\\#ffef00\\",
};

char sRainbowText[RAINBOW_TEXT_LEN + 1] = { 0 };

char* generate_rainbow_text(char* text) {
    char* src = text;
    char* dst = sRainbowText;
    char tmpChar[10] = { 0 };
    int i = 0;
    *dst = '\0';
    while (*src) {
        if (*src == '\\') {
            snprintf(sRainbowText, RAINBOW_TEXT_LEN, "%s", text);
            return sRainbowText;
        }
        s32 restrictSize = RAINBOW_TEXT_LEN - (s32)(dst - sRainbowText);
        if (restrictSize <= 0) { break; }
        snprintf(dst, restrictSize, "%s", configExCoopTheme ? sExCoopRainbowColors[i++ % 4] : sRainbowColors[i++ % 4]);
        dst = &sRainbowText[strlen(sRainbowText)];

        restrictSize = RAINBOW_TEXT_LEN - (s32)(dst - sRainbowText);
        if (restrictSize <= 0) { break; }

        djui_unicode_get_char(src, tmpChar);
        snprintf(dst, restrictSize, "%s", tmpChar);
        dst = &sRainbowText[strlen(sRainbowText)];

        src = djui_unicode_next_char(src);
    }

    return sRainbowText;
}

char* djui_menu_get_rainbow_string_color(enum DjuiRainbowColor color) {
    int i = (color >= 0 && color <= 3) ? color : 0;
    return configExCoopTheme ? sExCoopRainbowColors[i] : sRainbowColors[i];
}

void djui_panel_menu_back(UNUSED struct DjuiBase* base) {
    djui_panel_back();
}

struct DjuiThreePanel* djui_panel_menu_create(char* headerText, bool forcedLeftSide) {
    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, 0, 0);
    bool center = !forcedLeftSide && configDjuiThemeCenter;
    f32 widthMultiplier = center ? DJUI_THEME_CENTERED_WIDTH : 1.0f;
    f32 heightMultiplier = center ? DJUI_THEME_CENTERED_HEIGHT : 1.0f;

    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, DJUI_DEFAULT_PANEL_WIDTH * widthMultiplier, heightMultiplier);
    djui_base_set_color_with_color(&panel->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_THREE_PANEL]);
    djui_base_set_border_color_with_color(&panel->base, configDjuiTheme.elements[DJUI_THEME_ELEMENT_THREE_PANEL_BORDER]);
    if (center) djui_base_set_alignment(&panel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    {
        u8 headerFont = configDjuiTheme.headerFont;
        bool useRainbowColor = configDjuiTheme.useRainbowColor;
        struct DjuiColor headerColor = configDjuiTheme.elements[DJUI_THEME_ELEMENT_PANEL_HEADER_COLOR];
        if (useRainbowColor) generate_rainbow_text(headerText);
        struct DjuiText* header = djui_text_create(&panel->base, useRainbowColor ? sRainbowText : headerText);
        djui_base_set_size_type(&header->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&header->base, 1.0f, 1.0f);
        if (!useRainbowColor) {
            djui_base_set_color(&header->base, headerColor.r, headerColor.g, headerColor.b, headerColor.a);
        } else {
            djui_base_set_color(&header->base, 255, 8, 0, 255);
        }
        djui_base_set_location(&header->base, 0, DJUI_PANEL_HEADER_OFFSET);
        djui_text_set_alignment(header, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
        djui_text_set_font(header, gDjuiFonts[headerFont]);
        // if only we had unified font sizes and I didn't have to do this hack
        djui_text_set_font_scale(header, headerFont == FONT_CUSTOM_HUD ? 96 : 64);

        struct DjuiFlowLayout* body = djui_flow_layout_create(&panel->base);
        djui_base_set_alignment(&body->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&body->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&body->base, 1.0f, 0);
        djui_base_set_color(&body->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(body, 16);
        djui_flow_layout_set_flow_direction(body, DJUI_FLOW_DIR_DOWN);
    }
    return panel;
}
