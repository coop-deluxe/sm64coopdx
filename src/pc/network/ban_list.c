#include <stdlib.h>
#include <string.h>
#include <PR/ultratypes.h>
#include "ban_list.h"
#include "pc/debuglog.h"

char** gBanAddresses = NULL;
bool* gBanPerm = NULL;
u16 gBanCount = 0;

void ban_list_add(char* address, bool perm) {
    u16 index = gBanCount++;
    if (gBanAddresses == NULL) {
        gBanAddresses = malloc(sizeof(char*) * gBanCount);
        gBanPerm = malloc(sizeof(bool) * gBanCount);
    } else {
        gBanAddresses = realloc(gBanAddresses, sizeof(char*) * gBanCount);
        assert(gBanAddresses != NULL);
        gBanPerm = realloc(gBanPerm, sizeof(bool) * gBanCount);
        assert(gBanPerm != NULL);
    }
    if (gBanAddresses == NULL) {
        LOG_ERROR("Failed to allocate gBanAddresses");
        return;
    }
    if (gBanPerm == NULL) {
        LOG_ERROR("Failed to allocate gBanPerm");
        return;
    }
    gBanAddresses[index] = strdup(address);
    gBanPerm[index] = perm;
}

bool ban_list_contains(char* address) {
    if (gBanAddresses == NULL || address == NULL) {
        return false;
    }

    for (s32 i = 0; i < gBanCount; i++) {
        if (gBanAddresses[i] == NULL) { continue; }
        if (strcmp(address, gBanAddresses[i]) == 0) {
            return true;
        }
    }

    return false;
}
