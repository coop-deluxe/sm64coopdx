#!/bin/bash
make clean ; scan-build -disable-checker deadcode.DeadStores make BETTERCAMERA=1 NODRAWINGDISTANCE=1 DEBUG=1 IMMEDIATELOAD=1 DEVELOPMENT=1 STRICT=1 EXTRA_INCLUDES="-IC:/msys64/mingw64/include" -j
