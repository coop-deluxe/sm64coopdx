#!/bin/bash
cmd //C "taskkill /F /T /IM sm64coopdx.exe"
cd ..; make -j; if [ $? -ne 0 ]; then echo ' '; echo ' '; echo '----------------------------------------'; echo '[BUILDING/COMPILING FAILED]'; echo '----------------------------------------'; echo ' '; else echo ' '; echo ' '; echo '++++++++++++++++++++++++++++++++++++++++'; echo '[BUILDING/COMPILING SUCCESSFUL]'; echo '++++++++++++++++++++++++++++++++++++++++'; echo ' '; start build/us_pc/sm64coopdx.exe --console --server 7777; fi; read -p 'Press [Enter] to close...'
