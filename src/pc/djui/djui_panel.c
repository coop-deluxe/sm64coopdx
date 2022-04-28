#include "djui.h"
#include "src/pc/utils/misc.h"
#include "sounds.h"
#include "audio/external.h"
#include "src/game/bettercamera.h"

struct DjuiPanel {
    struct DjuiBase* base;
    struct DjuiPanel* parent;
    struct DjuiBase* defaultElementBase;
};

static struct DjuiPanel* sPanelList = NULL;
static struct DjuiPanel* sPanelRemoving = NULL;
static f32 sMoveAmount = 0;

bool djui_panel_is_active(void) {
    return (sPanelList != NULL);
}

void djui_panel_add(struct DjuiBase* caller, struct DjuiBase* panelBase, struct DjuiBase* defaultElementBase) {
    if (sPanelRemoving != NULL) { return; }
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

    // allocate panel
    struct DjuiPanel* panel = calloc(1, sizeof(struct DjuiPanel));
    panel->parent = sPanelList;
    panel->base = panelBase;
    panel->defaultElementBase = defaultElementBase;
    sPanelList = panel;

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
}

void djui_panel_back(void) {
    if (sPanelRemoving != NULL) { return; }
    if (sPanelList == NULL) { return; }
    if (sPanelList->parent == NULL) {
        if (gDjuiPanelPauseCreated) { djui_panel_shutdown(); }
        return;
    }

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
            djui_base_destroy(removingBase);
            free(sPanelRemoving);
            sPanelRemoving = NULL;
        }
    }

    if (removingBase != NULL) {
        activeBase->y.value = moveMax - moveMax * smoothstep(0, moveMax, sMoveAmount);
        if (sPanelRemoving != NULL) {
            removingBase->y.value = activeBase->y.value - 1.0f;
        }
    } else if (parentBase != NULL) {
        activeBase->y.value = moveMax * smoothstep(0, moveMax, sMoveAmount) - moveMax;
        parentBase->y.value = activeBase->y.value + moveMax;
    }
}

void djui_panel_shutdown(void) {
    struct DjuiPanel* panel = sPanelList;
    while (panel != NULL) {
        struct DjuiPanel* next = panel->parent;
        djui_base_destroy(panel->base);
        free(panel);
        panel = next;
    }

    if (sPanelRemoving != NULL) {
        djui_base_destroy(sPanelRemoving->base);
        free(sPanelRemoving);
    }

    sPanelList = NULL;
    sPanelRemoving = NULL;
    sMoveAmount = 0;
    gInteractableOverridePad = false;
    gDjuiPanelJoinMessageVisible = false;
    gDjuiPanelMainCreated = false;
    gDjuiPanelPauseCreated = false;
    djui_cursor_set_visible(false);
    configfile_save(configfile_name());
    if (gDjuiInMainMenu) {
        gDjuiInMainMenu = false;
        newcam_init_settings();
    }
}