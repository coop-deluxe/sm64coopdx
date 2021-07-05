#!/bin/bash
make BETTERCAMERA=1 NODRAWINGDISTANCE=1 DEBUG=1 IMMEDIATELOAD=1 DEVELOPMENT=1 STRICT=1 && winpty cgdb ./build/us_pc/sm64.us.f3dex2e.exe -ex 'break debug_breakpoint_here'
#make BETTERCAMERA=1 NODRAWINGDISTANCE=1 DEBUG=1 IMMEDIATELOAD=1 DEVELOPMENT=1 STRICT=1 && winpty cgdb ./build/us_pc/sm64.us.f3dex2e.exe -ex 'break debug_breakpoint_here' -ex 'run --server 27015 --configfile sm64config_server.txt'
