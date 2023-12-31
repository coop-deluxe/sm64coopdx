#include "pc/nametags.h"
#include "pc/network/network_player.h"
#include "game/object_helpers.h"
#include "behavior_data.h"
#include "pc/djui/djui_hud_utils.h"
#include "engine/math_util.h"
#include "game/obj_behaviors.h"
#include "game/camera.h"
#include "pc/lua/utils/smlua_math_utils.h"
#include "pc/lua/utils/smlua_misc_utils.h"

#define NAMETAG_MAX_SCALE 0.32f
#define NAMETAG_DIST 7000.0f

struct StateExtras {
    Vec3f prevPos;
    f32 prevScale;
};
struct StateExtras sStateExtras[MAX_PLAYERS];

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

void djui_hud_print_outlined_text_interpolated(const char* text, f32 prevX, f32 prevY, f32 prevScale, f32 x, f32 y, f32 scale, u8 r, u8 g, u8 b, u8 a, f32 outlineDarkness) {
    f32 offset = 1 * (scale * 2);
    f32 prevOffset = 1 * (prevScale * 2);

    // render outline
    djui_hud_set_color(r * outlineDarkness, g * outlineDarkness, b * outlineDarkness, a);
    djui_hud_print_text_interpolated(text, prevX - prevOffset, prevY,              prevScale, x - offset, y,          scale);
    djui_hud_print_text_interpolated(text, prevX + prevOffset, prevY,              prevScale, x + offset, y,          scale);
    djui_hud_print_text_interpolated(text, prevX,              prevY - prevOffset, prevScale, x,          y - offset, scale);
    djui_hud_print_text_interpolated(text, prevX,              prevY + prevOffset, prevScale, x,          y + offset, scale);
    // render text
    djui_hud_set_color(r, g, b, 255);
    djui_hud_print_text_interpolated(text, prevX, prevY, prevScale, x, y, scale);
    djui_hud_set_color(255, 255, 255, 255);
}

void nametags_render(void) {
    if ((!gNametagsSettings.showSelfTag && network_player_connected_count() == 1) ||
        !gNetworkPlayerLocal->currAreaSyncValid ||
        find_object_with_behavior(bhvActSelector) != NULL) {
        return;
    }

    djui_hud_set_resolution(RESOLUTION_N64);
    djui_hud_set_font(FONT_NORMAL);

    for (u8 i = gNametagsSettings.showSelfTag ? 0 : 1; i < MAX_PLAYERS; i++) {
        struct MarioState* m = &gMarioStates[i];
        if (!is_player_active(m)) { continue; }
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        Vec3f pos;
        Vec3f out;
        vec3f_copy(pos, m->marioObj->header.gfx.pos);
        pos[1] = m->pos[1] + 210;

        if (djui_hud_world_pos_to_screen_pos(pos, out) &&
            m->marioBodyState->updateTorsoTime == gMarioStates[0].marioBodyState->updateTorsoTime &&
            m->action != ACT_IN_CANNON &&
            (i != 0 || (i == 0 && m->action != ACT_FIRST_PERSON))) {
            f32 scale = NAMETAG_MAX_SCALE;
            f32 dist = vec3f_dist(gLakituState.pos, m->pos);
            if (i != 0 && dist > 1000) {
                scale = 0.5f + dist / NAMETAG_DIST;
                scale = clampf(1 - scale, 0, NAMETAG_MAX_SCALE);
            }

            char name[MAX_PLAYER_STRING + 1];
            strncpy(name, np->name, MAX_PLAYER_STRING + 1);
            name_without_hex(name);
            Color color = {
                np->palette.parts[SHIRT][0],
                np->palette.parts[SHIRT][1],
                np->palette.parts[SHIRT][2]
            };
            f32 measure = djui_hud_measure_text(name) * scale * 0.5f;
            f32 alpha = m->action == ACT_START_CROUCHING ||
                m->action == ACT_CROUCHING ||
                m->action == ACT_STOP_CROUCHING ||
                m->action == ACT_START_CRAWLING ||
                m->action == ACT_CRAWLING ||
                m->action == ACT_STOP_CRAWLING ? 100 : 255;

            struct StateExtras* e = &sStateExtras[i];
            djui_hud_print_outlined_text_interpolated(name, e->prevPos[0] - measure, e->prevPos[1], e->prevScale, out[0] - measure, out[1], scale, color[0], color[1], color[2], alpha, 0.25);

            if (i != 0 && gNametagsSettings.showHealth) {
                djui_hud_set_color(255, 255, 255, alpha);
                f32 healthScale = 90 * scale;
                f32 prevHealthScale = 90 * e->prevScale;
                hud_render_power_meter_interpolated(m->health,
                    e->prevPos[0] - (prevHealthScale * 0.5f), e->prevPos[1] - 23, prevHealthScale, prevHealthScale,
                    out[0] - (healthScale * 0.5f), out[1] - 23, healthScale, healthScale
                );
            }

            vec3f_copy(e->prevPos, out);
            e->prevScale = scale;
        }
    }
}
