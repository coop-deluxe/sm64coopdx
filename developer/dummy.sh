#!/bin/bash

set -e
make RENDER_API=DUMMY AUDIO_API=DUMMY CONTOLLER_API= -j

# find file
FILE=./build/us_pc/sm64.us.f3dex2e.exe
if [ ! -f "$FILE" ]; then
    FILE=./build/us_pc/sm64.us.f3dex2e
fi

$FILE --server 7777 --savepath ./build/us_pc/
