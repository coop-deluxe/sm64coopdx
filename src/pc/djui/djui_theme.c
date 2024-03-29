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

static struct DjuiTheme sDjuiThemeLuigi = {
    .id = "LUIGI_THEME",
    .name = "LUIGI_THEME",
    .interactables = {
            .textColor = {
            0, 0, 0, 255
        },

        .defaultRectColor = {
            0, 210, 0, 255
        },
        .cursorDownRectColor = {
            0, 100, 0, 255
        },
        .hoveredRectColor = {
            50, 200, 50, 255
        },

        .defaultBorderColor = {
            0, 210, 0, 255
        },
        .cursorDownBorderColor = {
            0, 150, 0, 255
        },
        .hoveredBorderColor = {
            100, 210, 100, 255
        }
    },
    .threePanels = {
        .rectColor = {
            100, 180, 100, 235
        },
        .borderColor = {
            0, 150, 0, 200
        }
    },
    .panels = {
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemeWario = {
    .id = "WARIO_THEME",
    .name = "WARIO_THEME",
    .interactables = {
        .textColor = {
            255, 255, 255, 255
        },

        .defaultRectColor = {
            200, 170, 0, 255
        },
        .cursorDownRectColor = {
            255, 0, 0, 255
        },
        .hoveredRectColor = {
            120, 0, 0, 255
        },

        .defaultBorderColor = {
            255, 0, 0, 255
        },
        .cursorDownBorderColor = {
            200, 170, 0, 255
        },
        .hoveredBorderColor = {
            200, 170, 0, 255
        }
    },
    .threePanels = {
        .rectColor = {
            200, 170, 0, 235
        },
        .borderColor = {
            120, 0, 0, 200
        }
    },
    .panels = {
        .hudFontHeader = true
    }
};

static struct DjuiTheme sDjuiThemeBlue = {
    .id = "BLUE_THEME",
    .name = "BLUE_THEME",
    .interactables = {
        .textColor = {
            255, 255, 255, 255
        },

        .defaultRectColor = {
            70, 130, 180, 255
        },
        .cursorDownRectColor = {
            30, 144, 255, 255
        },
        .hoveredRectColor = {
            50, 100, 150, 255
        },

        .defaultBorderColor = {
            50, 100, 150, 255
        },
        .cursorDownBorderColor = {
            0, 0, 128, 255
        },
        .hoveredBorderColor = {
            65, 105, 225, 255
        }
    },
    .threePanels = {
        .rectColor = {
            100, 149, 237, 235
        },
        .borderColor = {
            0, 0, 139, 200
        }
    },
    .panels = {
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemeRed = {
    .id = "RED_THEME",
    .name = "RED_THEME",
    .interactables = {
        .textColor = {
            255, 255, 255, 255
        },

        .defaultRectColor = {
            255, 0, 0, 255
        },
        .cursorDownRectColor = {
            100, 0, 0, 255
        },
        .hoveredRectColor = {
            200, 50, 50, 255
        },

        .defaultBorderColor = {
            255, 0, 0, 255
        },
        .cursorDownBorderColor = {
            150, 0, 0, 255
        },
        .hoveredBorderColor = {
            255, 100, 100, 255
        }
    },
    .threePanels = {
        .rectColor = {
            255, 100, 100, 235
        },
        .borderColor = {
            150, 0, 0, 200
        }
    },
    .panels = {
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemeTransgender = {
    .id = "TRANSGENDER_THEME",
    .name = "TRANSGENDER_THEME",
    .interactables = {
        .textColor = {
            0, 0, 0, 255
        },

        .defaultRectColor = {
            255, 255, 255, 255 
        },
        .cursorDownRectColor = {
            255, 255, 255, 255 
        },
        .hoveredRectColor = {
            255, 255, 255, 255 
        },

        .defaultBorderColor = {
            192, 192, 192, 255 
        },
        .cursorDownBorderColor = {
            192, 192, 192, 255 
        },
        .hoveredBorderColor = {
            192, 192, 192, 255 
        }
    },
    .threePanels = {
        .rectColor = {
            245, 169, 184, 200
        },
        .borderColor = {
            0, 174, 239, 235
        }
    },
    .panels = {
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemePurple = {
    .id = "PURPLE_THEME",
    .name = "PURPLE_THEME",
    .interactables = {
        .textColor = {
            255, 255, 255, 255
        },

        .defaultRectColor = {
            128, 0, 128, 255
        },
        .cursorDownRectColor = {
            128, 0, 128, 255
        },
        .hoveredRectColor = {
            128, 0, 128, 255
        },

        .defaultBorderColor = {
            128, 0, 128, 255
        },
        .cursorDownBorderColor = {
            128, 0, 128, 255
        },
        .hoveredBorderColor = {
            128, 0, 128, 255
        }
    },
    .threePanels = {
        .rectColor = {
            147, 112, 219, 235
        },
        .borderColor = {
            138, 43, 226, 200
        }
    },
    .panels = {
        .hudFontHeader = false
    }
};

static struct DjuiTheme sDjuiThemeMidnightBlue = {
    .id = "MIDNIGHT_BLUE_THEME",
    .name = "MIDNIGHT_BLUE_THEME",
    .interactables = {
        .textColor = {
            255, 255, 255, 255
        },

        .defaultRectColor = {
            0, 0, 139, 255
        },
        .cursorDownRectColor = {
            30, 144, 255, 255
        },
        .hoveredRectColor = {
            0, 0, 100, 255
        },

        .defaultBorderColor = {
            0, 0, 139, 255
        },
        .cursorDownBorderColor = {
            0, 0, 128, 255
        },
        .hoveredBorderColor = {
            65, 105, 225, 255
        }
    },
    .threePanels = {
        .rectColor = {
            100, 129, 237, 235
        },
        .borderColor = {
            0, 0, 139, 200
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
    &sDjuiThemeLuigi,
    &sDjuiThemeWario,
    &sDjuiThemeBlue,
    &sDjuiThemeRed,
    &sDjuiThemeTransgender,
    &sDjuiThemePurple,
    &sDjuiThemeMidnightBlue
};

struct DjuiColor djui_theme_shade_color(struct DjuiColor color) {
    color.r *= 0.6f;
    color.g *= 0.6f;
    color.b *= 0.6f;
    return color;
}

void djui_themes_init(void) {
    for (s32 i = 0; i < DJUI_THEME_MAX; i++) {
        gDjuiThemes[i]->name = djui_language_get("DJUI_THEMES", gDjuiThemes[i]->id);
    }
}
