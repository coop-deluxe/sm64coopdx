#include <stdio.h>
#include "reservation_area.h"
#include "network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_table.h"
#include "course_table.h"
#include "src/game/interaction.h"
#include "src/engine/math_util.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

#define RESERVED_IDS_PER_AREA 127
#define RESERVED_IDS_UNRESERVED ((u32)-1)
#define RESERVED_IDS_USED ((u32)-2)

struct ReservationArea {
    s16 courseNum;
    s16 actNum;
    s16 levelNum;
    s16 areaIndex;
    u16 playersActive;
    u32 reservedIds[RESERVED_IDS_PER_AREA];
    struct ReservationArea* next;
};

struct ReservationArea* sReservationAreas = NULL;
struct ReservationArea* sReservationAreaPerPlayer[MAX_PLAYERS] = { NULL };

struct LocalReservationArea {
    s16 courseNum;
    s16 actNum;
    s16 levelNum;
    s16 areaIndex;
    u32 reservedIds[RESERVED_IDS_PER_PLAYER_COUNT];
};
struct LocalReservationArea sLocalReservationArea = { 0 };

void reservation_area_debug(void) {
    printf("\n============ %02d ============\n", gNetworkPlayerLocal->globalIndex);

    printf("reservation area per player:\n");
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct ReservationArea* ra = sReservationAreaPerPlayer[i];
        if (ra != NULL) {
            printf("  %d : (%d, %d, %d, %d)\n", i, ra->courseNum, ra->actNum, ra->levelNum, ra->areaIndex);
        }
    }
    printf("\n");

    printf("reservation areas:\n");
    struct ReservationArea* ra = sReservationAreas;
    while (ra != NULL) {
        printf("  (%d, %d, %d, %d) : %d\n", ra->courseNum, ra->actNum, ra->levelNum, ra->areaIndex, ra->playersActive);

        printf("    ");
        u32 idsUntilBreak = 10;
        for (int i = 0; i < RESERVED_IDS_PER_AREA; i++) {
            switch (ra->reservedIds[i])
            {
                case RESERVED_IDS_UNRESERVED: printf("UNR "); break;
                case RESERVED_IDS_USED:       printf("USD "); break;
                default:                      printf("%03d ", ra->reservedIds[i]); break;
            }
            if (--idsUntilBreak == 0) {
                printf("\n    ");
                idsUntilBreak = 10;
            }
        }
        printf("\n\n");
        ra = ra->next;
    }

    printf("local reservation area:\n");
    struct LocalReservationArea* la = &sLocalReservationArea;
    printf("  (%d, %d, %d, %d) : ", la->courseNum, la->actNum, la->levelNum, la->areaIndex);
    for (int i = 0; i < RESERVED_IDS_PER_PLAYER_COUNT; i++) {
        switch (la->reservedIds[i])
        {
            case RESERVED_IDS_UNRESERVED: printf("UNR "); break;
            case RESERVED_IDS_USED:       printf("USD "); break;
            default:                      printf("%03d ", la->reservedIds[i]); break;
        }
    }
    printf("\n\n");
}

static void reservation_area_refresh_ids(struct NetworkPlayer* np) {
    bool informPlayer = false;

    // make sure player has a RA
    struct ReservationArea* ra = sReservationAreaPerPlayer[np->globalIndex];
    if (ra == NULL) { return; }

    // count current reserved ids
    u32 reservedIds[RESERVED_IDS_PER_PLAYER_COUNT] = { RESERVED_IDS_UNRESERVED };
    u32 reservedIdCount = 0;
    for (int i = 0; i < RESERVED_IDS_PER_AREA; i++) {
        if (ra->reservedIds[i] != np->globalIndex) { continue; }
        reservedIds[reservedIdCount] = i + RESERVED_IDS_SYNC_OBJECT_OFFSET;
        reservedIdCount++;
    }

    // fill in missing reserved ids
    if (reservedIdCount < RESERVED_IDS_PER_PLAYER_COUNT) {
        for (int i = 0; i < RESERVED_IDS_PER_AREA; i++) {
            if (ra->reservedIds[i] != RESERVED_IDS_UNRESERVED) { continue; }
            ra->reservedIds[i] = np->globalIndex;
            informPlayer = true;
            reservedIds[reservedIdCount] = i + RESERVED_IDS_SYNC_OBJECT_OFFSET;
            reservedIdCount++;
            if (reservedIdCount >= RESERVED_IDS_PER_PLAYER_COUNT) { break; }
        }
    }

    if (gNetworkType == NT_SERVER && np == gNetworkPlayerLocal) {
        // refresh server's local
        sLocalReservationArea.courseNum = np->currCourseNum;
        sLocalReservationArea.actNum    = np->currActNum;
        sLocalReservationArea.levelNum  = np->currLevelNum;
        sLocalReservationArea.areaIndex = np->currAreaIndex;

        for (int i = 0; i < RESERVED_IDS_PER_PLAYER_COUNT; i++) {
            sLocalReservationArea.reservedIds[i] = reservedIds[i];
        }
    } else if (informPlayer) {
        // inform remote player of reservation list
        network_send_reservation_list(np, reservedIds);
    }
}

static void reservation_area_unload(struct ReservationArea* unloadRa) {
    struct ReservationArea* ra = sReservationAreas;
    struct ReservationArea* lastRa = NULL;
    while (ra != NULL) {
        if (ra == unloadRa) {
            if (lastRa == NULL) {
                sReservationAreas = ra->next;
            } else {
                lastRa->next = ra->next;
            }
            free(unloadRa);
            return;
        }
        lastRa = ra;
        ra = ra->next;
    }
    SOFT_ASSERT(false);
}

static void reservation_area_player_left(struct NetworkPlayer* np) {
    // make sure player has a RA
    struct ReservationArea* ra = sReservationAreaPerPlayer[np->globalIndex];
    if (ra == NULL) { return; }

    // remove player's reserved ids
    for (int i = 0; i < RESERVED_IDS_PER_AREA; i++) {
        if (ra->reservedIds[i] == np->globalIndex) {
            ra->reservedIds[i] = RESERVED_IDS_UNRESERVED;
        }
    }

    // remove player from RA, unload if sensible
    ra->playersActive--;
    if (ra->playersActive == 0) {
        reservation_area_unload(ra);
    }
    sReservationAreaPerPlayer[np->globalIndex] = NULL;
}

void reservation_area_change(struct NetworkPlayer* np) {
    // check for disconnection
    if (!np->connected) {
        reservation_area_player_left(np);
        return;
    }

    // make sure the location actually changed
    struct ReservationArea* ra = sReservationAreaPerPlayer[np->globalIndex];
    if (ra != NULL && ra->courseNum == np->currCourseNum && ra->actNum == np->currActNum && ra->levelNum == np->currLevelNum && ra->areaIndex == np->currAreaIndex) {
        return;
    }

    // remove from the old reservation area
    reservation_area_player_left(np);

    // find the reservation area
    ra = sReservationAreas;
    struct ReservationArea* lastRa = ra;
    while (ra != NULL) {
        if (ra->courseNum == np->currCourseNum && ra->actNum == np->currActNum && ra->levelNum == np->currLevelNum && ra->areaIndex == np->currAreaIndex) {
            // add to new reservation area
            ra->playersActive++;
            sReservationAreaPerPlayer[np->globalIndex] = ra;
            reservation_area_refresh_ids(np);
            return;
        }
        lastRa = ra;
        ra = ra->next;
    }

    // allocate the reservation area
    ra = malloc(sizeof(struct ReservationArea));
    ra->courseNum = np->currCourseNum;
    ra->actNum    = np->currActNum;
    ra->levelNum  = np->currLevelNum;
    ra->areaIndex = np->currAreaIndex;
    for (int i = 0; i < RESERVED_IDS_PER_AREA; i++) {
        ra->reservedIds[i] = RESERVED_IDS_UNRESERVED;
    }

    ra->playersActive = 1;
    ra->next = NULL;

    sReservationAreaPerPlayer[np->globalIndex] = ra;

    // fix up linked list
    if (lastRa == NULL) {
        sReservationAreas = ra;
    } else {
        lastRa->next = ra;
    }

    // refresh ids
    reservation_area_refresh_ids(np);
}

void reservation_area_use(struct NetworkPlayer* np, u32 syncId) {
    // make sure player has a RA
    struct ReservationArea* ra = sReservationAreaPerPlayer[np->globalIndex];
    if (ra == NULL) { return; }

    u32 offset = syncId - RESERVED_IDS_SYNC_OBJECT_OFFSET;

    // sanity check
    if (offset >= RESERVED_IDS_PER_AREA) { return; }

    ra->reservedIds[offset] = RESERVED_IDS_USED;

    reservation_area_refresh_ids(np);
}

void reservation_area_release(struct NetworkPlayer* np, u32 syncId) {
    // make sure player has a RA
    struct ReservationArea* ra = sReservationAreaPerPlayer[np->globalIndex];
    if (ra == NULL) { return; }

    u32 offset = syncId - RESERVED_IDS_SYNC_OBJECT_OFFSET;

    // sanity check
    if (offset >= RESERVED_IDS_PER_AREA) { return; }

    ra->reservedIds[offset] = RESERVED_IDS_UNRESERVED;

    reservation_area_refresh_ids(np);
}

void reservation_area_local_update(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex, u32 syncIds[]) {
    sLocalReservationArea.courseNum = courseNum;
    sLocalReservationArea.actNum    = actNum;
    sLocalReservationArea.levelNum  = levelNum;
    sLocalReservationArea.areaIndex = areaIndex;

    for (int i = 0; i < RESERVED_IDS_PER_PLAYER_COUNT; i++) {
        sLocalReservationArea.reservedIds[i] = syncIds[i];
    }
}

u32 reservation_area_local_grab_id(void) {
    struct LocalReservationArea* la = &sLocalReservationArea;

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
    if (la->courseNum != gCurrCourseNum || la->actNum != gCurrActStarNum || la->levelNum != gCurrLevelNum || la->areaIndex != gCurrAreaIndex) {
        // invalid location
        return 0;
    }

    // grab a sync id from reserved list
    u32 syncId = 0;
    for (int i = 0; i < RESERVED_IDS_PER_PLAYER_COUNT; i++) {
        if (la->reservedIds[i] == 0 || la->reservedIds[i] == RESERVED_IDS_UNRESERVED || la->reservedIds[i] == RESERVED_IDS_USED) { continue; }

        // found one
        syncId = la->reservedIds[i];
        la->reservedIds[i] = 0;
        break;
    }

    // sanity check
    if (syncId == 0) { return 0; }

    // inform the server that we used that id
    if (gNetworkType == NT_SERVER) {
        reservation_area_use(gNetworkPlayerLocal, syncId);
    } else {
        network_send_reservation_use(syncId);
    }

    return syncId;
}
