#!/bin/bash
set -e

function compiler() {
    make clean
    make RENDER_API=$1 WINDOW_API=$2 AUDIO_API=$3 CONTROLLER_API=$4
    mv ./build ./build_$5
}

function compiler_no_discord() {
    make clean
    make DISCORD_SDK=0
    mv ./build ./build_no_discord
}

compiler GL_LEGACY SDL1 SDL1 SDL1 legacy_1
compiler GL SDL1 SDL1 SDL1 gl_1
compiler D3D11 DXGI SDL1 SDL1 d3d11_1
compiler D3D12 DXGI SDL1 SDL1 d3d12_1

compiler GL_LEGACY SDL2 SDL2 SDL2 legacy_2
compiler GL SDL2 SDL2 SDL2 gl_2
compiler D3D11 DXGI SDL2 SDL2 d3d11_2
compiler D3D12 DXGI SDL2 SDL2 d3d12_2

compiler_no_discord
