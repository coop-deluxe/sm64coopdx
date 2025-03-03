#ifndef SOCKET_H
#define SOCKET_H

#ifdef __SWITCH__
#include "socket_nx.h"
#else
#include "socket_pc.h"
#endif // __SWITCH__
#endif // SOCKET_H
