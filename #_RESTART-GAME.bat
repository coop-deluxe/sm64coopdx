@echo off
taskkill /F /IM sm64coopdx_rt64.exe
"C:\msys64\msys2_shell.cmd" -mingw64 -where "%cd%" -no-start -c "./build/us_pc/sm64coopdx_rt64.exe --console; exec bash"
