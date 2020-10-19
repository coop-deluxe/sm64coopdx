#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_menu_system.h"
#include "custom_menu.h"

#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "game/ingame_menu.h"
#include "game/game_init.h"
#include "game/segment2.h"
#include "object_fields.h"
#include "model_ids.h"
#include "behavior_data.h"
#include "audio_defines.h"
#include "audio/external.h"
#include "gfx_dimensions.h"
#include "config.h"

static struct CustomMenu* sHead = NULL;
static struct CustomMenu* sCurrentMenu = NULL;
static struct CustomMenu* sLastMenu = NULL;
struct CustomMenuButtonScale gButtonScale = {
    .small = 0.08111111f,
    .medium = 0.09511111f,
    .large = 0.11111111f,
};

u8 gMenuStringAlpha = 255;

struct ErrorDialog {
    u8* dialog;
    struct ErrorDialog* next;
};
static struct ErrorDialog* sErrorDialog = NULL;

struct CustomMenuButton* custom_menu_create_button(struct CustomMenu* parent, char* label, u16 x, u16 y, f32 scale, s32 clickSound, void (*on_click)(void)) {
    struct CustomMenuButton* button = calloc(1, sizeof(struct CustomMenuButton));
    if (parent->buttons == NULL) {
        parent->buttons = button;
    } else {
        struct CustomMenuButton* parentButton = parent->buttons;
        while (parentButton->next != NULL) { parentButton = parentButton->next; }
        parentButton->next = button;
    }
    button->label = calloc(strlen(label), sizeof(char) + 1);
    strcpy(button->label, label);

    button->on_click = on_click;
    button->clickSound = clickSound;

    struct Object* obj = spawn_object_rel_with_rot(parent->me->object, MODEL_MAIN_MENU_MARIO_NEW_BUTTON, bhvMenuButton, x * -1, y, -1, 0, 0x8000, 0);

    obj->oMenuButtonScale = scale;
    obj->oFaceAngleRoll = 0;
    obj->oMenuButtonTimer = 0;
    obj->oMenuButtonOrigPosX = obj->oParentRelativePosX;
    obj->oMenuButtonOrigPosY = obj->oParentRelativePosY;
    obj->oMenuButtonOrigPosZ = obj->oParentRelativePosZ;
    obj->oMenuButtonIsCustom = 1;
    obj->oMenuButtonState = MENU_BUTTON_STATE_DEFAULT;
    button->object = obj;
    return button;
}

struct CustomMenu* custom_menu_create(struct CustomMenu* parent, char* label, u16 x, u16 y, f32 scale) {
    struct CustomMenuButton* button = custom_menu_create_button(parent, label, x, y, scale, SOUND_MENU_CAMERA_ZOOM_IN, NULL);
    struct CustomMenu* menu = calloc(1, sizeof(struct CustomMenu));
    menu->parent = parent;
    menu->depth = parent->depth + 1;
    menu->headerY = 25;
    menu->me = button;
    button->menu = menu;
    return menu;
}

void custom_menu_system_init(void) {
    // allocate the main menu and set it to current
    sHead = calloc(1, sizeof(struct CustomMenu));
    sHead->me = calloc(1, sizeof(struct CustomMenuButton));
    sCurrentMenu = sHead;

    // spawn the main menu game object
    struct Object* obj = spawn_object_rel_with_rot(gCurrentObject, MODEL_MAIN_MENU_GREEN_SCORE_BUTTON, bhvMenuButton, 0, 0, 0, 0, 0, 0);
    obj->oParentRelativePosZ += 1000;
    obj->oMenuButtonState = MENU_BUTTON_STATE_FULLSCREEN;
    obj->oFaceAngleYaw = 0x8000;
    obj->oFaceAngleRoll = 0;
    obj->oMenuButtonScale = 9.0f;
    obj->oMenuButtonOrigPosZ = obj->oPosZ;
    obj->oMenuButtonOrigPosX = 99999;
    obj->oMenuButtonIsCustom = 1;
    sHead->me->object = obj;

    custom_menu_init(sHead);
}

void custom_menu_destroy(void) {
    //  TODO: clean up all of the calloc()'d memory
}

void custom_menu_system_loop(void) {
    custom_menu_loop();
}

static void button_force_instant_close(struct Object* obj) {
    obj->oFaceAngleYaw = 0x8000;
    obj->oFaceAnglePitch = 0;
    obj->oParentRelativePosX = obj->oMenuButtonOrigPosX;
    obj->oParentRelativePosY = obj->oMenuButtonOrigPosY;
    obj->oParentRelativePosZ = obj->oMenuButtonOrigPosZ;
    obj->oMenuButtonScale = 0.11111111f;
    obj->oMenuButtonState = MENU_BUTTON_STATE_DEFAULT;
    obj->oMenuButtonTimer = 0;
}

static void button_force_instant_open(struct Object* obj) {
    obj->oFaceAngleYaw = 0;
    obj->oFaceAnglePitch = 0;
    obj->oParentRelativePosX = 0.0f;
    obj->oParentRelativePosY = 0.0f;
    obj->oParentRelativePosZ = -801;
    obj->oMenuButtonScale = 0.623111;
    obj->oMenuButtonState = MENU_BUTTON_STATE_FULLSCREEN;
    obj->oMenuButtonTimer = 0;
}

void custom_menu_open(struct CustomMenu* menu) {
    if (sCurrentMenu == menu) { return; }
    if (menu == NULL) { return; }
    // force instant-close all parents if not a direct route
    {
        // check all buttons of current menu to see if the desired menu is directly beneath it
        struct CustomMenuButton* onButton = sCurrentMenu->buttons;
        u8 foundMenu = FALSE;
        while (onButton != NULL) {
            if (onButton == menu->me) { foundMenu = TRUE; break; }
            onButton = onButton->next;
        }

        // if not direct route, force close all the way to the main menu
        if (!foundMenu) {
            struct CustomMenu* onMenu = sCurrentMenu;
            while (onMenu != NULL && onMenu != sHead) {
                struct Object* obj = onMenu->me->object;
                if (obj->oMenuButtonState != MENU_BUTTON_STATE_FULLSCREEN) { break; }
                button_force_instant_close(obj);
                if (onMenu->on_close != NULL) { onMenu->on_close(); }
                onMenu = onMenu->parent;
            }
        }
    }

    // force instant-open all parents
    {
        struct CustomMenu* onMenu = menu->parent;
        while (onMenu != NULL) {
            struct Object* obj = onMenu->me->object;
            if (obj->oMenuButtonState == MENU_BUTTON_STATE_FULLSCREEN) { break; }
            button_force_instant_open(obj);
            onMenu = onMenu->parent;
        }
    }
    struct Object* obj = menu->me->object;
    obj->oMenuButtonState = MENU_BUTTON_STATE_GROWING;
    obj->oMenuButtonTimer = 0;
    gMenuStringAlpha = 0;
    sLastMenu = sCurrentMenu;
    sCurrentMenu = menu;
}

void custom_menu_close(void) {
    struct Object* obj = sCurrentMenu->me->object;
    obj->oMenuButtonState = MENU_BUTTON_STATE_SHRINKING;
    obj->oMenuButtonTimer = 0;
    gMenuStringAlpha = 0;
    if (sCurrentMenu->on_close != NULL) { sCurrentMenu->on_close(); }
    sLastMenu = sCurrentMenu;
    if (sCurrentMenu->parent != NULL) {
        sCurrentMenu = sCurrentMenu->parent;
    }
}

void custom_menu_close_system(void) {
    sHead->me->object->oMenuButtonState = MENU_BUTTON_STATE_SHRINKING;
    gInCustomMenu = FALSE;
}

static s32 cursor_inside_button(struct CustomMenuButton* button, f32 cursorX, f32 cursorY) {
    f32 x = button->object->oParentRelativePosX;
    f32 y = button->object->oParentRelativePosY;
    f32 scale = button->object->oMenuButtonScale;

    x *= -0.137f;
    y *= 0.137f;

    s16 maxX = x + scale * 185.0f;
    s16 minX = x - scale * 185.0f;
    s16 maxY = y + scale * 185.0f;
    s16 minY = y - scale * 101.0f;

    return (cursorX < maxX && minX < cursorX && cursorY < maxY && minY < cursorY);
}

void custom_menu_cursor_click(f32 cursorX, f32 cursorY) {

#ifdef VERSION_EU
    u16 cursorClickButtons = (A_BUTTON | B_BUTTON | START_BUTTON | Z_TRIG);
#else
    u16 cursorClickButtons = (A_BUTTON | B_BUTTON | START_BUTTON);
#endif
    if (!(gPlayer3Controller->buttonPressed & cursorClickButtons)) { return; }
    if (sCurrentMenu->me->object->oMenuButtonState != MENU_BUTTON_STATE_FULLSCREEN) { return; }

    if (sErrorDialog != NULL) {
        struct ErrorDialog* current = sErrorDialog;
        sErrorDialog = sErrorDialog->next;
        free(current->dialog);
        free(current);
        play_sound(SOUND_ACTION_BONK, gDefaultSoundArgs);
        if (sErrorDialog != NULL) {
            play_sound(SOUND_MARIO_OOOF2, gDefaultSoundArgs);
        }
        return;
    }

    struct CustomMenuButton* button = sCurrentMenu->buttons;
    while (button != NULL) {
        if (cursor_inside_button(button, cursorX, cursorY)) {
            u8 didSomething = FALSE;

            if (button->menu != NULL) {
                custom_menu_open(button->menu);
                didSomething = TRUE;
            }

            if (button->on_click != NULL) {
                button->on_click();
                didSomething = TRUE;
            }

            if (button->clickSound != 0) {
                play_sound(button->clickSound, gDefaultSoundArgs);
            }

            if (didSomething) { break; }
        }
        button = button->next;
    }
}

static void button_label_pos(struct CustomMenuButton* button, s16* outX, s16* outY) {
    f32 x = button->object->oParentRelativePosX;
    f32 y = button->object->oParentRelativePosY;
    x -= strlen(button->label) * -27.0f;
    y += -163.0f;
    *outX = 165.0f + x * -0.137f;
    *outY = 110.0f + y * 0.137f;
}

void custom_menu_print_strings(void) {
    // figure out alpha
    struct Object* curObj = sCurrentMenu->me->object;
    struct Object* lastObj = (sLastMenu != NULL) ? sLastMenu->me->object : NULL;

    if (curObj != NULL && lastObj != NULL) {
        if (curObj->oMenuButtonState == MENU_BUTTON_STATE_FULLSCREEN && lastObj->oMenuButtonState != MENU_BUTTON_STATE_SHRINKING) {
            if (gMenuStringAlpha < 250) {
                gMenuStringAlpha += 10;
            } else {
                gMenuStringAlpha = 255;
            }
        }
    }

    // print header
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gMenuStringAlpha);
        char* headerLabel = sCurrentMenu->me->label;
        u16 headerLabelLen = strlen(headerLabel);
        u16 headerX = (u16)(159.66f - (headerLabelLen * 5.66f));

        unsigned char header[64];
        str_ascii_to_dialog(headerLabel, header, headerLabelLen);

        print_hud_lut_string(HUD_LUT_DIFF, headerX, sCurrentMenu->headerY, header);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);

    // print text
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    struct CustomMenuButton* button = sCurrentMenu->buttons;
    while (button != NULL) {
        gDPSetEnvColor(gDisplayListHead++, 222, 222, 222, gMenuStringAlpha);
        s16 x, y;
        button_label_pos(button, &x, &y);
        print_generic_ascii_string(x, y, button->label);
        button = button->next;
    }
    if (sCurrentMenu->draw_strings != NULL) { sCurrentMenu->draw_strings(); }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void custom_menu_render_top(void) {
    // print error message
    if (sErrorDialog != NULL) {
        // black screen
        create_dl_translation_matrix(MENU_MTX_PUSH, GFX_DIMENSIONS_FROM_LEFT_EDGE(0), 240.0f, 0);
        create_dl_scale_matrix(MENU_MTX_NOPUSH, GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT / 130.0f, 3.0f, 1.0f);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 240);
        gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        // print text
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        f32 textWidth = get_generic_dialog_width(sErrorDialog->dialog);
        f32 textHeight = get_generic_dialog_height(sErrorDialog->dialog);

        f32 xPos = (SCREEN_WIDTH - textWidth) / 2.0f;
        f32 yPos = (SCREEN_HEIGHT + textHeight) / 2.0f;

        gDPSetEnvColor(gDisplayListHead++, 30, 30, 30, 255);
        print_generic_string(xPos, yPos, sErrorDialog->dialog);

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_generic_string((xPos - 1), (yPos + 1), sErrorDialog->dialog);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    }
}

/**
 * Grow from submenu, used by selecting a file in the score menu.
 */
void bhv_menu_button_growing_from_custom(struct Object* button) {
    if (button->oMenuButtonTimer < 16) {
        button->oFaceAngleYaw += 0x800;
    }
    if (button->oMenuButtonTimer < 8) {
        button->oFaceAnglePitch += 0x800;
    }
    if (button->oMenuButtonTimer >= 8 && button->oMenuButtonTimer < 16) {
        button->oFaceAnglePitch -= 0x800;
    }

    button->oParentRelativePosX -= button->oMenuButtonOrigPosX / 16.0;
    button->oParentRelativePosY -= button->oMenuButtonOrigPosY / 16.0;
    button->oParentRelativePosZ -= 50;

    button->oMenuButtonScale += 0.032f;

    button->oMenuButtonTimer++;
    if (button->oMenuButtonTimer == 16) {
        button->oParentRelativePosX = 0.0f;
        button->oParentRelativePosY = 0.0f;
        button->oMenuButtonState = MENU_BUTTON_STATE_FULLSCREEN;
        button->oMenuButtonTimer = 0;
    }
}

/**
 * Shrink back to submenu, used to return back while inside a score save menu.
 */
void bhv_menu_button_shrinking_to_custom(struct Object* button) {
    if (button->oMenuButtonTimer < 16) {
        button->oFaceAngleYaw -= 0x800;
    }
    if (button->oMenuButtonTimer < 8) {
        button->oFaceAnglePitch -= 0x800;
    }
    if (button->oMenuButtonTimer >= 8 && button->oMenuButtonTimer < 16) {
        button->oFaceAnglePitch += 0x800;
    }

    button->oParentRelativePosX += button->oMenuButtonOrigPosX / 16.0;
    button->oParentRelativePosY += button->oMenuButtonOrigPosY / 16.0;
    button->oParentRelativePosZ += 50;

    button->oMenuButtonScale -= 0.032f;

    button->oMenuButtonTimer++;
    if (button->oMenuButtonTimer == 16) {
        button->oParentRelativePosX = button->oMenuButtonOrigPosX;
        button->oParentRelativePosY = button->oMenuButtonOrigPosY;
        button->oMenuButtonScale = 0.11111111f;
        button->oMenuButtonState = MENU_BUTTON_STATE_DEFAULT;
        button->oMenuButtonTimer = 0;
    }
}

void custom_menu_error(char* message) {
    struct ErrorDialog* errorDialog = malloc(sizeof(struct ErrorDialog));
    memset(errorDialog, 0, sizeof(struct ErrorDialog));
    errorDialog->dialog = malloc(sizeof(u8) * (strlen(message) + 1));
    str_ascii_to_dialog(message, errorDialog->dialog, strlen(message));

    if (sErrorDialog == NULL) {
        sErrorDialog = errorDialog;
        play_sound(SOUND_MARIO_OOOF2, gDefaultSoundArgs);
    } else {
        struct ErrorDialog* item = sErrorDialog;
        while (item != NULL) {
            if (item->next == NULL) {
                item->next = errorDialog;
                break;
            }
            item = item->next;
        }
    }
}
