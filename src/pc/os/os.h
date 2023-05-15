#pragma once
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include "os_win.h"
#else
#include "os_other.h"
#endif