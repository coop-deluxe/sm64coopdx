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
    packet_write(&p, &gCurrSaveFileNum, sizeof(s16));
    packet_write(&p, &gCurrCourseNum,   sizeof(s16));
    packet_write(&p, &gCurrActStarNum,  sizeof(s16));
    packet_write(&p, &gCurrLevelNum,    sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,   sizeof(s16));
    packet_write(&p, &o->oPosX, sizeof(f32) * 3);
    packet_write(&p, &behaviorId, sizeof(u32));
    packet_write(&p, &coinScore,  sizeof(s16));
    packet_write(&p, &starIndex,  sizeof(s16));
    packet_write(&p, &gSaveFileUsingBackupSlot, sizeof(u8));

    network_send(&p);
}

void network_receive_collect_star(struct Packet* p) {
    f32 pos[3] = { 0 };
    u32 behaviorId;
    s16 coinScore, starIndex;
    s16 lastSaveFileNum = gCurrSaveFileNum;
    s16 lastCourseNum   = gCurrCourseNum;
    s16 lastStarActNum  = gCurrActStarNum;
    s16 lastLevelNum    = gCurrLevelNum;
    s16 lastAreaIndex   = gCurrAreaIndex;
    u8  lastBackupSlot  = gSaveFileUsingBackupSlot;

    packet_read(p, &gCurrSaveFileNum, sizeof(s16));
    packet_read(p, &gCurrCourseNum,   sizeof(s16));
    packet_read(p, &gCurrActStarNum,  sizeof(s16));
    packet_read(p, &gCurrLevelNum,    sizeof(s16));
    packet_read(p, &gCurrAreaIndex,   sizeof(s16));
    packet_read(p, &pos, sizeof(f32) * 3);
    packet_read(p, &behaviorId, sizeof(u32));
    packet_read(p, &coinScore,  sizeof(s16));
    packet_read(p, &starIndex,  sizeof(s16));
    packet_read(p, &gSaveFileUsingBackupSlot, sizeof(u8));
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
