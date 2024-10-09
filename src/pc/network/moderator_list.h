#ifndef MODERATOR_LIST_H
#define MODERATOR_LIST_H

#include <stdbool.h>

extern char** gModeratorAddresses;
extern bool* gModerator;
extern u16 gModeratorCount;

void moderator_list_clear(void);
void moderator_list_add(char* address, bool perm);
bool moderator_list_contains(char* address);

#endif