#!/bin/bash
set -e

function compiler() {
    make clean
    make RENDER_API=$1 WINDOW_API=$2 AUDIO_API=$3 CONTROLLER_API=$4 TARGET_BITS=$5
    mv ./build ./build_$6
}

function compiler_no_discord() {
    make clean
    make DISCORD_SDK=0
    mv ./build ./build_no_discord
}

compiler DUMMY DUMMY DUMMY "" 64 dummy_64
compiler GL_LEGACY SDL1 SDL1 SDL1 64 legacy_1
#compiler GL SDL1 SDL1 SDL1 64 gl_1
#compiler D3D11 DXGI SDL1 SDL1 64 d3d11_1
#compiler D3D12 DXGI SDL1 SDL1 64 d3d12_1

compiler GL_LEGACY SDL2 SDL2 SDL2 64 legacy_2
compiler GL SDL2 SDL2 SDL2 64 gl_2
compiler D3D11 DXGI SDL2 SDL2 64 d3d11_2
compiler D3D12 DXGI SDL2 SDL2 64 d3d12_2

compiler GL SDL2 SDL2 SDL2 32 gl_2_32

compiler_no_discord
