#!/bin/bash
# This script installs the 'requests' package and runs download.py

# Check for pip; if not found, try pip3
if command -v pip &>/dev/null; then
    echo "Using pip..."
    pip install requests
elif command -v pip3 &>/dev/null; then
    echo "pip not found, falling back to pip3..."
    pip3 install requests
else
    echo "Error: Neither pip nor pip3 is installed. Please install pip before running this script." >&2
    exit 1
fi

# Now, run download.py using python. If 'python' is not available, try 'python3'
if command -v python &>/dev/null; then
    echo "Running download.py with python..."
    python download.py
elif command -v python3 &>/dev/null; then
    echo "python not found, using python3..."
    python3 download.py
else
    echo "Error: Neither python nor python3 is installed. Please install Python before running this script." >&2
    exit 1
fi
