#include <string.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_pause.h"
#include "djui_panel_modlist.h"
#include "djui_panel_playerlist.h"

#include "pc/controller/controller_sdl.h"
#include "pc/controller/controller_mouse.h"
#include "pc/controller/controller_keyboard.h"
#include "pc/utils/misc.h"
#include "pc/network/network.h"

#include "sounds.h"
#include "audio/external.h"

#define CALL_CALLBACK(x) if (base->interactable->x != NULL) { base->interactable->x(base); }
#define CALL_CALLBACK_PARAM(x, y) if (base->interactable->x != NULL) { base->interactable->x(base, y); }

enum PadHoldDirection { PAD_HOLD_DIR_NONE, PAD_HOLD_DIR_UP, PAD_HOLD_DIR_DOWN, PAD_HOLD_DIR_LEFT, PAD_HOLD_DIR_RIGHT };
static enum PadHoldDirection sKeyboardHoldDirection = PAD_HOLD_DIR_NONE;
static u16 sKeyboardButtons = 0;

static bool sIgnoreInteractableUntilCursorReleased = false;

struct DjuiBase* gDjuiHovered = NULL;
struct DjuiBase* gDjuiCursorDownOn = NULL;
struct DjuiBase* gInteractableFocus = NULL;
struct DjuiBase* gInteractableBinding = NULL;
struct DjuiBase* gInteractableMouseDown    = NULL;
bool gInteractableOverridePad         = false;
OSContPad gInteractablePad            = { 0 };
static OSContPad sLastInteractablePad = { 0 };
static int sLastMouseButtons          = 0;

static void djui_interactable_update_style(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }
    CALL_CALLBACK(update_style);
}

static void djui_interactable_on_click(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }
    djui_interactable_update_style(base);
    CALL_CALLBACK(on_click);
}

static void djui_interactable_on_hover(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }

    djui_interactable_update_style(base);
    CALL_CALLBACK(on_hover);
}

static void djui_interactable_on_hover_end(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }

    djui_interactable_update_style(base);
    CALL_CALLBACK(on_hover_end);
}

static void djui_interactable_on_cursor_down_begin(struct DjuiBase* base, bool inputCursor) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }

    if (gDjuiHovered != NULL) {
        djui_interactable_on_hover_end(gDjuiHovered);
        gDjuiHovered = NULL;
    }

    gDjuiCursorDownOn = base;

    djui_interactable_update_style(base);
    CALL_CALLBACK_PARAM(on_cursor_down_begin, inputCursor);
}

static void djui_interactable_on_cursor_down(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }
    djui_interactable_update_style(base);
    CALL_CALLBACK(on_cursor_down);
}

static void djui_interactable_on_cursor_down_end(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }

    if (gDjuiCursorDownOn == base) {
        gDjuiCursorDownOn = NULL;
    }

    djui_interactable_update_style(base);
    CALL_CALLBACK(on_cursor_down_end);

    if (djui_cursor_inside_base(base)) {
        djui_interactable_on_click(base);
    }
}

static void djui_interactable_on_focus_begin(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }

    djui_interactable_update_style(base);
    CALL_CALLBACK(on_focus_begin);
}

static void djui_interactable_on_focus(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }

    djui_interactable_update_style(base);
    CALL_CALLBACK_PARAM(on_focus, &gInteractablePad);
}

static void djui_interactable_on_focus_end(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }

    djui_interactable_update_style(base);
    CALL_CALLBACK(on_focus_end);
}

static void djui_interactable_on_value_change(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }

    djui_interactable_update_style(base);
    CALL_CALLBACK(on_value_change);
}

static void djui_interactable_on_bind(struct DjuiBase* base) {
    if (base               == NULL) { return; }
    if (base->interactable == NULL) { return; }

    djui_interactable_update_style(base);
    CALL_CALLBACK(on_bind);
}

static void djui_interactable_cursor_update_active(struct DjuiBase* base) {
    if (!base->visible) { return; }
    if (!base->enabled) { return; }

    static struct DjuiBase* insideParent = NULL;

    if (!djui_cursor_inside_base(base)) { return; }

    if (base->interactable != NULL) {
        gDjuiHovered = base;
        insideParent = base;
    } else if (insideParent == NULL) {
        gDjuiHovered = NULL;
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

bool djui_interactable_is_binding(void) {
    return gInteractableBinding != NULL;
}

void djui_interactable_set_binding(struct DjuiBase* base) {
    gInteractableBinding = base;
    djui_cursor_set_visible(base == NULL);
    if (base == NULL) {
        sIgnoreInteractableUntilCursorReleased = true;
    }
}

void djui_interactable_set_input_focus(struct DjuiBase* base) {
    if (gDjuiConsoleFocus && base != &gDjuiConsole->base) {
        return;
    }

    djui_interactable_on_focus_end(gInteractableFocus);
    gInteractableFocus = base;
    djui_interactable_on_focus_begin(base);
}

bool djui_interactable_is_input_focus(struct DjuiBase* base) {
    return gInteractableFocus == base;
}

bool djui_interactable_on_key_down(int scancode) {
    if (gInteractableBinding != NULL) {
        return true;
    }

    if (!gDjuiChatBoxFocus) {
        for (int i = 0; i < MAX_BINDS; i++) {
            if (scancode == (int)configKeyConsole[i]) { djui_console_toggle(); break; }
        }
    }

    bool keyFocused = (gInteractableFocus != NULL)
                   && (gInteractableFocus->interactable != NULL)
                   && (gInteractableFocus->interactable->on_key_down != NULL);

    if (keyFocused) {
        bool consume = gInteractableFocus->interactable->on_key_down(gInteractableFocus, scancode);
        if (consume) {
            sKeyboardHoldDirection = PAD_HOLD_DIR_NONE;
            sKeyboardButtons = 0;
            return true;
        }
    }

    if (scancode == SCANCODE_ESCAPE && djui_panel_is_active()) {
        // pressed escape button on keyboard
        djui_panel_back();
        return true;
    }

    if (gDjuiChatBox != NULL && !gDjuiChatBoxFocus) {
        bool pressChat = false;
        for (int i = 0; i < MAX_BINDS; i++) {
            if (scancode == (int)configKeyChat[i]) { pressChat = true; }
        }

        if (pressChat && !gDjuiConsoleFocus) {
            djui_chat_box_toggle();
            return true;
        }
    }

    if ((gDjuiPlayerList != NULL || gDjuiModList != NULL)) {
        for (int i = 0; i < MAX_BINDS; i++) {
            if (scancode == (int)configKeyPlayerList[i] && !gDjuiInMainMenu && gNetworkType != NT_NONE) {
                if (gServerSettings.enablePlayerList) {
                    if (gDjuiPlayerList != NULL) {
                        djui_base_set_visible(&gDjuiPlayerList->base, true);
                    }
                    if (gDjuiModList != NULL) {
                        djui_base_set_visible(&gDjuiModList->base, true);
                    }
                }
                gAttemptingToOpenPlayerlist = true;
                break;
            }
            if (gDjuiPlayerList->base.visible) {
                if (scancode == (int)configKeyNextPage[i]) {
                    sPageIndex++;
                    if (sPageIndex > ((network_player_connected_count() - 1) / sPlayerListSize)) {
                        sPageIndex = 0;
                    }
                    break;
                }
                if (scancode == (int)configKeyPrevPage[i]) {
                    if (sPageIndex == 0) {
                        sPageIndex = ((network_player_connected_count() - 1) / sPlayerListSize);
                    }
                    else {
                        sPageIndex--;
                    }
                    break;
                }
            }
        }
    }

    if (gDjuiChatBoxFocus || djui_panel_is_active()) {
        switch (scancode) {
            case SCANCODE_UP:    sKeyboardHoldDirection = PAD_HOLD_DIR_UP;    return true;
            case SCANCODE_DOWN:  sKeyboardHoldDirection = PAD_HOLD_DIR_DOWN;  return true;
            case SCANCODE_LEFT:  sKeyboardHoldDirection = PAD_HOLD_DIR_LEFT;  return true;
            case SCANCODE_RIGHT: sKeyboardHoldDirection = PAD_HOLD_DIR_RIGHT; return true;
            case SCANCODE_ENTER: sKeyboardButtons |= PAD_BUTTON_A;            return true;
        }
    }

    return false;
}

void djui_interactable_on_key_up(int scancode) {

    bool keyFocused = (gInteractableFocus != NULL)
                   && (gInteractableFocus->interactable != NULL)
                   && (gInteractableFocus->interactable->on_key_up != NULL);

    if (gDjuiPlayerList != NULL || gDjuiModList != NULL) {
        for (int i = 0; i < MAX_BINDS; i++) {
            if (scancode == (int)configKeyPlayerList[i]) {
                if (gDjuiPlayerList != NULL) {
                    djui_base_set_visible(&gDjuiPlayerList->base, false);
                }
                if (gDjuiModList != NULL) {
                    djui_base_set_visible(&gDjuiModList->base, false);
                }
                gAttemptingToOpenPlayerlist = false;
                break;
            }
        }
    }

    if (keyFocused) {
        gInteractableFocus->interactable->on_key_up(gInteractableFocus, scancode);
        sKeyboardHoldDirection = PAD_HOLD_DIR_NONE;
        sKeyboardButtons = 0;
        return;
    }

    OSContPad* pad = &gInteractablePad;
    switch (scancode) {
        case SCANCODE_UP:    if (sKeyboardHoldDirection == PAD_HOLD_DIR_UP)    { sKeyboardHoldDirection = PAD_HOLD_DIR_NONE; pad->stick_y = 0; } break;
        case SCANCODE_DOWN:  if (sKeyboardHoldDirection == PAD_HOLD_DIR_DOWN)  { sKeyboardHoldDirection = PAD_HOLD_DIR_NONE; pad->stick_y = 0; } break;
        case SCANCODE_LEFT:  if (sKeyboardHoldDirection == PAD_HOLD_DIR_LEFT)  { sKeyboardHoldDirection = PAD_HOLD_DIR_NONE; pad->stick_x = 0; } break;
        case SCANCODE_RIGHT: if (sKeyboardHoldDirection == PAD_HOLD_DIR_RIGHT) { sKeyboardHoldDirection = PAD_HOLD_DIR_NONE; pad->stick_x = 0; } break;
        case SCANCODE_ENTER: sKeyboardButtons &= ~PAD_BUTTON_A; break;
    }
}

void djui_interactable_on_text_input(char* text) {
    if (gInteractableFocus == NULL) { return; }
    if (gInteractableFocus->interactable == NULL) { return; }
    if (gInteractableFocus->interactable->on_text_input == NULL) { return; }
    gInteractableFocus->interactable->on_text_input(gInteractableFocus, text);
}

void djui_interactable_on_text_editing(char* text, int cursorPos) {
    if (gInteractableFocus == NULL) { return; }
    if (gInteractableFocus->interactable == NULL) { return; }
    if (gInteractableFocus->interactable->on_text_editing == NULL) { return; }
    gInteractableFocus->interactable->on_text_editing(gInteractableFocus, text, cursorPos);
}

void djui_interactable_update_pad(void) {
    OSContPad* pad = &gInteractablePad;

    pad->button |= sKeyboardButtons;

    static enum PadHoldDirection lastPadHoldDirection = PAD_HOLD_DIR_NONE;
    static f32 padHoldTimer = 0;

    enum PadHoldDirection padHoldDirection = sKeyboardHoldDirection;
    // allow dpad to navigate
    if (padHoldDirection == PAD_HOLD_DIR_NONE) {
        if (pad->button & U_JPAD) {
            padHoldDirection = PAD_HOLD_DIR_UP;
        } else if (pad->button & D_JPAD) {
            padHoldDirection = PAD_HOLD_DIR_DOWN;
        } else if (pad->button & L_JPAD) {
            padHoldDirection = PAD_HOLD_DIR_LEFT;
        } else if (pad->button & R_JPAD) {
            padHoldDirection = PAD_HOLD_DIR_RIGHT;
        }
    }
    if (padHoldDirection != PAD_HOLD_DIR_NONE) {
        switch (padHoldDirection) {
            case PAD_HOLD_DIR_UP:    pad->stick_x =   0; pad->stick_y = -64; break;
            case PAD_HOLD_DIR_DOWN:  pad->stick_x =   0; pad->stick_y =  64; break;
            case PAD_HOLD_DIR_LEFT:  pad->stick_x = -64; pad->stick_y =   0; break;
            case PAD_HOLD_DIR_RIGHT: pad->stick_x =  64; pad->stick_y =   0; break;
            default: break;
        }
    } else if (pad->stick_x == 0 && pad->stick_y == 0) {
        padHoldDirection = PAD_HOLD_DIR_NONE;
    } else if (abs(pad->stick_x) > abs(pad->stick_y)) {
        padHoldDirection = (pad->stick_x < 0) ? PAD_HOLD_DIR_LEFT : PAD_HOLD_DIR_RIGHT;
    } else {
        padHoldDirection = (pad->stick_y > 0) ? PAD_HOLD_DIR_UP : PAD_HOLD_DIR_DOWN;
    }

    bool validPadHold = false;
    if (padHoldDirection == PAD_HOLD_DIR_NONE) {
        // nothing to do
    } else if (padHoldDirection != lastPadHoldDirection) {
        padHoldTimer = clock_elapsed() + 0.25f;
        validPadHold = true;
    } else if (clock_elapsed() > padHoldTimer) {
        padHoldTimer = clock_elapsed() + 0.10f;
        validPadHold = true;
    }

    if (validPadHold && gInteractableFocus == NULL) {
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
    // update pad
    djui_interactable_update_pad();

    // prevent pressing buttons when they should be ignored
    int mouseButtons = mouse_window_buttons;
    u16 padButtons = gInteractablePad.button;
    if (sIgnoreInteractableUntilCursorReleased) {
        if ((padButtons & PAD_BUTTON_A) || (mouseButtons & MOUSE_BUTTON_1)) {
            padButtons   &= ~PAD_BUTTON_A;
            mouseButtons &= ~MOUSE_BUTTON_1;
        } else {
            sIgnoreInteractableUntilCursorReleased = false;
        }
    }

    // update focused
    if (gInteractableFocus) {
        u16 mainButtons = PAD_BUTTON_A | PAD_BUTTON_B;
        if ((mouseButtons & MOUSE_BUTTON_1) && !(sLastMouseButtons && MOUSE_BUTTON_1) && !djui_cursor_inside_base(gInteractableFocus)) {
            // clicked outside of focus
            if (!gDjuiChatBoxFocus) {
                djui_interactable_set_input_focus(NULL);
            }
        } else if ((padButtons & mainButtons) && !(sLastInteractablePad.button & mainButtons)) {
            // pressed main face button
            if (!gDjuiChatBoxFocus) {
                djui_interactable_set_input_focus(NULL);
            }
        } else {
            djui_interactable_on_focus(gInteractableFocus);
        }
    } else if ((padButtons & PAD_BUTTON_B) && !(sLastInteractablePad.button & PAD_BUTTON_B)) {
        // pressed back button on controller
        djui_panel_back();
    } else if ((padButtons & PAD_BUTTON_START) && !(sLastInteractablePad.button & PAD_BUTTON_START)) {
        // pressed start button
        if (gDjuiPanelPauseCreated) { djui_panel_shutdown(); }
    }

    if (gInteractableBinding != NULL) {
        djui_interactable_on_bind(gInteractableBinding);
    } else if ((padButtons & PAD_BUTTON_A) || (mouseButtons & MOUSE_BUTTON_1)) {
        // cursor down events
        if (gDjuiHovered != NULL) {
            gInteractableMouseDown = gDjuiHovered;
            gDjuiHovered = NULL;
            djui_interactable_on_cursor_down_begin(gInteractableMouseDown, !mouseButtons);
        } else {
            djui_interactable_on_cursor_down(gInteractableMouseDown);
        }
    } else {
        // cursor up event
        if (gInteractableMouseDown != NULL) {
            djui_interactable_on_cursor_down_end(gInteractableMouseDown);
            gInteractableMouseDown = NULL;
        }
        struct DjuiBase* lastHovered = gDjuiHovered;
        gDjuiHovered = NULL;
        djui_interactable_cursor_update_active(&gDjuiRoot->base);
        if (lastHovered != gDjuiHovered) {
            djui_interactable_on_hover_end(lastHovered);
            play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
        }
        djui_interactable_on_hover(gDjuiHovered);
    }

    sLastInteractablePad = gInteractablePad;
    sLastMouseButtons = mouseButtons;
}

void djui_interactable_hook_hover(struct DjuiBase* base,
                                  void (*on_hover)(struct DjuiBase*),
                                  void (*on_hover_end)(struct DjuiBase*)) {
    struct DjuiInteractable* interactable = base->interactable;
    interactable->on_hover     = on_hover;
    interactable->on_hover_end = on_hover_end;
}

void djui_interactable_hook_cursor_down(struct DjuiBase* base,
                                        void (*on_cursor_down_begin)(struct DjuiBase*, bool),
                                        void (*on_cursor_down)(struct DjuiBase*),
                                        void (*on_cursor_down_end)(struct DjuiBase*)) {
    struct DjuiInteractable* interactable = base->interactable;
    interactable->on_cursor_down_begin = on_cursor_down_begin;
    interactable->on_cursor_down       = on_cursor_down;
    interactable->on_cursor_down_end   = on_cursor_down_end;
}

void djui_interactable_hook_focus(struct DjuiBase* base,
                                        void (*on_focus_begin)(struct DjuiBase*),
                                        void (*on_focus)(struct DjuiBase*, OSContPad*),
                                        void (*on_focus_end)(struct DjuiBase*)) {
    struct DjuiInteractable* interactable = base->interactable;
    interactable->on_focus_begin = on_focus_begin;
    interactable->on_focus       = on_focus;
    interactable->on_focus_end   = on_focus_end;
}

void djui_interactable_hook_click(struct DjuiBase* base,
                                  void (*on_click)(struct DjuiBase*)) {
    struct DjuiInteractable* interactable = base->interactable;
    interactable->on_click = on_click;
}

void djui_interactable_hook_value_change(struct DjuiBase* base,
                                         void (*on_value_change)(struct DjuiBase*)) {
    struct DjuiInteractable* interactable = base->interactable;
    interactable->on_value_change = on_value_change;
}

void djui_interactable_hook_bind(struct DjuiBase* base,
                                 void (*on_bind)(struct DjuiBase*)) {
    struct DjuiInteractable* interactable = base->interactable;
    interactable->on_bind = on_bind;
}

void djui_interactable_hook_key(struct DjuiBase* base,
                                 bool (*on_key_down)(struct DjuiBase*, int),
                                 void (*on_key_up)(struct DjuiBase*, int)) {
    struct DjuiInteractable *interactable = base->interactable;
    interactable->on_key_down = on_key_down;
    interactable->on_key_up   = on_key_up;

}

void djui_interactable_hook_text_input(struct DjuiBase *base,
                                       void (*on_text_input)(struct DjuiBase*, char*)) {
    struct DjuiInteractable *interactable = base->interactable;
    interactable->on_text_input = on_text_input;
}

void djui_interactable_hook_text_editing(struct DjuiBase* base,
                                       void (*on_text_editing)(struct DjuiBase*, char*, int)) {
    struct DjuiInteractable *interactable = base->interactable;
    interactable->on_text_editing = on_text_editing;
}

void djui_interactable_hook_enabled_change(struct DjuiBase *base,
                                           void (*on_enabled_change)(struct DjuiBase*)) {
    struct DjuiInteractable *interactable = base->interactable;
    interactable->on_enabled_change = on_enabled_change;
}

void djui_interactable_create(struct DjuiBase* base, void (*update_style)(struct DjuiBase*)) {

    if (base->interactable != NULL) {
        free(base->interactable);
    }

    struct DjuiInteractable* interactable = calloc(1, sizeof(struct DjuiInteractable));
    interactable->enabled = true;
    base->interactable = interactable;

    base->interactable->update_style = update_style;
}
