#include "types.h"
#include "network_player.h"
#include "lag_compensation.h"
#include "pc/debuglog.h"
#include "game/object_helpers.h"
#include "behavior_table.h"
#include "model_ids.h"

struct StateHistory {
    struct MarioState m;
    struct Object marioObj;
    struct MarioBodyState bodyState;
};

static struct StateHistory sLocalStateHistory[MAX_LOCAL_STATE_HISTORY] = { 0 };
static bool sLocalStateHistoryReady = false;
static u32 sLocalStateHistoryIndex = 0;

void lag_compensation_clear(void) {
    sLocalStateHistoryReady = false;
    sLocalStateHistoryIndex = 0;
}

void lag_compensation_store(void) {
    if (!gMarioStates[0].marioBodyState) { return; }
    if (!gMarioStates[0].marioObj) { return; }

    struct StateHistory* sh = &sLocalStateHistory[sLocalStateHistoryIndex];
    memcpy(&sh->m, &gMarioStates[0], sizeof(struct MarioState));
    memcpy(&sh->marioObj, gMarioStates[0].marioObj, sizeof(struct Object));
    memcpy(&sh->bodyState, gMarioStates[0].marioBodyState, sizeof(struct MarioBodyState));
    sh->m.marioObj = &sh->marioObj;
    sh->m.marioBodyState = &sh->bodyState;

    if (sLocalStateHistoryIndex + 1 >= MAX_LOCAL_STATE_HISTORY) {
        sLocalStateHistoryReady = true;
    }
    sLocalStateHistoryIndex = (sLocalStateHistoryIndex + 1) % MAX_LOCAL_STATE_HISTORY;
}

struct MarioState* lag_compensation_get_local_state(struct NetworkPlayer* otherNp) {
    if (!otherNp) { return &gMarioStates[0]; }
    if (gNetworkType == NT_NONE) { return &gMarioStates[0]; }
    if (!sLocalStateHistoryReady) { return &gMarioStates[0]; }

    s32 pingToTicks = (otherNp->ping / 1000.0f) * 30;
    if (pingToTicks > (MAX_LOCAL_STATE_HISTORY-1)) {
        pingToTicks = (MAX_LOCAL_STATE_HISTORY-1);
    }
    //LOG_INFO("Ping: %s :: %u :: %d", otherNp->name, otherNp->ping, pingToTicks);
    if (pingToTicks == 0) { return &gMarioStates[0]; }

    s32 index = (s32)sLocalStateHistoryIndex - pingToTicks;
    while (index < 0) { index += MAX_LOCAL_STATE_HISTORY; }
    index = index % MAX_LOCAL_STATE_HISTORY;

    return &sLocalStateHistory[index].m;
}

bool lag_compensation_get_local_state_ready(void) {
    return sLocalStateHistoryReady;
}

u32 lag_compensation_get_local_state_index(void) {
    return sLocalStateHistoryIndex;
}
