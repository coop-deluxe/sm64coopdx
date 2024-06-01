local play_step_sound,set_mario_action,play_character_sound,vec3f_length,perform_ground_step,vec3f_copy,perform_air_step,clampf,vec3f_add,set_mario_particle_flags,play_mario_heavy_landing_sound = play_step_sound,set_mario_action,play_character_sound,vec3f_length,perform_ground_step,vec3f_copy,perform_air_step,clampf,vec3f_add,set_mario_particle_flags,play_mario_heavy_landing_sound



local function play_local_footstep_sounds(m,rate,max) 
	cl_footstepTimer = cl_footstepTimer + rate
	if (cl_footstepTimer >= max) then
		m.marioObj.header.gfx.animInfo.animFrame = 0
		play_step_sound(m, 0, 1)
		cl_footstepTimer = 0
	end
end

-------------------------------
-- Code for our local player --
-------------------------------

--- @param m MarioState
local function local_act_dm_grounded_movement(m)
	local valid_update = local_update(m) 

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
	
	if (m.controller.buttonDown & A_BUTTON) ~= 0 and no_dialog_open() and m.floor ~= nil then
		set_character_animation(m, CHAR_ANIM_IDLE_HEAD_CENTER)
		
		-- m.controller.buttonPressed = m.controller.buttonPressed & ~A_BUTTON
		
		if (m.vel.y < 0) then m.vel.y = m.vel.y * 0.33 end
		
		m.vel.y = m.vel.y + ifelse(metal_underwater,135*sv_jumpheight,140*sv_jumpheight)
		
		if (m.vel.y > 320*sv_jumpheight) then m.vel.y = 320*sv_jumpheight end
		
		play_mario_jump_sound(m)
		
		SV_PlayerMovement_Relative(m)
		
		-- SV_PlayerMovement_Store(m,true)
		
		set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
		act_dm_air_movement(m)
		return
	end
	
	SV_PlayerMovement(m)
	
	set_character_animation(m, CHAR_ANIM_A_POSE)
	if (not cl_bowserthrow) then
		local len = vec3f_length(vec3_qscale(m.vel,1,0,1))
		if (len < 1) then
			m.faceAngle.y = m.area.camera.yaw + 0x8000
			if (m.action == ACT_DM_GROUNDED_MOVEMENT) then m.action = ACT_DM_GROUNDED_IDLE end 
		else
			play_local_footstep_sounds(m,len * 0.08,60) 
			m.faceAngle.y = atan2s(m.vel.z, m.vel.x)
			if (m.action == ACT_DM_GROUNDED_IDLE) then m.action = ACT_DM_GROUNDED_MOVEMENT end 
		end
	end
	
	if (valid_update) then
	m.forwardVel = vec3f_length(vec3_qscale(m.vel,sv_scalerate,0,sv_scalerate))
	else m.forwardVel = 0 end
	
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
		vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.wall.normal,0.0))
	end
	
	if (m.pos.y <= m.waterLevel-sv_playersubmergelevel and m.waterLevel > m.floorHeight + sv_playersubmergelevel) and (m.flags & MARIO_METAL_CAP) == 0 then
		if (m.action == ACT_DM_GROUNDED_MOVEMENT_METAL) then
			set_mario_action(m, ACT_DM_AIR_MOVEMENT_METAL, 0)
		else
			set_mario_action(m, ACT_DM_WATER_MOVEMENT, 0)
		end
	end
end
--- @param m MarioState
local function local_act_dm_air_movement(m)
	local valid_update = local_update(m) 
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
	
	if (m.controller.buttonPressed & Z_TRIG) ~= 0 and (m.controller.buttonDown & A_BUTTON) == 0 and sv_groundpound and m.heldObj == nil and no_dialog_open() then --and m.prevAction ~= ACT_DM_WATER_MOVEMENT then 
		m.vel.y = 0
		m.controller.buttonPressed = m.controller.buttonPressed & ~Z_TRIG
		set_mario_action(m, ifelse(metal_underwater,ACT_DM_GROUND_POUND_METAL,ACT_GROUND_POUND), 1)
		play_sound(SOUND_ACTION_TWIRL,m.marioObj.header.gfx.cameraToObject)
		return 
	end
	
	SV_PlayerMovement(m)
	
	local len_spd = vec3f_length(vec3_qscale(m.vel,1,0,1))
	
	if (len_spd < 1) then
		m.faceAngle.y = m.area.camera.yaw + 0x8000
	else
		m.faceAngle.y = atan2s(m.vel.z, m.vel.x)
	end
	set_character_animation(m, CHAR_ANIM_A_POSE)
	
	if (metal_underwater) then
		SV_UserGravity(m,0.66)
	else
		SV_UserGravity(m,1.0)
	end
	
	if ((m.flags & MARIO_WING_CAP) ~= 0 and (m.controller.buttonPressed & A_BUTTON) ~= 0) and no_dialog_open() then 
		if (m.vel.y < 0) then m.vel.y = 0 end
		m.vel.y = m.vel.y + ifelse(metal_underwater,100,200)
		if (m.vel.y > 320) then m.vel.y = 320 end
		set_mario_particle_flags(m, (PARTICLE_DUST | PARTICLE_MIST_CIRCLE), false)
	end
	
	local preStepYVel = m.vel.y
	
	if (valid_update) then
	m.forwardVel = len_spd*sv_scalerate
	else m.forwardVel = 0 end
	
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_air_step(m,0)
	SV_PlayerMovement_Scale(m,true)
	
	if (stepResult == AIR_STEP_LANDED) then 
		if (m.floor ~= nil) then
			if (m.floor.normal.y > SV_GetSurfaceStandableMinimum(m.floor.type,m.area.terrainType) and ifelse(sv_sticky,m.vel.y < (sv_gravity*sv_tickrate)*2,true)) then
				vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.floor.normal,0.0))
				-- SV_PlayerMovement_Store(m,true)
				
				cl_airstrafelimiter = 0
				m.marioObj.header.gfx.animInfo.animFrame = 0
				play_step_sound(m, 0, 1)
				gLakituState.roll = gLakituState.roll + clampf(-1.75*(preStepYVel+200),0,1000)
				
				if (m.action == ACT_DM_AIR_MOVEMENT_METAL) then
					set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT_METAL, 0)
				else
					set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT, 0)
				end
				return
			else
				vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.floor.normal,0))
				vec3f_add(m.pos,vec3_scale(m.floor.normal,6))
				-- vec3f_add(m.vel,vec3_scale(m.floor.normal,clampf(preStepYVel*0.75,-1,1)))
				return
			end
		end
	end
	if (stepResult == AIR_STEP_HIT_WALL) and m.wall ~= nil then 
		if (m.controller.buttonDown & ifelse(cl_altWalljumpKey,B_BUTTON,A_BUTTON)) ~= 0 and sv_walljump and no_dialog_open() and m.heldObj == nil and len_spd > 100 then 
			cl_airstrafelimiter = 0.66
			vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.wall.normal,0.965))
			set_mario_particle_flags(m, (PARTICLE_VERTICAL_STAR | PARTICLE_DUST), false)
			m.vel.y = 250*sv_jumpheight
			play_sound(SOUND_ACTION_BONK,m.marioObj.header.gfx.cameraToObject)
			play_character_sound(m,CHAR_SOUND_YAH_WAH_HOO)
		else	
			vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.wall.normal,0.05))
		end
	end
	
	if (m.pos.y <= m.waterLevel-sv_playersubmergelevel and m.waterLevel > m.floorHeight + sv_playersubmergelevel) and (m.flags & MARIO_METAL_CAP) == 0 then
		if (m.action ~= ACT_DM_AIR_MOVEMENT_METAL) then
			set_mario_action(m, ACT_DM_WATER_MOVEMENT, 0)
		end
	end
end
--- @param m MarioState
local function local_act_dm_water_movement(m)
	local valid_update = local_update(m) 
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
	
	if (valid_update) then
	m.forwardVel = vec3f_length(vec3_qscale(m.vel,sv_scalerate,0,sv_scalerate))
	else m.forwardVel = 0 end
		
	if (m.pos.y+(m.vel.y*sv_scalerate) < m.floorHeight + 2) then
		m.pos.y = m.floorHeight + 2
		m.vel.y = 0
	end
	
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_air_step(m,0)
	SV_PlayerMovement_Scale(m,true)
	
	if (stepResult == AIR_STEP_HIT_WALL) and m.wall ~= nil then 
		vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.wall.normal,0.05))
	end
	
	local isSnowy = ((m.area.terrainType & TERRAIN_MASK) == TERRAIN_SNOW)
	
	if (m.area.camera.pos.y >= m.waterLevel - 15 and not isSnowy) or mario_holding_underwater_shell(m) then
		m.healCounter = 1
		if (m.controller.buttonDown & A_BUTTON) ~= 0 and m.vel.y > 0 then
			m.vel.y = 180
		end
	elseif (not mario_holding_underwater_shell(m)) then
		m.health = m.health - ifelse(isSnowy,3,1)
	end
		
	if (m.pos.y > m.waterLevel-sv_playersubmergelevel) then
		set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
		return
	end
end
--- @param m MarioState
local function local_act_dm_ground_pound(m)
	local valid_update = local_update(m) 
	
	local metal_underwater = (m.flags & MARIO_METAL_CAP) ~= 0 and m.pos.y <= m.waterLevel-sv_playersubmergelevel
	
	if (metal_underwater and act ~= ACT_DM_GROUND_POUND_METAL) then
		SV_PlayerMovement_Store(m,true)
		set_mario_action(m, ACT_DM_GROUND_POUND_METAL, 0)
		SV_PlayerMovement_Store(m,false)
	elseif (act == ACT_DM_AIR_MOVEMENT_METAL and not metal_underwater) then
		set_mario_action(m, ACT_DM_GROUND_POUND, 0)
	end
	
	if (m.controller.buttonPressed & Z_TRIG) ~= 0 then
		m.vel.x = 0
		m.vel.z = 0
	end
	
	m.faceAngle.y = m.area.camera.yaw + 0x8000
	set_character_animation(m, CHAR_ANIM_A_POSE)
	
	SV_UserGravityEx(m,1.0,0.75)
	
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_air_step(m,0)
	SV_PlayerMovement_Scale(m,true)
	
	if (stepResult == AIR_STEP_LANDED) then 
		if (m.floor ~= nil) then
			play_mario_heavy_landing_sound(m, SOUND_ACTION_TERRAIN_HEAVY_LANDING)
			set_mario_particle_flags(m, (PARTICLE_MIST_CIRCLE | PARTICLE_HORIZONTAL_STAR), false)
				gLakituState.roll = gLakituState.roll + 500
			if (m.controller.buttonDown & A_BUTTON) ~= 0 and m.health > 0xFF then
				SV_HandleSpecialFloors(m,true)
			
				local direction = GetAngleVectors(m).forward
				local yV = m.vel.y * 0.32 * sv_scalerate
				local len = vec3f_length(vec3_qscale(m.vel,1,0,1))
				
				vec3f_copy(m.vel,vec3_scale(direction,len*0.895))
				
				vec3f_add(m.vel,vec3_qscale(m.floor.normal,-0.3,85 * clampf((len+math.abs(yV)) / 320, 0.5, 1.0),-0.3))
				
				m.vel.y = (m.vel.y + (250 * clampf((len+math.abs(yV)) / 320, 0.65, 1.0)))*sv_jumpheight
				-- PHYS_CollideWithNormal(m.vel,m.floor.normal,0.0,1.0)
				
				set_mario_action(m, ifelse(metal_underwater,ACT_DM_AIR_MOVEMENT_METAL,ACT_DM_AIR_MOVEMENT), 0)
				play_character_sound(m,CHAR_SOUND_YAHOO)
			else
				m.forwardVel = 0
				m.vel.x = 0
				m.vel.y = 0
				m.vel.z = 0
				set_mario_action(m, ifelse(metal_underwater,ACT_DM_GROUNDED_MOVEMENT_METAL,ACT_GROUND_POUND_LAND), 0)
			end
			return;
		end
	end
end
--- @param m MarioState
local function local_act_dm_pole_movement(m)
	local_update(m) 
	
	m.vel.x = 0
	m.vel.z = 0
	
	if (m.health <= 0xFF or m.usedObj == nil or (m.controller.buttonPressed & Z_TRIG) ~= 0) then 
		m.vel.y = 0
		m.forwardVel = 3
		m.controller.buttonPressed = m.controller.buttonPressed & ~(Z_TRIG|A_BUTTON)
		return set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
	end
	
	m.faceAngle.y = m.area.camera.yaw + 0x8000
	
	if (m.controller.buttonPressed & A_BUTTON) ~= 0 then 
		m.vel.y = 12
		m.forwardVel = 36
		return set_mario_action(m, ACT_WALL_KICK_AIR, 0)
	end
	
	set_character_animation(m, CHAR_ANIM_A_POSE)
	
	local o = m.usedObj
	local i = ifelse(gFirstPersonCamera.pitch < 0,1.0,-1.0)
	m.pos.y = m.pos.y + (m.usedObj.oPosY-cl_poleY)
	cl_poleY = m.usedObj.oPosY
	
	m.pos.x = o.oPosX + sins(m.faceAngle.y)
	m.pos.z = o.oPosZ + coss(m.faceAngle.y)
	
	m.vel.y = m.controller.rawStickY*0.66*i
	local intendedPos = m.pos.y + (m.vel.y*sv_scalerate)

	if (intendedPos < o.oPosY) then
		m.vel.y = 0
		m.pos.y = o.oPosY
	end

	if (intendedPos > o.oPosY+o.hitboxHeight) then
		m.vel.y = 0
		m.pos.y = o.oPosY+o.hitboxHeight
	end
	
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_air_step(m,0)
	SV_PlayerMovement_Scale(m,true)
end


----------------------------------
-- Prediction for other players --
----------------------------------

--- @param m MarioState
local function prediction_act_dm_grounded_movement(m)
	local crouch = gPlayerSyncTable[m.playerIndex].playerCrouching
	
	if ((m.controller.buttonDown & A_BUTTON) ~= 0 or (m.controller.buttonPressed & A_BUTTON) ~= 0) and m.floor ~= nil then
		play_character_sound(m,CHAR_SOUND_YAH_WAH_HOO)
		-- return
	end
	
	if (not cl_disableAccelPred) then SV_PlayerMovement(m) end
	
	local scale = m.forwardVel
	if (scale < 5) then
		set_character_animation(m, ifelse(crouch,CHAR_ANIM_CROUCHING,CHAR_ANIM_FIRST_PERSON))
	else
		play_step_sound(m, ifelse(crouch,26,9), ifelse(crouch,79,45))
		set_character_anim_with_accel(m, ifelse(crouch,CHAR_ANIM_CRAWLING,CHAR_ANIM_RUNNING), scale*ifelse(crouch,0x4000,0x2600))
	end
	
	m.forwardVel = vec3f_length(vec3_qscale(m.vel,sv_scalerate,0,sv_scalerate))
	
	SV_PlayerMovement_Scale(m,false)
	
	local stepResult = perform_ground_step(m)
	
	SV_PlayerMovement_Scale(m,true)
end
--- @param m MarioState
local function prediction_act_dm_air_movement(m)
	local crouch = gPlayerSyncTable[m.playerIndex].playerCrouching
	
	if (not cl_disableAccelPred) then SV_PlayerMovement(m) end
	
	set_character_animation(m, ifelse(crouch,CHAR_ANIM_FAST_LONGJUMP,ifelse(m.vel.y < 0,CHAR_ANIM_DOUBLE_JUMP_FALL,CHAR_ANIM_DOUBLE_JUMP_RISE)))
	
	if (metal_underwater) then
		SV_UserGravity(m,0.66)
	else
		SV_UserGravity(m,1.0)
	end
	
	if ((m.flags & MARIO_WING_CAP) ~= 0 and (m.controller.buttonDown & A_BUTTON) ~= 0 and m.vel.y < 0) then m.vel.y = 0 end
	
	m.forwardVel = vec3f_length(vec3_qscale(m.vel,sv_scalerate,0,sv_scalerate))
	
	SV_PlayerMovement_Scale(m,false)
	
	local stepResult = perform_air_step(m,0)
	
	SV_PlayerMovement_Scale(m,true)
end
--- @param m MarioState
local function prediction_act_dm_water_movement(m)

	if (not cl_disableAccelPred) then SV_WaterMovement(m) end
	
	local scale = m.forwardVel
	if (scale < 10) then
		set_character_animation(m, CHAR_ANIM_WATER_IDLE)
	else
		set_character_anim_with_accel(m, CHAR_ANIM_FLUTTERKICK, scale*0x800)
	end
	
	if (vec3f_length(m.vel) <= 10) then 
		m.forwardVel = 0
		return
	end
	
	m.forwardVel = vec3f_length(vec3_qscale(m.vel,sv_scalerate,0,sv_scalerate))
	
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_air_step(m,0)
	SV_PlayerMovement_Scale(m,true)
end
--- @param m MarioState
local function prediction_act_dm_ground_pound(m)
	set_character_animation(m, CHAR_ANIM_TRIPLE_JUMP_GROUND_POUND)
	
	SV_UserGravityEx(m,1.0,0.75)
	
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_air_step(m,0)
	SV_PlayerMovement_Scale(m,true)
	
	if (stepResult == AIR_STEP_LANDED) then 
		if (m.floor ~= nil) then
			play_mario_heavy_landing_sound(m, SOUND_ACTION_TERRAIN_HEAVY_LANDING)
			set_mario_particle_flags(m, (PARTICLE_MIST_CIRCLE | PARTICLE_HORIZONTAL_STAR), false)
			if (m.controller.buttonDown & A_BUTTON) ~= 0 then
				play_character_sound(m,CHAR_SOUND_YAHOO)
			end
		end
	end
end
--- @param m MarioState
local function prediction_act_dm_pole_movement(m)	
	set_character_animation(m, CHAR_ANIM_IDLE_ON_POLE)
	
	SV_PlayerMovement_Scale(m,false)
	local stepResult = perform_air_step(m,0)
	SV_PlayerMovement_Scale(m,true)
end


--- @param m MarioState
function act_dm_grounded_movement(m)
	if (m.playerIndex == 0) then return local_act_dm_grounded_movement(m) else return prediction_act_dm_grounded_movement(m) end
end
--- @param m MarioState
function act_dm_air_movement(m)
	if (m.playerIndex == 0) then return local_act_dm_air_movement(m) else return prediction_act_dm_air_movement(m) end
end
--- @param m MarioState
function act_dm_water_movement(m)
	if (m.playerIndex == 0) then return local_act_dm_water_movement(m) else return prediction_act_dm_water_movement(m) end
end
--- @param m MarioState
function act_dm_ground_pound(m)
	if (m.playerIndex == 0) then return local_act_dm_ground_pound(m) else return prediction_act_dm_ground_pound(m) end
end
--- @param m MarioState
function act_dm_pole_movement(m)
	if (m.playerIndex == 0) then return local_act_dm_pole_movement(m) else return prediction_act_dm_pole_movement(m) end
end



