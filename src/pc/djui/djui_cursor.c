#include "djui.h"
#include "djui_panel.h"
#include "pc/controller/controller_mouse.h"
#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/pc_main.h"

extern ALIGNED8 u8 gd_texture_hand_open[];
extern ALIGNED8 u8 gd_texture_hand_closed[];

struct DjuiImage* sMouseCursor = NULL;

static bool sCursorMouseControlled = false;
static struct DjuiBase* sInputControlledBase = NULL;

static f32 sSavedMouseX = 0;
static f32 sSavedMouseY = 0;
f32 gCursorX = 0;
f32 gCursorY = 0;

void djui_cursor_set_visible(bool visible) {
    if (sMouseCursor) {
        djui_base_set_visible(&sMouseCursor->base, visible);
    }

    if (wm_api) {
        if (configWindow.fullscreen) {
            wm_api->set_cursor_visible(false);
        } else {
            wm_api->set_cursor_visible(!visible);
        }
    }
    sSavedMouseX = mouse_window_x;
    sSavedMouseY = mouse_window_y;
}

bool djui_cursor_inside_base(struct DjuiBase* base) {
    struct DjuiBaseRect* clip = &base->elem;
    if (gCursorX < clip->x)                { return false; }
    if (gCursorX > clip->x + clip->width)  { return false; }
    if (gCursorY < clip->y)                { return false; }
    if (gCursorY > clip->y + clip->height) { return false; }
    return true;
}

static void djui_cursor_base_hover_location(struct DjuiBase* base, f32* x, f32* y) {
    base->get_cursor_hover_location(base, x, y);
}

void djui_cursor_input_controlled_center(struct DjuiBase* base) {
    if (!sCursorMouseControlled && (!base || (base && base->interactable && base->interactable->enabled))) {
        sInputControlledBase = base;
        djui_cursor_set_visible(base != NULL);
    }
}

static f32 djui_cursor_base_distance(struct DjuiBase* base, f32 xScale, f32 yScale) {
    f32 x, y;
    djui_cursor_base_hover_location(base, &x, &y);
    x -= gCursorX;
    y -= gCursorY;
    return sqrtf((x * x) * xScale + (y * y) * yScale);
}

static void djui_cursor_move_check(s8 xDir, s8 yDir, struct DjuiBase** pick, struct DjuiBase* base) {
    if (!base->visible) { return; }

    if (base->interactable != NULL && base->interactable->enabled) {
        f32 x1, y1, x2, y2;
        x1 = base->elem.x;
        y1 = base->elem.y;
        x2 = base->elem.x + base->elem.width;
        y2 = base->elem.y + base->elem.height;
        bool xWithin = (gCursorX >= x1 && gCursorX <= x2) || sCursorMouseControlled;
        bool yWithin = (gCursorY >= y1 && gCursorY <= y2) || sCursorMouseControlled;

        bool valid = false;
        if (yDir > 0 && gCursorY < y1 && xWithin) { valid = true; }
        if (yDir < 0 && gCursorY > y2 && xWithin) { valid = true; }
        if (xDir > 0 && gCursorX < x1 && yWithin) { valid = true; }
        if (xDir < 0 && gCursorX > x2 && yWithin) { valid = true; }

        f32 xH, yH;
        djui_cursor_base_hover_location(base, &xH, &yH);
        if (valid) {
            if (*pick == NULL) {
                *pick = base;
            } else {
                f32 pickDist = djui_cursor_base_distance(*pick, xDir ? 1.0f : 2.0f, yDir ? 1.0f : 2.0f);
                f32 baseDist = djui_cursor_base_distance(base,  xDir ? 1.0f : 2.0f, yDir ? 1.0f : 2.0f);
                if (baseDist < pickDist) { *pick = base; }
            }
        }
    }

    // check all children
    struct DjuiBaseChild* child = base->child;
    while (child != NULL) {
        djui_cursor_move_check(xDir, yDir, pick, child->base);
        child = child->next;
    }
}

void djui_cursor_move(s8 xDir, s8 yDir) {
    if (xDir == 0 && yDir == 0) { return; }

    struct DjuiBase* pick = NULL;
    djui_cursor_move_check(xDir, yDir, &pick, &gDjuiRoot->base);
    if (pick != NULL) {
        sCursorMouseControlled = false;
        djui_cursor_input_controlled_center(pick);
    }
}

void djui_cursor_update(void) {
#if defined(CAPI_SDL2) || defined(CAPI_SDL1)
    if (djui_interactable_is_binding()) { return; }
    if (sMouseCursor == NULL) { return; }
    if (!djui_panel_is_active()) { return; }

    controller_mouse_read_window();

    // check if mouse is in control again
    static bool sFirstUpdate = true;
    if (sFirstUpdate) {
        sFirstUpdate = false;
        sCursorMouseControlled = false;
        sSavedMouseX = mouse_window_x;
        sSavedMouseY = mouse_window_y;
    } else if (!sCursorMouseControlled || (sMouseCursor && !sMouseCursor->base.visible)) {
        f32 dist = sqrtf(powf(mouse_window_x - sSavedMouseX, 2) + powf(mouse_window_y - sSavedMouseY, 2));
        if (dist > 5) {
            sCursorMouseControlled = true;
            djui_cursor_set_visible(true);
        }
    }

    // update mouse cursor
    if (sCursorMouseControlled) {
        gCursorX = mouse_window_x / djui_gfx_get_scale();
        gCursorY = mouse_window_y / djui_gfx_get_scale();
    } else if (sInputControlledBase != NULL) {
        djui_cursor_base_hover_location(sInputControlledBase, &gCursorX, &gCursorY);
    }

    // set cursor position
    djui_base_set_location(&sMouseCursor->base, gCursorX - 13, gCursorY - 13);

    // set cursor sprite
    if ((gInteractablePad.button & PAD_BUTTON_A) || (mouse_window_buttons & MOUSE_BUTTON_1)) {
        djui_image_set_image(sMouseCursor, gd_texture_hand_closed, 32, 32, 16);
    } else {
        djui_image_set_image(sMouseCursor, gd_texture_hand_open, 32, 32, 16);
    }
#endif
    djui_base_render(&sMouseCursor->base);
}

void djui_cursor_create(void) {
    sMouseCursor = djui_image_create(NULL, gd_texture_hand_open, 32, 32, 16);
    djui_base_set_location(&sMouseCursor->base, 0, 0);
    djui_base_set_size(&sMouseCursor->base, 64, 64);
}
