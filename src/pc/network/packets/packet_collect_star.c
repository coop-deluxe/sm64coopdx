#include <stdio.h>
#include "../network.h"
#include "behavior_table.h"
#include "course_table.h"
#include "object_fields.h"
#include "object_constants.h"
#include "game/interaction.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/save_file.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/debuglog.h"

extern s16 gCurrSaveFileNum;
extern s16 gCurrCourseNum;
extern u8 gSaveFileUsingBackupSlot;

static f32 dist_to_pos(struct Object* o, f32* pos) {
    f32 x = o->oPosX - pos[0]; x *= x;
    f32 y = o->oPosY - pos[1]; y *= y;
    f32 z = o->oPosZ - pos[2]; z *= z;
    return (f32)sqrt(x + y + z);
}

static struct Object* find_nearest_star(const BehaviorScript* behavior, f32* pos, f32 minDist) {
    behavior = smlua_override_behavior(behavior);
    uintptr_t* behaviorAddr = segmented_to_virtual(behavior);
    struct Object* closestObj = NULL;
    struct Object* obj;
    struct ObjectNode* listHead;

    extern struct ObjectNode* gObjectLists;
    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object*) listHead->next;

    while (obj != (struct Object*) listHead) {
        if (obj->behavior == behaviorAddr && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
            f32 objDist = dist_to_pos(obj, pos);
            if (objDist < minDist) {
                closestObj = obj;
                minDist = objDist;
            }
        }
        obj = (struct Object*) obj->header.next;
    }

    return closestObj;
}

void network_send_collect_star(struct Object* o, s16 coinScore, s16 starIndex) {
    u32 behaviorId = get_id_from_behavior(o->behavior);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_COLLECT_STAR, true, PLMT_NONE);
    packet_write_int16(&p, gCurrSaveFileNum);
    packet_write_int16(&p, gCurrCourseNum);
    packet_write_int16(&p, gCurrActStarNum);
    packet_write_int16(&p, gCurrLevelNum);
    packet_write_int16(&p, gCurrAreaIndex);
    packet_write_int16(&p, coinScore);
    packet_write_int16(&p, starIndex);
    packet_write_float32(&p, o->oPosX);
    packet_write_float32(&p, o->oPosY);
    packet_write_float32(&p, o->oPosZ);
    packet_write_uint32(&p, behaviorId);
    packet_write_uint8(&p, gSaveFileUsingBackupSlot);

    network_send(&p);
    
    packet_clear(&p);
}

void network_receive_collect_star(struct Packet* p) {
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= (sizeof(s16) * 7) + (sizeof(f32) * 3) + sizeof(u32) + sizeof(u8));
    
    f32 pos[3] = { 0 };
    
    s16 lastSaveFileNum = gCurrSaveFileNum;
    s16 lastCourseNum   = gCurrCourseNum;
    s16 lastStarActNum  = gCurrActStarNum;
    s16 lastLevelNum    = gCurrLevelNum;
    s16 lastAreaIndex   = gCurrAreaIndex;
    u8  lastBackupSlot  = gSaveFileUsingBackupSlot;
    
    gCurrSaveFileNum = packet_read_int16(p);
    gCurrCourseNum = packet_read_int16(p);
    gCurrActStarNum = packet_read_int16(p);
    gCurrLevelNum = packet_read_int16(p);
    gCurrAreaIndex = packet_read_int16(p);
    s16 coinScore = packet_read_int16(p);
    s16 starIndex = packet_read_int16(p);
    pos[0] = packet_read_float32(p);
    pos[1] = packet_read_float32(p);
    pos[2] = packet_read_float32(p);
    u32 behaviorId = packet_read_uint32(p);
    gSaveFileUsingBackupSlot = packet_read_uint8(p);

    if (gSaveFileUsingBackupSlot != 0) { gSaveFileUsingBackupSlot = 1; }

    const void* behavior = get_behavior_from_id(behaviorId);

    save_file_collect_star_or_key(coinScore, starIndex, 1);

    struct NetworkPlayer* np = gNetworkPlayerLocal;
    bool levelAreaMismatch = ((np == NULL)
        || np->currCourseNum != gCurrCourseNum
        || np->currActNum    != gCurrActStarNum
        || np->currLevelNum  != gCurrLevelNum
        || np->currAreaIndex != gCurrAreaIndex);

    gCurrSaveFileNum         = lastSaveFileNum;
    gCurrCourseNum           = lastCourseNum;
    gCurrActStarNum          = lastStarActNum;
    gCurrLevelNum            = lastLevelNum;
    gCurrAreaIndex           = lastAreaIndex;
    gSaveFileUsingBackupSlot = lastBackupSlot;

    s32 numStars = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        gMarioStates[i].numStars = numStars;
    }

    if (!levelAreaMismatch) {
        struct Object* star = find_nearest_star(behavior, pos, 500);
        if (star != NULL) {
            star->oInteractStatus = INT_STATUS_INTERACTED;
        }
    }
}
