## [:rewind: Lua Functions](functions.md)

---

[< prev](functions-5.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | 6]


---
# functions from seqplayer.h

<br />


## [sequence_player_get_tempo](#sequence_player_get_tempo)

### Description
Gets the tempo of `player`

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

## [sequence_player_set_tempo](#sequence_player_set_tempo)

### Description
Sets the `tempo` of `player`. Resets when another sequence is played

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

## [sequence_player_get_tempo_acc](#sequence_player_get_tempo_acc)

### Description
Gets the tempoAcc (tempo accumulation) of `player`

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

## [sequence_player_set_tempo_acc](#sequence_player_set_tempo_acc)

### Description
Sets the `tempoAcc` (tempo accumulation) of `player`. Resets when another sequence is played

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

## [sequence_player_get_transposition](#sequence_player_get_transposition)

### Description
Gets the transposition (pitch) of `player`

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

## [sequence_player_set_transposition](#sequence_player_set_transposition)

### Description
Sets the `transposition` (pitch) of `player`. Resets when another sequence is played

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

## [sequence_player_get_volume](#sequence_player_get_volume)

### Description
Gets the volume of `player`

### Lua Example
`local numberValue = sequence_player_get_volume(player)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |

### Returns
- `number`

### C Prototype
`f32 sequence_player_get_volume(u8 player);`

[:arrow_up_small:](#)

<br />

## [sequence_player_get_fade_volume](#sequence_player_get_fade_volume)

### Description
Gets the fade volume of `player`

### Lua Example
`local numberValue = sequence_player_get_fade_volume(player)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |

### Returns
- `number`

### C Prototype
`f32 sequence_player_get_fade_volume(u8 player);`

[:arrow_up_small:](#)

<br />

## [sequence_player_get_mute_volume_scale](#sequence_player_get_mute_volume_scale)

### Description
Gets the mute volume scale of `player`

### Lua Example
`local numberValue = sequence_player_get_mute_volume_scale(player)`

### Parameters
| Field | Type |
| ----- | ---- |
| player | `integer` |

### Returns
- `number`

### C Prototype
`f32 sequence_player_get_mute_volume_scale(u8 player);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_anim_utils.h

<br />


## [get_mario_vanilla_animation](#get_mario_vanilla_animation)

### Description
Gets a vanilla mario Animation with `index`

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

## [smlua_anim_util_set_animation](#smlua_anim_util_set_animation)

### Description
Sets the animation of `obj` to the animation `name` corresponds to

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

## [smlua_anim_util_get_current_animation_name](#smlua_anim_util_get_current_animation_name)

### Description
Gets the name of the current animation playing on `obj`, returns `nil` if there's no name

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

---
# functions from smlua_audio_utils.h

<br />


## [smlua_audio_utils_reset_all](#smlua_audio_utils_reset_all)

### Description
Resets all custom sequences back to vanilla

### Lua Example
`smlua_audio_utils_reset_all()`

### Parameters
- None

### Returns
- None

### C Prototype
`void smlua_audio_utils_reset_all(void);`

[:arrow_up_small:](#)

<br />

## [smlua_audio_utils_replace_sequence](#smlua_audio_utils_replace_sequence)

### Description
Replaces the sequence corresponding to `sequenceId` with one called `m64Name`.m64 with `bankId` and `defaultVolume`

### Lua Example
`smlua_audio_utils_replace_sequence(sequenceId, bankId, defaultVolume, m64Name)`

### Parameters
| Field | Type |
| ----- | ---- |
| sequenceId | `integer` |
| bankId | `integer` |
| defaultVolume | `integer` |
| m64Name | `string` |

### Returns
- None

### C Prototype
`void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, u8 defaultVolume, const char* m64Name);`

[:arrow_up_small:](#)

<br />

## [audio_stream_load](#audio_stream_load)

### Description
Loads an `audio` stream by `filename` (with extension)

### Lua Example
`local ModAudioValue = audio_stream_load(filename)`

### Parameters
| Field | Type |
| ----- | ---- |
| filename | `string` |

### Returns
[ModAudio](structs.md#ModAudio)

### C Prototype
`struct ModAudio* audio_stream_load(const char* filename);`

[:arrow_up_small:](#)

<br />

## [audio_stream_destroy](#audio_stream_destroy)

### Description
Destroys an `audio` stream

### Lua Example
`audio_stream_destroy(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_stream_destroy(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_play](#audio_stream_play)

### Description
Plays an `audio` stream with `volume`. `restart` sets the elapsed time back to 0.

### Lua Example
`audio_stream_play(audio, restart, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| restart | `boolean` |
| volume | `number` |

### Returns
- None

### C Prototype
`void audio_stream_play(struct ModAudio* audio, bool restart, f32 volume);`

[:arrow_up_small:](#)

<br />

## [audio_stream_pause](#audio_stream_pause)

### Description
Pauses an `audio` stream

### Lua Example
`audio_stream_pause(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_stream_pause(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_stop](#audio_stream_stop)

### Description
Stops an `audio` stream

### Lua Example
`audio_stream_stop(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_stream_stop(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_position](#audio_stream_get_position)

### Description
Gets the position of an `audio` stream in seconds

### Lua Example
`local numberValue = audio_stream_get_position(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_position(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_position](#audio_stream_set_position)

### Description
Sets the position of an `audio` stream in seconds

### Lua Example
`audio_stream_set_position(audio, pos)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| pos | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_position(struct ModAudio* audio, f32 pos);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_looping](#audio_stream_get_looping)

### Description
Gets if an `audio` stream is looping or not

### Lua Example
`local booleanValue = audio_stream_get_looping(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- `boolean`

### C Prototype
`bool audio_stream_get_looping(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_looping](#audio_stream_set_looping)

### Description
Sets if an `audio` stream is looping or not

### Lua Example
`audio_stream_set_looping(audio, looping)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| looping | `boolean` |

### Returns
- None

### C Prototype
`void audio_stream_set_looping(struct ModAudio* audio, bool looping);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_loop_points](#audio_stream_set_loop_points)

### Description
Sets an `audio` stream's loop points in samples

### Lua Example
`audio_stream_set_loop_points(audio, loopStart, loopEnd)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| loopStart | `integer` |
| loopEnd | `integer` |

### Returns
- None

### C Prototype
`void audio_stream_set_loop_points(struct ModAudio* audio, s64 loopStart, s64 loopEnd);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_frequency](#audio_stream_get_frequency)

### Description
Gets the frequency of an `audio` stream

### Lua Example
`local numberValue = audio_stream_get_frequency(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_frequency(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_frequency](#audio_stream_set_frequency)

### Description
Sets the frequency of an `audio` stream

### Lua Example
`audio_stream_set_frequency(audio, freq)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| freq | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_frequency(struct ModAudio* audio, f32 freq);`

[:arrow_up_small:](#)

<br />

## [audio_stream_get_volume](#audio_stream_get_volume)

### Description
Gets the volume of an `audio` stream

### Lua Example
`local numberValue = audio_stream_get_volume(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- `number`

### C Prototype
`f32 audio_stream_get_volume(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_stream_set_volume](#audio_stream_set_volume)

### Description
Sets the volume of an `audio` stream

### Lua Example
`audio_stream_set_volume(audio, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| volume | `number` |

### Returns
- None

### C Prototype
`void audio_stream_set_volume(struct ModAudio* audio, f32 volume);`

[:arrow_up_small:](#)

<br />

## [audio_sample_load](#audio_sample_load)

### Description
Loads an `audio` sample

### Lua Example
`local ModAudioValue = audio_sample_load(filename)`

### Parameters
| Field | Type |
| ----- | ---- |
| filename | `string` |

### Returns
[ModAudio](structs.md#ModAudio)

### C Prototype
`struct ModAudio* audio_sample_load(const char* filename);`

[:arrow_up_small:](#)

<br />

## [audio_sample_destroy](#audio_sample_destroy)

### Description
Destroys an `audio` sample

### Lua Example
`audio_sample_destroy(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_sample_destroy(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_sample_stop](#audio_sample_stop)

### Description
Stops an `audio` sample

### Lua Example
`audio_sample_stop(audio)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |

### Returns
- None

### C Prototype
`void audio_sample_stop(struct ModAudio* audio);`

[:arrow_up_small:](#)

<br />

## [audio_sample_play](#audio_sample_play)

### Description
Plays an `audio` sample at `position` with `volume`

### Lua Example
`audio_sample_play(audio, position, volume)`

### Parameters
| Field | Type |
| ----- | ---- |
| audio | [ModAudio](structs.md#ModAudio) |
| position | [Vec3f](structs.md#Vec3f) |
| volume | `number` |

### Returns
- None

### C Prototype
`void audio_sample_play(struct ModAudio* audio, Vec3f position, f32 volume);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_camera_utils.h

<br />


## [camera_reset_overrides](#camera_reset_overrides)

### Description
Resets camera config overrides

### Lua Example
`camera_reset_overrides()`

### Parameters
- None

### Returns
- None

### C Prototype
`void camera_reset_overrides(void);`

[:arrow_up_small:](#)

<br />

## [camera_freeze](#camera_freeze)

### Description
Freezes the camera by not updating it

### Lua Example
`camera_freeze()`

### Parameters
- None

### Returns
- None

### C Prototype
`void camera_freeze(void);`

[:arrow_up_small:](#)

<br />

## [camera_unfreeze](#camera_unfreeze)

### Description
Unfreezes the camera

### Lua Example
`camera_unfreeze()`

### Parameters
- None

### Returns
- None

### C Prototype
`void camera_unfreeze(void);`

[:arrow_up_small:](#)

<br />

## [camera_is_frozen](#camera_is_frozen)

### Description
Checks if the camera is frozen

### Lua Example
`local booleanValue = camera_is_frozen()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_is_frozen(void);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_allow_only_mods](#camera_romhack_allow_only_mods)

### Description
Sets if only mods are allowed to modify the camera (Enabling prevents the player from modifying the camera through the settings)

### Lua Example
`camera_romhack_allow_only_mods(allow)`

### Parameters
| Field | Type |
| ----- | ---- |
| allow | `integer` |

### Returns
- None

### C Prototype
`void camera_romhack_allow_only_mods(u8 allow);`

[:arrow_up_small:](#)

<br />

## [camera_set_romhack_override](#camera_set_romhack_override)

### Description
Sets the romhack camera override status

### Lua Example
`camera_set_romhack_override(rco)`

### Parameters
| Field | Type |
| ----- | ---- |
| rco | [enum RomhackCameraOverride](constants.md#enum-RomhackCameraOverride) |

### Returns
- None

### C Prototype
`void camera_set_romhack_override(enum RomhackCameraOverride rco);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_allow_centering](#camera_romhack_allow_centering)

### Description
Sets if the romhack camera should allow centering, triggered with the L button

### Lua Example
`camera_romhack_allow_centering(allow)`

### Parameters
| Field | Type |
| ----- | ---- |
| allow | `integer` |

### Returns
- None

### C Prototype
`void camera_romhack_allow_centering(u8 allow);`

[:arrow_up_small:](#)

<br />

## [camera_allow_toxic_gas_camera](#camera_allow_toxic_gas_camera)

### Description
Sets if the romhack camera should fly above poison gas

### Lua Example
`camera_allow_toxic_gas_camera(allow)`

### Parameters
| Field | Type |
| ----- | ---- |
| allow | `integer` |

### Returns
- None

### C Prototype
`void camera_allow_toxic_gas_camera(u8 allow);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_allow_dpad_usage](#camera_romhack_allow_dpad_usage)

### Description
Sets if the romhack camera should allow D-Pad movement

### Lua Example
`camera_romhack_allow_dpad_usage(allow)`

### Parameters
| Field | Type |
| ----- | ---- |
| allow | `integer` |

### Returns
- None

### C Prototype
`void camera_romhack_allow_dpad_usage(u8 allow);`

[:arrow_up_small:](#)

<br />

## [rom_hack_cam_set_collisions](#rom_hack_cam_set_collisions)

### Description
Toggles collision settings for the ROM hack camera. This enables or disables specific collision behaviors in modded levels

### Lua Example
`rom_hack_cam_set_collisions(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `integer` |

### Returns
- None

### C Prototype
`void rom_hack_cam_set_collisions(u8 enable);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_set_zoomed_in_dist](#camera_romhack_set_zoomed_in_dist)

### Description
Sets the romhack camera's zoomed in distance (Default: 900)

### Lua Example
`camera_romhack_set_zoomed_in_dist(val)`

### Parameters
| Field | Type |
| ----- | ---- |
| val | `integer` |

### Returns
- None

### C Prototype
`void camera_romhack_set_zoomed_in_dist(u32 val);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_set_zoomed_out_dist](#camera_romhack_set_zoomed_out_dist)

### Description
Sets the romhack camera's zoomed out additional distance (Default: 500)

### Lua Example
`camera_romhack_set_zoomed_out_dist(val)`

### Parameters
| Field | Type |
| ----- | ---- |
| val | `integer` |

### Returns
- None

### C Prototype
`void camera_romhack_set_zoomed_out_dist(u32 val);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_set_zoomed_in_height](#camera_romhack_set_zoomed_in_height)

### Description
Sets the romhack camera's zoomed in height (Default: 300)

### Lua Example
`camera_romhack_set_zoomed_in_height(val)`

### Parameters
| Field | Type |
| ----- | ---- |
| val | `integer` |

### Returns
- None

### C Prototype
`void camera_romhack_set_zoomed_in_height(u32 val);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_set_zoomed_out_height](#camera_romhack_set_zoomed_out_height)

### Description
Sets the romhack camera's zoomed out additional height (Default: 150)

### Lua Example
`camera_romhack_set_zoomed_out_height(val)`

### Parameters
| Field | Type |
| ----- | ---- |
| val | `integer` |

### Returns
- None

### C Prototype
`void camera_romhack_set_zoomed_out_height(u32 val);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_get_zoomed_in_dist](#camera_romhack_get_zoomed_in_dist)

### Description
Gets the romhack camera's zoomed in distance

### Lua Example
`local integerValue = camera_romhack_get_zoomed_in_dist()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_romhack_get_zoomed_in_dist(void);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_get_zoomed_out_dist](#camera_romhack_get_zoomed_out_dist)

### Description
Gets the romhack camera's additional zoomed out distance

### Lua Example
`local integerValue = camera_romhack_get_zoomed_out_dist()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_romhack_get_zoomed_out_dist(void);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_get_zoomed_in_height](#camera_romhack_get_zoomed_in_height)

### Description
Gets the romhack camera's zoomed in height

### Lua Example
`local integerValue = camera_romhack_get_zoomed_in_height()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_romhack_get_zoomed_in_height(void);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_get_zoomed_out_height](#camera_romhack_get_zoomed_out_height)

### Description
Gets the romhack camera's additional zoomed out height

### Lua Example
`local integerValue = camera_romhack_get_zoomed_out_height()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_romhack_get_zoomed_out_height(void);`

[:arrow_up_small:](#)

<br />

## [camera_get_romhack_override](#camera_get_romhack_override)

### Description
Gets the current romhack camera override status

### Lua Example
`local enumValue = camera_get_romhack_override()`

### Parameters
- None

### Returns
[enum RomhackCameraOverride](constants.md#enum-RomhackCameraOverride)

### C Prototype
`enum RomhackCameraOverride camera_get_romhack_override(void);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_get_allow_centering](#camera_romhack_get_allow_centering)

### Description
Gets if the romhack camera should allow centering

### Lua Example
`local integerValue = camera_romhack_get_allow_centering()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 camera_romhack_get_allow_centering(void);`

[:arrow_up_small:](#)

<br />

## [camera_get_allow_toxic_gas_camera](#camera_get_allow_toxic_gas_camera)

### Description
Gets if the romhack camera should fly above poison gas

### Lua Example
`local integerValue = camera_get_allow_toxic_gas_camera()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 camera_get_allow_toxic_gas_camera(void);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_get_allow_dpad_usage](#camera_romhack_get_allow_dpad_usage)

### Description
Gets if the romhack camera should allow D-Pad movement

### Lua Example
`local integerValue = camera_romhack_get_allow_dpad_usage()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 camera_romhack_get_allow_dpad_usage(void);`

[:arrow_up_small:](#)

<br />

## [camera_romhack_get_collisions](#camera_romhack_get_collisions)

### Description
Gets if the romhack camera has surface collisions

### Lua Example
`local integerValue = camera_romhack_get_collisions()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 camera_romhack_get_collisions(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_free_cam_enabled](#camera_config_is_free_cam_enabled)

### Description
Checks if Free Camera is enabled

### Lua Example
`local booleanValue = camera_config_is_free_cam_enabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_free_cam_enabled(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_analog_cam_enabled](#camera_config_is_analog_cam_enabled)

### Description
Checks if Analog Camera is enabled

### Lua Example
`local booleanValue = camera_config_is_analog_cam_enabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_analog_cam_enabled(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_dpad_enabled](#camera_config_is_dpad_enabled)

### Description
Checks if Freecam DPad Behavior is enabled

### Lua Example
`local booleanValue = camera_config_is_dpad_enabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_dpad_enabled(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_collision_enabled](#camera_config_is_collision_enabled)

### Description
Checks if Camera Collision is enabled

### Lua Example
`local booleanValue = camera_config_is_collision_enabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_collision_enabled(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_mouse_look_enabled](#camera_config_is_mouse_look_enabled)

### Description
Checks if Mouse Look is enabled

### Lua Example
`local booleanValue = camera_config_is_mouse_look_enabled()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_mouse_look_enabled(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_x_inverted](#camera_config_is_x_inverted)

### Description
Checks if camera X is inverted

### Lua Example
`local booleanValue = camera_config_is_x_inverted()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_x_inverted(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_is_y_inverted](#camera_config_is_y_inverted)

### Description
Checks if camera Y is inverted

### Lua Example
`local booleanValue = camera_config_is_y_inverted()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_is_y_inverted(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_x_sensitivity](#camera_config_get_x_sensitivity)

### Description
Gets camera X sensitivity

### Lua Example
`local integerValue = camera_config_get_x_sensitivity()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_x_sensitivity(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_y_sensitivity](#camera_config_get_y_sensitivity)

### Description
Gets camera Y sensitivity

### Lua Example
`local integerValue = camera_config_get_y_sensitivity()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_y_sensitivity(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_aggression](#camera_config_get_aggression)

### Description
Gets camera aggression

### Lua Example
`local integerValue = camera_config_get_aggression()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_aggression(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_pan_level](#camera_config_get_pan_level)

### Description
Gets camera pan level

### Lua Example
`local integerValue = camera_config_get_pan_level()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_pan_level(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_deceleration](#camera_config_get_deceleration)

### Description
Gets camera deceleration

### Lua Example
`local integerValue = camera_config_get_deceleration()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u32 camera_config_get_deceleration(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_get_centering](#camera_config_get_centering)

### Description
Gets if the L button will center the camera

### Lua Example
`local booleanValue = camera_config_get_centering()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_config_get_centering(void);`

[:arrow_up_small:](#)

<br />

## [camera_config_enable_free_cam](#camera_config_enable_free_cam)

### Description
Overrides if Free Camera is enabled

### Lua Example
`camera_config_enable_free_cam(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_enable_free_cam(bool enable);`

[:arrow_up_small:](#)

<br />

## [camera_config_enable_analog_cam](#camera_config_enable_analog_cam)

### Description
Overrides if Analog Camera is enabled

### Lua Example
`camera_config_enable_analog_cam(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_enable_analog_cam(bool enable);`

[:arrow_up_small:](#)

<br />

## [camera_config_enable_centering](#camera_config_enable_centering)

### Description
Overrides if the L button will center the camera

### Lua Example
`camera_config_enable_centering(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_enable_centering(bool enable);`

[:arrow_up_small:](#)

<br />

## [camera_config_enable_dpad](#camera_config_enable_dpad)

### Description
Overrides if Freecam DPad Behavior is enabled

### Lua Example
`camera_config_enable_dpad(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_enable_dpad(bool enable);`

[:arrow_up_small:](#)

<br />

## [camera_config_enable_collisions](#camera_config_enable_collisions)

### Description
Overrides if Camera Collision is enabled

### Lua Example
`camera_config_enable_collisions(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_enable_collisions(bool enable);`

[:arrow_up_small:](#)

<br />

## [camera_config_enable_mouse_look](#camera_config_enable_mouse_look)

### Description
Overrides if camera mouse look is enabled

### Lua Example
`camera_config_enable_mouse_look(enable)`

### Parameters
| Field | Type |
| ----- | ---- |
| enable | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_enable_mouse_look(bool enable);`

[:arrow_up_small:](#)

<br />

## [camera_config_invert_x](#camera_config_invert_x)

### Description
Overrides if camera X is inverted

### Lua Example
`camera_config_invert_x(invert)`

### Parameters
| Field | Type |
| ----- | ---- |
| invert | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_invert_x(bool invert);`

[:arrow_up_small:](#)

<br />

## [camera_config_invert_y](#camera_config_invert_y)

### Description
Overrides if camera Y is inverted

### Lua Example
`camera_config_invert_y(invert)`

### Parameters
| Field | Type |
| ----- | ---- |
| invert | `boolean` |

### Returns
- None

### C Prototype
`void camera_config_invert_y(bool invert);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_x_sensitivity](#camera_config_set_x_sensitivity)

### Description
Overrides camera X sensitivity

### Lua Example
`camera_config_set_x_sensitivity(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_x_sensitivity(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_y_sensitivity](#camera_config_set_y_sensitivity)

### Description
Overrides camera Y sensitivity

### Lua Example
`camera_config_set_y_sensitivity(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_y_sensitivity(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_aggression](#camera_config_set_aggression)

### Description
Overrides camera aggression

### Lua Example
`camera_config_set_aggression(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_aggression(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_pan_level](#camera_config_set_pan_level)

### Description
Overrides camera pan level

### Lua Example
`camera_config_set_pan_level(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_pan_level(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_config_set_deceleration](#camera_config_set_deceleration)

### Description
Overrides camera deceleration

### Lua Example
`camera_config_set_deceleration(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `integer` |

### Returns
- None

### C Prototype
`void camera_config_set_deceleration(u32 value);`

[:arrow_up_small:](#)

<br />

## [camera_get_checking_surfaces](#camera_get_checking_surfaces)

### Description
Checks if the camera should account for surfaces

### Lua Example
`local booleanValue = camera_get_checking_surfaces()`

### Parameters
- None

### Returns
- `boolean`

### C Prototype
`bool camera_get_checking_surfaces(void);`

[:arrow_up_small:](#)

<br />

## [camera_set_checking_surfaces](#camera_set_checking_surfaces)

### Description
Sets if the camera should account for surfaces

### Lua Example
`camera_set_checking_surfaces(value)`

### Parameters
| Field | Type |
| ----- | ---- |
| value | `boolean` |

### Returns
- None

### C Prototype
`void camera_set_checking_surfaces(bool value);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_collision_utils.h

<br />


## [collision_find_floor](#collision_find_floor)

### Description
Finds a potential floor at the given `x`, `y`, and `z` values

### Lua Example
`local SurfaceValue = collision_find_floor(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface* collision_find_floor(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [collision_find_ceil](#collision_find_ceil)

### Description
Finds a potential ceiling at the given `x`, `y`, and `z` values

### Lua Example
`local SurfaceValue = collision_find_ceil(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface* collision_find_ceil(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [get_water_surface_pseudo_floor](#get_water_surface_pseudo_floor)

### Description
Gets the generated water floor surface used when riding a shell

### Lua Example
`local SurfaceValue = get_water_surface_pseudo_floor()`

### Parameters
- None

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface* get_water_surface_pseudo_floor(void);`

[:arrow_up_small:](#)

<br />

## [smlua_collision_util_get](#smlua_collision_util_get)

### Description
Gets the `Collision` with `name`

### Lua Example
`local PointerValue = smlua_collision_util_get(name)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |

### Returns
- `Pointer` <`Collision`>

### C Prototype
`Collision* smlua_collision_util_get(const char* name);`

[:arrow_up_small:](#)

<br />

## [collision_get_temp_wall_collision_data](#collision_get_temp_wall_collision_data)

### Description
Returns a temporary wall collision data pointer

### Lua Example
`local WallCollisionDataValue = collision_get_temp_wall_collision_data()`

### Parameters
- None

### Returns
[WallCollisionData](structs.md#WallCollisionData)

### C Prototype
`struct WallCollisionData* collision_get_temp_wall_collision_data(void);`

[:arrow_up_small:](#)

<br />

## [get_surface_from_wcd_index](#get_surface_from_wcd_index)

### Description
Gets the surface corresponding to `index` from `wcd`

### Lua Example
`local SurfaceValue = get_surface_from_wcd_index(wcd, index)`

### Parameters
| Field | Type |
| ----- | ---- |
| wcd | [WallCollisionData](structs.md#WallCollisionData) |
| index | `integer` |

### Returns
[Surface](structs.md#Surface)

### C Prototype
`struct Surface* get_surface_from_wcd_index(struct WallCollisionData* wcd, s8 index);`

[:arrow_up_small:](#)

<br />

## [smlua_collision_util_get_current_terrain_collision](#smlua_collision_util_get_current_terrain_collision)

### Description
Gets the current level terrain collision

### Lua Example
`local PointerValue = smlua_collision_util_get_current_terrain_collision()`

### Parameters
- None

### Returns
- `Pointer` <`Collision`>

### C Prototype
`Collision* smlua_collision_util_get_current_terrain_collision(void);`

[:arrow_up_small:](#)

<br />

## [smlua_collision_util_get_level_collision](#smlua_collision_util_get_level_collision)

### Description
Gets the `level` terrain collision from `area`

### Lua Example
`local PointerValue = smlua_collision_util_get_level_collision(level, area)`

### Parameters
| Field | Type |
| ----- | ---- |
| level | `integer` |
| area | `integer` |

### Returns
- `Pointer` <`Collision`>

### C Prototype
`Collision *smlua_collision_util_get_level_collision(u32 level, u16 area);`

[:arrow_up_small:](#)

<br />

## [smlua_collision_util_find_surface_types](#smlua_collision_util_find_surface_types)

### Description
Gets a table of the surface types from `data`

### Lua Example
`smlua_collision_util_find_surface_types(data)`

### Parameters
| Field | Type |
| ----- | ---- |
| data | `Pointer` <`Collision`> |

### Returns
- None

### C Prototype
`void smlua_collision_util_find_surface_types(Collision* data);`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_deprecated.h

<br />


---
# functions from smlua_gfx_utils.h

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
`void gfx_parse(Gfx *cmd, LuaFunction func);`

[:arrow_up_small:](#)

<br />

## [gfx_get_op](#gfx_get_op)

### Description
Gets the op of the display list command

### Lua Example
`local integerValue = gfx_get_op(cmd)`

### Parameters
| Field | Type |
| ----- | ---- |
| cmd | `Pointer` <`Gfx`> |

### Returns
- `integer`

### C Prototype
`u32 gfx_get_op(Gfx *cmd);`

[:arrow_up_small:](#)

<br />

## [gfx_get_display_list](#gfx_get_display_list)

### Description
Gets the display list from a display list command if it has the op `G_DL`

### Lua Example
`local PointerValue = gfx_get_display_list(cmd)`

### Parameters
| Field | Type |
| ----- | ---- |
| cmd | `Pointer` <`Gfx`> |

### Returns
- `Pointer` <`Gfx`>

### C Prototype
`Gfx *gfx_get_display_list(Gfx *cmd);`

[:arrow_up_small:](#)

<br />

## [gfx_get_vertex_buffer](#gfx_get_vertex_buffer)

### Description
Gets the vertex buffer from a display list command if it has the op `G_VTX`

### Lua Example
`local PointerValue = gfx_get_vertex_buffer(cmd)`

### Parameters
| Field | Type |
| ----- | ---- |
| cmd | `Pointer` <`Gfx`> |

### Returns
- `Pointer` <`Vtx`>

### C Prototype
`Vtx *gfx_get_vertex_buffer(Gfx *cmd);`

[:arrow_up_small:](#)

<br />

## [gfx_get_vertex_count](#gfx_get_vertex_count)

### Description
Gets the number of vertices from a display list command if it has the op `G_VTX`

### Lua Example
`local integerValue = gfx_get_vertex_count(cmd)`

### Parameters
| Field | Type |
| ----- | ---- |
| cmd | `Pointer` <`Gfx`> |

### Returns
- `integer`

### C Prototype
`u16 gfx_get_vertex_count(Gfx *cmd);`

[:arrow_up_small:](#)

<br />

## [gfx_get_length](#gfx_get_length)

### Description
Gets the max length of a display list

### Lua Example
`local integerValue = gfx_get_length(gfx)`

### Parameters
| Field | Type |
| ----- | ---- |
| gfx | `Pointer` <`Gfx`> |

### Returns
- `integer`

### C Prototype
`u32 gfx_get_length(Gfx *gfx);`

[:arrow_up_small:](#)

<br />

## [gfx_get_command](#gfx_get_command)

### Description
Gets a command of a display list at position `offset`

### Lua Example
`local PointerValue = gfx_get_command(gfx, offset)`

### Parameters
| Field | Type |
| ----- | ---- |
| gfx | `Pointer` <`Gfx`> |
| offset | `integer` |

### Returns
- `Pointer` <`Gfx`>

### C Prototype
`Gfx *gfx_get_command(Gfx *gfx, u32 offset);`

[:arrow_up_small:](#)

<br />

## [gfx_get_next_command](#gfx_get_next_command)

### Description
Gets the next command of a given display list pointer. Intended to use in a for loop

### Lua Example
`local PointerValue = gfx_get_next_command(gfx)`

### Parameters
| Field | Type |
| ----- | ---- |
| gfx | `Pointer` <`Gfx`> |

### Returns
- `Pointer` <`Gfx`>

### C Prototype
`Gfx *gfx_get_next_command(Gfx *gfx);`

[:arrow_up_small:](#)

<br />

## [gfx_copy](#gfx_copy)

### Description
Copies `length` commands from display list `src` to display list `dest`

### Lua Example
`gfx_copy(dest, src, length)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Pointer` <`Gfx`> |
| src | `Pointer` <`Gfx`> |
| length | `integer` |

### Returns
- None

### C Prototype
`void gfx_copy(Gfx *dest, Gfx *src, u32 length);`

[:arrow_up_small:](#)

<br />

## [gfx_create](#gfx_create)

### Description
Creates a new named display list of `length` commands

### Lua Example
`local PointerValue = gfx_create(name, length)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |
| length | `integer` |

### Returns
- `Pointer` <`Gfx`>

### C Prototype
`Gfx *gfx_create(const char *name, u32 length);`

[:arrow_up_small:](#)

<br />

## [gfx_resize](#gfx_resize)

### Description
Resizes a display list created by `gfx_create`

### Lua Example
`gfx_resize(gfx, newLength)`

### Parameters
| Field | Type |
| ----- | ---- |
| gfx | `Pointer` <`Gfx`> |
| newLength | `integer` |

### Returns
- None

### C Prototype
`void gfx_resize(Gfx *gfx, u32 newLength);`

[:arrow_up_small:](#)

<br />

## [gfx_delete](#gfx_delete)

### Description
Deletes a display list created by `gfx_create`

### Lua Example
`gfx_delete(gfx)`

### Parameters
| Field | Type |
| ----- | ---- |
| gfx | `Pointer` <`Gfx`> |

### Returns
- None

### C Prototype
`void gfx_delete(Gfx *gfx);`

[:arrow_up_small:](#)

<br />

## [gfx_delete_all](#gfx_delete_all)

### Description
Deletes all display lists created by `gfx_create`

### Lua Example
`gfx_delete_all()`

### Parameters
- None

### Returns
- None

### C Prototype
`void gfx_delete_all();`

[:arrow_up_small:](#)

<br />

## [vtx_get_count](#vtx_get_count)

### Description
Gets the max count of vertices of a vertex buffer

### Lua Example
`local integerValue = vtx_get_count(vtx)`

### Parameters
| Field | Type |
| ----- | ---- |
| vtx | `Pointer` <`Vtx`> |

### Returns
- `integer`

### C Prototype
`u32 vtx_get_count(Vtx *vtx);`

[:arrow_up_small:](#)

<br />

## [vtx_get_vertex](#vtx_get_vertex)

### Description
Gets a vertex of a vertex buffer at position `offset`

### Lua Example
`local PointerValue = vtx_get_vertex(vtx, offset)`

### Parameters
| Field | Type |
| ----- | ---- |
| vtx | `Pointer` <`Vtx`> |
| offset | `integer` |

### Returns
- `Pointer` <`Vtx`>

### C Prototype
`Vtx *vtx_get_vertex(Vtx *vtx, u32 offset);`

[:arrow_up_small:](#)

<br />

## [vtx_get_next_vertex](#vtx_get_next_vertex)

### Description
Gets the next vertex of a given vertex pointer. Intended to use in a for loop

### Lua Example
`local PointerValue = vtx_get_next_vertex(vtx)`

### Parameters
| Field | Type |
| ----- | ---- |
| vtx | `Pointer` <`Vtx`> |

### Returns
- `Pointer` <`Vtx`>

### C Prototype
`Vtx *vtx_get_next_vertex(Vtx *vtx);`

[:arrow_up_small:](#)

<br />

## [vtx_copy](#vtx_copy)

### Description
Copies `count` vertices from vertex buffer `src` to vertex buffer `dest`

### Lua Example
`vtx_copy(dest, src, count)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | `Pointer` <`Vtx`> |
| src | `Pointer` <`Vtx`> |
| count | `integer` |

### Returns
- None

### C Prototype
`void vtx_copy(Vtx *dest, Vtx *src, u32 count);`

[:arrow_up_small:](#)

<br />

## [vtx_create](#vtx_create)

### Description
Creates a new named vertex buffer of `count` vertices

### Lua Example
`local PointerValue = vtx_create(name, count)`

### Parameters
| Field | Type |
| ----- | ---- |
| name | `string` |
| count | `integer` |

### Returns
- `Pointer` <`Vtx`>

### C Prototype
`Vtx *vtx_create(const char *name, u32 count);`

[:arrow_up_small:](#)

<br />

## [vtx_resize](#vtx_resize)

### Description
Resizes a vertex buffer created by `vtx_create`

### Lua Example
`vtx_resize(vtx, newCount)`

### Parameters
| Field | Type |
| ----- | ---- |
| vtx | `Pointer` <`Vtx`> |
| newCount | `integer` |

### Returns
- None

### C Prototype
`void vtx_resize(Vtx *vtx, u32 newCount);`

[:arrow_up_small:](#)

<br />

## [vtx_delete](#vtx_delete)

### Description
Deletes a vertex buffer created by `vtx_create`

### Lua Example
`vtx_delete(vtx)`

### Parameters
| Field | Type |
| ----- | ---- |
| vtx | `Pointer` <`Vtx`> |

### Returns
- None

### C Prototype
`void vtx_delete(Vtx *vtx);`

[:arrow_up_small:](#)

<br />

## [vtx_delete_all](#vtx_delete_all)

### Description
Deletes all vertex buffers created by `vtx_create`

### Lua Example
`vtx_delete_all()`

### Parameters
- None

### Returns
- None

### C Prototype
`void vtx_delete_all();`

[:arrow_up_small:](#)

<br />

---
# functions from smlua_level_utils.h

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

---
# functions from smlua_misc_utils.h

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

## [get_temp_s32_pointer](#get_temp_s32_pointer)

### Description
Returns a temporary signed 32-bit integer pointer with its value set to `initialValue`

### Lua Example
`local PointerValue = get_temp_s32_pointer(initialValue)`

### Parameters
| Field | Type |
| ----- | ---- |
| initialValue | `integer` |

### Returns
- `Pointer` <`integer`>

### C Prototype
`s32* get_temp_s32_pointer(s32 initialValue);`

[:arrow_up_small:](#)

<br />

## [deref_s32_pointer](#deref_s32_pointer)

### Description
Gets the signed 32-bit integer value from `pointer`

### Lua Example
`local integerValue = deref_s32_pointer(pointer)`

### Parameters
| Field | Type |
| ----- | ---- |
| pointer | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 deref_s32_pointer(s32* pointer);`

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

## [djui_get_playerlist_page_index](#djui_get_playerlist_page_index)

### Description
Gets the DJUI playerlist's page index

### Lua Example
`local integerValue = djui_get_playerlist_page_index()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`u8 djui_get_playerlist_page_index(void);`

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

## [hud_get_value](#hud_get_value)

### Description
Gets a HUD display value

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

## [get_mario_anim_part_pos](#get_mario_anim_part_pos)

### Description
Retrieves the animated part position associated to `animPart` from the MarioState `m` and stores it into `pos`. Returns `true` on success or `false` on failure

### Lua Example
`local booleanValue = get_mario_anim_part_pos(m, animPart, pos)`

### Parameters
| Field | Type |
| ----- | ---- |
| m | [MarioState](structs.md#MarioState) |
| animPart | `integer` |
| pos | [Vec3f](structs.md#Vec3f) |

### Returns
- `boolean`

### C Prototype
`bool get_mario_anim_part_pos(struct MarioState *m, u32 animPart, Vec3f pos);`

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

## [get_environment_region](#get_environment_region)

### Description
Gets an environment region (gas/water boxes) height value

### Lua Example
`local integerValue = get_environment_region(index)`

### Parameters
| Field | Type |
| ----- | ---- |
| index | `integer` |

### Returns
- `integer`

### C Prototype
`s16 get_environment_region(u8 index);`

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
`void set_environment_region(u8 index, s16 value);`

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

## [geo_get_current_root](#geo_get_current_root)

### Description
Gets the current GraphNodeRoot

### Lua Example
`local GraphNodeRootValue = geo_get_current_root()`

### Parameters
- None

### Returns
[GraphNodeRoot](structs.md#GraphNodeRoot)

### C Prototype
`struct GraphNodeRoot* geo_get_current_root(void);`

[:arrow_up_small:](#)

<br />

## [geo_get_current_master_list](#geo_get_current_master_list)

### Description
Gets the current GraphNodeMasterList

### Lua Example
`local GraphNodeMasterListValue = geo_get_current_master_list()`

### Parameters
- None

### Returns
[GraphNodeMasterList](structs.md#GraphNodeMasterList)

### C Prototype
`struct GraphNodeMasterList* geo_get_current_master_list(void);`

[:arrow_up_small:](#)

<br />

## [geo_get_current_perspective](#geo_get_current_perspective)

### Description
Gets the current GraphNodePerspective

### Lua Example
`local GraphNodePerspectiveValue = geo_get_current_perspective()`

### Parameters
- None

### Returns
[GraphNodePerspective](structs.md#GraphNodePerspective)

### C Prototype
`struct GraphNodePerspective* geo_get_current_perspective(void);`

[:arrow_up_small:](#)

<br />

## [geo_get_current_camera](#geo_get_current_camera)

### Description
Gets the current GraphNodeCamera

### Lua Example
`local GraphNodeCameraValue = geo_get_current_camera()`

### Parameters
- None

### Returns
[GraphNodeCamera](structs.md#GraphNodeCamera)

### C Prototype
`struct GraphNodeCamera* geo_get_current_camera(void);`

[:arrow_up_small:](#)

<br />

## [geo_get_current_held_object](#geo_get_current_held_object)

### Description
Gets the current GraphNodeHeldObject

### Lua Example
`local GraphNodeHeldObjectValue = geo_get_current_held_object()`

### Parameters
- None

### Returns
[GraphNodeHeldObject](structs.md#GraphNodeHeldObject)

### C Prototype
`struct GraphNodeHeldObject* geo_get_current_held_object(void);`

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

---
# functions from smlua_text_utils.h

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

---
# functions from sound_init.h

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

---
# functions from spawn_sound.h

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

---
# functions from surface_collision.h

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

## [closest_point_to_triangle](#closest_point_to_triangle)

### Description
Gets the closest point of the triangle to `src` and returns it in `out`.

### Lua Example
`closest_point_to_triangle(surf, src, out)`

### Parameters
| Field | Type |
| ----- | ---- |
| surf | [Surface](structs.md#Surface) |
| src | [Vec3f](structs.md#Vec3f) |
| out | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void closest_point_to_triangle(struct Surface* surf, Vec3f src, Vec3f out);`

[:arrow_up_small:](#)

<br />

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

[< prev](functions-5.md) | [1](functions.md) | [2](functions-2.md) | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | 6]

