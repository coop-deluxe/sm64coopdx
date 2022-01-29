s32 f32_find_wall_collision(f32 *xPtr, f32 *yPtr, f32 *zPtr, f32 offsetY, f32 radius);
s32 find_wall_collisions(struct WallCollisionData *colData);
f32 find_ceil(f32 posX, f32 posY, f32 posZ, struct Surface **pceil);
f32 find_floor_height_and_data(f32 xPos, f32 yPos, f32 zPos, struct FloorGeometry **floorGeo);
f32 find_floor_height(f32 x, f32 y, f32 z);
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor);
f32 find_water_level(f32 x, f32 z);
f32 find_poison_gas_level(f32 x, f32 z);
void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos);
