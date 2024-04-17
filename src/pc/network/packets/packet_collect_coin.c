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
    packet_write(&p, &behaviorId, sizeof(u32));
    packet_write(&p, &o->oPosX, sizeof(f32) * 3);
    packet_write(&p, &gMarioStates[0].numCoins, sizeof(s16));
    packet_write(&p, &o->oDamageOrCoinValue, sizeof(s32));
    packet_write(&p, &gCurrAreaIndex, sizeof(s16));

    network_send(&p);
}

void network_receive_collect_coin(struct Packet* p) {
    s16 oldNumCoins = gMarioStates[0].numCoins;

    u32 behaviorId;
    f32 pos[3] = { 0 };
    s16 numCoins = 0;
    s32 coinValue = 0;
    s16 areaIndex = 0;

    packet_read(p, &behaviorId, sizeof(u32));
    packet_read(p, &pos, sizeof(f32) * 3);
    packet_read(p, &numCoins, sizeof(s16));
    packet_read(p, &coinValue, sizeof(s32));
    packet_read(p, &areaIndex, sizeof(s16));

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
