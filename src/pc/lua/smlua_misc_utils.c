#include "types.h"

#include "smlua.h"
#include "smlua_misc_utils.h"
#include "src/engine/surface_collision.h"
#include "pc/debuglog.h"

struct RayIntersectionInfo* collision_find_surface_on_ray(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ) {
    static struct RayIntersectionInfo info = { 0 };
    Vec3f orig = { startX, startY, startZ };
    Vec3f end = { endX, endY, endZ };
    find_surface_on_ray(orig, end, &info.surface, info.hitPos);
    return &info;
}

u32 get_network_area_timer(void) {
    return gNetworkAreaTimer;
}