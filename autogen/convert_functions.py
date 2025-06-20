import re
import sys
from extract_functions import *
from common import *
from vec_types import *

verbose = len(sys.argv) > 1 and (sys.argv[1] == "-v" or sys.argv[1] == "--verbose")

rejects = ""
integer_types = ["u8", "u16", "u32", "u64", "s8", "s16", "s32", "s64", "int"]
number_types = ["f32", "float", "f64", "double"]
out_filename = 'src/pc/lua/smlua_functions_autogen.c'
out_filename_docs = 'docs/lua/functions%s.md'
out_filename_defs = 'autogen/lua_definitions/functions.lua'

in_files = [
    "src/audio/external.h",
    "src/engine/math_util.h",
    "src/engine/math_util.inl",
    "src/engine/math_util_vec3f.inl",
    "src/engine/math_util_vec3i.inl",
    "src/engine/math_util_vec3s.inl",
    "src/engine/math_util_mat4.inl",
    "src/engine/surface_collision.h",
    "src/engine/surface_load.h",
    "src/game/camera.h",
    "src/game/characters.h",
    "src/game/mario_actions_airborne.c",
    "src/game/mario_actions_automatic.c",
    "src/game/mario_actions_cutscene.c",
    "src/game/mario_actions_moving.c",
    "src/game/mario_actions_object.c",
    "src/game/mario_actions_stationary.c",
    "src/game/mario_actions_submerged.c",
    "src/game/mario_step.h",
    "src/game/mario.h",
    "src/game/rumble_init.h",
    "src/pc/djui/djui_popup.h",
    "src/pc/network/network_utils.h",
    "src/pc/djui/djui_console.h",
    "src/pc/djui/djui_chat_message.h",
    "src/pc/djui/djui_language.h",
    "src/game/interaction.h",
    "src/game/level_info.h",
    "src/game/save_file.h",
    "src/game/sound_init.h",
    "src/pc/djui/djui_hud_utils.h",
    "src/pc/djui/djui_panel_menu.h",
    "src/pc/network/network_player.h",
    "src/pc/network/lag_compensation.h",
    "include/behavior_table.h",
    "src/pc/lua/utils/smlua_obj_utils.h",
    "src/pc/lua/utils/smlua_misc_utils.h",
    "src/pc/lua/utils/smlua_camera_utils.h",
    "src/pc/lua/utils/smlua_gfx_utils.h",
    "src/pc/lua/utils/smlua_collision_utils.h",
    "src/pc/lua/utils/smlua_model_utils.h",
    "src/pc/lua/utils/smlua_text_utils.h",
    "src/pc/lua/utils/smlua_audio_utils.h",
    "src/pc/lua/utils/smlua_level_utils.h",
    "src/pc/lua/utils/smlua_anim_utils.h",
    "src/pc/lua/utils/smlua_deprecated.h",
    "src/game/object_helpers.c",
    "src/game/obj_behaviors.c",
    "src/game/obj_behaviors_2.c",
    "src/game/platform_displacement.h",
    "src/game/spawn_sound.h",
    "src/game/object_list_processor.h",
    "src/game/behavior_actions.h",
    "src/game/mario_misc.h",
    "src/pc/mods/mod_storage.h",
    "src/pc/utils/misc.h",
    "src/game/level_update.h",
    "src/game/area.h",
    "src/engine/level_script.h",
    "src/game/ingame_menu.h",
    "src/game/first_person_cam.h",
    "src/engine/behavior_script.h",
    "src/audio/seqplayer.h",
    "src/engine/lighting_engine.h",
    "src/pc/network/sync_object.h"
]

override_allowed_functions = {
    "src/audio/external.h":                 [ " play_", "fade", "current_background", "stop_", "sound_banks", "drop_queued_background_music", "set_sound_moving_speed", "background_music_default_volume", "get_sound_pan", "sound_get_level_intensity", "set_audio_muted" ],
    "src/game/rumble_init.h":               [ "queue_rumble_", "reset_rumble_timers" ],
    "src/pc/djui/djui_popup.h":             [ "create" ],
    "src/pc/djui/djui_language.h":          [ "djui_language_get" ],
    "src/pc/djui/djui_panel_menu.h":        [ "djui_menu_get_rainbow_string_color" ],
    "src/game/save_file.h":                 [ "get_level_", "save_file_get_", "save_file_set_flags", "save_file_clear_flags", "save_file_reload", "save_file_erase_current_backup_save", "save_file_set_star_flags", "save_file_is_cannon_unlocked", "touch_coin_score_age", "save_file_set_course_coin_score", "save_file_do_save", "save_file_remove_star_flags", "save_file_erase" ],
    "src/pc/lua/utils/smlua_model_utils.h": [ "smlua_model_util_get_id" ],
    "src/game/object_list_processor.h":     [ "set_object_respawn_info_bits" ],
    "src/game/platform_displacement.h":     [ "apply_platform_displacement" ],
    "src/game/mario_misc.h":                [ "bhv_toad.*", "bhv_unlock_door.*", "geo_get_.*_state" ],
    "src/game/level_update.h":              [ "level_trigger_warp", "get_painting_warp_node", "initiate_painting_warp", "warp_special", "lvl_set_current_level", "level_control_timer_running", "fade_into_special_warp", "get_instant_warp" ],
    "src/game/area.h":                      [ "get_mario_spawn_type", "area_get_warp_node", "area_get_any_warp_node", "play_transition" ],
    "src/engine/level_script.h":            [ "area_create_warp_node" ],
    "src/game/ingame_menu.h":               [ "set_min_dialog_width", "set_dialog_override_pos", "reset_dialog_override_pos", "set_dialog_override_color", "reset_dialog_override_color", "set_menu_mode", "create_dialog_box", "create_dialog_box_with_var", "create_dialog_inverted_box", "create_dialog_box_with_response", "reset_dialog_render_state", "set_dialog_box_state", ],
    "src/audio/seqplayer.h":                [ "sequence_player_set_tempo", "sequence_player_set_tempo_acc", "sequence_player_set_transposition", "sequence_player_get_tempo", "sequence_player_get_tempo_acc", "sequence_player_get_transposition", "sequence_player_get_volume", "sequence_player_get_fade_volume", "sequence_player_get_mute_volume_scale" ],
    "src/pc/network/sync_object.h":         [ "sync_object_is_initialized", "sync_object_is_owned_locally", "sync_object_get_object" ]
}

override_disallowed_functions = {
    "src/audio/external.h":                     [ " func_" ],
    "src/engine/surface_load.h":                [ "load_area_terrain", "alloc_surface_pools", "clear_dynamic_surfaces", "get_area_terrain_size" ],
    "src/engine/surface_collision.h":           [ " debug_", "f32_find_wall_collision" ],
    "src/game/mario_actions_airborne.c":        [ "^[us]32 act_.*" ],
    "src/game/mario_actions_automatic.c":       [ "^[us]32 act_.*" ],
    "src/game/mario_actions_cutscene.c":        [ "^[us]32 act_.*", " geo_", "spawn_obj", "print_displaying_credits_entry" ],
    "src/game/mario_actions_moving.c":          [ "^[us]32 act_.*" ],
    "src/game/mario_actions_object.c":          [ "^[us]32 act_.*" ],
    "src/game/mario_actions_stationary.c":      [ "^[us]32 act_.*" ],
    "src/game/mario_actions_submerged.c":       [ "^[us]32 act_.*" ],
    "src/game/mario_step.h":                    [ " stub_mario_step", "transfer_bully_speed" ],
    "src/game/mario.h":                         [ " init_mario" ],
    "src/pc/djui/djui_console.h":               [ " djui_console_create", "djui_console_message_create", "djui_console_message_dequeue" ],
    "src/pc/djui/djui_chat_message.h":          [ "create_from" ],
    "src/game/interaction.h":                   [ "process_interaction", "_handle_" ],
    "src/game/sound_init.h":                    [ "_loop_", "thread4_", "set_sound_mode" ],
    "src/pc/network/network_utils.h":           [ "network_get_player_text_color[^_]" ],
    "src/pc/network/network_player.h":          [ "_init", "_connected[^_]", "_shutdown", "_disconnected", "_update", "construct_player_popup", "network_player_name_valid" ],
    "src/game/object_helpers.c":                [ "spawn_obj", "^bhv_", "abs[fi]", "^bit_shift", "_debug$", "^stub_", "_set_model", "cur_obj_set_direction_table", "cur_obj_progress_direction_table" ],
    "src/game/obj_behaviors.c":                 [ "debug_", "turn_obj_away_from_surface" ],
    "src/game/obj_behaviors_2.c":               [ "wiggler_jumped_on_attack_handler", "huge_goomba_weakly_attacked" ],
    "src/game/spawn_sound.h":                   [ "exec_anim_sound_state" ],
    "src/game/level_info.h":                    [ "_name_table" ],
    "src/pc/lua/utils/smlua_obj_utils.h":       [ "spawn_object_remember_field" ],
    "src/game/camera.h":                        [ "update_camera", "init_camera", "stub_camera", "^reset_camera", "move_point_along_spline", "romhack_camera_init_settings", "romhack_camera_reset_settings" ],
    "src/game/behavior_actions.h":              [ "bhv_dust_smoke_loop", "bhv_init_room" ],
    "src/pc/lua/utils/smlua_audio_utils.h":     [ "smlua_audio_utils_override", "audio_custom_shutdown", "smlua_audio_custom_deinit", "audio_sample_destroy_pending_copies", "audio_custom_update_volume" ],
    "src/pc/djui/djui_hud_utils.h":             [ "djui_hud_render_texture_raw", "djui_hud_render_texture_tile_raw" ],
    "src/pc/lua/utils/smlua_level_utils.h":     [ "smlua_level_util_reset" ],
    "src/pc/lua/utils/smlua_text_utils.h":      [ "smlua_text_utils_init", "smlua_text_utils_shutdown" ],
    "src/pc/lua/utils/smlua_anim_utils.h":      [ "smlua_anim_util_reset", "smlua_anim_util_register_animation" ],
    "src/pc/lua/utils/smlua_gfx_utils.h":       [ "gfx_allocate_internal", "vtx_allocate_internal", "gfx_get_length_no_sentinel" ],
    "src/pc/network/lag_compensation.h":        [ "lag_compensation_clear" ],
    "src/game/first_person_cam.h":              [ "first_person_update" ],
    "src/pc/lua/utils/smlua_collision_utils.h": [ "collision_find_surface_on_ray" ],
    "src/engine/behavior_script.h":             [ "stub_behavior_script_2", "cur_obj_update" ],
    "src/pc/utils/misc.h":                      [ "str_.*", "file_get_line", "delta_interpolate_(normal|rgba|mtx)", "detect_and_skip_mtx_interpolation" ],
    "src/engine/lighting_engine.h":             [ "le_calculate_vertex_lighting", "le_clear", "le_shutdown" ]
}

override_hide_functions = {
    "smlua_deprecated.h": [ ".*" ],
    "network_player.h":   [ "network_player_get_palette_color_channel", "network_player_get_override_palette_color_channel" ]
}

override_function_version_excludes = {
    "bhv_play_music_track_when_touched_loop": "VERSION_JP",
    "play_knockback_sound": "VERSION_JP",
    "cur_obj_spawn_star_at_y_offset": "VERSION_JP"
}

lua_function_params = {
    "src/pc/lua/utils/smlua_obj_utils.h::spawn_object_sync::objSetupFunction": [ "struct Object*" ]
}

###########################################################

template = """/* THIS FILE IS AUTOGENERATED */
/* SHOULD NOT BE MANUALLY CHANGED */

#include "smlua.h"

$[INCLUDES]

$[TYPES]

$[FUNCTIONS]

void smlua_bind_functions_autogen(void) {
    lua_State* L = gLuaState;
$[BINDS]
}
"""

###########################################################

vec_type_before = """
    %s $[IDENTIFIER];
    smlua_get_%s($[IDENTIFIER], $[INDEX]);
"""

vec_type_after = """
    smlua_push_%s($[IDENTIFIER], $[INDEX]);
"""

#
# Special cases for sound functions
#

SOUND_FUNCTIONS = [
    "play_sound",
    "play_sound_with_freq_scale",
    "stop_sound",
    "stop_sounds_from_source",
]

vec3f_sound_before = """
    f32 *$[IDENTIFIER] = smlua_get_vec3f_from_buffer();
    smlua_get_vec3f($[IDENTIFIER], $[INDEX]);
"""

###########################################################

manual_index_documentation = """
- manually written functions
   - [define_custom_obj_fields](#define_custom_obj_fields)
   - [network_init_object](#network_init_object)
   - [network_send_object](#network_send_object)
   - [network_send_to](#network_send_to)
   - [network_send](#network_send)
   - [get_texture_info](#get_texture_info)
   - [texture_override_set](#texture_override_set)
   - [texture_override_reset](#texture_override_reset)
   - [smlua_anim_util_register_animation](#smlua_anim_util_register_animation)
   - [level_script_parse](#level_script_parse)
   - [log_to_console](#log_to_console)
   - [add_scroll_target](#add_scroll_target)
   - [collision_find_surface_on_ray](#collision_find_surface_on_ray)
   - [cast_graph_node](#cast_graph_node)
   - [get_uncolored_string](#get_uncolored_string)
   - [gfx_set_command](#gfx_set_command)

<br />

"""
manual_documentation = """
---
# manually written functions

## [define_custom_obj_fields](#define_custom_obj_fields)

Defines a custom set of overlapping object fields.

The `fieldTable` table's keys must start with the letter `o` and the values must be either `u32`, `s32`, or `f32`.

### Lua Example
`define_custom_obj_fields({ oCustomField1 = 'u32', oCustomField2 = 's32', oCustomField3 = 'f32' })`

### Parameters
| Field | Type |
| ----- | ---- |
| fieldTable | `Lua Table` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

## [network_init_object](#network_init_object)

Enables synchronization on an object.

- Setting `standardSync` to `true` will automatically synchronize the object at a rate that is determined based on player distance. The commonly used object fields will be automatically synchronized.
- Setting `standardSync` to `false` will not automatically synchronize the object, or add commonly used object fields. The mod must manually call `network_send_object()` when fields have changed.

The `fieldTable` parameter can be `nil`, or a list of object fields.

### Lua Example
`network_init_object(obj, true, { 'oCustomField1', 'oCustomField2', 'oCustomField3' })`

### Parameters
| Field | Type |
| ----- | ---- |
| object | [Object](structs.md#Object) |
| standardSync | `bool` |
| fieldTable | `Lua Table` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />

## [network_send_object](#network_send_object)

Sends a packet that synchronizes an object. This does not need to be called when `standardSync` is enabled.

The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.

### Lua Example
`network_send_object(obj, false)`

### Parameters
| Field | Type |
| ----- | ---- |
| object | [Object](structs.md#Object) |
| reliable | `bool` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />

## [network_send_to](#network_send_to)

Sends a packet to a particular player (using their local index) containing whatever data you want.

`dataTable` can only contain strings, integers, numbers, booleans, and nil

The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.

### Lua Example
`network_send_to(localPlayerIndex, reliable, { data1 = 'hello', data2 = 10})`

### Parameters
| Field | Type |
| ----- | ---- |
| localPlayerIndex | `integer` |
| reliable | `bool` |
| dataTable | `table` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />

## [network_send](#network_send)

Sends a packet to all players containing whatever data you want.

`dataTable` can only contain strings, integers, numbers, booleans, and nil

The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.

### Lua Example
`network_send(reliable, { data1 = 'hello', data2 = 10})`

### Parameters
| Field | Type |
| ----- | ---- |
| reliable | `bool` |
| dataTable | `table` |

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />

## [get_texture_info](#get_texture_info)

Retrieves a texture by name.

### Lua Example
`get_texture_info(textureName)`

### Parameters
| Field | Type |
| ----- | ---- |
| textureName | `string` |

### Returns
- [TextureInfo](structs.md#TextureInfo)

### C Prototype
`N/A`

[:arrow_up_small:](#)

<br />

## [texture_override_reset](#texture_override_reset)

Resets an overridden texture.

### Lua Example
`texture_override_reset("outside_09004000")`

### Parameters
| Field | Type |
| ----- | ---- |
| textureName | `string` |

### Returns
- None

### C Prototype
`void dynos_texture_override_reset(const char* textureName);`

[:arrow_up_small:](#)

<br />

## [texture_override_set](#texture_override_set)

Overrides a texture with a custom `TextureInfo`.

### Lua Example
`texture_override_set("outside_09004000", overrideTexInfo)`

### Parameters
| Field | Type |
| ----- | ---- |
| textureName | `string` |
| overrideTexInfo | [TextureInfo](structs.md#TextureInfo) |

### Returns
- None

### C Prototype
`void dynos_texture_override_set(const char* textureName, struct TextureInfo* overrideTexInfo);`

[:arrow_up_small:](#)

<br />

## [smlua_anim_util_register_animation](#smlua_anim_util_register_animation)

Register a new Lua animation.

### Lua Example
`smlua_anim_util_register_animation("apparition_idle", 0, 189, 0, 0, 0x5A, values, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |
| flags | `integer` |
| animYTransDivisor | `integer` |
| startFrame | `integer` |
| loopStart | `integer` |
| loopEnd | `integer` |
| values | `table` |
| index | `table` |

### Returns
- None

### C Prototype
`void smlua_anim_util_register_animation(const char *name, s16 flags, s16 animYTransDivisor, s16 startFrame, s16 loopStart, s16 loopEnd, s16 *values, u32 valuesLength, u16 *index, u32 indexLength);`

[:arrow_up_small:](#)

<br />

## [level_script_parse](#level_script_parse)

### Lua Example
`level_script_parse(LEVEL_BOB, func)`

Parses a level script and passes area index, behavior data, macro behavior IDs and macro behavior arguments to a function.

### Parameters
| Field | Type |
| ----- | ---- |
| levelNum | `LevelNum` |
| func | `function` |

### Returns
- None

### C Prototype
`void smlua_func_level_script_parse(lua_State* L);`

[:arrow_up_small:](#)

<br />

## [log_to_console](#log_to_console)

Logs a message to the in-game console.

### Lua Example
`log_to_console("sm64coopdx FTW", CONSOLE_MESSAGE_INFO)`

### Parameters
| Field | Type |
| ----- | ---- |
| message | `string` |
| level (optional) | `ConsoleMessageLevel` |

### Returns
- None

### C Prototype
`void log_to_console(const char* message, enum ConsoleMessageLevel level);`

[:arrow_up_small:](#)

<br />

## [add_scroll_target](#add_scroll_target)

Registers a vertex buffer to be used for a scrolling texture. Should be used with `RM_Scroll_Texture` or `editor_Scroll_Texture`

### Lua Example
`add_scroll_target(0, "arena_rainbow_dl_StarRoad_mesh_layer_5_vtx_0")`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |
| name | `string` |

### Returns
- None

### C Prototype
`void dynos_add_scroll_target(u32 index, const char *name, u32 offset, u32 size);`

[:arrow_up_small:](#)

<br />

## [collision_find_surface_on_ray](#collision_find_surface_on_ray)

Shoots a raycast from `startX`, `startY`, and `startZ` in the direction of `dirX`, `dirY`, and `dirZ`.

### Lua Example
`collision_find_surface_on_ray(0, 0, 0, 50, 100, 50)`

### Parameters
| Field | Type |
| ----- | ---- |
| startX | `number` |
| startY | `number` |
| startZ | `number` |
| dirX | `number` |
| dirY | `number` |
| dirZ | `number` |
| precision (optional) | `number` |

### Returns
- [RayIntersectionInfo](structs.md#RayIntersectionInfo)

### C Prototype
`struct RayIntersectionInfo* collision_find_surface_on_ray(f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32 precision);`

[:arrow_up_small:](#)

<br />

## [set_exclamation_box_contents](#set_exclamation_box_contents)

Sets the contents that the exclamation box spawns. A single content has 5 keys: `id`, `unused`, `firstByte`, `model`, and `behavior`.
* `id`: Required; what value the box's oBehParams2ndByte needs to be to spawn this object.
* `unused`: Optional; unused by vanilla.
* `firstByte`: Optional; Overrides the 1st byte given to the spawned object.
* `model`: Required; The model that the object will spawn with. Uses `ModelExtendedId`.
* `behavior`: Required; The behavior ID that the object will spawn with. Uses `BehaviorId`.

### Lua Example
```lua
set_exclamation_box_contents({
   {id = 0, unused = 0, firstByte = 0, model = E_MODEL_GOOMBA, behavior = id_bhvGoomba}, -- Uses both optional fields
   {id = 1, unused = 0, model = E_MODEL_KOOPA_WITH_SHELL, behavior = id_bhvKoopa}, -- Only uses `unused` optional field
   {id = 2, firsteByte = model = E_MODEL_BLACK_BOBOMB, behavior = id_bhvBobomb}, -- Only uses `firstByte` optional field
   {id = 3, model = E_MODEL_BOO, behavior = id_bhvBoo}, -- Uses no optional fields
})
```

### Parameters
There exists only 1 parameter to this function which is the main table. However, each subtable has 5 different keys that could be accessed.
| Field | Type |
| ----- | ---- |
| id | `integer` |
| unused (Optional) | `integer` |
| firstByte (Optional) | `integer` |
| model | [ModelExtendedId](#ModelExtendedId) |
| behavior | [BehaviorId](#BehaviorId) |

### Returns
- None

### C Prototype
N/A

[:arrow_up_small:](#)

<br />

## [get_exclamation_box_contents](#get_exclamation_box_contents)

Gets the contents that the exclamation box spawns. A single content has 5 keys: `id`, `unused`, `firstByte`, `model`, and `behavior`.
* `id`: Required; what value the box's oBehParams2ndByte needs to be to spawn this object.
* `unused`: Optional; unused by vanilla.
* `firstByte`: Optional; Overrides the 1st byte given to the spawned object.
* `model`: Required; The model that the object will spawn with. Uses `ModelExtendedId`.
* `behavior`: Required; The behavior ID that the object will spawn with. Uses `BehaviorId`.

### Lua Example
```lua
local contents = get_exclamation_box_contents()
for index, content in pairs(contents) do -- Enter the main table
   djui_chat_message_create("Table index " .. index) -- Print the current table index
      for key, value in pairs(content) do
         djui_chat_message_create(key .. ": " .. value) -- Print a key-value pair within this subtable
      end
   djui_chat_message_create("---------------------------------") -- Separator
end
```

### Parameters
- N/A

### Returns
The function itself does not return every key/value pair. Instead it returns the main table which holds all the subtables that hold each key/value pair.
| Field | Type |
| ----- | ---- |
| id | `integer` |
| unused (Optional) | `integer` |
| firstByte (Optional) | `integer` |
| model | [ModelExtendedId](#ModelExtendedId) |
| behavior | [BehaviorId](#BehaviorId) |

### C Prototype
N/A

[:arrow_up_small:](#)

<br />

## [cast_graph_node](#cast_graph_node)

Returns the specific GraphNode(...) the node is part of. Basically the reverse of `.node` or `.fnNode`.

### Lua Example
```lua
local marioGfx = gMarioStates[0].marioObj.header.gfx -- GraphNodeObject
local node = marioGfx.node -- GraphNode

print(marioGfx == cast_graph_node(node)) -- true
```

### Parameters
| Field | Type |
| ----- | ---- |
| node  | [GraphNode](structs.md#GraphNode) |

### Returns
- GraphNode(...)

### C Prototype
N/A

[:arrow_up_small:](#)

<br />

## [get_uncolored_string](#get_uncolored_string)

Removes color codes from a string.

### Lua Example
```lua
print(get_uncolored_string("\\#210059\\Colored \\#FF086F\\String")) -- "Colored String"
```

### Parameters
| Field | Type |
| ----- | ---- |
| str   | 'string' |

### Returns
- `string`

### C Prototype
N/A

[:arrow_up_small:](#)

<br />

## [gfx_set_command](#gfx_set_command)

Sets a display list command on the display list given.

If `command` includes parameter specifiers (subsequences beginning with `%`), the additional arguments following `command` are converted and inserted in `command` replacing their respective specifiers.

The number of provided parameters must be equal to the number of specifiers in `command`, and the order of parameters must be the same as the specifiers.

The following specifiers are allowed:
- `%i` for an `integer` parameter
- `%s` for a `string` parameter
- `%v` for a `Vtx` parameter
- `%t` for a `Texture` parameter
- `%g` for a `Gfx` parameter

### Lua Examples

Plain string:
```lua
gfx_set_command(gfx, "gsDPSetEnvColor(0x00, 0xFF, 0x00, 0xFF)")
```

With parameter specifiers:
```lua
r, g, b, a = 0x00, 0xFF, 0x00, 0xFF
gfx_set_command(gfx, "gsDPSetEnvColor(%i, %i, %i, %i)", r, g, b, a)
```

### Parameters
| Field | Type |
| ----- | ---- |
| gfx   | [Gfx](structs.md#Gfx) |
| command | `string` |
| parameters... | any of `integer`, `string`, `Gfx`, `Texture`, `Vtx` |

### Returns
- None

### C Prototype
N/A

[:arrow_up_small:](#)

<br />

"""

############################################################################

total_functions = 0
total_doc_functions = 0
header_h = ""

def reject_line(line):
    if len(line) == 0:
        return True
    if '(' not in line:
        return True
    if ')' not in line:
        return True
    if ';' not in line:
        return True

def normalize_type(t):
    if 'char' not in t:
        t = t.replace('const', '')

    t = t.strip()
    if ' ' in t:
        parts = t.split(' ', 1)
        t = parts[0] + ' ' + parts[1].replace(' ', '')
    return t

def alter_type(t):
    if t.startswith('enum '):
        return 'int'
    return t

############################################################################

def build_vec_types():
    s = gen_comment_header("vec types")
    for type_name, vec_type in VEC_TYPES.items():

        # New
        s += "void smlua_new_%s(%s src) {\n" % (type_name.lower(), type_name)
        s += "    struct lua_State *L = gLuaState;\n"
        s += "    lua_newtable(L);\n"
        s += "    int tableIndex = lua_gettop(L);\n"
        for lua_field, c_field in vec_type["fields_mapping"].items():
            s += "    lua_pushstring(L, \"%s\");\n" % (lua_field)
            s += "    lua_push%s(L, src%s);\n" % (vec_type["field_lua_type"], c_field)
            s += "    lua_settable(L, tableIndex);\n"
        s += "}\n\n"

        # Get
        s += "void smlua_get_%s(%s dest, int index) {\n" % (type_name.lower(), type_name)
        for lua_field, c_field in vec_type["fields_mapping"].items():
            s += "    dest%s = smlua_get_%s_field(index, \"%s\");\n" % (c_field, vec_type["field_lua_type"], lua_field)
        s += "}\n\n"

        # Push
        s += "void smlua_push_%s(%s src, int index) {\n" % (type_name.lower(), type_name)
        for lua_field, c_field in vec_type["fields_mapping"].items():
            s += "    smlua_push_%s_field(index, \"%s\", src%s);\n" % (vec_type["field_lua_type"], lua_field, c_field)
        for lua_field, c_field in vec_type.get('optional_fields_mapping', {}).items():
            s += "    smlua_push_%s_field(index, \"%s\", src%s);\n" % (vec_type["field_lua_type"], lua_field, c_field)
        s += "}\n\n"

    return s

############################################################################

def build_param(fid, param, i):
    ptype = alter_type(param['type'])
    pid = param['identifier']

    if "struct TextureInfo" in ptype and "*" in ptype:
        return '    struct TextureInfo *texInfo = smlua_to_texture_info(L, %d);\n' % (i)

    if ptype in VEC_TYPES:
        if ptype == "Vec3f" and fid in SOUND_FUNCTIONS:
            return vec3f_sound_before.replace('$[IDENTIFIER]', str(pid)).replace('$[INDEX]', str(i))
        else:
            return (vec_type_before % (ptype, ptype.lower())).replace('$[IDENTIFIER]', str(pid)).replace('$[INDEX]', str(i))
    elif ptype == 'bool':
        return '    %s %s = smlua_to_boolean(L, %d);\n' % (ptype, pid, i)
    elif ptype in integer_types:
        return '    %s %s = smlua_to_integer(L, %d);\n' % (ptype, pid, i)
    elif ptype in number_types:
        return '    %s %s = smlua_to_number(L, %d);\n' % (ptype, pid, i)
    elif ptype == 'const char*':
        return '    %s %s = smlua_to_string(L, %d);\n' % (ptype, pid, i)
    elif ptype == 'LuaFunction':
        return '    %s %s = smlua_to_lua_function(L, %d);\n' % (ptype, pid, i)
    elif translate_type_to_lot(ptype) == 'LOT_POINTER':
        lvt = translate_type_to_lvt(ptype)
        return '    %s %s = (%s)smlua_to_cpointer(L, %d, %s);\n' % (ptype, pid, ptype, i, lvt)
    else:
        lot = translate_type_to_lot(ptype)
        s = '  %s %s = (%s)smlua_to_cobject(L, %d, %s);' % (ptype, pid, ptype, i, lot)

        if '???' in lot or "GRAPHNODE" in lot:
            s = '//' + s + ' <--- UNIMPLEMENTED'
        else:
            s = '  ' + s

        return s + '\n'

def build_param_after(param, i):
    ptype = param['type']
    pid = param['identifier']
    is_output = param.get('out', False)

    if ptype in VEC_TYPES and is_output:
        return (vec_type_after % (ptype.lower())).replace('$[IDENTIFIER]', str(pid)).replace('$[INDEX]', str(i))
    else:
        return ''

def build_call(function):
    ftype = alter_type(function['type'])
    fid = function['identifier']

    ccall = '%s(%s)' % (fid, ', '.join([x['identifier'] for x in function['params']]))

    if ftype == 'void':
        return '    %s;\n' % ccall
    # We can't possibly know the type of a void pointer,
    # So we just don't return anything from it
    elif ftype == 'void *':
        return '    %s;\n' % ccall

    if ftype in VECP_TYPES:
        return '    %s;\n' % ccall

    flot = translate_type_to_lot(ftype)

    lfunc = 'UNIMPLEMENTED -->'
    if ftype in integer_types:
        lfunc = 'lua_pushinteger'
    elif ftype in number_types:
        lfunc = 'lua_pushnumber'
    elif ftype == 'bool':
        lfunc = 'lua_pushboolean'
    elif ftype == 'char*':
        lfunc = 'lua_pushstring'
    elif ftype == 'const char*':
        lfunc = 'lua_pushstring'
    elif translate_type_to_lot(ftype) == 'LOT_POINTER':
        lvt = translate_type_to_lvt(ftype)
        return '    smlua_push_pointer(L, %s, (void*)%s, NULL);\n' % (lvt, ccall)
    elif '???' not in flot and flot != 'LOT_NONE':
        return '    smlua_push_object(L, %s, %s, NULL);\n' % (flot, ccall)

    return '    %s(L, %s);\n' % (lfunc, ccall)

def build_function(function, do_extern):
    s = ''
    fid = function['identifier']

    if fid in override_function_version_excludes:
        s += '#ifndef ' + override_function_version_excludes[fid] + '\n'

    if len(function['params']) <= 0:
        s += 'int smlua_func_%s(UNUSED lua_State* L) {\n' % function['identifier']
    else:
        s += 'int smlua_func_%s(lua_State* L) {\n' % function['identifier']

    # make sure the bhv functions have a current object
    fname = function['filename']
    if fname == 'behavior_actions.h' or fname == 'obj_behaviors_2.h' or fname == 'obj_behaviors.h':
        if 'bhv_' in fid:
            s += '    if (!gCurrentObject) { return 0; }\n'

    s += """    if (L == NULL) { return 0; }\n
    int top = lua_gettop(L);
    if (top != %d) {
        LOG_LUA_LINE("Improper param count for '%%s': Expected %%u, Received %%u", "%s", %d, top);
        return 0;
    }\n\n""" % (len(function['params']), function['identifier'], len(function['params']))

    is_interact_func = fid.startswith('interact_') and fname == 'interaction.h'

    i = 1
    for param in function['params']:
        if is_interact_func and param['identifier'] == 'interactType':
            s += "    // interactType skipped so mods can't lie about what interaction it is\n"
        else:
            s += build_param(fid, param, i)
            s += '    if (!gSmLuaConvertSuccess) { LOG_LUA("Failed to convert parameter %%u for function \'%%s\'", %d, "%s"); return 0; }\n' % (i, fid)
        i += 1
    s += '\n'

    if do_extern:
        s += '    extern %s\n' % function['line']

    if is_interact_func:
        # special case for interaction functions to call the hooks associated with interactions
        s += "    lua_pushinteger(L, process_interaction(m, " + fid.upper() + ", o, " + fid + "));\n"
    else:
        s += build_call(function)

    i = 1
    for param in function['params']:
        s += build_param_after(param, i)
        i += 1
    s += '\n'

    # To allow chaining vector functions calls, return the table corresponding to the `OUT` parameter
    if function['type'] in VECP_TYPES:
        for i, param in enumerate(function['params']):
            if param.get('out', False):
                s += '    lua_settop(L, %d);\n' % (i + 1)
                break

    s += '    return 1;\n}\n'

    if fid in override_function_version_excludes:
        s += '#endif\n'

    function['implemented'] = 'UNIMPLEMENTED' not in s
    if 'UNIMPLEMENTED' in s:
        s = "/*\n" + s + "*/\n"
    else:
        global total_functions
        total_functions += 1
        if function['description'] != "":
            global total_doc_functions
            total_doc_functions += 1
        elif verbose:
            print("UNDOCUMENTED: " + function['filename'] + ":     " + function['line'])

    return s + "\n"

def build_functions(processed_files):
    s = ''
    for processed_file in processed_files:
        s += gen_comment_header(processed_file['filename'])

        for function in processed_file['functions']:
            function['filename'] = processed_file['filename']
            s += build_function(function, processed_file['extern'])
    return s

def build_bind(function):
    fid = function['identifier']
    s = 'smlua_bind_function(L, "%s", smlua_func_%s);' % (fid, fid)
    if function['implemented']:
        s = '    ' + s
        # There is no point in adding the ifndef statement if the function is commented out here anyways.
        # So we only do it on implemented functions.
        if fid in override_function_version_excludes:
            s = '#ifndef ' + override_function_version_excludes[fid] + '\n' + s
            s += '\n#endif'
    else:
        s = '    //' + s + ' <--- UNIMPLEMENTED'
    return s + "\n"

def build_binds(processed_files):
    s = ''
    for processed_file in processed_files:
        s += "\n    // " + processed_file['filename'] + "\n"

        for function in processed_file['functions']:
            s += build_bind(function)
    return s

def build_includes():
    s = ''
    for f in in_files:
        if not f.endswith('.h'):
            continue
        s += '#include "%s"\n' % f
    return s

############################################################################

def process_function(fname, line, description):
    if fname in override_allowed_functions:
        found_match = False
        for pattern in override_allowed_functions[fname]:
            if re.search(pattern, line) != None:
                found_match = True
                break
        if not found_match:
            return None

    if fname in override_disallowed_functions:
        for pattern in override_disallowed_functions[fname]:
            if re.search(pattern, line) != None:
                return None

    function = {}

    line = line.strip()
    function['line'] = line
    function['description'] = description  # use the specific description passed in

    line = line.replace('UNUSED', '')

    match = re.search(r'[a-zA-Z0-9_]+\(', line)
    function['type'] = normalize_type(line[0:match.span()[0]])
    function['identifier'] = match.group()[0:-1]

    function['params'] = []
    params_str = line.split('(', 1)[1].rsplit(')', 1)[0].strip()
    if len(params_str) == 0 or params_str == 'void':
        pass
    else:
        param_index = 0
        for param_str in params_str.split(','):
            param = {}
            param_str = param_str.strip()

            if param_str.startswith('OUT '):
                param['out'] = True
                param_str = param_str[len('OUT'):].strip()

            if param_str.endswith('*') or ' ' not in param_str:
                param['type'] = normalize_type(param_str)
                param['identifier'] = 'arg%d' % param_index
            else:
                match = re.search(r'[a-zA-Z0-9_\[\]]+$', param_str)
                if match == None:
                    return None
                param['type'] = normalize_type(param_str[0:match.span()[0]])
                param['identifier'] = match.group()

            # override Vec3s/f
            if param['identifier'] == 'pos':
                if param['type'].replace(' ', '') == 'f32*':
                    param['type'] = 'Vec3f'
                if param['type'].replace(' ', '') == 's16*':
                    param['type'] = 'Vec3s'

            # remember lua function params
            lf_key = fname + '::' + function['identifier'] + '::' + param['identifier']
            if param['type'] == 'LuaFunction' and lf_key in lua_function_params:
                param['lua_function_params'] = lua_function_params[lf_key]

            function['params'].append(param)
            param_index += 1

    return function

def process_functions(fname, file_str, extracted_descriptions):
    functions = []
    for line in file_str.splitlines():
        if reject_line(line):
            global rejects
            rejects += line + '\n'
            continue
        line = line.strip()
        description = extracted_descriptions.get(line, "")
        fn = process_function(fname, line, description)
        if fn == None:
            continue
        functions.append(fn)
    return functions

def process_file(fname):
    processed_file = {}
    processed_file['filename'] = fname.replace('\\', '/').split('/')[-1]
    processed_file['extern'] = fname.endswith('.c')

    extracted_str, extracted_descriptions = extract_functions(fname)
    processed_file['functions'] = process_functions(fname, extracted_str, extracted_descriptions)

    return processed_file

def process_files():
    processed_files = []
    files = sorted(in_files, key=lambda d: d.split('/')[-1])
    for f in files:
        processed_files.append(process_file(f))
    return processed_files


############################################################################

fuzz_from = ""
fuzz_to = ""
fuzz_functions = ""

def output_fuzz_function(fname, function):
    first = True
    comment = ' -- '
    fid = function['identifier']

    line = '        function() return ' + fid + '('

    for param in function['params']:
        if first:
            first = False
        else:
            line += ', '
            comment += ', '
        pid = param['identifier']
        ptype = param['type']
        ptype, plink = translate_type_to_lua(ptype)

        if '(' in pid or '[' in pid or ']' in pid:
            continue

        line += translate_type_to_rnd(ptype)

        comment += ptype

    line += ') end,\n'
    #if len(line) >= 80:
    #    line = line + '\n        ' + comment + '\n'
    #else:
    #    line = line.ljust(80) + comment + '\n'

    global fuzz_functions
    fuzz_functions += line

def output_fuzz_file():
    global fuzz_functions
    with open(fuzz_from) as f:
        file_str = f.read()
    with open(fuzz_to, 'w', encoding='utf-8', newline='\n') as f:
        f.write(file_str.replace('-- $[FUNCS]', fuzz_functions))

############################################################################

def doc_should_document(fname, identifier):
    if fname in override_hide_functions:
        found_match = False
        for pattern in override_hide_functions[fname]:
            if re.search(pattern, identifier) != None:
                found_match = True
                break
        return not found_match
    return True

def doc_page_link(page_num):
    if page_num == 1:
        return 'functions.md'
    else:
        return 'functions-%d.md' % page_num

def doc_function_index(processed_files):
    s = '# Supported Functions\n'
    s += manual_index_documentation
    count = 0
    for processed_file in processed_files:
        page_num = processed_file['page_num']
        s += '- %s\n' % processed_file['filename']
        for function in processed_file['functions']:
            if not function['implemented']:
                continue
            if not doc_should_document(processed_file['filename'], function['identifier']):
                continue

            s += '   - [%s](%s#%s)\n' % (function['identifier'], doc_page_link(page_num), function['identifier'])
        s += '\n<br />\n\n'

    return s

def doc_lua_func_param(param):
    s = 'LuaFunction('

    lfp = param['lua_function_params']
    first_lfp = True

    for lfp_type in lfp:
        if not first_lfp:
            lfp_type += ', '
        first_lfp = False

        lfp_type, lfp_link = translate_type_to_lua(lfp_type)

        if lfp_link:
            s += '[%s](%s)' % (lfp_type, lfp_link)
        else:
            s += lfp_type

    s += ')'
    return s

def doc_function(fname, function):
    if not function['implemented']:
        return ''

    # debug print out lua nuke functions
    if len(sys.argv) >= 2 and sys.argv[1] == 'fuzz':
        output_fuzz_function(fname, function)

    if not doc_should_document(fname, function['identifier']):
        return ''

    fid = function['identifier']
    s = '\n## [%s](#%s)\n' % (fid, fid)

    description = function.get('description', "")

    rtype, rlink = translate_type_to_lua(function['type'])
    param_str = ', '.join([x['identifier'] for x in function['params']])

    if description != "":
        s += '\n### Description\n'
        s +=  f'{description}\n'

    s += "\n### Lua Example\n"
    if rtype != None:
        s += "`local %sValue = %s(%s)`\n" % (rtype.replace('`', '').split(' ')[0], fid, param_str)
    else:
        s += "`%s(%s)`\n" % (fid, param_str)

    s += '\n### Parameters\n'
    if len(function['params']) > 0:
        s += '| Field | Type |\n'
        s += '| ----- | ---- |\n'
        for param in function['params']:
            pid = param['identifier']
            ptype = param['type']
            ptype, plink = translate_type_to_lua(ptype)

            # build lua function params
            if param['type'] == 'LuaFunction' and 'lua_function_params' in param:
                ptype = doc_lua_func_param(param)

            if plink:
                s += '| %s | [%s](%s) |\n'  % (pid, ptype, plink)
                continue

            s += '| %s | %s |\n'  % (pid, ptype)

    else:
        s += '- None\n'

    s += '\n### Returns\n'
    if rtype != None:
        if rlink:
            s += '[%s](%s)\n' % (rtype, rlink)
        else:
            s += '- %s\n' % rtype
    else:
        s += '- None\n'


    s += '\n### C Prototype\n'
    s += '`%s`\n' % function['line'].strip()

    s += '\n[:arrow_up_small:](#)\n\n<br />\n'

    return s

def doc_functions(fname, functions):
    s = ''
    for function in functions:
        s += doc_function(fname, function)
    return s

def doc_files(processed_files):
    pages = {}
    page_num = 1
    page_len_limit = 150000
    extra_space = 25000

    s = '## [:rewind: Lua Reference](lua.md)\n\n'
    s += '---\n\n$[FUNCTION_NAV_HERE]\n\n---\n\n'
    s += '$[FUNCTION_INDEX_HERE]'
    s += manual_documentation
    for processed_file in processed_files:
        s_file  = '\n---'
        s_file += '\n# functions from %s\n\n<br />\n\n' % processed_file['filename']
        s_file += doc_functions(processed_file['filename'], processed_file['functions'])

        if len(s) + len(s_file) + extra_space > page_len_limit:
            s += '---\n\n$[FUNCTION_NAV_HERE]\n\n'
            pages[page_num] = s
            s = '## [:rewind: Lua Functions](functions.md)\n\n'
            s += '---\n\n$[FUNCTION_NAV_HERE]\n\n'
            page_num += 1
            extra_space = 0

        s += s_file
        processed_file['page_num'] = page_num

    s += '\n---\n\n$[FUNCTION_NAV_HERE]\n\n'
    pages[page_num] = s

    for pnum in pages:
        buffer = pages[pnum]
        page_name = ''
        if pnum == 1:
            buffer = buffer.replace('$[FUNCTION_INDEX_HERE]', doc_function_index(processed_files))
            page_name = ''
        else:
            page_name = '-%d' % pnum

        # build up nav
        function_nav = ''
        if (pnum - 1) in pages:
            function_nav += '[< prev](%s) | ' % doc_page_link(pnum - 1)
        for pnum_nav in pages:
            if pnum_nav == pnum:
                function_nav += '%d' % pnum_nav
            else:
                function_nav += '[%d](%s)' % (pnum_nav, doc_page_link(pnum_nav))

            if (pnum_nav + 1) in pages:
                function_nav += ' | '
        if (pnum + 1) in pages:
            function_nav += ' | [next >](%s)' % doc_page_link(pnum + 1)

        buffer = buffer.replace('$[FUNCTION_NAV_HERE', function_nav)

        with open(get_path(out_filename_docs % page_name), 'w', encoding='utf-8', newline='\n') as out:
            out.write(buffer)

############################################################################

def_pointers = []

def def_function(fname, function):
    s = ''
    if not function['implemented']:
        return ''

    fid = function['identifier']
    if not doc_should_document(fname, fid):
        return ''

    rtype, rlink = translate_type_to_lua(function['type'])
    param_str = ', '.join([x['identifier'] for x in function['params']])

    if rtype == None:
        rtype = 'nil'

    if function['description'].startswith("[DEPRECATED"):
        s += "--- @deprecated\n"

    for param in function['params']:
        pid = param['identifier']
        ptype = param['type']
        ptype, plink = translate_type_to_lua(ptype)

        ptype = translate_to_def(ptype)
        if ptype.startswith('Pointer_') and ptype not in def_pointers:
            def_pointers.append(ptype)

        s += '--- @param %s %s\n' % (pid, ptype)

    rtype = translate_to_def(rtype)
    if rtype.startswith('Pointer_') and rtype not in def_pointers:
        def_pointers.append(rtype)

    if rtype != "nil":
        s += '--- @return %s\n' % rtype
    if function['description'] != "":
        s += "--- %s\n" % (function['description'])
    s += "function %s(%s)\n    -- ...\nend\n\n" % (fid, param_str)

    return s


def def_files(processed_files):
    s = '-- AUTOGENERATED FOR CODE EDITORS --\n\n'
    for processed_file in processed_files:
        for function in processed_file['functions']:
            s += def_function(processed_file['filename'], function)

    for def_pointer in def_pointers:
        s += '--- @alias %s %s\n' % (def_pointer, def_pointer[8:])

    for vecp_type, vec_type in VECP_TYPES.items():
        s += '--- @alias %s %s\n' % (vecp_type, vec_type)

    with open(get_path(out_filename_defs), 'w', encoding='utf-8', newline='\n') as out:
        out.write(s)

############################################################################

def main():
    processed_files = process_files()

    built_vec_types = build_vec_types()
    built_functions = build_functions(processed_files)
    built_binds = build_binds(processed_files)
    built_includes = build_includes()

    filename = get_path(out_filename)

    gen = template                                \
        .replace("$[TYPES]", built_vec_types)     \
        .replace("$[FUNCTIONS]", built_functions) \
        .replace("$[BINDS]", built_binds)         \
        .replace("$[INCLUDES]", built_includes)

    with open(filename, 'w', encoding='utf-8', newline='\n') as out:
        out.write(gen)

    if rejects != "":
        print(f"REJECTS:\n{rejects}")

    doc_files(processed_files)
    def_files(processed_files)

    global total_functions
    print(f"Total functions: {total_functions}")
    global total_doc_functions
    print(f"Total documented functions: {total_doc_functions} ({round((total_doc_functions / total_functions) * 100, 2)}%)")

    if len(sys.argv) >= 2 and sys.argv[1] == 'fuzz':
        output_fuzz_file()

if __name__ == '__main__':
   main()
