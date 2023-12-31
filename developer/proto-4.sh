#!/bin/bash
set -e
if [ $# -eq 0 ]; then
    make DEBUG=1 DEVELOPMENT=1 STRICT=1 -j
else
    make DEBUG=1 DEVELOPMENT=1 -j
fi

# find file
FILE=./build/us_pc/sm64.us.f3dex2e.exe
if [ ! -f "$FILE" ]; then
    FILE=./build/us_pc/sm64.us.f3dex2e
fi

$FILE --server 27015 --configfile sm64config_p1.txt  &
sleep 4
$FILE --client 127.0.0.1 27015 --configfile sm64config_p2.txt  &
sleep 2
$FILE --client 127.0.0.1 27015 --configfile sm64config_p3.txt  &
sleep 2
$FILE --client 127.0.0.1 27015 --configfile sm64config_p4.txt  &
