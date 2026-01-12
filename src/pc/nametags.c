#include "pc/nametags.h"
#include "pc/network/network_player.h"
#include "game/object_helpers.h"
#include "behavior_data.h"
#include "pc/djui/djui_hud_utils.h"
#include "engine/math_util.h"
#include "game/obj_behaviors.h"
#include "game/camera.h"
#include "pc/lua/utils/smlua_misc_utils.h"
#include "pc/lua/smlua_hooks.h"

#define FADE_SCALE 4.f

struct StateExtras {
    Vec3f prevPos;
    f32 prevScale;
    bool inited;
};
static struct StateExtras sStateExtras[MAX_PLAYERS];

void name_without_hex(char* input) {
    s32 i, j;
    bool inSlash = false;
    for (i = j = 0; input[i] != '\0'; i++) {
        if (input[i] == '\\') {
            inSlash = !inSlash;
        } else if (!inSlash) {
            input[j++] = input[i]; // it just works
        }
    }

    input[j] = '\0';
}

s32 hex_char_to_s32(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    return -1;
}

s32 hex_byte_to_s32(char *b) {
    s32 first = hex_char_to_s32(b[0]);
    s32 second = hex_char_to_s32(b[1]);

    if (first < 0 || second < 0){
        return -1;
    }

    return first * 16 + second;
}

bool get_hex_color(char *hex, s32 length, struct DjuiColor *color) {
    
    if (hex[0] != '#' || (length != 4 && length != 7)) return false;
    
    char hexByte[2];
    s32 rgb[3];

    s32 i;
    for (i = 1; i <= 3; i++) {
        hexByte[0] = hex[(length == 4)? i : 2 * i - 1];
        hexByte[1] = hex[(length == 4)? i : 2 * i];

        rgb[i - 1] = hex_byte_to_s32(hexByte);
    }

    if (rgb[0] >= 0 && rgb[1] >= 0 && rgb[2] >= 0){
        color->r = rgb[0];
        color->g = rgb[1];
        color->b = rgb[2];
    } else {
        return false;
    }

    return true;
}

void djui_hud_print_colored_nametag(const char *message, f32 prevX, f32 prevY, f32 prevScale, f32 x, f32 y, f32 scale) {
    
    char noHexMsg[MAX_CONFIG_STRING];
    snprintf(noHexMsg, MAX_CONFIG_STRING, "%s", message);
    name_without_hex(noHexMsg);

    f32 measure = djui_hud_measure_text(noHexMsg) * scale * 0.5f;
    prevX -= measure;
    x -= measure;

    f32 offset = scale * 2;
    f32 prevOffset = prevScale * 2;

    struct DjuiColor *color = djui_hud_get_color();

    djui_hud_set_color(0, 0, 0, color->a);
    djui_hud_print_text_interpolated(noHexMsg, prevX - prevOffset, prevY, prevScale, x - offset, y, scale);
    djui_hud_print_text_interpolated(noHexMsg, prevX + prevOffset, prevY, prevScale, x + offset, y, scale);
    djui_hud_print_text_interpolated(noHexMsg, prevX, prevY - prevOffset, prevScale, x, y - offset, scale);
    djui_hud_print_text_interpolated(noHexMsg, prevX, prevY + prevOffset, prevScale, x, y + offset, scale);

    djui_hud_set_color(color->r, color->g, color->b, color->a);

    s32 i, j;
    bool inSlash = false;
    
    char auxStr[MAX_CONFIG_STRING];
    
    for (i = j = 0; true; i++) {
        if (message[i] == '\\' || message[i] == '\0'){
            if (auxStr[0] != '\0') {
                
                auxStr[j] = '\0';
                
                if (!inSlash) {
                    djui_hud_print_text_interpolated(auxStr, prevX, prevY, prevScale, x, y, scale);
                    f32 size = djui_hud_measure_text(auxStr);
                    prevX += size * prevScale;
                    x += size * scale;
                } else if (message[i] != '\0') {
                    if (get_hex_color(auxStr, j, color)) {
                        djui_hud_set_color(color->r, color->g, color->b, color->a);
                    }
                }

                j = 0;
                auxStr[0] = '\0';

                if (message[i] == '\0') {
                    break;
                }
            }

            inSlash = !inSlash;
        } else {
            auxStr[j++] = message[i];
        }
    }
}

void nametags_render(void) {
    if (gNetworkType == NT_NONE ||
        (!gNametagsSettings.showSelfTag && network_player_connected_count() == 1) ||
        !gNetworkPlayerLocal->currAreaSyncValid ||
        find_object_with_behavior(bhvActSelector) != NULL) {
        return;
    }

    djui_hud_set_resolution(RESOLUTION_N64);
    djui_hud_set_font(FONT_SPECIAL);

    for (u8 i = gNametagsSettings.showSelfTag ? 0 : 1; i < MAX_PLAYERS; i++) {
        struct MarioState* m = &gMarioStates[i];
        if (!is_player_active(m)) { continue; }
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->currAreaSyncValid) { continue; }

        switch (m->action) {
            case ACT_START_CROUCHING:
            case ACT_CROUCHING:
            case ACT_STOP_CROUCHING:
            case ACT_START_CRAWLING:
            case ACT_CRAWLING:
            case ACT_STOP_CRAWLING:
            case ACT_IN_CANNON:
            case ACT_DISAPPEARED:
            continue;
        }

        if (m->marioBodyState->mirrorMario || m->marioBodyState->updateHeadPosTime != gGlobalTimer) { continue; }

        Vec3f pos;
        Vec3f out;
        vec3f_copy(pos, m->marioBodyState->headPos);
        pos[1] += 100;

        extern bool gDjuiHudToWorldCalcViewport;
        gDjuiHudToWorldCalcViewport = false;
        if ((i != 0 || (i == 0 && m->action != ACT_FIRST_PERSON)) &&
            djui_hud_world_pos_to_screen_pos(pos, out)) {

            char name[MAX_CONFIG_STRING];
            const char* hookedString = NULL;
            u8* color = NULL;

            smlua_call_event_hooks(HOOK_ON_NAMETAGS_RENDER, i, pos, &hookedString, &color);
            if (!djui_hud_world_pos_to_screen_pos(pos, out)) {
                continue;
            }

            if (hookedString) {
                snprintf(name, MAX_CONFIG_STRING, "%s", hookedString);
            } else {
                snprintf(name, MAX_CONFIG_STRING, "%s", np->name);
            }
             
            if (!color) {
                color = network_get_player_text_color(m->playerIndex);
            }

            f32 scale = -300 / out[2] * djui_hud_get_fov_coeff();
            f32 measure = djui_hud_measure_text(name) * scale * 0.5f;
            out[1] -= 16 * scale;

            u8 alpha = (i == 0 ? 255 : MIN(np->fadeOpacity << 3, 255)) * clamp(FADE_SCALE - scale, 0.f, 1.f);

            struct StateExtras* e = &sStateExtras[i];
            if (!e->inited) {
                vec3f_copy(e->prevPos, out);
                e->prevScale = scale;
                e->inited = true;
            }

            // Apply viewport for credits
            extern Vp *gViewportOverride;
            extern Vp *gViewportClip;
            extern Vp gViewportFullscreen;
            Vp *viewport = gViewportOverride == NULL ? gViewportClip : gViewportOverride;
            if (viewport) {
                make_viewport_clip_rect(viewport);
                gSPViewport(gDisplayListHead++, viewport);
            }

            djui_hud_set_color(color[0], color[1], color[2], alpha);

            if (gServerSettings.nametags == NAMETAGS_COLORED) {
                djui_hud_print_colored_nametag(name, e->prevPos[0], e->prevPos[1], e->prevScale, out[0], out[1], scale);
            } else {

                if (!hookedString){
                    name_without_hex(name);
                }

                djui_hud_print_outlined_text_interpolated(name,
                    e->prevPos[0] - measure, e->prevPos[1], e->prevScale, 1,
                    out[0] - measure,        out[1],        scale, 1, 0.25
                );
            }

            if (i != 0 && gNametagsSettings.showHealth) {
                djui_hud_set_color(255, 255, 255, alpha);
                f32 healthScale = 90 * scale;
                f32 prevHealthScale = 90 * e->prevScale;
                hud_render_power_meter_interpolated(m->health,
                    e->prevPos[0] - (prevHealthScale * 0.5f), e->prevPos[1] - 72 * scale, prevHealthScale, prevHealthScale,
                           out[0] - (    healthScale * 0.5f),        out[1] - 72 * scale,     healthScale,     healthScale
                );
            }

            // Reset viewport
            if (viewport) {
                gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, BORDER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BORDER_HEIGHT);
                gSPViewport(gDisplayListHead++, &gViewportFullscreen);
            }

            vec3f_copy(e->prevPos, out);
            e->prevScale = scale;
        }
        gDjuiHudToWorldCalcViewport = true;
    }
}

void nametags_reset(void) {
    for (u8 i = 0; i < MAX_PLAYERS; i++) {
        sStateExtras[i].inited = false;
    }
}
