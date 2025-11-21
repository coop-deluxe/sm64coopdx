#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_selectionbox.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"

#define CHAT_WIDTH_DEFAULT                800
#define CHAT_HEIGHT_DEFAULT               400
#define CHAT_TEXT_SCALE_DEFAULT           100
#define CHAT_BG_OPACITY_DEFAULT           70
#define CHAT_TEXT_OPACITY_DEFAULT         100
#define CHAT_LIFETIME_DEFAULT             10
#define CHAT_USE_STD_KEY_BINDINGS_DEFAULT true
#define CHAT_CHAR_COUNTER_DEFAULT         true
#define CHAT_CLOSED_MODE_DEFAULT          1

static const u8 CHAT_LABEL_LOW_RGB[3]     = {  32,  64, 255 };
static const u8 CHAT_LABEL_DEFAULT_RGB[3] = {  32, 224,  32 }; 
static const u8 CHAT_LABEL_HIGH_RGB[3]    = { 255,  64,  32 };

static struct DjuiText*   sChatTextScaleLabel      = NULL;
static struct DjuiText*   sChatBgOpacityLabel      = NULL;
static struct DjuiText*   sChatTextOpacityLabel    = NULL;
static struct DjuiText*   sChatLifetimeLabel       = NULL;
static struct DjuiText*   sChatWidthLabel          = NULL;
static struct DjuiText*   sChatHeightLabel         = NULL;

static struct DjuiSlider* sSliderWidth             = NULL;
static struct DjuiSlider* sSliderHeight            = NULL;
static struct DjuiSlider* sSliderTextScale         = NULL;
static struct DjuiSlider* sSliderBgOpacity         = NULL;
static struct DjuiSlider* sSliderTextOpacity       = NULL;
static struct DjuiSlider* sSliderLifetime          = NULL;

static struct DjuiCheckbox* sCheckboxUseStdChat    = NULL;
static struct DjuiCheckbox* sCheckboxCharCounter   = NULL;

static struct DjuiButton* sResetWidthButton        = NULL;
static struct DjuiButton* sResetHeightButton       = NULL;
static struct DjuiButton* sResetTextScaleButton    = NULL;
static struct DjuiButton* sResetBgOpacityButton    = NULL;
static struct DjuiButton* sResetTextOpacityButton  = NULL;
static struct DjuiButton* sResetLifetimeButton     = NULL;
static struct DjuiButton* sResetUseStdChatButton   = NULL;
static struct DjuiButton* sResetCharCounterButton  = NULL;
static struct DjuiButton* sResetClosedModeButton   = NULL;

static void djui_panel_chat_update_lifetime_slider_enabled(void);
static void djui_panel_chat_update_closed_mode_lifetime_label(void);

static struct DjuiSelectionbox* sChatClosedModeSelection = NULL;

static void djui_panel_chat_apply_chatbox_style(void) {
    djui_chat_messages_apply_style();
    if (gDjuiChatBox != NULL) {
        bool hasMessages = (gDjuiChatBox->chatFlow->base.height.value > 2.0f);
        u8 alpha = 0;
        if (hasMessages) {
            int baseAlpha = (int)(configChatBackgroundOpacity * 2.55f);
            if (baseAlpha > 255) { baseAlpha = 255; }
            if (baseAlpha < 0)   { baseAlpha = 0; }
            alpha = gDjuiChatBoxFocus ? (u8)baseAlpha : 0;
        }
        djui_base_set_color(&gDjuiChatBox->chatFlow->base, 0, 0, 0, alpha);
    }
}

static void djui_panel_chat_update_value_labels(void) {
    if (sChatWidthLabel != NULL) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%u", configChatWidth);
        djui_text_set_text(sChatWidthLabel, buf);
        struct DjuiBase* base = &sChatWidthLabel->base;
        if (configChatWidth < CHAT_WIDTH_DEFAULT) {
            djui_base_set_color(base, CHAT_LABEL_LOW_RGB[0], CHAT_LABEL_LOW_RGB[1], CHAT_LABEL_LOW_RGB[2], 255);
        } else if (configChatWidth == CHAT_WIDTH_DEFAULT) {
            djui_base_set_color(base, CHAT_LABEL_DEFAULT_RGB[0], CHAT_LABEL_DEFAULT_RGB[1], CHAT_LABEL_DEFAULT_RGB[2], 255);
        } else {
            djui_base_set_color(base, CHAT_LABEL_HIGH_RGB[0], CHAT_LABEL_HIGH_RGB[1], CHAT_LABEL_HIGH_RGB[2], 255);
        }
    }

    if (sChatHeightLabel != NULL) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%u", configChatHeight);
        djui_text_set_text(sChatHeightLabel, buf);
        struct DjuiBase* base = &sChatHeightLabel->base;
        if (configChatHeight < CHAT_HEIGHT_DEFAULT) {
            djui_base_set_color(base, CHAT_LABEL_LOW_RGB[0], CHAT_LABEL_LOW_RGB[1], CHAT_LABEL_LOW_RGB[2], 255);
        } else if (configChatHeight == CHAT_HEIGHT_DEFAULT) {
            djui_base_set_color(base, CHAT_LABEL_DEFAULT_RGB[0], CHAT_LABEL_DEFAULT_RGB[1], CHAT_LABEL_DEFAULT_RGB[2], 255);
        } else {
            djui_base_set_color(base, CHAT_LABEL_HIGH_RGB[0], CHAT_LABEL_HIGH_RGB[1], CHAT_LABEL_HIGH_RGB[2], 255);
        }
    }

    if (sChatTextScaleLabel != NULL) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%u%%", configChatTextScale);
        djui_text_set_text(sChatTextScaleLabel, buf);
        struct DjuiBase* base = &sChatTextScaleLabel->base;
        if (configChatTextScale < 100) {
            djui_base_set_color(base, CHAT_LABEL_LOW_RGB[0], CHAT_LABEL_LOW_RGB[1], CHAT_LABEL_LOW_RGB[2], 255);
        } else if (configChatTextScale == 100) {
            djui_base_set_color(base, CHAT_LABEL_DEFAULT_RGB[0], CHAT_LABEL_DEFAULT_RGB[1], CHAT_LABEL_DEFAULT_RGB[2], 255);
        } else {
            djui_base_set_color(base, CHAT_LABEL_HIGH_RGB[0], CHAT_LABEL_HIGH_RGB[1], CHAT_LABEL_HIGH_RGB[2], 255);
        }
    }

    if (sChatBgOpacityLabel != NULL) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%u%%", configChatBackgroundOpacity);
        djui_text_set_text(sChatBgOpacityLabel, buf);
        struct DjuiBase* base = &sChatBgOpacityLabel->base;
        if (configChatBackgroundOpacity < 70) {
            djui_base_set_color(base, CHAT_LABEL_LOW_RGB[0], CHAT_LABEL_LOW_RGB[1], CHAT_LABEL_LOW_RGB[2], 255);
        } else if (configChatBackgroundOpacity == 70) {
            djui_base_set_color(base, CHAT_LABEL_DEFAULT_RGB[0], CHAT_LABEL_DEFAULT_RGB[1], CHAT_LABEL_DEFAULT_RGB[2], 255);
        } else {
            djui_base_set_color(base, CHAT_LABEL_HIGH_RGB[0], CHAT_LABEL_HIGH_RGB[1], CHAT_LABEL_HIGH_RGB[2], 255);
        }
    }

    if (sChatTextOpacityLabel != NULL) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%u%%", configChatTextOpacity);
        djui_text_set_text(sChatTextOpacityLabel, buf);
        struct DjuiBase* base = &sChatTextOpacityLabel->base;
        if (configChatTextOpacity < 100) {
            djui_base_set_color(base, CHAT_LABEL_LOW_RGB[0], CHAT_LABEL_LOW_RGB[1], CHAT_LABEL_LOW_RGB[2], 255);
        } else if (configChatTextOpacity == 100) {
            djui_base_set_color(base, CHAT_LABEL_DEFAULT_RGB[0], CHAT_LABEL_DEFAULT_RGB[1], CHAT_LABEL_DEFAULT_RGB[2], 255);
        } else {
            djui_base_set_color(base, CHAT_LABEL_HIGH_RGB[0], CHAT_LABEL_HIGH_RGB[1], CHAT_LABEL_HIGH_RGB[2], 255);
        }
    }

    if (sChatLifetimeLabel != NULL) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%us", configChatMessageLifetime);
        djui_text_set_text(sChatLifetimeLabel, buf);
        struct DjuiBase* base = &sChatLifetimeLabel->base;

        if (configChatClosedMode != 1) {
            // Deaktivierter Modus: Wert grau darstellen
            djui_base_set_color(base, 160, 160, 160, 255);
        } else {
            if (configChatMessageLifetime < CHAT_LIFETIME_DEFAULT) {
                djui_base_set_color(base, CHAT_LABEL_LOW_RGB[0], CHAT_LABEL_LOW_RGB[1], CHAT_LABEL_LOW_RGB[2], 255);
            } else if (configChatMessageLifetime == CHAT_LIFETIME_DEFAULT) {
                djui_base_set_color(base, CHAT_LABEL_DEFAULT_RGB[0], CHAT_LABEL_DEFAULT_RGB[1], CHAT_LABEL_DEFAULT_RGB[2], 255);
            } else {
                djui_base_set_color(base, CHAT_LABEL_HIGH_RGB[0], CHAT_LABEL_HIGH_RGB[1], CHAT_LABEL_HIGH_RGB[2], 255);
            }
        }
    }
}

static void djui_panel_chat_update_reset_buttons(void) {
    const struct { struct DjuiButton** btn; bool active; } entries[] = {
        { &sResetUseStdChatButton,   configUseStandardKeyBindingsChat != CHAT_USE_STD_KEY_BINDINGS_DEFAULT },
        { &sResetCharCounterButton,  configChatCharCounter            != CHAT_CHAR_COUNTER_DEFAULT          },
        { &sResetClosedModeButton,   configChatClosedMode             != CHAT_CLOSED_MODE_DEFAULT           },
        { &sResetWidthButton,        configChatWidth           != CHAT_WIDTH_DEFAULT        },
        { &sResetHeightButton,       configChatHeight          != CHAT_HEIGHT_DEFAULT       },
        { &sResetTextScaleButton,    configChatTextScale       != CHAT_TEXT_SCALE_DEFAULT   },
        { &sResetBgOpacityButton,    configChatBackgroundOpacity != CHAT_BG_OPACITY_DEFAULT },
        { &sResetTextOpacityButton,  configChatTextOpacity     != CHAT_TEXT_OPACITY_DEFAULT },
        { &sResetLifetimeButton,     (configChatClosedMode == 1) && (configChatMessageLifetime != CHAT_LIFETIME_DEFAULT) },
    };

    for (int i = 0; i < 9; i++) {
        struct DjuiButton* btn = *entries[i].btn;
        if (btn == NULL) { continue; }

        bool active = entries[i].active;
        djui_base_set_enabled(&btn->base, active);

        if (btn->text != NULL) {
            if (active) {
                djui_base_set_color(&btn->text->base, 255, 64, 64, 255);   // rot
            } else {
                djui_base_set_color(&btn->text->base, 160, 160, 160, 255); // grau
            }
        }
    }
}

static void djui_panel_chat_update_lifetime_slider_enabled(void) {
    if (sSliderLifetime == NULL) { return; }
    bool lifetimeActive = (configChatClosedMode == 1);
    djui_base_set_enabled(&sSliderLifetime->base, lifetimeActive);
}

static void djui_panel_chat_slider_on_cursor_down(struct DjuiBase* base) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    u32  min   = slider->min;
    u32  max   = slider->max;
    u32* value = slider->value;
    f32 x = slider->rect->base.elem.x;
    f32 w = slider->rect->base.elem.width;
    f32 cursorX = gCursorX;
    cursorX = fmax(cursorX, x);
    cursorX = fmin(cursorX, x + w);

    f32 t = 0.0f;
    if (w > 0.0f) {
        t = (cursorX - x) / w;
    }
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    int newValue = (int)(t * (f32)(max - min) + 0.5f) + (int)min;
    if (newValue < (int)min) newValue = (int)min;
    if (newValue > (int)max) newValue = (int)max;
    *value = (u32)newValue;

    if (base != NULL && base->interactable != NULL && base->interactable->on_value_change != NULL) {
        base->interactable->on_value_change(base);
    }
    djui_slider_update_value(base);
}

static void djui_panel_chat_slider_on_cursor_down_begin(struct DjuiBase* base, bool inputCursor) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    f32 x = slider->rect->base.elem.x;
    if (gCursorX >= x) {
        if (inputCursor) {
            djui_interactable_set_input_focus(base);
        } else {
            slider->base.interactable->on_cursor_down = djui_panel_chat_slider_on_cursor_down;
        }
    } else {
        slider->base.interactable->on_cursor_down = NULL;
    }
}

static void djui_panel_chat_slider_on_cursor_down_end(struct DjuiBase* base) {
    struct DjuiSlider* slider = (struct DjuiSlider*)base;
    slider->base.interactable->on_cursor_down = NULL;
}

static void djui_panel_chat_on_width_slider_change(UNUSED struct DjuiBase* b) {
    if (configChatWidth < 200)  { configChatWidth = 200; }
    if (configChatWidth > 2000) { configChatWidth = 2000; }
    if (gDjuiChatBox != NULL) {
        djui_base_set_size(&gDjuiChatBox->base, configChatWidth, gDjuiChatBox->base.height.value);
        djui_panel_chat_apply_chatbox_style();
    }
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_height_slider_change(UNUSED struct DjuiBase* b) {
    if (configChatHeight < 100)  { configChatHeight = 100; }
    if (configChatHeight > 1000) { configChatHeight = 1000; }
    if (gDjuiChatBox != NULL) {
        djui_base_set_size(&gDjuiChatBox->base, gDjuiChatBox->base.width.value, configChatHeight);
        djui_panel_chat_apply_chatbox_style();
    }
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_style_change(UNUSED struct DjuiBase* b) {
    djui_panel_chat_apply_chatbox_style();
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_lifetime_change(UNUSED struct DjuiBase* b) {
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
    djui_panel_chat_update_closed_mode_lifetime_label();
}

static void djui_panel_chat_on_closed_mode_change(UNUSED struct DjuiBase* b) {
    if (configChatClosedMode > 2) {
        configChatClosedMode = 1;
    }
    djui_panel_chat_update_lifetime_slider_enabled();
    djui_panel_chat_update_reset_buttons();
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_closed_mode_lifetime_label();
}

static void djui_panel_chat_update_closed_mode_lifetime_label(void) {
    if (sChatClosedModeSelection == NULL) { return; }
    char buf[64];
    snprintf(buf, sizeof(buf), DLANG(CHAT_OPTIONS, CHAT_CLOSED_LIFETIME), configChatMessageLifetime);
    djui_selectionbox_set_choice_text(sChatClosedModeSelection, 1, buf);
}

static void djui_panel_chat_on_reset_width(UNUSED struct DjuiBase* b) {
    configChatWidth = CHAT_WIDTH_DEFAULT;
    if (sSliderWidth != NULL) {
        djui_slider_update_value(&sSliderWidth->base);
    }
    if (gDjuiChatBox != NULL) {
        djui_base_set_size(&gDjuiChatBox->base, configChatWidth, gDjuiChatBox->base.height.value);
        djui_panel_chat_apply_chatbox_style();
    }
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_reset_height(UNUSED struct DjuiBase* b) {
    configChatHeight = CHAT_HEIGHT_DEFAULT;
    if (sSliderHeight != NULL) {
        djui_slider_update_value(&sSliderHeight->base);
    }
    if (gDjuiChatBox != NULL) {
        djui_base_set_size(&gDjuiChatBox->base, gDjuiChatBox->base.width.value, configChatHeight);
        djui_panel_chat_apply_chatbox_style();
    }
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_reset_text_scale(UNUSED struct DjuiBase* b) {
    configChatTextScale = CHAT_TEXT_SCALE_DEFAULT;
    if (sSliderTextScale != NULL) {
        djui_slider_update_value(&sSliderTextScale->base);
    }
    djui_panel_chat_apply_chatbox_style();
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_reset_bg_opacity(UNUSED struct DjuiBase* b) {
    configChatBackgroundOpacity = CHAT_BG_OPACITY_DEFAULT;
    if (sSliderBgOpacity != NULL) {
        djui_slider_update_value(&sSliderBgOpacity->base);
    }
    djui_panel_chat_apply_chatbox_style();
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_reset_text_opacity(UNUSED struct DjuiBase* b) {
    configChatTextOpacity = CHAT_TEXT_OPACITY_DEFAULT;
    if (sSliderTextOpacity != NULL) {
        djui_slider_update_value(&sSliderTextOpacity->base);
    }
    djui_panel_chat_apply_chatbox_style();
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_reset_lifetime(UNUSED struct DjuiBase* b) {
    configChatMessageLifetime = CHAT_LIFETIME_DEFAULT;
    if (sSliderLifetime != NULL) {
        djui_slider_update_value(&sSliderLifetime->base);
    }
    djui_panel_chat_update_value_labels();
    djui_panel_chat_update_reset_buttons();
    djui_panel_chat_update_closed_mode_lifetime_label();
}

static void djui_panel_chat_on_reset_use_std_chat(UNUSED struct DjuiBase* b) {
    configUseStandardKeyBindingsChat = CHAT_USE_STD_KEY_BINDINGS_DEFAULT;
    if (sCheckboxUseStdChat != NULL && sCheckboxUseStdChat->rectValue != NULL) {
        djui_base_set_visible(&sCheckboxUseStdChat->rectValue->base, configUseStandardKeyBindingsChat);
    }
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_reset_char_counter(UNUSED struct DjuiBase* b) {
    configChatCharCounter = CHAT_CHAR_COUNTER_DEFAULT;
    if (sCheckboxCharCounter != NULL && sCheckboxCharCounter->rectValue != NULL) {
        djui_base_set_visible(&sCheckboxCharCounter->rectValue->base, configChatCharCounter);
    }
    djui_panel_chat_update_reset_buttons();
}

static void djui_panel_chat_on_reset_closed_mode(UNUSED struct DjuiBase* b) {
    configChatClosedMode = CHAT_CLOSED_MODE_DEFAULT;
    if (sChatClosedModeSelection != NULL) {
        djui_selectionbox_update_value(&sChatClosedModeSelection->base);
        djui_panel_chat_on_closed_mode_change(&sChatClosedModeSelection->base);
    } else {
        djui_panel_chat_on_closed_mode_change(NULL);
    }
}

static void djui_panel_chat_on_checkbox_change(UNUSED struct DjuiBase* b) {
    djui_panel_chat_update_reset_buttons();
}

void djui_panel_chat_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHAT_OPTIONS, CHAT), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiRect* rowUseStdChat  = djui_rect_container_create(body, 32);
        struct DjuiRect* rowCharCounter = djui_rect_container_create(body, 32);
        struct DjuiRect* rowClosedMode  = djui_rect_container_create(body, 32);

        sCheckboxUseStdChat  = djui_checkbox_create(&rowUseStdChat->base,  DLANG(CHAT_OPTIONS, USE_STANDARD_KEY_BINDINGS_CHAT), &configUseStandardKeyBindingsChat, djui_panel_chat_on_checkbox_change);
        sCheckboxCharCounter = djui_checkbox_create(&rowCharCounter->base, DLANG(CHAT_OPTIONS, CHAT_CHAR_COUNTER),             &configChatCharCounter,           djui_panel_chat_on_checkbox_change);

        char lifetimeChoice[64];
        snprintf(lifetimeChoice, sizeof(lifetimeChoice), DLANG(CHAT_OPTIONS, CHAT_CLOSED_LIFETIME), configChatMessageLifetime);
        char* chatClosedModeChoices[] = {
            DLANG(CHAT_OPTIONS, CHAT_CLOSED_DISABLED),
            lifetimeChoice,
            DLANG(CHAT_OPTIONS, CHAT_CLOSED_ALWAYS),
        };
        sChatClosedModeSelection = djui_selectionbox_create(&rowClosedMode->base, DLANG(CHAT_OPTIONS, CHAT_CLOSED_MODE), chatClosedModeChoices, 3, &configChatClosedMode, djui_panel_chat_on_closed_mode_change);

        char* chatSizeChoices[] = {
            DLANG(CHAT_OPTIONS, CHAT_SIZE_MINIMUM),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_TINY),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_TINY),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_SMALL),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_SMALL),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_NORMAL),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_BIG),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_BIG),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_HUGE),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_HUGE),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_MAXIMUM)
        };
        (void)chatSizeChoices;

        // Checkbox- / Selection-Basis und -Track an Sliderbreite anpassen
        if (sCheckboxUseStdChat != NULL) {
            djui_base_set_size(&sCheckboxUseStdChat->base, 0.94f, 32.0f);
        }
        if (sCheckboxCharCounter != NULL) {
            djui_base_set_size(&sCheckboxCharCounter->base, 0.94f, 32.0f);
        }
        if (sChatClosedModeSelection != NULL) {
            djui_base_set_size(&sChatClosedModeSelection->base, 0.94f, 32.0f);
            if (sChatClosedModeSelection->rect != NULL) {
                djui_base_set_size(&sChatClosedModeSelection->rect->base, 0.46f, 1.0f);
            }
        }

        struct DjuiRect* rowLifetime   = djui_rect_container_create(body, 32);
        struct DjuiRect* rowWidth      = djui_rect_container_create(body, 32);
        struct DjuiRect* rowHeight     = djui_rect_container_create(body, 32);
        struct DjuiRect* rowTextScale  = djui_rect_container_create(body, 32);
        struct DjuiRect* rowBgOpacity  = djui_rect_container_create(body, 32);
        struct DjuiRect* rowTextOpacity= djui_rect_container_create(body, 32);

        sSliderLifetime     = djui_slider_create(&rowLifetime->base,    DLANG(CHAT_OPTIONS, CHAT_LIFETIME),           &configChatMessageLifetime,    1,  120, djui_panel_chat_on_lifetime_change);
        sSliderWidth        = djui_slider_create(&rowWidth->base,       DLANG(CHAT_OPTIONS, CHAT_WIDTH),              &configChatWidth,           200, 2000, djui_panel_chat_on_width_slider_change);
        sSliderHeight       = djui_slider_create(&rowHeight->base,      DLANG(CHAT_OPTIONS, CHAT_HEIGHT),             &configChatHeight,          100, 1000, djui_panel_chat_on_height_slider_change);
        sSliderTextScale    = djui_slider_create(&rowTextScale->base,   DLANG(CHAT_OPTIONS, CHAT_TEXT_SCALE),         &configChatTextScale,         50,  200, djui_panel_chat_on_style_change);
        sSliderBgOpacity    = djui_slider_create(&rowBgOpacity->base,   DLANG(CHAT_OPTIONS, CHAT_BACKGROUND_OPACITY), &configChatBackgroundOpacity,  0,  100, djui_panel_chat_on_style_change);
        sSliderTextOpacity  = djui_slider_create(&rowTextOpacity->base, DLANG(CHAT_OPTIONS, CHAT_TEXT_OPACITY),       &configChatTextOpacity,        0,  100, djui_panel_chat_on_style_change);

        {
            struct DjuiSlider* slidersForCursor[] = {
                sSliderWidth,
                sSliderHeight,
                sSliderTextScale,
                sSliderBgOpacity,
                sSliderTextOpacity,
                sSliderLifetime,
            };
            for (int i = 0; i < 6; i++) {
                struct DjuiSlider* s = slidersForCursor[i];
                if (s == NULL) { continue; }
                djui_interactable_hook_cursor_down(
                    &s->base,
                    djui_panel_chat_slider_on_cursor_down_begin,
                    djui_panel_chat_slider_on_cursor_down,
                    djui_panel_chat_slider_on_cursor_down_end
                );
            }
        }

        struct DjuiSlider* sliders[] = {
            sSliderWidth,
            sSliderHeight,
            sSliderTextScale,
            sSliderBgOpacity,
            sSliderTextOpacity,
            sSliderLifetime,
        };
        for (int i = 0; i < 6; i++) {
            struct DjuiSlider* s = sliders[i];
            if (s == NULL) { continue; }
            djui_base_set_alignment(&s->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_CENTER);
            djui_base_set_size_type(&s->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            // Slider-Bereich weiter nach rechts ziehen, sodass nur noch ein schmaler Abstand vor dem X bleibt
            djui_base_set_size(&s->base, 0.94f, 32.0f);
            djui_base_set_size(&s->rect->base, 0.46f, 1.0f);
        }

        sChatWidthLabel = djui_text_create(&sSliderWidth->rect->base, "");
        djui_base_set_alignment(&sChatWidthLabel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sChatWidthLabel->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&sChatWidthLabel->base, 1.0f, 1.0f);
        djui_text_set_alignment(sChatWidthLabel, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(sChatWidthLabel, 64, 64, 64, 100);

        sChatHeightLabel = djui_text_create(&sSliderHeight->rect->base, "");
        djui_base_set_alignment(&sChatHeightLabel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sChatHeightLabel->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&sChatHeightLabel->base, 1.0f, 1.0f);
        djui_text_set_alignment(sChatHeightLabel, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(sChatHeightLabel, 64, 64, 64, 100);

        sChatTextScaleLabel = djui_text_create(&sSliderTextScale->rect->base, "");
        djui_base_set_alignment(&sChatTextScaleLabel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sChatTextScaleLabel->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&sChatTextScaleLabel->base, 1.0f, 1.0f);
        djui_text_set_alignment(sChatTextScaleLabel, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(sChatTextScaleLabel, 64, 64, 64, 100);

        sChatBgOpacityLabel = djui_text_create(&sSliderBgOpacity->rect->base, "");
        djui_base_set_alignment(&sChatBgOpacityLabel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sChatBgOpacityLabel->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&sChatBgOpacityLabel->base, 1.0f, 1.0f);
        djui_text_set_alignment(sChatBgOpacityLabel, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(sChatBgOpacityLabel, 64, 64, 64, 100);

        sChatTextOpacityLabel = djui_text_create(&sSliderTextOpacity->rect->base, "");
        djui_base_set_alignment(&sChatTextOpacityLabel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sChatTextOpacityLabel->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&sChatTextOpacityLabel->base, 1.0f, 1.0f);
        djui_text_set_alignment(sChatTextOpacityLabel, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(sChatTextOpacityLabel, 64, 64, 64, 100);

        sChatLifetimeLabel = djui_text_create(&sSliderLifetime->rect->base, "");
        djui_base_set_alignment(&sChatLifetimeLabel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sChatLifetimeLabel->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&sChatLifetimeLabel->base, 1.0f, 1.0f);
        djui_text_set_alignment(sChatLifetimeLabel, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(sChatLifetimeLabel, 64, 64, 64, 100);

        sResetUseStdChatButton  = djui_button_create(&rowUseStdChat->base,   "X", DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_on_reset_use_std_chat);
        sResetCharCounterButton = djui_button_create(&rowCharCounter->base,  "X", DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_on_reset_char_counter);
        sResetClosedModeButton  = djui_button_create(&rowClosedMode->base,   "X", DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_on_reset_closed_mode);
        sResetWidthButton       = djui_button_create(&rowWidth->base,        "X", DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_on_reset_width);
        sResetHeightButton      = djui_button_create(&rowHeight->base,       "X", DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_on_reset_height);
        sResetTextScaleButton   = djui_button_create(&rowTextScale->base,    "X", DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_on_reset_text_scale);
        sResetBgOpacityButton   = djui_button_create(&rowBgOpacity->base,    "X", DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_on_reset_bg_opacity);
        sResetTextOpacityButton = djui_button_create(&rowTextOpacity->base,  "X", DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_on_reset_text_opacity);
        sResetLifetimeButton    = djui_button_create(&rowLifetime->base,     "X", DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_on_reset_lifetime);

        struct DjuiButton* buttons[] = {
            sResetUseStdChatButton,
            sResetCharCounterButton,
            sResetClosedModeButton,
            sResetWidthButton,
            sResetHeightButton,
            sResetTextScaleButton,
            sResetBgOpacityButton,
            sResetTextOpacityButton,
            sResetLifetimeButton,
        };
        for (int i = 0; i < 9; i++) {
            struct DjuiButton* btn = buttons[i];
            if (btn == NULL) { continue; }
            djui_base_set_alignment(&btn->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
            djui_base_set_size_type(&btn->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&btn->base, 32.0f, 32.0f);
        }

        djui_panel_chat_update_value_labels();
        djui_panel_chat_update_lifetime_slider_enabled();
        djui_panel_chat_update_reset_buttons();

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}


