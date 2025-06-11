#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/controller/controller_system.h"
#include "game/local_multiplayer.h"

struct DjuiSplitScreenWindow {
    struct DjuiRect *rect;
    struct DjuiText *text;
    struct DjuiText *ctrText;
    struct DjuiSelectionbox *selectionBox;
};

static struct DjuiSplitScreenWindow *sDjuiSplitScreenWindows[POSSIBLE_NUM_PLAYERS] = { 0 };

static void djui_panel_splitscreen_window_update_controller_text(struct DjuiSplitScreenWindow *window, u16 index) {

    // Update the index translation
    for (u16 i = 0, index = 0; i < POSSIBLE_NUM_PLAYERS; i++) {
        struct ControllerPlace *c = &gPlayerControllerInfos[i];
        c->index = index;
        if (c->type == 1) { continue; }
        index++;
    }

    struct ControllerPlace *cntr = &gPlayerControllerInfos[index];
    const char *name = "Main Keyboard";
    if (cntr->type != 1) {
        name = SDL_JoystickNameForIndex(cntr->index);
        name = name ? name : "Disconnected";
    }
    djui_text_set_text(window->ctrText, name);

    cntr->connected = (cntr->type == 1 || name != NULL);

    djui_base_compute_tree(&window->ctrText->base);
    u16 lines = djui_text_count_lines(window->ctrText, 2);
    const struct DjuiFont *font = window->ctrText->font;
    f32 directTextHeight = font->defaultFontScale * font->lineHeight * lines + 8;
    djui_base_set_size(&window->ctrText->base, 1.0f, directTextHeight);
}

void djui_panel_splitscreen_options_refresh() {
    for (u16 i = 0; i < POSSIBLE_NUM_PLAYERS; i++) {
        struct DjuiSplitScreenWindow *window = sDjuiSplitScreenWindows[i];
        if (!window) { return; }
        djui_panel_splitscreen_window_update_controller_text(window, i);
    }
}

void djui_panel_splitscreen_selection_box_changed(struct DjuiBase *caller) {
    struct DjuiSelectionbox *selectionBox = (struct DjuiSelectionbox *) caller;
    for (u16 i = 0; i < POSSIBLE_NUM_PLAYERS; i++) {
        struct DjuiSplitScreenWindow *window = sDjuiSplitScreenWindows[i];
        if (!window || window->selectionBox != selectionBox) { continue; }

        struct ControllerPlace *cntr = &gPlayerControllerInfos[i];
        if (cntr->type != 1) { continue; }

        // This player is a keyboard
        for (u16 j = 0; j < POSSIBLE_NUM_PLAYERS; j++) {
            if (i == j) { continue; }
            struct ControllerPlace *c = &gPlayerControllerInfos[j];
            if (c->type == 1) {
                c->type = 0;
                struct DjuiSplitScreenWindow *window2 = sDjuiSplitScreenWindows[j];
                djui_selectionbox_update_value(&window2->selectionBox->base);
            }
        }
        break;
    }
    controller_update_controller_count();
    djui_panel_splitscreen_options_refresh();
}

static struct DjuiSplitScreenWindow *djui_panel_splitscreen_controller_window_create(struct DjuiBase *parent, u16 index) {
    struct DjuiSplitScreenWindow *window = calloc(1, sizeof(struct DjuiSplitScreenWindow));
    struct ControllerPlace *cntr = &gPlayerControllerInfos[index];

    // Border
    window->rect = djui_rect_create(parent);
    djui_base_set_size_type(&window->rect->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&window->rect->base, 240, 1.f);
    djui_base_set_alignment(&window->rect->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    djui_base_set_color(&window->rect->base, 0, 0, 0, 0);
    djui_base_set_border_color(&window->rect->base, 0xFF, 0xFF, 0xFF, 160);
    djui_base_set_border_width(&window->rect->base, 4);
    djui_base_compute_tree(&window->rect->base);

    // Player index
    char buffer[15];
    snprintf(buffer, 15, "Player %d", index + 1);
    window->text = djui_text_create(&window->rect->base, buffer);
    djui_base_set_size_type(&window->text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_compute_tree(&window->text->base);
    djui_base_set_size(&window->text->base, 1.0f, 32);
    djui_base_set_color(&window->text->base, 220, 220, 220, 255);
    djui_text_set_alignment(window->text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);

    // Controller type
    static char *choices[] = { "Gamepad", "Keyboard" };
    window->selectionBox = djui_selectionbox_create(&window->rect->base, "Type:", choices, 2, &cntr->type, djui_panel_splitscreen_selection_box_changed);
    djui_base_set_size_type(&window->selectionBox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&window->selectionBox->base, 0.7f, 32);
    djui_base_set_alignment(&window->selectionBox->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&window->selectionBox->rect->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&window->selectionBox->rect->base, 0.6f, 32);

    // Controller name text
    window->ctrText = djui_text_create(&window->rect->base, "Disconnected");
    djui_base_set_size_type(&window->ctrText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_compute_tree(&window->ctrText->base);
    djui_base_set_size(&window->ctrText->base, 1.0f, 32);
    djui_base_set_color(&window->ctrText->base, 220, 220, 220, 255);
    djui_base_set_alignment(&window->ctrText->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
    djui_text_set_alignment(window->ctrText, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
    djui_panel_splitscreen_window_update_controller_text(window, index);

    sDjuiSplitScreenWindows[index] = window;

    return window;
}

void djui_panel_splitscreen_options_destroy(UNUSED struct DjuiBase* caller) {
    memset(sDjuiSplitScreenWindows, 0, sizeof(sDjuiSplitScreenWindows));
}

void djui_panel_splitscreen_options_create(struct DjuiBase* caller) {
    struct DjuiThreePanel *panel = djui_panel_menu_create(DLANG(HOST, SPLITSCREEN), false);
    struct DjuiBase *body = djui_three_panel_get_body(panel);

    {
        for (u16 i = 0; i < POSSIBLE_NUM_PLAYERS; i += 2) {
            struct DjuiFlowLayout* row = djui_flow_layout_create(body);
            djui_base_set_size_type(&row->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&row->base, 1.0f, 200.f);
            djui_base_set_color(&row->base, 0, 0, 0, 128);
            djui_flow_layout_set_flow_direction(row, DJUI_FLOW_DIR_RIGHT);
            djui_flow_layout_set_margin(row, 4);

            djui_panel_splitscreen_controller_window_create(&row->base, i + 0);
            djui_panel_splitscreen_controller_window_create(&row->base, i + 1);
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    struct DjuiPanel *p = djui_panel_add(caller, panel, NULL);
    if (!p) { return; }
    p->on_panel_destroy = djui_panel_splitscreen_options_destroy;
}
