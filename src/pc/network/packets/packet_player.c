#include <stdio.h>
#include <stddef.h>
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
#include "pc/djui/djui_language.h"
#include "pc/debuglog.h"
#include "src/game/hardcoded.h"

#pragma pack(1)
struct PacketPlayerData {
    // Controls and Input
    u16 input;
    u16 cButtonDown;
    u16 cButtonPressed;
    u16 cButtonReleased;
    f32 cStickX;
    f32 cStickY;
    f32 cStickMag;
    s16 cRawStickX;
    s16 cRawStickY;
    s16 cExtStickX;
    s16 cExtStickY;
    
    // Graph Node
    s16 nodeFlags;

    // Player (Mario)
    u32 flags;
    u32 particleFlags;
    u32 action;
    u32 prevAction;
    u16 actionState;
    u16 actionTimer;
    u32 actionArg;
    s32 dialogId;
    f32 intendedMag;
    s16 intendedYaw;
    s16 invincTimer;
    u8 framesSinceA;
    u8 framesSinceB;
    u8 wallKickTimer;
    u8 doubleJumpTimer;
    u8 squishTimer;
    u8 knockbackTimer;
    u8 specialTripleJump;
    Vec3s faceAngle;
    Vec3s angleVel;
    s16 slideYaw;
    s16 twirlYaw;
    Vec3f pos;
    Vec3f vel;
    f32 forwardVel;
    f32 slideVelX;
    f32 slideVelZ;
    f32 peakHeight;
    s16 health;
    s16 currentRoom;
    Vec3s headRotation;
    
    // Level Sync
    u32 heldSyncID;
    u32 heldBySyncID;
    u32 riddenSyncID;
    u32 interactSyncID;
    u32 usedSyncID;
    u32 platformSyncID;
    u8  levelSyncValid;
    u8  areaSyncValid;
    u8  customFlags;
    
    // Raw Object Fields
    u32 rawData[OBJECT_NUM_FIELDS];
};
#pragma pack()

OPTIMIZE_O3 void write_packet_data(struct Packet* p, struct MarioState* m) {
    if (p == NULL || m == NULL) { return; }
    
    // Controls and Input
    packet_write_uint16(p, m->input);
    packet_write_uint16(p, m->controller->buttonDown);
    packet_write_uint16(p, m->controller->buttonPressed);
    packet_write_uint16(p, m->controller->buttonReleased);
    packet_write_float32(p, m->controller->stickX);
    packet_write_float32(p, m->controller->stickY);
    packet_write_float32(p, m->controller->stickMag);
    packet_write_int16(p, m->controller->rawStickX);
    packet_write_int16(p, m->controller->rawStickY);
    packet_write_int16(p, m->controller->extStickX);
    packet_write_int16(p, m->controller->extStickY);
    
    // Graph Node
    packet_write_int16(p, m->marioObj->header.gfx.node.flags);
    
    // Player (Mario)
    packet_write_uint32(p, m->flags);
    packet_write_uint32(p, m->particleFlags);
    packet_write_uint32(p, m->action);
    packet_write_uint32(p, m->prevAction);
    packet_write_uint16(p, m->actionState);
    packet_write_uint16(p, m->actionTimer);
    packet_write_uint32(p, m->actionArg);
    packet_write_int32(p, get_dialog_id());
    packet_write_float32(p, m->intendedMag);
    packet_write_int16(p, m->intendedYaw);
    packet_write_int16(p, m->invincTimer);
    packet_write_uint8(p, m->framesSinceA);
    packet_write_uint8(p, m->framesSinceB);
    packet_write_uint8(p, m->wallKickTimer);
    packet_write_uint8(p, m->doubleJumpTimer);
    packet_write_uint8(p, m->squishTimer);
    packet_write_uint8(p, m->knockbackTimer);
    packet_write_uint8(p, m->specialTripleJump);
    packet_write_int16(p, m->faceAngle[0]);
    packet_write_int16(p, m->faceAngle[1]);
    packet_write_int16(p, m->faceAngle[2]);
    packet_write_int16(p, m->angleVel[0]);
    packet_write_int16(p, m->angleVel[1]);
    packet_write_int16(p, m->angleVel[2]);
    packet_write_int16(p, m->slideYaw);
    packet_write_int16(p, m->twirlYaw);
    packet_write_float32(p, m->pos[0]);
    packet_write_float32(p, m->pos[1]);
    packet_write_float32(p, m->pos[2]);
    packet_write_float32(p, m->vel[0]);
    packet_write_float32(p, m->vel[1]);
    packet_write_float32(p, m->vel[2]);
    packet_write_float32(p, m->forwardVel);
    packet_write_float32(p, m->slideVelX);
    packet_write_float32(p, m->slideVelZ);
    packet_write_float32(p, m->peakHeight);
    packet_write_int16(p, m->health);
    packet_write_int16(p, m->currentRoom);
    packet_write_int16(p, gPlayerCameraState[m->playerIndex].headRotation[0]);
    packet_write_int16(p, gPlayerCameraState[m->playerIndex].headRotation[1]);
    packet_write_int16(p, gPlayerCameraState[m->playerIndex].headRotation[2]);
    
    // Level Sync
    u32 heldSyncID     = (m->heldObj != NULL)            ? m->heldObj->oSyncID            : 0;
    u32 heldBySyncID   = (m->heldByObj != NULL)          ? m->heldByObj->oSyncID          : 0;
    u32 riddenSyncID   = (m->riddenObj != NULL)          ? m->riddenObj->oSyncID          : 0;
    u32 interactSyncID = (m->interactObj != NULL)        ? m->interactObj->oSyncID        : 0;
    u32 usedSyncID     = (m->usedObj != NULL)            ? m->usedObj->oSyncID            : 0;
    u32 platformSyncID = (m->marioObj->platform != NULL) ? m->marioObj->platform->oSyncID : 0;
    
    packet_write_uint32(p, heldSyncID);
    packet_write_uint32(p, heldBySyncID);
    packet_write_uint32(p, riddenSyncID);
    packet_write_uint32(p, interactSyncID);
    packet_write_uint32(p, usedSyncID);
    packet_write_uint32(p, platformSyncID);
    
    struct NetworkPlayer* np = &gNetworkPlayers[m->playerIndex];
    packet_write_uint8(p, np->currLevelSyncValid);
    packet_write_uint8(p, np->currAreaSyncValid);
    
    packet_write_uint8(p, SET_BIT((m->freeze > 0), 0));
    
    // Raw Object Fields
    packet_write(p, m->marioObj->rawData.asU32, sizeof(u32) * OBJECT_NUM_FIELDS);
}

OPTIMIZE_O3 void read_packet_data(struct Packet* p, struct PacketPlayerData* data) {
    if (p == NULL || data == NULL) { return; }
    
    // Controls and Input
    data->input = packet_read_uint16(p);
    data->cButtonDown = packet_read_uint16(p);
    data->cButtonPressed = packet_read_uint16(p);
    data->cButtonReleased = packet_read_uint16(p);
    data->cStickX = packet_read_float32(p);
    data->cStickY = packet_read_float32(p);
    data->cStickMag = packet_read_float32(p);
    data->cRawStickX = packet_read_int16(p);
    data->cRawStickY = packet_read_int16(p);
    data->cExtStickX = packet_read_int16(p);
    data->cExtStickY = packet_read_int16(p);
    
    // Graph Node
    data->nodeFlags = packet_read_int16(p);
    
    // Player (Mario)
    data->flags = packet_read_uint32(p);
    data->particleFlags = packet_read_uint32(p);
    data->action = packet_read_uint32(p);
    data->prevAction = packet_read_uint32(p);
    data->actionState = packet_read_uint16(p);
    data->actionTimer = packet_read_uint16(p);
    data->actionArg = packet_read_uint32(p);
    data->dialogId = packet_read_int32(p);
    data->intendedMag = packet_read_float32(p);
    data->intendedYaw = packet_read_int16(p);
    data->invincTimer = packet_read_int16(p);
    data->framesSinceA = packet_read_uint8(p);
    data->framesSinceB = packet_read_uint8(p);
    data->wallKickTimer = packet_read_uint8(p);
    data->doubleJumpTimer = packet_read_uint8(p);
    data->squishTimer = packet_read_uint8(p);
    data->knockbackTimer = packet_read_uint8(p);
    data->specialTripleJump = packet_read_uint8(p);
    data->faceAngle[0] = packet_read_int16(p);
    data->faceAngle[1] = packet_read_int16(p);
    data->faceAngle[2] = packet_read_int16(p);
    data->angleVel[0] = packet_read_int16(p);
    data->angleVel[1] = packet_read_int16(p);
    data->angleVel[2] = packet_read_int16(p);
    data->slideYaw = packet_read_int16(p);
    data->twirlYaw = packet_read_int16(p);
    data->pos[0] = packet_read_float32(p);
    data->pos[1] = packet_read_float32(p);
    data->pos[2] = packet_read_float32(p);
    data->vel[0] = packet_read_float32(p);
    data->vel[1] = packet_read_float32(p);
    data->vel[2] = packet_read_float32(p);
    data->forwardVel = packet_read_float32(p);
    data->slideVelX = packet_read_float32(p);
    data->slideVelZ = packet_read_float32(p);
    data->peakHeight = packet_read_float32(p);
    data->health = packet_read_int16(p);
    data->currentRoom = packet_read_int16(p);
    data->headRotation[0] = packet_read_int16(p);
    data->headRotation[1] = packet_read_int16(p);
    data->headRotation[2] = packet_read_int16(p);
    
    // Level Sync
    data->heldSyncID = packet_read_uint32(p);
    data->heldBySyncID = packet_read_uint32(p);
    data->riddenSyncID = packet_read_uint32(p);
    data->interactSyncID = packet_read_uint32(p);
    data->usedSyncID = packet_read_uint32(p);
    data->platformSyncID = packet_read_uint32(p);
    data->levelSyncValid = packet_read_uint8(p);
    data->areaSyncValid = packet_read_uint8(p);
    data->customFlags = packet_read_uint8(p);
    
    // Raw Object Fields
    packet_read(p, data->rawData, sizeof(u32) * OBJECT_NUM_FIELDS);
}

OPTIMIZE_O3 void apply_packet_data(struct PacketPlayerData* data, struct MarioState* m,
                              u8* customFlags, u32* heldSyncID, u32* heldBySyncID,
                              u32* riddenSyncID, u32* interactSyncID, u32* usedSyncID,
                              u32* platformSyncID) {
    memcpy(m->marioObj->rawData.asU32, data->rawData, sizeof(u32) * OBJECT_NUM_FIELDS);
    m->marioObj->header.gfx.node.flags = data->nodeFlags;

    m->controller->rawStickX      = data->cRawStickX;
    m->controller->rawStickY      = data->cRawStickY;
    m->controller->stickX         = data->cStickX;
    m->controller->stickY         = data->cStickY;
    m->controller->stickMag       = data->cStickMag;
    m->controller->buttonDown     = data->cButtonDown;
    m->controller->buttonPressed  = data->cButtonPressed;
    m->controller->buttonReleased = data->cButtonReleased;
    m->controller->extStickX      = data->cExtStickX;
    m->controller->extStickY      = data->cExtStickY;

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
    m->specialTripleJump = data->specialTripleJump;
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
    memcpy(gPlayerCameraState[m->playerIndex].headRotation, data->headRotation, sizeof(s16) * 3);

    *customFlags    = data->customFlags;
    *heldSyncID     = data->heldSyncID;
    *heldBySyncID   = data->heldBySyncID;
    *riddenSyncID   = data->riddenSyncID;
    *interactSyncID = data->interactSyncID;
    *usedSyncID     = data->usedSyncID;
    *platformSyncID = data->platformSyncID;

    if (gNetworkType != NT_SERVER) {
        struct NetworkPlayer* np = &gNetworkPlayers[m->playerIndex];
        np->currAreaSyncValid  = data->areaSyncValid;
        np->currLevelSyncValid = data->levelSyncValid;
    }

    m->knockbackTimer = data->knockbackTimer;

    m->dialogId = data->dialogId;
}

void network_send_player(u8 localIndex) {
    if (gMarioStates[localIndex].marioObj == NULL) { return; }
    if (gDjuiInMainMenu) { return; }
    if (gNetworkPlayerLocal == NULL || !gNetworkPlayerLocal->currAreaSyncValid) { return; }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_PLAYER, false, PLMT_AREA);
    packet_write(&p, &gNetworkPlayers[localIndex].globalIndex, sizeof(u8));
    write_packet_data(&p, &gMarioStates[localIndex]);
    network_send(&p);
    packet_clear(&p);
}

void network_receive_player(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8) + sizeof(struct PacketPlayerData));
    
    u8 globalIndex = packet_read_uint8(p);
    
    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) { return; }

    // Prevent receiving a packet about our player
    if (gNetworkPlayerLocal && globalIndex == gNetworkPlayerLocal->globalIndex) { return; }

    struct MarioState* m = &gMarioStates[np->localIndex];
    if (m == NULL || m->marioObj == NULL) { return; }
    
    // Load Mario information from the packet
    struct PacketPlayerData data = { 0 };
    read_packet_data(p, &data);

    if (gNetworkType == NT_SERVER && data.action == ACT_DEBUG_FREE_MOVE) {
#ifdef DEVELOPMENT
        if (m->action != ACT_DEBUG_FREE_MOVE) {
            construct_player_popup(np, DLANG(NOTIF, DEBUG_FLY), NULL);
        }
#else
        network_send_kick(np->localIndex, EKT_KICKED);
        network_player_disconnected(np->localIndex);
        return;
#endif
    }

    // Prevent receiving player from other area
    bool levelAreaMismatch = ((gNetworkPlayerLocal == NULL)
        || np->currCourseNum != gNetworkPlayerLocal->currCourseNum
        || np->currActNum    != gNetworkPlayerLocal->currActNum
        || np->currLevelNum  != gNetworkPlayerLocal->currLevelNum
        || np->currAreaIndex != gNetworkPlayerLocal->currAreaIndex);
    if (levelAreaMismatch) { np->currPositionValid = false; return; }

    // Save any needed previous state information.
    u32 oldAction = m->action;
    u16 oldActionState = m->actionState;
    u32 oldActionArg = m->actionArg;
    u32 oldBehParams = m->marioObj->oBehParams;
    u32 oldParticleFlags = m->marioObj->oActiveParticleFlags;
    
    u16 playerIndex  = np->localIndex;

    // Check to see if we should just drop this packet
    if (oldAction == ACT_JUMBO_STAR_CUTSCENE && data.action == ACT_JUMBO_STAR_CUTSCENE) {
        return;
    }

    // Apply data from packet to mario state
    u32 heldSyncID     = 0;
    u32 heldBySyncID   = 0;
    u32 riddenSyncID   = 0;
    u32 interactSyncID = 0;
    u32 usedSyncID     = 0;
    u32 platformSyncID = 0;
    u8  customFlags    = 0;
    apply_packet_data(&data, m, &customFlags,
                      &heldSyncID, &heldBySyncID,
                      &riddenSyncID, &interactSyncID,
                      &usedSyncID, &platformSyncID);

    // Read custom flags
    m->freeze = GET_BIT(customFlags, 0);

    // Reset player index
    m->playerIndex = playerIndex;
    m->marioObj->oBehParams = oldBehParams;

    // Reset Mario sound play flag so that their jump sounds work
    if (m->action != oldAction) {
        m->flags &= ~(MARIO_ACTION_SOUND_PLAYED | MARIO_MARIO_SOUND_PLAYED);
    }

    // Find and set their held object
    struct SyncObject* heldSo = sync_object_get(heldSyncID);
    m->heldObj = heldSo ? heldSo->o : NULL;
    if (m->heldObj != NULL) {
        if (gMarioStates[0].heldObj == m->heldObj && np->globalIndex < gNetworkPlayerLocal->globalIndex) {
            // Drop the object if a higher priority player is holding our object
            mario_drop_held_object(&gMarioStates[0]);
            force_idle_state(&gMarioStates[0]);
        }
        m->heldObj->oHeldState = HELD_HELD;
        m->heldObj->heldByPlayerIndex = np->localIndex;
    }

    // Find and set their held-by object
    struct SyncObject* heldBySo = sync_object_get(heldBySyncID);
    if (heldBySo && heldBySo->o) {
        // TODO: Do we have to move graphics nodes around to make this visible?
        m->heldByObj = heldBySo->o;
    } else {
        m->heldByObj = NULL;
    }

    // Find and set their ridden object
    struct SyncObject* riddenSo = sync_object_get(riddenSyncID);
    if (riddenSo && riddenSo->o) {
        riddenSo->o->heldByPlayerIndex = np->localIndex;
        m->riddenObj = riddenSo->o;
    } else {
        m->riddenObj = NULL;
    }

    // Find and set their interact object
    struct SyncObject* interactSo = sync_object_get(interactSyncID);
    if (interactSo && interactSo->o) {
        m->interactObj = interactSo->o;
    }

    // Find and set their used object
    struct SyncObject* usedSo = sync_object_get(usedSyncID);
    if (usedSo && usedSo->o != NULL) {
        m->usedObj = usedSo->o;
    }

    // Place on top of platform
    struct SyncObject* platformSo = sync_object_get(platformSyncID);
    if (platformSo && platformSo->o) {

        // Search up to 500 units for the platform
        f32 maxDifference = 500;

        // Look for a platform above and below, and a ceiling above the player
        gCheckingSurfaceCollisionsForObject = platformSo->o;
        f32 currFloorHeight = find_floor_height(m->pos[0], m->pos[1], m->pos[2]);
        f32 floorHeight = find_floor_height(m->pos[0], m->pos[1] + maxDifference, m->pos[2]);
        f32 ceilHeight = find_ceil_height(m->pos[0], m->pos[1], m->pos[2]);
        gCheckingSurfaceCollisionsForObject = NULL;

        // Always prefer the closest floor
        // Use the floor below if there's a ceiling between the player and the floor above
        // only accept floors 500 units away
        f32 diffAbove = ABS(m->pos[1] - floorHeight);
        f32 diffBelow = ABS(m->pos[1] - currFloorHeight);
        if (floorHeight != gLevelValues.floorLowerLimit &&
            (currFloorHeight == gLevelValues.floorLowerLimit || diffBelow > diffAbove) &&
            (ceilHeight == gLevelValues.cellHeightLimit || floorHeight < ceilHeight) &&
            diffAbove <= maxDifference) {
            // Place on top of platform
            m->pos[1] = floorHeight;
        }
    }

    // Jump kicking: Restore action state, otherwise it won't play
    if (m->action == ACT_JUMP_KICK) {
        m->actionState = oldActionState;
    }

    // Punching:
    if ((m->action == ACT_PUNCHING || m->action == ACT_MOVE_PUNCHING)) {
        // Play first punching sound, otherwise it will be missed
        if (m->action != oldAction) {
            play_character_sound(m, CHAR_SOUND_PUNCH_YAH);
        }
        // Make the first punch large, otherwise it will be missed
        if (m->actionArg == 2 && oldActionArg == 1) {
            m->marioBodyState->punchState = (0 << 6) | 4;
        }
    }

    // Inform of player death
    if (oldAction != ACT_BUBBLED && data.action == ACT_BUBBLED && !data.actionArg) {
        construct_player_popup(np, DLANG(NOTIF, DIED), NULL);
    }

    // Action changed, reset timer
    if (m->action != oldAction) {
        m->actionTimer = 0;
    }

    // Mark this player as visible
    if (gNetworkAreaLoaded && !m->wasNetworkVisible) {
        m->wasNetworkVisible = true;
        vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
        vec3s_copy(m->marioObj->header.gfx.angle, m->faceAngle);
    }

    // Player's position is valid since it's updated and in the same area as the local player
    np->currPositionValid = true;

    if (np->currLevelNum == LEVEL_BOWSER_3 && m->action == ACT_JUMBO_STAR_CUTSCENE && gMarioStates[0].action != ACT_JUMBO_STAR_CUTSCENE) {
        set_mario_action(&gMarioStates[0], ACT_JUMBO_STAR_CUTSCENE, 0);
    }
    m->marioObj->oActiveParticleFlags = oldParticleFlags;
}

void network_update_player(void) {
    if (!network_player_any_connected()) { return; }
    struct MarioState* m = &gMarioStates[0];

    u8 localIsHeadless = (&gNetworkPlayers[0] == gNetworkPlayerServer && gServerSettings.headlessServer);
    if (localIsHeadless) { return; }

    // figure out if we should send it or not
    static u8 sTicksSinceSend = 0;
    static u32 sLastPlayerAction = 0;
    static u32 sLastPlayerParticles = 0;
    static f32 sLastStickX = 0;
    static f32 sLastStickY = 0;
    static u32 sLastButtonDown = 0;
    static u32 sLastButtonPressed = 0;
    static u32 sLastButtonReleased = 0;

    f32 stickDist = sqrtf(powf(sLastStickX - m->controller->stickX, 2) + powf(sLastStickY - m->controller->stickY, 2));
    bool shouldSend = (sTicksSinceSend > 2)
        || (sLastPlayerAction    != m->action)
        || (sLastButtonDown      != m->controller->buttonDown)
        || (sLastButtonPressed   != m->controller->buttonPressed)
        || (sLastButtonReleased  != m->controller->buttonReleased)
        || (sLastPlayerParticles != m->particleFlags)
        || (stickDist          > 5.0f);

    if (!shouldSend) { sTicksSinceSend++; return; }
    network_send_player(0);
    sTicksSinceSend = 0;

    sLastPlayerAction    = m->action;
    sLastStickX          = m->controller->stickX;
    sLastStickY          = m->controller->stickY;
    sLastButtonDown      = m->controller->buttonDown;
    sLastButtonPressed   = m->controller->buttonPressed;
    sLastButtonReleased  = m->controller->buttonReleased;
    sLastPlayerParticles = m->particleFlags;
}
