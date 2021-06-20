#pragma once
#include "djui.h"
#include "djui_base.h"

#pragma pack(1)
struct DjuiInteractable {
    void (*on_hover_begin)(struct DjuiBase*);
    void (*on_hover_end)(struct DjuiBase*);
};

void djui_interactable_on_hover_begin(struct DjuiBase* base);
void djui_interactable_on_hover_end(struct DjuiBase* base);

void djui_interactable_create(struct DjuiBase* base,
                              void (*on_hover_begin)(struct DjuiBase*),
                              void (*on_hover_end)(struct DjuiBase*));
