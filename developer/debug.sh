#!/bin/bash
winpty cgdb ./build/us_pc/sm64.us.f3dex2e.exe -ex 'break debug_breakpoint_here'
