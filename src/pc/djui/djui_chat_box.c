#include <stdio.h>
#include <string.h>
#include "pc/network/network.h"
#include "pc/lua/smlua_hooks.h"
#include "djui.h"

struct DjuiChatBox* gDjuiChatBox = NULL;
bool gDjuiChatBoxFocus = false;

bool djui_chat_box_render(struct DjuiBase* base) {
    struct DjuiChatBox* chatBox = (struct DjuiChatBox*)base;
    struct DjuiBase* ccBase = &chatBox->chatContainer->base;
    djui_base_set_size(ccBase, 1.0f, chatBox->base.comp.height - 32 - 8);
    return true;
}

static void djui_chat_box_destroy(struct DjuiBase* base) {
    struct DjuiChatBox* chatBox = (struct DjuiChatBox*)base;
    free(chatBox);
}

static void djui_chat_box_set_focus_style(void) {
    djui_base_set_visible(&gDjuiChatBox->chatInput->base, gDjuiChatBoxFocus);
    if (gDjuiChatBoxFocus) {
        djui_interactable_set_input_focus(&gDjuiChatBox->chatInput->base);
    }

    djui_base_set_color(&gDjuiChatBox->chatFlow->base, 0, 0, 0, gDjuiChatBoxFocus ? 128 : 0);
}

static void djui_chat_box_input_enter(struct DjuiInputbox* chatInput) {
    djui_interactable_set_input_focus(NULL);

    if (strlen(chatInput->buffer) != 0) {
        if (chatInput->buffer[0] == '/') {
            if (!smlua_call_chat_command_hook(chatInput->buffer)) {
                djui_chat_message_create("Unrecognized chat command.");
                smlua_display_chat_commands();
            }
        } else {
            djui_chat_message_create_from(gNetworkPlayerLocal->globalIndex, chatInput->buffer);
            network_send_chat(chatInput->buffer, gNetworkPlayerLocal->globalIndex);
        }
    }

    djui_inputbox_set_text(chatInput, "");
    djui_inputbox_select_all(chatInput);
    if (gDjuiChatBoxFocus) { djui_chat_box_toggle(); }
}

static void djui_chat_box_input_escape(struct DjuiInputbox* chatInput) {
    djui_interactable_set_input_focus(NULL);
    djui_inputbox_set_text(chatInput, "");
    djui_inputbox_select_all(chatInput);
    if (gDjuiChatBoxFocus) { djui_chat_box_toggle(); }
}

static bool djui_chat_box_input_on_key_down(struct DjuiBase* base, int scancode) {
    if (gDjuiChatBox == NULL) { return false; }
    f32 yMax = gDjuiChatBox->chatContainer->base.elem.height - gDjuiChatBox->chatFlow->base.height.value;

    f32* yValue = &gDjuiChatBox->chatFlow->base.y.value;
    bool canScrollUp   = (*yValue > yMax);
    bool canScrollDown = (*yValue < 0);
    f32 pageAmount = gDjuiChatBox->chatFlow->base.elem.height / 3.0f;

    switch (scancode) {
        case SCANCODE_UP:
            gDjuiChatBox->scrolling = true;
            if (canScrollDown) { *yValue = fmin(*yValue + 15, 0); }
            return true;
        case SCANCODE_DOWN:
            gDjuiChatBox->scrolling = true;
            if (canScrollUp) { *yValue = fmax(*yValue - 15, yMax); }
            return true;
        case SCANCODE_PAGE_UP:
            gDjuiChatBox->scrolling = true;
            if (canScrollDown) { *yValue = fmin(*yValue + pageAmount, 0); }
            return true;
        case SCANCODE_PAGE_DOWN:
            gDjuiChatBox->scrolling = true;
            if (canScrollUp) { *yValue = fmax(*yValue - pageAmount, yMax); }
            return true;
        case SCANCODE_ENTER:  djui_chat_box_input_enter(gDjuiChatBox->chatInput);  return true;
        case SCANCODE_ESCAPE: djui_chat_box_input_escape(gDjuiChatBox->chatInput); return true;
        default: return djui_inputbox_on_key_down(base, scancode);
    }
}

void djui_chat_box_toggle(void) {
    if (gDjuiChatBox == NULL) { return; }
    gDjuiChatBoxFocus = !gDjuiChatBoxFocus;
    djui_chat_box_set_focus_style();
    gDjuiChatBox->scrolling = false;
    gDjuiChatBox->chatFlow->base.y.value = gDjuiChatBox->chatContainer->base.elem.height - gDjuiChatBox->chatFlow->base.height.value;
}

struct DjuiChatBox* djui_chat_box_create(void) {
    if (gDjuiChatBox != NULL) {
        djui_base_destroy(&gDjuiChatBox->base);
        gDjuiChatBox = NULL;
    }

    struct DjuiChatBox* chatBox = calloc(1, sizeof(struct DjuiChatBox));
    struct DjuiBase* base = &chatBox->base;

    djui_base_init(&gDjuiRoot->base, base, djui_chat_box_render, djui_chat_box_destroy);
    djui_base_set_size_type(base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 600, 400);
    djui_base_set_alignment(base, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_base_set_color(base, 0, 0, 0, 0);
    djui_base_set_padding(base, 0, 8, 8, 8);

    struct DjuiRect* chatContainer = djui_rect_create(base);
    struct DjuiBase* ccBase = &chatContainer->base;
    djui_base_set_size_type(ccBase, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(ccBase, 1.0f, 0);
    djui_base_set_color(ccBase, 0, 0, 0, 0);
    chatBox->chatContainer = chatContainer;

    struct DjuiFlowLayout* chatFlow = djui_flow_layout_create(ccBase);
    struct DjuiBase* cfBase = &chatFlow->base;
    djui_base_set_location(cfBase, 0, 0);
    djui_base_set_size_type(cfBase, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(cfBase, 1.0f, 2);
    djui_base_set_color(cfBase, 0, 0, 0, 128);
    djui_base_set_padding(cfBase, 2, 2, 2, 2);
    djui_flow_layout_set_margin(chatFlow, 2);
    djui_flow_layout_set_flow_direction(chatFlow, DJUI_FLOW_DIR_UP);
    cfBase->addChildrenToHead = true;
    cfBase->abandonAfterChildRenderFail = true;
    chatBox->chatFlow = chatFlow;

    struct DjuiInputbox* chatInput = djui_inputbox_create(base, 200);
    struct DjuiBase* ciBase = &chatInput->base;
    djui_base_set_size_type(ciBase, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(ciBase, 1.0f, 32);
    djui_base_set_alignment(ciBase, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_interactable_hook_key(&chatInput->base, djui_chat_box_input_on_key_down, djui_inputbox_on_key_up);
    chatBox->chatInput = chatInput;

    gDjuiChatBox = chatBox;
    djui_chat_box_set_focus_style();
    return chatBox;
}
