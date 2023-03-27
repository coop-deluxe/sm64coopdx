#ifndef RESERVATION_AREA_H
#define RESERVATION_AREA_H

#include "PR/ultratypes.h"
#include <time.h>
#include <types.h>
#include <assert.h>
#include <stdbool.h>

#define RESERVED_IDS_PER_PLAYER_COUNT 5
#define RESERVED_IDS_SYNC_OBJECT_OFFSET 2048

struct NetworkPlayer;

void reservation_area_debug(void);
void reservation_area_change(struct NetworkPlayer* np);
void reservation_area_use(struct NetworkPlayer* np, u32 syncId);
void reservation_area_release(struct NetworkPlayer* np, u32 syncId);
void reservation_area_local_update(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex, u32 syncIds[]);
u32 reservation_area_local_grab_id(void);

#endif
