#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "sm64.h"
#include "game/interaction.h"
#include "game/mario.h"
#include "game/area.h"
#include "audio/external.h"
#include "engine/surface_collision.h"
#include "engine/math_util.h"
#include "game/object_list_processor.h"
#include "game/mario_misc.h"
#include "pc/configfile.h"
#include "pc/djui/djui.h"

#pragma pack(1)
struct PacketPlayerData {
    u32 rawData[80];

    s16 cRawStickX;
    s16 cRawStickY;
    f32 cStickX;
    f32 cStickY;
    f32 cStickMag;
    u16 cButtonDown;
    u16 cButtonPressed;
    s16 cExtStickX;
    s16 cExtStickY;

    s16 nodeFlags;

    u16 input;
    u32 flags;
    u32 particleFlags;
    u32 action;
    u32 prevAction;
    u16 actionState;
    u16 actionTimer;
    u32 actionArg;
    f32 intendedMag;
    s16 intendedYaw;
    s16 invincTimer;
    u8  framesSinceA;
    u8  framesSinceB;
    u8  wallKickTimer;
    u8  doubleJumpTimer;
    Vec3s faceAngle;
    Vec3s angleVel;
    s16 slideYaw;
    s16 twirlYaw;
    Vec3f pos;
    Vec3f vel;
    f32 forwardVel;
    f32 slideVelX;
    f32 slideVelZ;
    s16 health;
    u8  squishTimer;
    f32 peakHeight;
    s16 currentRoom;

    u8  customFlags;
    u8 heldSyncID;
    u8 heldBySyncID;
    u8 riddenSyncID;
    u8 interactSyncID;
    u8 usedSyncID;
    u8 platformSyncID;
};
#pragma pack()

static void read_packet_data(struct PacketPlayerData* data, struct MarioState* m) {
    u8 heldSyncID     = (m->heldObj != NULL)            ? m->heldObj->oSyncID            : 0;
    u8 heldBySyncID   = (m->heldByObj != NULL)          ? m->heldByObj->oSyncID          : 0;
    u8 riddenSyncID   = (m->riddenObj != NULL)          ? m->riddenObj->oSyncID          : 0;
    u8 interactSyncID = (m->interactObj != NULL)        ? m->interactObj->oSyncID        : 0;
    u8 usedSyncID     = (m->usedObj != NULL)            ? m->usedObj->oSyncID            : 0;
    u8 platformSyncID = (m->marioObj->platform != NULL) ? m->marioObj->platform->oSyncID : 0;

    u8 customFlags     = SET_BIT((m->freeze > 0), 0);

    memcpy(data->rawData, m->marioObj->rawData.asU32, sizeof(u32) * 80);
    data->nodeFlags    = m->marioObj->header.gfx.node.flags;

    data->cRawStickX     = m->controller->rawStickX;
    data->cRawStickY     = m->controller->rawStickY;
    data->cStickX        = m->controller->stickX;
    data->cStickY        = m->controller->stickY;
    data->cStickMag      = m->controller->stickMag;
    data->cButtonDown    = m->controller->buttonDown;
    data->cButtonPressed = m->controller->buttonPressed;
    data->cExtStickX     = m->controller->extStickX;
    data->cExtStickY     = m->controller->extStickY;

    data->input           = m->input;
    data->flags           = m->flags;
    data->particleFlags   = m->particleFlags;
    data->action          = m->action;
    data->prevAction      = m->prevAction;
    data->actionState     = m->actionState;
    data->actionTimer     = m->actionTimer;
    data->actionArg       = m->actionArg;
    data->intendedMag     = m->intendedMag;
    data->intendedYaw     = m->intendedYaw;
    data->invincTimer     = m->invincTimer;
    data->framesSinceA    = m->framesSinceA;
    data->framesSinceB    = m->framesSinceB;
    data->wallKickTimer   = m->wallKickTimer;
    data->doubleJumpTimer = m->doubleJumpTimer;
    memcpy(data->faceAngle, m->faceAngle, sizeof(s16) * 3);
    memcpy(data->angleVel,  m->angleVel,  sizeof(s16) * 3);
    data->slideYaw        = m->slideYaw;
    data->twirlYaw        = m->twirlYaw;
    memcpy(data->pos, m->pos, sizeof(f32) * 3);
    memcpy(data->vel, m->vel, sizeof(f32) * 3);
    data->forwardVel      = m->forwardVel;
    data->slideVelX       = m->slideVelX;
    data->slideVelZ       = m->slideVelZ;
    data->health          = m->health;
    data->squishTimer     = m->squishTimer;
    data->peakHeight      = m->peakHeight;
    data->currentRoom     = m->currentRoom;

    data->customFlags    = customFlags;
    data->heldSyncID     = heldSyncID;
    data->heldBySyncID   = heldBySyncID;
    data->riddenSyncID   = riddenSyncID;
    data->interactSyncID = interactSyncID;
    data->usedSyncID     = usedSyncID;
    data->platformSyncID = platformSyncID;
}

static void write_packet_data(struct PacketPlayerData* data, struct MarioState* m,
                              u8* customFlags, u8* heldSyncID, u8* heldBySyncID,
                              u8* riddenSyncID, u8* interactSyncID, u8* usedSyncID,
                              u8* platformSyncID) {
    memcpy(m->marioObj->rawData.asU32, data->rawData, sizeof(u32) * 80);
    m->marioObj->header.gfx.node.flags = data->nodeFlags;

    m->controller->rawStickX     = data->cRawStickX;
    m->controller->rawStickY     = data->cRawStickY;
    m->controller->stickX        = data->cStickX;
    m->controller->stickY        = data->cStickY;
    m->controller->stickMag      = data->cStickMag;
    m->controller->buttonDown    = data->cButtonDown;
    m->controller->buttonPressed = data->cButtonPressed;
    m->controller->extStickX     = data->cExtStickX;
    m->controller->extStickY     = data->cExtStickY;

    m->input           = data->input;
    m->flags           = data->flags;
    m->particleFlags   = data->particleFlags;
    m->action          = data->action;
    m->prevAction      = data->prevAction;
    m->actionState     = data->actionState;
    m->actionTimer     = data->actionTimer;
    m->actionArg       = data->actionArg;
    m->intendedMag     = data->intendedMag;
    m->intendedYaw     = data->intendedYaw;
    m->invincTimer     = data->invincTimer;
    m->framesSinceA    = data->framesSinceA;
    m->framesSinceB    = data->framesSinceB;
    m->wallKickTimer   = data->wallKickTimer;
    m->doubleJumpTimer = data->doubleJumpTimer;
    memcpy(m->faceAngle, data->faceAngle, sizeof(s16) * 3);
    memcpy(m->angleVel,  data->angleVel,  sizeof(s16) * 3);
    m->slideYaw        = data->slideYaw;
    m->twirlYaw        = data->twirlYaw;
    memcpy(m->pos, data->pos, sizeof(f32) * 3);
    memcpy(m->vel, data->vel, sizeof(f32) * 3);
    m->forwardVel      = data->forwardVel;
    m->slideVelX       = data->slideVelX;
    m->slideVelZ       = data->slideVelZ;
    m->health          = data->health;
    m->squishTimer     = data->squishTimer;
    m->peakHeight      = data->peakHeight;
    m->currentRoom     = data->currentRoom;

    *customFlags    = data->customFlags;
    *heldSyncID     = data->heldSyncID;
    *heldBySyncID   = data->heldBySyncID;
    *riddenSyncID   = data->riddenSyncID;
    *interactSyncID = data->interactSyncID;
    *usedSyncID     = data->usedSyncID;
    *platformSyncID = data->platformSyncID;
}

void network_send_player(u8 localIndex) {
    if (gMarioStates[localIndex].marioObj == NULL) { return; }
    if (gDjuiInMainMenu) { return; }
    if (gNetworkPlayerLocal == NULL || !gNetworkPlayerLocal->currAreaSyncValid) { return; }

    struct PacketPlayerData data = { 0 };
    read_packet_data(&data, &gMarioStates[localIndex]);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_PLAYER, false, PLMT_AREA);
    packet_write(&p, &gNetworkPlayers[localIndex].globalIndex, sizeof(u8));
    packet_write(&p, &data, sizeof(struct PacketPlayerData));
    network_send(&p);
}

void network_receive_player(struct Packet* p) {
    u8 globalIndex = 0;
    packet_read(p, &globalIndex, sizeof(u8));
    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) { return; }

    // prevent receiving a packet about our player
    if (gNetworkPlayerLocal && globalIndex == gNetworkPlayerLocal->globalIndex) { return; }

    struct MarioState* m = &gMarioStates[np->localIndex];
    if (m == NULL || m->marioObj == NULL) { return; }

    // prevent receiving player from other area
    bool levelAreaMismatch = ((gNetworkPlayerLocal == NULL)
        || np->currCourseNum != gNetworkPlayerLocal->currCourseNum
        || np->currActNum    != gNetworkPlayerLocal->currActNum
        || np->currLevelNum  != gNetworkPlayerLocal->currLevelNum
        || np->currAreaIndex != gNetworkPlayerLocal->currAreaIndex);
    if (levelAreaMismatch) { return; }

    // save previous state
    struct PacketPlayerData oldData = { 0 };
    read_packet_data(&oldData, m);
    u16 playerIndex  = np->localIndex;
    u32 oldBehParams = m->marioObj->oBehParams;

    // load mario information from packet
    struct PacketPlayerData data = { 0 };
    packet_read(p, &data, sizeof(struct PacketPlayerData));

    // check to see if we should just drop this packet
    if (oldData.action == ACT_JUMBO_STAR_CUTSCENE && data.action == ACT_JUMBO_STAR_CUTSCENE) {
        return;
    }

    // apply data from packet to mario state
    u8 heldSyncID     = 0;
    u8 heldBySyncID   = 0;
    u8 riddenSyncID   = 0;
    u8 interactSyncID = 0;
    u8 usedSyncID     = 0;
    u8 platformSyncID = 0;
    u8 customFlags    = 0;
    write_packet_data(&data, m, &customFlags,
                      &heldSyncID, &heldBySyncID,
                      &riddenSyncID, &interactSyncID,
                      &usedSyncID, &platformSyncID);

    // read custom flags
    m->freeze = GET_BIT(customFlags, 0);

    // reset player index
    m->playerIndex = playerIndex;
    m->marioObj->oBehParams = oldBehParams;

    // reset mario sound play flag so that their jump sounds work
    if (m->action != oldData.action) {
        m->flags &= ~(MARIO_ACTION_SOUND_PLAYED | MARIO_MARIO_SOUND_PLAYED);
    }

    // find and set their held object
    m->heldObj = (heldSyncID != 0) ? gSyncObjects[heldSyncID].o : NULL;
    if (m->heldObj != NULL) {
        if (gMarioStates[0].heldObj == m->heldObj && np->globalIndex < gNetworkPlayerLocal->globalIndex) {
            // drop the object if a higher priority player is holding our object
            mario_drop_held_object(&gMarioStates[0]);
            force_idle_state(&gMarioStates[0]);
        }
        m->heldObj->oHeldState = HELD_HELD;
        m->heldObj->heldByPlayerIndex = np->localIndex;
    }

    // find and set their held-by object
    if (heldBySyncID != 0 && gSyncObjects[heldBySyncID].o != NULL) {
        // TODO: do we have to move graphics nodes around to make this visible?
        m->heldByObj = gSyncObjects[heldBySyncID].o;
    } else {
        m->heldByObj = NULL;
    }

    // find and set their ridden object
    if (riddenSyncID != 0 && gSyncObjects[riddenSyncID].o != NULL) {
        gSyncObjects[riddenSyncID].o->heldByPlayerIndex = np->localIndex;
        m->riddenObj = gSyncObjects[riddenSyncID].o;
    } else {
        m->riddenObj = NULL;
    }

    // find and set their interact object
    if (interactSyncID != 0 && gSyncObjects[interactSyncID].o != NULL) {
        m->interactObj = gSyncObjects[interactSyncID].o;
    }

    // find and set their used object
    if (usedSyncID != 0 && gSyncObjects[usedSyncID].o != NULL) {
        m->usedObj = gSyncObjects[usedSyncID].o;
    }

    // place on top of platform
    if (platformSyncID != 0 && gSyncObjects[platformSyncID].o != NULL) {
        struct Surface* floor = NULL;
        // search up to 500 units for the platform
        f32 maxDifference = 500;
        m->pos[1] += maxDifference;

        // find the platform
        gCheckingSurfaceCollisionsForObject = gSyncObjects[platformSyncID].o;
        f32 height = find_floor(m->pos[0], m->pos[1], m->pos[2], &floor);
        gCheckingSurfaceCollisionsForObject = NULL;

        f32 difference = ABS((m->pos[1] - maxDifference) - height);
        if (floor != NULL && difference <= maxDifference) {
            // place on top of platform
            m->pos[1] = height;
        } else {
            // search failed, reset position
            m->pos[1] -= maxDifference;
        }
    }

    // jump kicking: restore action state, otherwise it won't play
    if (m->action == ACT_JUMP_KICK) {
        m->actionState = oldData.actionState;
    }

    // punching:
    if ((m->action == ACT_PUNCHING || m->action == ACT_MOVE_PUNCHING)) {
        // play first punching sound, otherwise it will be missed
        if (m->action != oldData.action) {
            play_character_sound(m, CHAR_SOUND_PUNCH_YAH);
        }
        // make the first punch large, otherwise it will be missed
        if (m->actionArg == 2 && oldData.actionArg == 1) {
            m->marioBodyState->punchState = (0 << 6) | 4;
        }
    }

    // inform of player death
    if (oldData.action != ACT_BUBBLED && data.action == ACT_BUBBLED) {
        // display popup
        char* playerColorString = network_get_player_text_color_string(np->localIndex);
        char popupMsg[128] = { 0 };
        snprintf(popupMsg, 128, "%s%s\\#dcdcdc\\ died", playerColorString, np->name);
        djui_popup_create(popupMsg, 1);
    }

    // action changed, reset timer
    if (m->action != oldData.action) {
        m->actionTimer = 0;
    }

    // mark this player as visible
    if (gNetworkAreaLoaded && !m->wasNetworkVisible) {
        m->wasNetworkVisible = true;
        vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
        vec3s_copy(m->marioObj->header.gfx.angle, m->faceAngle);
    }
}

void network_update_player(void) {
    if (!network_player_any_connected()) { return; }

    u8 localIsHeadless = (&gNetworkPlayers[0] == gNetworkPlayerServer && gServerSettings.headlessServer);
    if (!localIsHeadless) {
        network_send_player(0);
    }
}
