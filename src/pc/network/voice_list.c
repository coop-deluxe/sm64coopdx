#include "voice_list.h"

struct VoiceList* gVoiceList;

u32 gVoiceListCount;
static u32 gVoiceListCapacity;

struct VoiceList* voice_list_get(const char* address) {
    for (u32 i = 0; gVoiceList && i < gVoiceListCount; i++) {
        if (strcmp(address, gVoiceList[i].address) == 0)
            return &gVoiceList[i];
    }
    return NULL;
}

struct VoiceList* voice_list_get_or_create(const char* address) {
    struct VoiceList* list = voice_list_get(address);
    if (list) return list;

    if (gVoiceListCount >= gVoiceListCapacity) {
        if (gVoiceListCapacity == 0) gVoiceListCapacity = 4;
        else gVoiceListCapacity *= 2;

        gVoiceList = realloc(gVoiceList, sizeof(struct VoiceList) * gVoiceListCapacity);
    }

    list = &gVoiceList[gVoiceListCount++];
    memset(list, 0, sizeof(struct VoiceList));
    list->address = strdup(address);
    list->volume = 100;
    return list;
}
