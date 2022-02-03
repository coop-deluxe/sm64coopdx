#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <stdbool.h>
#include "network.h"

u8 network_global_index_from_local(u8 localIndex);
u8 network_local_index_from_global(u8 globalIndex);

bool network_is_server(void);

#endif