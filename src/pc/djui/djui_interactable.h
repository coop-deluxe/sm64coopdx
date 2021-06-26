#pragma once
#include "djui.h"
#include "djui_base.h"

#define PAD_BUTTON_A ((u16)(1 << 15))
#define PAD_BUTTON_B ((u16)(1 << 14))

#define MOUSE_BUTTON_1  ((u16)(1 << 0))

#pragma pack(1)
struct DjuiInteractable {
    bool enabled;
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
};

extern bool gInteractableOverridePad;
extern OSContPad gInteractablePad;

void djui_interactable_set_input_focus(struct DjuiBase* base);
void djui_interactable_on_key_down(int scancode);
void djui_interactable_on_key_up(int scancode);
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

void djui_interactable_create(struct DjuiBase* base);
