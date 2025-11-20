## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-4.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | 5 | [6](functions-6.md) | [7](functions-7.md) | [next >](functions-6.md)]


---
# functions from math_util_vec3s.inl

<br />


## [vec3s_zero](#vec3s_zero)

### Description
Sets the components of the 3D short integer vector `v` to 0

### Lua Example
`local Vec3sValue = vec3s_zero(v)`

### Parameters
| Field | Type |
| ----- | ---- |
| v | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_zero(OUT Vec3s v);`

[:arrow_up_small:](#)

<br />

## [vec3s_copy](#vec3s_copy)

### Description
Copies the contents of a 3D short integer vector (`src`) into another 3D short integer vector (`dest`)

### Lua Example
`local Vec3sValue = vec3s_copy(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| src | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_copy(OUT Vec3s dest, Vec3s src);`

[:arrow_up_small:](#)

<br />

## [vec3s_set](#vec3s_set)

### Description
Sets the values of the 3D short integer vector `dest` to the given x, y, and z values

### Lua Example
`local Vec3sValue = vec3s_set(dest, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| x | `integer` |
| y | `integer` |
| z | `integer` |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_set(OUT Vec3s dest, s16 x, s16 y, s16 z);`

[:arrow_up_small:](#)

<br />

## [vec3s_add](#vec3s_add)

### Description
Adds the components of the 3D short integer vector `a` to `dest`

### Lua Example
`local Vec3sValue = vec3s_add(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_add(OUT Vec3s dest, Vec3s a);`

[:arrow_up_small:](#)

<br />

## [vec3s_sum](#vec3s_sum)

### Description
Adds the components of two 3D short integer vectors `a` and `b` and stores the result in `dest`

### Lua Example
`local Vec3sValue = vec3s_sum(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |
| b | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_sum(OUT Vec3s dest, Vec3s a, Vec3s b);`

[:arrow_up_small:](#)

<br />

## [vec3s_sub](#vec3s_sub)

### Description
Subtracts the components of the 3D short integer vector `a` from `dest`

### Lua Example
`local Vec3sValue = vec3s_sub(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_sub(OUT Vec3s dest, Vec3s a);`

[:arrow_up_small:](#)

<br />

## [vec3s_dif](#vec3s_dif)

### Description
Subtracts the components of the 3D short integer vector `b` from the components of `a` and stores the result in `dest`

### Lua Example
`local Vec3sValue = vec3s_dif(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |
| b | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_dif(OUT Vec3s dest, Vec3s a, Vec3s b);`

[:arrow_up_small:](#)

<br />

## [vec3s_mul](#vec3s_mul)

### Description
Multiplies each component of the 3D short integer vector `dest` by the scalar value `a`

### Lua Example
`local Vec3sValue = vec3s_mul(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | `number` |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_mul(OUT Vec3s dest, f32 a);`

[:arrow_up_small:](#)

<br />

## [vec3s_mult](#vec3s_mult)

### Description
Multiplies the components of the 3D short integer vector `dest` with the components of `a`

### Lua Example
`local Vec3sValue = vec3s_mult(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_mult(OUT Vec3s dest, Vec3s a);`

[:arrow_up_small:](#)

<br />

## [vec3s_prod](#vec3s_prod)

### Description
Multiplies the components of two 3D short integer vectors `a` and `b` and stores the result in `dest`

### Lua Example
`local Vec3sValue = vec3s_prod(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |
| b | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_prod(OUT Vec3s dest, Vec3s a, Vec3s b);`

[:arrow_up_small:](#)

<br />

## [vec3s_div](#vec3s_div)

### Description
Divides each component of the 3D short integer vector `dest` by the scalar value `a`

### Lua Example
`local Vec3sValue = vec3s_div(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | `number` |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_div(OUT Vec3s dest, f32 a);`

[:arrow_up_small:](#)

<br />

## [vec3s_length](#vec3s_length)

### Description
Calculates the length (magnitude) of the 3D short integer vector `a`

### Lua Example
`local numberValue = vec3s_length(a)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
- `number`

### C Prototype
`f32 vec3s_length(Vec3s a);`

[:arrow_up_small:](#)

<br />

## [vec3s_normalize](#vec3s_normalize)

### Description
Normalizes the 3D short integer vector `v` so that its length (magnitude) becomes 1, while retaining its direction

### Lua Example
`local Vec3sValue = vec3s_normalize(v)`

### Parameters
| Field | Type |
| ----- | ---- |
| v | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_normalize(OUT Vec3s v);`

[:arrow_up_small:](#)

<br />

## [vec3s_set_magnitude](#vec3s_set_magnitude)

### Description
Sets the length (magnitude) of 3D short integer vector `v`, while retaining its direction

### Lua Example
`local Vec3sValue = vec3s_set_magnitude(v, mag)`

### Parameters
| Field | Type |
| ----- | ---- |
| v | [Vec3s](structs.md#Vec3s) |
| mag | `number` |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_set_magnitude(OUT Vec3s v, f32 mag);`

[:arrow_up_small:](#)

<br />

## [vec3s_dot](#vec3s_dot)

### Description
Computes the dot product of the two 3D short integer vectors `a` and `b`

### Lua Example
`local numberValue = vec3s_dot(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | [Vec3s](structs.md#Vec3s) |
| b | [Vec3s](structs.md#Vec3s) |

### Returns
- `number`

### C Prototype
`f32 vec3s_dot(Vec3s a, Vec3s b);`

[:arrow_up_small:](#)

<br />

## [vec3s_cross](#vec3s_cross)

### Description
Computes the cross product of two 3D short integer vectors `a` and `b` and stores the result in `dest`

### Lua Example
`local Vec3sValue = vec3s_cross(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |
| b | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_cross(OUT Vec3s dest, Vec3s a, Vec3s b);`

[:arrow_up_small:](#)

<br />

## [vec3s_combine](#vec3s_combine)

### Description
Takes two 3D short integer vectors `vecA` and `vecB`, multiplies them by `sclA` and `sclB` respectively, adds the scaled vectors together and stores the result in `dest`

### Lua Example
`local Vec3sValue = vec3s_combine(dest, vecA, vecB, sclA, sclB)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| vecA | [Vec3s](structs.md#Vec3s) |
| vecB | [Vec3s](structs.md#Vec3s) |
| sclA | `number` |
| sclB | `number` |

### Returns
[Vec3s](structs.md#Vec3s)

### C Prototype
`Vec3sp vec3s_combine(OUT Vec3s dest, Vec3s vecA, Vec3s vecB, f32 sclA, f32 sclB);`

[:arrow_up_small:](#)

<br />

## [vec3s_dist](#vec3s_dist)

### Description
Calculates the distance between two 3D short integer vectors `v1` and `v2`

### Lua Example
`local numberValue = vec3s_dist(v1, v2)`

### Parameters
| Field | Type |
| ----- | ---- |
| v1 | [Vec3s](structs.md#Vec3s) |
| v2 | [Vec3s](structs.md#Vec3s) |

### Returns
- `number`

### C Prototype
`f32 vec3s_dist(Vec3s v1, Vec3s v2);`

[:arrow_up_small:](#)

<br />

## [vec3s_hdist](#vec3s_hdist)

### Description
Calculates the horizontal distance between two 3D short integer vectors `v1` and `v2`, as if their y component was 0

### Lua Example
`local numberValue = vec3s_hdist(v1, v2)`

### Parameters
| Field | Type |
| ----- | ---- |
| v1 | [Vec3s](structs.md#Vec3s) |
| v2 | [Vec3s](structs.md#Vec3s) |

### Returns
- `number`

### C Prototype
`f32 vec3s_hdist(Vec3s v1, Vec3s v2);`

[:arrow_up_small:](#)

<br />

## [vec3s_is_zero](#vec3s_is_zero)

### Description
Returns `true` if all components of the 3D short integer vector `v` are zero

### Lua Example
`local booleanValue = vec3s_is_zero(v)`

### Parameters
| Field | Type |
| ----- | ---- |
| v | [Vec3s](structs.md#Vec3s) |

### Returns
- `boolean`

### C Prototype
`bool vec3s_is_zero(Vec3s v);`

[:arrow_up_small:](#)

<br />

## [vec3s_to_vec3f](#vec3s_to_vec3f)

### Description
Converts a 3D short integer vector `a` into a 3D floating-point vector and stores the result in `dest`

### Lua Example
`local Vec3fValue = vec3s_to_vec3f(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3f](structs.md#Vec3f)

### C Prototype
`Vec3fp vec3s_to_vec3f(OUT Vec3f dest, Vec3s a);`

[:arrow_up_small:](#)

<br />

## [vec3s_to_vec3i](#vec3s_to_vec3i)

### Description
Converts a 3D short integer vector `a` into a 3D integer vector and stores the result in `dest`

### Lua Example
`local Vec3iValue = vec3s_to_vec3i(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3i](structs.md#Vec3i) |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
[Vec3i](structs.md#Vec3i)

### C Prototype
`Vec3ip vec3s_to_vec3i(OUT Vec3i dest, Vec3s a);`

[:arrow_up_small:](#)

<br />

---
# functions from misc.h

<br />


## [smooth_step](#smooth_step)

### Description
Smoothly steps between `edge0` and `edge1` with `x` as delta

### Lua Example
`local numberValue = smooth_step(edge0, edge1, x)`

### Parameters
| Field | Type |
| ----- | ---- |
| edge0 | `number` |
| edge1 | `number` |
| x | `number` |

### Returns
- `number`

### C Prototype
`float smooth_step(float edge0, float edge1, float x);`

[:arrow_up_small:](#)

<br />

## [update_all_mario_stars](#update_all_mario_stars)

### Description
Updates every Mario state's star count with the save file total star count

### Lua Example
`update_all_mario_stars()`

### Parameters
- None

### Returns
- None

### C Prototype
`void update_all_mario_stars(void);`

[:arrow_up_small:](#)

<br />

## [clock_elapsed](#clock_elapsed)

### Description
Gets the current clock elapsed time

### Lua Example
`local numberValue = clock_elapsed()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 clock_elapsed(void);`

[:arrow_up_small:](#)

<br />

## [clock_elapsed_f64](#clock_elapsed_f64)

### Description
Gets the current clock elapsed time with double precision

### Lua Example
`local numberValue = clock_elapsed_f64()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f64 clock_elapsed_f64(void);`

[:arrow_up_small:](#)

<br />

## [clock_elapsed_ticks](#clock_elapsed_ticks)

### Description
Gets the current clock elapsed time in frames

### Lua Example
`local integerValue = clock_elapsed_ticks()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 clock_elapsed_ticks(void);`

[:arrow_up_small:](#)

<br />

## [clock_is_date](#clock_is_date)

### Description
Checks whether it is the day given

### Lua Example
`local booleanValue = clock_is_date(month, day)`

### Parameters
| Field | Type |
| ----- | ---- |
| month | `integer` |
| day | `integer` |

### Returns
- `boolean`

### C Prototype
`bool clock_is_date(u8 month, u8 day);`

[:arrow_up_small:](#)

<br />

## [delta_interpolate_f32](#delta_interpolate_f32)

### Description
Linearly interpolates between `a` and `b` with `delta`

### Lua Example
`local numberValue = delta_interpolate_f32(a, b, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `number` |
| b | `number` |
| delta | `number` |

### Returns
- `number`

### C Prototype
`f32 delta_interpolate_f32(f32 a, f32 b, f32 delta);`

[:arrow_up_small:](#)

<br />

## [delta_interpolate_s32](#delta_interpolate_s32)

### Description
Linearly interpolates between `a` and `b` with `delta`

### Lua Example
`local integerValue = delta_interpolate_s32(a, b, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |
| b | `integer` |
| delta | `number` |

### Returns
- `integer`

### C Prototype
`s32 delta_interpolate_s32(s32 a, s32 b, f32 delta);`

[:arrow_up_small:](#)

<br />

## [delta_interpolate_vec3f](#delta_interpolate_vec3f)

### Description
Linearly interpolates `res` between `a` and `b` with `delta`

### Lua Example
`delta_interpolate_vec3f(res, a, b, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| res | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |
| delta | `number` |

### Returns
- None

### C Prototype
`void delta_interpolate_vec3f(OUT Vec3f res, Vec3f a, Vec3f b, f32 delta);`

[:arrow_up_small:](#)

<br />

## [delta_interpolate_vec3s](#delta_interpolate_vec3s)

### Description
Linearly interpolates `res` between `a` and `b` with `delta`

### Lua Example
`delta_interpolate_vec3s(res, a, b, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| res | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |
| b | [Vec3s](structs.md#Vec3s) |
| delta | `number` |

### Returns
- None

### C Prototype
`void delta_interpolate_vec3s(OUT Vec3s res, Vec3s a, Vec3s b, f32 delta);`

[:arrow_up_small:](#)

<br />

---
# functions from mod_fs.h

<br />


## [mod_fs_exists](#mod_fs_exists)

### Description
Checks the existence of a modfs at path `modPath` or for the active mod if not provided. Checking for the existence of a private modfs will return false, even if it exists

### Lua Example
`local booleanValue = mod_fs_exists(modPath)`

### Parameters
| Field | Type |
| ----- | ---- |
| modPath | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_exists(OPTIONAL const char *modPath);`

[:arrow_up_small:](#)

<br />

## [mod_fs_get](#mod_fs_get)

### Description
Gets the modfs object at path `modPath` or the active mod one if not provided. This function will return nil for a private modfs, even if it exists

### Lua Example
`local ModFsValue = mod_fs_get(modPath)`

### Parameters
| Field | Type |
| ----- | ---- |
| modPath | `string` |

### Returns
[ModFs](structs.md#ModFs)

### C Prototype
`struct ModFs *mod_fs_get(OPTIONAL const char *modPath);`

[:arrow_up_small:](#)

<br />

## [mod_fs_reload](#mod_fs_reload)

### Description
Reloads the modfs object at path `modPath`. This function will return nil for a private modfs, even if it exists

### Lua Example
`local ModFsValue = mod_fs_reload(modPath)`

### Parameters
| Field | Type |
| ----- | ---- |
| modPath | `string` |

### Returns
[ModFs](structs.md#ModFs)

### C Prototype
`struct ModFs *mod_fs_reload(OPTIONAL const char *modPath);`

[:arrow_up_small:](#)

<br />

## [mod_fs_create](#mod_fs_create)

### Description
Creates a modfs object for the active mod if it doesn't exist. Returns the modfs object on success

### Lua Example
`local ModFsValue = mod_fs_create()`

### Parameters
- None

### Returns
[ModFs](structs.md#ModFs)

### C Prototype
`struct ModFs *mod_fs_create();`

[:arrow_up_small:](#)

<br />

## [mod_fs_get_filename](#mod_fs_get_filename)

### Description
Gets the filename at position `index` of the provided `modFs`

### Lua Example
`local stringValue = mod_fs_get_filename(modFs, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |
| index | `integer` |

### Returns
- `string`

### C Prototype
`const char *mod_fs_get_filename(struct ModFs *modFs, u16 index);`

[:arrow_up_small:](#)

<br />

## [mod_fs_get_file](#mod_fs_get_file)

### Description
Gets the file object at path `filepath` of the provided `modFs`. This function will return nil for a private modfs file, even if it exists

### Lua Example
`local ModFsFileValue = mod_fs_get_file(modFs, filepath)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |
| filepath | `string` |

### Returns
[ModFsFile](structs.md#ModFsFile)

### C Prototype
`struct ModFsFile *mod_fs_get_file(struct ModFs *modFs, const char *filepath);`

[:arrow_up_small:](#)

<br />

## [mod_fs_create_file](#mod_fs_create_file)

### Description
Creates a new file at path `filepath` for the provided `modFs`. Set `text` to true to treat the file as a pure text file, not a binary file. Returns the created file on success

### Lua Example
`local ModFsFileValue = mod_fs_create_file(modFs, filepath, text)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |
| filepath | `string` |
| text | `boolean` |

### Returns
[ModFsFile](structs.md#ModFsFile)

### C Prototype
`struct ModFsFile *mod_fs_create_file(struct ModFs *modFs, const char *filepath, bool text);`

[:arrow_up_small:](#)

<br />

## [mod_fs_move_file](#mod_fs_move_file)

### Description
Moves the file at path `oldpath` to `newpath` of the provided `modFs`. Set `overwriteExisting` to true to overwrite the file at path `newpath` if it exists. Returns true on success

### Lua Example
`local booleanValue = mod_fs_move_file(modFs, oldpath, newpath, overwriteExisting)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |
| oldpath | `string` |
| newpath | `string` |
| overwriteExisting | `boolean` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_move_file(struct ModFs *modFs, const char *oldpath, const char *newpath, bool overwriteExisting);`

[:arrow_up_small:](#)

<br />

## [mod_fs_copy_file](#mod_fs_copy_file)

### Description
Copies the file at path `srcpath` to `dstpath` of the provided `modFs`. Set `overwriteExisting` to true to overwrite the file at path `dstpath` if it exists. Returns true on success

### Lua Example
`local booleanValue = mod_fs_copy_file(modFs, srcpath, dstpath, overwriteExisting)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |
| srcpath | `string` |
| dstpath | `string` |
| overwriteExisting | `boolean` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_copy_file(struct ModFs *modFs, const char *srcpath, const char *dstpath, bool overwriteExisting);`

[:arrow_up_small:](#)

<br />

## [mod_fs_delete_file](#mod_fs_delete_file)

### Description
Deletes the file at path `filepath` of the provided `modFs`. Returns true on success

### Lua Example
`local booleanValue = mod_fs_delete_file(modFs, filepath)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |
| filepath | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_delete_file(struct ModFs *modFs, const char *filepath);`

[:arrow_up_small:](#)

<br />

## [mod_fs_clear](#mod_fs_clear)

### Description
Deletes all files of the provided `modFs`. Returns true on success

### Lua Example
`local booleanValue = mod_fs_clear(modFs)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_clear(struct ModFs *modFs);`

[:arrow_up_small:](#)

<br />

## [mod_fs_save](#mod_fs_save)

### Description
Saves the provided `modFs` to persistent storage. Returns true on success

### Lua Example
`local booleanValue = mod_fs_save(modFs)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_save(struct ModFs *modFs);`

[:arrow_up_small:](#)

<br />

## [mod_fs_delete](#mod_fs_delete)

### Description
Removes the provided `modFs` from persistent storage and deletes its object. Returns true on success

### Lua Example
`local booleanValue = mod_fs_delete(modFs)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_delete(struct ModFs *modFs);`

[:arrow_up_small:](#)

<br />

## [mod_fs_set_public](#mod_fs_set_public)

### Description
Marks the provided `modFs` as public (i.e. readable by other mods). Returns true on success

### Lua Example
`local booleanValue = mod_fs_set_public(modFs, pub)`

### Parameters
| Field | Type |
| ----- | ---- |
| modFs | [ModFs](structs.md#ModFs) |
| pub | `boolean` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_set_public(struct ModFs *modFs, bool pub);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_read_bool](#mod_fs_file_read_bool)

### Description
Reads a boolean from a binary modfs `file`

### Lua Example
`local booleanValue = mod_fs_file_read_bool(file)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_read_bool(struct ModFsFile *file);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_read_integer](#mod_fs_file_read_integer)

### Description
Reads an integer from a binary modfs `file`. `intType` must be one of the `INT_TYPE_*` constants

### Lua Example
`local integerValue = mod_fs_file_read_integer(file, intType)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| intType | [enum ModFsFileIntType](constants.md#enum-ModFsFileIntType) |

### Returns
- `integer`

### C Prototype
`lua_Integer mod_fs_file_read_integer(struct ModFsFile *file, enum ModFsFileIntType intType);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_read_number](#mod_fs_file_read_number)

### Description
Reads an floating-point number from a binary modfs `file`. `floatType` must be one of the `FLOAT_TYPE_*` constants

### Lua Example
`local numberValue = mod_fs_file_read_number(file, floatType)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| floatType | [enum ModFsFileFloatType](constants.md#enum-ModFsFileFloatType) |

### Returns
- `number`

### C Prototype
`lua_Number mod_fs_file_read_number(struct ModFsFile *file, enum ModFsFileFloatType floatType);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_read_bytes](#mod_fs_file_read_bytes)

### Description
Reads a bytestring of `length` bytes from a binary modfs `file`

### Lua Example
`local stringValue = mod_fs_file_read_bytes(file, length)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| length | `integer` |

### Returns
- `string`

### C Prototype
`ByteString mod_fs_file_read_bytes(struct ModFsFile *file, u32 length);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_read_string](#mod_fs_file_read_string)

### Description
Reads a string from a binary modfs `file`, or read the whole content of a text modfs `file`

### Lua Example
`local stringValue = mod_fs_file_read_string(file)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |

### Returns
- `string`

### C Prototype
`const char *mod_fs_file_read_string(struct ModFsFile *file);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_read_line](#mod_fs_file_read_line)

### Description
Reads a line from a text modfs `file`

### Lua Example
`local stringValue = mod_fs_file_read_line(file)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |

### Returns
- `string`

### C Prototype
`const char *mod_fs_file_read_line(struct ModFsFile *file);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_write_bool](#mod_fs_file_write_bool)

### Description
Writes a boolean to a binary modfs `file`. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_write_bool(file, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| value | `boolean` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_write_bool(struct ModFsFile *file, bool value);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_write_integer](#mod_fs_file_write_integer)

### Description
Writes an integer to a binary modfs `file`. `intType` must be one of the `INT_TYPE_*` constants. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_write_integer(file, value, intType)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| value | `integer` |
| intType | [enum ModFsFileIntType](constants.md#enum-ModFsFileIntType) |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_write_integer(struct ModFsFile *file, lua_Integer value, enum ModFsFileIntType intType);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_write_number](#mod_fs_file_write_number)

### Description
Writes an floating-point number to a binary modfs `file`. `floatType` must be one of the `FLOAT_TYPE_*` constants. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_write_number(file, value, floatType)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| value | `number` |
| floatType | [enum ModFsFileFloatType](constants.md#enum-ModFsFileFloatType) |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_write_number(struct ModFsFile *file, lua_Number value, enum ModFsFileFloatType floatType);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_write_bytes](#mod_fs_file_write_bytes)

### Description
Writes a bytestring to a modfs `file`. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_write_bytes(file, bytestring)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| bytestring | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_write_bytes(struct ModFsFile *file, ByteString bytestring);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_write_string](#mod_fs_file_write_string)

### Description
Writes a string to a modfs `file`. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_write_string(file, str)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| str | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_write_string(struct ModFsFile *file, const char *str);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_write_line](#mod_fs_file_write_line)

### Description
Writes a line to a text modfs `file`. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_write_line(file, str)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| str | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_write_line(struct ModFsFile *file, const char *str);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_seek](#mod_fs_file_seek)

### Description
Sets the current position of a modfs `file`. If `origin` is `FILE_SEEK_SET`, file position is set to `offset`. If `origin` is `FILE_SEEK_CUR`, `offset` is added to file current position. If `origin` is `FILE_SEEK_END`, file position is set to `end of file + offset`. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_seek(file, offset, origin)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| offset | `integer` |
| origin | [enum ModFsFileSeek](constants.md#enum-ModFsFileSeek) |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_seek(struct ModFsFile *file, s32 offset, enum ModFsFileSeek origin);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_rewind](#mod_fs_file_rewind)

### Description
Sets the current position of a modfs `file` to its beginning. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_rewind(file)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_rewind(struct ModFsFile *file);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_is_eof](#mod_fs_file_is_eof)

### Description
Returns true if the provided modfs `file` has reached its end of file

### Lua Example
`local booleanValue = mod_fs_file_is_eof(file)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_is_eof(struct ModFsFile *file);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_fill](#mod_fs_file_fill)

### Description
Fills a modfs `file` with `byte` repeated `length` times. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_fill(file, byte, length)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| byte | `integer` |
| length | `integer` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_fill(struct ModFsFile *file, u8 byte, u32 length);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_erase](#mod_fs_file_erase)

### Description
Erases `length` bytes or characters from a modfs `file`. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_erase(file, length)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| length | `integer` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_erase(struct ModFsFile *file, u32 length);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_set_text_mode](#mod_fs_file_set_text_mode)

### Description
Marks the provided modfs `file` as text. Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_set_text_mode(file, text)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| text | `boolean` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_set_text_mode(struct ModFsFile *file, bool text);`

[:arrow_up_small:](#)

<br />

## [mod_fs_file_set_public](#mod_fs_file_set_public)

### Description
Marks the provided modfs `file` as public (i.e. readable by other mods). Returns true on success

### Lua Example
`local booleanValue = mod_fs_file_set_public(file, pub)`

### Parameters
| Field | Type |
| ----- | ---- |
| file | [ModFsFile](structs.md#ModFsFile) |
| pub | `boolean` |

### Returns
- `boolean`

### C Prototype
`bool mod_fs_file_set_public(struct ModFsFile *file, bool pub);`

[:arrow_up_small:](#)

<br />

## [mod_fs_hide_errors](#mod_fs_hide_errors)

### Description
Hides script errors raised by `mod_fs` functions. Errors messages are still generated and can be retrieved with `mod_fs_get_last_error()`

### Lua Example
`mod_fs_hide_errors(hide)`

### Parameters
| Field | Type |
| ----- | ---- |
| hide | `boolean` |

### Returns
- None

### C Prototype
`void mod_fs_hide_errors(bool hide);`

[:arrow_up_small:](#)

<br />

## [mod_fs_get_last_error](#mod_fs_get_last_error)

### Description
Returns the last error message generated by `mod_fs` functions or nil if no error occurred

### Lua Example
`local stringValue = mod_fs_get_last_error()`

### Parameters
- None

### Returns
- `string`

### C Prototype
`const char *mod_fs_get_last_error();`

[:arrow_up_small:](#)

<br />

---
# functions from mod_storage.h

<br />


## [mod_storage_save](#mod_storage_save)

### Description
Saves a `key` corresponding to a string `value` to mod storage

### Lua Example
`local booleanValue = mod_storage_save(key, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |
| value | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_save(const char* key, const char* value);`

[:arrow_up_small:](#)

<br />

## [mod_storage_save_number](#mod_storage_save_number)

### Description
Saves a `key` corresponding to a float `value` to mod storage

### Lua Example
`local booleanValue = mod_storage_save_number(key, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |
| value | `number` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_save_number(const char* key, f32 value);`

[:arrow_up_small:](#)

<br />

## [mod_storage_save_bool](#mod_storage_save_bool)

### Description
Saves a `key` corresponding to a bool `value` to mod storage

### Lua Example
`local booleanValue = mod_storage_save_bool(key, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |
| value | `boolean` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_save_bool(const char* key, bool value);`

[:arrow_up_small:](#)

<br />

## [mod_storage_load](#mod_storage_load)

### Description
Loads a string `value` from a `key` in mod storage

### Lua Example
`local stringValue = mod_storage_load(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `string`

### C Prototype
`const char *mod_storage_load(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_load_number](#mod_storage_load_number)

### Description
Loads a float `value` from a `key` in mod storage

### Lua Example
`local numberValue = mod_storage_load_number(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `number`

### C Prototype
`f32 mod_storage_load_number(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_load_bool](#mod_storage_load_bool)

### Description
Loads a bool `value` from a `key` in mod storage

### Lua Example
`local booleanValue = mod_storage_load_bool(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_load_bool(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_load_all](#mod_storage_load_all)

### Description
Loads all keys and values in mod storage as strings and returns them as a table

### Lua Example
`local tableValue = mod_storage_load_all()`

### Parameters
- None

### Returns
- `table`

### C Prototype
`LuaTable mod_storage_load_all(void);`

[:arrow_up_small:](#)

<br />

## [mod_storage_exists](#mod_storage_exists)

### Description
Checks if a `key` is in mod storage

### Lua Example
`local booleanValue = mod_storage_exists(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_exists(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_remove](#mod_storage_remove)

### Description
Removes a `key` from mod storage

### Lua Example
`local booleanValue = mod_storage_remove(key)`

### Parameters
| Field | Type |
| ----- | ---- |
| key | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_storage_remove(const char* key);`

[:arrow_up_small:](#)

<br />

## [mod_storage_clear](#mod_storage_clear)

### Description
Clears the mod's data from mod storage

### Lua Example
`local booleanValue = mod_storage_clear()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool mod_storage_clear(void);`

[:arrow_up_small:](#)

<br />

---
# functions from network_player.h

<br />


## [network_player_connected_count](#network_player_connected_count)

### Description
Gets the amount of players connected

### Lua Example
`local integerValue = network_player_connected_count()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 network_player_connected_count(void);`

[:arrow_up_small:](#)

<br />

## [network_player_set_description](#network_player_set_description)

### Description
Sets the description field of `np`

### Lua Example
`network_player_set_description(np, description, r, g, b, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |
| description | `string` |
| r | `integer` |
| g | `integer` |
| b | `integer` |
| a | `integer` |

### Returns
- None

### C Prototype
`void network_player_set_description(struct NetworkPlayer* np, const char* description, u8 r, u8 g, u8 b, u8 a);`

[:arrow_up_small:](#)

<br />

## [network_player_set_override_location](#network_player_set_override_location)

### Description
Overrides the location of `np`

### Lua Example
`network_player_set_override_location(np, location)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |
| location | `string` |

### Returns
- None

### C Prototype
`void network_player_set_override_location(struct NetworkPlayer *np, const char *location);`

[:arrow_up_small:](#)

<br />

## [network_player_from_global_index](#network_player_from_global_index)

### Description
Gets a network player from `globalIndex`

### Lua Example
`local NetworkPlayerValue = network_player_from_global_index(globalIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| globalIndex | `integer` |

### Returns
[NetworkPlayer](structs.md#NetworkPlayer)

### C Prototype
`struct NetworkPlayer* network_player_from_global_index(u8 globalIndex);`

[:arrow_up_small:](#)

<br />

## [get_network_player_from_level](#get_network_player_from_level)

### Description
Gets the first network player whose information matches `courseNum`, `actNum`, and `levelNum`

### Lua Example
`local NetworkPlayerValue = get_network_player_from_level(courseNum, actNum, levelNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |
| levelNum | `integer` |

### Returns
[NetworkPlayer](structs.md#NetworkPlayer)

### C Prototype
`struct NetworkPlayer* get_network_player_from_level(s16 courseNum, s16 actNum, s16 levelNum);`

[:arrow_up_small:](#)

<br />

## [get_network_player_from_area](#get_network_player_from_area)

### Description
Gets the first network player whose information matches `courseNum`, `actNum`, `levelNum`, and `areaIndex`

### Lua Example
`local NetworkPlayerValue = get_network_player_from_area(courseNum, actNum, levelNum, areaIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |
| levelNum | `integer` |
| areaIndex | `integer` |

### Returns
[NetworkPlayer](structs.md#NetworkPlayer)

### C Prototype
`struct NetworkPlayer* get_network_player_from_area(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex);`

[:arrow_up_small:](#)

<br />

## [get_network_player_smallest_global](#get_network_player_smallest_global)

### Description
Gets the active network player with the smallest global index. Useful for assigning one player to "own" some kind of functionality or object

### Lua Example
`local NetworkPlayerValue = get_network_player_smallest_global()`

### Parameters
- None

### Returns
[NetworkPlayer](structs.md#NetworkPlayer)

### C Prototype
`struct NetworkPlayer* get_network_player_smallest_global(void);`

[:arrow_up_small:](#)

<br />

## [network_player_set_override_palette_color](#network_player_set_override_palette_color)

### Description
Sets the `part in `np`'s override color palette`

### Lua Example
`network_player_set_override_palette_color(np, part, color)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |
| part | [enum PlayerPart](constants.md#enum-PlayerPart) |
| color | [Color](structs.md#Color) |

### Returns
- None

### C Prototype
`void network_player_set_override_palette_color(struct NetworkPlayer *np, enum PlayerPart part, Color color);`

[:arrow_up_small:](#)

<br />

## [network_player_reset_override_palette](#network_player_reset_override_palette)

### Description
Resets `np`'s override color palette

### Lua Example
`network_player_reset_override_palette(np)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |

### Returns
- None

### C Prototype
`void network_player_reset_override_palette(struct NetworkPlayer *np);`

[:arrow_up_small:](#)

<br />

## [network_player_is_override_palette_same](#network_player_is_override_palette_same)

### Description
Checks if `np`'s override color palette is identical to the regular color palette

### Lua Example
`local booleanValue = network_player_is_override_palette_same(np)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |

### Returns
- `boolean`

### C Prototype
`bool network_player_is_override_palette_same(struct NetworkPlayer *np);`

[:arrow_up_small:](#)

<br />

---
# functions from network_utils.h

<br />


## [network_global_index_from_local](#network_global_index_from_local)

### Description
Gets a player's global index from their local index

### Lua Example
`local integerValue = network_global_index_from_local(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u8 network_global_index_from_local(u8 localIndex);`

[:arrow_up_small:](#)

<br />

## [network_local_index_from_global](#network_local_index_from_global)

### Description
Gets a player's local index from their global index

### Lua Example
`local integerValue = network_local_index_from_global(globalIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| globalIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u8 network_local_index_from_global(u8 globalIndex);`

[:arrow_up_small:](#)

<br />

## [network_is_server](#network_is_server)

### Description
Checks if you are hosting the current lobby, this value doesn't change

### Lua Example
`local booleanValue = network_is_server()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool network_is_server(void);`

[:arrow_up_small:](#)

<br />

## [network_is_moderator](#network_is_moderator)

### Description
Checks if you are a moderator in the current lobby

### Lua Example
`local booleanValue = network_is_moderator()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool network_is_moderator(void);`

[:arrow_up_small:](#)

<br />

## [network_get_player_text_color_string](#network_get_player_text_color_string)

### Description
Gets the DJUI hex color code string for the player corresponding to `localIndex`'s cap color

### Lua Example
`local stringValue = network_get_player_text_color_string(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `string`

### C Prototype
`const char* network_get_player_text_color_string(u8 localIndex);`

[:arrow_up_small:](#)

<br />

## [network_check_singleplayer_pause](#network_check_singleplayer_pause)

### Description
Checks if the game can currently be paused in singleplayer

### Lua Example
`local booleanValue = network_check_singleplayer_pause()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool network_check_singleplayer_pause(void);`

[:arrow_up_small:](#)

<br />

## [network_discord_id_from_local_index](#network_discord_id_from_local_index)

### Description
Gets a Discord ID corresponding to the network player with `localIndex`

### Lua Example
`local stringValue = network_discord_id_from_local_index(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `string`

### C Prototype
`const char* network_discord_id_from_local_index(u8 localIndex);`

[:arrow_up_small:](#)

<br />

---
# functions from obj_behaviors.c

<br />


## [set_yoshi_as_not_dead](#set_yoshi_as_not_dead)

### Description
Resets Yoshi as being alive

### Lua Example
`set_yoshi_as_not_dead()`

### Parameters
- None

### Returns
- None

### C Prototype
`void set_yoshi_as_not_dead(void);`

[:arrow_up_small:](#)

<br />

## [absf_2](#absf_2)

### Description
An absolute value (always positive) function.

### Lua Example
`local numberValue = absf_2(f)`

### Parameters
| Field | Type |
| ----- | ---- |
| f | `number` |

### Returns
- `number`

### C Prototype
`f32 absf_2(f32 f);`

[:arrow_up_small:](#)

<br />

## [obj_find_wall](#obj_find_wall)

### Description
Finds any wall collisions, applies them, and turns away from the surface.

### Lua Example
`local integerValue = obj_find_wall(objNewX, objY, objNewZ, objVelX, objVelZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| objNewX | `number` |
| objY | `number` |
| objNewZ | `number` |
| objVelX | `number` |
| objVelZ | `number` |

### Returns
- `integer`

### C Prototype
`s8 obj_find_wall(f32 objNewX, f32 objY, f32 objNewZ, f32 objVelX, f32 objVelZ);`

[:arrow_up_small:](#)

<br />

## [turn_obj_away_from_steep_floor](#turn_obj_away_from_steep_floor)

### Description
Turns an object away from steep floors, similarly to walls.

### Lua Example
`local integerValue = turn_obj_away_from_steep_floor(objFloor, floorY, objVelX, objVelZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| objFloor | [Surface](structs.md#Surface) |
| floorY | `number` |
| objVelX | `number` |
| objVelZ | `number` |

### Returns
- `integer`

### C Prototype
`s8 turn_obj_away_from_steep_floor(struct Surface *objFloor, f32 floorY, f32 objVelX, f32 objVelZ);`

[:arrow_up_small:](#)

<br />

## [obj_orient_graph](#obj_orient_graph)

### Description
Orients an object with the given normals, typically the surface under the object.

### Lua Example
`obj_orient_graph(obj, normalX, normalY, normalZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| normalX | `number` |
| normalY | `number` |
| normalZ | `number` |

### Returns
- None

### C Prototype
`void obj_orient_graph(struct Object *obj, f32 normalX, f32 normalY, f32 normalZ);`

[:arrow_up_small:](#)

<br />

## [calc_obj_friction](#calc_obj_friction)

### Description
Orients an object with the given normals, typically the surface under the object.

### Lua Example
`calc_obj_friction(objFriction, floor_nY)`

### Parameters
| Field | Type |
| ----- | ---- |
| objFriction | `Pointer` <`number`> |
| floor_nY | `number` |

### Returns
- None

### C Prototype
`void calc_obj_friction(f32 *objFriction, f32 floor_nY);`

[:arrow_up_small:](#)

<br />

## [calc_new_obj_vel_and_pos_y](#calc_new_obj_vel_and_pos_y)

### Description
Updates an objects speed for gravity and updates Y position.

### Lua Example
`calc_new_obj_vel_and_pos_y(objFloor, objFloorY, objVelX, objVelZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| objFloor | [Surface](structs.md#Surface) |
| objFloorY | `number` |
| objVelX | `number` |
| objVelZ | `number` |

### Returns
- None

### C Prototype
`void calc_new_obj_vel_and_pos_y(struct Surface *objFloor, f32 objFloorY, f32 objVelX, f32 objVelZ);`

[:arrow_up_small:](#)

<br />

## [calc_new_obj_vel_and_pos_y_underwater](#calc_new_obj_vel_and_pos_y_underwater)

### Description
Adjusts the current object's veloicty and y position for being underwater

### Lua Example
`calc_new_obj_vel_and_pos_y_underwater(objFloor, floorY, objVelX, objVelZ, waterY)`

### Parameters
| Field | Type |
| ----- | ---- |
| objFloor | [Surface](structs.md#Surface) |
| floorY | `number` |
| objVelX | `number` |
| objVelZ | `number` |
| waterY | `number` |

### Returns
- None

### C Prototype
`void calc_new_obj_vel_and_pos_y_underwater(struct Surface *objFloor, f32 floorY, f32 objVelX, f32 objVelZ, f32 waterY);`

[:arrow_up_small:](#)

<br />

## [obj_update_pos_vel_xz](#obj_update_pos_vel_xz)

### Description
Updates an objects position from oForwardVel and oMoveAngleYaw.

### Lua Example
`obj_update_pos_vel_xz()`

### Parameters
- None

### Returns
- None

### C Prototype
`void obj_update_pos_vel_xz(void);`

[:arrow_up_small:](#)

<br />

## [obj_splash](#obj_splash)

### Description
Generates splashes if at surface of water, entering water, or bubbles if underwater

### Lua Example
`obj_splash(waterY, objY)`

### Parameters
| Field | Type |
| ----- | ---- |
| waterY | `integer` |
| objY | `integer` |

### Returns
- None

### C Prototype
`void obj_splash(s32 waterY, s32 objY);`

[:arrow_up_small:](#)

<br />

## [object_step](#object_step)

### Description
Generic object move function. Handles walls, water, floors, and gravity. Returns flags for certain interactions

### Lua Example
`local integerValue = object_step()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 object_step(void);`

[:arrow_up_small:](#)

<br />

## [object_step_without_floor_orient](#object_step_without_floor_orient)

### Description
Takes an object step but does not orient with the object's floor. Used for boulders, falling pillars, and the rolling snowman body

### Lua Example
`local integerValue = object_step_without_floor_orient()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 object_step_without_floor_orient(void);`

[:arrow_up_small:](#)

<br />

## [obj_move_xyz_using_fvel_and_yaw](#obj_move_xyz_using_fvel_and_yaw)

### Description
Don't use this function outside of of a context where the current object and `obj` are the same. Moves `obj` based on a seemingly random mix of using either the current obj or `obj`'s fields

### Lua Example
`obj_move_xyz_using_fvel_and_yaw(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_move_xyz_using_fvel_and_yaw(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [is_point_within_radius_of_mario](#is_point_within_radius_of_mario)

### Description
Checks if a point is within distance from any active Mario visible to enemies' graphical position

### Lua Example
`local integerValue = is_point_within_radius_of_mario(x, y, z, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |
| dist | `integer` |

### Returns
- `integer`

### C Prototype
`s8 is_point_within_radius_of_mario(f32 x, f32 y, f32 z, s32 dist);`

[:arrow_up_small:](#)

<br />

## [is_point_within_radius_of_any_player](#is_point_within_radius_of_any_player)

### Description
Checks if a point is within distance from any active Mario's graphical position

### Lua Example
`local integerValue = is_point_within_radius_of_any_player(x, y, z, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |
| dist | `integer` |

### Returns
- `integer`

### C Prototype
`s8 is_point_within_radius_of_any_player(f32 x, f32 y, f32 z, s32 dist);`

[:arrow_up_small:](#)

<br />

## [is_player_active](#is_player_active)

### Description
Checks if `m` is in the current course/act/level/area and isn't bubbled

### Lua Example
`local integerValue = is_player_active(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u8 is_player_active(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [is_other_player_active](#is_other_player_active)

### Description
Checks if any player besides the local player is in the current course/act/level/area

### Lua Example
`local integerValue = is_other_player_active()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 is_other_player_active(void);`

[:arrow_up_small:](#)

<br />

## [is_player_in_local_area](#is_player_in_local_area)

### Description
Checks if `m` is in the current course/act/level/area

### Lua Example
`local integerValue = is_player_in_local_area(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`u8 is_player_in_local_area(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [nearest_mario_state_to_object](#nearest_mario_state_to_object)

### Description
Gets the nearest active Mario who isn't bubbled to `obj`

### Lua Example
`local MarioStateValue = nearest_mario_state_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[MarioState](structs.md#MarioState)

### C Prototype
`struct MarioState* nearest_mario_state_to_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [nearest_possible_mario_state_to_object](#nearest_possible_mario_state_to_object)

### Description
Gets the nearest possible Mario to `obj` despite anything like bubbled state or enemy visibility

### Lua Example
`local MarioStateValue = nearest_possible_mario_state_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[MarioState](structs.md#MarioState)

### C Prototype
`struct MarioState* nearest_possible_mario_state_to_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [nearest_player_to_object](#nearest_player_to_object)

### Description
Gets the nearest player (Mario Object) to `obj`

### Lua Example
`local ObjectValue = nearest_player_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* nearest_player_to_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [nearest_interacting_mario_state_to_object](#nearest_interacting_mario_state_to_object)

### Description
Gets the nearest interacting Mario to `obj`

### Lua Example
`local MarioStateValue = nearest_interacting_mario_state_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[MarioState](structs.md#MarioState)

### C Prototype
`struct MarioState *nearest_interacting_mario_state_to_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [nearest_interacting_player_to_object](#nearest_interacting_player_to_object)

### Description
Gets the nearest interacting player (Mario Object) to `obj`

### Lua Example
`local ObjectValue = nearest_interacting_player_to_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *nearest_interacting_player_to_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [is_nearest_mario_state_to_object](#is_nearest_mario_state_to_object)

### Description
Checks if `m` is the nearest Mario to `obj`

### Lua Example
`local integerValue = is_nearest_mario_state_to_object(m, obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| obj | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u8 is_nearest_mario_state_to_object(struct MarioState *m, struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [is_nearest_player_to_object](#is_nearest_player_to_object)

### Description
Checks if `m` is the nearest player (Mario Object) to `obj`

### Lua Example
`local integerValue = is_nearest_player_to_object(m, obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [Object](structs.md#Object) |
| obj | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`u8 is_nearest_player_to_object(struct Object *m, struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [is_point_close_to_object](#is_point_close_to_object)

### Description
Checks if a point is within `dist` of `obj`

### Lua Example
`local integerValue = is_point_close_to_object(obj, x, y, z, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| x | `number` |
| y | `number` |
| z | `number` |
| dist | `integer` |

### Returns
- `integer`

### C Prototype
`s8 is_point_close_to_object(struct Object *obj, f32 x, f32 y, f32 z, s32 dist);`

[:arrow_up_small:](#)

<br />

## [set_object_visibility](#set_object_visibility)

### Description
Sets an object as visible if within a certain distance of Mario's graphical position

### Lua Example
`set_object_visibility(obj, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| dist | `integer` |

### Returns
- None

### C Prototype
`void set_object_visibility(struct Object *obj, s32 dist);`

[:arrow_up_small:](#)

<br />

## [obj_return_home_if_safe](#obj_return_home_if_safe)

### Description
Turns an object towards home if Mario is not near to it

### Lua Example
`local integerValue = obj_return_home_if_safe(obj, homeX, y, homeZ, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| homeX | `number` |
| y | `number` |
| homeZ | `number` |
| dist | `integer` |

### Returns
- `integer`

### C Prototype
`s8 obj_return_home_if_safe(struct Object *obj, f32 homeX, f32 y, f32 homeZ, s32 dist);`

[:arrow_up_small:](#)

<br />

## [obj_return_and_displace_home](#obj_return_and_displace_home)

### Description
Randomly displaces an objects home if RNG says to, and turns the object towards its home

### Lua Example
`obj_return_and_displace_home(obj, homeX, homeY, homeZ, baseDisp)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| homeX | `number` |
| homeY | `number` |
| homeZ | `number` |
| baseDisp | `integer` |

### Returns
- None

### C Prototype
`void obj_return_and_displace_home(struct Object *obj, f32 homeX, UNUSED f32 homeY, f32 homeZ, s32 baseDisp);`

[:arrow_up_small:](#)

<br />

## [obj_check_if_facing_toward_angle](#obj_check_if_facing_toward_angle)

### Description
A series of checks using sin and cos to see if a given angle is facing in the same direction of a given angle, within a certain range

### Lua Example
`local integerValue = obj_check_if_facing_toward_angle(base, goal, range)`

### Parameters
| Field | Type |
| ----- | ---- |
| base | `integer` |
| goal | `integer` |
| range | `integer` |

### Returns
- `integer`

### C Prototype
`s8 obj_check_if_facing_toward_angle(u32 base, u32 goal, s16 range);`

[:arrow_up_small:](#)

<br />

## [obj_find_wall_displacement](#obj_find_wall_displacement)

### Description
Finds any wall collisions and returns what the displacement vector would be.

### Lua Example
`local integerValue = obj_find_wall_displacement(dist, x, y, z, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| dist | [Vec3f](structs.md#Vec3f) |
| x | `number` |
| y | `number` |
| z | `number` |
| radius | `number` |

### Returns
- `integer`

### C Prototype
`s8 obj_find_wall_displacement(OUT Vec3f dist, f32 x, f32 y, f32 z, f32 radius);`

[:arrow_up_small:](#)

<br />

## [obj_spawn_yellow_coins](#obj_spawn_yellow_coins)

### Description
Spawns a number of coins at the location of an object with a random forward velocity, y velocity, and direction

### Lua Example
`obj_spawn_yellow_coins(obj, nCoins)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| nCoins | `integer` |

### Returns
- None

### C Prototype
`void obj_spawn_yellow_coins(struct Object *obj, s8 nCoins);`

[:arrow_up_small:](#)

<br />

## [obj_flicker_and_disappear](#obj_flicker_and_disappear)

### Description
Controls whether certain objects should flicker/when to despawn

### Lua Example
`local integerValue = obj_flicker_and_disappear(obj, lifeSpan)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| lifeSpan | `integer` |

### Returns
- `integer`

### C Prototype
`s8 obj_flicker_and_disappear(struct Object *obj, s16 lifeSpan);`

[:arrow_up_small:](#)

<br />

## [current_mario_room_check](#current_mario_room_check)

### Description
Checks if a given room is Mario's current room, even if on an object

### Lua Example
`local integerValue = current_mario_room_check(room)`

### Parameters
| Field | Type |
| ----- | ---- |
| room | `integer` |

### Returns
- `integer`

### C Prototype
`s8 current_mario_room_check(s16 room);`

[:arrow_up_small:](#)

<br />

## [obj_check_floor_death](#obj_check_floor_death)

### Description
Checks if `floor`'s type is burning or death plane and if so change the current object's action accordingly

### Lua Example
`obj_check_floor_death(collisionFlags, floor)`

### Parameters
| Field | Type |
| ----- | ---- |
| collisionFlags | `integer` |
| floor | [Surface](structs.md#Surface) |

### Returns
- None

### C Prototype
`void obj_check_floor_death(s16 collisionFlags, struct Surface *floor);`

[:arrow_up_small:](#)

<br />

## [obj_lava_death](#obj_lava_death)

### Description
Controls an object dying in lava by creating smoke, sinking the object, playing audio, and eventually despawning it. Returns TRUE when the obj is dead

### Lua Example
`local integerValue = obj_lava_death()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s8 obj_lava_death(void);`

[:arrow_up_small:](#)

<br />

## [spawn_orange_number](#spawn_orange_number)

### Description
Spawns an orange number object relatively, such as those that count up for secrets.

### Lua Example
`spawn_orange_number(behParam, relX, relY, relZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| behParam | `integer` |
| relX | `integer` |
| relY | `integer` |
| relZ | `integer` |

### Returns
- None

### C Prototype
`void spawn_orange_number(s8 behParam, s16 relX, s16 relY, s16 relZ);`

[:arrow_up_small:](#)

<br />

---
# functions from obj_behaviors_2.c

<br />


## [obj_is_rendering_enabled](#obj_is_rendering_enabled)

### Description
Checks if the current object's rendering is enabled

### Lua Example
`local integerValue = obj_is_rendering_enabled()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 obj_is_rendering_enabled(void);`

[:arrow_up_small:](#)

<br />

## [obj_get_pitch_from_vel](#obj_get_pitch_from_vel)

### Description
Calculates the current object's theoretical pitch from forward velocity and vertical velocity

### Lua Example
`local integerValue = obj_get_pitch_from_vel()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 obj_get_pitch_from_vel(void);`

[:arrow_up_small:](#)

<br />

## [obj_set_dist_from_home](#obj_set_dist_from_home)

### Description
Sets the current object's position to the home with an additional forward vector multiplied by `distFromHome`

### Lua Example
`obj_set_dist_from_home(distFromHome)`

### Parameters
| Field | Type |
| ----- | ---- |
| distFromHome | `number` |

### Returns
- None

### C Prototype
`void obj_set_dist_from_home(f32 distFromHome);`

[:arrow_up_small:](#)

<br />

## [obj_is_near_to_and_facing_mario](#obj_is_near_to_and_facing_mario)

### Description
Checks if the current object is in `maxDist` to `m` and the angle difference is less than `maxAngleDiff`

### Lua Example
`local integerValue = obj_is_near_to_and_facing_mario(m, maxDist, maxAngleDiff)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| maxDist | `number` |
| maxAngleDiff | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_is_near_to_and_facing_mario(struct MarioState* m, f32 maxDist, s16 maxAngleDiff);`

[:arrow_up_small:](#)

<br />

## [platform_on_track_update_pos_or_spawn_ball](#platform_on_track_update_pos_or_spawn_ball)

### Description
Handles the platform on track's trajectory marker ball spawning

### Lua Example
`platform_on_track_update_pos_or_spawn_ball(ballIndex, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| ballIndex | `integer` |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- None

### C Prototype
`void platform_on_track_update_pos_or_spawn_ball(s32 ballIndex, f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spin_all_dimensions](#cur_obj_spin_all_dimensions)

### Description
Spins an object in every direction with `pitchSpeed` and `rollSpeed`

### Lua Example
`cur_obj_spin_all_dimensions(pitchSpeed, rollSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| pitchSpeed | `number` |
| rollSpeed | `number` |

### Returns
- None

### C Prototype
`void cur_obj_spin_all_dimensions(f32 pitchSpeed, f32 rollSpeed);`

[:arrow_up_small:](#)

<br />

## [obj_rotate_yaw_and_bounce_off_walls](#obj_rotate_yaw_and_bounce_off_walls)

### Description
Approaches the current object's yaw to `targetYaw` by `turnAmount`

### Lua Example
`obj_rotate_yaw_and_bounce_off_walls(targetYaw, turnAmount)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `integer` |
| turnAmount | `integer` |

### Returns
- None

### C Prototype
`void obj_rotate_yaw_and_bounce_off_walls(s16 targetYaw, s16 turnAmount);`

[:arrow_up_small:](#)

<br />

## [obj_get_pitch_to_home](#obj_get_pitch_to_home)

### Description
Gets the current object's theoretical pitch to the home with the lateral distance from it

### Lua Example
`local integerValue = obj_get_pitch_to_home(latDistToHome)`

### Parameters
| Field | Type |
| ----- | ---- |
| latDistToHome | `number` |

### Returns
- `integer`

### C Prototype
`s16 obj_get_pitch_to_home(f32 latDistToHome);`

[:arrow_up_small:](#)

<br />

## [obj_compute_vel_from_move_pitch](#obj_compute_vel_from_move_pitch)

### Description
Computes the current object's forward vel and vertical velocity with the move angle pitch

### Lua Example
`obj_compute_vel_from_move_pitch(speed)`

### Parameters
| Field | Type |
| ----- | ---- |
| speed | `number` |

### Returns
- None

### C Prototype
`void obj_compute_vel_from_move_pitch(f32 speed);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_anim_extend](#cur_obj_init_anim_extend)

### Description
Initializes an animation for the current object and loops back around if the animation ends

### Lua Example
`cur_obj_init_anim_extend(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_anim_extend(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_anim_and_check_if_end](#cur_obj_init_anim_and_check_if_end)

### Description
Initializes an animation for the current object and returns if the animation has ended

### Lua Example
`local integerValue = cur_obj_init_anim_and_check_if_end(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_init_anim_and_check_if_end(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_anim_check_frame](#cur_obj_init_anim_check_frame)

### Description
Initializes an animation for the current object and checks if the animation frame is a specific frame

### Lua Example
`local integerValue = cur_obj_init_anim_check_frame(animIndex, animFrame)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |
| animFrame | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_init_anim_check_frame(s32 animIndex, s32 animFrame);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_anim_if_at_end](#cur_obj_set_anim_if_at_end)

### Description
Sets the current object's animation to a new animation if the current animation has ended

### Lua Example
`local integerValue = cur_obj_set_anim_if_at_end(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_set_anim_if_at_end(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_play_sound_at_anim_range](#cur_obj_play_sound_at_anim_range)

### Description
Plays a sound when the animation frame is in a range

### Lua Example
`local integerValue = cur_obj_play_sound_at_anim_range(startFrame, endFrame, sound)`

### Parameters
| Field | Type |
| ----- | ---- |
| startFrame | `integer` |
| endFrame | `integer` |
| sound | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_play_sound_at_anim_range(s8 startFrame, s8 endFrame, u32 sound);`

[:arrow_up_small:](#)

<br />

## [obj_turn_pitch_toward_mario](#obj_turn_pitch_toward_mario)

### Description
Turns the current object towards `m` by `turnAmount` and subtracts and adds `targetOffsetY` to the Y position, effectively cancelling any effect out

### Lua Example
`local integerValue = obj_turn_pitch_toward_mario(m, targetOffsetY, turnAmount)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| targetOffsetY | `number` |
| turnAmount | `integer` |

### Returns
- `integer`

### C Prototype
`s16 obj_turn_pitch_toward_mario(struct MarioState* m, f32 targetOffsetY, s16 turnAmount);`

[:arrow_up_small:](#)

<br />

## [approach_f32_ptr](#approach_f32_ptr)

### Description
Approaches a `target` for `px` using `delta`

### Lua Example
`local integerValue = approach_f32_ptr(px, target, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| px | `Pointer` <`number`> |
| target | `number` |
| delta | `number` |

### Returns
- `integer`

### C Prototype
`s32 approach_f32_ptr(f32 *px, f32 target, f32 delta);`

[:arrow_up_small:](#)

<br />

## [obj_forward_vel_approach](#obj_forward_vel_approach)

### Description
Approaches a `target` value with the current object's forward velocity using `delta`

### Lua Example
`local integerValue = obj_forward_vel_approach(target, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `number` |
| delta | `number` |

### Returns
- `integer`

### C Prototype
`s32 obj_forward_vel_approach(f32 target, f32 delta);`

[:arrow_up_small:](#)

<br />

## [obj_y_vel_approach](#obj_y_vel_approach)

### Description
Approaches a `target` value with the current object's vertical velocity using `delta`

### Lua Example
`local integerValue = obj_y_vel_approach(target, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `number` |
| delta | `number` |

### Returns
- `integer`

### C Prototype
`s32 obj_y_vel_approach(f32 target, f32 delta);`

[:arrow_up_small:](#)

<br />

## [obj_move_pitch_approach](#obj_move_pitch_approach)

### Description
Approaches a `target` value with the current object's move pitch using `delta`

### Lua Example
`local integerValue = obj_move_pitch_approach(target, delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `integer` |
| delta | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_move_pitch_approach(s16 target, s16 delta);`

[:arrow_up_small:](#)

<br />

## [obj_face_pitch_approach](#obj_face_pitch_approach)

### Description
Approaches a `target` value with the current object's facing pitch using `delta`

### Lua Example
`local integerValue = obj_face_pitch_approach(targetPitch, deltaPitch)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetPitch | `integer` |
| deltaPitch | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_face_pitch_approach(s16 targetPitch, s16 deltaPitch);`

[:arrow_up_small:](#)

<br />

## [obj_face_yaw_approach](#obj_face_yaw_approach)

### Description
Approaches a `target` value with the current object's facing yaw using `delta`

### Lua Example
`local integerValue = obj_face_yaw_approach(targetYaw, deltaYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `integer` |
| deltaYaw | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_face_yaw_approach(s16 targetYaw, s16 deltaYaw);`

[:arrow_up_small:](#)

<br />

## [obj_face_roll_approach](#obj_face_roll_approach)

### Description
Approaches a `target` value with the current object's facing roll using `delta`

### Lua Example
`local integerValue = obj_face_roll_approach(targetRoll, deltaRoll)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetRoll | `integer` |
| deltaRoll | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_face_roll_approach(s16 targetRoll, s16 deltaRoll);`

[:arrow_up_small:](#)

<br />

## [obj_smooth_turn](#obj_smooth_turn)

### Lua Example
`local integerValue = obj_smooth_turn(angleVel, angle, targetAngle, targetSpeedProportion, accel, minSpeed, maxSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| angleVel | `Pointer` <`integer`> |
| angle | `Pointer` <`integer`> |
| targetAngle | `integer` |
| targetSpeedProportion | `number` |
| accel | `integer` |
| minSpeed | `integer` |
| maxSpeed | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_smooth_turn(s16 *angleVel, s32 *angle, s16 targetAngle, f32 targetSpeedProportion, s16 accel, s16 minSpeed, s16 maxSpeed);`

[:arrow_up_small:](#)

<br />

## [obj_roll_to_match_yaw_turn](#obj_roll_to_match_yaw_turn)

### Description
Rolls the current object to the move angle subtracted by `targetYaw`, clamping between negative and positive `maxRoll` and using `rollSpeed`

### Lua Example
`obj_roll_to_match_yaw_turn(targetYaw, maxRoll, rollSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `integer` |
| maxRoll | `integer` |
| rollSpeed | `integer` |

### Returns
- None

### C Prototype
`void obj_roll_to_match_yaw_turn(s16 targetYaw, s16 maxRoll, s16 rollSpeed);`

[:arrow_up_small:](#)

<br />

## [random_linear_offset](#random_linear_offset)

### Description
Generates a random offset with a base and range of `base` to `range`

### Lua Example
`local integerValue = random_linear_offset(base, range)`

### Parameters
| Field | Type |
| ----- | ---- |
| base | `integer` |
| range | `integer` |

### Returns
- `integer`

### C Prototype
`s16 random_linear_offset(s16 base, s16 range);`

[:arrow_up_small:](#)

<br />

## [random_mod_offset](#random_mod_offset)

### Description
Generates a random offset using step multiplied a value between 0 and `mod` (the random function goes to 65535 but wraps around to 0 at `mod`)

### Lua Example
`local integerValue = random_mod_offset(base, step, mod)`

### Parameters
| Field | Type |
| ----- | ---- |
| base | `integer` |
| step | `integer` |
| mod | `integer` |

### Returns
- `integer`

### C Prototype
`s16 random_mod_offset(s16 base, s16 step, s16 mod);`

[:arrow_up_small:](#)

<br />

## [obj_random_fixed_turn](#obj_random_fixed_turn)

### Description
Rotates the current object's move angle yaw using `delta` in either a randomly decided positive or negative direction

### Lua Example
`local integerValue = obj_random_fixed_turn(delta)`

### Parameters
| Field | Type |
| ----- | ---- |
| delta | `integer` |

### Returns
- `integer`

### C Prototype
`s16 obj_random_fixed_turn(s16 delta);`

[:arrow_up_small:](#)

<br />

## [obj_grow_then_shrink](#obj_grow_then_shrink)

### Description
Begin by increasing the current object's scale by `*scaleVel`, and slowly decreasing `scaleVel`. Once the object starts to shrink, wait a bit, and then begin to scale the object toward `endScale`. The first time it reaches below `shootFireScale` during this time, return 1. Return -1 once it's reached endScale

### Lua Example
`local integerValue = obj_grow_then_shrink(scaleVel, shootFireScale, endScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| scaleVel | `Pointer` <`number`> |
| shootFireScale | `number` |
| endScale | `number` |

### Returns
- `integer`

### C Prototype
`s32 obj_grow_then_shrink(f32 *scaleVel, f32 shootFireScale, f32 endScale);`

[:arrow_up_small:](#)

<br />

## [oscillate_toward](#oscillate_toward)

### Lua Example
`local integerValue = oscillate_toward(value, vel, target, velCloseToZero, accel, slowdown)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `Pointer` <`integer`> |
| vel | `Pointer` <`number`> |
| target | `integer` |
| velCloseToZero | `number` |
| accel | `number` |
| slowdown | `number` |

### Returns
- `integer`

### C Prototype
`s32 oscillate_toward(s32 *value, f32 *vel, s32 target, f32 velCloseToZero, f32 accel, f32 slowdown);`

[:arrow_up_small:](#)

<br />

## [obj_update_blinking](#obj_update_blinking)

### Lua Example
`obj_update_blinking(blinkTimer, baseCycleLength, cycleLengthRange, blinkLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| blinkTimer | `Pointer` <`integer`> |
| baseCycleLength | `integer` |
| cycleLengthRange | `integer` |
| blinkLength | `integer` |

### Returns
- None

### C Prototype
`void obj_update_blinking(s32 *blinkTimer, s16 baseCycleLength, s16 cycleLengthRange, s16 blinkLength);`

[:arrow_up_small:](#)

<br />

## [obj_resolve_object_collisions](#obj_resolve_object_collisions)

### Description
Resolves "collisions" with the current object and other objects by offsetting the current object's position

### Lua Example
`local integerValue = obj_resolve_object_collisions(targetYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 obj_resolve_object_collisions(s32 *targetYaw);`

[:arrow_up_small:](#)

<br />

## [obj_bounce_off_walls_edges_objects](#obj_bounce_off_walls_edges_objects)

### Description
Bounces the current object off of walls, edges, and objects using `*targetYaw`

### Lua Example
`local integerValue = obj_bounce_off_walls_edges_objects(targetYaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 obj_bounce_off_walls_edges_objects(s32 *targetYaw);`

[:arrow_up_small:](#)

<br />

## [obj_resolve_collisions_and_turn](#obj_resolve_collisions_and_turn)

### Description
Resolves collisions and turns the current object towards `targetYaw` using `turnSpeed`

### Lua Example
`local integerValue = obj_resolve_collisions_and_turn(targetYaw, turnSpeed)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetYaw | `integer` |
| turnSpeed | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_resolve_collisions_and_turn(s16 targetYaw, s16 turnSpeed);`

[:arrow_up_small:](#)

<br />

## [obj_die_if_health_non_positive](#obj_die_if_health_non_positive)

### Description
Spawns mist particles, plays a sound (`oDeathSound`,) spawns coins (`oNumLootCoins`,) and hides the object if the health is less than 0 or deletes the object if the health is 0 or higher

### Lua Example
`obj_die_if_health_non_positive()`

### Parameters
- None

### Returns
- None

### C Prototype
`void obj_die_if_health_non_positive(void);`

[:arrow_up_small:](#)

<br />

## [obj_unused_die](#obj_unused_die)

### Description
Sets the current object's health to 0 and runs `obj_die_if_health_non_positive()`

### Lua Example
`obj_unused_die()`

### Parameters
- None

### Returns
- None

### C Prototype
`void obj_unused_die(void);`

[:arrow_up_small:](#)

<br />

## [obj_set_knockback_action](#obj_set_knockback_action)

### Description
Sets the current object's action, forward velocity, and vertical velocity to preset values (`OBJ_ACT_*`)

### Lua Example
`obj_set_knockback_action(attackType)`

### Parameters
| Field | Type |
| ----- | ---- |
| attackType | `integer` |

### Returns
- None

### C Prototype
`void obj_set_knockback_action(s32 attackType);`

[:arrow_up_small:](#)

<br />

## [obj_set_squished_action](#obj_set_squished_action)

### Description
Plays `SOUND_OBJ_STOMPED` and sets the current object's action to `OBJ_ACT_SQUISHED`

### Lua Example
`obj_set_squished_action()`

### Parameters
- None

### Returns
- None

### C Prototype
`void obj_set_squished_action(void);`

[:arrow_up_small:](#)

<br />

## [obj_die_if_above_lava_and_health_non_positive](#obj_die_if_above_lava_and_health_non_positive)

### Lua Example
`local integerValue = obj_die_if_above_lava_and_health_non_positive()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 obj_die_if_above_lava_and_health_non_positive(void);`

[:arrow_up_small:](#)

<br />

## [obj_handle_attacks](#obj_handle_attacks)

### Lua Example
`local integerValue = obj_handle_attacks(hitbox, attackedMarioAction, attackHandlers)`

### Parameters
| Field | Type |
| ----- | ---- |
| hitbox | [ObjectHitbox](structs.md#ObjectHitbox) |
| attackedMarioAction | `integer` |
| attackHandlers | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 obj_handle_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction, u8 *attackHandlers);`

[:arrow_up_small:](#)

<br />

## [obj_act_knockback](#obj_act_knockback)

### Lua Example
`obj_act_knockback(baseScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| baseScale | `number` |

### Returns
- None

### C Prototype
`void obj_act_knockback(UNUSED f32 baseScale);`

[:arrow_up_small:](#)

<br />

## [obj_act_squished](#obj_act_squished)

### Lua Example
`obj_act_squished(baseScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| baseScale | `number` |

### Returns
- None

### C Prototype
`void obj_act_squished(f32 baseScale);`

[:arrow_up_small:](#)

<br />

## [obj_update_standard_actions](#obj_update_standard_actions)

### Lua Example
`local integerValue = obj_update_standard_actions(scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| scale | `number` |

### Returns
- `integer`

### C Prototype
`s32 obj_update_standard_actions(f32 scale);`

[:arrow_up_small:](#)

<br />

## [obj_check_attacks](#obj_check_attacks)

### Description
Checks the current object's interaction status and sets action to `attackedMarioAction` if Mario has been attacked and runs `obj_die_if_health_non_positive()` if the object is attacked by Mario. Sets the hitbox parameters and resets interaction status to 0

### Lua Example
`local integerValue = obj_check_attacks(hitbox, attackedMarioAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| hitbox | [ObjectHitbox](structs.md#ObjectHitbox) |
| attackedMarioAction | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_check_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction);`

[:arrow_up_small:](#)

<br />

## [obj_move_for_one_second](#obj_move_for_one_second)

### Description
Moves the current object for specifically one second (`oTimer` < 30)

### Lua Example
`local integerValue = obj_move_for_one_second(endAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| endAction | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_move_for_one_second(s32 endAction);`

[:arrow_up_small:](#)

<br />

## [treat_far_home_as_mario](#treat_far_home_as_mario)

### Description
Moves the current object for specifically one second (`oTimer` < 30)

### Lua Example
`treat_far_home_as_mario(threshold, distanceToPlayer, angleToPlayer)`

### Parameters
| Field | Type |
| ----- | ---- |
| threshold | `number` |
| distanceToPlayer | `Pointer` <`integer`> |
| angleToPlayer | `Pointer` <`integer`> |

### Returns
- None

### C Prototype
`void treat_far_home_as_mario(f32 threshold, s32* distanceToPlayer, s32* angleToPlayer);`

[:arrow_up_small:](#)

<br />

## [obj_spit_fire](#obj_spit_fire)

### Lua Example
`local ObjectValue = obj_spit_fire(relativePosX, relativePosY, relativePosZ, scale, model, startSpeed, endSpeed, movePitch)`

### Parameters
| Field | Type |
| ----- | ---- |
| relativePosX | `integer` |
| relativePosY | `integer` |
| relativePosZ | `integer` |
| scale | `number` |
| model | `integer` |
| startSpeed | `number` |
| endSpeed | `number` |
| movePitch | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* obj_spit_fire(s16 relativePosX, s16 relativePosY, s16 relativePosZ, f32 scale, s32 model, f32 startSpeed, f32 endSpeed, s16 movePitch);`

[:arrow_up_small:](#)

<br />
---

[< prev](functions-4.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | 5 | [6](functions-6.md) | [7](functions-7.md) | [next >](functions-6.md)]

