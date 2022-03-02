#!/bin/bash

set -e

make RENDER_API=GL WINDOW_API=SDL1 AUDIO_API=SDL1 CONTROLLER_API=SDL1 DEBUG=1 DEVELOPMENT=1 -j

# find file
FILE=./build/us_pc/sm64.us.f3dex2e.exe
if [ ! -f "$FILE" ]; then
    FILE=./build/us_pc/sm64.us.f3dex2e
fi

$FILE &
