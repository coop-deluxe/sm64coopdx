## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-3.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | 4 | [5](functions-5.md) | [next >](functions-5.md)]


---
# functions from math_util.h

<br />


## [anim_spline_init](#anim_spline_init)

### Lua Example
`anim_spline_init(m, keyFrames)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| keyFrames | `Pointer` <`Vec4s`> |

### Returns
- None

### C Prototype
`void anim_spline_init(struct MarioState* m, Vec4s *keyFrames);`

[:arrow_up_small:](#)

<br />

## [anim_spline_poll](#anim_spline_poll)

### Lua Example
`local integerValue = anim_spline_poll(m, result)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| result | [Vec3f](structs.md#Vec3f) |

### Returns
- `integer`

### C Prototype
`s32 anim_spline_poll(struct MarioState* m, Vec3f result);`

[:arrow_up_small:](#)

<br />

## [approach_f32](#approach_f32)

### Lua Example
`local numberValue = approach_f32(current, target, inc, dec)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `number` |
| target | `number` |
| inc | `number` |
| dec | `number` |

### Returns
- `number`

### C Prototype
`f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec);`

[:arrow_up_small:](#)

<br />

## [approach_s32](#approach_s32)

### Lua Example
`local integerValue = approach_s32(current, target, inc, dec)`

### Parameters
| Field | Type |
| ----- | ---- |
| current | `integer` |
| target | `integer` |
| inc | `integer` |
| dec | `integer` |

### Returns
- `integer`

### C Prototype
`s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec);`

[:arrow_up_small:](#)

<br />

## [atan2s](#atan2s)

### Lua Example
`local integerValue = atan2s(y, x)`

### Parameters
| Field | Type |
| ----- | ---- |
| y | `number` |
| x | `number` |

### Returns
- `integer`

### C Prototype
`s16 atan2s(f32 y, f32 x);`

[:arrow_up_small:](#)

<br />

## [coss](#coss)

### Lua Example
`local numberValue = coss(sm64Angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| sm64Angle | `integer` |

### Returns
- `number`

### C Prototype
`f32 coss(s16 sm64Angle);`

[:arrow_up_small:](#)

<br />

## [find_vector_perpendicular_to_plane](#find_vector_perpendicular_to_plane)

### Lua Example
`local voidValue = find_vector_perpendicular_to_plane(dest, a, b, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |
| c | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c);`

[:arrow_up_small:](#)

<br />

## [get_pos_from_transform_mtx](#get_pos_from_transform_mtx)

### Lua Example
`get_pos_from_transform_mtx(dest, objMtx, camMtx)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| objMtx | `Mat4` |
| camMtx | `Mat4` |

### Returns
- None

### C Prototype
`void get_pos_from_transform_mtx(Vec3f dest, Mat4 objMtx, Mat4 camMtx);`

[:arrow_up_small:](#)

<br />

## [max](#max)

### Lua Example
`local integerValue = max(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |
| b | `integer` |

### Returns
- `integer`

### C Prototype
`s16 max(s16 a, s16 b);`

[:arrow_up_small:](#)

<br />

## [maxf](#maxf)

### Lua Example
`local numberValue = maxf(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `number` |
| b | `number` |

### Returns
- `number`

### C Prototype
`f32 maxf(f32 a, f32 b);`

[:arrow_up_small:](#)

<br />

## [min](#min)

### Lua Example
`local integerValue = min(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |
| b | `integer` |

### Returns
- `integer`

### C Prototype
`s16 min(s16 a, s16 b);`

[:arrow_up_small:](#)

<br />

## [minf](#minf)

### Lua Example
`local numberValue = minf(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `number` |
| b | `number` |

### Returns
- `number`

### C Prototype
`f32 minf(f32 a, f32 b);`

[:arrow_up_small:](#)

<br />

## [mtxf_align_terrain_normal](#mtxf_align_terrain_normal)

### Lua Example
`mtxf_align_terrain_normal(dest, upDir, pos, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| upDir | [Vec3f](structs.md#Vec3f) |
| pos | [Vec3f](structs.md#Vec3f) |
| yaw | `integer` |

### Returns
- None

### C Prototype
`void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw);`

[:arrow_up_small:](#)

<br />

## [mtxf_align_terrain_triangle](#mtxf_align_terrain_triangle)

### Lua Example
`mtxf_align_terrain_triangle(mtx, pos, yaw, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| mtx | `Mat4` |
| pos | [Vec3f](structs.md#Vec3f) |
| yaw | `integer` |
| radius | `number` |

### Returns
- None

### C Prototype
`void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, s16 yaw, f32 radius);`

[:arrow_up_small:](#)

<br />

## [mtxf_billboard](#mtxf_billboard)

### Lua Example
`mtxf_billboard(dest, mtx, position, angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| mtx | `Mat4` |
| position | [Vec3f](structs.md#Vec3f) |
| angle | `integer` |

### Returns
- None

### C Prototype
`void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);`

[:arrow_up_small:](#)

<br />

## [mtxf_copy](#mtxf_copy)

### Lua Example
`mtxf_copy(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| src | `Mat4` |

### Returns
- None

### C Prototype
`void mtxf_copy(Mat4 dest, Mat4 src);`

[:arrow_up_small:](#)

<br />

## [mtxf_cylboard](#mtxf_cylboard)

### Lua Example
`mtxf_cylboard(dest, mtx, position, angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| mtx | `Mat4` |
| position | [Vec3f](structs.md#Vec3f) |
| angle | `integer` |

### Returns
- None

### C Prototype
`void mtxf_cylboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);`

[:arrow_up_small:](#)

<br />

## [mtxf_identity](#mtxf_identity)

### Lua Example
`mtxf_identity(mtx)`

### Parameters
| Field | Type |
| ----- | ---- |
| mtx | `Mat4` |

### Returns
- None

### C Prototype
`void mtxf_identity(Mat4 mtx);`

[:arrow_up_small:](#)

<br />

## [mtxf_inverse](#mtxf_inverse)

### Lua Example
`mtxf_inverse(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| src | `Mat4` |

### Returns
- None

### C Prototype
`void mtxf_inverse(Mat4 dest, Mat4 src);`

[:arrow_up_small:](#)

<br />

## [mtxf_lookat](#mtxf_lookat)

### Lua Example
`mtxf_lookat(mtx, from, to, roll)`

### Parameters
| Field | Type |
| ----- | ---- |
| mtx | `Mat4` |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| roll | `integer` |

### Returns
- None

### C Prototype
`void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, s16 roll);`

[:arrow_up_small:](#)

<br />

## [mtxf_mul](#mtxf_mul)

### Lua Example
`mtxf_mul(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| a | `Mat4` |
| b | `Mat4` |

### Returns
- None

### C Prototype
`void mtxf_mul(Mat4 dest, Mat4 a, Mat4 b);`

[:arrow_up_small:](#)

<br />

## [mtxf_mul_vec3s](#mtxf_mul_vec3s)

### Lua Example
`mtxf_mul_vec3s(mtx, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| mtx | `Mat4` |
| b | [Vec3s](structs.md#Vec3s) |

### Returns
- None

### C Prototype
`void mtxf_mul_vec3s(Mat4 mtx, Vec3s b);`

[:arrow_up_small:](#)

<br />

## [mtxf_rotate_xy](#mtxf_rotate_xy)

### Lua Example
`mtxf_rotate_xy(mtx, angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| mtx | `Pointer` <`Mtx`> |
| angle | `integer` |

### Returns
- None

### C Prototype
`void mtxf_rotate_xy(Mtx *mtx, s16 angle);`

[:arrow_up_small:](#)

<br />

## [mtxf_rotate_xyz_and_translate](#mtxf_rotate_xyz_and_translate)

### Lua Example
`mtxf_rotate_xyz_and_translate(dest, b, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| b | [Vec3f](structs.md#Vec3f) |
| c | [Vec3s](structs.md#Vec3s) |

### Returns
- None

### C Prototype
`void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f b, Vec3s c);`

[:arrow_up_small:](#)

<br />

## [mtxf_rotate_zxy_and_translate](#mtxf_rotate_zxy_and_translate)

### Lua Example
`mtxf_rotate_zxy_and_translate(dest, translate, rotate)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| translate | [Vec3f](structs.md#Vec3f) |
| rotate | [Vec3s](structs.md#Vec3s) |

### Returns
- None

### C Prototype
`void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3s rotate);`

[:arrow_up_small:](#)

<br />

## [mtxf_scale_vec3f](#mtxf_scale_vec3f)

### Lua Example
`mtxf_scale_vec3f(dest, mtx, s)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| mtx | `Mat4` |
| s | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s);`

[:arrow_up_small:](#)

<br />

## [mtxf_to_mtx](#mtxf_to_mtx)

### Lua Example
`mtxf_to_mtx(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Pointer` <`Mtx`> |
| src | `Mat4` |

### Returns
- None

### C Prototype
`void mtxf_to_mtx(Mtx *dest, Mat4 src);`

[:arrow_up_small:](#)

<br />

## [mtxf_translate](#mtxf_translate)

### Lua Example
`mtxf_translate(dest, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Mat4` |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void mtxf_translate(Mat4 dest, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [not_zero](#not_zero)

### Lua Example
`local numberValue = not_zero(value, replacement)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `number` |
| replacement | `number` |

### Returns
- `number`

### C Prototype
`f32 not_zero(f32 value, f32 replacement);`

[:arrow_up_small:](#)

<br />

## [sins](#sins)

### Lua Example
`local numberValue = sins(sm64Angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| sm64Angle | `integer` |

### Returns
- `number`

### C Prototype
`f32 sins(s16 sm64Angle);`

[:arrow_up_small:](#)

<br />

## [spline_get_weights](#spline_get_weights)

### Lua Example
`spline_get_weights(m, result, t, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| result | `Vec4f` |
| t | `number` |
| c | `integer` |

### Returns
- None

### C Prototype
`void spline_get_weights(struct MarioState* m, Vec4f result, f32 t, UNUSED s32 c);`

[:arrow_up_small:](#)

<br />

## [sqr](#sqr)

### Lua Example
`local integerValue = sqr(x)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `integer` |

### Returns
- `integer`

### C Prototype
`s16 sqr(s16 x);`

[:arrow_up_small:](#)

<br />

## [sqrf](#sqrf)

### Lua Example
`local numberValue = sqrf(x)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |

### Returns
- `number`

### C Prototype
`f32 sqrf(f32 x);`

[:arrow_up_small:](#)

<br />

## [vec3f_add](#vec3f_add)

### Lua Example
`local voidValue = vec3f_add(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_add(Vec3f dest, Vec3f a);`

[:arrow_up_small:](#)

<br />

## [vec3f_combine](#vec3f_combine)

### Lua Example
`vec3f_combine(dest, vecA, vecB, sclA, sclB)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| vecA | [Vec3f](structs.md#Vec3f) |
| vecB | [Vec3f](structs.md#Vec3f) |
| sclA | `number` |
| sclB | `number` |

### Returns
- None

### C Prototype
`void vec3f_combine(Vec3f dest, Vec3f vecA, Vec3f vecB, f32 sclA, f32 sclB);`

[:arrow_up_small:](#)

<br />

## [vec3f_copy](#vec3f_copy)

### Lua Example
`local voidValue = vec3f_copy(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| src | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_copy(Vec3f dest, Vec3f src);`

[:arrow_up_small:](#)

<br />

## [vec3f_cross](#vec3f_cross)

### Lua Example
`local voidValue = vec3f_cross(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_cross(Vec3f dest, Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [vec3f_dif](#vec3f_dif)

### Lua Example
`local voidValue = vec3f_dif(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_dif(Vec3f dest, Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [vec3f_dist](#vec3f_dist)

### Lua Example
`local numberValue = vec3f_dist(v1, v2)`

### Parameters
| Field | Type |
| ----- | ---- |
| v1 | [Vec3f](structs.md#Vec3f) |
| v2 | [Vec3f](structs.md#Vec3f) |

### Returns
- `number`

### C Prototype
`f32 vec3f_dist(Vec3f v1, Vec3f v2);`

[:arrow_up_small:](#)

<br />

## [vec3f_dot](#vec3f_dot)

### Lua Example
`local numberValue = vec3f_dot(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `number`

### C Prototype
`f32 vec3f_dot(Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [vec3f_get_dist_and_angle](#vec3f_get_dist_and_angle)

### Lua Example
`vec3f_get_dist_and_angle(from, to, dist, pitch, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| dist | `Pointer` <`number`> |
| pitch | `Pointer` <`integer`> |
| yaw | `Pointer` <`integer`> |

### Returns
- None

### C Prototype
`void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, s16 *pitch, s16 *yaw);`

[:arrow_up_small:](#)

<br />

## [vec3f_length](#vec3f_length)

### Lua Example
`local numberValue = vec3f_length(a)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | [Vec3f](structs.md#Vec3f) |

### Returns
- `number`

### C Prototype
`f32 vec3f_length(Vec3f a);`

[:arrow_up_small:](#)

<br />

## [vec3f_mul](#vec3f_mul)

### Lua Example
`local voidValue = vec3f_mul(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | `number` |

### Returns
- `void *`

### C Prototype
`void *vec3f_mul(Vec3f dest, f32 a);`

[:arrow_up_small:](#)

<br />

## [vec3f_normalize](#vec3f_normalize)

### Lua Example
`local voidValue = vec3f_normalize(dest)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_normalize(Vec3f dest);`

[:arrow_up_small:](#)

<br />

## [vec3f_project](#vec3f_project)

### Lua Example
`vec3f_project(vec, onto, out)`

### Parameters
| Field | Type |
| ----- | ---- |
| vec | [Vec3f](structs.md#Vec3f) |
| onto | [Vec3f](structs.md#Vec3f) |
| out | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void vec3f_project(Vec3f vec, Vec3f onto, Vec3f out);`

[:arrow_up_small:](#)

<br />

## [vec3f_rotate_zxy](#vec3f_rotate_zxy)

### Lua Example
`local voidValue = vec3f_rotate_zxy(v, rotate)`

### Parameters
| Field | Type |
| ----- | ---- |
| v | [Vec3f](structs.md#Vec3f) |
| rotate | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3f_rotate_zxy(Vec3f v, Vec3s rotate);`

[:arrow_up_small:](#)

<br />

## [vec3f_set](#vec3f_set)

### Lua Example
`local voidValue = vec3f_set(dest, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- `void *`

### C Prototype
`void *vec3f_set(Vec3f dest, f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [vec3f_set_dist_and_angle](#vec3f_set_dist_and_angle)

### Lua Example
`vec3f_set_dist_and_angle(from, to, dist, pitch, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| from | [Vec3f](structs.md#Vec3f) |
| to | [Vec3f](structs.md#Vec3f) |
| dist | `number` |
| pitch | `integer` |
| yaw | `integer` |

### Returns
- None

### C Prototype
`void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32 dist, s16 pitch, s16 yaw);`

[:arrow_up_small:](#)

<br />

## [vec3f_sum](#vec3f_sum)

### Lua Example
`local voidValue = vec3f_sum(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3f](structs.md#Vec3f) |
| b | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_sum(Vec3f dest, Vec3f a, Vec3f b);`

[:arrow_up_small:](#)

<br />

## [vec3f_to_vec3s](#vec3f_to_vec3s)

### Lua Example
`local voidValue = vec3f_to_vec3s(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3f](structs.md#Vec3f) |

### Returns
- `void *`

### C Prototype
`void *vec3f_to_vec3s(Vec3s dest, Vec3f a);`

[:arrow_up_small:](#)

<br />

## [vec3s_add](#vec3s_add)

### Lua Example
`local voidValue = vec3s_add(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3s_add(Vec3s dest, Vec3s a);`

[:arrow_up_small:](#)

<br />

## [vec3s_copy](#vec3s_copy)

### Lua Example
`local voidValue = vec3s_copy(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| src | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3s_copy(Vec3s dest, Vec3s src);`

[:arrow_up_small:](#)

<br />

## [vec3s_set](#vec3s_set)

### Lua Example
`local voidValue = vec3s_set(dest, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| x | `integer` |
| y | `integer` |
| z | `integer` |

### Returns
- `void *`

### C Prototype
`void *vec3s_set(Vec3s dest, s16 x, s16 y, s16 z);`

[:arrow_up_small:](#)

<br />

## [vec3s_sum](#vec3s_sum)

### Lua Example
`local voidValue = vec3s_sum(dest, a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3s](structs.md#Vec3s) |
| a | [Vec3s](structs.md#Vec3s) |
| b | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3s_sum(Vec3s dest, Vec3s a, Vec3s b);`

[:arrow_up_small:](#)

<br />

## [vec3s_to_vec3f](#vec3s_to_vec3f)

### Lua Example
`local voidValue = vec3s_to_vec3f(dest, a)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| a | [Vec3s](structs.md#Vec3s) |

### Returns
- `void *`

### C Prototype
`void *vec3s_to_vec3f(Vec3f dest, Vec3s a);`

[:arrow_up_small:](#)

<br />

---
# functions from misc.h

<br />


## [update_all_mario_stars](#update_all_mario_stars)

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

---
# functions from mod_storage.h

<br />


## [mod_storage_clear](#mod_storage_clear)

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

## [mod_storage_load](#mod_storage_load)

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

## [mod_storage_load_bool](#mod_storage_load_bool)

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

## [mod_storage_load_number](#mod_storage_load_number)

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

## [mod_storage_remove](#mod_storage_remove)

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

## [mod_storage_save](#mod_storage_save)

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

## [mod_storage_save_bool](#mod_storage_save_bool)

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

## [mod_storage_save_number](#mod_storage_save_number)

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

---
# functions from network_player.h

<br />


## [get_network_player_from_area](#get_network_player_from_area)

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

## [get_network_player_from_level](#get_network_player_from_level)

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

## [get_network_player_smallest_global](#get_network_player_smallest_global)

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

## [network_player_connected_count](#network_player_connected_count)

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

## [network_player_from_global_index](#network_player_from_global_index)

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

## [network_player_is_override_palette_same](#network_player_is_override_palette_same)

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

## [network_player_reset_override_palette](#network_player_reset_override_palette)

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

## [network_player_set_description](#network_player_set_description)

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

## [network_player_set_override_palette_color](#network_player_set_override_palette_color)

### Lua Example
`network_player_set_override_palette_color(np, part, color)`

### Parameters
| Field | Type |
| ----- | ---- |
| np | [NetworkPlayer](structs.md#NetworkPlayer) |
| part | [enum PlayerPart](constants.md#enum-PlayerPart) |
| color | `Color` |

### Returns
- None

### C Prototype
`void network_player_set_override_palette_color(struct NetworkPlayer *np, enum PlayerPart part, Color color);`

[:arrow_up_small:](#)

<br />

---
# functions from network_utils.h

<br />


## [network_check_singleplayer_pause](#network_check_singleplayer_pause)

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

## [network_get_player_text_color_string](#network_get_player_text_color_string)

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

## [network_global_index_from_local](#network_global_index_from_local)

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

## [network_is_moderator](#network_is_moderator)

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

## [network_is_server](#network_is_server)

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

## [network_local_index_from_global](#network_local_index_from_global)

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

---
# functions from obj_behaviors.c

<br />


## [absf_2](#absf_2)

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

## [calc_new_obj_vel_and_pos_y](#calc_new_obj_vel_and_pos_y)

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

## [calc_obj_friction](#calc_obj_friction)

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

## [current_mario_room_check](#current_mario_room_check)

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

## [is_nearest_mario_state_to_object](#is_nearest_mario_state_to_object)

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

## [is_other_player_active](#is_other_player_active)

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

## [is_player_active](#is_player_active)

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

## [is_player_in_local_area](#is_player_in_local_area)

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

## [is_point_close_to_object](#is_point_close_to_object)

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

## [is_point_within_radius_of_any_player](#is_point_within_radius_of_any_player)

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

## [is_point_within_radius_of_mario](#is_point_within_radius_of_mario)

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

## [nearest_interacting_mario_state_to_object](#nearest_interacting_mario_state_to_object)

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

## [nearest_mario_state_to_object](#nearest_mario_state_to_object)

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

## [nearest_player_to_object](#nearest_player_to_object)

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

## [nearest_possible_mario_state_to_object](#nearest_possible_mario_state_to_object)

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

## [obj_check_floor_death](#obj_check_floor_death)

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

## [obj_check_if_facing_toward_angle](#obj_check_if_facing_toward_angle)

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

## [obj_find_wall](#obj_find_wall)

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

## [obj_find_wall_displacement](#obj_find_wall_displacement)

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
`s8 obj_find_wall_displacement(Vec3f dist, f32 x, f32 y, f32 z, f32 radius);`

[:arrow_up_small:](#)

<br />

## [obj_flicker_and_disappear](#obj_flicker_and_disappear)

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

## [obj_lava_death](#obj_lava_death)

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

## [obj_move_xyz_using_fvel_and_yaw](#obj_move_xyz_using_fvel_and_yaw)

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

## [obj_orient_graph](#obj_orient_graph)

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

## [obj_return_and_displace_home](#obj_return_and_displace_home)

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

## [obj_return_home_if_safe](#obj_return_home_if_safe)

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

## [obj_spawn_yellow_coins](#obj_spawn_yellow_coins)

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

## [obj_splash](#obj_splash)

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

## [obj_update_pos_vel_xz](#obj_update_pos_vel_xz)

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

## [object_step](#object_step)

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

## [set_object_visibility](#set_object_visibility)

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

## [set_yoshi_as_not_dead](#set_yoshi_as_not_dead)

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

## [spawn_orange_number](#spawn_orange_number)

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

## [turn_obj_away_from_steep_floor](#turn_obj_away_from_steep_floor)

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

## [turn_obj_away_from_surface](#turn_obj_away_from_surface)

### Lua Example
`turn_obj_away_from_surface(velX, velZ, nX, nY, nZ, objYawX, objYawZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| velX | `number` |
| velZ | `number` |
| nX | `number` |
| nY | `number` |
| nZ | `number` |
| objYawX | `Pointer` <`number`> |
| objYawZ | `Pointer` <`number`> |

### Returns
- None

### C Prototype
`void turn_obj_away_from_surface(f32 velX, f32 velZ, f32 nX, UNUSED f32 nY, f32 nZ, f32 *objYawX, f32 *objYawZ);`

[:arrow_up_small:](#)

<br />

---
# functions from obj_behaviors_2.c

<br />


## [approach_f32_ptr](#approach_f32_ptr)

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

## [cur_obj_init_anim_and_check_if_end](#cur_obj_init_anim_and_check_if_end)

### Lua Example
`local integerValue = cur_obj_init_anim_and_check_if_end(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_init_anim_and_check_if_end(s32 arg0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_anim_check_frame](#cur_obj_init_anim_check_frame)

### Lua Example
`local integerValue = cur_obj_init_anim_check_frame(arg0, arg1)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |
| arg1 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_init_anim_check_frame(s32 arg0, s32 arg1);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_anim_extend](#cur_obj_init_anim_extend)

### Lua Example
`cur_obj_init_anim_extend(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_anim_extend(s32 arg0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_play_sound_at_anim_range](#cur_obj_play_sound_at_anim_range)

### Lua Example
`local integerValue = cur_obj_play_sound_at_anim_range(arg0, arg1, sound)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |
| arg1 | `integer` |
| sound | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_play_sound_at_anim_range(s8 arg0, s8 arg1, u32 sound);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_anim_if_at_end](#cur_obj_set_anim_if_at_end)

### Lua Example
`local integerValue = cur_obj_set_anim_if_at_end(arg0)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_set_anim_if_at_end(s32 arg0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spin_all_dimensions](#cur_obj_spin_all_dimensions)

### Lua Example
`cur_obj_spin_all_dimensions(arg0, arg1)`

### Parameters
| Field | Type |
| ----- | ---- |
| arg0 | `number` |
| arg1 | `number` |

### Returns
- None

### C Prototype
`void cur_obj_spin_all_dimensions(f32 arg0, f32 arg1);`

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

## [obj_bounce_off_walls_edges_objects](#obj_bounce_off_walls_edges_objects)

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

## [obj_check_attacks](#obj_check_attacks)

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

## [obj_compute_vel_from_move_pitch](#obj_compute_vel_from_move_pitch)

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

## [obj_die_if_health_non_positive](#obj_die_if_health_non_positive)

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

## [obj_face_pitch_approach](#obj_face_pitch_approach)

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

## [obj_face_roll_approach](#obj_face_roll_approach)

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

## [obj_face_yaw_approach](#obj_face_yaw_approach)

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

## [obj_forward_vel_approach](#obj_forward_vel_approach)

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

## [obj_get_pitch_from_vel](#obj_get_pitch_from_vel)

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

## [obj_get_pitch_to_home](#obj_get_pitch_to_home)

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

## [obj_grow_then_shrink](#obj_grow_then_shrink)

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

## [obj_is_near_to_and_facing_mario](#obj_is_near_to_and_facing_mario)

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

## [obj_is_rendering_enabled](#obj_is_rendering_enabled)

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

## [obj_move_for_one_second](#obj_move_for_one_second)

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

## [obj_move_pitch_approach](#obj_move_pitch_approach)

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

## [obj_random_fixed_turn](#obj_random_fixed_turn)

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

## [obj_resolve_collisions_and_turn](#obj_resolve_collisions_and_turn)

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

## [obj_resolve_object_collisions](#obj_resolve_object_collisions)

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

## [obj_roll_to_match_yaw_turn](#obj_roll_to_match_yaw_turn)

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

## [obj_rotate_yaw_and_bounce_off_walls](#obj_rotate_yaw_and_bounce_off_walls)

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

## [obj_set_dist_from_home](#obj_set_dist_from_home)

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

## [obj_set_knockback_action](#obj_set_knockback_action)

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

## [obj_turn_pitch_toward_mario](#obj_turn_pitch_toward_mario)

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

## [obj_unused_die](#obj_unused_die)

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

## [obj_y_vel_approach](#obj_y_vel_approach)

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

## [platform_on_track_update_pos_or_spawn_ball](#platform_on_track_update_pos_or_spawn_ball)

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

## [random_linear_offset](#random_linear_offset)

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

## [treat_far_home_as_mario](#treat_far_home_as_mario)

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

---
# functions from object_helpers.c

<br />


## [abs_angle_diff](#abs_angle_diff)

### Lua Example
`local integerValue = abs_angle_diff(x0, x1)`

### Parameters
| Field | Type |
| ----- | ---- |
| x0 | `integer` |
| x1 | `integer` |

### Returns
- `integer`

### C Prototype
`s16 abs_angle_diff(s16 x0, s16 x1);`

[:arrow_up_small:](#)

<br />

## [apply_drag_to_value](#apply_drag_to_value)

### Lua Example
`apply_drag_to_value(value, dragStrength)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `Pointer` <`number`> |
| dragStrength | `number` |

### Returns
- None

### C Prototype
`void apply_drag_to_value(f32 *value, f32 dragStrength);`

[:arrow_up_small:](#)

<br />

## [approach_f32_signed](#approach_f32_signed)

### Lua Example
`local integerValue = approach_f32_signed(value, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `Pointer` <`number`> |
| target | `number` |
| increment | `number` |

### Returns
- `integer`

### C Prototype
`s32 approach_f32_signed(f32 *value, f32 target, f32 increment);`

[:arrow_up_small:](#)

<br />

## [approach_f32_symmetric](#approach_f32_symmetric)

### Lua Example
`local numberValue = approach_f32_symmetric(value, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `number` |
| target | `number` |
| increment | `number` |

### Returns
- `number`

### C Prototype
`f32 approach_f32_symmetric(f32 value, f32 target, f32 increment);`

[:arrow_up_small:](#)

<br />

## [approach_s16_symmetric](#approach_s16_symmetric)

### Lua Example
`local integerValue = approach_s16_symmetric(value, target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |
| target | `integer` |
| increment | `integer` |

### Returns
- `integer`

### C Prototype
`s16 approach_s16_symmetric(s16 value, s16 target, s16 increment);`

[:arrow_up_small:](#)

<br />

## [bhv_dust_smoke_loop](#bhv_dust_smoke_loop)

### Lua Example
`bhv_dust_smoke_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_dust_smoke_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_init_room](#bhv_init_room)

### Lua Example
`bhv_init_room()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_init_room(void);`

[:arrow_up_small:](#)

<br />

## [bit_shift_left](#bit_shift_left)

### Lua Example
`local integerValue = bit_shift_left(a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 bit_shift_left(s32 a0);`

[:arrow_up_small:](#)

<br />

## [chain_segment_init](#chain_segment_init)

### Lua Example
`chain_segment_init(segment)`

### Parameters
| Field | Type |
| ----- | ---- |
| segment | [ChainSegment](structs.md#ChainSegment) |

### Returns
- None

### C Prototype
`void chain_segment_init(struct ChainSegment *segment);`

[:arrow_up_small:](#)

<br />

## [clear_move_flag](#clear_move_flag)

### Lua Example
`local integerValue = clear_move_flag(bitSet, flag)`

### Parameters
| Field | Type |
| ----- | ---- |
| bitSet | `Pointer` <`integer`> |
| flag | `integer` |

### Returns
- `integer`

### C Prototype
`s32 clear_move_flag(u32 *bitSet, s32 flag);`

[:arrow_up_small:](#)

<br />

## [clear_time_stop_flags](#clear_time_stop_flags)

### Lua Example
`clear_time_stop_flags(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void clear_time_stop_flags(s32 flags);`

[:arrow_up_small:](#)

<br />

## [count_objects_with_behavior](#count_objects_with_behavior)

### Lua Example
`local integerValue = count_objects_with_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `integer`

### C Prototype
`s32 count_objects_with_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [count_unimportant_objects](#count_unimportant_objects)

### Lua Example
`local integerValue = count_unimportant_objects()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 count_unimportant_objects(void);`

[:arrow_up_small:](#)

<br />

## [create_transformation_from_matrices](#create_transformation_from_matrices)

### Lua Example
`create_transformation_from_matrices(a0, a1, a2)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `Mat4` |
| a1 | `Mat4` |
| a2 | `Mat4` |

### Returns
- None

### C Prototype
`void create_transformation_from_matrices(Mat4 a0, Mat4 a1, Mat4 a2);`

[:arrow_up_small:](#)

<br />

## [cur_obj_abs_y_dist_to_home](#cur_obj_abs_y_dist_to_home)

### Lua Example
`local numberValue = cur_obj_abs_y_dist_to_home()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 cur_obj_abs_y_dist_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_advance_looping_anim](#cur_obj_advance_looping_anim)

### Lua Example
`local integerValue = cur_obj_advance_looping_anim()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_advance_looping_anim(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_align_gfx_with_floor](#cur_obj_align_gfx_with_floor)

### Lua Example
`cur_obj_align_gfx_with_floor()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_align_gfx_with_floor(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_angle_to_home](#cur_obj_angle_to_home)

### Lua Example
`local integerValue = cur_obj_angle_to_home()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 cur_obj_angle_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_apply_drag_xz](#cur_obj_apply_drag_xz)

### Lua Example
`cur_obj_apply_drag_xz(dragStrength)`

### Parameters
| Field | Type |
| ----- | ---- |
| dragStrength | `number` |

### Returns
- None

### C Prototype
`void cur_obj_apply_drag_xz(f32 dragStrength);`

[:arrow_up_small:](#)

<br />

## [cur_obj_become_intangible](#cur_obj_become_intangible)

### Lua Example
`cur_obj_become_intangible()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_become_intangible(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_become_tangible](#cur_obj_become_tangible)

### Lua Example
`cur_obj_become_tangible()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_become_tangible(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_can_mario_activate_textbox](#cur_obj_can_mario_activate_textbox)

### Lua Example
`local integerValue = cur_obj_can_mario_activate_textbox(m, radius, height, unused)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| radius | `number` |
| height | `number` |
| unused | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_can_mario_activate_textbox(struct MarioState* m, f32 radius, f32 height, UNUSED s32 unused);`

[:arrow_up_small:](#)

<br />

## [cur_obj_can_mario_activate_textbox_2](#cur_obj_can_mario_activate_textbox_2)

### Lua Example
`local integerValue = cur_obj_can_mario_activate_textbox_2(m, radius, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| radius | `number` |
| height | `number` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_can_mario_activate_textbox_2(struct MarioState* m, f32 radius, f32 height);`

[:arrow_up_small:](#)

<br />

## [cur_obj_change_action](#cur_obj_change_action)

### Lua Example
`cur_obj_change_action(action)`

### Parameters
| Field | Type |
| ----- | ---- |
| action | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_change_action(s32 action);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_anim_frame](#cur_obj_check_anim_frame)

### Lua Example
`local integerValue = cur_obj_check_anim_frame(frame)`

### Parameters
| Field | Type |
| ----- | ---- |
| frame | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_anim_frame(s32 frame);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_anim_frame_in_range](#cur_obj_check_anim_frame_in_range)

### Lua Example
`local integerValue = cur_obj_check_anim_frame_in_range(startFrame, rangeLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| startFrame | `integer` |
| rangeLength | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_anim_frame_in_range(s32 startFrame, s32 rangeLength);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_frame_prior_current_frame](#cur_obj_check_frame_prior_current_frame)

### Lua Example
`local integerValue = cur_obj_check_frame_prior_current_frame(a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_frame_prior_current_frame(s16 *a0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_grabbed_mario](#cur_obj_check_grabbed_mario)

### Lua Example
`local integerValue = cur_obj_check_grabbed_mario()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_grabbed_mario(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_if_at_animation_end](#cur_obj_check_if_at_animation_end)

### Lua Example
`local integerValue = cur_obj_check_if_at_animation_end()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_if_at_animation_end(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_if_near_animation_end](#cur_obj_check_if_near_animation_end)

### Lua Example
`local integerValue = cur_obj_check_if_near_animation_end()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_if_near_animation_end(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_check_interacted](#cur_obj_check_interacted)

### Lua Example
`local integerValue = cur_obj_check_interacted()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_check_interacted(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_clear_interact_status_flag](#cur_obj_clear_interact_status_flag)

### Lua Example
`local integerValue = cur_obj_clear_interact_status_flag(flag)`

### Parameters
| Field | Type |
| ----- | ---- |
| flag | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_clear_interact_status_flag(s32 flag);`

[:arrow_up_small:](#)

<br />

## [cur_obj_compute_vel_xz](#cur_obj_compute_vel_xz)

### Lua Example
`cur_obj_compute_vel_xz()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_compute_vel_xz(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_count_objects_with_behavior](#cur_obj_count_objects_with_behavior)

### Lua Example
`local integerValue = cur_obj_count_objects_with_behavior(behavior, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |
| dist | `number` |

### Returns
- `integer`

### C Prototype
`u16 cur_obj_count_objects_with_behavior(const BehaviorScript* behavior, f32 dist);`

[:arrow_up_small:](#)

<br />

## [cur_obj_detect_steep_floor](#cur_obj_detect_steep_floor)

### Lua Example
`local integerValue = cur_obj_detect_steep_floor(steepAngleDegrees)`

### Parameters
| Field | Type |
| ----- | ---- |
| steepAngleDegrees | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_detect_steep_floor(s16 steepAngleDegrees);`

[:arrow_up_small:](#)

<br />

## [cur_obj_disable](#cur_obj_disable)

### Lua Example
`cur_obj_disable()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_disable(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_disable_rendering](#cur_obj_disable_rendering)

### Lua Example
`cur_obj_disable_rendering()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_disable_rendering(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_disable_rendering_and_become_intangible](#cur_obj_disable_rendering_and_become_intangible)

### Lua Example
`cur_obj_disable_rendering_and_become_intangible(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void cur_obj_disable_rendering_and_become_intangible(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [cur_obj_dist_to_nearest_object_with_behavior](#cur_obj_dist_to_nearest_object_with_behavior)

### Lua Example
`local numberValue = cur_obj_dist_to_nearest_object_with_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `number`

### C Prototype
`f32 cur_obj_dist_to_nearest_object_with_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [cur_obj_enable_rendering](#cur_obj_enable_rendering)

### Lua Example
`cur_obj_enable_rendering()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_enable_rendering(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_enable_rendering_2](#cur_obj_enable_rendering_2)

### Lua Example
`cur_obj_enable_rendering_2()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_enable_rendering_2(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_enable_rendering_and_become_tangible](#cur_obj_enable_rendering_and_become_tangible)

### Lua Example
`cur_obj_enable_rendering_and_become_tangible(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void cur_obj_enable_rendering_and_become_tangible(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [cur_obj_enable_rendering_if_mario_in_room](#cur_obj_enable_rendering_if_mario_in_room)

### Lua Example
`cur_obj_enable_rendering_if_mario_in_room()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_enable_rendering_if_mario_in_room(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_end_dialog](#cur_obj_end_dialog)

### Lua Example
`cur_obj_end_dialog(m, dialogFlags, dialogResult)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| dialogFlags | `integer` |
| dialogResult | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_end_dialog(struct MarioState* m, s32 dialogFlags, s32 dialogResult);`

[:arrow_up_small:](#)

<br />

## [cur_obj_extend_animation_if_at_end](#cur_obj_extend_animation_if_at_end)

### Lua Example
`cur_obj_extend_animation_if_at_end()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_extend_animation_if_at_end(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_find_nearby_held_actor](#cur_obj_find_nearby_held_actor)

### Lua Example
`local ObjectValue = cur_obj_find_nearby_held_actor(behavior, maxDist)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |
| maxDist | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *cur_obj_find_nearby_held_actor(const BehaviorScript *behavior, f32 maxDist);`

[:arrow_up_small:](#)

<br />

## [cur_obj_find_nearest_object_with_behavior](#cur_obj_find_nearest_object_with_behavior)

### Lua Example
`local ObjectValue = cur_obj_find_nearest_object_with_behavior(behavior, dist)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |
| dist | `Pointer` <`number`> |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *cur_obj_find_nearest_object_with_behavior(const BehaviorScript *behavior, f32 *dist);`

[:arrow_up_small:](#)

<br />

## [cur_obj_find_nearest_pole](#cur_obj_find_nearest_pole)

### Lua Example
`local ObjectValue = cur_obj_find_nearest_pole()`

### Parameters
- None

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* cur_obj_find_nearest_pole(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_follow_path](#cur_obj_follow_path)

### Lua Example
`local integerValue = cur_obj_follow_path(unusedArg)`

### Parameters
| Field | Type |
| ----- | ---- |
| unusedArg | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_follow_path(UNUSED s32 unusedArg);`

[:arrow_up_small:](#)

<br />

## [cur_obj_forward_vel_approach_upward](#cur_obj_forward_vel_approach_upward)

### Lua Example
`cur_obj_forward_vel_approach_upward(target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `number` |
| increment | `number` |

### Returns
- None

### C Prototype
`void cur_obj_forward_vel_approach_upward(f32 target, f32 increment);`

[:arrow_up_small:](#)

<br />

## [cur_obj_get_dropped](#cur_obj_get_dropped)

### Lua Example
`cur_obj_get_dropped()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_get_dropped(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_get_thrown_or_placed](#cur_obj_get_thrown_or_placed)

### Lua Example
`cur_obj_get_thrown_or_placed(forwardVel, velY, thrownAction)`

### Parameters
| Field | Type |
| ----- | ---- |
| forwardVel | `number` |
| velY | `number` |
| thrownAction | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_get_thrown_or_placed(f32 forwardVel, f32 velY, s32 thrownAction);`

[:arrow_up_small:](#)

<br />

## [cur_obj_has_behavior](#cur_obj_has_behavior)

### Lua Example
`local integerValue = cur_obj_has_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_has_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [cur_obj_has_model](#cur_obj_has_model)

### Lua Example
`local integerValue = cur_obj_has_model(modelID)`

### Parameters
| Field | Type |
| ----- | ---- |
| modelID | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_has_model(u16 modelID);`

[:arrow_up_small:](#)

<br />

## [cur_obj_hide](#cur_obj_hide)

### Lua Example
`cur_obj_hide()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_hide(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_hide_if_mario_far_away_y](#cur_obj_hide_if_mario_far_away_y)

### Lua Example
`local integerValue = cur_obj_hide_if_mario_far_away_y(distY)`

### Parameters
| Field | Type |
| ----- | ---- |
| distY | `number` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_hide_if_mario_far_away_y(f32 distY);`

[:arrow_up_small:](#)

<br />

## [cur_obj_if_hit_wall_bounce_away](#cur_obj_if_hit_wall_bounce_away)

### Lua Example
`cur_obj_if_hit_wall_bounce_away()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_if_hit_wall_bounce_away(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation](#cur_obj_init_animation)

### Lua Example
`cur_obj_init_animation(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_and_anim_frame](#cur_obj_init_animation_and_anim_frame)

### Lua Example
`cur_obj_init_animation_and_anim_frame(animIndex, animFrame)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |
| animFrame | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation_and_anim_frame(s32 animIndex, s32 animFrame);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_and_check_if_near_end](#cur_obj_init_animation_and_check_if_near_end)

### Lua Example
`local integerValue = cur_obj_init_animation_and_check_if_near_end(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_init_animation_and_check_if_near_end(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_and_extend_if_at_end](#cur_obj_init_animation_and_extend_if_at_end)

### Lua Example
`cur_obj_init_animation_and_extend_if_at_end(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation_and_extend_if_at_end(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_with_accel_and_sound](#cur_obj_init_animation_with_accel_and_sound)

### Lua Example
`cur_obj_init_animation_with_accel_and_sound(animIndex, accel)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |
| accel | `number` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation_with_accel_and_sound(s32 animIndex, f32 accel);`

[:arrow_up_small:](#)

<br />

## [cur_obj_init_animation_with_sound](#cur_obj_init_animation_with_sound)

### Lua Example
`cur_obj_init_animation_with_sound(animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_init_animation_with_sound(s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [cur_obj_is_any_player_on_platform](#cur_obj_is_any_player_on_platform)

### Lua Example
`local integerValue = cur_obj_is_any_player_on_platform()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_is_any_player_on_platform(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_is_mario_ground_pounding_platform](#cur_obj_is_mario_ground_pounding_platform)

### Lua Example
`local integerValue = cur_obj_is_mario_ground_pounding_platform()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_is_mario_ground_pounding_platform(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_is_mario_on_platform](#cur_obj_is_mario_on_platform)

### Lua Example
`local integerValue = cur_obj_is_mario_on_platform()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_is_mario_on_platform(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_lateral_dist_from_mario_to_home](#cur_obj_lateral_dist_from_mario_to_home)

### Lua Example
`local numberValue = cur_obj_lateral_dist_from_mario_to_home()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 cur_obj_lateral_dist_from_mario_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_lateral_dist_from_obj_to_home](#cur_obj_lateral_dist_from_obj_to_home)

### Lua Example
`local numberValue = cur_obj_lateral_dist_from_obj_to_home(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- `number`

### C Prototype
`f32 cur_obj_lateral_dist_from_obj_to_home(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [cur_obj_lateral_dist_to_home](#cur_obj_lateral_dist_to_home)

### Lua Example
`local numberValue = cur_obj_lateral_dist_to_home()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 cur_obj_lateral_dist_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_mario_far_away](#cur_obj_mario_far_away)

### Lua Example
`local integerValue = cur_obj_mario_far_away()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_mario_far_away(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_after_thrown_or_dropped](#cur_obj_move_after_thrown_or_dropped)

### Lua Example
`cur_obj_move_after_thrown_or_dropped(forwardVel, velY)`

### Parameters
| Field | Type |
| ----- | ---- |
| forwardVel | `number` |
| velY | `number` |

### Returns
- None

### C Prototype
`void cur_obj_move_after_thrown_or_dropped(f32 forwardVel, f32 velY);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_standard](#cur_obj_move_standard)

### Lua Example
`cur_obj_move_standard(steepSlopeAngleDegrees)`

### Parameters
| Field | Type |
| ----- | ---- |
| steepSlopeAngleDegrees | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_move_standard(s16 steepSlopeAngleDegrees);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_up_and_down](#cur_obj_move_up_and_down)

### Lua Example
`local integerValue = cur_obj_move_up_and_down(a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_move_up_and_down(s32 a0);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_update_ground_air_flags](#cur_obj_move_update_ground_air_flags)

### Lua Example
`cur_obj_move_update_ground_air_flags(gravity, bounciness)`

### Parameters
| Field | Type |
| ----- | ---- |
| gravity | `number` |
| bounciness | `number` |

### Returns
- None

### C Prototype
`void cur_obj_move_update_ground_air_flags(UNUSED f32 gravity, f32 bounciness);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_update_underwater_flags](#cur_obj_move_update_underwater_flags)

### Lua Example
`cur_obj_move_update_underwater_flags()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_update_underwater_flags(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_using_fvel_and_gravity](#cur_obj_move_using_fvel_and_gravity)

### Lua Example
`cur_obj_move_using_fvel_and_gravity()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_using_fvel_and_gravity(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_using_vel](#cur_obj_move_using_vel)

### Lua Example
`cur_obj_move_using_vel()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_using_vel(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_using_vel_and_gravity](#cur_obj_move_using_vel_and_gravity)

### Lua Example
`cur_obj_move_using_vel_and_gravity()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_using_vel_and_gravity(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_xz](#cur_obj_move_xz)

### Lua Example
`local integerValue = cur_obj_move_xz(steepSlopeNormalY, careAboutEdgesAndSteepSlopes)`

### Parameters
| Field | Type |
| ----- | ---- |
| steepSlopeNormalY | `number` |
| careAboutEdgesAndSteepSlopes | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_move_xz(f32 steepSlopeNormalY, s32 careAboutEdgesAndSteepSlopes);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_xz_using_fvel_and_yaw](#cur_obj_move_xz_using_fvel_and_yaw)

### Lua Example
`cur_obj_move_xz_using_fvel_and_yaw()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_xz_using_fvel_and_yaw(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_y](#cur_obj_move_y)

### Lua Example
`cur_obj_move_y(gravity, bounciness, buoyancy)`

### Parameters
| Field | Type |
| ----- | ---- |
| gravity | `number` |
| bounciness | `number` |
| buoyancy | `number` |

### Returns
- None

### C Prototype
`void cur_obj_move_y(f32 gravity, f32 bounciness, f32 buoyancy);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_y_and_get_water_level](#cur_obj_move_y_and_get_water_level)

### Lua Example
`local numberValue = cur_obj_move_y_and_get_water_level(gravity, buoyancy)`

### Parameters
| Field | Type |
| ----- | ---- |
| gravity | `number` |
| buoyancy | `number` |

### Returns
- `number`

### C Prototype
`f32 cur_obj_move_y_and_get_water_level(f32 gravity, f32 buoyancy);`

[:arrow_up_small:](#)

<br />

## [cur_obj_move_y_with_terminal_vel](#cur_obj_move_y_with_terminal_vel)

### Lua Example
`cur_obj_move_y_with_terminal_vel()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_move_y_with_terminal_vel(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_nearest_object_with_behavior](#cur_obj_nearest_object_with_behavior)

### Lua Example
`local ObjectValue = cur_obj_nearest_object_with_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *cur_obj_nearest_object_with_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [cur_obj_outside_home_rectangle](#cur_obj_outside_home_rectangle)

### Lua Example
`local integerValue = cur_obj_outside_home_rectangle(minX, maxX, minZ, maxZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| minX | `number` |
| maxX | `number` |
| minZ | `number` |
| maxZ | `number` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_outside_home_rectangle(f32 minX, f32 maxX, f32 minZ, f32 maxZ);`

[:arrow_up_small:](#)

<br />

## [cur_obj_outside_home_square](#cur_obj_outside_home_square)

### Lua Example
`local integerValue = cur_obj_outside_home_square(halfLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| halfLength | `number` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_outside_home_square(f32 halfLength);`

[:arrow_up_small:](#)

<br />

## [cur_obj_push_mario_away](#cur_obj_push_mario_away)

### Lua Example
`cur_obj_push_mario_away(radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| radius | `number` |

### Returns
- None

### C Prototype
`void cur_obj_push_mario_away(f32 radius);`

[:arrow_up_small:](#)

<br />

## [cur_obj_push_mario_away_from_cylinder](#cur_obj_push_mario_away_from_cylinder)

### Lua Example
`cur_obj_push_mario_away_from_cylinder(radius, extentY)`

### Parameters
| Field | Type |
| ----- | ---- |
| radius | `number` |
| extentY | `number` |

### Returns
- None

### C Prototype
`void cur_obj_push_mario_away_from_cylinder(f32 radius, f32 extentY);`

[:arrow_up_small:](#)

<br />

## [cur_obj_reflect_move_angle_off_wall](#cur_obj_reflect_move_angle_off_wall)

### Lua Example
`local integerValue = cur_obj_reflect_move_angle_off_wall()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 cur_obj_reflect_move_angle_off_wall(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_reset_timer_and_subaction](#cur_obj_reset_timer_and_subaction)

### Lua Example
`cur_obj_reset_timer_and_subaction()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_reset_timer_and_subaction(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_resolve_wall_collisions](#cur_obj_resolve_wall_collisions)

### Lua Example
`local integerValue = cur_obj_resolve_wall_collisions()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_resolve_wall_collisions(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_reverse_animation](#cur_obj_reverse_animation)

### Lua Example
`cur_obj_reverse_animation()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_reverse_animation(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_rotate_face_angle_using_vel](#cur_obj_rotate_face_angle_using_vel)

### Lua Example
`cur_obj_rotate_face_angle_using_vel()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_rotate_face_angle_using_vel(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_rotate_move_angle_using_vel](#cur_obj_rotate_move_angle_using_vel)

### Lua Example
`cur_obj_rotate_move_angle_using_vel()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_rotate_move_angle_using_vel(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_rotate_yaw_toward](#cur_obj_rotate_yaw_toward)

### Lua Example
`local integerValue = cur_obj_rotate_yaw_toward(target, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| target | `integer` |
| increment | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_rotate_yaw_toward(s16 target, s16 increment);`

[:arrow_up_small:](#)

<br />

## [cur_obj_scale](#cur_obj_scale)

### Lua Example
`cur_obj_scale(scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| scale | `number` |

### Returns
- None

### C Prototype
`void cur_obj_scale(f32 scale);`

[:arrow_up_small:](#)

<br />

## [cur_obj_scale_over_time](#cur_obj_scale_over_time)

### Lua Example
`cur_obj_scale_over_time(a0, a1, sp10, sp14)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `integer` |
| a1 | `integer` |
| sp10 | `number` |
| sp14 | `number` |

### Returns
- None

### C Prototype
`void cur_obj_scale_over_time(s32 a0, s32 a1, f32 sp10, f32 sp14);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_behavior](#cur_obj_set_behavior)

### Lua Example
`cur_obj_set_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- None

### C Prototype
`void cur_obj_set_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_billboard_if_vanilla_cam](#cur_obj_set_billboard_if_vanilla_cam)

### Lua Example
`cur_obj_set_billboard_if_vanilla_cam()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_billboard_if_vanilla_cam(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_face_angle_to_move_angle](#cur_obj_set_face_angle_to_move_angle)

### Lua Example
`cur_obj_set_face_angle_to_move_angle()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_face_angle_to_move_angle(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_hitbox_and_die_if_attacked](#cur_obj_set_hitbox_and_die_if_attacked)

### Lua Example
`local integerValue = cur_obj_set_hitbox_and_die_if_attacked(hitbox, deathSound, noLootCoins)`

### Parameters
| Field | Type |
| ----- | ---- |
| hitbox | [ObjectHitbox](structs.md#ObjectHitbox) |
| deathSound | `integer` |
| noLootCoins | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_set_hitbox_and_die_if_attacked(struct ObjectHitbox *hitbox, s32 deathSound, s32 noLootCoins);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_hitbox_radius_and_height](#cur_obj_set_hitbox_radius_and_height)

### Lua Example
`cur_obj_set_hitbox_radius_and_height(radius, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| radius | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_hitbox_radius_and_height(f32 radius, f32 height);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_home_once](#cur_obj_set_home_once)

### Lua Example
`cur_obj_set_home_once()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_home_once(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_hurtbox_radius_and_height](#cur_obj_set_hurtbox_radius_and_height)

### Lua Example
`cur_obj_set_hurtbox_radius_and_height(radius, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| radius | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_hurtbox_radius_and_height(f32 radius, f32 height);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_relative](#cur_obj_set_pos_relative)

### Lua Example
`cur_obj_set_pos_relative(other, dleft, dy, dforward)`

### Parameters
| Field | Type |
| ----- | ---- |
| other | [Object](structs.md#Object) |
| dleft | `number` |
| dy | `number` |
| dforward | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_pos_relative(struct Object *other, f32 dleft, f32 dy, f32 dforward);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_relative_to_parent](#cur_obj_set_pos_relative_to_parent)

### Lua Example
`cur_obj_set_pos_relative_to_parent(dleft, dy, dforward)`

### Parameters
| Field | Type |
| ----- | ---- |
| dleft | `number` |
| dy | `number` |
| dforward | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_pos_relative_to_parent(f32 dleft, f32 dy, f32 dforward);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_to_home](#cur_obj_set_pos_to_home)

### Lua Example
`cur_obj_set_pos_to_home()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_pos_to_home(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_to_home_and_stop](#cur_obj_set_pos_to_home_and_stop)

### Lua Example
`cur_obj_set_pos_to_home_and_stop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_pos_to_home_and_stop(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_to_home_with_debug](#cur_obj_set_pos_to_home_with_debug)

### Lua Example
`cur_obj_set_pos_to_home_with_debug()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_pos_to_home_with_debug(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_pos_via_transform](#cur_obj_set_pos_via_transform)

### Lua Example
`cur_obj_set_pos_via_transform()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_set_pos_via_transform(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_vel_from_mario_vel](#cur_obj_set_vel_from_mario_vel)

### Lua Example
`cur_obj_set_vel_from_mario_vel(m, f12, f14)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| f12 | `number` |
| f14 | `number` |

### Returns
- None

### C Prototype
`void cur_obj_set_vel_from_mario_vel(struct MarioState* m, f32 f12, f32 f14);`

[:arrow_up_small:](#)

<br />

## [cur_obj_set_y_vel_and_animation](#cur_obj_set_y_vel_and_animation)

### Lua Example
`cur_obj_set_y_vel_and_animation(sp18, sp1C)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp18 | `number` |
| sp1C | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_set_y_vel_and_animation(f32 sp18, s32 sp1C);`

[:arrow_up_small:](#)

<br />

## [cur_obj_shake_screen](#cur_obj_shake_screen)

### Lua Example
`cur_obj_shake_screen(shake)`

### Parameters
| Field | Type |
| ----- | ---- |
| shake | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_shake_screen(s32 shake);`

[:arrow_up_small:](#)

<br />

## [cur_obj_shake_y](#cur_obj_shake_y)

### Lua Example
`cur_obj_shake_y(amount)`

### Parameters
| Field | Type |
| ----- | ---- |
| amount | `number` |

### Returns
- None

### C Prototype
`void cur_obj_shake_y(f32 amount);`

[:arrow_up_small:](#)

<br />

## [cur_obj_shake_y_until](#cur_obj_shake_y_until)

### Lua Example
`local integerValue = cur_obj_shake_y_until(cycles, amount)`

### Parameters
| Field | Type |
| ----- | ---- |
| cycles | `integer` |
| amount | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_shake_y_until(s32 cycles, s32 amount);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spawn_loot_blue_coin](#cur_obj_spawn_loot_blue_coin)

### Lua Example
`cur_obj_spawn_loot_blue_coin()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_spawn_loot_blue_coin(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spawn_loot_coin_at_mario_pos](#cur_obj_spawn_loot_coin_at_mario_pos)

### Lua Example
`cur_obj_spawn_loot_coin_at_mario_pos(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void cur_obj_spawn_loot_coin_at_mario_pos(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spawn_particles](#cur_obj_spawn_particles)

### Lua Example
`cur_obj_spawn_particles(info)`

### Parameters
| Field | Type |
| ----- | ---- |
| info | [SpawnParticlesInfo](structs.md#SpawnParticlesInfo) |

### Returns
- None

### C Prototype
`void cur_obj_spawn_particles(struct SpawnParticlesInfo *info);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spawn_star_at_y_offset](#cur_obj_spawn_star_at_y_offset)

### Lua Example
`cur_obj_spawn_star_at_y_offset(targetX, targetY, targetZ, offsetY)`

### Parameters
| Field | Type |
| ----- | ---- |
| targetX | `number` |
| targetY | `number` |
| targetZ | `number` |
| offsetY | `number` |

### Returns
- None

### C Prototype
`void cur_obj_spawn_star_at_y_offset(f32 targetX, f32 targetY, f32 targetZ, f32 offsetY);`

[:arrow_up_small:](#)

<br />

## [cur_obj_start_cam_event](#cur_obj_start_cam_event)

### Lua Example
`cur_obj_start_cam_event(obj, cameraEvent)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| cameraEvent | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_start_cam_event(UNUSED struct Object *obj, s32 cameraEvent);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unhide](#cur_obj_unhide)

### Lua Example
`cur_obj_unhide()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_unhide(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unrender_and_reset_state](#cur_obj_unrender_and_reset_state)

### Lua Example
`cur_obj_unrender_and_reset_state(sp18, sp1C)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp18 | `integer` |
| sp1C | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_unrender_and_reset_state(s32 sp18, s32 sp1C);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unused_init_on_floor](#cur_obj_unused_init_on_floor)

### Lua Example
`cur_obj_unused_init_on_floor()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_unused_init_on_floor(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unused_play_footstep_sound](#cur_obj_unused_play_footstep_sound)

### Lua Example
`cur_obj_unused_play_footstep_sound(animFrame1, animFrame2, sound)`

### Parameters
| Field | Type |
| ----- | ---- |
| animFrame1 | `integer` |
| animFrame2 | `integer` |
| sound | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_unused_play_footstep_sound(s32 animFrame1, s32 animFrame2, s32 sound);`

[:arrow_up_small:](#)

<br />

## [cur_obj_unused_resolve_wall_collisions](#cur_obj_unused_resolve_wall_collisions)

### Lua Example
`cur_obj_unused_resolve_wall_collisions(offsetY, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| offsetY | `number` |
| radius | `number` |

### Returns
- None

### C Prototype
`void cur_obj_unused_resolve_wall_collisions(f32 offsetY, f32 radius);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor](#cur_obj_update_floor)

### Lua Example
`cur_obj_update_floor()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_update_floor(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor_and_resolve_wall_collisions](#cur_obj_update_floor_and_resolve_wall_collisions)

### Lua Example
`cur_obj_update_floor_and_resolve_wall_collisions(steepSlopeDegrees)`

### Parameters
| Field | Type |
| ----- | ---- |
| steepSlopeDegrees | `integer` |

### Returns
- None

### C Prototype
`void cur_obj_update_floor_and_resolve_wall_collisions(s16 steepSlopeDegrees);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor_and_walls](#cur_obj_update_floor_and_walls)

### Lua Example
`cur_obj_update_floor_and_walls()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_update_floor_and_walls(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor_height](#cur_obj_update_floor_height)

### Lua Example
`cur_obj_update_floor_height()`

### Parameters
- None

### Returns
- None

### C Prototype
`void cur_obj_update_floor_height(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_update_floor_height_and_get_floor](#cur_obj_update_floor_height_and_get_floor)

### Lua Example
`local SurfaceValue = cur_obj_update_floor_height_and_get_floor()`

### Parameters
- None

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface *cur_obj_update_floor_height_and_get_floor(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_wait_then_blink](#cur_obj_wait_then_blink)

### Lua Example
`local integerValue = cur_obj_wait_then_blink(timeUntilBlinking, numBlinks)`

### Parameters
| Field | Type |
| ----- | ---- |
| timeUntilBlinking | `integer` |
| numBlinks | `integer` |

### Returns
- `integer`

### C Prototype
`s32 cur_obj_wait_then_blink(s32 timeUntilBlinking, s32 numBlinks);`

[:arrow_up_small:](#)

<br />

## [cur_obj_was_attacked_or_ground_pounded](#cur_obj_was_attacked_or_ground_pounded)

### Lua Example
`local integerValue = cur_obj_was_attacked_or_ground_pounded()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_was_attacked_or_ground_pounded(void);`

[:arrow_up_small:](#)

<br />

## [cur_obj_within_12k_bounds](#cur_obj_within_12k_bounds)

### Lua Example
`local integerValue = cur_obj_within_12k_bounds()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 cur_obj_within_12k_bounds(void);`

[:arrow_up_small:](#)

<br />

## [disable_time_stop](#disable_time_stop)

### Lua Example
`disable_time_stop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void disable_time_stop(void);`

[:arrow_up_small:](#)

<br />

## [disable_time_stop_including_mario](#disable_time_stop_including_mario)

### Lua Example
`disable_time_stop_including_mario()`

### Parameters
- None

### Returns
- None

### C Prototype
`void disable_time_stop_including_mario(void);`

[:arrow_up_small:](#)

<br />

## [dist_between_object_and_point](#dist_between_object_and_point)

### Lua Example
`local numberValue = dist_between_object_and_point(obj, pointX, pointY, pointZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| pointX | `number` |
| pointY | `number` |
| pointZ | `number` |

### Returns
- `number`

### C Prototype
`f32 dist_between_object_and_point(struct Object *obj, f32 pointX, f32 pointY, f32 pointZ);`

[:arrow_up_small:](#)

<br />

## [dist_between_objects](#dist_between_objects)

### Lua Example
`local numberValue = dist_between_objects(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- `number`

### C Prototype
`f32 dist_between_objects(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [enable_time_stop](#enable_time_stop)

### Lua Example
`enable_time_stop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void enable_time_stop(void);`

[:arrow_up_small:](#)

<br />

## [enable_time_stop_if_alone](#enable_time_stop_if_alone)

### Lua Example
`enable_time_stop_if_alone()`

### Parameters
- None

### Returns
- None

### C Prototype
`void enable_time_stop_if_alone(void);`

[:arrow_up_small:](#)

<br />

## [enable_time_stop_including_mario](#enable_time_stop_including_mario)

### Lua Example
`enable_time_stop_including_mario()`

### Parameters
- None

### Returns
- None

### C Prototype
`void enable_time_stop_including_mario(void);`

[:arrow_up_small:](#)

<br />

## [find_object_with_behavior](#find_object_with_behavior)

### Lua Example
`local ObjectValue = find_object_with_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *find_object_with_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [find_unimportant_object](#find_unimportant_object)

### Lua Example
`local ObjectValue = find_unimportant_object()`

### Parameters
- None

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *find_unimportant_object(void);`

[:arrow_up_small:](#)

<br />

## [geo_offset_klepto_debug](#geo_offset_klepto_debug)

### Lua Example
`local integerValue = geo_offset_klepto_debug(callContext, a1, sp8)`

### Parameters
| Field | Type |
| ----- | ---- |
| callContext | `integer` |
| a1 | [GraphNode](structs.md#GraphNode) |
| sp8 | `integer` |

### Returns
- `integer`

### C Prototype
`s32 geo_offset_klepto_debug(s32 callContext, struct GraphNode *a1, UNUSED s32 sp8);`

[:arrow_up_small:](#)

<br />

## [get_object_list_from_behavior](#get_object_list_from_behavior)

### Lua Example
`local integerValue = get_object_list_from_behavior(behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `integer`

### C Prototype
`u32 get_object_list_from_behavior(const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [get_trajectory_length](#get_trajectory_length)

### Lua Example
`local integerValue = get_trajectory_length(trajectory)`

### Parameters
| Field | Type |
| ----- | ---- |
| trajectory | `Pointer` <`Trajectory`> |

### Returns
- `integer`

### C Prototype
`s32 get_trajectory_length(Trajectory* trajectory);`

[:arrow_up_small:](#)

<br />

## [increment_velocity_toward_range](#increment_velocity_toward_range)

### Lua Example
`local numberValue = increment_velocity_toward_range(value, center, zeroThreshold, increment)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `number` |
| center | `number` |
| zeroThreshold | `number` |
| increment | `number` |

### Returns
- `number`

### C Prototype
`f32 increment_velocity_toward_range(f32 value, f32 center, f32 zeroThreshold, f32 increment);`

[:arrow_up_small:](#)

<br />

## [is_item_in_array](#is_item_in_array)

### Lua Example
`local integerValue = is_item_in_array(item, array)`

### Parameters
| Field | Type |
| ----- | ---- |
| item | `integer` |
| array | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 is_item_in_array(s8 item, s8 *array);`

[:arrow_up_small:](#)

<br />

## [is_mario_moving_fast_or_in_air](#is_mario_moving_fast_or_in_air)

### Lua Example
`local integerValue = is_mario_moving_fast_or_in_air(speedThreshold)`

### Parameters
| Field | Type |
| ----- | ---- |
| speedThreshold | `integer` |

### Returns
- `integer`

### C Prototype
`s32 is_mario_moving_fast_or_in_air(s32 speedThreshold);`

[:arrow_up_small:](#)

<br />

## [lateral_dist_between_objects](#lateral_dist_between_objects)

### Lua Example
`local numberValue = lateral_dist_between_objects(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- `number`

### C Prototype
`f32 lateral_dist_between_objects(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [linear_mtxf_mul_vec3f](#linear_mtxf_mul_vec3f)

### Lua Example
`linear_mtxf_mul_vec3f(m, dst, v)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | `Mat4` |
| dst | [Vec3f](structs.md#Vec3f) |
| v | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void linear_mtxf_mul_vec3f(Mat4 m, Vec3f dst, Vec3f v);`

[:arrow_up_small:](#)

<br />

## [linear_mtxf_transpose_mul_vec3f](#linear_mtxf_transpose_mul_vec3f)

### Lua Example
`linear_mtxf_transpose_mul_vec3f(m, dst, v)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | `Mat4` |
| dst | [Vec3f](structs.md#Vec3f) |
| v | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void linear_mtxf_transpose_mul_vec3f(Mat4 m, Vec3f dst, Vec3f v);`

[:arrow_up_small:](#)

<br />

## [mario_is_dive_sliding](#mario_is_dive_sliding)

### Lua Example
`local integerValue = mario_is_dive_sliding(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_is_dive_sliding(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [mario_is_in_air_action](#mario_is_in_air_action)

### Lua Example
`local integerValue = mario_is_in_air_action(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- `integer`

### C Prototype
`s32 mario_is_in_air_action(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [mario_is_within_rectangle](#mario_is_within_rectangle)

### Lua Example
`local integerValue = mario_is_within_rectangle(minX, maxX, minZ, maxZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| minX | `integer` |
| maxX | `integer` |
| minZ | `integer` |
| maxZ | `integer` |

### Returns
- `integer`

### C Prototype
`s32 mario_is_within_rectangle(s16 minX, s16 maxX, s16 minZ, s16 maxZ);`

[:arrow_up_small:](#)

<br />

## [mario_set_flag](#mario_set_flag)

### Lua Example
`mario_set_flag(flag)`

### Parameters
| Field | Type |
| ----- | ---- |
| flag | `integer` |

### Returns
- None

### C Prototype
`void mario_set_flag(s32 flag);`

[:arrow_up_small:](#)

<br />

## [obj_angle_to_object](#obj_angle_to_object)

### Lua Example
`local integerValue = obj_angle_to_object(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s16 obj_angle_to_object(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [obj_angle_to_point](#obj_angle_to_point)

### Lua Example
`local integerValue = obj_angle_to_point(obj, pointX, pointZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| pointX | `number` |
| pointZ | `number` |

### Returns
- `integer`

### C Prototype
`s16 obj_angle_to_point(struct Object *obj, f32 pointX, f32 pointZ);`

[:arrow_up_small:](#)

<br />

## [obj_apply_scale_to_matrix](#obj_apply_scale_to_matrix)

### Lua Example
`obj_apply_scale_to_matrix(obj, dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| dst | `Mat4` |
| src | `Mat4` |

### Returns
- None

### C Prototype
`void obj_apply_scale_to_matrix(struct Object *obj, Mat4 dst, Mat4 src);`

[:arrow_up_small:](#)

<br />

## [obj_apply_scale_to_transform](#obj_apply_scale_to_transform)

### Lua Example
`obj_apply_scale_to_transform(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_apply_scale_to_transform(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_attack_collided_from_other_object](#obj_attack_collided_from_other_object)

### Lua Example
`local integerValue = obj_attack_collided_from_other_object(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s32 obj_attack_collided_from_other_object(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_become_tangible](#obj_become_tangible)

### Lua Example
`obj_become_tangible(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_become_tangible(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_build_relative_transform](#obj_build_relative_transform)

### Lua Example
`obj_build_relative_transform(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_build_relative_transform(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_build_transform_from_pos_and_angle](#obj_build_transform_from_pos_and_angle)

### Lua Example
`obj_build_transform_from_pos_and_angle(obj, posIndex, angleIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| posIndex | `integer` |
| angleIndex | `integer` |

### Returns
- None

### C Prototype
`void obj_build_transform_from_pos_and_angle(struct Object *obj, s16 posIndex, s16 angleIndex);`

[:arrow_up_small:](#)

<br />

## [obj_build_transform_relative_to_parent](#obj_build_transform_relative_to_parent)

### Lua Example
`obj_build_transform_relative_to_parent(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_build_transform_relative_to_parent(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_build_vel_from_transform](#obj_build_vel_from_transform)

### Lua Example
`obj_build_vel_from_transform(a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_build_vel_from_transform(struct Object *a0);`

[:arrow_up_small:](#)

<br />

## [obj_check_if_collided_with_object](#obj_check_if_collided_with_object)

### Lua Example
`local integerValue = obj_check_if_collided_with_object(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s32 obj_check_if_collided_with_object(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [obj_copy_angle](#obj_copy_angle)

### Lua Example
`obj_copy_angle(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_angle(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_behavior_params](#obj_copy_behavior_params)

### Lua Example
`obj_copy_behavior_params(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_behavior_params(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_graph_y_offset](#obj_copy_graph_y_offset)

### Lua Example
`obj_copy_graph_y_offset(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_graph_y_offset(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_pos](#obj_copy_pos)

### Lua Example
`obj_copy_pos(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_pos(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_pos_and_angle](#obj_copy_pos_and_angle)

### Lua Example
`obj_copy_pos_and_angle(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_pos_and_angle(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_copy_scale](#obj_copy_scale)

### Lua Example
`obj_copy_scale(dst, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dst | [Object](structs.md#Object) |
| src | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_copy_scale(struct Object *dst, struct Object *src);`

[:arrow_up_small:](#)

<br />

## [obj_create_transform_from_self](#obj_create_transform_from_self)

### Lua Example
`obj_create_transform_from_self(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_create_transform_from_self(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_explode_and_spawn_coins](#obj_explode_and_spawn_coins)

### Lua Example
`obj_explode_and_spawn_coins(sp18, sp1C)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp18 | `number` |
| sp1C | `integer` |

### Returns
- None

### C Prototype
`void obj_explode_and_spawn_coins(f32 sp18, s32 sp1C);`

[:arrow_up_small:](#)

<br />

## [obj_has_behavior](#obj_has_behavior)

### Lua Example
`local integerValue = obj_has_behavior(obj, behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- `integer`

### C Prototype
`s32 obj_has_behavior(struct Object *obj, const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [obj_init_animation](#obj_init_animation)

### Lua Example
`obj_init_animation(obj, animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void obj_init_animation(struct Object *obj, s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [obj_init_animation_with_accel_and_sound](#obj_init_animation_with_accel_and_sound)

### Lua Example
`obj_init_animation_with_accel_and_sound(obj, animIndex, accel)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| animIndex | `integer` |
| accel | `number` |

### Returns
- None

### C Prototype
`void obj_init_animation_with_accel_and_sound(struct Object *obj, s32 animIndex, f32 accel);`

[:arrow_up_small:](#)

<br />

## [obj_init_animation_with_sound](#obj_init_animation_with_sound)

### Lua Example
`obj_init_animation_with_sound(obj, animations, animIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| animations | [AnimationTable](structs.md#AnimationTable) |
| animIndex | `integer` |

### Returns
- None

### C Prototype
`void obj_init_animation_with_sound(struct Object *obj, const struct AnimationTable* animations, s32 animIndex);`

[:arrow_up_small:](#)

<br />

## [obj_is_hidden](#obj_is_hidden)

### Lua Example
`local integerValue = obj_is_hidden(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s32 obj_is_hidden(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_mark_for_deletion](#obj_mark_for_deletion)

### Lua Example
`obj_mark_for_deletion(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_mark_for_deletion(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_pitch_to_object](#obj_pitch_to_object)

### Lua Example
`local integerValue = obj_pitch_to_object(obj, target)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| target | [Object](structs.md#Object) |

### Returns
- `integer`

### C Prototype
`s16 obj_pitch_to_object(struct Object* obj, struct Object* target);`

[:arrow_up_small:](#)

<br />

## [obj_scale](#obj_scale)

### Lua Example
`obj_scale(obj, scale)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| scale | `number` |

### Returns
- None

### C Prototype
`void obj_scale(struct Object *obj, f32 scale);`

[:arrow_up_small:](#)

<br />

## [obj_scale_random](#obj_scale_random)

### Lua Example
`obj_scale_random(obj, rangeLength, minScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| rangeLength | `number` |
| minScale | `number` |

### Returns
- None

### C Prototype
`void obj_scale_random(struct Object *obj, f32 rangeLength, f32 minScale);`

[:arrow_up_small:](#)

<br />

## [obj_scale_xyz](#obj_scale_xyz)

### Lua Example
`obj_scale_xyz(obj, xScale, yScale, zScale)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| xScale | `number` |
| yScale | `number` |
| zScale | `number` |

### Returns
- None

### C Prototype
`void obj_scale_xyz(struct Object *obj, f32 xScale, f32 yScale, f32 zScale);`

[:arrow_up_small:](#)

<br />

## [obj_set_angle](#obj_set_angle)

### Lua Example
`obj_set_angle(obj, pitch, yaw, roll)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| pitch | `integer` |
| yaw | `integer` |
| roll | `integer` |

### Returns
- None

### C Prototype
`void obj_set_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll);`

[:arrow_up_small:](#)

<br />

## [obj_set_behavior](#obj_set_behavior)

### Lua Example
`obj_set_behavior(obj, behavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| behavior | `Pointer` <`BehaviorScript`> |

### Returns
- None

### C Prototype
`void obj_set_behavior(struct Object *obj, const BehaviorScript *behavior);`

[:arrow_up_small:](#)

<br />

## [obj_set_billboard](#obj_set_billboard)

### Lua Example
`obj_set_billboard(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_billboard(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_set_cylboard](#obj_set_cylboard)

### Lua Example
`obj_set_cylboard(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_cylboard(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_set_face_angle](#obj_set_face_angle)

### Lua Example
`obj_set_face_angle(obj, pitch, yaw, roll)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| pitch | `integer` |
| yaw | `integer` |
| roll | `integer` |

### Returns
- None

### C Prototype
`void obj_set_face_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll);`

[:arrow_up_small:](#)

<br />

## [obj_set_face_angle_to_move_angle](#obj_set_face_angle_to_move_angle)

### Lua Example
`obj_set_face_angle_to_move_angle(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_face_angle_to_move_angle(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_set_gfx_angle](#obj_set_gfx_angle)

### Lua Example
`obj_set_gfx_angle(obj, pitch, yaw, roll)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| pitch | `integer` |
| yaw | `integer` |
| roll | `integer` |

### Returns
- None

### C Prototype
`void obj_set_gfx_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll);`

[:arrow_up_small:](#)

<br />

## [obj_set_gfx_pos](#obj_set_gfx_pos)

### Lua Example
`obj_set_gfx_pos(obj, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- None

### C Prototype
`void obj_set_gfx_pos(struct Object *obj, f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [obj_set_gfx_pos_at_obj_pos](#obj_set_gfx_pos_at_obj_pos)

### Lua Example
`obj_set_gfx_pos_at_obj_pos(obj1, obj2)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj1 | [Object](structs.md#Object) |
| obj2 | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_gfx_pos_at_obj_pos(struct Object *obj1, struct Object *obj2);`

[:arrow_up_small:](#)

<br />

## [obj_set_gfx_pos_from_pos](#obj_set_gfx_pos_from_pos)

### Lua Example
`obj_set_gfx_pos_from_pos(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_gfx_pos_from_pos(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_set_gfx_scale](#obj_set_gfx_scale)

### Lua Example
`obj_set_gfx_scale(obj, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
- None

### C Prototype
`void obj_set_gfx_scale(struct Object *obj, f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [obj_set_held_state](#obj_set_held_state)

### Lua Example
`obj_set_held_state(obj, heldBehavior)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| heldBehavior | `Pointer` <`BehaviorScript`> |

### Returns
- None

### C Prototype
`void obj_set_held_state(struct Object *obj, const BehaviorScript *heldBehavior);`

[:arrow_up_small:](#)

<br />

## [obj_set_hitbox](#obj_set_hitbox)

### Lua Example
`obj_set_hitbox(obj, hitbox)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| hitbox | [ObjectHitbox](structs.md#ObjectHitbox) |

### Returns
- None

### C Prototype
`void obj_set_hitbox(struct Object *obj, struct ObjectHitbox *hitbox);`

[:arrow_up_small:](#)

<br />

## [obj_set_hitbox_radius_and_height](#obj_set_hitbox_radius_and_height)

### Lua Example
`obj_set_hitbox_radius_and_height(o, radius, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| radius | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void obj_set_hitbox_radius_and_height(struct Object *o, f32 radius, f32 height);`

[:arrow_up_small:](#)

<br />

## [obj_set_hurtbox_radius_and_height](#obj_set_hurtbox_radius_and_height)

### Lua Example
`obj_set_hurtbox_radius_and_height(o, radius, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| radius | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void obj_set_hurtbox_radius_and_height(struct Object *o, f32 radius, f32 height);`

[:arrow_up_small:](#)

<br />

## [obj_set_move_angle](#obj_set_move_angle)

### Lua Example
`obj_set_move_angle(obj, pitch, yaw, roll)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| pitch | `integer` |
| yaw | `integer` |
| roll | `integer` |

### Returns
- None

### C Prototype
`void obj_set_move_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll);`

[:arrow_up_small:](#)

<br />

## [obj_set_parent_relative_pos](#obj_set_parent_relative_pos)

### Lua Example
`obj_set_parent_relative_pos(obj, relX, relY, relZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| relX | `integer` |
| relY | `integer` |
| relZ | `integer` |

### Returns
- None

### C Prototype
`void obj_set_parent_relative_pos(struct Object *obj, s16 relX, s16 relY, s16 relZ);`

[:arrow_up_small:](#)

<br />

## [obj_set_pos](#obj_set_pos)

### Lua Example
`obj_set_pos(obj, x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| x | `integer` |
| y | `integer` |
| z | `integer` |

### Returns
- None

### C Prototype
`void obj_set_pos(struct Object *obj, s16 x, s16 y, s16 z);`

[:arrow_up_small:](#)

<br />

## [obj_set_pos_relative](#obj_set_pos_relative)

### Lua Example
`obj_set_pos_relative(obj, other, dleft, dy, dforward)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| other | [Object](structs.md#Object) |
| dleft | `number` |
| dy | `number` |
| dforward | `number` |

### Returns
- None

### C Prototype
`void obj_set_pos_relative(struct Object *obj, struct Object *other, f32 dleft, f32 dy, f32 dforward);`

[:arrow_up_small:](#)

<br />

## [obj_set_throw_matrix_from_transform](#obj_set_throw_matrix_from_transform)

### Lua Example
`obj_set_throw_matrix_from_transform(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_set_throw_matrix_from_transform(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [obj_spawn_loot_blue_coins](#obj_spawn_loot_blue_coins)

### Lua Example
`obj_spawn_loot_blue_coins(obj, numCoins, sp28, posJitter)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| numCoins | `integer` |
| sp28 | `number` |
| posJitter | `integer` |

### Returns
- None

### C Prototype
`void obj_spawn_loot_blue_coins(struct Object *obj, s32 numCoins, f32 sp28, s16 posJitter);`

[:arrow_up_small:](#)

<br />

## [obj_spawn_loot_coins](#obj_spawn_loot_coins)

### Lua Example
`obj_spawn_loot_coins(obj, numCoins, sp30, coinBehavior, posJitter, model)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| numCoins | `integer` |
| sp30 | `number` |
| coinBehavior | `Pointer` <`BehaviorScript`> |
| posJitter | `integer` |
| model | `integer` |

### Returns
- None

### C Prototype
`void obj_spawn_loot_coins(struct Object *obj, s32 numCoins, f32 sp30, const BehaviorScript *coinBehavior, s16 posJitter, s16 model);`

[:arrow_up_small:](#)

<br />

## [obj_spawn_loot_yellow_coins](#obj_spawn_loot_yellow_coins)

### Lua Example
`obj_spawn_loot_yellow_coins(obj, numCoins, sp28)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| numCoins | `integer` |
| sp28 | `number` |

### Returns
- None

### C Prototype
`void obj_spawn_loot_yellow_coins(struct Object *obj, s32 numCoins, f32 sp28);`

[:arrow_up_small:](#)

<br />

## [obj_translate_local](#obj_translate_local)

### Lua Example
`obj_translate_local(obj, posIndex, localTranslateIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| posIndex | `integer` |
| localTranslateIndex | `integer` |

### Returns
- None

### C Prototype
`void obj_translate_local(struct Object *obj, s16 posIndex, s16 localTranslateIndex);`

[:arrow_up_small:](#)

<br />

## [obj_translate_xyz_random](#obj_translate_xyz_random)

### Lua Example
`obj_translate_xyz_random(obj, rangeLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| rangeLength | `number` |

### Returns
- None

### C Prototype
`void obj_translate_xyz_random(struct Object *obj, f32 rangeLength);`

[:arrow_up_small:](#)

<br />

## [obj_translate_xz_random](#obj_translate_xz_random)

### Lua Example
`obj_translate_xz_random(obj, rangeLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| rangeLength | `number` |

### Returns
- None

### C Prototype
`void obj_translate_xz_random(struct Object *obj, f32 rangeLength);`

[:arrow_up_small:](#)

<br />

## [obj_turn_toward_object](#obj_turn_toward_object)

### Lua Example
`local integerValue = obj_turn_toward_object(obj, target, angleIndex, turnAmount)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| target | [Object](structs.md#Object) |
| angleIndex | `integer` |
| turnAmount | `integer` |

### Returns
- `integer`

### C Prototype
`s16 obj_turn_toward_object(struct Object *obj, struct Object *target, s16 angleIndex, s16 turnAmount);`

[:arrow_up_small:](#)

<br />

## [obj_update_pos_from_parent_transformation](#obj_update_pos_from_parent_transformation)

### Lua Example
`obj_update_pos_from_parent_transformation(a0, a1)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `Mat4` |
| a1 | [Object](structs.md#Object) |

### Returns
- None

### C Prototype
`void obj_update_pos_from_parent_transformation(Mat4 a0, struct Object *a1);`

[:arrow_up_small:](#)

<br />

## [player_performed_grab_escape_action](#player_performed_grab_escape_action)

### Lua Example
`local integerValue = player_performed_grab_escape_action()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 player_performed_grab_escape_action(void);`

[:arrow_up_small:](#)

<br />

## [random_f32_around_zero](#random_f32_around_zero)

### Lua Example
`local numberValue = random_f32_around_zero(diameter)`

### Parameters
| Field | Type |
| ----- | ---- |
| diameter | `number` |

### Returns
- `number`

### C Prototype
`f32 random_f32_around_zero(f32 diameter);`

[:arrow_up_small:](#)

<br />

## [set_mario_interact_hoot_if_in_range](#set_mario_interact_hoot_if_in_range)

### Lua Example
`set_mario_interact_hoot_if_in_range(sp0, sp4, sp8)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp0 | `integer` |
| sp4 | `integer` |
| sp8 | `number` |

### Returns
- None

### C Prototype
`void set_mario_interact_hoot_if_in_range(UNUSED s32 sp0, UNUSED s32 sp4, f32 sp8);`

[:arrow_up_small:](#)

<br />

## [set_time_stop_flags](#set_time_stop_flags)

### Lua Example
`set_time_stop_flags(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void set_time_stop_flags(s32 flags);`

[:arrow_up_small:](#)

<br />

## [set_time_stop_flags_if_alone](#set_time_stop_flags_if_alone)

### Lua Example
`set_time_stop_flags_if_alone(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void set_time_stop_flags_if_alone(s32 flags);`

[:arrow_up_small:](#)

<br />

## [signum_positive](#signum_positive)

### Lua Example
`local integerValue = signum_positive(x)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `integer` |

### Returns
- `integer`

### C Prototype
`s32 signum_positive(s32 x);`

[:arrow_up_small:](#)

<br />

## [spawn_base_star_with_no_lvl_exit](#spawn_base_star_with_no_lvl_exit)

### Lua Example
`spawn_base_star_with_no_lvl_exit()`

### Parameters
- None

### Returns
- None

### C Prototype
`void spawn_base_star_with_no_lvl_exit(void);`

[:arrow_up_small:](#)

<br />

## [spawn_mist_particles](#spawn_mist_particles)

### Lua Example
`spawn_mist_particles()`

### Parameters
- None

### Returns
- None

### C Prototype
`void spawn_mist_particles(void);`

[:arrow_up_small:](#)

<br />

## [spawn_mist_particles_with_sound](#spawn_mist_particles_with_sound)

### Lua Example
`spawn_mist_particles_with_sound(sp18)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp18 | `integer` |

### Returns
- None

### C Prototype
`void spawn_mist_particles_with_sound(u32 sp18);`

[:arrow_up_small:](#)

<br />

## [spawn_star_with_no_lvl_exit](#spawn_star_with_no_lvl_exit)

### Lua Example
`local ObjectValue = spawn_star_with_no_lvl_exit(sp20, sp24)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp20 | `integer` |
| sp24 | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *spawn_star_with_no_lvl_exit(s32 sp20, s32 sp24);`

[:arrow_up_small:](#)

<br />

## [spawn_water_droplet](#spawn_water_droplet)

### Lua Example
`local ObjectValue = spawn_water_droplet(parent, params)`

### Parameters
| Field | Type |
| ----- | ---- |
| parent | [Object](structs.md#Object) |
| params | [WaterDropletParams](structs.md#WaterDropletParams) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *spawn_water_droplet(struct Object *parent, struct WaterDropletParams *params);`

[:arrow_up_small:](#)

<br />

## [stub_obj_helpers_3](#stub_obj_helpers_3)

### Lua Example
`stub_obj_helpers_3(sp0, sp4)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp0 | `integer` |
| sp4 | `integer` |

### Returns
- None

### C Prototype
`void stub_obj_helpers_3(UNUSED s32 sp0, UNUSED s32 sp4);`

[:arrow_up_small:](#)

<br />

## [stub_obj_helpers_4](#stub_obj_helpers_4)

### Lua Example
`stub_obj_helpers_4()`

### Parameters
- None

### Returns
- None

### C Prototype
`void stub_obj_helpers_4(void);`

[:arrow_up_small:](#)

<br />

---
# functions from object_list_processor.h

<br />


## [set_object_respawn_info_bits](#set_object_respawn_info_bits)

### Lua Example
`set_object_respawn_info_bits(obj, bits)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| bits | `integer` |

### Returns
- None

### C Prototype
`void set_object_respawn_info_bits(struct Object *obj, u8 bits);`

[:arrow_up_small:](#)

<br />

---
# functions from rumble_init.c

<br />


## [queue_rumble_data](#queue_rumble_data)

### Lua Example
`queue_rumble_data(a0, a1)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `integer` |
| a1 | `integer` |

### Returns
- None

### C Prototype
`void queue_rumble_data(s16 a0, s16 a1);`

[:arrow_up_small:](#)

<br />

## [queue_rumble_data_mario](#queue_rumble_data_mario)

### Lua Example
`queue_rumble_data_mario(m, a0, a1)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| a0 | `integer` |
| a1 | `integer` |

### Returns
- None

### C Prototype
`void queue_rumble_data_mario(struct MarioState* m, s16 a0, s16 a1);`

[:arrow_up_small:](#)

<br />

## [queue_rumble_data_object](#queue_rumble_data_object)

### Lua Example
`queue_rumble_data_object(object, a0, a1)`

### Parameters
| Field | Type |
| ----- | ---- |
| object | [Object](structs.md#Object) |
| a0 | `integer` |
| a1 | `integer` |

### Returns
- None

### C Prototype
`void queue_rumble_data_object(struct Object* object, s16 a0, s16 a1);`

[:arrow_up_small:](#)

<br />

## [reset_rumble_timers](#reset_rumble_timers)

### Lua Example
`reset_rumble_timers(m)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |

### Returns
- None

### C Prototype
`void reset_rumble_timers(struct MarioState* m);`

[:arrow_up_small:](#)

<br />

## [reset_rumble_timers_2](#reset_rumble_timers_2)

### Lua Example
`reset_rumble_timers_2(m, a0)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| a0 | `integer` |

### Returns
- None

### C Prototype
`void reset_rumble_timers_2(struct MarioState* m, s32 a0);`

[:arrow_up_small:](#)

<br />

---
# functions from save_file.h

<br />


## [save_file_clear_flags](#save_file_clear_flags)

### Lua Example
`save_file_clear_flags(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void save_file_clear_flags(u32 flags);`

[:arrow_up_small:](#)

<br />

## [save_file_do_save](#save_file_do_save)

### Lua Example
`save_file_do_save(fileIndex, forceSave)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| forceSave | `integer` |

### Returns
- None

### C Prototype
`void save_file_do_save(s32 fileIndex, s8 forceSave);`

[:arrow_up_small:](#)

<br />

## [save_file_erase](#save_file_erase)

### Lua Example
`save_file_erase(fileIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |

### Returns
- None

### C Prototype
`void save_file_erase(s32 fileIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_erase_current_backup_save](#save_file_erase_current_backup_save)

### Lua Example
`save_file_erase_current_backup_save()`

### Parameters
- None

### Returns
- None

### C Prototype
`void save_file_erase_current_backup_save(void);`

[:arrow_up_small:](#)

<br />

## [save_file_get_cap_pos](#save_file_get_cap_pos)

### Lua Example
`local integerValue = save_file_get_cap_pos(capPos)`

### Parameters
| Field | Type |
| ----- | ---- |
| capPos | [Vec3s](structs.md#Vec3s) |

### Returns
- `integer`

### C Prototype
`s32 save_file_get_cap_pos(Vec3s capPos);`

[:arrow_up_small:](#)

<br />

## [save_file_get_course_coin_score](#save_file_get_course_coin_score)

### Lua Example
`local integerValue = save_file_get_course_coin_score(fileIndex, courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 save_file_get_course_coin_score(s32 fileIndex, s32 courseIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_get_course_star_count](#save_file_get_course_star_count)

### Lua Example
`local integerValue = save_file_get_course_star_count(fileIndex, courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 save_file_get_course_star_count(s32 fileIndex, s32 courseIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_get_flags](#save_file_get_flags)

### Lua Example
`local integerValue = save_file_get_flags()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 save_file_get_flags(void);`

[:arrow_up_small:](#)

<br />

## [save_file_get_max_coin_score](#save_file_get_max_coin_score)

### Lua Example
`local integerValue = save_file_get_max_coin_score(courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u32 save_file_get_max_coin_score(s32 courseIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_get_sound_mode](#save_file_get_sound_mode)

### Lua Example
`local integerValue = save_file_get_sound_mode()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u16 save_file_get_sound_mode(void);`

[:arrow_up_small:](#)

<br />

## [save_file_get_star_flags](#save_file_get_star_flags)

### Lua Example
`local integerValue = save_file_get_star_flags(fileIndex, courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u32 save_file_get_star_flags(s32 fileIndex, s32 courseIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_get_total_star_count](#save_file_get_total_star_count)

### Lua Example
`local integerValue = save_file_get_total_star_count(fileIndex, minCourse, maxCourse)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| minCourse | `integer` |
| maxCourse | `integer` |

### Returns
- `integer`

### C Prototype
`s32 save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);`

[:arrow_up_small:](#)

<br />

## [save_file_is_cannon_unlocked](#save_file_is_cannon_unlocked)

### Lua Example
`local integerValue = save_file_is_cannon_unlocked(fileIndex, courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 save_file_is_cannon_unlocked(s32 fileIndex, s32 courseIndex);`

[:arrow_up_small:](#)

<br />

## [save_file_reload](#save_file_reload)

### Lua Example
`save_file_reload(load_all)`

### Parameters
| Field | Type |
| ----- | ---- |
| load_all | `integer` |

### Returns
- None

### C Prototype
`void save_file_reload(u8 load_all);`

[:arrow_up_small:](#)

<br />

## [save_file_remove_star_flags](#save_file_remove_star_flags)

### Lua Example
`save_file_remove_star_flags(fileIndex, courseIndex, starFlagsToRemove)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |
| starFlagsToRemove | `integer` |

### Returns
- None

### C Prototype
`void save_file_remove_star_flags(s32 fileIndex, s32 courseIndex, u32 starFlagsToRemove);`

[:arrow_up_small:](#)

<br />

## [save_file_set_course_coin_score](#save_file_set_course_coin_score)

### Lua Example
`save_file_set_course_coin_score(fileIndex, courseIndex, coinScore)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |
| coinScore | `integer` |

### Returns
- None

### C Prototype
`void save_file_set_course_coin_score(s32 fileIndex, s32 courseIndex, u8 coinScore);`

[:arrow_up_small:](#)

<br />

## [save_file_set_flags](#save_file_set_flags)

### Lua Example
`save_file_set_flags(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void save_file_set_flags(u32 flags);`

[:arrow_up_small:](#)

<br />

## [save_file_set_star_flags](#save_file_set_star_flags)

### Lua Example
`save_file_set_star_flags(fileIndex, courseIndex, starFlags)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |
| starFlags | `integer` |

### Returns
- None

### C Prototype
`void save_file_set_star_flags(s32 fileIndex, s32 courseIndex, u32 starFlags);`

[:arrow_up_small:](#)

<br />

## [touch_coin_score_age](#touch_coin_score_age)

### Lua Example
`touch_coin_score_age(fileIndex, courseIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| fileIndex | `integer` |
| courseIndex | `integer` |

### Returns
- None

### C Prototype
`void touch_coin_score_age(s32 fileIndex, s32 courseIndex);`

[:arrow_up_small:](#)

<br />

---
# functions from seqplayer.h

<br />


## [sequence_player_get_tempo](#sequence_player_get_tempo)

### Lua Example
`local integerValue = sequence_player_get_tempo(player)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |

### Returns
- `integer`

### C Prototype
`u16 sequence_player_get_tempo(u8 player);`

[:arrow_up_small:](#)

<br />

## [sequence_player_get_tempo_acc](#sequence_player_get_tempo_acc)

### Lua Example
`local integerValue = sequence_player_get_tempo_acc(player)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |

### Returns
- `integer`

### C Prototype
`u16 sequence_player_get_tempo_acc(u8 player);`

[:arrow_up_small:](#)

<br />

## [sequence_player_get_transposition](#sequence_player_get_transposition)

### Lua Example
`local integerValue = sequence_player_get_transposition(player)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |

### Returns
- `integer`

### C Prototype
`u16 sequence_player_get_transposition(u8 player);`

[:arrow_up_small:](#)

<br />

## [sequence_player_set_tempo](#sequence_player_set_tempo)

### Lua Example
`sequence_player_set_tempo(player, tempo)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| tempo | `integer` |

### Returns
- None

### C Prototype
`void sequence_player_set_tempo(u8 player, u16 tempo);`

[:arrow_up_small:](#)

<br />

## [sequence_player_set_tempo_acc](#sequence_player_set_tempo_acc)

### Lua Example
`sequence_player_set_tempo_acc(player, tempoAcc)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| tempoAcc | `integer` |

### Returns
- None

### C Prototype
`void sequence_player_set_tempo_acc(u8 player, u16 tempoAcc);`

[:arrow_up_small:](#)

<br />

## [sequence_player_set_transposition](#sequence_player_set_transposition)

### Lua Example
`sequence_player_set_transposition(player, transposition)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |
| transposition | `integer` |

### Returns
- None

### C Prototype
`void sequence_player_set_transposition(u8 player, u16 transposition);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_anim_utils.h

<br />


## [get_mario_vanilla_animation](#get_mario_vanilla_animation)

### Lua Example
`local AnimationValue = get_mario_vanilla_animation(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
[Animation](structs.md#Animation)

### C Prototype
`struct Animation *get_mario_vanilla_animation(u16 index);`

[:arrow_up_small:](#)

<br />

## [smlua_anim_util_get_current_animation_name](#smlua_anim_util_get_current_animation_name)

### Lua Example
`local stringValue = smlua_anim_util_get_current_animation_name(obj)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |

### Returns
- `string`

### C Prototype
`const char *smlua_anim_util_get_current_animation_name(struct Object *obj);`

[:arrow_up_small:](#)

<br />

## [smlua_anim_util_set_animation](#smlua_anim_util_set_animation)

### Lua Example
`smlua_anim_util_set_animation(obj, name)`

### Parameters
| Field | Type |
| ----- | ---- |
| obj | [Object](structs.md#Object) |
| name | `string` |

### Returns
- None

### C Prototype
`void smlua_anim_util_set_animation(struct Object *obj, const char *name);`

[:arrow_up_small:](#)

<br />
---

[< prev](functions-3.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | 4 | [5](functions-5.md) | [next >](functions-5.md)]

