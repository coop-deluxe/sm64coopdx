#!/bin/bash

set -e
if [ $# -eq 0 ]; then
    make DEBUG=1 DEVELOPMENT=1 STRICT=1 ASAN=1 COMPILER=clang -j
else
    make DEBUG=1 DEVELOPMENT=1 ASAN=1 COMPILER=clang -j
fi

# find file
FILE=./build/us_pc/sm64.us.f3dex2e.exe
WINPTY=winpty
if [ ! -f "$FILE" ]; then
    FILE=./build/us_pc/sm64.us.f3dex2e
    WINPTY=
fi

$WINPTY cgdb $FILE
