#pragma once
#include "djui.h"

#define THEMES_DIRECTORY "themes"
#define MAX_DJUI_THEME_NAME_LEN 64
#define MAX_DJUI_THEMES 64
#define DJUI_THEME_CENTERED_WIDTH 1.3f
#define DJUI_THEME_CENTERED_HEIGHT 0.921f

enum DjuiBuiltinThemes {
    DJUI_THEME_LIGHT,
    DJUI_THEME_DARK,
    DJUI_THEME_COUNT
};

enum DjuiThemeElements {
    #define DEFINE_THEME_ELEMENT(name) name,
    #include "src/pc/djui/djui_theme_elements.inl"
    #undef DEFINE_THEME_ELEMENT
    DJUI_THEME_ELEMENT_COUNT,
};

struct DjuiDeprecatedTheme {
    PROPERTY(textColor,             djui_theme_get_text_color,               NULL);
    PROPERTY(defaultRectColor,      djui_theme_get_default_rect_color,       NULL);
    PROPERTY(cursorDownRectColor,   djui_theme_get_cursor_down_rect_color,   NULL);
    PROPERTY(hoveredRectColor,      djui_theme_get_hovered_rect_color,       NULL);
    PROPERTY(defaultBorderColor,    djui_theme_get_default_border_color,     NULL);
    PROPERTY(cursorDownBorderColor, djui_theme_get_cursor_down_border_color, NULL);
    PROPERTY(hoveredBorderColor,    djui_theme_get_hovered_border_color,     NULL);
    PROPERTY(rectColor,             djui_theme_get_rect_color,               NULL);
    PROPERTY(borderColor,           djui_theme_get_border_color,             NULL);
    PROPERTY(hudFontHeader,         djui_theme_get_hud_font_header,          NULL);
    bool unused; // needed to keep the compiler happy
};

struct DjuiTheme {
    char name[MAX_DJUI_THEME_NAME_LEN];
    char path[SYS_MAX_PATH];
    C_ARRAY struct DjuiColor elements[DJUI_THEME_ELEMENT_COUNT];
    u32 headerFont;
    bool useRainbowColor;
    bool gradients;
    struct DjuiDeprecatedTheme interactables;
    struct DjuiDeprecatedTheme threePanels;
    struct DjuiDeprecatedTheme panels;
};

extern struct GrowingArray *gDjuiThemes;
extern struct DjuiTheme gDjuiThemeDark;

struct DjuiColor djui_theme_shade_color(struct DjuiColor color, f32 mult);
bool djui_themes_save(struct DjuiTheme *theme);
void djui_theme_load(const char *path);
void djui_themes_load_all(void);
void djui_theme_delete(struct DjuiTheme *theme);
void djui_theme_init(void);
/* |description|Gets the color of the `DJUI_THEME_ELEMENT_TEXT` of the current menu theme|descriptionEnd| */
struct DjuiColor *djui_theme_get_text_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
/* |description|Gets the color of the `DJUI_THEME_ELEMENT_PRIMARY` of the current menu theme|descriptionEnd| */
struct DjuiColor *djui_theme_get_default_rect_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
/* |description|Gets the color of the `DJUI_THEME_ELEMENT_PRIMARY_DOWN` of the current menu theme|descriptionEnd| */
struct DjuiColor *djui_theme_get_cursor_down_rect_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
/* |description|Gets the color of the `DJUI_THEME_ELEMENT_PRIMARY_HOVER` of the current menu theme|descriptionEnd| */
struct DjuiColor *djui_theme_get_hovered_rect_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
/* |description|Gets the color of the `DJUI_THEME_ELEMENT_PRIMARY_BORDER` of the current menu theme|descriptionEnd| */
struct DjuiColor *djui_theme_get_default_border_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
/* |description|Gets the color of the `DJUI_THEME_ELEMENT_PRIMARY_BORDER_DOWN` of the current menu theme|descriptionEnd| */
struct DjuiColor *djui_theme_get_cursor_down_border_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
/* |description|Gets the color of the `DJUI_THEME_ELEMENT_PRIMARY_BORDER_HOVER` of the current menu theme|descriptionEnd| */
struct DjuiColor *djui_theme_get_hovered_border_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
/* |description|Gets the color of the `DJUI_THEME_ELEMENT_THREE_PANEL` of the current menu theme|descriptionEnd| */
struct DjuiColor *djui_theme_get_rect_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
/* |description|Gets the color of the `DJUI_THEME_ELEMENT_THREE_PANEL_BORDER` of the current menu theme|descriptionEnd| */
struct DjuiColor *djui_theme_get_border_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
/* |description|Gets whether header font of the theme is `FONT_HUD`|descriptionEnd| */
bool djui_theme_get_hud_font_header(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme);
