#include <stdlib.h>
#include <string.h>
#include <PR/ultratypes.h>
#include "moderator_list.h"
#include "pc/debuglog.h"

char** gModeratorAddresses = NULL;
bool* gModerator = NULL;
u16 gModeratorCount = 0;

void moderator_list_clear(void) {
    for (u16 i = 0; i < gModeratorCount; i++) {
        if (gModeratorAddresses[i] == NULL) { continue; }
        free(gModeratorAddresses[i]);
    }
    gModeratorCount = 0;

    if (gModeratorAddresses != NULL) {
        free(gModeratorAddresses);
        gModeratorAddresses = NULL;
    }
    if (gModerator != NULL) {
        free(gModerator);
        gModerator = NULL;
    }
}

void moderator_list_add(char* address, bool perm) {
    u16 index = gModeratorCount++;
    if (gModeratorAddresses == NULL) {
        gModeratorAddresses = malloc(sizeof(char*) * gModeratorCount);
        gModerator = malloc(sizeof(bool) * gModeratorCount);
    } else {
        gModeratorAddresses = realloc(gModeratorAddresses, sizeof(char*) * gModeratorCount);
        gModerator = realloc(gModerator, sizeof(bool) * gModeratorCount);
    }
    if (gModeratorAddresses == NULL) {
        LOG_ERROR("Failed to allocate gModeratorAddresses");
        return;
    }
    if (gModerator == NULL) {
        LOG_ERROR("Failed to allocate gModerator");
        return;
    }
    gModeratorAddresses[index] = strdup(address);
    gModerator[index] = perm;
}

bool moderator_list_contains(char* address) {
    if (gModeratorAddresses == NULL || address == NULL) {
        return false;
    }

    for (s32 i = 0; i < gModeratorCount; i++) {
        if (gModeratorAddresses[i] == NULL) { continue; }
        if (strcmp(address, gModeratorAddresses[i]) == 0) {
            return true;
        }
    }

    return false;
}
