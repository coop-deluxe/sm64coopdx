#ifdef COOP
#include "dynos.cpp.h"
extern "C" {

bool dynos_warp_to_level(s32 aLevel, s32 aArea, s32 aAct) {
    return DynOS_Warp_ToLevel(aLevel, aArea, aAct);
}

}
#endif
