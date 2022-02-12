#ifndef BAN_LIST_H
#define BAN_LIST_H

#include <stdbool.h>

extern char** gBanAddresses;
extern bool* gBanPerm;
extern u16 gBanCount;

void ban_list_add(char* address, bool perm);
bool ban_list_contains(char* address);

#endif