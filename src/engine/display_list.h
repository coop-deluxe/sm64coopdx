#include <PR/gbi.h>

#define C0(cmd, pos, width) (((cmd)->words.w0 >> (pos)) & ((1U << width) - 1))

u32 gfx_get_size(const Gfx* gfx);
