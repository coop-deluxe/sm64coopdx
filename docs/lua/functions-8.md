## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-7.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | [7](functions-7.md) | 8]


---
# functions from spawn_sound.h

<br />


## [cur_obj_play_sound_1](#cur_obj_play_sound_1)

### Description
Plays a sound if the current object is visible

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = cur_obj_play_sound_1(soundMagic)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundMagic | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_play_sound_1(s32 soundMagic);`

[:arrow_up_small:](#)

<br />

## [cur_obj_play_sound_2](#cur_obj_play_sound_2)

### Description
Plays a sound if the current object is visible and queues rumble for specific sounds

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c75000> = cur_obj_play_sound_2(soundMagic)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundMagic | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_play_sound_2(s32 soundMagic);`

[:arrow_up_small:](#)

<br />

## [create_sound_spawner](#create_sound_spawner)

### Description
Create a sound spawner for objects that need a sound play once. (Breakable walls, King Bobomb exploding, etc)

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = create_sound_spawner(soundMagic)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundMagic | `integer` |

### Returns
- None

### C Prototype
`void create_sound_spawner(s32 soundMagic);`

[:arrow_up_small:](#)

<br />

## [calc_dist_to_volume_range_1](#calc_dist_to_volume_range_1)

### Description
Unused vanilla function, calculates a volume based on `distance`. If `distance` is less than 500 then 127, if `distance` is greater than 1500 then 0, if `distance` is between 500 and 1500 then it ranges linearly from 60 to 124. What an even more strange and confusing function

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = calc_dist_to_volume_range_1(distance)`

### Parameters
| Field | Type |
| ----- | ---- |
| distance | `number` |

### Returns
- `integer`

### C Prototype
`s32 calc_dist_to_volume_range_1(f32 distance);`

[:arrow_up_small:](#)

<br />

## [calc_dist_to_volume_range_2](#calc_dist_to_volume_range_2)

### Description
Unused vanilla function, calculates a volume based on `distance`. If `distance` is less than 1300 then 127, if `distance` is greater than 2300 then 0, if `distance` is between 1300 and 2300 then it ranges linearly from 60 to 127. What a strange and confusing function

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = calc_dist_to_volume_range_2(distance)`

### Parameters
| Field | Type |
| ----- | ---- |
| distance | `number` |

### Returns
- `integer`

### C Prototype
`s32 calc_dist_to_volume_range_2(f32 distance);`

[:arrow_up_small:](#)

<br />

---
# functions from surface_collision.h

<br />


## [find_wall_collisions](#find_wall_collisions)

### Description
Detects wall collisions at a given position and adjusts the position based on the walls found. Returns the number of wall collisions detected

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = find_wall_collisions(colData)`

### Parameters
| Field | Type |
| ----- | ---- |
| colData | [WallCollisionData](structs.md#WallCollisionData) |

### Returns
- `integer`

### C Prototype
`s32 find_wall_collisions(struct WallCollisionData *colData);`

[:arrow_up_small:](#)

<br />

## [find_ceil](#find_ceil)

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = find_ceil(posX, posY, posZ, pceil)`

### Parameters
| Field | Type |
| ----- | ---- |
| posX | `number` |
| posY | `number` |
| posZ | `number` |
| pceil | [Surface](structs.md#Surface) |

### Returns
- `number`

### C Prototype
`f32 find_ceil(f32 posX, f32 posY, f32 posZ, struct Surface **pceil);`

[:arrow_up_small:](#)

<br />

## [find_ceil_height](#find_ceil_height)

### Description
Finds the height of the highest ceiling above a given position (x, y, z). If no ceiling is found, returns the default height limit of `gLevelValues.cellHeightLimit`(20000 by default)

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = find_ceil_height(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- `number`

### C Prototype
`f32 find_ceil_height(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [find_floor_height_and_data](#find_floor_height_and_data)

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = find_floor_height_and_data(xPos, yPos, zPos, floorGeo)`

### Parameters
| Field | Type |
| ----- | ---- |
| xPos | `number` |
| yPos | `number` |
| zPos | `number` |
| floorGeo | [FloorGeometry](structs.md#FloorGeometry) |

### Returns
- `number`

### C Prototype
`f32 find_floor_height_and_data(f32 xPos, f32 yPos, f32 zPos, struct FloorGeometry **floorGeo);`

[:arrow_up_small:](#)

<br />

## [find_floor_height](#find_floor_height)

### Description
Finds the height of the highest floor below a given position (x, y, z). If no floor is found, returns the default floor height of `gLevelValues.floorLowerLimit`(-11000 by default)

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = find_floor_height(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- `number`

### C Prototype
`f32 find_floor_height(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [find_floor](#find_floor)

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = find_floor(xPos, yPos, zPos, pfloor)`

### Parameters
| Field | Type |
| ----- | ---- |
| xPos | `number` |
| yPos | `number` |
| zPos | `number` |
| pfloor | [Surface](structs.md#Surface) |

### Returns
- `number`

### C Prototype
`f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor);`

[:arrow_up_small:](#)

<br />

## [find_water_level](#find_water_level)

### Description
Finds the height of water at a given position (x, z), if the position is within a water region. If no water is found, returns the default height of `gLevelValues.floorLowerLimit`(-11000 by default)

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = find_water_level(x, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| z | `number` |

### Returns
- `number`

### C Prototype
`f32 find_water_level(f32 x, f32 z);`

[:arrow_up_small:](#)

<br />

## [find_poison_gas_level](#find_poison_gas_level)

### Description
Finds the height of the poison gas at a given position (x, z), if the position is within a gas region. If no gas is found, returns the default height of `gLevelValues.floorLowerLimit`(-11000 by default)

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = find_poison_gas_level(x, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| z | `number` |

### Returns
- `number`

### C Prototype
`f32 find_poison_gas_level(f32 x, f32 z);`

[:arrow_up_small:](#)

<br />

## [find_surface_on_ray](#find_surface_on_ray)

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = find_surface_on_ray(orig, dir, hit_surface, hit_pos, precision)`

### Parameters
| Field | Type |
| ----- | ---- |
| orig | [Vec3f](structs.md#Vec3f) |
| dir | [Vec3f](structs.md#Vec3f) |
| hit_surface | [Surface](structs.md#Surface) |
| hit_pos | [Vec3f](structs.md#Vec3f) |
| precision | `number` |

### Returns
- None

### C Prototype
`void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos, f32 precision);`

[:arrow_up_small:](#)

<br />

## [set_find_wall_direction](#set_find_wall_direction)

### Description
Sets whether collision finding functions should check wall directions.

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = set_find_wall_direction(dir, active, airborne)`

### Parameters
| Field | Type |
| ----- | ---- |
| dir | [Vec3f](structs.md#Vec3f) |
| active | `boolean` |
| airborne | `boolean` |

### Returns
- None

### C Prototype
`void set_find_wall_direction(Vec3f dir, bool active, bool airborne);`

[:arrow_up_small:](#)

<br />

## [closest_point_to_triangle](#closest_point_to_triangle)

### Description
Gets the closest point of the triangle to `src` and returns it in `out`.

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = closest_point_to_triangle(surf, src, out)`

### Parameters
| Field | Type |
| ----- | ---- |
| surf | [Surface](structs.md#Surface) |
| src | [Vec3f](structs.md#Vec3f) |
| out | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void closest_point_to_triangle(struct Surface* surf, Vec3f src, OUT Vec3f out);`

[:arrow_up_small:](#)

<br />

---
# functions from surface_load.h

<br />


## [load_object_collision_model](#load_object_collision_model)

### Description
Loads the object's collision data into dynamic collision. You must run this every frame in your object's behavior loop for it to have collision

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = load_object_collision_model()`

### Parameters
- None

### Returns
- None

### C Prototype
`void load_object_collision_model(void);`

[:arrow_up_small:](#)

<br />

## [load_static_object_collision](#load_static_object_collision)

### Description
Loads the object's collision data into static collision. You may run this only once to capture the object's collision at that frame.

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = load_static_object_collision()`

### Parameters
- None

### Returns
- [StaticObjectCollision](structs.md#StaticObjectCollision)

### C Prototype
`struct StaticObjectCollision *load_static_object_collision();`

[:arrow_up_small:](#)

<br />

## [toggle_static_object_collision](#toggle_static_object_collision)

### Description
Toggles a collection of static object surfaces

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = toggle_static_object_collision(col, tangible)`

### Parameters
| Field | Type |
| ----- | ---- |
| col | [StaticObjectCollision](structs.md#StaticObjectCollision) |
| tangible | `boolean` |

### Returns
- None

### C Prototype
`void toggle_static_object_collision(struct StaticObjectCollision *col, bool tangible);`

[:arrow_up_small:](#)

<br />

## [get_static_object_surface](#get_static_object_surface)

### Description
Gets a surface corresponding to `index` from the static object collision

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = get_static_object_surface(col, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| col | [StaticObjectCollision](structs.md#StaticObjectCollision) |
| index | `integer` |

### Returns
- [Surface](structs.md#Surface)

### C Prototype
`struct Surface *get_static_object_surface(struct StaticObjectCollision *col, u32 index);`

[:arrow_up_small:](#)

<br />

## [obj_get_surface_from_index](#obj_get_surface_from_index)

### Description
Gets a surface corresponding to `index` from the surface pool buffer

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = obj_get_surface_from_index(o, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| index | `integer` |

### Returns
- [Surface](structs.md#Surface)

### C Prototype
`struct Surface *obj_get_surface_from_index(struct Object *o, u32 index);`

[:arrow_up_small:](#)

<br />

## [surface_has_force](#surface_has_force)

### Description
Checks if a surface has force

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = surface_has_force(surfaceType)`

### Parameters
| Field | Type |
| ----- | ---- |
| surfaceType | `integer` |

### Returns
- `boolean`

### C Prototype
`bool surface_has_force(s16 surfaceType);`

[:arrow_up_small:](#)

<br />

---
# functions from sync_object.h

<br />


## [sync_object_get_object](#sync_object_get_object)

### Description
Retrieves an object from a sync ID

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = sync_object_get_object(syncId)`

### Parameters
| Field | Type |
| ----- | ---- |
| syncId | `integer` |

### Returns
- [Object](structs.md#Object)

### C Prototype
`struct Object* sync_object_get_object(u32 syncId);`

[:arrow_up_small:](#)

<br />

## [sync_object_is_initialized](#sync_object_is_initialized)

### Description
Checks if a sync object is initialized using a `syncId`

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = sync_object_is_initialized(syncId)`

### Parameters
| Field | Type |
| ----- | ---- |
| syncId | `integer` |

### Returns
- `boolean`

### C Prototype
`bool sync_object_is_initialized(u32 syncId);`

[:arrow_up_small:](#)

<br />

## [sync_object_is_owned_locally](#sync_object_is_owned_locally)

### Description
Checks if a sync object is owned locally using a `syncId`

### Lua Example
`local <generator object doc_function.<locals>.<genexpr> at 0x000001e039c74f20> = sync_object_is_owned_locally(syncId)`

### Parameters
| Field | Type |
| ----- | ---- |
| syncId | `integer` |

### Returns
- `boolean`

### C Prototype
`bool sync_object_is_owned_locally(u32 syncId);`

[:arrow_up_small:](#)

<br />

---

[< prev](functions-7.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | [7](functions-7.md) | 8]

