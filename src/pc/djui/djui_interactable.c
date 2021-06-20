#include <string.h>
#include "djui.h"

void djui_interactable_on_hover_begin(struct DjuiBase* base) {
    if (base                               == NULL) { return; }
    if (base->interactable                 == NULL) { return; }
    if (base->interactable->on_hover_begin == NULL) { return; }
    base->interactable->on_hover_begin(base);
}

void djui_interactable_on_hover_end(struct DjuiBase* base) {
    if (base                               == NULL) { return; }
    if (base->interactable                 == NULL) { return; }
    if (base->interactable->on_hover_begin == NULL) { return; }
    base->interactable->on_hover_end(base);
}

void djui_interactable_create(struct DjuiBase* base,
    void (*on_hover_begin)(struct DjuiBase*),
    void (*on_hover_end)(struct DjuiBase*)) {

    if (base->interactable != NULL) {
        free(base->interactable);
    }

    struct DjuiInteractable* interactable = malloc(sizeof(struct DjuiInteractable));
    interactable->on_hover_begin = on_hover_begin;
    interactable->on_hover_end   = on_hover_end;

    base->interactable = interactable;
}