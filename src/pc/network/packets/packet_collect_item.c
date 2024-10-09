#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_table.h"
#include "course_table.h"
#include "game/interaction.h"
#include "engine/math_util.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "pc/lua/smlua_hooks.h"

static f32 dist_to_pos(struct Object* o, f32* pos) {
    f32 x = o->oPosX - pos[0]; x *= x;
    f32 y = o->oPosY - pos[1]; y *= y;
    f32 z = o->oPosZ - pos[2]; z *= z;
    return (f32)sqrt(x + y + z);
}

static struct Object* find_nearest_item(const BehaviorScript *behavior, f32* pos, float minDist) {
    behavior = smlua_override_behavior(behavior);
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct Object *closestObj = NULL;
    struct Object *obj;
    struct ObjectNode *listHead;

    extern struct ObjectNode *gObjectLists;
    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && !(obj->oInteractStatus & INT_STATUS_INTERACTED)) {
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

void network_send_collect_item(struct Object* o) {
    if (gNetworkPlayerLocal == NULL || !gNetworkPlayerLocal->currAreaSyncValid) { return; }
    u32 behaviorId = get_id_from_behavior(o->behavior);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_COLLECT_ITEM, true, PLMT_AREA);
    packet_write(&p, &behaviorId, sizeof(u32));
    packet_write(&p, &o->oPosX, sizeof(f32) * 3);

    network_send(&p);
}

void network_receive_collect_item(struct Packet* p) {
    u32 behaviorId;
    f32 pos[3] = { 0 };

    packet_read(p, &behaviorId, sizeof(u32));
    packet_read(p, &pos, sizeof(f32) * 3);

    const void* behavior = get_behavior_from_id(behaviorId);

    // make sure it's valid
    if (behavior == NULL) { return; }

    // find the item
    struct Object* item = find_nearest_item(behavior, pos, 1000);
    if (item == NULL) { return; }

    // destroy item
    item->oInteractStatus = INT_STATUS_INTERACTED;
}
