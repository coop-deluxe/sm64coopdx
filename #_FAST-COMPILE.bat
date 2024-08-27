@echo off
"C:\msys64\msys2_shell.cmd" -mingw64 -where "%cd%" -no-start -c "make RENDER_API=RT64 -j16; exec bash"
