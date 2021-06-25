#include "djui.h"
#include "src/pc/utils/misc.h"

struct DjuiPanel {
    struct DjuiBase* base;
    struct DjuiPanel* parent;
    struct DjuiBase* defaultElementBase;
};

static struct DjuiPanel* sPanelList = NULL;
static struct DjuiPanel* sPanelRemoving = NULL;
static f32 sMoveAmount = 0;

void djui_panel_add(struct DjuiBase* caller, struct DjuiBase* panelBase, struct DjuiBase* defaultElementBase) {
    bool firstPanel = (sPanelList == NULL);

    // remember element that triggered this panel add
    if (sPanelList != NULL) {
        sPanelList->defaultElementBase = caller;
    }

    // allocate panel
    struct DjuiPanel* panel = malloc(sizeof(struct DjuiPanel));
    panel->parent = sPanelList;
    panel->base = panelBase;
    panel->defaultElementBase = defaultElementBase;
    sPanelList = panel;

    // deselect cursor input
    djui_cursor_input_controlled_center(NULL);

    // hide new panel off screen initially
    djui_base_set_location(panelBase, 0, -gDjuiRoot->base.height.value);

    // disable panels
    djui_base_set_enabled(panel->base, false);
    if (panel->parent != NULL) {
        djui_base_set_enabled(panel->parent->base, false);
    }

    // reset move amount
    sMoveAmount = 0;

    if (firstPanel) {
        djui_base_set_location(panelBase, 0, 0);
        djui_cursor_input_controlled_center(panel->defaultElementBase);
        djui_base_set_enabled(panel->base, true);
    }
}

void djui_panel_back(void) {
    if (sPanelList == NULL) { return; }
    if (sPanelList->parent == NULL) { return; }

    // deselect cursor input
    djui_cursor_input_controlled_center(NULL);

    // remember which panel to remove
    sPanelRemoving = sPanelList;

    // disable old active
    djui_base_set_enabled(sPanelRemoving->base, false);

    // set the previous active
    sPanelList = sPanelList->parent;

    // reset move amount
    sMoveAmount = 0;

    // set new active as visible
    djui_base_set_visible(sPanelList->base, true);
}

void djui_panel_update(void) {
    if (sPanelList == NULL) { return; }
    if (sPanelList->base == NULL) { return; }
    if (sPanelList->base->elem.height == 0) { return; }

    struct DjuiBase* activeBase   = sPanelList->base;
    struct DjuiBase* parentBase   = (sPanelList->parent == NULL) ? NULL : sPanelList->parent->base;
    struct DjuiBase* removingBase = (sPanelRemoving     == NULL) ? NULL : sPanelRemoving->base;

    float moveMax = activeBase->elem.height;
    if (sMoveAmount >= moveMax) { return; }

    sMoveAmount += moveMax / 10.0f;
    if (sMoveAmount >= moveMax) {
        sMoveAmount = moveMax;
        if (parentBase != NULL) {
            djui_base_set_visible(parentBase, false);
        }
        djui_base_set_enabled(activeBase, true);
        djui_cursor_input_controlled_center(sPanelList->defaultElementBase);

        if (removingBase != NULL) {
            djui_base_destroy(removingBase);
            free(sPanelRemoving);
            sPanelRemoving = NULL;
        }
    }

    if (removingBase != NULL) {
        activeBase->y.value = moveMax - moveMax * smoothstep(0, moveMax, sMoveAmount);
        if (sPanelRemoving != NULL) {
            removingBase->y.value = activeBase->y.value - removingBase->elem.height;
        }
    } else if (parentBase != NULL) {
        activeBase->y.value = moveMax * smoothstep(0, moveMax, sMoveAmount) - moveMax;
        parentBase->y.value = activeBase->y.value + moveMax;
    }
}