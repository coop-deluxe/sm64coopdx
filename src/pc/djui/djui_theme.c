#include "djui.h"
#include "djui_hud_utils.h"
#include "pc/ini.h"
#include "pc/debuglog.h"
#include "pc/mods/mod.h"
#include "pc/mods/mods_utils.h"

static ini_t* sTheme = NULL;

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

struct DjuiTheme* gDjuiThemes[MAX_DJUI_THEMES] = {
    &sDjuiThemeLight,
    &gDjuiThemeDark,
};

struct DjuiColor djui_theme_shade_color(struct DjuiColor color, f32 mult) {
    color.r *= mult;
    color.g *= mult;
    color.b *= mult;
    return color;
}

int djui_theme_get_next_available_index() {
    for (int i = 0; i < MAX_DJUI_THEMES; i++) {
        if (!gDjuiThemes[i]) return i;
    }
    return -1;
}

static u8 read_value(const char* data) {
    if (data == NULL) { return 0; }
    data = sys_strlwr((char*)data);
    for (size_t i = 0; i < strlen(data); i++) {
        char c = data[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || c == 'x')) {
            return 0;
        }
    }
    return MIN(strtol(data, NULL, 0), 255);
}

static bool theme_ini_init(const char* themeFile) {
    // free old ini
    if (sTheme != NULL) {
        ini_free(sTheme);
        sTheme = NULL;
    }

    // construct path
    char path[SYS_MAX_PATH] = "";
    snprintf(path, SYS_MAX_PATH, "%s/%s.ini", fs_get_write_path(THEMES_DIRECTORY), themeFile);

    // load
    sTheme = ini_load(path);

    return sTheme != NULL;
}

void djui_themes_save_current(bool setThemeArray) {
    struct DjuiTheme* theme = calloc(1, sizeof(struct DjuiTheme));
    memcpy(theme, &configDjuiTheme, sizeof(struct DjuiTheme));
    djui_themes_save(theme, setThemeArray);
}

void djui_themes_save(struct DjuiTheme* theme, bool setThemeArray) {
    int nextAvailableIndex = djui_theme_get_next_available_index();
    if (nextAvailableIndex < 0) {
        LOG_ERROR("Failed to save theme %s. Full on themes!", theme->name);
        return;
    }
    const char* themesPath = fs_get_write_path(THEMES_DIRECTORY);
    char ppath[SYS_MAX_PATH] = "";
    snprintf(ppath, SYS_MAX_PATH, "%s/%s.ini", themesPath, theme->name);
    fs_sys_mkdir(themesPath);

    LOG_INFO("Saving theme as '%s.ini'", theme->name);
    FILE* file = fopen(ppath, "w");
    if (!file) {
        LOG_ERROR("Failed to save theme %s", theme->name);
        return;
    }
    fprintf(file, "[THEME]\n");
    for (int i = 0; i < DJUI_THEME_ELEMENT_COUNT; i++) {
        fprintf(file, "theme_element_%d_r = %d\n", i, theme->elements[i].r);
        fprintf(file, "theme_element_%d_g = %d\n", i, theme->elements[i].g);
        fprintf(file, "theme_element_%d_b = %d\n", i, theme->elements[i].b);
        fprintf(file, "theme_element_%d_a = %d\n", i, theme->elements[i].a);
    }
    fprintf(file, "theme_header_font = %d\n", theme->headerFont);
    fprintf(file, "theme_use_rainbow = %u\n", theme->useRainbowColor ? 1 : 0);
    fprintf(file, "theme_gradients = %u\n", theme->gradients ? 1 : 0);
    fclose(file);

    if (setThemeArray) gDjuiThemes[djui_theme_get_next_available_index()] = theme;
}

void djui_themes_load() {
    const char* directoryPath = fs_get_write_path(THEMES_DIRECTORY);

    // open directory
    struct dirent* dir = NULL;

    DIR* d = opendir(directoryPath);
    if (!d) { return; }

    // iterate
    char path[SYS_MAX_PATH] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        // sanity check / fill path[]
        if (!directory_sanity_check(dir, (char*)directoryPath, path)) continue;
        snprintf(path, SYS_MAX_PATH, "%s", dir->d_name);
        // strip the name before the .
        char* c = path;
        while (*c != '\0') {
            if (*c == '.') { *c = '\0'; break; }
            c++;
        }
        if (strlen(path) == 0) continue;
        if (!theme_ini_init(path)) {
            printf("Failed to load theme '%s.ini'\n", path);
            continue;
        }

        int themeIndex = djui_theme_get_next_available_index();
        if (themeIndex < 0 || themeIndex >= MAX_DJUI_THEMES) continue;
        struct DjuiTheme* theme = calloc(1, sizeof(struct DjuiTheme));
        if (!theme) continue;

        snprintf(theme->name, MAX_DJUI_THEME_NAME_LEN, "%s", path);
        for (int i = 0; i < DJUI_THEME_ELEMENT_COUNT; i++) {
            char key[32];
            snprintf(key, sizeof(key), "theme_element_%d_r", i);
            theme->elements[i].r = read_value(ini_get(sTheme, "THEME", key));
            snprintf(key, sizeof(key), "theme_element_%d_g", i);
            theme->elements[i].g = read_value(ini_get(sTheme, "THEME", key));
            snprintf(key, sizeof(key), "theme_element_%d_b", i);
            theme->elements[i].b = read_value(ini_get(sTheme, "THEME", key));
            snprintf(key, sizeof(key), "theme_element_%d_a", i);
            theme->elements[i].a = read_value(ini_get(sTheme, "THEME", key));
        }
        theme->headerFont = read_value(ini_get(sTheme, "THEME", "theme_header_font"));
        theme->useRainbowColor = read_value(ini_get(sTheme, "THEME", "theme_use_rainbow")) == 1 ? true : false;
        theme->gradients = read_value(ini_get(sTheme, "THEME", "theme_gradients")) == 1 ? true : false;
        gDjuiThemes[themeIndex] = theme;
        LOG_INFO("Loaded theme %s", theme->name);
    }
    closedir(d);
}

void djui_theme_delete(struct DjuiTheme* theme) {
    char filePath[SYS_MAX_PATH] = "";
    snprintf(filePath, SYS_MAX_PATH, "%s/%s.ini", fs_get_write_path(THEMES_DIRECTORY), theme->name);

    // start iterating after the builtin themes
    for (int i = DJUI_THEME_COUNT; i < MAX_DJUI_THEMES; i++) {
        if (!gDjuiThemes[i]) return;
        if (memcmp(theme, gDjuiThemes[i], sizeof(struct DjuiTheme)) != 0) continue;
        if (memcmp(theme, &configDjuiTheme, sizeof(struct DjuiTheme)) == 0) {
            int prevValidIndex = i - 1;
            while (!gDjuiThemes[prevValidIndex]) {
                prevValidIndex--;
            }
            memcpy(&configDjuiTheme, gDjuiThemes[prevValidIndex], sizeof(struct DjuiTheme));
        }
        free(gDjuiThemes[i]);
        gDjuiThemes[i] = NULL;

        for (int j = i; j < MAX_DJUI_THEMES - 1; j++) {
            gDjuiThemes[j] = gDjuiThemes[j + 1];
        }
        gDjuiThemes[MAX_DJUI_THEMES - 1] = NULL;
        break;
    }

    if (!fs_sys_file_exists(filePath)) return;

    remove(filePath);
}
