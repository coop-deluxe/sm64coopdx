#include "djui.h"
#include "djui_panel.h"
#include "djui_unicode.h"
#include "djui_panel_menu.h"
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

static void generate_rainbow_text(char* text) {
    char* src = text;
    char* dst = sRainbowText;
    char tmpChar[10] = { 0 };
    int i = 0;
    *dst = '\0';
    while (*src) {
        if (*src == '\\') {
            snprintf(sRainbowText, RAINBOW_TEXT_LEN, "%s", text);
            return;
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
    struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
    struct DjuiThreePanelTheme three = theme->threePanels;
    bool center = !forcedLeftSide && configDjuiThemeCenter;
    f32 widthMultiplier = center ? DJUI_THEME_CENTERED_WIDTH : 1.0f;
    f32 heightMultiplier = center ? DJUI_THEME_CENTERED_HEIGHT : 1.0f;

    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, DJUI_DEFAULT_PANEL_WIDTH * widthMultiplier, heightMultiplier);
    djui_base_set_color(&panel->base, three.rectColor.r, three.rectColor.g, three.rectColor.b, three.rectColor.a);
    djui_base_set_border_color(&panel->base, three.borderColor.r, three.borderColor.g, three.borderColor.b, three.borderColor.a);
    if (center) djui_base_set_alignment(&panel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    {
        bool hudFontHeader = gDjuiThemes[configDjuiTheme]->panels.hudFontHeader;
        if (!hudFontHeader) { generate_rainbow_text(headerText); }
        struct DjuiText* header = djui_text_create(&panel->base, hudFontHeader ? headerText : sRainbowText);
        djui_base_set_size_type(&header->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&header->base, 1.0f, 1.0f);
        if (hudFontHeader) {
            djui_base_set_color(&header->base, 255, 255, 255, 255);
        } else {
            djui_base_set_color(&header->base, 255, 8, 0, 255);
        }
        djui_base_set_location(&header->base, 0, DJUI_PANEL_HEADER_OFFSET);
        djui_text_set_alignment(header, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
        djui_text_set_font(header, hudFontHeader ? gDjuiFonts[2] : gDjuiFonts[1]);
        if (configExCoopTheme) {
            djui_text_set_font_scale(header, gDjuiFonts[1]->defaultFontScale);
        } else {
            djui_text_set_font_scale(header, gDjuiFonts[1]->defaultFontScale * (hudFontHeader ? 0.7f : 1.0f) * (strlen(headerText) > 15 ? 0.9f : 1.0f));
        }

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
