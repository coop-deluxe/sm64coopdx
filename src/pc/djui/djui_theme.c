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
            0, 0, 0, 230
        },
        .borderColor = {
            0, 0, 0, 200
        }
    },
    .panels = {
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
            0, 0, 0, 230
        },
        .borderColor = {
            0, 0, 0, 200
        }
    },
    .panels = {
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
        .hudFontHeader = true
    }
};

static struct DjuiTheme sDjuiThemeMario = {
    .id = "MARIO_THEME",
    .name = "MARIO_THEME",
    .interactables = {
        .textColor = {
            11, 11, 11, 255
        },

        .defaultRectColor = {
            255, 227, 0, 255
        },
        .cursorDownRectColor = {
            204, 228, 247, 255
        },
        .hoveredRectColor = {
            229, 241, 251, 255
        },

        .defaultBorderColor = {
            196, 165, 0, 255
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
            76, 116, 201, 235
        },
        .borderColor = {
            255, 82, 82, 200
        }
    },
    .panels = {
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemeOdyssey = {
    .id = "ODYSSEY_THEME",
    .name = "ODYSSEY_THEME",
    .interactables = {
        .textColor = {
            11, 11, 11, 255
        },

        .defaultRectColor = {
            255, 255, 255, 255
        },
        .cursorDownRectColor = {
            204, 228, 247, 255
        },
        .hoveredRectColor = {
            229, 241, 251, 255
        },

        .defaultBorderColor = {
            200, 200, 200, 255
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
            247, 0, 37, 200
        },
        .borderColor = {
            255, 255, 255, 200
        }
    },
    .panels = {
        .hudFontHeader = false
    }
};

struct DjuiTheme* gDjuiThemes[] = {
    &sDjuiThemeLight,
    &sDjuiThemeDark,
    &sDjuiThemeFileSelect,
    &sDjuiThemeMario,
    &sDjuiThemeOdyssey
};

struct DjuiColor djui_theme_shade_color(struct DjuiColor color, f32 mult) {
    color.r *= mult;
    color.g *= mult;
    color.b *= mult;
    return color;
}

void djui_themes_init(void) {
    for (s32 i = 0; i < DJUI_THEME_MAX; i++) {
        gDjuiThemes[i]->name = djui_language_get("DJUI_THEMES", gDjuiThemes[i]->id);
    }
}
