#include <stdio.h>
#include <string.h>
#include "djui.h"
#include "djui_panel_menu.h"
#include "djui_console.h"

#define MAX_CONSOLE_MESSAGES 500

struct DjuiConsole* gDjuiConsole = NULL;
bool gDjuiConsoleFocus = false;
char gDjuiConsoleTmpBuffer[CONSOLE_MAX_TMP_BUFFER] = "";
u32 sDjuiConsoleMessages = 0;

void djui_console_toggle(void) {
    if (gDjuiConsole == NULL) { return; }
    gDjuiConsoleFocus = !gDjuiConsoleFocus;
    djui_base_set_visible(&gDjuiConsole->panel->base, gDjuiConsoleFocus);

    if (gDjuiConsoleFocus) {
        if (gDjuiChatBoxFocus) { djui_chat_box_toggle(); }
        djui_interactable_set_input_focus(&gDjuiConsole->panel->base);
    } else {
        djui_interactable_set_input_focus(NULL);
    }
}

static bool djui_console_on_key_down(UNUSED struct DjuiBase* base, int scancode) {
    if (gDjuiConsole == NULL) { return false; }
    struct DjuiBase* body = djui_three_panel_get_body(gDjuiConsole->panel);
    f32 yMax = body->height.value - gDjuiConsole->flow->base.height.value;

    f32* yValue = &gDjuiConsole->flow->base.y.value;
    bool canScrollUp   = (*yValue > yMax);
    bool canScrollDown = (*yValue < 0);
    f32 pageAmount = body->height.value;

    switch (scancode) {
        case SCANCODE_UP:
            if (canScrollUp) { *yValue = fmax(*yValue - 30, yMax); }
            break;
        case SCANCODE_DOWN:
            if (canScrollDown) { *yValue = fmin(*yValue + 30, 0); }
            break;
        case SCANCODE_PAGE_UP:
            if (canScrollUp) { *yValue = fmax(*yValue - pageAmount, yMax); }
            break;
        case SCANCODE_PAGE_DOWN:
            if (canScrollDown) { *yValue = fmin(*yValue + pageAmount, 0); }
            break;
        case SCANCODE_ESCAPE: djui_console_toggle(); break;
        default: break;
    }
    gDjuiConsole->scrolling = (*yValue != 0);
    return true;
}

void djui_console_message_create(char* message) {
    if (!gDjuiConsole) { return; }
    djui_base_compute_tree(&gDjuiConsole->panel->base);
    struct DjuiBase* cfBase = &gDjuiConsole->flow->base;

    f32 maxTextWidth = gDjuiConsole->panel->base.comp.width - gDjuiConsole->panel->base.padding.left.value - gDjuiConsole->panel->base.padding.right.value - 20;

    struct DjuiText* text = djui_text_create(cfBase, message);
    struct DjuiBase* tBase = &text->base;
    djui_base_set_alignment(tBase, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_base_set_size_type(tBase, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(tBase, maxTextWidth, 32);
    djui_base_set_color(tBase, 255, 255, 255, 255);

    // figure out chat message height
    text->base.comp.width = maxTextWidth;
    f32 messageHeight = djui_text_count_lines(text, 10) * (text->font->lineHeight * text->font->defaultFontScale) + 8;
    djui_base_set_size(tBase, maxTextWidth, messageHeight);

    f32 heightAdjust = messageHeight + gDjuiConsole->flow->margin.value;
    cfBase->height.value += heightAdjust;

    if (gDjuiConsole->scrolling) {
        cfBase->y.value -= heightAdjust;
    }

    sDjuiConsoleMessages++;
    if (sDjuiConsoleMessages >= MAX_CONSOLE_MESSAGES) {
        if (cfBase->child) {
            heightAdjust = cfBase->child->base->height.value + gDjuiConsole->flow->margin.value;
            cfBase->height.value -= heightAdjust;
            if (gDjuiConsole->scrolling) {
                cfBase->y.value += heightAdjust;
            }
        }

        djui_base_destroy_one_child(cfBase);
        sDjuiConsoleMessages--;
    }
}

struct DjuiConsole* djui_console_create(void) {
    if (gDjuiConsole != NULL) {
        djui_base_destroy(&gDjuiConsole->panel->base);
        gDjuiConsole = NULL;
    }

    struct DjuiConsole* console = calloc(1, sizeof(struct DjuiConsole));
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CONSOLE, CONSOLE));
    djui_three_panel_set_body_size(panel, 750);
    console->panel = panel;

    djui_base_set_alignment(&panel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&panel->base, 850, 750 + (32 + 16) + 32 +  32);
    djui_base_set_visible(&panel->base, false);

    djui_interactable_create(&panel->base, NULL);
    djui_interactable_hook_key(&panel->base, djui_console_on_key_down, NULL);

    struct DjuiBase* body = djui_three_panel_get_body(panel);
    struct DjuiFlowLayout* flow = djui_flow_layout_create(body);
    struct DjuiBase* cfBase = &flow->base;
    djui_base_set_alignment(cfBase, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_base_set_location(cfBase, 0, 0);
    djui_base_set_size_type(cfBase, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(cfBase, 1.0f, 0);
    djui_base_set_color(cfBase, 0, 0, 0, 0);
    djui_base_set_padding(cfBase, 2, 2, 2, 2);
    djui_flow_layout_set_margin(flow, 2);
    djui_flow_layout_set_flow_direction(flow, DJUI_FLOW_DIR_UP);
    cfBase->addChildrenToHead = true;
    cfBase->abandonAfterChildRenderFail = true;
    console->flow = flow;

    gDjuiConsole = console;

    return console;
}
