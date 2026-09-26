#ifndef BADNET_H
#define BADNET_H

#include <PR/ultratypes.h>

extern bool gBadNetEnabled;
extern f64 gBadNetLatency;
extern f64 gBadNetLatencyJitter;
extern f64 gBadNetPacketLoss;
extern f64 gBadNetPacketDuplicate;
extern struct NetworkSystem gNetworkSystemBadNet;

#endif
