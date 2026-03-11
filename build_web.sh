#!/bin/bash
# Build sm64coopdx for Emscripten/WebAssembly
# Usage: ./build_web.sh         (incremental build)
#        ./build_web.sh clean   (clean then build)

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

# Source Emscripten SDK
if [ -f "$HOME/emsdk/emsdk_env.sh" ]; then
    source "$HOME/emsdk/emsdk_env.sh" 2>/dev/null
elif [ -f "/usr/local/emsdk/emsdk_env.sh" ]; then
    source "/usr/local/emsdk/emsdk_env.sh" 2>/dev/null
fi

if ! command -v emcc &>/dev/null; then
    echo "ERROR: emcc not found. Install Emscripten SDK first."
    exit 1
fi

# Only clean if explicitly requested
if [ "$1" = "clean" ]; then
    echo "Cleaning build/us_pc..."
    rm -rf build/us_pc
fi

echo "Building sm64coopdx for web (TARGET_WEB=1)..."
emmake make TARGET_WEB=1 VERSION=us DEBUG=1 -j$(nproc) 2>&1
