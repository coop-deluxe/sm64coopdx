--- @type integer
FONT_TINY = -1

--- @type integer
ANIM_FLAG_FORWARD = (1 << 1)

SPECIAL_WARP_CAKE             = -1 --- @type integer
SPECIAL_WARP_GODDARD          = -2 --- @type integer
SPECIAL_WARP_GODDARD_GAMEOVER = -3 --- @type integer
SPECIAL_WARP_TITLE            = -8 --- @type integer
SPECIAL_WARP_LEVEL_SELECT     = -9 --- @type integer

-----------------------
-- Renamed functions --
-----------------------

rom_hack_cam_set_collisions = camera_romhack_set_collisions
camera_romhack_allow_centering = camera_romhack_allow_switchable
camera_romhack_get_allow_centering = camera_romhack_get_allow_switchable
bhv_star_door_loop_2 = bhv_star_door_loop_update_render_state
absf_2 = math.abs
cur_obj_enable_rendering_2 = cur_obj_enable_rendering
cur_obj_can_mario_activate_textbox_2 = cur_obj_can_mario_activate_textbox
reset_rumble_timers_2 = reset_rumble_timers_vibrate
cur_obj_play_sound_1 = cur_obj_play_sound_if_visible
cur_obj_play_sound_2 = cur_obj_play_sound_and_rumble_if_visible
bit_shift_left = function (shift) return math.u8(1 << shift) end

--------------------
-- Math functions --
--------------------
--- Note: These functions were originally in smlua_math_utils.h,
--- but performed worse (~2x slower) than built-in Lua math functions

min = math.min
minf = math.min
max = math.max
maxf = math.max
sqr = math.sqr
sqrf = math.sqr
clamp = math.clamp
clampf = math.clamp
hypotf = math.hypot

-------------------------
-- Old audio functions --
-------------------------

function audio_sample_load(filename) return audio_load(filename, MA_TYPE_SAMPLE) end
function audio_stream_load(filename) return audio_load(filename, MA_TYPE_STREAM) end
audio_sample_play = audio_play
audio_stream_play = audio_play
audio_sample_destroy = audio_destroy
audio_stream_destroy = audio_destroy
audio_sample_stop = audio_stop
audio_stream_stop = audio_stop
audio_stream_pause = audio_pause
audio_stream_get_position = audio_get_position
audio_stream_set_position = audio_set_position
audio_stream_get_looping = audio_get_looping
audio_stream_set_looping = audio_set_looping
audio_stream_set_loop_points = audio_set_loop_points
audio_stream_get_frequency = audio_get_frequency
audio_stream_set_frequency = audio_set_frequency
audio_stream_get_volume = audio_get_volume
audio_stream_set_volume = audio_set_volume

-- compatibility band-aid
function return_self(self) return self end