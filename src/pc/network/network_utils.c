#include "network_utils.h"

u8 network_global_index_from_local(u8 localIndex) {
    if (gNetworkType == NT_SERVER) { return localIndex; }

    if (gNetworkPlayerLocal == NULL) { return UNKNOWN_GLOBAL_INDEX; }
    if (localIndex == 0) { return gNetworkPlayerLocal->globalIndex; } // me
    if (localIndex == 1) { return 0; } // server

    return localIndex - ((localIndex <= gNetworkPlayerLocal->globalIndex) ? 1 : 0);
}

u8 network_local_index_from_global(u8 globalIndex) {
    if (gNetworkType == NT_SERVER) { return globalIndex; }

    if (gNetworkPlayerLocal == NULL) { return UNKNOWN_LOCAL_INDEX; }
    if (gNetworkPlayerLocal->globalIndex == globalIndex) { return 0; } // me
    if (globalIndex == 0) { return 1; } // server

    return globalIndex + ((globalIndex < gNetworkPlayerLocal->globalIndex) ? 1 : 0);
}

bool network_is_server(void) {
    return gNetworkType == NT_SERVER;
}
