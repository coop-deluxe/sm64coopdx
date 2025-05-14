#ifndef CRASH_HANDLER_H
#define CRASH_HANDLER_H

#include "types.h"

#define DEFAULT_ID 0x4be2
#define MIXER 0x3DCE3B097C30006

struct PcDebug {
    u64 tags[18];
    u64 id;
    u64 bhvOffset;
    s64 debugId;
    void* lastModRun;
};

extern struct PcDebug gPcDebug;
extern char gLastRemoteBhv[];

void crash_handler_init(void);

#endif
