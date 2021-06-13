#ifndef RESERVATION_AREA_H
#define RESERVATION_AREA_H

#include "PR/ultratypes.h"
#include <time.h>
#include <types.h>
#include <assert.h>
#include <stdbool.h>

#define RESERVED_IDS_PER_PLAYER_COUNT 5
#define RESERVED_IDS_SYNC_OBJECT_OFFSET 127

struct NetworkPlayer;

void reservation_area_debug(void);
void reservation_area_change(struct NetworkPlayer* np);
void reservation_area_use(struct NetworkPlayer* np, u8 syncId);
void reservation_area_release(struct NetworkPlayer* np, u8 syncId);
void reservation_area_local_update(u8 courseNum, u8 actNum, u8 levelNum, u8 areaIndex, u8 syncIds[]);
u8 reservation_area_local_grab_id(void);

#endif
