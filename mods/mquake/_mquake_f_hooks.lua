-- _mquake_a_constants
-- _mquake_b_actions_predefine
-- _mquake_c_actions
-- _mquake_d_physics
-- _mquake_e_hooks

hook_mario_action(ACT_DM_GROUNDED_MOVEMENT, act_dm_grounded_movement)
hook_mario_action(ACT_DM_GROUNDED_IDLE, act_dm_grounded_movement)
hook_mario_action(ACT_DM_AIR_MOVEMENT, act_dm_air_movement) 
hook_mario_action(ACT_DM_GROUNDED_MOVEMENT_METAL, act_dm_grounded_movement)
hook_mario_action(ACT_DM_AIR_MOVEMENT_METAL, act_dm_air_movement) 
hook_mario_action(ACT_DM_WATER_MOVEMENT, act_dm_water_movement)
hook_event(HOOK_UPDATE, local_update)
hook_event(HOOK_ON_PLAYER_CONNECTED, on_player_connected)
hook_event(HOOK_OVERRIDE_PHYS_STEP_DEFACTO_SPEED, override_defacto)
hook_event(HOOK_CHARACTER_SOUND, allow_voice)
hook_event(HOOK_BEFORE_SET_MARIO_ACTION, before_set_mario_action)
hook_event(HOOK_ON_SET_MARIO_ACTION, on_set_mario_action)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_BEFORE_PHYS_STEP, before_phys_step)
hook_event(HOOK_ALLOW_HAZARD_SURFACE, function(m) return false end)
hook_event(HOOK_ON_INTERACT, on_interact)
hook_event(HOOK_ALLOW_INTERACT, allow_interact)
hook_event(HOOK_ON_PVP_ATTACK, on_pvp)
hook_event(HOOK_ALLOW_PVP_ATTACK, allow_pvp)
hook_event(HOOK_ON_OBJECT_RENDER, on_object_render)
hook_event(HOOK_ON_HUD_RENDER_BEHIND, render_hud_effects)