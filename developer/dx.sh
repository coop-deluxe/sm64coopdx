function compiler() {
    make RENDER_API=$1 WINDOW_API=$2 AUDIO_API=$3 CONTROLLER_API=$4
}

compiler D3D12 DXGI SDL2 SDL2 d3d12_2

./build/us_pc/sm64.us.f3dex2e.exe
