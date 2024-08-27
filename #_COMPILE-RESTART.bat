@echo off
taskkill /F /IM sm64coopdx_rt64.exe
taskkill /F /IM mintty.exe
"C:\msys64\msys2_shell.cmd" -mingw64 -where "%cd%" -no-start -c "make RENDER_API=RT64; ./build/us_pc/sm64coopdx_rt64.exe --console; exec bash"
