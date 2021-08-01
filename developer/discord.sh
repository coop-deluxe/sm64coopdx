#!/bin/bash
set -e
if [ $# -eq 0 ]; then
    make BETTERCAMERA=1 NODRAWINGDISTANCE=1 DEBUG=1 IMMEDIATELOAD=1 DEVELOPMENT=1 STRICT=1 -j
else
    make BETTERCAMERA=1 NODRAWINGDISTANCE=1 DEBUG=1 IMMEDIATELOAD=1 DEVELOPMENT=1 -j
fi

# find file
FILE=./build/us_pc/sm64.us.f3dex2e.exe
if [ ! -f "$FILE" ]; then
    FILE=./build/us_pc/sm64.us.f3dex2e
fi

# no debug, discord
$FILE --discord 2 --configfile sm64config_server.txt  &
$FILE --discord 1 --configfile sm64config_client.txt  &
exit


#debug discord client
$FILE --discord 2 --configfile sm64config_server.txt  &
winpty cgdb ./build/us_pc/sm64.us.f3dex2e.exe -ex 'break debug_breakpoint_here' -ex 'r --discord 1 --configfile sm64config_client.txt'
