#ifndef VOICE_LIST_H
#define VOICE_LIST_H

#include "types.h"

struct VoiceList {
    char* address;
    u32 volume;
    bool is_muted, is_globally_muted;
};

extern struct VoiceList* gVoiceList;
extern u32 gVoiceListCount;

struct VoiceList* voice_list_get(const char* address);
struct VoiceList* voice_list_get_or_create(const char* address);

#endif