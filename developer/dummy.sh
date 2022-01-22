#!/bin/bash
make RENDER_API=DUMMY AUDIO_API=DUMMY CONTROLLER_API= DEBUG=1 DEVELOPMENT=1 STRICT=1 -j && ./build/us_pc/sm64.us.f3dex2e.exe --server 7777 --savepath ./build/us_pc/
