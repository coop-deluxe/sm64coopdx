#!/bin/bash
make clean ; scan-build -disable-checker deadcode.DeadStores make DEBUG=1 DEVELOPMENT=1 COMPILER=clang EXTRA_INCLUDES="-IC:/msys64/mingw64/include" -j
