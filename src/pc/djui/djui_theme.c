#include "djui.h"
#include "djui_hud_utils.h"
#include "pc/debuglog.h"
#include "pc/mods/mod.h"
#include "pc/mods/mods_utils.h"
#include "pc/utils/misc.h"

static struct DjuiTheme sDjuiThemeLight = {
    .name = "LIGHT_THEME",
    .elements = {
        [DJUI_THEME_ELEMENT_PRIMARY] = {222, 222, 222, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_HOVER] = {229, 241, 251, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_DOWN] = {204, 228, 247, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_DISABLED] = {111, 111, 111, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_TEXT] = {11, 11, 11, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_TEXT_DISABLED] = {5, 5, 5, 255},

        [DJUI_THEME_ELEMENT_PRIMARY_BORDER] = {150, 150, 150, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_BORDER_HOVER] = {0, 120, 215, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_BORDER_DOWN] = {0, 84, 153, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_BORDER_DISABLED] = {75, 75, 75, 255},

        [DJUI_THEME_ELEMENT_SECONDARY] = {150, 150, 150, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_HOVER] = {209, 221, 231, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_DOWN] = {184, 208, 227, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_DISABLED] = {75, 75, 75, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_TEXT] = {11, 11, 11, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_TEXT_DISABLED] = {5, 5, 5, 255},

        [DJUI_THEME_ELEMENT_SECONDARY_BORDER] = {100, 100, 100, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_BORDER_HOVER] = {0, 100, 200, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_BORDER_DOWN] = {0, 74, 143, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_BORDER_DISABLED] = {50, 50, 50, 255},

        [DJUI_THEME_ELEMENT_INPUTBOX] = {240, 240, 240, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_HOVER] = {250, 250, 250, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_DOWN] = {255, 255, 255, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_DISABLED] = {140, 140, 140, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_TEXT] = {0, 0, 0, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_TEXT_PLACEHOLDER] = {120, 120, 120, 255},

        [DJUI_THEME_ELEMENT_INPUTBOX_BORDER] = {150, 150, 150, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_BORDER_HOVER] = {0, 120, 215, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_BORDER_DOWN] = {0, 84, 153, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_BORDER_DISABLED] = {75, 75, 75, 255},

        [DJUI_THEME_ELEMENT_CHECKBOX] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_HOVER] = {229, 241, 251, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_DOWN] = {255, 255, 255, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_DISABLED] = {100, 100, 100, 255},

        [DJUI_THEME_ELEMENT_CHECKBOX_BORDER] = {173, 173, 173, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_BORDER_HOVER] = {0, 120, 215, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_BORDER_DOWN] = {20, 170, 255, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_BORDER_DISABLED] = {93, 93, 93, 255},

        [DJUI_THEME_ELEMENT_SLIDER] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_SLIDER_HOVER] = {229, 241, 251, 255},
        [DJUI_THEME_ELEMENT_SLIDER_DOWN] = {255, 255, 255, 255},
        [DJUI_THEME_ELEMENT_SLIDER_DISABLED] = {100, 100, 100, 255},

        [DJUI_THEME_ELEMENT_SLIDER_BORDER] = {173, 173, 173, 255},
        [DJUI_THEME_ELEMENT_SLIDER_BORDER_HOVER] = {0, 120, 215, 255},
        [DJUI_THEME_ELEMENT_SLIDER_BORDER_DOWN] = {20, 170, 255, 255},
        [DJUI_THEME_ELEMENT_SLIDER_BORDER_DISABLED] = {93, 93, 93, 255},

        [DJUI_THEME_ELEMENT_TEXT] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_TEXT_DISABLED] = {200, 200, 200, 255},

        [DJUI_THEME_ELEMENT_SELECTIONBOX_IMAGE] = {11, 11, 11, 255},
        [DJUI_THEME_ELEMENT_SELECTIONBOX_IMAGE_DISABLED] = {5, 5, 5, 255},

        [DJUI_THEME_ELEMENT_THREE_PANEL] = {0, 0, 0, 230},
        [DJUI_THEME_ELEMENT_THREE_PANEL_BORDER] = {0, 0, 0, 200},

        [DJUI_THEME_ELEMENT_PANEL_HEADER_COLOR] = {220, 220, 220, 255},
    },
    .headerFont = FONT_MENU,
    .useRainbowColor = true,
    .gradients = false,
};

struct DjuiTheme gDjuiThemeDark = {
    .name = "DARK_THEME",
    .elements = {
        [DJUI_THEME_ELEMENT_PRIMARY] = {22, 22, 22, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_HOVER] = {80, 80, 80, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_DOWN] = {100, 100, 100, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_DISABLED] = {15, 15, 15, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_TEXT] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_TEXT_DISABLED] = {100, 100, 100, 255},

        [DJUI_THEME_ELEMENT_PRIMARY_BORDER] = {75, 75, 75, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_BORDER_HOVER] = {0, 120, 215, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_BORDER_DOWN] = {0, 84, 153, 255},
        [DJUI_THEME_ELEMENT_PRIMARY_BORDER_DISABLED] = {40, 40, 40, 255},

        [DJUI_THEME_ELEMENT_SECONDARY] = {12, 12, 12, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_HOVER] = {50, 50, 50, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_DOWN] = {60, 60, 60, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_DISABLED] = {7, 7, 7, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_TEXT] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_TEXT_DISABLED] = {100, 100, 100, 255},

        [DJUI_THEME_ELEMENT_SECONDARY_BORDER] = {30, 30, 30, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_BORDER_HOVER] = {0, 120, 215, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_BORDER_DOWN] = {0, 84, 153, 255},
        [DJUI_THEME_ELEMENT_SECONDARY_BORDER_DISABLED] = {40, 40, 40, 255},

        [DJUI_THEME_ELEMENT_INPUTBOX] = {22, 22, 22, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_HOVER] = {80, 80, 80, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_DOWN] = {100, 100, 100, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_DISABLED] = {15, 15, 15, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_TEXT] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_TEXT_PLACEHOLDER] = {130, 130, 130, 255},

        [DJUI_THEME_ELEMENT_INPUTBOX_BORDER] = {75, 75, 75, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_BORDER_HOVER] = {0, 120, 215, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_BORDER_DOWN] = {0, 84, 153, 255},
        [DJUI_THEME_ELEMENT_INPUTBOX_BORDER_DISABLED] = {40, 40, 40, 255},

        [DJUI_THEME_ELEMENT_CHECKBOX] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_HOVER] = {229, 241, 251, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_DOWN] = {255, 255, 255, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_DISABLED] = {100, 100, 100, 255},

        [DJUI_THEME_ELEMENT_CHECKBOX_BORDER] = {173, 173, 173, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_BORDER_HOVER] = {0, 120, 215, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_BORDER_DOWN] = {20, 170, 255, 255},
        [DJUI_THEME_ELEMENT_CHECKBOX_BORDER_DISABLED] = {93, 93, 93, 255},

        [DJUI_THEME_ELEMENT_SLIDER] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_SLIDER_HOVER] = {229, 241, 251, 255},
        [DJUI_THEME_ELEMENT_SLIDER_DOWN] = {255, 255, 255, 255},
        [DJUI_THEME_ELEMENT_SLIDER_DISABLED] = {100, 100, 100, 255},

        [DJUI_THEME_ELEMENT_SLIDER_BORDER] = {173, 173, 173, 255},
        [DJUI_THEME_ELEMENT_SLIDER_BORDER_HOVER] = {0, 120, 215, 255},
        [DJUI_THEME_ELEMENT_SLIDER_BORDER_DOWN] = {20, 170, 255, 255},
        [DJUI_THEME_ELEMENT_SLIDER_BORDER_DISABLED] = {93, 93, 93, 255},

        [DJUI_THEME_ELEMENT_TEXT] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_TEXT_DISABLED] = {100, 100, 100, 255},

        [DJUI_THEME_ELEMENT_SELECTIONBOX_IMAGE] = {220, 220, 220, 255},
        [DJUI_THEME_ELEMENT_SELECTIONBOX_IMAGE_DISABLED] = {100, 100, 100, 255},

        [DJUI_THEME_ELEMENT_THREE_PANEL] = {0, 0, 0, 230},
        [DJUI_THEME_ELEMENT_THREE_PANEL_BORDER] = {0, 0, 0, 200},

        [DJUI_THEME_ELEMENT_PANEL_HEADER_COLOR] = {220, 220, 220, 255},
    },
    .headerFont = FONT_MENU,
    .useRainbowColor = true,
    .gradients = true,
};

struct GrowingArray *gDjuiThemes = NULL;

char *sDjuiThemeElementKeys[DJUI_THEME_ELEMENT_COUNT] = {
    #define DEFINE_THEME_ELEMENT(name) #name,
    #include "djui_theme_elements.inl"
    #undef DEFINE_THEME_ELEMENT
};

struct DjuiColor djui_theme_shade_color(struct DjuiColor color, f32 mult) {
    color.r *= mult;
    color.g *= mult;
    color.b *= mult;
    return color;
}

static bool djui_theme_theme_elements_equivalent(struct DjuiTheme *themeOne, struct DjuiTheme *themeTwo) {
    if (themeOne->headerFont != themeTwo->headerFont) {
        return false;
    }

    if (themeOne->useRainbowColor != themeTwo->useRainbowColor) {
        return false;
    }

    if (themeOne->gradients != themeTwo->gradients) {
        return false;
    }

    if (memcmp(themeOne->elements, themeTwo->elements, sizeof(themeOne->elements)) != 0) {
        return false;
    }

    return true;
}

bool djui_themes_save(struct DjuiTheme *theme) {
    // validate theme and name
    if (!theme || theme->name[0] == '\0') {
        LOG_ERROR("Failed to save theme: theme is either NULL or the name is empty!");
        return false;
    }

    // get target file path to write to
    const char *themesPath = fs_get_write_path(THEMES_DIRECTORY);
    char targetThemePath[SYS_MAX_PATH] = "";
    snprintf(targetThemePath, SYS_MAX_PATH, "%s/%s.json", themesPath, theme->name);
    fs_sys_mkdir(themesPath);

    // if the target path and current theme path are not equivalent, nuke the old file and
    // write a new file
    if (strcmp(theme->path, targetThemePath) != 0) {
        if (fs_sys_file_exists(theme->path)) {
            remove(theme->path);
        }

        // if this file already exists, that means another theme used it before
        // look for a unique name and use that
        if (fs_sys_file_exists(targetThemePath)) {
            u32 uniqueIdentifier = 2;
            do {
                snprintf(targetThemePath, SYS_MAX_PATH, "%s/%s-%u.json", themesPath, theme->name, uniqueIdentifier);
                uniqueIdentifier++;
            } while (fs_sys_file_exists(targetThemePath));
        }

        // set our theme path
        snprintf(theme->path, SYS_MAX_PATH, "%s", targetThemePath);
    }

    LOG_INFO("Saving theme to '%s'", theme->path);

    // create json doc
    yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
    if (!doc) {
        LOG_ERROR("Failed to create JSON doc for theme %s", theme->name);
        return false;
    }

    // create root
    yyjson_mut_val *root = yyjson_mut_obj(doc);
    yyjson_mut_doc_set_root(doc, root);

    // add basic theme values
    yyjson_mut_obj_add_str(doc, root, "name", theme->name);
    yyjson_mut_obj_add_uint(doc, root, "headerFont", theme->headerFont);
    yyjson_mut_obj_add_bool(doc, root, "useRainbowColor", theme->useRainbowColor);
    yyjson_mut_obj_add_bool(doc, root, "gradients", theme->gradients);

    // add theme elements
    yyjson_mut_val *elementsObj = yyjson_mut_obj(doc);
    for (int i = 0; i < DJUI_THEME_ELEMENT_COUNT; i++) {
        char hexColor[10];
        snprintf(hexColor, sizeof(hexColor), "#%02x%02x%02x%02x", theme->elements[i].r, theme->elements[i].g, theme->elements[i].b, theme->elements[i].a);

        yyjson_mut_obj_add_strcpy(doc, elementsObj, sDjuiThemeElementKeys[i], hexColor);
    }
    yyjson_mut_obj_add_val(doc, root, "elements", elementsObj);

    // write json to file
    yyjson_write_err err;
    bool success = yyjson_mut_write_file(theme->path, doc, YYJSON_WRITE_PRETTY, NULL, &err);
    yyjson_mut_doc_free(doc);

    if (!success) {
        LOG_ERROR("Failed to write JSON file for theme %s: %s", theme->name, err.msg);
        return false;
    }

    return true;
}

void djui_theme_load(const char *path) {
    // load json from path
    yyjson_doc *doc = get_yyjson_doc_from_path(path);
    if (!doc) {
        LOG_ERROR("Failed to load theme '%s'\n", path);
        return;
    }
    yyjson_val *root = yyjson_doc_get_root(doc);

    // allocate theme
    struct DjuiTheme *theme = growing_array_alloc(gDjuiThemes, sizeof(struct DjuiTheme));
    if (!theme) { goto CLEANUP; }

    // set theme path
    snprintf(theme->path, SYS_MAX_PATH, "%s", path);

    // get theme name
    const char *name = yyjson_get_str(yyjson_obj_get(root, "name"));
    if (!name) {
        LOG_ERROR("Failed to load theme '%s'\n", path);
        growing_array_swap_and_pop(gDjuiThemes, theme);
        goto CLEANUP;
    }
    snprintf(theme->name, MAX_DJUI_THEME_NAME_LEN, "%s", name);

    // get basic theme values
    theme->headerFont = yyjson_get_uint(yyjson_obj_get(root, "headerFont"));
    if (theme->headerFont >= FONT_COUNT) {
        theme->headerFont = FONT_MENU;
    }
    theme->useRainbowColor = yyjson_get_bool(yyjson_obj_get(root, "useRainbowColor"));
    theme->gradients = yyjson_get_bool(yyjson_obj_get(root, "gradients"));

    // get theme elements
    yyjson_val *elements = yyjson_obj_get(root, "elements");
    if (yyjson_is_obj(elements)) {
        size_t idx, max;
        yyjson_val *keyVal, *colorVal;

        bool loadedKeys[DJUI_THEME_ELEMENT_COUNT] = { 0 };

        // iterate over elements
        yyjson_obj_foreach(elements, idx, max, keyVal, colorVal) {
            // get key and validate color string value
            const char *key = yyjson_get_str(keyVal);
            const char *hexStr = yyjson_get_str(colorVal);
            if (!key || !hexStr) { continue; }

            // skip # if it exists
            if (hexStr[0] == '#') {
                hexStr++;
            }

            // convert hex to rgba
            struct DjuiColor color = { 0 };
            if (sscanf(hexStr, "%02hhx%02hhx%02hhx%02hhx", &color.r, &color.g, &color.b, &color.a) < 4) {
                // bail if we don't have all the necessary colors
                continue;
            }

            // figure out the key and set the color
            for (int i = 0; i < DJUI_THEME_ELEMENT_COUNT; i++) {
                if (sys_strcasecmp(key, sDjuiThemeElementKeys[i]) == 0) {
                    theme->elements[i] = color;
                    loadedKeys[i] = true;
                    break;
                }
            }
        }

        // for every key NOT loaded, set it to the default dark theme
        for (int i = 0; i < DJUI_THEME_ELEMENT_COUNT; i++) {
            if (!loadedKeys[i]) {
                theme->elements[i] = gDjuiThemeDark.elements[i];
            }
        }
    }

    LOG_INFO("Loaded theme %s", theme->name);

    if (djui_theme_theme_elements_equivalent(theme, &configDjuiTheme)) {
        configDjuiTheme = *theme; // sets name and path to be equivalent
    }

CLEANUP:
    yyjson_doc_free(doc);
}

void djui_themes_load_all() {
    const char *directoryPath = fs_get_write_path(THEMES_DIRECTORY);

    // open themes directory
    struct dirent *dir = NULL;

    DIR *d = opendir(directoryPath);
    if (!d) { return; }

    // iterate through dir
    char path[SYS_MAX_PATH] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        // sanity check / fill path[]
        if (!directory_sanity_check(dir, (char *)directoryPath, path)) { continue; }
        if (strlen(path) == 0) { continue; } // sanity check length

        // load theme
        djui_theme_load(path);
    }
    closedir(d);
}

void djui_theme_delete(struct DjuiTheme *theme) {
    if (theme == NULL) { return; }

    // if somehow the count is lower than the builtin theme count, return, something
    // has gone wrong
    if (gDjuiThemes->count < DJUI_THEME_COUNT) { return; }

    // store theme path for later
    char themePath[SYS_MAX_PATH];
    snprintf(themePath, SYS_MAX_PATH, "%s", theme->path);

    // start iterating after the builtin themes, so custom themes
    for (u32 i = DJUI_THEME_COUNT; i < gDjuiThemes->count; i++) {
        if (!gDjuiThemes->buffer[i]) { return; }
        // make sure they are equivalent
        if (memcmp(theme, gDjuiThemes->buffer[i], sizeof(struct DjuiTheme)) != 0) { continue; }
        // if the current theme and the config theme are the same, move the config theme to the
        // previous valid theme
        if (memcmp(theme, &configDjuiTheme, sizeof(struct DjuiTheme)) == 0) {
            // this will always hit a valid index because builtin themes exist, so no OOB
            // check is needed
            memcpy(&configDjuiTheme, gDjuiThemes->buffer[i - 1], sizeof(struct DjuiTheme));
        }
        // remove theme
        growing_array_swap_and_pop_index(gDjuiThemes, i);
        theme = NULL;
        break;
    }

    // delete file if it exists
    if (!fs_sys_file_exists(themePath)) { return; }
    remove(themePath);
}

void djui_theme_init(void) {
    // initialize growing array
    gDjuiThemes = growing_array_init(gDjuiThemes, 2, malloc, free);

    // allocate default light theme
    struct DjuiTheme *lightTheme = growing_array_alloc(gDjuiThemes, sizeof(struct DjuiTheme));
    if (!lightTheme) {
        sys_fatal("Failed to allocate memory for builtin DJUI light theme!");
    }
    memcpy(lightTheme, &sDjuiThemeLight, sizeof(struct DjuiTheme));

    // allocate default dark theme
    struct DjuiTheme *darkTheme = growing_array_alloc(gDjuiThemes, sizeof(struct DjuiTheme));
    if (!darkTheme) {
        sys_fatal("Failed to allocate memory for builtin DJUI dark theme!");
    }
    memcpy(darkTheme, &gDjuiThemeDark, sizeof(struct DjuiTheme));

    // load all custom themes
    djui_themes_load_all();
}

struct DjuiColor *djui_theme_get_text_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return &configDjuiTheme.elements[DJUI_THEME_ELEMENT_TEXT];
}

struct DjuiColor *djui_theme_get_default_rect_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return &configDjuiTheme.elements[DJUI_THEME_ELEMENT_PRIMARY];
}

struct DjuiColor *djui_theme_get_cursor_down_rect_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return &configDjuiTheme.elements[DJUI_THEME_ELEMENT_PRIMARY_DOWN];
}

struct DjuiColor *djui_theme_get_hovered_rect_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return &configDjuiTheme.elements[DJUI_THEME_ELEMENT_PRIMARY_HOVER];
}

struct DjuiColor *djui_theme_get_default_border_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return &configDjuiTheme.elements[DJUI_THEME_ELEMENT_PRIMARY_BORDER];
}

struct DjuiColor *djui_theme_get_cursor_down_border_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return &configDjuiTheme.elements[DJUI_THEME_ELEMENT_PRIMARY_BORDER_DOWN];
}

struct DjuiColor *djui_theme_get_hovered_border_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return &configDjuiTheme.elements[DJUI_THEME_ELEMENT_PRIMARY_BORDER_HOVER];
}

struct DjuiColor *djui_theme_get_rect_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return &configDjuiTheme.elements[DJUI_THEME_ELEMENT_THREE_PANEL];
}

struct DjuiColor *djui_theme_get_border_color(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return &configDjuiTheme.elements[DJUI_THEME_ELEMENT_THREE_PANEL_BORDER];
}

bool djui_theme_get_hud_font_header(UNUSED struct DjuiDeprecatedTheme *deprecatedTheme) {
    return configDjuiTheme.headerFont == FONT_CUSTOM_HUD;
}
