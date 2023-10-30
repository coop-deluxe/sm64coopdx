#include "djui.h"

static struct DjuiTheme sDjuiThemeLight = {
    .id = "LIGHT_THEME",
    .name = "LIGHT_THEME",
    .interactables = {
        .textColor = {
            .r = 11, .g = 11, .b = 11, .a = 255
        },

        .defaultRectColor = {
            .r = 222, .g = 222, .b = 222, .a = 255
        },
        .cursorDownRectColor = {
            .r = 204, .g = 228, .b = 247, .a = 255
        },
        .hoveredRectColor = {
            .r = 229, .g = 241, .b = 251, .a = 255
        },

        .defaultBorderColor = {
            .r = 75, .g = 75, .b = 75, .a = 255
        },
        .cursorDownBorderColor = {
            .r = 0, .g = 84, .b = 153, .a = 255
        },
        .hoveredBorderColor = {
            .r = 0, .g = 120, .b = 215, .a = 255
        },

        .darkRectColor = {
            .r = 150, .g = 150, .b = 150, .a = 255
        },
        .darkBorderColor = {
            .r = 100, .g = 100, .b = 100, .a = 255
        }
    },
    .threePanels = {
        .rectColor = {
            .r = 0, .g = 0, .b = 0, .a = 235
        },
        .borderColor = {
            .r = 0, .g = 0, .b = 0, .a = 200
        },
    },
    .panels = {
        .widthMultiplier = 1.0f,
        .heightMultiplier = 1.0f,
        .center = false
    }
};

static struct DjuiTheme sDjuiThemeDark = {
    .id = "DARK_THEME",
    .name = "DARK_THEME",
    .interactables = {
        .textColor = {
            .r = 220, .g = 220, .b = 220, .a = 255
        },

        .defaultRectColor = {
            .r = 22, .g = 22, .b = 22, .a = 255
        },
        .cursorDownRectColor = {
            .r = 100, .g = 100, .b = 100, .a = 255
        },
        .hoveredRectColor = {
            .r = 80, .g = 80, .b = 80, .a = 255
        },

        .defaultBorderColor = {
            .r = 75, .g = 75, .b = 75, .a = 255
        },
        .cursorDownBorderColor = {
            .r = 0, .g = 84, .b = 153, .a = 255
        },
        .hoveredBorderColor = {
            .r = 0, .g = 120, .b = 215, .a = 255
        },

        .darkRectColor = {
            .r = 10, .g = 10, .b = 10, .a = 255
        },
        .darkBorderColor = {
            .r = 75, .g = 75, .b = 75, .a = 255
        }
    },
    .threePanels = {
        .rectColor = {
            .r = 0, .g = 0, .b = 0, .a = 235
        },
        .borderColor = {
            .r = 0, .g = 0, .b = 0, .a = 200
        },
    },
    .panels = {
        .widthMultiplier = 1.0f,
        .heightMultiplier = 1.0f,
        .center = false
    }
};

static struct DjuiTheme sDjuiThemeLightCentered = {
    .id = "LIGHT_THEME_CENTERED",
    .name = "LIGHT_THEME_CENTERED",
    .interactables = {
        .textColor = {
            .r = 11, .g = 11, .b = 11, .a = 255
        },

        .defaultRectColor = {
            .r = 222, .g = 222, .b = 222, .a = 255
        },
        .cursorDownRectColor = {
            .r = 204, .g = 228, .b = 247, .a = 255
        },
        .hoveredRectColor = {
            .r = 229, .g = 241, .b = 251, .a = 255
        },

        .defaultBorderColor = {
            .r = 75, .g = 75, .b = 75, .a = 255
        },
        .cursorDownBorderColor = {
            .r = 0, .g = 84, .b = 153, .a = 255
        },
        .hoveredBorderColor = {
            .r = 0, .g = 120, .b = 215, .a = 255
        },

        .darkRectColor = {
            .r = 150, .g = 150, .b = 150, .a = 255
        },
        .darkBorderColor = {
            .r = 100, .g = 100, .b = 100, .a = 255
        },
    },
    .threePanels = {
        .rectColor = {
            .r = 0, .g = 0, .b = 0, .a = 235
        },
        .borderColor = {
            .r = 0, .g = 0, .b = 0, .a = 200
        },
    },
    .panels = {
        .widthMultiplier = 1.25f,
        .heightMultiplier = 0.88f,
        .center = true
    }
};

static struct DjuiTheme sDjuiThemeDarkCentered = {
    .id = "DARK_THEME_CENTERED",
    .name = "DARK_THEME_CENTERED",
    .interactables = {
        .textColor = {
            .r = 220, .g = 220, .b = 220, .a = 255
        },

        .defaultRectColor = {
            .r = 22, .g = 22, .b = 22, .a = 255
        },
        .cursorDownRectColor = {
            .r = 100, .g = 100, .b = 100, .a = 255
        },
        .hoveredRectColor = {
            .r = 80, .g = 80, .b = 80, .a = 255
        },

        .defaultBorderColor = {
            .r = 75, .g = 75, .b = 75, .a = 255
        },
        .cursorDownBorderColor = {
            .r = 0, .g = 84, .b = 153, .a = 255
        },
        .hoveredBorderColor = {
            .r = 0, .g = 120, .b = 215, .a = 255
        },

        .darkRectColor = {
            .r = 10, .g = 10, .b = 10, .a = 255
        },
        .darkBorderColor = {
            .r = 75, .g = 75, .b = 75, .a = 255
        }
    },
    .threePanels = {
        .rectColor = {
            .r = 0, .g = 0, .b = 0, .a = 235
        },
        .borderColor = {
            .r = 0, .g = 0, .b = 0, .a = 200
        },
    },
    .panels = {
        .widthMultiplier = 1.25f,
        .heightMultiplier = 0.88f,
        .center = true
    }
};

struct DjuiTheme* gDjuiThemes[] = {
    &sDjuiThemeLight,
    &sDjuiThemeDark,
    &sDjuiThemeLightCentered,
    &sDjuiThemeDarkCentered
};

void djui_themes_init(void) {
    for (s32 i = 0; i < DJUI_THEME_MAX; i++) {
        gDjuiThemes[i]->name = djui_language_get("DJUI_THEMES", gDjuiThemes[i]->id);
    }
}
