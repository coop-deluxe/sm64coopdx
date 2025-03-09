## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-5.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | 6]


---
# functions from smlua_gfx_utils.h

<br />


## [get_fog_color](#get_fog_color)

### Description
Gets a value of the global fog color

### Lua Example
`local integerValue = get_fog_color(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_fog_color(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_fog_intensity](#get_fog_intensity)

### Description
Gets the intensity of the fog

### Lua Example
`local numberValue = get_fog_intensity()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_fog_intensity(void);`

[:arrow_up_small:](#)

<br />

## [get_lighting_color](#get_lighting_color)

### Description
Gets a value of the global lighting color

### Lua Example
`local integerValue = get_lighting_color(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_lighting_color(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_lighting_color_ambient](#get_lighting_color_ambient)

### Description
Gets a value of the global ambient lighting color

### Lua Example
`local integerValue = get_lighting_color_ambient(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_lighting_color_ambient(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_lighting_dir](#get_lighting_dir)

### Description
Gets a value of the global lighting direction

### Lua Example
`local numberValue = get_lighting_dir(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_lighting_dir(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_skybox](#get_skybox)

### Description
Gets the current skybox

### Lua Example
`local integerValue = get_skybox()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s8 get_skybox(void);`

[:arrow_up_small:](#)

<br />

## [get_skybox_color](#get_skybox_color)

### Description
Gets a value of the global skybox color

### Lua Example
`local integerValue = get_skybox_color(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_skybox_color(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_vertex_color](#get_vertex_color)

### Description
Gets a value of the global vertex shading color

### Lua Example
`local integerValue = get_vertex_color(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`u8 get_vertex_color(u8 index);`

[:arrow_up_small:](#)

<br />

## [gfx_get_vtx](#gfx_get_vtx)

### Description
Gets a vertex from a display list command if it has the correct op. Intended to be used with `gfx_parse`

### Lua Example
`local PointerValue = gfx_get_vtx(gfx, offset)`

### Parameters
| Field | Type |
| ----- | ---- |
| gfx | `Pointer` <`Gfx`> |
| offset | `integer` |

### Returns
- `Pointer` <`Vtx`>

### C Prototype
`Vtx *gfx_get_vtx(Gfx* gfx, u16 offset);`

[:arrow_up_small:](#)

<br />

## [gfx_get_vtx_count](#gfx_get_vtx_count)

### Description
Gets the number of vertices from a display list command if it has the correct op

### Lua Example
`local integerValue = gfx_get_vtx_count(cmd)`

### Parameters
| Field | Type |
| ----- | ---- |
| cmd | `Pointer` <`Gfx`> |

### Returns
- `integer`

### C Prototype
`u16 gfx_get_vtx_count(Gfx* cmd);`

[:arrow_up_small:](#)

<br />

## [gfx_parse](#gfx_parse)

### Description
Traverses a display list. Takes a Lua function as a parameter, which is called back for each command in the display list with the parameters `cmd` (display list pointer), and `op`

### Lua Example
`gfx_parse(cmd, func)`

### Parameters
| Field | Type |
| ----- | ---- |
| cmd | `Pointer` <`Gfx`> |
| func | `Lua Function` () |

### Returns
- None

### C Prototype
`void gfx_parse(Gfx* cmd, LuaFunction func);`

[:arrow_up_small:](#)

<br />

## [gfx_set_combine_lerp](#gfx_set_combine_lerp)

### Description
Sets the display list combine mode. you can fill this function with G_CCMUX_* and G_ACMUX_* constants

### Lua Example
`gfx_set_combine_lerp(gfx, a0, b0, c0, d0, Aa0, Ab0, Ac0, Ad0, a1, b1, c1, d1, Aa1, Ab1, Ac1, Ad1)`

### Parameters
| Field | Type |
| ----- | ---- |
| gfx | `Pointer` <`Gfx`> |
| a0 | `integer` |
| b0 | `integer` |
| c0 | `integer` |
| d0 | `integer` |
| Aa0 | `integer` |
| Ab0 | `integer` |
| Ac0 | `integer` |
| Ad0 | `integer` |
| a1 | `integer` |
| b1 | `integer` |
| c1 | `integer` |
| d1 | `integer` |
| Aa1 | `integer` |
| Ab1 | `integer` |
| Ac1 | `integer` |
| Ad1 | `integer` |

### Returns
- None

### C Prototype
`void gfx_set_combine_lerp(Gfx* gfx, u32 a0, u32 b0, u32 c0, u32 d0, u32 Aa0, u32 Ab0, u32 Ac0, u32 Ad0, u32 a1, u32 b1, u32 c1, u32 d1,	u32 Aa1, u32 Ab1, u32 Ac1, u32 Ad1);`

[:arrow_up_small:](#)

<br />

## [gfx_set_texture_image](#gfx_set_texture_image)

### Description
Sets the display list texture image. Pass in textureInfo.texture as `texture`

### Lua Example
`gfx_set_texture_image(gfx, format, size, width, texture)`

### Parameters
| Field | Type |
| ----- | ---- |
| gfx | `Pointer` <`Gfx`> |
| format | `integer` |
| size | `integer` |
| width | `integer` |
| texture | `Pointer` <`integer`> |

### Returns
- None

### C Prototype
`void gfx_set_texture_image(Gfx* gfx, u32 format, u32 size, u32 width, u8* texture);`

[:arrow_up_small:](#)

<br />

## [set_fog_color](#set_fog_color)

### Description
Sets a value of the global fog color

### Lua Example
`set_fog_color(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_fog_color(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

## [set_fog_intensity](#set_fog_intensity)

### Description
Sets the intensity of the fog (this value scales very quickly, 1.0 to 1.1 is a desirable range)

### Lua Example
`set_fog_intensity(intensity)`

### Parameters
| Field | Type |
| ----- | ---- |
| intensity | `number` |

### Returns
- None

### C Prototype
`void set_fog_intensity(f32 intensity);`

[:arrow_up_small:](#)

<br />

## [set_lighting_color](#set_lighting_color)

### Description
Sets a value of the global lighting color

### Lua Example
`set_lighting_color(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_lighting_color(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

## [set_lighting_color_ambient](#set_lighting_color_ambient)

### Description
Sets a value of the global lighting color (run this after `set_lighting_color` for the ambient color to not be overriden)

### Lua Example
`set_lighting_color_ambient(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_lighting_color_ambient(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

## [set_lighting_dir](#set_lighting_dir)

### Description
Sets a value of the global lighting direction

### Lua Example
`set_lighting_dir(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `number` |

### Returns
- None

### C Prototype
`void set_lighting_dir(u8 index, f32 value);`

[:arrow_up_small:](#)

<br />

## [set_override_far](#set_override_far)

### Description
Sets the override far plane

### Lua Example
`set_override_far(far)`

### Parameters
| Field | Type |
| ----- | ---- |
| far | `number` |

### Returns
- None

### C Prototype
`void set_override_far(f32 far);`

[:arrow_up_small:](#)

<br />

## [set_override_fov](#set_override_fov)

### Description
Sets the override FOV

### Lua Example
`set_override_fov(fov)`

### Parameters
| Field | Type |
| ----- | ---- |
| fov | `number` |

### Returns
- None

### C Prototype
`void set_override_fov(f32 fov);`

[:arrow_up_small:](#)

<br />

## [set_override_near](#set_override_near)

### Description
Sets the override near plane

### Lua Example
`set_override_near(near)`

### Parameters
| Field | Type |
| ----- | ---- |
| near | `number` |

### Returns
- None

### C Prototype
`void set_override_near(f32 near);`

[:arrow_up_small:](#)

<br />

## [set_override_skybox](#set_override_skybox)

### Description
Sets the override skybox

### Lua Example
`set_override_skybox(background)`

### Parameters
| Field | Type |
| ----- | ---- |
| background | `integer` |

### Returns
- None

### C Prototype
`void set_override_skybox(s8 background);`

[:arrow_up_small:](#)

<br />

## [set_skybox_color](#set_skybox_color)

### Description
Sets a value of the global skybox color

### Lua Example
`set_skybox_color(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_skybox_color(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

## [set_vertex_color](#set_vertex_color)

### Description
Sets a value of the global vertex shading color

### Lua Example
`set_vertex_color(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_vertex_color(u8 index, u8 value);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_level_utils.h

<br />


## [level_is_vanilla_level](#level_is_vanilla_level)

### Description
Checks if `levelNum` is a vanilla level

### Lua Example
`local booleanValue = level_is_vanilla_level(levelNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| levelNum | `integer` |

### Returns
- `boolean`

### C Prototype
`bool level_is_vanilla_level(s16 levelNum);`

[:arrow_up_small:](#)

<br />

## [level_register](#level_register)

### Description
Registers a fully custom level. Level ID begins at 50

### Lua Example
`local integerValue = level_register(scriptEntryName, courseNum, fullName, shortName, acousticReach, echoLevel1, echoLevel2, echoLevel3)`

### Parameters
| Field | Type |
| ----- | ---- |
| scriptEntryName | `string` |
| courseNum | `integer` |
| fullName | `string` |
| shortName | `string` |
| acousticReach | `integer` |
| echoLevel1 | `integer` |
| echoLevel2 | `integer` |
| echoLevel3 | `integer` |

### Returns
- `integer`

### C Prototype
`s16 level_register(const char* scriptEntryName, s16 courseNum, const char* fullName, const char* shortName, u32 acousticReach, u32 echoLevel1, u32 echoLevel2, u32 echoLevel3);`

[:arrow_up_small:](#)

<br />

## [smlua_level_util_change_area](#smlua_level_util_change_area)

### Description
Instantly changes the current area to `areaIndex`

### Lua Example
`smlua_level_util_change_area(areaIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| areaIndex | `integer` |

### Returns
- None

### C Prototype
`void smlua_level_util_change_area(s32 areaIndex);`

[:arrow_up_small:](#)

<br />

## [smlua_level_util_get_info](#smlua_level_util_get_info)

### Description
Gets information on a custom level from `levelNum`

### Lua Example
`local CustomLevelInfoValue = smlua_level_util_get_info(levelNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| levelNum | `integer` |

### Returns
[CustomLevelInfo](structs.md#CustomLevelInfo)

### C Prototype
`struct CustomLevelInfo* smlua_level_util_get_info(s16 levelNum);`

[:arrow_up_small:](#)

<br />

## [smlua_level_util_get_info_from_course_num](#smlua_level_util_get_info_from_course_num)

### Description
Gets information on a custom level from `courseNum`

### Lua Example
`local CustomLevelInfoValue = smlua_level_util_get_info_from_course_num(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
[CustomLevelInfo](structs.md#CustomLevelInfo)

### C Prototype
`struct CustomLevelInfo* smlua_level_util_get_info_from_course_num(u8 courseNum);`

[:arrow_up_small:](#)

<br />

## [smlua_level_util_get_info_from_short_name](#smlua_level_util_get_info_from_short_name)

### Description
Gets information on a custom level from `shortName`

### Lua Example
`local CustomLevelInfoValue = smlua_level_util_get_info_from_short_name(shortName)`

### Parameters
| Field | Type |
| ----- | ---- |
| shortName | `string` |

### Returns
[CustomLevelInfo](structs.md#CustomLevelInfo)

### C Prototype
`struct CustomLevelInfo* smlua_level_util_get_info_from_short_name(const char* shortName);`

[:arrow_up_small:](#)

<br />

## [warp_exit_level](#warp_exit_level)

### Description
Exits the current level after `aDelay`

### Lua Example
`local booleanValue = warp_exit_level(aDelay)`

### Parameters
| Field | Type |
| ----- | ---- |
| aDelay | `integer` |

### Returns
- `boolean`

### C Prototype
`bool warp_exit_level(s32 aDelay);`

[:arrow_up_small:](#)

<br />

## [warp_restart_level](#warp_restart_level)

### Description
Restarts the current level

### Lua Example
`local booleanValue = warp_restart_level()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool warp_restart_level(void);`

[:arrow_up_small:](#)

<br />

## [warp_to_castle](#warp_to_castle)

### Description
Warps back to the castle from `aLevel`

### Lua Example
`local booleanValue = warp_to_castle(aLevel)`

### Parameters
| Field | Type |
| ----- | ---- |
| aLevel | `integer` |

### Returns
- `boolean`

### C Prototype
`bool warp_to_castle(s32 aLevel);`

[:arrow_up_small:](#)

<br />

## [warp_to_level](#warp_to_level)

### Description
Warps to `aArea` of `aLevel` in `aAct`

### Lua Example
`local booleanValue = warp_to_level(aLevel, aArea, aAct)`

### Parameters
| Field | Type |
| ----- | ---- |
| aLevel | `integer` |
| aArea | `integer` |
| aAct | `integer` |

### Returns
- `boolean`

### C Prototype
`bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct);`

[:arrow_up_small:](#)

<br />

## [warp_to_start_level](#warp_to_start_level)

### Description
Warps to the start level (Castle Grounds by default)

### Lua Example
`local booleanValue = warp_to_start_level()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool warp_to_start_level(void);`

[:arrow_up_small:](#)

<br />

## [warp_to_warpnode](#warp_to_warpnode)

### Description
Warps to `aWarpId` of `aArea` in `aLevel` during `aAct`

### Lua Example
`local booleanValue = warp_to_warpnode(aLevel, aArea, aAct, aWarpId)`

### Parameters
| Field | Type |
| ----- | ---- |
| aLevel | `integer` |
| aArea | `integer` |
| aAct | `integer` |
| aWarpId | `integer` |

### Returns
- `boolean`

### C Prototype
`bool warp_to_warpnode(s32 aLevel, s32 aArea, s32 aAct, s32 aWarpId);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_math_utils.h

<br />


## [clamp](#clamp)

### Description
Clamps a signed 32-bit integer `a` between bounds `b` (minimum) and `c` (maximum)

### Lua Example
`local integerValue = clamp(a, b, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |
| b | `integer` |
| c | `integer` |

### Returns
- `integer`

### C Prototype
`s32 clamp(s32 a, s32 b, s32 c);`

[:arrow_up_small:](#)

<br />

## [clampf](#clampf)

### Description
Clamps a floating-point number `a` between bounds `b` (minimum) and `c` (maximum)

### Lua Example
`local numberValue = clampf(a, b, c)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `number` |
| b | `number` |
| c | `number` |

### Returns
- `number`

### C Prototype
`f32 clampf(f32 a, f32 b, f32 c);`

[:arrow_up_small:](#)

<br />

## [degrees_to_sm64](#degrees_to_sm64)

### Description
Converts an angle from degrees to SM64 format

### Lua Example
`local integerValue = degrees_to_sm64(degreesAngle)`

### Parameters
| Field | Type |
| ----- | ---- |
| degreesAngle | `number` |

### Returns
- `integer`

### C Prototype
`s16 degrees_to_sm64(f32 degreesAngle);`

[:arrow_up_small:](#)

<br />

## [hypotf](#hypotf)

### Description
Computes the hypotenuse of a right triangle given sides `a` and `b` using the Pythagorean theorem

### Lua Example
`local numberValue = hypotf(a, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `number` |
| b | `number` |

### Returns
- `number`

### C Prototype
`f32 hypotf(f32 a, f32 b);`

[:arrow_up_small:](#)

<br />

## [max](#max)

### Description
Finds the maximum of two signed 32-bit integers

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
`s32 max(s32 a, s32 b);`

[:arrow_up_small:](#)

<br />

## [maxf](#maxf)

### Description
Finds the maximum of two floating-point numbers

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

### Description
Finds the minimum of two signed 32-bit integers

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
`s32 min(s32 a, s32 b);`

[:arrow_up_small:](#)

<br />

## [minf](#minf)

### Description
Finds the minimum of two floating-point numbers

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

## [radians_to_sm64](#radians_to_sm64)

### Description
Converts an angle from radians to SM64 format

### Lua Example
`local integerValue = radians_to_sm64(radiansAngle)`

### Parameters
| Field | Type |
| ----- | ---- |
| radiansAngle | `number` |

### Returns
- `integer`

### C Prototype
`s16 radians_to_sm64(f32 radiansAngle);`

[:arrow_up_small:](#)

<br />

## [sm64_to_degrees](#sm64_to_degrees)

### Description
Converts an angle from SM64 format to degrees

### Lua Example
`local numberValue = sm64_to_degrees(sm64Angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| sm64Angle | `integer` |

### Returns
- `number`

### C Prototype
`f32 sm64_to_degrees(s16 sm64Angle);`

[:arrow_up_small:](#)

<br />

## [sm64_to_radians](#sm64_to_radians)

### Description
Converts an angle from SM64 format to radians

### Lua Example
`local numberValue = sm64_to_radians(sm64Angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| sm64Angle | `integer` |

### Returns
- `number`

### C Prototype
`f32 sm64_to_radians(s16 sm64Angle);`

[:arrow_up_small:](#)

<br />

## [sqr](#sqr)

### Description
Computes the square of a signed 32-bit integer

### Lua Example
`local integerValue = sqr(x)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `integer` |

### Returns
- `integer`

### C Prototype
`s32 sqr(s32 x);`

[:arrow_up_small:](#)

<br />

## [sqrf](#sqrf)

### Description
Computes the square of a floating-point number

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

---
# functions from smlua_misc_utils.h

<br />


## [allocate_mario_action](#allocate_mario_action)

### Description
Allocates an action ID with bitwise flags

### Lua Example
`local integerValue = allocate_mario_action(actFlags)`

### Parameters
| Field | Type |
| ----- | ---- |
| actFlags | `integer` |

### Returns
- `integer`

### C Prototype
`u32 allocate_mario_action(u32 actFlags);`

[:arrow_up_small:](#)

<br />

## [course_is_main_course](#course_is_main_course)

### Description
Checks if a course is a main course and not the castle or secret levels

### Lua Example
`local booleanValue = course_is_main_course(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- `boolean`

### C Prototype
`bool course_is_main_course(u16 courseNum);`

[:arrow_up_small:](#)

<br />

## [djui_attempting_to_open_playerlist](#djui_attempting_to_open_playerlist)

### Description
Checks if the DJUI playerlist is attempting to be opened

### Lua Example
`local booleanValue = djui_attempting_to_open_playerlist()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool djui_attempting_to_open_playerlist(void);`

[:arrow_up_small:](#)

<br />

## [djui_is_playerlist_open](#djui_is_playerlist_open)

### Description
Checks if the DJUI playerlist is open

### Lua Example
`local booleanValue = djui_is_playerlist_open()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool djui_is_playerlist_open(void);`

[:arrow_up_small:](#)

<br />

## [djui_is_popup_disabled](#djui_is_popup_disabled)

### Description
Returns if popups are disabled

### Lua Example
`local booleanValue = djui_is_popup_disabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool djui_is_popup_disabled(void);`

[:arrow_up_small:](#)

<br />

## [djui_menu_get_font](#djui_menu_get_font)

### Description
Gets the DJUI menu font

### Lua Example
`local enumValue = djui_menu_get_font()`

### Parameters
- None

### Returns
[enum DjuiFontType](constants.md#enum-DjuiFontType)

### C Prototype
`enum DjuiFontType djui_menu_get_font(void);`

[:arrow_up_small:](#)

<br />

## [djui_menu_get_theme](#djui_menu_get_theme)

### Description
Gets the DJUI menu theme

### Lua Example
`local DjuiThemeValue = djui_menu_get_theme()`

### Parameters
- None

### Returns
[DjuiTheme](structs.md#DjuiTheme)

### C Prototype
`struct DjuiTheme* djui_menu_get_theme(void);`

[:arrow_up_small:](#)

<br />

## [djui_popup_create_global](#djui_popup_create_global)

### Description
Creates a DJUI popup that is broadcasted to every client

### Lua Example
`djui_popup_create_global(message, lines)`

### Parameters
| Field | Type |
| ----- | ---- |
| message | `string` |
| lines | `integer` |

### Returns
- None

### C Prototype
`void djui_popup_create_global(const char* message, int lines);`

[:arrow_up_small:](#)

<br />

## [djui_reset_popup_disabled_override](#djui_reset_popup_disabled_override)

### Description
Resets if popups are disabled

### Lua Example
`djui_reset_popup_disabled_override()`

### Parameters
- None

### Returns
- None

### C Prototype
`void djui_reset_popup_disabled_override(void);`

[:arrow_up_small:](#)

<br />

## [djui_set_popup_disabled_override](#djui_set_popup_disabled_override)

### Description
Sets if popups are disabled

### Lua Example
`djui_set_popup_disabled_override(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `boolean` |

### Returns
- None

### C Prototype
`void djui_set_popup_disabled_override(bool value);`

[:arrow_up_small:](#)

<br />

## [get_active_mod](#get_active_mod)

### Description
Gets the mod currently being processed

### Lua Example
`local ModValue = get_active_mod()`

### Parameters
- None

### Returns
[Mod](structs.md#Mod)

### C Prototype
`struct Mod* get_active_mod(void);`

[:arrow_up_small:](#)

<br />

## [get_area_update_counter](#get_area_update_counter)

### Description
Gets the area update counter incremented when objects are updated

### Lua Example
`local integerValue = get_area_update_counter()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u16 get_area_update_counter(void);`

[:arrow_up_small:](#)

<br />

## [get_coopnet_id](#get_coopnet_id)

### Description
Gets the CoopNet ID of a player with `localIndex` if CoopNet is being used and the player is connected, otherwise "-1" is returned

### Lua Example
`local stringValue = get_coopnet_id(localIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| localIndex | `integer` |

### Returns
- `string`

### C Prototype
`const char* get_coopnet_id(s8 localIndex);`

[:arrow_up_small:](#)

<br />

## [get_current_save_file_num](#get_current_save_file_num)

### Description
Gets the current save file number (1-indexed)

### Lua Example
`local integerValue = get_current_save_file_num()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 get_current_save_file_num(void);`

[:arrow_up_small:](#)

<br />

## [get_date_and_time](#get_date_and_time)

### Description
Gets the system clock's date and time

### Lua Example
`local DateTimeValue = get_date_and_time()`

### Parameters
- None

### Returns
[DateTime](structs.md#DateTime)

### C Prototype
`struct DateTime* get_date_and_time(void);`

[:arrow_up_small:](#)

<br />

## [get_dialog_box_state](#get_dialog_box_state)

### Description
Gets the current state of the dialog box

### Lua Example
`local integerValue = get_dialog_box_state()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s8 get_dialog_box_state(void);`

[:arrow_up_small:](#)

<br />

## [get_dialog_id](#get_dialog_id)

### Description
Gets the current dialog box ID

### Lua Example
`local integerValue = get_dialog_id()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 get_dialog_id(void);`

[:arrow_up_small:](#)

<br />

## [get_dialog_response](#get_dialog_response)

### Description
Gets the choice selected inside of a dialog box (0-1)

### Lua Example
`local integerValue = get_dialog_response()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 get_dialog_response(void);`

[:arrow_up_small:](#)

<br />

## [get_envfx](#get_envfx)

### Description
Gets the non overridden environment effect (e.g. snow)

### Lua Example
`local integerValue = get_envfx()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u16 get_envfx(void);`

[:arrow_up_small:](#)

<br />

## [get_environment_region](#get_environment_region)

### Description
Gets an environment region (gas/water boxes) height value

### Lua Example
`local numberValue = get_environment_region(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_environment_region(u8 index);`

[:arrow_up_small:](#)

<br />

## [get_global_timer](#get_global_timer)

### Description
Gets the global timer that has been ticking at 30 frames per second since game boot

### Lua Example
`local integerValue = get_global_timer()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 get_global_timer(void);`

[:arrow_up_small:](#)

<br />

## [get_got_file_coin_hi_score](#get_got_file_coin_hi_score)

### Description
Checks if the save file's coin "HI SCORE" was obtained with the last star or key collection

### Lua Example
`local booleanValue = get_got_file_coin_hi_score()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool get_got_file_coin_hi_score(void);`

[:arrow_up_small:](#)

<br />

## [get_hand_foot_pos_x](#get_hand_foot_pos_x)

### Description
Gets the X coordinate of Mario's hand (0-1) or foot (2-3) but it is important to note that the positions are not updated off-screen

### Lua Example
`local numberValue = get_hand_foot_pos_x(m, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_hand_foot_pos_x(struct MarioState* m, u8 index);`

[:arrow_up_small:](#)

<br />

## [get_hand_foot_pos_y](#get_hand_foot_pos_y)

### Description
Gets the Y coordinate of Mario's hand (0-1) or foot (2-3) but It is important to note that the positions are not updated off-screen

### Lua Example
`local numberValue = get_hand_foot_pos_y(m, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_hand_foot_pos_y(struct MarioState* m, u8 index);`

[:arrow_up_small:](#)

<br />

## [get_hand_foot_pos_z](#get_hand_foot_pos_z)

### Description
Gets the Z coordinate of Mario's hand (0-1) or foot (2-3) but it is important to note that the positions are not updated off-screen

### Lua Example
`local numberValue = get_hand_foot_pos_z(m, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| index | `integer` |

### Returns
- `number`

### C Prototype
`f32 get_hand_foot_pos_z(struct MarioState* m, u8 index);`

[:arrow_up_small:](#)

<br />

## [get_last_completed_course_num](#get_last_completed_course_num)

### Description
Gets the last course a star or key was collected in

### Lua Example
`local integerValue = get_last_completed_course_num()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 get_last_completed_course_num(void);`

[:arrow_up_small:](#)

<br />

## [get_last_completed_star_num](#get_last_completed_star_num)

### Description
Gets the last collected star's number (1-7)

### Lua Example
`local integerValue = get_last_completed_star_num()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 get_last_completed_star_num(void);`

[:arrow_up_small:](#)

<br />

## [get_last_star_or_key](#get_last_star_or_key)

### Description
Gets if the last objective collected was a star (0) or a key (1)

### Lua Example
`local integerValue = get_last_star_or_key()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 get_last_star_or_key(void);`

[:arrow_up_small:](#)

<br />

## [get_local_discord_id](#get_local_discord_id)

### Description
Gets the local discord ID if it isn't disabled, otherwise "0" is returned

### Lua Example
`local stringValue = get_local_discord_id()`

### Parameters
- None

### Returns
- `string`

### C Prototype
`const char* get_local_discord_id(void);`

[:arrow_up_small:](#)

<br />

## [get_network_area_timer](#get_network_area_timer)

### Description
Gets the current area's networked timer

### Lua Example
`local integerValue = get_network_area_timer()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 get_network_area_timer(void);`

[:arrow_up_small:](#)

<br />

## [get_os_name](#get_os_name)

### Description
Gets the name of the operating system the game is running on

### Lua Example
`local stringValue = get_os_name()`

### Parameters
- None

### Returns
- `string`

### C Prototype
`const char* get_os_name(void);`

[:arrow_up_small:](#)

<br />

## [get_save_file_modified](#get_save_file_modified)

### Description
Checks if the save file has been modified without saving

### Lua Example
`local booleanValue = get_save_file_modified()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool get_save_file_modified(void);`

[:arrow_up_small:](#)

<br />

## [get_time](#get_time)

### Description
Gets the Unix Timestamp

### Lua Example
`local integerValue = get_time()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s64 get_time(void);`

[:arrow_up_small:](#)

<br />

## [get_ttc_speed_setting](#get_ttc_speed_setting)

### Description
Gets TTC's speed setting

### Lua Example
`local integerValue = get_ttc_speed_setting()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s16 get_ttc_speed_setting(void);`

[:arrow_up_small:](#)

<br />

## [get_volume_env](#get_volume_env)

### Description
Gets the volume level of environment sounds effects

### Lua Example
`local numberValue = get_volume_env()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_volume_env(void);`

[:arrow_up_small:](#)

<br />

## [get_volume_level](#get_volume_level)

### Description
Gets the volume level of music

### Lua Example
`local numberValue = get_volume_level()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_volume_level(void);`

[:arrow_up_small:](#)

<br />

## [get_volume_master](#get_volume_master)

### Description
Gets the master volume level

### Lua Example
`local numberValue = get_volume_master()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_volume_master(void);`

[:arrow_up_small:](#)

<br />

## [get_volume_sfx](#get_volume_sfx)

### Description
Gets the volume level of sound effects

### Lua Example
`local numberValue = get_volume_sfx()`

### Parameters
- None

### Returns
- `number`

### C Prototype
`f32 get_volume_sfx(void);`

[:arrow_up_small:](#)

<br />

## [get_water_level](#get_water_level)

### Description
Gets the water level in an area corresponding to `index` (0-indexed)

### Lua Example
`local integerValue = get_water_level(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`s16 get_water_level(u8 index);`

[:arrow_up_small:](#)

<br />

## [hud_get_flash](#hud_get_flash)

### Description
Gets if the star counter on the HUD should flash

### Lua Example
`local integerValue = hud_get_flash()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s8 hud_get_flash(void);`

[:arrow_up_small:](#)

<br />

## [hud_get_value](#hud_get_value)

### Lua Example
`local integerValue = hud_get_value(type)`

### Parameters
| Field | Type |
| ----- | ---- |
| type | [enum HudDisplayValue](constants.md#enum-HudDisplayValue) |

### Returns
- `integer`

### C Prototype
`s32 hud_get_value(enum HudDisplayValue type);`

[:arrow_up_small:](#)

<br />

## [hud_hide](#hud_hide)

### Description
Hides the HUD

### Lua Example
`hud_hide()`

### Parameters
- None

### Returns
- None

### C Prototype
`void hud_hide(void);`

[:arrow_up_small:](#)

<br />

## [hud_is_hidden](#hud_is_hidden)

### Description
Checks if the HUD is hidden

### Lua Example
`local booleanValue = hud_is_hidden()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool hud_is_hidden(void);`

[:arrow_up_small:](#)

<br />

## [hud_render_power_meter](#hud_render_power_meter)

### Description
Renders a power meter on the HUD

### Lua Example
`hud_render_power_meter(health, x, y, width, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| health | `integer` |
| x | `number` |
| y | `number` |
| width | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void hud_render_power_meter(s32 health, f32 x, f32 y, f32 width, f32 height);`

[:arrow_up_small:](#)

<br />

## [hud_render_power_meter_interpolated](#hud_render_power_meter_interpolated)

### Description
Renders an interpolated power meter on the HUD

### Lua Example
`hud_render_power_meter_interpolated(health, prevX, prevY, prevWidth, prevHeight, x, y, width, height)`

### Parameters
| Field | Type |
| ----- | ---- |
| health | `integer` |
| prevX | `number` |
| prevY | `number` |
| prevWidth | `number` |
| prevHeight | `number` |
| x | `number` |
| y | `number` |
| width | `number` |
| height | `number` |

### Returns
- None

### C Prototype
`void hud_render_power_meter_interpolated(s32 health, f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height);`

[:arrow_up_small:](#)

<br />

## [hud_set_flash](#hud_set_flash)

### Description
Sets if the star counter on the HUD should flash

### Lua Example
`hud_set_flash(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void hud_set_flash(s8 value);`

[:arrow_up_small:](#)

<br />

## [hud_set_value](#hud_set_value)

### Description
Sets a HUD display value

### Lua Example
`hud_set_value(type, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| type | [enum HudDisplayValue](constants.md#enum-HudDisplayValue) |
| value | `integer` |

### Returns
- None

### C Prototype
`void hud_set_value(enum HudDisplayValue type, s32 value);`

[:arrow_up_small:](#)

<br />

## [hud_show](#hud_show)

### Description
Shows the HUD

### Lua Example
`hud_show()`

### Parameters
- None

### Returns
- None

### C Prototype
`void hud_show(void);`

[:arrow_up_small:](#)

<br />

## [is_game_paused](#is_game_paused)

### Description
Checks if the game is paused

### Lua Example
`local booleanValue = is_game_paused()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool is_game_paused(void);`

[:arrow_up_small:](#)

<br />

## [is_transition_playing](#is_transition_playing)

### Description
Checks if a screen transition is playing

### Lua Example
`local booleanValue = is_transition_playing()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool is_transition_playing(void);`

[:arrow_up_small:](#)

<br />

## [mod_file_exists](#mod_file_exists)

### Description
Checks if a file exists inside of a mod

### Lua Example
`local booleanValue = mod_file_exists(filename)`

### Parameters
| Field | Type |
| ----- | ---- |
| filename | `string` |

### Returns
- `boolean`

### C Prototype
`bool mod_file_exists(const char* filename);`

[:arrow_up_small:](#)

<br />

## [movtexqc_register](#movtexqc_register)

### Description
Registers a custom moving texture entry (used for vanilla water boxes)

### Lua Example
`movtexqc_register(name, level, area, type)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |
| level | `integer` |
| area | `integer` |
| type | `integer` |

### Returns
- None

### C Prototype
`void movtexqc_register(const char* name, s16 level, s16 area, s16 type);`

[:arrow_up_small:](#)

<br />

## [play_transition](#play_transition)

### Description
Plays a screen transition

### Lua Example
`play_transition(transType, time, red, green, blue)`

### Parameters
| Field | Type |
| ----- | ---- |
| transType | `integer` |
| time | `integer` |
| red | `integer` |
| green | `integer` |
| blue | `integer` |

### Returns
- None

### C Prototype
`void play_transition(s16 transType, s16 time, u8 red, u8 green, u8 blue);`

[:arrow_up_small:](#)

<br />

## [reset_window_title](#reset_window_title)

### Description
Resets the window title

### Lua Example
`reset_window_title()`

### Parameters
- None

### Returns
- None

### C Prototype
`void reset_window_title(void);`

[:arrow_up_small:](#)

<br />

## [save_file_get_using_backup_slot](#save_file_get_using_backup_slot)

### Description
Checks if the save file is using its backup slot

### Lua Example
`local booleanValue = save_file_get_using_backup_slot()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool save_file_get_using_backup_slot(void);`

[:arrow_up_small:](#)

<br />

## [save_file_set_using_backup_slot](#save_file_set_using_backup_slot)

### Description
Sets if the save file should use its backup slot

### Lua Example
`save_file_set_using_backup_slot(usingBackupSlot)`

### Parameters
| Field | Type |
| ----- | ---- |
| usingBackupSlot | `boolean` |

### Returns
- None

### C Prototype
`void save_file_set_using_backup_slot(bool usingBackupSlot);`

[:arrow_up_small:](#)

<br />

## [set_environment_region](#set_environment_region)

### Description
Sets an environment region (gas/water boxes) height value

### Lua Example
`set_environment_region(index, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_environment_region(u8 index, s32 value);`

[:arrow_up_small:](#)

<br />

## [set_got_file_coin_hi_score](#set_got_file_coin_hi_score)

### Description
Sets if the save file's coin "HI SCORE" was obtained with the last star or key collection

### Lua Example
`set_got_file_coin_hi_score(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `boolean` |

### Returns
- None

### C Prototype
`void set_got_file_coin_hi_score(bool value);`

[:arrow_up_small:](#)

<br />

## [set_last_completed_course_num](#set_last_completed_course_num)

### Description
Sets the last course a star or key was collected in

### Lua Example
`set_last_completed_course_num(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- None

### C Prototype
`void set_last_completed_course_num(u8 courseNum);`

[:arrow_up_small:](#)

<br />

## [set_last_completed_star_num](#set_last_completed_star_num)

### Description
Sets the last collected star's number (1-7)

### Lua Example
`set_last_completed_star_num(starNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| starNum | `integer` |

### Returns
- None

### C Prototype
`void set_last_completed_star_num(u8 starNum);`

[:arrow_up_small:](#)

<br />

## [set_last_star_or_key](#set_last_star_or_key)

### Description
Sets if the last objective collected was a star (0) or a key (1)

### Lua Example
`set_last_star_or_key(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void set_last_star_or_key(u8 value);`

[:arrow_up_small:](#)

<br />

## [set_override_envfx](#set_override_envfx)

### Description
Sets the override environment effect (e.g. snow)

### Lua Example
`set_override_envfx(envfx)`

### Parameters
| Field | Type |
| ----- | ---- |
| envfx | `integer` |

### Returns
- None

### C Prototype
`void set_override_envfx(s32 envfx);`

[:arrow_up_small:](#)

<br />

## [set_save_file_modified](#set_save_file_modified)

### Description
Sets if the save file has been modified without saving

### Lua Example
`set_save_file_modified(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `boolean` |

### Returns
- None

### C Prototype
`void set_save_file_modified(bool value);`

[:arrow_up_small:](#)

<br />

## [set_ttc_speed_setting](#set_ttc_speed_setting)

### Description
Sets TTC's speed setting (TTC_SPEED_*)

### Lua Example
`set_ttc_speed_setting(speed)`

### Parameters
| Field | Type |
| ----- | ---- |
| speed | `integer` |

### Returns
- None

### C Prototype
`void set_ttc_speed_setting(s16 speed);`

[:arrow_up_small:](#)

<br />

## [set_volume_env](#set_volume_env)

### Description
Sets the volume level of environment sounds effects

### Lua Example
`set_volume_env(volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| volume | `number` |

### Returns
- None

### C Prototype
`void set_volume_env(f32 volume);`

[:arrow_up_small:](#)

<br />

## [set_volume_level](#set_volume_level)

### Description
Sets the volume level of music

### Lua Example
`set_volume_level(volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| volume | `number` |

### Returns
- None

### C Prototype
`void set_volume_level(f32 volume);`

[:arrow_up_small:](#)

<br />

## [set_volume_master](#set_volume_master)

### Description
Sets the master volume level

### Lua Example
`set_volume_master(volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| volume | `number` |

### Returns
- None

### C Prototype
`void set_volume_master(f32 volume);`

[:arrow_up_small:](#)

<br />

## [set_volume_sfx](#set_volume_sfx)

### Description
Sets the volume level of sound effects

### Lua Example
`set_volume_sfx(volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| volume | `number` |

### Returns
- None

### C Prototype
`void set_volume_sfx(f32 volume);`

[:arrow_up_small:](#)

<br />

## [set_water_level](#set_water_level)

### Description
Sets the water level in an area corresponding to `index` (0-indexed)

### Lua Example
`set_water_level(index, height, sync)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| height | `integer` |
| sync | `boolean` |

### Returns
- None

### C Prototype
`void set_water_level(u8 index, s16 height, bool sync);`

[:arrow_up_small:](#)

<br />

## [set_window_title](#set_window_title)

### Description
Sets the window title to a custom title

### Lua Example
`set_window_title(title)`

### Parameters
| Field | Type |
| ----- | ---- |
| title | `string` |

### Returns
- None

### C Prototype
`void set_window_title(const char* title);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_model_utils.h

<br />


## [smlua_model_util_get_id](#smlua_model_util_get_id)

### Description
Gets the extended model ID for the `name` of a `GeoLayout`

### Lua Example
`local enumValue = smlua_model_util_get_id(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
[enum ModelExtendedId](constants.md#enum-ModelExtendedId)

### C Prototype
`enum ModelExtendedId smlua_model_util_get_id(const char* name);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_obj_utils.h

<br />


## [geo_get_current_object](#geo_get_current_object)

### Description
When used in a geo function, retrieve the current processed object

### Lua Example
`local ObjectValue = geo_get_current_object()`

### Parameters
- None

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *geo_get_current_object(void);`

[:arrow_up_small:](#)

<br />

## [get_current_object](#get_current_object)

### Description
Gets the object currently being processed

### Lua Example
`local ObjectValue = get_current_object()`

### Parameters
- None

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *get_current_object(void);`

[:arrow_up_small:](#)

<br />

## [get_cutscene_focus](#get_cutscene_focus)

### Description
Gets the cutscene focus object

### Lua Example
`local ObjectValue = get_cutscene_focus()`

### Parameters
- None

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *get_cutscene_focus(void);`

[:arrow_up_small:](#)

<br />

## [get_dialog_object](#get_dialog_object)

### Description
Gets the NPC object Mario is talking to

### Lua Example
`local ObjectValue = get_dialog_object()`

### Parameters
- None

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *get_dialog_object(void);`

[:arrow_up_small:](#)

<br />

## [get_secondary_camera_focus](#get_secondary_camera_focus)

### Description
Gets the secondary camera focus object

### Lua Example
`local ObjectValue = get_secondary_camera_focus()`

### Parameters
- None

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *get_secondary_camera_focus(void);`

[:arrow_up_small:](#)

<br />

## [get_temp_object_hitbox](#get_temp_object_hitbox)

### Description
Returns a temporary object hitbox pointer

### Lua Example
`local ObjectHitboxValue = get_temp_object_hitbox()`

### Parameters
- None

### Returns
[ObjectHitbox](structs.md#ObjectHitbox)

### C Prototype
`struct ObjectHitbox* get_temp_object_hitbox(void);`

[:arrow_up_small:](#)

<br />

## [get_trajectory](#get_trajectory)

### Description
Gets a trajectory by `name`

### Lua Example
`local PointerValue = get_trajectory(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
- `Pointer` <`Trajectory`>

### C Prototype
`Trajectory* get_trajectory(const char* name);`

[:arrow_up_small:](#)

<br />

## [obj_check_hitbox_overlap](#obj_check_hitbox_overlap)

### Description
Checks if `o1`'s hitbox is colliding with `o2`'s hitbox

### Lua Example
`local booleanValue = obj_check_hitbox_overlap(o1, o2)`

### Parameters
| Field | Type |
| ----- | ---- |
| o1 | [Object](structs.md#Object) |
| o2 | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_check_hitbox_overlap(struct Object *o1, struct Object *o2);`

[:arrow_up_small:](#)

<br />

## [obj_check_overlap_with_hitbox_params](#obj_check_overlap_with_hitbox_params)

### Description
Checks if `o`'s hitbox is colliding with the parameters of a hitbox

### Lua Example
`local booleanValue = obj_check_overlap_with_hitbox_params(o, x, y, z, h, r, d)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| x | `number` |
| y | `number` |
| z | `number` |
| h | `number` |
| r | `number` |
| d | `number` |

### Returns
- `boolean`

### C Prototype
`bool obj_check_overlap_with_hitbox_params(struct Object *o, f32 x, f32 y, f32 z, f32 h, f32 r, f32 d);`

[:arrow_up_small:](#)

<br />

## [obj_count_objects_with_behavior_id](#obj_count_objects_with_behavior_id)

### Description
Counts every object with `behaviorId`

### Lua Example
`local integerValue = obj_count_objects_with_behavior_id(behaviorId)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
- `integer`

### C Prototype
`s32 obj_count_objects_with_behavior_id(enum BehaviorId behaviorId);`

[:arrow_up_small:](#)

<br />

## [obj_get_collided_object](#obj_get_collided_object)

### Description
Gets the corresponding collided object to an index from `o`

### Lua Example
`local ObjectValue = obj_get_collided_object(o, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| index | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_collided_object(struct Object *o, s16 index);`

[:arrow_up_small:](#)

<br />

## [obj_get_field_f32](#obj_get_field_f32)

### Description
Sets the float value from the field corresponding to `fieldIndex`

### Lua Example
`local numberValue = obj_get_field_f32(o, fieldIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |

### Returns
- `number`

### C Prototype
`f32 obj_get_field_f32(struct Object *o, s32 fieldIndex);`

[:arrow_up_small:](#)

<br />

## [obj_get_field_s16](#obj_get_field_s16)

### Description
Gets the signed 32-bit integer value from the sub field corresponding to `fieldSubIndex` from the field corresponding to `fieldIndex`

### Lua Example
`local integerValue = obj_get_field_s16(o, fieldIndex, fieldSubIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| fieldSubIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s16 obj_get_field_s16(struct Object *o, s32 fieldIndex, s32 fieldSubIndex);`

[:arrow_up_small:](#)

<br />

## [obj_get_field_s32](#obj_get_field_s32)

### Description
Gets the signed 32-bit integer value from the field corresponding to `fieldIndex`

### Lua Example
`local integerValue = obj_get_field_s32(o, fieldIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |

### Returns
- `integer`

### C Prototype
`s32 obj_get_field_s32(struct Object *o, s32 fieldIndex);`

[:arrow_up_small:](#)

<br />

## [obj_get_field_u32](#obj_get_field_u32)

### Description
Gets the unsigned 32-bit integer value from the field corresponding to `fieldIndex`

### Lua Example
`local integerValue = obj_get_field_u32(o, fieldIndex)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |

### Returns
- `integer`

### C Prototype
`u32 obj_get_field_u32(struct Object *o, s32 fieldIndex);`

[:arrow_up_small:](#)

<br />

## [obj_get_first](#obj_get_first)

### Description
Gets the first object in an object list

### Lua Example
`local ObjectValue = obj_get_first(objList)`

### Parameters
| Field | Type |
| ----- | ---- |
| objList | [enum ObjectList](constants.md#enum-ObjectList) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_first(enum ObjectList objList);`

[:arrow_up_small:](#)

<br />

## [obj_get_first_with_behavior_id](#obj_get_first_with_behavior_id)

### Description
Gets the first object loaded with `behaviorId`

### Lua Example
`local ObjectValue = obj_get_first_with_behavior_id(behaviorId)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_first_with_behavior_id(enum BehaviorId behaviorId);`

[:arrow_up_small:](#)

<br />

## [obj_get_first_with_behavior_id_and_field_f32](#obj_get_first_with_behavior_id_and_field_f32)

### Description
Gets the first object loaded with `behaviorId` and object float field (look in `object_fields.h` to get the index of a field)

### Lua Example
`local ObjectValue = obj_get_first_with_behavior_id_and_field_f32(behaviorId, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |
| fieldIndex | `integer` |
| value | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_first_with_behavior_id_and_field_f32(enum BehaviorId behaviorId, s32 fieldIndex, f32 value);`

[:arrow_up_small:](#)

<br />

## [obj_get_first_with_behavior_id_and_field_s32](#obj_get_first_with_behavior_id_and_field_s32)

### Description
Gets the first object loaded with `behaviorId` and object signed 32-bit integer field (look in `object_fields.h` to get the index of a field)

### Lua Example
`local ObjectValue = obj_get_first_with_behavior_id_and_field_s32(behaviorId, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |
| fieldIndex | `integer` |
| value | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_first_with_behavior_id_and_field_s32(enum BehaviorId behaviorId, s32 fieldIndex, s32 value);`

[:arrow_up_small:](#)

<br />

## [obj_get_model_id_extended](#obj_get_model_id_extended)

### Description
Returns an object's extended model id

### Lua Example
`local enumValue = obj_get_model_id_extended(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
[enum ModelExtendedId](constants.md#enum-ModelExtendedId)

### C Prototype
`enum ModelExtendedId obj_get_model_id_extended(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_get_nearest_object_with_behavior_id](#obj_get_nearest_object_with_behavior_id)

### Description
Gets the nearest object with `behaviorId` to `o`

### Lua Example
`local ObjectValue = obj_get_nearest_object_with_behavior_id(o, behaviorId)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_nearest_object_with_behavior_id(struct Object *o, enum BehaviorId behaviorId);`

[:arrow_up_small:](#)

<br />

## [obj_get_next](#obj_get_next)

### Description
Gets the next object in an object list

### Lua Example
`local ObjectValue = obj_get_next(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_next(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_get_next_with_same_behavior_id](#obj_get_next_with_same_behavior_id)

### Description
Gets the next object loaded with the same behavior ID

### Lua Example
`local ObjectValue = obj_get_next_with_same_behavior_id(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_next_with_same_behavior_id(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_get_next_with_same_behavior_id_and_field_f32](#obj_get_next_with_same_behavior_id_and_field_f32)

### Description
Gets the next object loaded with the same behavior ID and object float field (look in `object_fields.h` to get the index of a field)

### Lua Example
`local ObjectValue = obj_get_next_with_same_behavior_id_and_field_f32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_next_with_same_behavior_id_and_field_f32(struct Object *o, s32 fieldIndex, f32 value);`

[:arrow_up_small:](#)

<br />

## [obj_get_next_with_same_behavior_id_and_field_s32](#obj_get_next_with_same_behavior_id_and_field_s32)

### Description
Gets the next object loaded with the same behavior ID and object signed 32-bit integer field (look in `object_fields.h` to get the index of a field)

### Lua Example
`local ObjectValue = obj_get_next_with_same_behavior_id_and_field_s32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object *obj_get_next_with_same_behavior_id_and_field_s32(struct Object *o, s32 fieldIndex, s32 value);`

[:arrow_up_small:](#)

<br />

## [obj_get_temp_spawn_particles_info](#obj_get_temp_spawn_particles_info)

### Description
Returns a temporary particle spawn info pointer with its model loaded in from `modelId`

### Lua Example
`local SpawnParticlesInfoValue = obj_get_temp_spawn_particles_info(modelId)`

### Parameters
| Field | Type |
| ----- | ---- |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |

### Returns
[SpawnParticlesInfo](structs.md#SpawnParticlesInfo)

### C Prototype
`struct SpawnParticlesInfo* obj_get_temp_spawn_particles_info(enum ModelExtendedId modelId);`

[:arrow_up_small:](#)

<br />

## [obj_has_behavior_id](#obj_has_behavior_id)

### Description
Checks if an object has `behaviorId`

### Lua Example
`local integerValue = obj_has_behavior_id(o, behaviorId)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |

### Returns
- `integer`

### C Prototype
`s32 obj_has_behavior_id(struct Object *o, enum BehaviorId behaviorId);`

[:arrow_up_small:](#)

<br />

## [obj_has_model_extended](#obj_has_model_extended)

### Description
Checks if an object's model is equal to `modelId`

### Lua Example
`local integerValue = obj_has_model_extended(o, modelId)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |

### Returns
- `integer`

### C Prototype
`s32 obj_has_model_extended(struct Object *o, enum ModelExtendedId modelId);`

[:arrow_up_small:](#)

<br />

## [obj_is_attackable](#obj_is_attackable)

### Description
Checks if `o` is attackable

### Lua Example
`local booleanValue = obj_is_attackable(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_attackable(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_breakable_object](#obj_is_breakable_object)

### Description
Checks if `o` is breakable

### Lua Example
`local booleanValue = obj_is_breakable_object(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_breakable_object(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_bully](#obj_is_bully)

### Description
Checks if `o` is a Bully

### Lua Example
`local booleanValue = obj_is_bully(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_bully(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_coin](#obj_is_coin)

### Description
Checks if `o` is a coin

### Lua Example
`local booleanValue = obj_is_coin(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_coin(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_exclamation_box](#obj_is_exclamation_box)

### Description
Checks if `o` is an exclamation box

### Lua Example
`local booleanValue = obj_is_exclamation_box(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_exclamation_box(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_grabbable](#obj_is_grabbable)

### Description
Checks if `o` is grabbable

### Lua Example
`local booleanValue = obj_is_grabbable(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_grabbable(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_mushroom_1up](#obj_is_mushroom_1up)

### Description
Checks if `o` is a 1-Up Mushroom

### Lua Example
`local booleanValue = obj_is_mushroom_1up(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_mushroom_1up(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_secret](#obj_is_secret)

### Description
Checks if `o` is a secret

### Lua Example
`local booleanValue = obj_is_secret(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_secret(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_is_valid_for_interaction](#obj_is_valid_for_interaction)

### Description
Checks if `o` is activated, tangible, and interactible

### Lua Example
`local booleanValue = obj_is_valid_for_interaction(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `boolean`

### C Prototype
`bool obj_is_valid_for_interaction(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [obj_move_xyz](#obj_move_xyz)

### Description
Moves the object in the direction of `dx`, `dy`, and `dz`

### Lua Example
`obj_move_xyz(o, dx, dy, dz)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| dx | `number` |
| dy | `number` |
| dz | `number` |

### Returns
- None

### C Prototype
`void obj_move_xyz(struct Object *o, f32 dx, f32 dy, f32 dz);`

[:arrow_up_small:](#)

<br />

## [obj_set_field_f32](#obj_set_field_f32)

### Description
Sets the float value from the field corresponding to `fieldIndex`

### Lua Example
`obj_set_field_f32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `number` |

### Returns
- None

### C Prototype
`void obj_set_field_f32(struct Object *o, s32 fieldIndex, f32 value);`

[:arrow_up_small:](#)

<br />

## [obj_set_field_s16](#obj_set_field_s16)

### Description
Sets the signed 32-bit integer value from the sub field corresponding to `fieldSubIndex` from the field corresponding to `fieldIndex`

### Lua Example
`obj_set_field_s16(o, fieldIndex, fieldSubIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| fieldSubIndex | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void obj_set_field_s16(struct Object *o, s32 fieldIndex, s32 fieldSubIndex, s16 value);`

[:arrow_up_small:](#)

<br />

## [obj_set_field_s32](#obj_set_field_s32)

### Description
Sets the signed 32-bit integer value from the field corresponding to `fieldIndex`

### Lua Example
`obj_set_field_s32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void obj_set_field_s32(struct Object *o, s32 fieldIndex, s32 value);`

[:arrow_up_small:](#)

<br />

## [obj_set_field_u32](#obj_set_field_u32)

### Description
Sets the unsigned 32-bit integer value from the field corresponding to `fieldIndex`

### Lua Example
`obj_set_field_u32(o, fieldIndex, value)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| fieldIndex | `integer` |
| value | `integer` |

### Returns
- None

### C Prototype
`void obj_set_field_u32(struct Object *o, s32 fieldIndex, u32 value);`

[:arrow_up_small:](#)

<br />

## [obj_set_model_extended](#obj_set_model_extended)

### Description
Sets an object's model to `modelId`

### Lua Example
`obj_set_model_extended(o, modelId)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |

### Returns
- None

### C Prototype
`void obj_set_model_extended(struct Object *o, enum ModelExtendedId modelId);`

[:arrow_up_small:](#)

<br />

## [obj_set_vel](#obj_set_vel)

### Description
Sets an object's velocity to `vx`, `vy`, and `vz`

### Lua Example
`obj_set_vel(o, vx, vy, vz)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |
| vx | `number` |
| vy | `number` |
| vz | `number` |

### Returns
- None

### C Prototype
`void obj_set_vel(struct Object *o, f32 vx, f32 vy, f32 vz);`

[:arrow_up_small:](#)

<br />

## [set_cutscene_focus](#set_cutscene_focus)

### Description
Sets the cutscene focus object

### Lua Example
`local voidValue = set_cutscene_focus(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `void *`

### C Prototype
`void *set_cutscene_focus(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [set_secondary_camera_focus](#set_secondary_camera_focus)

### Description
Sets the secondary camera focus object

### Lua Example
`local voidValue = set_secondary_camera_focus(o)`

### Parameters
| Field | Type |
| ----- | ---- |
| o | [Object](structs.md#Object) |

### Returns
- `void *`

### C Prototype
`void *set_secondary_camera_focus(struct Object *o);`

[:arrow_up_small:](#)

<br />

## [set_whirlpools](#set_whirlpools)

### Description
Sets the parameters of one of the two whirlpools (0-indexed) in an area

### Lua Example
`set_whirlpools(x, y, z, strength, area, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |
| strength | `integer` |
| area | `integer` |
| index | `integer` |

### Returns
- None

### C Prototype
`void set_whirlpools(f32 x, f32 y, f32 z, s16 strength, s16 area, s32 index);`

[:arrow_up_small:](#)

<br />

## [spawn_non_sync_object](#spawn_non_sync_object)

### Description
Spawns a synchronized object in at `x`, `y`, and `z` as a child object of the local Mario with his rotation. You can change the fields of the object in `objSetupFunction`

### Lua Example
`local ObjectValue = spawn_non_sync_object(behaviorId, modelId, x, y, z, objSetupFunction)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |
| x | `number` |
| y | `number` |
| z | `number` |
| objSetupFunction | `Lua Function` () |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* spawn_non_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);`

[:arrow_up_small:](#)

<br />

## [spawn_sync_object](#spawn_sync_object)

### Description
Spawns a synchronized object in at `x`, `y`, and `z` as a child object of the local Mario with his rotation. You can change the fields of the object in `objSetupFunction`

### Lua Example
`local ObjectValue = spawn_sync_object(behaviorId, modelId, x, y, z, objSetupFunction)`

### Parameters
| Field | Type |
| ----- | ---- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) |
| modelId | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |
| x | `number` |
| y | `number` |
| z | `number` |
| objSetupFunction | `Lua Function` () |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* spawn_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_text_utils.h

<br />


## [smlua_text_utils_act_name_get](#smlua_text_utils_act_name_get)

### Description
Gets the act name of `actNum` in `courseNum`

### Lua Example
`local stringValue = smlua_text_utils_act_name_get(courseNum, actNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |

### Returns
- `string`

### C Prototype
`const char* smlua_text_utils_act_name_get(s16 courseNum, u8 actNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_act_name_mod_index](#smlua_text_utils_act_name_mod_index)

### Description
Gets the index of the mod that replaced the act name of `actNum` in `courseNum`

### Lua Example
`local integerValue = smlua_text_utils_act_name_mod_index(courseNum, actNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |

### Returns
- `integer`

### C Prototype
`s32 smlua_text_utils_act_name_mod_index(s16 courseNum, u8 actNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_act_name_replace](#smlua_text_utils_act_name_replace)

### Description
Replaces the act name of `actNum` in `courseNum` with `name`

### Lua Example
`smlua_text_utils_act_name_replace(courseNum, actNum, name)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |
| name | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_act_name_replace(s16 courseNum, u8 actNum, const char* name);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_act_name_reset](#smlua_text_utils_act_name_reset)

### Description
Resets the act name of `actNum` in `courseNum`

### Lua Example
`smlua_text_utils_act_name_reset(courseNum, actNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| actNum | `integer` |

### Returns
- None

### C Prototype
`void smlua_text_utils_act_name_reset(s16 courseNum, u8 actNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_castle_secret_stars_replace](#smlua_text_utils_castle_secret_stars_replace)

### Description
Replaces the castle secret stars text with `name`

### Lua Example
`smlua_text_utils_castle_secret_stars_replace(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_castle_secret_stars_replace(const char* name);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_acts_replace](#smlua_text_utils_course_acts_replace)

### Description
Replaces the act names of `courseNum`

### Lua Example
`smlua_text_utils_course_acts_replace(courseNum, courseName, act1, act2, act3, act4, act5, act6)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| courseName | `string` |
| act1 | `string` |
| act2 | `string` |
| act3 | `string` |
| act4 | `string` |
| act5 | `string` |
| act6 | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_course_acts_replace(s16 courseNum, const char* courseName, const char* act1, const char* act2, const char* act3, const char* act4, const char* act5, const char* act6);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_name_get](#smlua_text_utils_course_name_get)

### Description
Gets the name of `courseNum`

### Lua Example
`local stringValue = smlua_text_utils_course_name_get(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- `string`

### C Prototype
`const char* smlua_text_utils_course_name_get(s16 courseNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_name_mod_index](#smlua_text_utils_course_name_mod_index)

### Description
Gets the index of the mod that replaced the name of `courseNum`

### Lua Example
`local integerValue = smlua_text_utils_course_name_mod_index(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- `integer`

### C Prototype
`s32 smlua_text_utils_course_name_mod_index(s16 courseNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_name_replace](#smlua_text_utils_course_name_replace)

### Description
Replaces the name of `courseNum` with `name`

### Lua Example
`smlua_text_utils_course_name_replace(courseNum, name)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| name | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_course_name_replace(s16 courseNum, const char* name);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_course_name_reset](#smlua_text_utils_course_name_reset)

### Description
Resets the name of `courseNum`

### Lua Example
`smlua_text_utils_course_name_reset(courseNum)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |

### Returns
- None

### C Prototype
`void smlua_text_utils_course_name_reset(s16 courseNum);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_dialog_replace](#smlua_text_utils_dialog_replace)

### Description
Replaces `dialogId` with a custom one

### Lua Example
`smlua_text_utils_dialog_replace(dialogId, unused, linesPerBox, leftOffset, width, str)`

### Parameters
| Field | Type |
| ----- | ---- |
| dialogId | [enum DialogId](constants.md#enum-DialogId) |
| unused | `integer` |
| linesPerBox | `integer` |
| leftOffset | `integer` |
| width | `integer` |
| str | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_dialog_replace(enum DialogId dialogId, u32 unused, s8 linesPerBox, s16 leftOffset, s16 width, const char* str);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_extra_text_replace](#smlua_text_utils_extra_text_replace)

### Description
Replace extra text (e.g. one of the castle's secret stars) with `text`

### Lua Example
`smlua_text_utils_extra_text_replace(index, text)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| text | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_extra_text_replace(s16 index, const char* text);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_get_language](#smlua_text_utils_get_language)

### Description
Gets the current language

### Lua Example
`local stringValue = smlua_text_utils_get_language()`

### Parameters
- None

### Returns
- `string`

### C Prototype
`const char* smlua_text_utils_get_language(void);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_reset_all](#smlua_text_utils_reset_all)

### Description
Resets every modified dialog back to vanilla

### Lua Example
`smlua_text_utils_reset_all()`

### Parameters
- None

### Returns
- None

### C Prototype
`void smlua_text_utils_reset_all(void);`

[:arrow_up_small:](#)

<br />

## [smlua_text_utils_secret_star_replace](#smlua_text_utils_secret_star_replace)

### Description
Replaces the secret star course name of `courseNum` with `courseName`

### Lua Example
`smlua_text_utils_secret_star_replace(courseNum, courseName)`

### Parameters
| Field | Type |
| ----- | ---- |
| courseNum | `integer` |
| courseName | `string` |

### Returns
- None

### C Prototype
`void smlua_text_utils_secret_star_replace(s16 courseNum, const char* courseName);`

[:arrow_up_small:](#)

<br />

---
# functions from sound_init.h

<br />


## [disable_background_sound](#disable_background_sound)

### Description
Disables background soundbanks

### Lua Example
`disable_background_sound()`

### Parameters
- None

### Returns
- None

### C Prototype
`void disable_background_sound(void);`

[:arrow_up_small:](#)

<br />

## [enable_background_sound](#enable_background_sound)

### Description
Enables background soundbanks

### Lua Example
`enable_background_sound()`

### Parameters
- None

### Returns
- None

### C Prototype
`void enable_background_sound(void);`

[:arrow_up_small:](#)

<br />

## [fadeout_cap_music](#fadeout_cap_music)

### Description
Fades out cap music

### Lua Example
`fadeout_cap_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void fadeout_cap_music(void);`

[:arrow_up_small:](#)

<br />

## [fadeout_level_music](#fadeout_level_music)

### Description
Fades out the level sequence player

### Lua Example
`fadeout_level_music(fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| fadeTimer | `integer` |

### Returns
- None

### C Prototype
`void fadeout_level_music(s16 fadeTimer);`

[:arrow_up_small:](#)

<br />

## [fadeout_music](#fadeout_music)

### Description
Fades out level, shell, and cap music

### Lua Example
`fadeout_music(fadeOutTime)`

### Parameters
| Field | Type |
| ----- | ---- |
| fadeOutTime | `integer` |

### Returns
- None

### C Prototype
`void fadeout_music(s16 fadeOutTime);`

[:arrow_up_small:](#)

<br />

## [lower_background_noise](#lower_background_noise)

### Description
Lowers the volume of music by 40%

### Lua Example
`lower_background_noise(a)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |

### Returns
- None

### C Prototype
`void lower_background_noise(s32 a);`

[:arrow_up_small:](#)

<br />

## [play_cap_music](#play_cap_music)

### Description
Plays `seqArgs` as cap music

### Lua Example
`play_cap_music(seqArgs)`

### Parameters
| Field | Type |
| ----- | ---- |
| seqArgs | `integer` |

### Returns
- None

### C Prototype
`void play_cap_music(u16 seqArgs);`

[:arrow_up_small:](#)

<br />

## [play_cutscene_music](#play_cutscene_music)

### Description
Plays and sets the current music to `seqArgs`

### Lua Example
`play_cutscene_music(seqArgs)`

### Parameters
| Field | Type |
| ----- | ---- |
| seqArgs | `integer` |

### Returns
- None

### C Prototype
`void play_cutscene_music(u16 seqArgs);`

[:arrow_up_small:](#)

<br />

## [play_infinite_stairs_music](#play_infinite_stairs_music)

### Description
Plays the infinite stairs music if you're in the endless stairs room and have less than `gLevelValues.infiniteStairsRequirement` stars

### Lua Example
`play_infinite_stairs_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_infinite_stairs_music(void);`

[:arrow_up_small:](#)

<br />

## [play_menu_sounds](#play_menu_sounds)

### Description
Play menu sounds from `SOUND_MENU_FLAG_*` constants and queues rumble if `SOUND_MENU_FLAG_LETGOMARIOFACE` is one of the flags

### Lua Example
`play_menu_sounds(soundMenuFlags)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundMenuFlags | `integer` |

### Returns
- None

### C Prototype
`void play_menu_sounds(s16 soundMenuFlags);`

[:arrow_up_small:](#)

<br />

## [play_painting_eject_sound](#play_painting_eject_sound)

### Description
Plays the painting eject sound effect if it has not already been played

### Lua Example
`play_painting_eject_sound()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_painting_eject_sound(void);`

[:arrow_up_small:](#)

<br />

## [play_shell_music](#play_shell_music)

### Description
Plays shell music

### Lua Example
`play_shell_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void play_shell_music(void);`

[:arrow_up_small:](#)

<br />

## [raise_background_noise](#raise_background_noise)

### Description
Raises music volume back up to normal levels

### Lua Example
`raise_background_noise(a)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |

### Returns
- None

### C Prototype
`void raise_background_noise(s32 a);`

[:arrow_up_small:](#)

<br />

## [reset_volume](#reset_volume)

### Description
Resets if music volume has been lowered

### Lua Example
`reset_volume()`

### Parameters
- None

### Returns
- None

### C Prototype
`void reset_volume(void);`

[:arrow_up_small:](#)

<br />

## [set_background_music](#set_background_music)

### Description
Sets the background music to `seqArgs` on sequence player `a` with a fade in time of `fadeTimer`

### Lua Example
`set_background_music(a, seqArgs, fadeTimer)`

### Parameters
| Field | Type |
| ----- | ---- |
| a | `integer` |
| seqArgs | `integer` |
| fadeTimer | `integer` |

### Returns
- None

### C Prototype
`void set_background_music(u16 a, u16 seqArgs, s16 fadeTimer);`

[:arrow_up_small:](#)

<br />

## [stop_cap_music](#stop_cap_music)

### Description
Stops cap music completely

### Lua Example
`stop_cap_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void stop_cap_music(void);`

[:arrow_up_small:](#)

<br />

## [stop_shell_music](#stop_shell_music)

### Description
Stops shell music completely

### Lua Example
`stop_shell_music()`

### Parameters
- None

### Returns
- None

### C Prototype
`void stop_shell_music(void);`

[:arrow_up_small:](#)

<br />

---
# functions from spawn_sound.h

<br />


## [calc_dist_to_volume_range_1](#calc_dist_to_volume_range_1)

### Description
Unused vanilla function, calculates a volume based on `distance`. If `distance` is less than 500 then 127, if `distance` is greater than 1500 then 0, if `distance` is between 500 and 1500 then it ranges linearly from 60 to 124. What an even more strange and confusing function

### Lua Example
`local integerValue = calc_dist_to_volume_range_1(distance)`

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
`local integerValue = calc_dist_to_volume_range_2(distance)`

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

## [create_sound_spawner](#create_sound_spawner)

### Description
Create a sound spawner for objects that need a sound play once. (Breakable walls, King Bobomb exploding, etc)

### Lua Example
`create_sound_spawner(soundMagic)`

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

## [cur_obj_play_sound_1](#cur_obj_play_sound_1)

### Description
Plays a sound if the current object is visible

### Lua Example
`cur_obj_play_sound_1(soundMagic)`

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
`cur_obj_play_sound_2(soundMagic)`

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

## [exec_anim_sound_state](#exec_anim_sound_state)

### Lua Example
`exec_anim_sound_state(soundStates, maxSoundStates)`

### Parameters
| Field | Type |
| ----- | ---- |
| soundStates | [SoundState](structs.md#SoundState) |
| maxSoundStates | `integer` |

### Returns
- None

### C Prototype
`void exec_anim_sound_state(struct SoundState *soundStates, u16 maxSoundStates);`

[:arrow_up_small:](#)

<br />

---
# functions from surface_collision.h

<br />


## [find_ceil_height](#find_ceil_height)

### Description
Finds the height of the highest ceiling above a given position (x, y, z). If no ceiling is found, returns the default height limit of `gLevelValues.cellHeightLimit`(20000 by default)

### Lua Example
`local numberValue = find_ceil_height(x, y, z)`

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

## [find_floor_height](#find_floor_height)

### Description
Finds the height of the highest floor below a given position (x, y, z). If no floor is found, returns the default floor height of `gLevelValues.floorLowerLimit`(-11000 by default)

### Lua Example
`local numberValue = find_floor_height(x, y, z)`

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

## [find_poison_gas_level](#find_poison_gas_level)

### Description
Finds the height of the poison gas at a given position (x, z), if the position is within a gas region. If no gas is found, returns the default height of `gLevelValues.floorLowerLimit`(-11000 by default)

### Lua Example
`local numberValue = find_poison_gas_level(x, z)`

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

## [find_wall_collisions](#find_wall_collisions)

### Description
Detects wall collisions at a given position and adjusts the position based on the walls found. Returns the number of wall collisions detected

### Lua Example
`local integerValue = find_wall_collisions(colData)`

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

## [find_water_level](#find_water_level)

### Description
Finds the height of water at a given position (x, z), if the position is within a water region. If no water is found, returns the default height of `gLevelValues.floorLowerLimit`(-11000 by default)

### Lua Example
`local numberValue = find_water_level(x, z)`

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

## [set_find_wall_direction](#set_find_wall_direction)

### Description
Sets whether collision finding functions should check wall directions.

### Lua Example
`set_find_wall_direction(dir, active, airborne)`

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

---
# functions from surface_load.h

<br />


## [get_area_terrain_size](#get_area_terrain_size)

### Lua Example
`local integerValue = get_area_terrain_size(data)`

### Parameters
| Field | Type |
| ----- | ---- |
| data | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`u32 get_area_terrain_size(s16 *data);`

[:arrow_up_small:](#)

<br />

## [load_area_terrain](#load_area_terrain)

### Lua Example
`load_area_terrain(index, data, surfaceRooms, macroObjects)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| data | `Pointer` <`integer`> |
| surfaceRooms | `Pointer` <`integer`> |
| macroObjects | `Pointer` <`integer`> |

### Returns
- None

### C Prototype
`void load_area_terrain(s16 index, s16 *data, s8 *surfaceRooms, s16 *macroObjects);`

[:arrow_up_small:](#)

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

[< prev](functions-5.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | 6]

