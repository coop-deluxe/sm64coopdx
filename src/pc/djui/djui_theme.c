#include "djui.h"

static struct DjuiTheme sDjuiThemeLight = {
    .id = "LIGHT_THEME",
    .name = "LIGHT_THEME",
    .interactables = {
        .textColor = {
            11, 11, 11, 255
        },

        .defaultRectColor = {
            222, 222, 222, 255
        },
        .cursorDownRectColor = {
            204, 228, 247, 255
        },
        .hoveredRectColor = {
            229, 241, 251, 255
        },

        .defaultBorderColor = {
            75, 75, 75, 255
        },
        .cursorDownBorderColor = {
            0, 84, 153, 255
        },
        .hoveredBorderColor = {
            0, 120, 215, 255
        }
    },
    .threePanels = {
        .rectColor = {
            0, 0, 0, 235
        },
        .borderColor = {
            0, 0, 0, 200
        }
    },
    .panels = {
        .widthMultiplier = 1.0f,
        .heightMultiplier = 1.0f,
        .center = false,
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemeDark = {
    .id = "DARK_THEME",
    .name = "DARK_THEME",
    .interactables = {
        .textColor = {
            220, 220, 220, 255
        },

        .defaultRectColor = {
            22, 22, 22, 255
        },
        .cursorDownRectColor = {
            100, 100, 100, 255
        },
        .hoveredRectColor = {
            80, 80, 80, 255
        },

        .defaultBorderColor = {
            75, 75, 75, 255
        },
        .cursorDownBorderColor = {
            0, 84, 153, 255
        },
        .hoveredBorderColor = {
            0, 120, 215, 255
        }
    },
    .threePanels = {
        .rectColor = {
            0, 0, 0, 235
        },
        .borderColor = {
            0, 0, 0, 200
        }
    },
    .panels = {
        .widthMultiplier = 1.0f,
        .heightMultiplier = 1.0f,
        .center = false,
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemeLightCentered = {
    .id = "LIGHT_THEME_CENTERED",
    .name = "LIGHT_THEME_CENTERED",
    .interactables = {
        .textColor = {
            11, 11, 11, 255
        },

        .defaultRectColor = {
            222, 222, 222, 255
        },
        .cursorDownRectColor = {
            204, 228, 247, 255
        },
        .hoveredRectColor = {
            229, 241, 251, 255
        },

        .defaultBorderColor = {
            75, 75, 75, 255
        },
        .cursorDownBorderColor = {
            0, 84, 153, 255
        },
        .hoveredBorderColor = {
            0, 120, 215, 255
        }
    },
    .threePanels = {
        .rectColor = {
            0, 0, 0, 235
        },
        .borderColor = {
            0, 0, 0, 200
        }
    },
    .panels = {
        .widthMultiplier = 1.25f,
        .heightMultiplier = 0.88f,
        .center = true,
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemeDarkCentered = {
    .id = "DARK_THEME_CENTERED",
    .name = "DARK_THEME_CENTERED",
    .interactables = {
        .textColor = {
            220, 220, 220, 255
        },

        .defaultRectColor = {
            22, 22, 22, 255
        },
        .cursorDownRectColor = {
            100, 100, 100, 255
        },
        .hoveredRectColor = {
            80, 80, 80, 255
        },

        .defaultBorderColor = {
            75, 75, 75, 255
        },
        .cursorDownBorderColor = {
            0, 84, 153, 255
        },
        .hoveredBorderColor = {
            0, 120, 215, 255
        }
    },
    .threePanels = {
        .rectColor = {
            0, 0, 0, 235
        },
        .borderColor = {
            0, 0, 0, 200
        }
    },
    .panels = {
        .widthMultiplier = 1.25f,
        .heightMultiplier = 0.88f,
        .center = true,
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemeFileSelect = {
    .id = "FILE_SELECT_THEME",
    .name = "FILE_SELECT_THEME",
    .interactables = {
        .textColor = {
            11, 11, 11, 255
        },

        .defaultRectColor = {
            200, 215, 197, 255
        },
        .cursorDownRectColor = {
            204, 228, 247, 255
        },
        .hoveredRectColor = {
            229, 241, 251, 255
        },

        .defaultBorderColor = {
            74, 79, 74, 255
        },
        .cursorDownBorderColor = {
            0, 84, 153, 255
        },
        .hoveredBorderColor = {
            0, 120, 215, 255
        }
    },
    .threePanels = {
        .rectColor = {
            208, 165, 32, 255
        },
        .borderColor = {
            182, 135, 8, 255
        }
    },
    .panels = {
        .widthMultiplier = 1.5f,
        .heightMultiplier = 0.88f,
        .center = true,
        .hudFontHeader = true
    }
};

struct DjuiTheme* gDjuiThemes[] = {
    &sDjuiThemeLight,
    &sDjuiThemeDark,
    &sDjuiThemeLightCentered,
    &sDjuiThemeDarkCentered,
    &sDjuiThemeFileSelect
};

struct DjuiColor djui_theme_shade_color(struct DjuiColor color) {
    color.r *= 0.5f;
    color.g *= 0.5f;
    color.b *= 0.5f;
    return color;
}

void djui_themes_init(void) {
    for (s32 i = 0; i < DJUI_THEME_MAX; i++) {
        gDjuiThemes[i]->name = djui_language_get("DJUI_THEMES", gDjuiThemes[i]->id);
    }
}
