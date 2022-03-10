#ifndef SMLUA_MISC_UTILS_H
#define SMLUA_MISC_UTILS_H

struct RayIntersectionInfo {
    struct Surface* surface;
    Vec3f hitPos;
};

struct RayIntersectionInfo* collision_find_surface_on_ray(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ);
u32 get_network_area_timer(void);

#endif
