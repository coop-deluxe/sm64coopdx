#ifndef NETWORK_LAG_COMPENSATION_H
#define NETWORK_LAG_COMPENSATION_H

#define MAX_LOCAL_STATE_HISTORY 30

void lag_compensation_clear(void);
/* |description|Stores the local Mario's current state in lag compensation history|descriptionEnd| */
void lag_compensation_store(void);
/* |description|Gets the local Mario's state stored in lag compensation history|descriptionEnd| */
struct MarioState* lag_compensation_get_local_state(struct NetworkPlayer* otherNp);
/* |description|Checks if lag compensation history is ready|descriptionEnd| */
bool lag_compensation_get_local_state_ready(void);
/* |description|Gets the local Mario's state index|descriptionEnd| */
u32 lag_compensation_get_local_state_index(void);

#endif