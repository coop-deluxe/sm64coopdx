#include "dynos.cpp.h"

u32 gDynosModDataLastError = 0;

extern "C" {

u32 dynos_mod_data_get_last_error() {
    return gDynosModDataLastError;
}

}
