## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-6.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | 7]


---
# functions from surface_load.h

<br />


## [load_object_collision_model](#load_object_collision_model)

### Description
Loads the object's collision data into dynamic collision. You must run this every frame in your object's behavior loop for it to have collision

### Lua Example
`load_object_collision_model()`

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
`local StaticObjectCollisionValue = load_static_object_collision()`

### Parameters
- None

### Returns
[StaticObjectCollision](structs.md#StaticObjectCollision)

### C Prototype
`struct StaticObjectCollision *load_static_object_collision();`

[:arrow_up_small:](#)

<br />

## [toggle_static_object_collision](#toggle_static_object_collision)

### Description
Toggles a collection of static object surfaces

### Lua Example
`toggle_static_object_collision(col, tangible)`

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
`local SurfaceValue = get_static_object_surface(col, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| col | [StaticObjectCollision](structs.md#StaticObjectCollision) |
| index | `integer` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface *get_static_object_surface(struct StaticObjectCollision *col, u32 index);`

[:arrow_up_small:](#)

<br />

## [obj_get_surface_from_index](#obj_get_surface_from_index)

### Description
Gets a surface corresponding to `index` from the surface pool buffer

### Lua Example
`local SurfaceValue = obj_get_surface_from_index(o, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| index | `integer` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface *obj_get_surface_from_index(struct Object *o, u32 index);`

[:arrow_up_small:](#)

<br />

## [surface_has_force](#surface_has_force)

### Description
Checks if a surface has force

### Lua Example
`local booleanValue = surface_has_force(surfaceType)`

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
`local ObjectValue = sync_object_get_object(syncId)`

### Parameters
| Field | Type |
| ----- | ---- |
| syncId | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* sync_object_get_object(u32 syncId);`

[:arrow_up_small:](#)

<br />

## [sync_object_is_initialized](#sync_object_is_initialized)

### Description
Checks if a sync object is initialized using a `syncId`

### Lua Example
`local booleanValue = sync_object_is_initialized(syncId)`

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
`local booleanValue = sync_object_is_owned_locally(syncId)`

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

[< prev](functions-6.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | 7]

