#include <string.h>
#include <time.h>
#include "djui.h"

#include "src/pc/controller/controller_sdl.h"
#include "src/pc/controller/controller_mouse.h"
#include "src/pc/controller/controller_keyboard.h"

#define PAD_BUTTON_A (1 << 15)

#define SCANCODE_UP    328
#define SCANCODE_DOWN  336
#define SCANCODE_LEFT  331
#define SCANCODE_RIGHT 333

#define SCANCODE_ENTER  28
#define SCANCODE_SPACE  57
#define SCANCODE_ESCAPE 1

enum PadHoldDirection { PAD_HOLD_DIR_NONE, PAD_HOLD_DIR_UP, PAD_HOLD_DIR_DOWN, PAD_HOLD_DIR_LEFT, PAD_HOLD_DIR_RIGHT };
static enum PadHoldDirection sKeyboardHoldDirection = PAD_HOLD_DIR_NONE;

static struct DjuiBase* sHovered   = NULL;
static struct DjuiBase* sMouseDown = NULL;
static u8 sInputCursorDown         = false;

static void djui_interactable_on_click(struct DjuiBase* base) {
    if (base                         == NULL) { return; }
    if (base->interactable           == NULL) { return; }
    if (base->interactable->on_click == NULL) { return; }
    base->interactable->on_click(base);
}

static void djui_interactable_on_hover_begin(struct DjuiBase* base) {
    if (base                               == NULL) { return; }
    if (base->interactable                 == NULL) { return; }
    if (base->interactable->on_hover_begin == NULL) { return; }
    base->interactable->on_hover_begin(base);
}

static void djui_interactable_on_hover_end(struct DjuiBase* base) {
    if (base                               == NULL) { return; }
    if (base->interactable                 == NULL) { return; }
    if (base->interactable->on_hover_begin == NULL) { return; }
    base->interactable->on_hover_end(base);
}

static void djui_interactable_on_cursor_down_begin(struct DjuiBase* base) {
    if (base                                    == NULL) { return; }
    if (base->interactable                      == NULL) { return; }
    if (base->interactable->on_cursor_down_begin == NULL) { return; }

    if (sHovered != NULL) {
        djui_interactable_on_hover_end(sHovered);
        sHovered = NULL;
    }

    base->interactable->on_cursor_down_begin(base);
}

static void djui_interactable_on_cursor_down_end(struct DjuiBase* base) {
    if (base                                  == NULL) { return; }
    if (base->interactable                    == NULL) { return; }
    if (base->interactable->on_cursor_down_end == NULL) { return; }
    base->interactable->on_cursor_down_end(base);

    if (djui_cursor_inside_base(base)) {
        djui_interactable_on_click(base);
    }
}

static void djui_interactable_cursor_update_active(struct DjuiBase* base) {
    if (!base->visible) { return; }
    if (!base->enabled) { return; }

    static struct DjuiBase* insideParent = NULL;

    if (!djui_cursor_inside_base(base)) { return; }

    if (base->interactable != NULL) {
        sHovered = base;
        insideParent = base;
    } else if (insideParent == NULL) {
        sHovered = NULL;
    }

    // check all children
    struct DjuiBaseChild* child = base->child;
    while (child != NULL) {
        djui_interactable_cursor_update_active(child->base);
        child = child->next;
    }

    if (insideParent == base) {
        insideParent = NULL;
    }
}

void djui_interactable_on_key_down(int scancode) {
    switch (scancode) {
        case SCANCODE_UP:    sKeyboardHoldDirection = PAD_HOLD_DIR_UP;    break;
        case SCANCODE_DOWN:  sKeyboardHoldDirection = PAD_HOLD_DIR_DOWN;  break;
        case SCANCODE_LEFT:  sKeyboardHoldDirection = PAD_HOLD_DIR_LEFT;  break;
        case SCANCODE_RIGHT: sKeyboardHoldDirection = PAD_HOLD_DIR_RIGHT; break;
        case SCANCODE_ENTER: sInputCursorDown |= (1 << 0);                break;
    }
}

void djui_interactable_on_key_up(int scancode) {
    switch (scancode) {
        case SCANCODE_UP:    if (sKeyboardHoldDirection == PAD_HOLD_DIR_UP)    { sKeyboardHoldDirection = PAD_HOLD_DIR_NONE; } break;
        case SCANCODE_DOWN:  if (sKeyboardHoldDirection == PAD_HOLD_DIR_DOWN)  { sKeyboardHoldDirection = PAD_HOLD_DIR_NONE; } break;
        case SCANCODE_LEFT:  if (sKeyboardHoldDirection == PAD_HOLD_DIR_LEFT)  { sKeyboardHoldDirection = PAD_HOLD_DIR_NONE; } break;
        case SCANCODE_RIGHT: if (sKeyboardHoldDirection == PAD_HOLD_DIR_RIGHT) { sKeyboardHoldDirection = PAD_HOLD_DIR_NONE; } break;
        case SCANCODE_ENTER: sInputCursorDown &= ~(1 << 0); break;
    }
    if (scancode == SCANCODE_ENTER) {
        sInputCursorDown &= ~(1 << 0);
    }
}

void djui_interactable_update_pad(void) {
    OSContPad* pad = &gControllerPads[0];

    sInputCursorDown &= ~(1 << 1);
    if (pad->button & PAD_BUTTON_A) {
        sInputCursorDown |=  (1 << 1);
    }

    static enum PadHoldDirection lastPadHoldDirection = PAD_HOLD_DIR_NONE;
    static clock_t padHoldTimer = 0;

    enum PadHoldDirection padHoldDirection = PAD_HOLD_DIR_NONE;
    if (pad->stick_x == 0 && pad->stick_y == 0) {
        padHoldDirection = PAD_HOLD_DIR_NONE;
    } else if (abs(pad->stick_x) > abs(pad->stick_y)) {
        padHoldDirection = (pad->stick_x < 0) ? PAD_HOLD_DIR_LEFT : PAD_HOLD_DIR_RIGHT;
    } else {
        padHoldDirection = (pad->stick_y > 0) ? PAD_HOLD_DIR_UP : PAD_HOLD_DIR_DOWN;
    }

    if (sKeyboardHoldDirection != PAD_HOLD_DIR_NONE) {
        padHoldDirection = sKeyboardHoldDirection;
    }

    bool validPadHold = false;
    if (padHoldDirection == PAD_HOLD_DIR_NONE) {
        // nothing to do
    } else if (padHoldDirection != lastPadHoldDirection) {
        padHoldTimer = clock() + CLOCKS_PER_SEC * 0.25f;
        validPadHold = true;
    } else if (clock() > padHoldTimer) {
        padHoldTimer = clock() + CLOCKS_PER_SEC * 0.10f;
        validPadHold = true;
    }

    if (validPadHold) {
        switch (padHoldDirection) {
            case PAD_HOLD_DIR_UP:    djui_cursor_move( 0, -1); break;
            case PAD_HOLD_DIR_DOWN:  djui_cursor_move( 0,  1); break;
            case PAD_HOLD_DIR_LEFT:  djui_cursor_move(-1,  0); break;
            case PAD_HOLD_DIR_RIGHT: djui_cursor_move( 1,  0); break;
            default: break;
        }
    }

    lastPadHoldDirection = padHoldDirection;
}

void djui_interactable_update(void) {
    djui_interactable_update_pad();
    if ((sInputCursorDown) || (mouse_window_buttons & 0b0001)) {
        if (sHovered != NULL) {
            sMouseDown = sHovered;
            sHovered = NULL;
            djui_interactable_on_cursor_down_begin(sMouseDown);
        }
    } else {
        if (sMouseDown != NULL) {
            djui_interactable_on_cursor_down_end(sMouseDown);
            sMouseDown = NULL;
        }
        struct DjuiBase* lastHovered = sHovered;
        sHovered = NULL;
        djui_interactable_cursor_update_active(&gDjuiRoot->base);
        if (lastHovered != sHovered) {
            djui_interactable_on_hover_end(lastHovered);
        }
        djui_interactable_on_hover_begin(sHovered);
    }

}

void djui_interactable_create(struct DjuiBase* base,
    void (*on_hover_begin)(struct DjuiBase*),
    void (*on_hover_end)(struct DjuiBase*),
    void (*on_cursor_down_begin)(struct DjuiBase*),
    void (*on_cursor_down_end)(struct DjuiBase*)) {

    if (base->interactable != NULL) {
        free(base->interactable);
    }

    struct DjuiInteractable* interactable = malloc(sizeof(struct DjuiInteractable));
    interactable->on_hover_begin      = on_hover_begin;
    interactable->on_hover_end        = on_hover_end;
    interactable->on_cursor_down_begin = on_cursor_down_begin;
    interactable->on_cursor_down_end   = on_cursor_down_end;
    interactable->on_click            = NULL;

    base->interactable = interactable;
}