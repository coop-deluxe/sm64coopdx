#!/bin/bash
#make BETTERCAMERA=1 NODRAWINGDISTANCE=1 DEBUG=1 IMMEDIATELOAD=1 DEVELOPMENT=1 STRICT=1 -j && winpty cgdb ./build/us_pc/sm64.us.f3dex2e.exe -ex 'break debug_breakpoint_here' -ex 'run' -ex 'quit'
#make BETTERCAMERA=1 NODRAWINGDISTANCE=1 DEBUG=1 IMMEDIATELOAD=1 DEVELOPMENT=1 STRICT=1 -j && winpty cgdb ./build/us_pc/sm64.us.f3dex2e.exe -ex 'break debug_breakpoint_here' -ex 'run --server 27015 --configfile sm64config_server.txt' -ex 'quit'
#make BETTERCAMERA=1 NODRAWINGDISTANCE=1 DEBUG=1 IMMEDIATELOAD=1 DEVELOPMENT=1 STRICT=1 -j && ./build/us_pc/sm64.us.f3dex2e.exe --server 27015 --configfile sm64config_server.txt
make BETTERCAMERA=1 NODRAWINGDISTANCE=1 DEBUG=1 IMMEDIATELOAD=1 DEVELOPMENT=1 STRICT=1 -j && ./build/us_pc/sm64.us.f3dex2e.exe
