#ifndef NETWORK_LAG_COMPENSATION_H
#define NETWORK_LAG_COMPENSATION_H

#define MAX_LOCAL_STATE_HISTORY 30

void lag_compensation_clear(void);
void lag_compensation_store(void);
struct MarioState* lag_compensation_get_local_state(struct NetworkPlayer* otherNp);
bool lag_compensation_get_local_state_ready(void);
u32 lag_compensation_get_local_state_index(void);

#endif