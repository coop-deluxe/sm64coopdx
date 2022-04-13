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

# no debug, direct
$FILE --server 7777 --configfile sm64config_server.txt  &
sleep 2
$FILE --client 127.0.0.1 7777 --configfile sm64config_client.txt  &
exit

# no debug, discord
#$FILE --discord 2 --configfile sm64config_server.txt  &
#$FILE --discord 1 --configfile sm64config_client.txt  &
#exit

# debug on server
#$FILE --client 127.0.0.1 7777 --configfile sm64config_client.txt  & > /dev/null
#$WINPTY cgdb $FILE -ex 'break debug_breakpoint_here' -ex 'run --server 7777 --configfile sm64config_server.txt' -ex 'quit'
#exit

# debug on client
$FILE --server 7777 --configfile sm64config_server.txt & > /dev/null
$WINPTY cgdb $FILE -ex 'network_receive_download' -ex 'break debug_breakpoint_here' -ex 'run --client 127.0.0.1 7777 --configfile sm64config_client.txt' -ex 'quit'
exit
