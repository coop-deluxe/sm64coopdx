if SM64COOPDX_VERSION == nil then return end
local collision_find_surface_on_ray,vec3f_dist,vec3f_sub,vec3f_dot,vec3f_project,vec3f_add,vec3f_copy,level_trigger_warp,vec3f_length,clampf,is_game_paused,vec3f_normalize,vec3f_mul = collision_find_surface_on_ray,vec3f_dist,vec3f_sub,vec3f_dot,vec3f_project,vec3f_add,vec3f_copy,level_trigger_warp,vec3f_length,clampf,is_game_paused,vec3f_normalize,vec3f_mul



-- Helper functions

-- Replaced with simplified quake code
function PHYS_CollideWithNormal(vel,norm,bounceFactor) 
	local backoff = vec3f_dot(vel,norm) * (1.0+bounceFactor)
	return {x=vel.x-(norm.x*backoff),y=vel.y-(norm.y*backoff),z=vel.z-(norm.z*backoff)}
end

SV_PlayerMovement_Scale = function(m,prescaled)
	-- if (m.playerIndex ~= 0) then return end
	if (sv_stopmovement) then return end
	
	if (prescaled) then
		m.vel.x = cl_speedbuffer.x
		m.vel.y = cl_speedbuffer.y
		m.vel.z = cl_speedbuffer.z
	else
		cl_speedbuffer.x = m.vel.x
		cl_speedbuffer.y = m.vel.y
		cl_speedbuffer.z = m.vel.z
		m.vel.x = m.vel.x * sv_scalerate
		m.vel.y = m.vel.y * sv_scalerate
		m.vel.z = m.vel.z * sv_scalerate
	end
end

function SV_PlayerMovement_Store(m,store)
	if (m.playerIndex == 0) then 
		if (store) then
			vec3f_copy(cl_upwarpfix_vel,m.vel)
			vec3f_copy(cl_upwarpfix_pos,m.pos)
		else
			vec3f_copy(m.vel,cl_upwarpfix_vel)
			vec3f_copy(m.pos,cl_upwarpfix_pos)
		end
	end
end

function SV_PlayerMovement_Relative(m)
	-- if (m.playerIndex ~= 0) then return end
	local obj = m.marioObj.platform
	if (obj ~= nil) then 
		m.vel.y = m.vel.y + (obj.oVelY*4)
	end
end

function SV_HandleSpecialFloors(m,bypassFloorCheck)
	if (m.floor ~= nil) then
		local type = m.floor.type
		if (type == SURFACE_VERTICAL_WIND) then 
			m.vel.y = m.vel.y + 18
			if (m.vel.y < -24) then 
				m.vel.y = -24
			end
			if (m.vel.y > 200) then 
				m.vel.y = 200
			end
			return true
		end
		if (type == SURFACE_HORIZONTAL_WIND and DM_ACTION_QPHYS[m.action] == 1) then 
			local pushAngle = m.floor.force << 8;
			
			local amt = ifelse((m.action & ACT_FLAG_AIR) == 0,48,8)
			
			m.vel.x = m.vel.x + (amt * sins(pushAngle))
			m.vel.z = m.vel.z + (amt * coss(pushAngle))
			return true
		end
		if (type == SURFACE_DEATH_PLANE or type == SURFACE_VERTICAL_WIND) and (m.pos.y < m.floorHeight + 2048) then
			if (level_trigger_warp(m, WARP_OP_WARP_FLOOR) == 20 and (m.flags & MARIO_UNKNOWN_18) ~= 0) then
				return true
			end
		end
		if (type == SURFACE_BURNING) and (m.invincTimer == 0) and ((m.flags & MARIO_METAL_CAP == 0) and (((m.action & ACT_FLAG_AIR) == 0 and (m.input & INPUT_OFF_FLOOR) == 0) or bypassFloorCheck)) then
			m.hurtCounter = 8
			m.invincTimer = 15
			cl_red = 128
		end
		if (type == SURFACE_INSTANT_QUICKSAND or type == SURFACE_INSTANT_MOVING_QUICKSAND) and (m.invincTimer == 0) and ((m.flags & MARIO_METAL_CAP == 0) and (((m.action & ACT_FLAG_AIR) == 0 and (m.input & INPUT_OFF_FLOOR) == 0) or bypassFloorCheck)) then
			m.hurtCounter = 4
			m.invincTimer = 10
			cl_red = 128
		end
	end
	return false
end

-- Player angle system

frameCalculatedAngles = false
local frameAngles = {}

function GetAngleVectors(m)
	local s = gPlayerSyncTable[m.playerIndex]
	
	local yaw = gFirstPersonCamera.yaw+0x8000
	local pitch = -gFirstPersonCamera.pitch
	
	if (m.playerIndex == 0) then
		s.playerYaw = yaw
		s.playerPitch = pitch
		if (frameCalculatedAngles) then return frameAngles end
		frameCalculatedAngles = true
	else
		yaw = s.playerYaw
		pitch = s.playerPitch
	end
	
	local sinYaw = sins(yaw)
	local cosYaw = coss(yaw)
	
	local yawRight = yaw-0x4000
	local cosYawRight = coss(yawRight)
	local sinYawRight = sins(yawRight)
	
	local cosPitch = coss(pitch)
	local sinPitch = sins(pitch)
	
	local _rawForward = {x=sinYaw*cosPitch,y=sinPitch,z=cosYaw*cosPitch} -- variable used this name, prevent old code from breaking; todo, rewrite?
	local _forward = {x=sinYaw,y=0,z=cosYaw}
	local _right = {x=sinYawRight,y=0,z=cosYawRight}
	
	local returnValue =  {
		rawForward=_rawForward,
		forward=_forward,
		right=_right
	}
	
	if (m.playerIndex == 0) then
		frameAngles = returnValue
	end
	
	return returnValue
end

-- Important Functions

-- Acceleration / Friction
function SV_UserFriction(m)
	-- if (m.playerIndex ~= 0) then return end
	local speed = vec3f_length(m.vel)
	if (speed <= 0.00001) then return end
	local friction = ((sv_friction*phys_friction_scale)+ifelse(gPlayerSyncTable[m.playerIndex].playerCrouching,sv_crouchfriction_scale,0))*SV_GetSurfaceStandableFrictionMultiplier(m.floor.type,m.area.terrainType)
	local control = nil
	
	if (speed <= sv_stopspeed) then
		control = sv_stopspeed
	else 
		control = speed
	end
	
	local newspeed = speed - sv_tickrate*control*friction
	
	if (newspeed < 0) then newspeed = 0 end
	if (newspeed > 0) then
		newspeed = newspeed / speed
	end
	m.vel.x = m.vel.x * newspeed
	m.vel.y = m.vel.y * newspeed
	m.vel.z = m.vel.z * newspeed
end

-- Acceleration / Friction
function SV_UserGravity(m,scale)
	m.vel.y = m.vel.y - (sv_gravity * sv_tickrate * scale * sv_gravity_scale)
	if (m.vel.y < -sv_gravity) then m.vel.y = -sv_gravity end
end
function SV_UserGravityEx(m,scale,minovr)
	m.vel.y = m.vel.y - (sv_gravity * sv_tickrate * scale * sv_gravity_scale)
	if (m.vel.y < -sv_gravity*minovr) then m.vel.y = -sv_gravity*minovr end
end

function SV_Accelerate(m,wishDir,wishspeed)
	-- if (m.playerIndex ~= 0) then return end
	local addspeed,accelspeed,currentspeed = 0,0,0
	currentspeed = vec3f_dot(m.vel,wishDir)
	addspeed = wishspeed - currentspeed
	if (addspeed <= 0) then return end
	accelspeed = sv_accelerate * wishspeed * sv_tickrate
	if (accelspeed > addspeed) then accelspeed = addspeed end
	m.vel.x = m.vel.x + (accelspeed * wishDir.x)
	m.vel.y = m.vel.y + (accelspeed * wishDir.y)
	m.vel.z = m.vel.z + (accelspeed * wishDir.z)
end

function SV_AirAccelerate(m,wishDir,wishspeed)
	-- Limiter code for wallkicks
	local airLimiter_Frac = (1.0-clampf(cl_airstrafelimiter,0.0,1.0))
	local addspeed,wishspd,accelspeed,currentspeed = 0,0,0,0
	
	wishspd = wishspeed*airLimiter_Frac
	
	-- Checks for a lack of acceleration
	if (wishspeed == 0) then return end
	if (wishspd > sv_playerclamp_air) then wishspd = sv_playerclamp_air end -- This is 30 in source, quake and other games
	
	currentspeed = vec3f_dot(m.vel,wishDir)
	addspeed = wishspd - currentspeed
	
	if (addspeed <= 0) then return end
	accelspeed = (sv_airaccelerate_value * phys_airaccel_scale) * (wishspd * airLimiter_Frac) * sv_tickrate
	
	if (accelspeed > addspeed) then accelspeed = addspeed end
	m.vel.x = m.vel.x + ((accelspeed * wishDir.x)*airLimiter_Frac)
	m.vel.y = m.vel.y + ((accelspeed * wishDir.y)*airLimiter_Frac)
	m.vel.z = m.vel.z + ((accelspeed * wishDir.z)*airLimiter_Frac)
end

-- Main movement functions

function SV_PlayerMovement(m)
	-- if (m.playerIndex ~= 0) then return end
	if (sv_stopmovement) then return end
	
	local isPrediction = m.playerIndex ~= 0
	
	-- if (isPrediction) then return end
	
	local crouch = gPlayerSyncTable[m.playerIndex].playerCrouching
	local playerSpeed = ifelse(crouch,sv_playerspeed_crouch,sv_playerspeed)
	local maxSpeed = ifelse(crouch,sv_maxspeed_crouch,sv_maxspeed)
	
	local vecInput = {x=0,y=0,z=0}
	if ((not is_game_paused()) and m.health > 0xFF and not cl_bowserthrow and not cl_bowserthrow and not (not no_dialog_open() and not isPrediction)) then
		vecInput.x = m.controller.rawStickX
		vecInput.y = m.controller.rawStickY
	end
	
	if (not isPrediction) then
	vec3f_normalize(vecInput)
	vec3f_mul(vecInput,m.controller.stickMag)
	end
	
	local fmove = (vecInput.y/32)*playerSpeed -- what are the maximums of these again?
	local smove = (vecInput.x/32)*playerSpeed
	-- local fmove = (vecInput.y/64)*playerSpeed -- what are the maximums of these again?
	-- local smove = (vecInput.x/64)*playerSpeed
	
	local wishVel = {x=0,y=0,z=0}
	local wishDir = {x=0,y=0,z=0}
	
	local AngledVectors = GetAngleVectors(m)
	
	wishVel.x = (AngledVectors.forward.x * fmove) + (AngledVectors.right.x * smove)
	wishVel.y = (AngledVectors.forward.y * fmove) + (AngledVectors.right.y * smove)
	wishVel.z = (AngledVectors.forward.z * fmove) + (AngledVectors.right.z * smove)
	
	
	if (not isPrediction) then
	if (m.action == ACT_DM_GROUNDED_MOVEMENT or m.action == ACT_DM_GROUNDED_MOVEMENT_METAL or m.action == ACT_DM_GROUNDED_IDLE) then
		wishVel.y = 0
		if (m.floor ~= nil) then
			local tempNormal = vec3_invert(m.floor.normal)
			tempNormal.y = 0 ; vec3f_normalize(tempNormal)
			local amount = (cl_grounddefacto * clampf(vec3f_dot(wishVel,tempNormal),0,1)) * m.floor.normal.y
			vec3f_sub(wishVel,vec3_scale(vec3f_project(wishVel, m.floor.normal), amount))
			vec3f_add(wishVel,vec3_scale(m.floor.normal, amount*0.125))
		end
	end
	end
	
	local wishspeed = vec3f_length(wishVel)
	vec3f_copy(wishDir, wishVel)
	vec3f_normalize(wishDir)
	if wishspeed > maxSpeed then 
		wishVel.x = wishVel.x * (maxSpeed / wishspeed)
		wishVel.y = wishVel.y * (maxSpeed / wishspeed)
		wishVel.z = wishVel.z * (maxSpeed / wishspeed)
		wishspeed = maxSpeed
	end
	if (m.action == ACT_DM_GROUNDED_MOVEMENT or m.action == ACT_DM_GROUNDED_MOVEMENT_METAL or m.action == ACT_DM_GROUNDED_IDLE) then
		SV_UserFriction(m,wishDir,wishspeed)
		SV_Accelerate(m,wishDir,wishspeed)
	elseif (m.action == ACT_DM_AIR_MOVEMENT or m.action == ACT_DM_AIR_MOVEMENT_METAL) then
		SV_AirAccelerate(m,wishDir,wishspeed)
	end
	
	local finalVelLen = vec3f_length(m.vel)
	if finalVelLen > sv_maxvelocity then 
		m.vel.x = m.vel.x * (sv_maxvelocity / finalVelLen)
		m.vel.y = m.vel.y * (sv_maxvelocity / finalVelLen)
		m.vel.z = m.vel.z * (sv_maxvelocity / finalVelLen)
	end
end

function SV_WaterMovement(m)
	-- if (m.playerIndex ~= 0) then return end
	if (sv_stopmovement) then return end
	
	local isPrediction = m.playerIndex ~= 0
	
	local shellSpeed = mario_holding_underwater_shell(m)
	
	local playerSpeed = ifelse(shellSpeed,sv_playerspeed_water_shell,sv_playerspeed_water)
	
	local vecInput = {x=0,y=0,z=0}
	if ((not is_game_paused()) and m.health > 0xFF) then
		vecInput.x = m.controller.rawStickX
		vecInput.y = m.controller.rawStickY
	end
	
	if (not isPrediction) then
	vec3f_normalize(vecInput)
	vec3f_mul(vecInput,m.controller.stickMag)
	end
	
	local fmove = (vecInput.y/32)*playerSpeed 
	local smove = (vecInput.x/32)*playerSpeed
	local umove = 0
	if (m.controller.buttonDown & A_BUTTON ~= 0) then umove = umove+1 end
	if (m.controller.buttonDown & Z_TRIG ~= 0) then umove = umove-1 end
	
	local wishVel = {x=0,y=0,z=0}
	
	local AngledVectors = GetAngleVectors(m)
	
	wishVel.x = (AngledVectors.rawForward.x * fmove) + (AngledVectors.right.x * smove)
	wishVel.y = (AngledVectors.rawForward.y * fmove) + (AngledVectors.right.y * smove)
	wishVel.z = (AngledVectors.rawForward.z * fmove) + (AngledVectors.right.z * smove)
	
	if (fmove < 0.1 and smove < 0.1 and umove == 0) then
		wishVel.y = wishVel.y - 30
	else
		wishVel.y = wishVel.y + sv_upspeed_water * umove
	end
	
	local wishspeed = vec3f_length(wishVel)
	
	local maxspeed = ifelse(shellSpeed,sv_playerspeed_water_shell,sv_maxspeed_water)
	
	if (wishspeed > maxspeed) then
		vec3f_mul(wishVel,maxspeed/wishspeed)
		wishspeed = maxspeed
	end
	wishspeed = wishspeed * 0.85
	--
	-- water friction
	--
	local speed = vec3f_length(m.vel)
	local newspeed = 0
	
	if (speed > 0.00001) then
		newspeed = speed - sv_tickrate * speed * sv_waterfriction
		if (newspeed < 0) then newspeed = 0 end 
		vec3f_mul(m.vel,newspeed/speed)
	end
	
	--
	-- water acceleration
	--
	if (wishspeed < 0.00001) then return end
	
	local addspeed = wishspeed - newspeed
	
	if (addspeed <= 0) then return end
	
	vec3f_normalize(wishVel)
	local accelspeed = (sv_accelerate * wishspeed) * sv_tickrate
	if (accelspeed > addspeed) then accelspeed = addspeed end
	
	m.vel.x = m.vel.x + (accelspeed * wishVel.x)
	m.vel.y = m.vel.y + (accelspeed * wishVel.y)
	m.vel.z = m.vel.z + (accelspeed * wishVel.z) 
	
end
