#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_table.h"
#include "course_table.h"
#include "game/hardcoded.h"
#include "game/interaction.h"
#include "engine/math_util.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/debuglog.h"

extern s16 gCurrCourseNum, gCurrAreaIndex;

// defined in sparkle_spawn_star.inc.c
void bhv_spawn_star_no_level_exit(struct Object* object, u32 sp20, u8 networkSendEvent);

static f32 dist_to_pos(struct Object* o, f32* pos) {
    f32 x = o->oPosX - pos[0]; x *= x;
    f32 y = o->oPosY - pos[1]; y *= y;
    f32 z = o->oPosZ - pos[2]; z *= z;
    return (f32)sqrt(x + y + z);
}

static struct Object* find_nearest_coin(const BehaviorScript *behavior, f32* pos, s32 coinValue, float minDist) {
    behavior = smlua_override_behavior(behavior);
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct Object *closestObj = NULL;
    struct Object *obj;
    struct ObjectNode *listHead;

    extern struct ObjectNode *gObjectLists;
    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj->oDamageOrCoinValue == coinValue) {
            f32 objDist = dist_to_pos(obj, pos);
            if (objDist < minDist) {
                closestObj = obj;
                minDist = objDist;
            }
        }
        obj = (struct Object *) obj->header.next;
    }

    return closestObj;
}

void network_send_collect_coin(struct Object* o) {
    if (gNetworkPlayerLocal == NULL || !gNetworkPlayerLocal->currAreaSyncValid) { return; }
    u32 behaviorId = get_id_from_behavior(o->behavior);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_COLLECT_COIN, true, PLMT_LEVEL);
    packet_write_uint32(&p, behaviorId);
    packet_write_float32(&p, o->oPosX);
    packet_write_float32(&p, o->oPosY);
    packet_write_float32(&p, o->oPosZ);
    packet_write_int32(&p, o->oDamageOrCoinValue);
    packet_write_int16(&p, gMarioStates[0].numCoins);
    packet_write_int16(&p, gCurrAreaIndex);
    
    network_send(&p);
    
    packet_clear(&p);
}

void network_receive_collect_coin(struct Packet* p) {
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u32) + sizeof(s32) + (sizeof(f32) * 3) + (sizeof(s16) * 2));

    f32 pos[3] = { 0.0f };
    
    u32 behaviorId = packet_read_uint32(p);
    pos[0] = packet_read_float32(p);
    pos[1] = packet_read_float32(p);
    pos[2] = packet_read_float32(p);
    s32 coinValue = packet_read_int32(p);
    s16 numCoins = packet_read_int16(p);
    s16 areaIndex = packet_read_int16(p);
    
    s16 oldNumCoins = gMarioStates[0].numCoins;

    if (areaIndex == gCurrAreaIndex) {
        const void* behavior = get_behavior_from_id(behaviorId);

        // make sure it's valid
        if (behavior == NULL) { goto SANITY_CHECK_COINS; }

        // find the coin
        float minDist = (behavior == smlua_override_behavior(bhvRedCoin)) ? 200 : 1000;
        struct Object* coin = find_nearest_coin(behavior, pos, coinValue, minDist);
        if (coin == NULL) { goto SANITY_CHECK_COINS; }

        // destroy coin
        coin->oInteractStatus = INT_STATUS_INTERACTED;
    }

SANITY_CHECK_COINS:;
    gMarioStates[0].numCoins = max(numCoins, gMarioStates[0].numCoins + coinValue);

    // check for 100-coin star
    if (COURSE_IS_MAIN_COURSE(gCurrCourseNum)
        && oldNumCoins < gLevelValues.coinsRequiredForCoinStar
        && gMarioStates[0].numCoins >= gLevelValues.coinsRequiredForCoinStar
        && gCurrAreaIndex == areaIndex) {
        bhv_spawn_star_no_level_exit(gMarioStates[p->localIndex].marioObj, 6, FALSE);
    }
}
