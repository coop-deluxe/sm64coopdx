#include <stdio.h>
#include <string.h>
#include "djui.h"
#include "djui_console.h"
#include "pc/pc_main.h"
#include "pc/commands.h"
#include "engine/math_util.h"

#define MAX_CONSOLE_MESSAGES 500

struct DjuiConsole* gDjuiConsole = NULL;
bool gDjuiConsoleFocus = false;
char gDjuiConsoleTmpBuffer[CONSOLE_MAX_TMP_BUFFER] = "";
u32 sDjuiConsoleMessages = 0;
bool sDjuiConsoleQueueMessages = true;
bool sIgnoreNextTextInput = false;

struct ConsoleQueuedMessage {
    char* message;
    enum ConsoleMessageLevel level;
    struct ConsoleQueuedMessage* next;
};

struct ConsoleQueuedMessage* sConsoleQueuedMessages = NULL;

static void djui_console_message_queue(const char* message, enum ConsoleMessageLevel level) {
    struct ConsoleQueuedMessage* queued = malloc(sizeof(struct ConsoleQueuedMessage));
    queued->message = strdup(message);
    queued->level = level;
    queued->next = NULL;
    if (sConsoleQueuedMessages == NULL) {
        sConsoleQueuedMessages = queued;
        return;
    }

    struct ConsoleQueuedMessage* entry = sConsoleQueuedMessages;
    while (entry->next) { entry = entry->next; }
    entry->next = queued;
}

void djui_console_message_dequeue(void) {
    if (!gDjuiConsole) { return; }
    sDjuiConsoleQueueMessages = false;
    struct ConsoleQueuedMessage* entry = sConsoleQueuedMessages;
    while (entry) {
        struct ConsoleQueuedMessage* next = entry->next;
        djui_console_message_create(entry->message, entry->level);
        free(entry->message);
        free(entry);
        entry = next;
    }
    sConsoleQueuedMessages = NULL;
}

bool djui_console_render(struct DjuiBase* base) {
    struct DjuiConsole* console = (struct DjuiConsole*)base;
    djui_base_set_size(&console->base, gDjuiRoot->base.width.value, gDjuiRoot->base.height.value * 0.5f);
    djui_base_set_size(&console->rectContainer->base, gDjuiRoot->base.width.value, gDjuiRoot->base.height.value * 0.5f - 32);
    if (console->scrolling) {
        f32 yMax = console->base.comp.height - console->flow->base.height.value - 32;
        f32 target = console->flow->base.y.value + (console->scrollY - console->flow->base.y.value) * (configSmoothScrolling ? 0.5f : 1.f);

        console->flow->base.y.value = clamp(target, yMax, 0.0f);
        if (target < yMax || 0.f < target) {
            console->scrollY = clamp(target, yMax, 0.f);
            if (target > 0.f) { gDjuiConsole->scrolling = false; }
        }
    } else { console->scrollY = console->flow->base.y.value; }

    djui_rect_render(base);
    return true;
}

static void djui_console_destroy(struct DjuiBase* base) {
    struct DjuiConsole* console = (struct DjuiConsole*)base;
    free(console);
}

void djui_console_toggle(void) {
    if (gDjuiConsole == NULL) { return; }
    sIgnoreNextTextInput = true;
    gDjuiConsoleFocus = !gDjuiConsoleFocus;
    djui_base_set_visible(&gDjuiConsole->base, gDjuiConsoleFocus);

    if (gDjuiConsoleFocus) {
        if (gDjuiChatBoxFocus) { djui_chat_box_toggle(); }
        djui_interactable_set_input_focus(&gDjuiConsole->inputbox->base);
    } else {
        djui_interactable_set_input_focus(NULL);
    }
}

static void djui_console_on_scroll(UNUSED struct DjuiBase *base, UNUSED float x, float y) {
    if (gDjuiConsole == NULL) { return; }

    f32 yMax = gDjuiConsole->base.comp.height - gDjuiConsole->flow->base.height.value;

    y *= 24.f;
    if (gDjuiInputHeldControl) { y /= 2; }
    if (gDjuiInputHeldShift) { y *= 3; }

    gDjuiConsole->scrollY -= y;

    if (!gDjuiConsole->scrolling) {
        gDjuiConsole->scrolling = y > 0 && gDjuiConsole->scrollY > yMax;
    }
}

static void djui_console_enter() {
    char* buffer = gDjuiConsole->inputbox->buffer;
    if (strcmp(buffer, "") == 0) return;
    if (buffer[0] == '/') buffer++;
    run_command(buffer);
    djui_inputbox_set_text(gDjuiConsole->inputbox, "");
    djui_inputbox_select_all(gDjuiConsole->inputbox);
}

static bool djui_console_on_key_down(struct DjuiBase* base, int scancode) {
    if (gDjuiConsole == NULL) { return false; }
    f32 yMax = gDjuiConsole->base.comp.height - gDjuiConsole->flow->base.height.value;

    f32 pageAmount = gDjuiConsole->base.comp.height * 3.0f / 4.0f;

    for (int i = 0; i < MAX_BINDS; i++) {
        if (scancode == (int)configKeyConsole[i]) {
            djui_console_toggle();
            return true;
        }
    }

    switch (scancode) {
        case SCANCODE_UP:
            gDjuiConsole->scrollY -= 15;
            break;
        case SCANCODE_DOWN:
            gDjuiConsole->scrollY += 15;
            break;
        case SCANCODE_PAGE_UP:
            gDjuiConsole->scrollY -= pageAmount;
            break;
        case SCANCODE_PAGE_DOWN:
            gDjuiConsole->scrollY += pageAmount;
            break;
        case SCANCODE_ENTER:
            djui_console_enter();
            break;
        case SCANCODE_ESCAPE:
            djui_console_toggle();
            break;
        default:
            return djui_inputbox_on_key_down(base, scancode);
    }

    if (!gDjuiConsole->scrolling) {
        gDjuiConsole->scrolling = gDjuiConsole->scrollY < 0 && gDjuiConsole->scrollY > yMax;
    }
    return true;
}

static void djui_console_on_text_input(struct DjuiBase* base, char* text) {
    if (sIgnoreNextTextInput) {
        sIgnoreNextTextInput = false;
        return;
    }
    djui_inputbox_on_text_input(base, text);
}

void djui_console_clear() {
    if (gDjuiConsole == NULL) { return; }

    struct DjuiBase* cfBase = &gDjuiConsole->flow->base;
    djui_base_destroy_children(cfBase);

    cfBase->height.value = 0;
    cfBase->y.value = 0;
    gDjuiConsole->scrollY = 0;
    gDjuiConsole->scrolling = false;
    sDjuiConsoleMessages = 0;
}

void djui_console_message_create(const char* message, enum ConsoleMessageLevel level) {
    if (sDjuiConsoleQueueMessages || !gDjuiConsole) {
        djui_console_message_queue(message, level);
        return;
    }
    djui_base_compute_tree(&gDjuiConsole->base);

    struct DjuiBase* cfBase = &gDjuiConsole->flow->base;

    f32 maxTextWidth = gDjuiConsole->base.comp.width - gDjuiConsole->base.padding.left.value - gDjuiConsole->base.padding.right.value;

    struct DjuiText* text = djui_text_create(cfBase, message);
    struct DjuiBase* tBase = &text->base;
    djui_base_set_alignment(tBase, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_base_set_size_type(tBase, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(tBase, maxTextWidth, 32);
    switch (level) {
        case CONSOLE_MESSAGE_INFO:
            djui_base_set_color(tBase, 220, 220, 220, 255);
            break;
        case CONSOLE_MESSAGE_WARNING:
            djui_base_set_color(tBase, 255, 255, 160, 255);
            break;
        case CONSOLE_MESSAGE_ERROR:
            djui_base_set_color(tBase, 255, 160, 160, 255);
            break;
    }

    // figure out chat message height
    text->base.comp.width = maxTextWidth;
    f32 messageHeight = djui_text_count_lines(text, 10) * (text->font->lineHeight * text->font->defaultFontScale) + 8;
    djui_base_set_size(tBase, maxTextWidth, messageHeight);

    f32 heightAdjust = messageHeight + gDjuiConsole->flow->margin.value;
    cfBase->height.value += heightAdjust;

    if (gDjuiConsole->scrolling && gDjuiConsole->scrollY != 0) {
        cfBase->y.value -= heightAdjust;
        gDjuiConsole->scrollY -= heightAdjust;
    }

    sDjuiConsoleMessages++;
    if (sDjuiConsoleMessages >= MAX_CONSOLE_MESSAGES) {
        if (cfBase->child) {
            heightAdjust = cfBase->child->base->height.value + gDjuiConsole->flow->margin.value;
            cfBase->height.value -= heightAdjust;
            if (gDjuiConsole->scrolling && gDjuiConsole->scrollY != 0) {
                cfBase->y.value += heightAdjust;
                gDjuiConsole->scrollY += heightAdjust;
            }
        }

        djui_base_destroy_one_child(cfBase);
        sDjuiConsoleMessages--;
    }
}

struct DjuiConsole* djui_console_create(void) {
    if (gDjuiConsole != NULL) {
        djui_base_destroy(&gDjuiConsole->base);
        gDjuiConsole = NULL;
    }

    struct DjuiConsole* console = calloc(1, sizeof(struct DjuiConsole));
    struct DjuiBase* base = &console->base;

    djui_base_init(NULL, base, djui_console_render, djui_console_destroy);
    djui_base_set_size_type(base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, gDjuiRoot->base.width.value, gDjuiRoot->base.height.value * 0.5f);
    djui_base_set_alignment(base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    djui_base_set_color(base, 0, 0, 0, 200);
    djui_base_set_padding(base, 0, 8, 8, 8);
    djui_base_set_visible(base, false);

    struct DjuiRect* rectContainer = djui_rect_container_create(base, 0);
    djui_base_set_alignment(&rectContainer->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    djui_base_set_size_type(&rectContainer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&rectContainer->base, 1.0f, gDjuiRoot->base.height.value * 0.5f);
    console->rectContainer = rectContainer;

    struct DjuiFlowLayout* flow = djui_flow_layout_create(&rectContainer->base);
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

    struct DjuiInputbox* inputbox = djui_inputbox_create(base, MAX_CONSOLE_INPUT_LENGTH);
    inputbox->base.interactable->update_style = NULL;
    djui_base_set_border_color(&inputbox->base, 0, 0, 0, 0);
    djui_base_set_color(&inputbox->base, 0, 0, 0, 0);
    djui_base_set_size_type(&inputbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&inputbox->base, 1.0f, 32);
    djui_base_set_alignment(&inputbox->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
    djui_interactable_hook_key(&inputbox->base, djui_console_on_key_down, djui_inputbox_on_key_up);
    djui_interactable_hook_text_input(&inputbox->base, djui_console_on_text_input);
    djui_interactable_hook_text_editing(&inputbox->base, djui_inputbox_on_text_editing);
    djui_interactable_hook_scroll(&inputbox->base, djui_console_on_scroll);
    djui_inputbox_set_text_color(inputbox, 255, 255, 255, 255);
    inputbox->yOffset = 6;
    console->inputbox = inputbox;

    gDjuiConsole = console;

    return console;
}
