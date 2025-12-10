@echo off
REM =====================================================
REM BungeeCord64 Test Environment Launcher
REM =====================================================
REM This script launches 4 instances of SM64CoopDX:
REM - Server 1 on port 7777 (Main Server)
REM - Server 2 on port 7778
REM - Server 3 on port 7779
REM - Player/Client instance (starts normally, join via menu)
REM =====================================================

REM Set the path to the executable (adjust if needed)
SET GAME_EXE=build\us_pc\sm64coopdx.exe

REM Check if executable exists
if not exist "%GAME_EXE%" (
    echo ERROR: Game executable not found at %GAME_EXE%
    pause
    exit /b 1
)

REM Start all servers and player without showing console windows
start "" /min "%GAME_EXE%" --server 7777 --skip-intro --configfile config_server_7777.txt
timeout /t 2 /nobreak > nul

start "" /min "%GAME_EXE%" --server 7778 --skip-intro --configfile config_server_7778.txt
timeout /t 2 /nobreak > nul

start "" /min "%GAME_EXE%" --server 7779 --skip-intro --configfile config_server_7779.txt
timeout /t 2 /nobreak > nul

start "" "%GAME_EXE%" --configfile config_player.txt

exit
