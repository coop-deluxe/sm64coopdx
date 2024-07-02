#!/bin/bash

set -e
if [ $# -eq 0 ]; then
    make DEBUG=1 DEVELOPMENT=1 STRICT=1 -j
else
    make DEBUG=1 DEVELOPMENT=1 -j
fi

# find file
FILE=./build/us_pc/sm64coopdx.exe
if [ ! -f "$FILE" ]; then
    FILE=./build/us_pc/sm64coopdx
fi

$FILE &
