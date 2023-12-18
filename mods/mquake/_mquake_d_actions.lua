-- _mquake_a_constants
-- _mquake_b_actions_predefine
-- _mquake_c_actions
-- _mquake_d_physics
-- _mquake_e_hooks
-- localize functions to improve performance - _mquake_d_actions.lua
local set_mario_action,vec3f_add,vec3f_length,perform_ground_step,vec3f_copy,perform_air_step = set_mario_action,vec3f_add,vec3f_length,perform_ground_step,vec3f_copy,perform_air_step


local function play_local_footstep_sounds(m,rate,max) 
	cl_footstepTimer = cl_footstepTimer + rate
	if (cl_footstepTimer >= max) then
		m.marioObj.header.gfx.animInfo.animFrame = 0
		play_step_sound(m, 0, 1)
		cl_footstepTimer = 0
	end
end

--- @param m MarioState
act_dm_grounded_movement = function(m)
	-- AngleVectors(m)
	local metal_underwater = (m.flags & MARIO_METAL_CAP) ~= 0 and m.pos.y <= m.waterLevel-sv_playersubmergelevel
	local crouch = gPlayerSyncTable[m.playerIndex].playerCrouching
	
	if (metal_underwater and m.action ~= ACT_DM_GROUNDED_MOVEMENT_METAL) then
		SV_PlayerMovement_Store(m,true)
		set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT_METAL, 0)
		m.action = ACT_DM_GROUNDED_MOVEMENT_METAL
		SV_PlayerMovement_Store(m,false)
		-- return
	elseif (m.action == ACT_DM_GROUNDED_MOVEMENT_METAL and not metal_underwater) then
		set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT, 0)
		m.action = ACT_DM_GROUNDED_MOVEMENT
		-- return
	end
	
	if (m.floor ~= nil) then
		if (m.floor.normal.y <= SV_GetSurfaceStandableMinimum(m.floor.type,m.area.terrainType)) then
			SV_PlayerMovement_Relative(m)
			set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
			act_dm_air_movement(m)
			return
		end
	end
	
	if (m.controller.buttonDown & A_BUTTON) ~= 0 and m.floor ~= nil then
		set_character_animation(m, CHAR_ANIM_IDLE_HEAD_CENTER)
		if (m.vel.y < 0) then m.vel.y = m.vel.y * 0.25 end
		
		if (metal_underwater) then
			vec3f_add(m.vel,vec3_qscale(m.floor.normal,-0.4,20,40,-0.4))
			m.vel.y = m.vel.y + 100
		else
			vec3f_add(m.vel,vec3_qscale(m.floor.normal,-0.4,40,-0.4))
			m.vel.y = m.vel.y + 110
		end
		
		if (m.vel.y > 320) then m.vel.y = 320 end
		
		play_character_sound(m,CHAR_SOUND_YAH_WAH_HOO)
		
		play_step_sound(m, 0, 1)
		
		
		SV_PlayerMovement_Relative(m)
		
		-- SV_PlayerMovement_Store(m,true)
		
		set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
		act_dm_air_movement(m)
		return
	end
	
	SV_PlayerMovement(m)
	
	if (m.playerIndex == 0) then
		set_character_animation(m, CHAR_ANIM_A_POSE)
		if (not cl_bowserthrow) then
			local len = vec3f_length(vec3_qscale(m.vel,1,0,1))
			if (len < 1) then
				m.faceAngle.y = m.area.camera.yaw + 0x8000
				if (m.action == ACT_DM_GROUNDED_MOVEMENT) then m.action = ACT_DM_GROUNDED_IDLE end 
			else
				play_local_footstep_sounds(m,len * 0.0625,60) 
				m.faceAngle.y = atan2s(m.vel.z, m.vel.x)
				if (m.action == ACT_DM_GROUNDED_IDLE) then m.action = ACT_DM_GROUNDED_MOVEMENT end 
			end
		end
	else
		local scale = m.forwardVel
		if (scale < 5) then
			set_character_animation(m, ifelse(crouch,CHAR_ANIM_CROUCHING,CHAR_ANIM_FIRST_PERSON))
		else
			play_step_sound(m, ifelse(crouch,26,9), ifelse(crouch,79,45))
			set_character_anim_with_accel(m, ifelse(crouch,CHAR_ANIM_CRAWLING,CHAR_ANIM_RUNNING), scale*ifelse(crouch,0x4000,0x2400))
		end
	end
	m.forwardVel = vec3f_length(vec3_qscale(m.vel,sv_scalerate,0,sv_scalerate))
	
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_ground_step(m)
	SV_PlayerMovement_Scale(m,true)
	
	if (stepResult == GROUND_STEP_LEFT_GROUND) then 
		SV_PlayerMovement_Relative(m)
		if (m.action == ACT_DM_GROUNDED_MOVEMENT_METAL) then
			set_mario_action(m, ACT_DM_AIR_MOVEMENT_METAL, 0)
		else
			set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
		end
	end
	if m.wall ~= nil and (stepResult == GROUND_STEP_HIT_WALL) then --or (stepResult == GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS) or (stepResult == GROUND_STEP_HIT_WALL_STOP_QSTEPS)) then 
		vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.wall.normal,-1.0,0.0))
	end
	
	if (m.pos.y <= m.waterLevel-sv_playersubmergelevel and m.waterLevel > m.floorHeight + sv_playersubmergelevel) and (m.flags & MARIO_METAL_CAP) == 0 then
		if (m.action == ACT_DM_GROUNDED_MOVEMENT_METAL) then
			set_mario_action(m, ACT_DM_AIR_MOVEMENT_METAL, 0)
		else
			set_mario_action(m, ACT_DM_WATER_MOVEMENT, 0)
		end
	end
	
	-- SV_PlayerMovement_Store(m,true)
end

--- @param m MarioState
act_dm_air_movement = function(m)
	-- AngleVectors(m)
	local metal_underwater = (m.flags & MARIO_METAL_CAP) ~= 0 and m.pos.y <= m.waterLevel-sv_playersubmergelevel
	local act = m.action
	local crouch = gPlayerSyncTable[m.playerIndex].playerCrouching
	
	if (metal_underwater and act ~= ACT_DM_AIR_MOVEMENT_METAL) then
		SV_PlayerMovement_Store(m,true)
		set_mario_action(m, ACT_DM_AIR_MOVEMENT_METAL, 0)
		m.action = ACT_DM_AIR_MOVEMENT_METAL
		SV_PlayerMovement_Store(m,false)
		-- return
	elseif (act == ACT_DM_AIR_MOVEMENT_METAL and not metal_underwater) then
		set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
		m.action = ACT_DM_AIR_MOVEMENT
		-- return
	end
	
	if (m.controller.buttonPressed & Z_TRIG) ~= 0 and (m.controller.buttonDown & A_BUTTON) == 0 and m.heldObj == nil and m.prevAction ~= ACT_DM_WATER_MOVEMENT then 
		if ((m.flags & MARIO_METAL_CAP) == 0) then
			set_mario_action(m, ACT_GROUND_POUND, 2)
			m.vel.x = m.vel.x * sv_scalerate
			m.vel.z = m.vel.z * sv_scalerate
			m.vel.y = -20 * sv_scalerate
			m.forwardVel = vec3f_length(vec3_qscale(m.vel,1,0,1))
			m.actionState = 2
			return 
		else
			m.vel.y = -200
		end
	end
	
	SV_PlayerMovement(m)
	
	if (m.playerIndex == 0) then
		if (vec3f_length(vec3_qscale(m.vel,1,0,1)) < 1) then
			m.faceAngle.y = m.area.camera.yaw + 0x8000
		else
			m.faceAngle.y = atan2s(m.vel.z, m.vel.x)
		end
		set_character_animation(m, CHAR_ANIM_A_POSE)
	else
		set_character_animation(m, ifelse(crouch,CHAR_ANIM_FAST_LONGJUMP,ifelse(m.vel.y < 0,CHAR_ANIM_DOUBLE_JUMP_FALL,CHAR_ANIM_DOUBLE_JUMP_RISE)))
	end
	
	if (metal_underwater) then
		m.vel.y = m.vel.y - 6 ; if (m.vel.y < -400) then m.vel.y = -400 end
	else
		m.vel.y = m.vel.y - 12 ; if (m.vel.y < -600) then m.vel.y = -600 end
	end
	
	if ((m.flags & MARIO_WING_CAP) ~= 0 and (m.controller.buttonDown & A_BUTTON) ~= 0 and m.vel.y < 60) then m.vel.y = 60 end
	
	local preStepYVel = m.vel.y
	
	m.forwardVel = vec3f_length(vec3_qscale(m.vel,sv_scalerate,0,sv_scalerate))
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_air_step(m,0)
	SV_PlayerMovement_Scale(m,true)
	
	if (stepResult == AIR_STEP_LANDED) then 
		if (m.floor ~= nil) then
			if (m.floor.normal.y > SV_GetSurfaceStandableMinimum(m.floor.type,m.area.terrainType)) then
				vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.floor.normal,-1.0,0.1))
				-- SV_PlayerMovement_Store(m,true)
				if (m.playerIndex == 0) then
					gLakituState.roll = gLakituState.roll + clampf(-0.75*preStepYVel,0,1000)
					gLakituState.oldRoll = gLakituState.roll
				end
				
				if (m.action == ACT_DM_AIR_MOVEMENT_METAL) then
					set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT_METAL, 0)
				else
					set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT, 0)
				end
				return
			else
				vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.floor.normal,-0.5,0.75))
				m.pos.y = m.pos.y + 2
				vec3f_add(m.pos,vec3_scale(m.floor.normal,4))
				vec3f_add(m.vel,vec3_scale(m.floor.normal,4))
				return
			end
		end
	end
	if (stepResult == AIR_STEP_HIT_WALL) and m.wall ~= nil then 
		vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.wall.normal,-1.0,0.05))
	end
	
	if (m.pos.y <= m.waterLevel-sv_playersubmergelevel and m.waterLevel > m.floorHeight + sv_playersubmergelevel) and (m.flags & MARIO_METAL_CAP) == 0 then
		if (m.action ~= ACT_DM_AIR_MOVEMENT_METAL) then
			set_mario_action(m, ACT_DM_WATER_MOVEMENT, 0)
		end
	end
	
	-- SV_PlayerMovement_Store(m,true)
end

act_dm_water_movement = function(m)
	-- AngleVectors(m)
	SV_WaterMovement(m)
	
	SV_PlayerMovement_Store(m,true)
	
	if (m.playerIndex == 0) then
		if (vec3f_length(vec3_qscale(m.vel,1,0,1)) < 1) then
			m.faceAngle.y = m.area.camera.yaw + 0x8000
		else
			m.faceAngle.y = atan2s(m.vel.z, m.vel.x)
		end
		set_character_animation(m, CHAR_ANIM_A_POSE)
	else
		local scale = m.forwardVel
		if (scale < 10) then
			set_character_animation(m, CHAR_ANIM_WATER_IDLE)
		else
			set_character_anim_with_accel(m, CHAR_ANIM_FLUTTERKICK, scale*0x800)
		end
	end
	
	m.forwardVel = vec3f_length(vec3_qscale(m.vel,sv_scalerate,0,sv_scalerate))
	
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_air_step(m,0)
	SV_PlayerMovement_Scale(m,true)
	
	if (stepResult == AIR_STEP_HIT_WALL) and m.wall ~= nil then 
		vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.wall.normal,-1.0,0.05))
	end
	
	local isSnowy = ((m.area.terrainType & TERRAIN_MASK) == TERRAIN_SNOW)
	
	if (m.area.camera.pos.y >= m.waterLevel - 10 and not isSnowy) or mario_holding_underwater_shell(m) then
		m.healCounter = 1
	elseif (not mario_holding_underwater_shell(m)) then
		m.health = m.health - ifelse(isSnowy,3,1)
	end
		
	if (m.pos.y > m.waterLevel-sv_playersubmergelevel) then
		set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
		return
	end
end
