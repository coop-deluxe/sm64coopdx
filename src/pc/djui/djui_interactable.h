#pragma once
#include "djui.h"
#include "djui_base.h"

#define PAD_BUTTON_A     ((u16)(1 << 15))
#define PAD_BUTTON_B     ((u16)(1 << 14))
#define PAD_BUTTON_Z     ((u16)(1 << 13))
#define PAD_BUTTON_START ((u16)(1 << 12))

#define MOUSE_BUTTON_1  ((u16)(1 << 0))

#define SCANCODE_UP        328
#define SCANCODE_DOWN      336
#define SCANCODE_LEFT      331
#define SCANCODE_RIGHT     333
#define SCANCODE_PAGE_DOWN 337
#define SCANCODE_PAGE_UP   329
#define SCANCODE_POS1      327
#define SCANCODE_END       335

#define SCANCODE_ENTER  28
#define SCANCODE_SPACE  57
#define SCANCODE_ESCAPE 1
#define SCANCODE_TAB    15
#define SCANCODE_LSHIFT 42
#define SCANCODE_RSHIFT 54

struct DjuiInteractable {
    bool enabled;
    void (*update_style)(struct DjuiBase*);
    void (*on_hover)(struct DjuiBase*);
    void (*on_hover_end)(struct DjuiBase*);
    void (*on_cursor_down_begin)(struct DjuiBase*, bool);
    void (*on_cursor_down)(struct DjuiBase*);
    void (*on_cursor_down_end)(struct DjuiBase*);
    void (*on_focus_begin)(struct DjuiBase*);
    void (*on_focus)(struct DjuiBase*, OSContPad*);
    void (*on_focus_end)(struct DjuiBase*);
    void (*on_click)(struct DjuiBase*);
    void (*on_value_change)(struct DjuiBase*);
    void (*on_bind)(struct DjuiBase*);
    bool (*on_key_down)(struct DjuiBase*, int scancode);
    void (*on_key_up)(struct DjuiBase*, int scancode);
    void (*on_text_input)(struct DjuiBase*, char* text);
    void (*on_text_editing)(struct DjuiBase*, char* text, int cursorPos);
    void (*on_enabled_change)(struct DjuiBase*);
};

extern bool gInteractableOverridePad;
extern OSContPad gInteractablePad;
extern struct DjuiBase* gDjuiHovered;
extern struct DjuiBase* gDjuiCursorDownOn;
extern struct DjuiBase* gInteractableFocus;
extern struct DjuiBase* gInteractableBinding;
extern struct DjuiBase* gInteractableMouseDown;
extern const u8 sPlayerListSize;
extern u8 sPageIndex;

bool djui_interactable_is_binding(void);
void djui_interactable_set_binding(struct DjuiBase* base);
void djui_interactable_set_input_focus(struct DjuiBase* base);
bool djui_interactable_is_input_focus(struct DjuiBase* base);
bool djui_interactable_on_key_down(int scancode);
void djui_interactable_on_key_up(int scancode);
void djui_interactable_on_text_input(char *text);
void djui_interactable_on_text_editing(char* text, int cursorPos);

void djui_interactable_update(void);

void djui_interactable_hook_hover(struct DjuiBase* base,
                                  void (*on_hover)(struct DjuiBase*),
                                  void (*on_hover_end)(struct DjuiBase*));

void djui_interactable_hook_cursor_down(struct DjuiBase* base,
                                        void (*on_cursor_down_begin)(struct DjuiBase*, bool),
                                        void (*on_cursor_down)(struct DjuiBase*),
                                        void (*on_cursor_down_end)(struct DjuiBase*));

void djui_interactable_hook_focus(struct DjuiBase* base,
                                  void (*on_focus_begin)(struct DjuiBase*),
                                  void (*on_focus)(struct DjuiBase*, OSContPad*),
                                  void (*on_focus_end)(struct DjuiBase*));

void djui_interactable_hook_click(struct DjuiBase* base,
                                  void (*on_click)(struct DjuiBase*));

void djui_interactable_hook_value_change(struct DjuiBase* base,
                                         void (*on_value_change)(struct DjuiBase*));

void djui_interactable_hook_bind(struct DjuiBase* base,
                                 void (*on_bind)(struct DjuiBase*));

void djui_interactable_hook_key(struct DjuiBase* base,
                                 bool (*on_key_down)(struct DjuiBase*, int),
                                 void (*on_key_up)(struct DjuiBase*, int));

void djui_interactable_hook_text_input(struct DjuiBase* base,
                                       void (*on_text_input)(struct DjuiBase*, char*));

void djui_interactable_hook_text_editing(struct DjuiBase* base,
                                       void (*on_text_editing)(struct DjuiBase*, char*, int));

void djui_interactable_hook_enabled_change(struct DjuiBase *base,
                                           void (*on_enabled_change)(struct DjuiBase*));

void djui_interactable_create(struct DjuiBase* base,
                              void (*update_style)(struct DjuiBase*));
