#include "dynos.cpp.h"
extern "C" {
}

bool gDynosModShutdown = false;

void DynOS_Gfx_Update() {
    DynOS_Mod_Update();
    DynOS_Tex_Update();
}
