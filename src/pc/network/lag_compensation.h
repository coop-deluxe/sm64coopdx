#ifndef NETWORK_LAG_COMPENSATION_H
#define NETWORK_LAG_COMPENSATION_H

void lag_compensation_clear(void);
void lag_compensation_store(void);
struct MarioState* lag_compensation_get_local_state(struct NetworkPlayer* otherNp);

#endif