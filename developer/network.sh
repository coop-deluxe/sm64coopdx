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
#$FILE --discord 2 --configfile sm64config_server.txt  &
#$FILE --discord 1 --configfile sm64config_client.txt  &
#exit

# no debug, direct
$FILE --server 27015 --configfile sm64config_server.txt  &
sleep 2
$FILE --client 127.0.0.1 27015 --configfile sm64config_client.txt  &
exit

# debug on server
#$FILE --client 127.0.0.1 27015 --configfile sm64config_client.txt  & > /dev/null
#winpty cgdb $FILE -ex 'break debug_breakpoint_here' -ex 'run --server 27015 --configfile sm64config_server.txt' -ex 'quit'
#exit

###################
# debug on client #
###################

$FILE --server 27015 --configfile sm64config_server.txt &

# debug if cgdb exists
if ! [ -x "$(command -v cgdb)" ]; then
    $FILE --client 127.0.0.1 27015 --configfile sm64config_client.txt &
else
    winpty cgdb $FILE -ex 'break debug_breakpoint_here' -ex 'run --client 127.0.0.1 27015 --configfile sm64config_client.txt' -ex 'quit'
fi
