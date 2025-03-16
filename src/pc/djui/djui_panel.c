#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_main.h"
#include "djui_panel_pause.h"
#include "djui_panel_join_message.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "sounds.h"
#include "audio/external.h"
#include "game/bettercamera.h"

static struct DjuiPanel* sPanelList = NULL;
static struct DjuiPanel* sPanelRemoving = NULL;
static f32 sMoveAmount = 0;

bool gDjuiPanelDisableBack = false;

bool djui_panel_is_active(void) {
    return (sPanelList != NULL);
}

static struct DjuiBase* djui_panel_find_first_interactable(struct DjuiBaseChild* child) {
    while (child) {
        if (child->base->interactable && child->base->interactable->enabled) {
            return child->base;
        }
        struct DjuiBase* check = djui_panel_find_first_interactable(child->base->child);
        if (check) { return check; }
        child = child->next;
    }

    // If we didn't find anything at all. Return NULL.
    // LOG_ERROR("Failed to find a interactable for child %p.", child);
    return NULL;
}

struct DjuiPanel* djui_panel_add(struct DjuiBase* caller, struct DjuiThreePanel* threePanel, struct DjuiBase* defaultElementBase) {
    if (sPanelRemoving != NULL) { return NULL; }
    struct DjuiBase* panelBase = &threePanel->base;
    bool firstPanel = (sPanelList == NULL);
    gDjuiPanelJoinMessageVisible = false;

    // remember element that triggered this panel add
    if (sPanelList != NULL) {
        sPanelList->defaultElementBase = caller;
    }

    // hide second from the top immediately
    if (sPanelList != NULL && sPanelList->parent != NULL) {
        djui_base_set_visible(sPanelList->parent->base, false);
    }

    // calculate 3panel body height
    djui_three_panel_recalculate_body_size(threePanel);

    // allocate panel
    struct DjuiPanel* panel = calloc(1, sizeof(struct DjuiPanel));
    panel->parent = sPanelList;
    panel->base = panelBase;
    panel->defaultElementBase = defaultElementBase;
    panel->on_back = threePanel->on_back;
    panel->on_panel_destroy = NULL;
    panel->temporary = threePanel->temporary;
    sPanelList = panel;

    // find better defaultElementBase
    if (panel->defaultElementBase == NULL) {
        panel->defaultElementBase = djui_panel_find_first_interactable(panel->base->child);
    }

    // deselect cursor input
    djui_cursor_input_controlled_center(NULL);

    // hide new panel off screen initially
    djui_base_set_location_type(panelBase, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_location(panelBase, 0, -1.0f);

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
    } else {
        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
    }

    return panel;
}

void djui_panel_back(void) {
    if (sPanelRemoving != NULL) { return; }
    if (sPanelList == NULL) { return; }
    if (gDjuiPanelDisableBack) { return; }
    if (sPanelList->parent == NULL) {
        if (gDjuiPanelPauseCreated) { djui_panel_shutdown(); }
        return;
    }

    // call back hook, return true to cancel back
    if (sPanelList->on_back) {
        if (sPanelList->on_back(sPanelList->base)) {
            return;
        }
    }

    // deselect cursor input
    djui_cursor_input_controlled_center(NULL);

    // remember which panel to remove
    sPanelRemoving = sPanelList;

    // disable old active
    djui_base_set_enabled(sPanelRemoving->base, false);

    // set the previous active
    sPanelList = sPanelList->parent;
    if (sPanelList->temporary) { sPanelList = sPanelList->parent; }

    // reset move amount
    sMoveAmount = 0;

    // set new active as visible
    djui_base_set_visible(sPanelList->base, true);

    // play a sound
    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);

    gDjuiPanelJoinMessageVisible = false;
}

void djui_panel_update(void) {
    if (sPanelList == NULL) { return; }
    if (sPanelList->base == NULL) { return; }
    if (sPanelList->base->elem.height == 0) { return; }

    struct DjuiBase* activeBase   = sPanelList->base;
    struct DjuiBase* parentBase   = (sPanelList->parent == NULL) ? NULL : sPanelList->parent->base;
    struct DjuiBase* removingBase = (sPanelRemoving     == NULL) ? NULL : sPanelRemoving->base;

    float moveMax = 1.0f;
    if (sMoveAmount >= moveMax) {
        sMoveAmount = moveMax;
        djui_base_set_enabled(activeBase, true);
        activeBase->y.value = 0;
        return;
    }

    extern u8 gRenderingInterpolated;
    sMoveAmount += (gRenderingInterpolated ? 1.0f : 2.0f) * (moveMax / 10.0f);
    if (sMoveAmount >= moveMax) {
        sMoveAmount = moveMax;
        if (parentBase != NULL) {
            djui_base_set_visible(parentBase, false);
        }
        djui_base_set_enabled(activeBase, true);
        activeBase->y.value = 0;
        djui_cursor_input_controlled_center(sPanelList->defaultElementBase);

        if (removingBase != NULL) {
            struct DjuiPanel* panel = sPanelRemoving;
            sPanelRemoving = NULL;
            if (panel->on_panel_destroy) {
                panel->on_panel_destroy(NULL);
            }
            if (activeBase == removingBase) { activeBase = NULL; }
            if (parentBase == removingBase) { parentBase = NULL; }
            djui_base_destroy(removingBase);
            free(panel);
            removingBase = NULL;
            return;
        }
    }

    if (activeBase && removingBase) {
        activeBase->y.value = moveMax - moveMax * smooth_step(0, moveMax, sMoveAmount);
        if (sPanelRemoving) {
            removingBase->y.value = activeBase->y.value - 1.0f;
        }
    } else if (activeBase && parentBase) {
        activeBase->y.value = moveMax * smooth_step(0, moveMax, sMoveAmount) - moveMax;
        parentBase->y.value = activeBase->y.value + moveMax;
    }
}

extern bool gDjuiShuttingDown;
void djui_panel_shutdown(void) {
    static bool sShuttingDown = false;
    if (sShuttingDown) { return; }
    sShuttingDown = true;
    struct DjuiPanel* panel = sPanelList;
    while (panel != NULL) {
        struct DjuiPanel* next = panel->parent;
        if (panel->on_panel_destroy) {
            panel->on_panel_destroy(NULL);
        }
        djui_base_destroy(panel->base);
        free(panel);
        panel = next;
    }

    if (sPanelRemoving != NULL) {
        struct DjuiPanel* panel = sPanelRemoving;
        sPanelRemoving = NULL;
        if (panel->on_panel_destroy) {
            panel->on_panel_destroy(NULL);
        }
        djui_base_destroy(panel->base);
        free(panel);
    }

    sPanelList = NULL;
    sPanelRemoving = NULL;
    sMoveAmount = 0;
    gInteractableOverridePad = false;
    gDjuiPanelJoinMessageVisible = false;
    gDjuiPanelMainCreated = false;
    gDjuiPanelPauseCreated = false;
    djui_cursor_set_visible(false);
    if (!gDjuiShuttingDown) {
        configfile_save(configfile_name());
        if (gDjuiInMainMenu) {
            gDjuiInMainMenu = false;
            newcam_init_settings();
        }
    }
    sShuttingDown = false;
}