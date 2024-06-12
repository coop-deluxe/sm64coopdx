hook_mario_action(ACT_DM_GROUNDED_MOVEMENT, act_dm_grounded_movement)
hook_mario_action(ACT_DM_GROUNDED_IDLE, act_dm_grounded_movement)
hook_mario_action(ACT_DM_AIR_MOVEMENT, act_dm_air_movement) 
hook_mario_action(ACT_GROUND_POUND, act_dm_ground_pound) 
hook_mario_action(ACT_DM_GROUND_POUND_METAL, act_dm_ground_pound) 
hook_mario_action(ACT_DM_GROUNDED_MOVEMENT_METAL, act_dm_grounded_movement)
hook_mario_action(ACT_DM_AIR_MOVEMENT_METAL, act_dm_air_movement) 
hook_mario_action(ACT_DM_POLE_MOVEMENT, act_dm_pole_movement) 
hook_mario_action(ACT_DM_WATER_MOVEMENT, act_dm_water_movement)
hook_event(HOOK_ON_PLAYER_CONNECTED, on_player_connected)
hook_event(HOOK_MARIO_OVERRIDE_PHYS_STEP_DEFACTO_SPEED, override_defacto)
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
hook_event(HOOK_UPDATE, on_game_update)

hook_chat_command('mq', "[list] - \\#FFE0A0\\List all commands", mquake)






--- Server ---


if (network_is_server()) then
	hook_chat_command('mq_server', "[list] - \\#A0FFE0\\List all convars/settings", mquake_server)
end



hook_on_sync_table_change(gGlobalSyncTable, 'Convar_StickySlope', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'StickySlope'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal==true).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal==true).."'\\#A0FFE0\\.") end
	sv_sticky = newVal
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_AirAccelerate', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'AirAccelerate'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal).."'\\#A0FFE0\\.") end
	sv_airaccelerate_value = newVal
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_Accelerate', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'Accelerate'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal).."'\\#A0FFE0\\.") end
	sv_accelerate = newVal
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_AirClamp', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'AirClamp'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal).."'\\#A0FFE0\\.") end
	sv_playerclamp_air = newVal
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_PlayerSpeed', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'PlayerSpeed'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal).."'\\#A0FFE0\\.") end
	sv_maxspeed = 180*newVal
	sv_maxspeed_crouch = 80*newVal
	sv_maxspeed_water = 180*newVal
	sv_playerspeed = 90*newVal
	sv_playerspeed_water = 90*newVal
	sv_playerspeed_water_shell = 300*newVal
	sv_upspeed_water = 180*newVal
	sv_playerspeed_crouch = 40*newVal
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_Gravity', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'Gravity'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal).."'\\#A0FFE0\\.") end
	sv_gravity = newVal
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_PlayerFriction', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'PlayerFriction'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal).."'\\#A0FFE0\\.") end
	sv_friction = 4*newVal
	sv_waterfriction = 2.5*newVal
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_PlayerJumpHeight', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'PlayerJumpHeight'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal).."'\\#A0FFE0\\.") end
	sv_jumpheight =newVal
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_PlayerAllow_GroundPound', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'PlayerAllow_GroundPound'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal==true).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal==true).."'\\#A0FFE0\\.") end
	sv_groundpound = newVal==true
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_PlayerAllow_WallJump', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'PlayerAllow_WallJump'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal==true).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal==true).."'\\#A0FFE0\\.") end
	sv_walljump = newVal==true
end)
hook_on_sync_table_change(gGlobalSyncTable, 'Convar_PlayerAllow_Interact', 'server', function(tag, oldVal, newVal) 
	if (oldVal ~= newVal) and (oldVal ~= nil) then djui_chat_message_create("\\#A0FFE0\\Cvar \\#14FF14\\'PlayerAllow_Interact'\\#A0FFE0\\ changed from \\#14FF14\\'"..tostring(oldVal==true).."'\\#A0FFE0\\ to \\#14FF14\\'"..tostring(newVal==true).."'\\#A0FFE0\\.") end
	sv_interact = newVal==true
end)