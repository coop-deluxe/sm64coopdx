@echo off
REM This script installs the 'requests' package and runs download.py

REM Check for pip installation
where pip >nul 2>&1
if errorlevel 1 (
    where pip3 >nul 2>&1
    if errorlevel 1 (
        echo Error: Neither pip nor pip3 is installed. Please install pip before running this script.
        exit /b 1
    ) else (
        echo pip not found, falling back to pip3...
        set "PIP_CMD=pip3"
    )
) else (
    echo Using pip...
    set "PIP_CMD=pip"
)

REM Install the requests package
%PIP_CMD% install requests
if errorlevel 1 (
    echo Error installing requests.
    exit /b 1
)

REM Check for python installation
where python >nul 2>&1
if errorlevel 1 (
    where python3 >nul 2>&1
    if errorlevel 1 (
        echo Error: Neither python nor python3 is installed. Please install Python before running this script.
        exit /b 1
    ) else (
        echo python not found, using python3...
        set "PYTHON_CMD=python3"
    )
) else (
    echo Using python...
    set "PYTHON_CMD=python"
)

REM Run the download.py script
%PYTHON_CMD% download.py
