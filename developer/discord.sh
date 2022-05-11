#!/bin/bash

set -e
if [ $# -eq 0 ]; then
    make DEBUG=1 DEVELOPMENT=1 STRICT=1 -j
else
    make DEBUG=1 DEVELOPMENT=1 -j
fi

# find file
FILE=./build/us_pc/sm64.us.f3dex2e.exe
WINPTY=winpty
if [ ! -f "$FILE" ]; then
    FILE=./build/us_pc/sm64.us.f3dex2e
    WINPTY=
fi

# no debug, discord
$FILE --discord 2 --configfile sm64config_server.txt  &
$FILE --discord 1 --configfile sm64config_client.txt  &
exit
