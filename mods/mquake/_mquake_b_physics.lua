-- _mquake_a_constants
-- _mquake_b_actions_predefine
-- _mquake_c_actions
-- _mquake_d_physics
-- _mquake_e_hooks
-- localize functions to improve performance - _mquake_b_physics.lua
local collision_find_surface_on_ray,vec3f_dist,vec3f_sub,vec3f_dot,vec3f_project,vec3f_add,vec3f_copy,level_trigger_warp,vec3f_normalize,vec3f_length,rotate_in_xz,is_game_paused,vec3f_mul,clampf = collision_find_surface_on_ray,vec3f_dist,vec3f_sub,vec3f_dot,vec3f_project,vec3f_add,vec3f_copy,level_trigger_warp,vec3f_normalize,vec3f_length,rotate_in_xz,is_game_paused,vec3f_mul,clampf


-- Helper functions

local function SV_Trace(start,stop) -- only made for friction
	local ray = collision_find_surface_on_ray(start.x,start.y,start.z,stop.x,stop.y,stop.z)
	return (vec3f_dist(start,stop) - vec3f_dist(ray.hitPos,stop)) <= 0.05
end
-- initial version was bugged but x showed me how to properly use vec3f_project
-- otherwise entirely written by yours truly :3
function PHYS_CollideWithNormal(vel,norm,slamFactor,bounceFactor) 
	-- if (m.playerIndex ~= 0) then return end
	-- First, define a temporary vel var
	local _vel = {x=vel.x,y=vel.y,z=vel.z}
	
	if (bounceFactor > 0) then
		-- Bounce off a bit if ye want to! 
		vec3f_sub(_vel,vec3_scale(vec3_scale(norm,2.0 * vec3f_dot(norm,_vel)),bounceFactor))
	end
	
	if (slamFactor < 0) then
		-- SLAM the vel against the normal with the factor (usually -1)
		local v = vec3f_project(_vel, norm)
		vec3f_add(_vel,vec3_scale(vec3f_project(_vel, norm), slamFactor))
	end
	
	-- Return the new velocity
	return _vel
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
	-- if (m.playerIndex ~= 0) then return end
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
	-- if (m.playerIndex ~= 0) then return end
	if (m.floor ~= nil) then
		local type = m.floor.type
		if (type == SURFACE_VERTICAL_WIND and m.action ~= ACT_GROUND_POUND) then 
			m.vel.y = m.vel.y + 18
			if (m.vel.y < -24) then 
				m.vel.y = -24
			end
			if (m.vel.y > 200) then 
				m.vel.y = 200
			end
			return true
		end
		if (type == SURFACE_HORIZONTAL_WIND) then 
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
			m.hurtCounter = 1
			m.invincTimer = 15
			cl_red = 128
		end
	end
	return false
end

-- Player angle system

function GetAngleVectors(m)
	local s = gPlayerSyncTable[m.playerIndex]
	
	local localForwardDirection = vec3f_normalize({x=(m.area.camera.focus.x - m.area.camera.pos.x),y=(m.area.camera.focus.y - m.area.camera.pos.y), z=(m.area.camera.focus.z - m.area.camera.pos.z)})
	
	if (m.playerIndex == 0) then
		s.playerStopFix = sv_stopfix
		s.playerFacingX = localForwardDirection.x
		s.playerFacingY = localForwardDirection.y
		s.playerFacingZ = localForwardDirection.z
		-- s.playerFacingYaw = (-(m.marioObj.header.gfx.angle.y - m.area.camera.yaw))+0x8000
		-- s.playerFacingPitch = -gLakituState.oldPitch
	end
	
	local forwardDirection = ifelse(m.playerIndex == 0,{x=localForwardDirection.x,y=localForwardDirection.y,z=localForwardDirection.z},{x=s.playerFacingX,y=s.playerFacingY,z=s.playerFacingZ})
	local rightDirection = {x=0,y=0,z=0}
	
	if (not s.playerStopFix) then
		local preRemovalLen = vec3f_length(forwardDirection)
		forwardDirection.y = 0
		
		local postRemovalLen = vec3f_length(forwardDirection)
		forwardDirection.x = forwardDirection.x * (preRemovalLen/postRemovalLen)
		forwardDirection.z = forwardDirection.z * (preRemovalLen/postRemovalLen)
	end
	
	rotate_in_xz(rightDirection,forwardDirection,-0x4000)
	
	return {
		rawForward=localForwardDirection,
		forward=forwardDirection,
		right=rightDirection
	}
end

-- Important Functions

-- Acceleration / Friction
local function SV_UserFriction(m)
	-- if (m.playerIndex ~= 0) then return end
	local speed = vec3f_length(m.vel)
	if (speed <= 0.00001) then return end
	local start = {x=(m.pos.x + (m.vel.x / speed * 16)),y=(m.pos.y + (m.vel.y / speed * 16)),z=(m.pos.z + (m.vel.z / speed * 16))}
	local stop = {x=start.x,y=start.y,z=start.z-24}
	local friction = 0
	if (SV_Trace(start,stop)) then
		friction = (sv_friction+ifelse(gPlayerSyncTable[m.playerIndex].playerCrouching,sv_crouchfriction_scale,0))*sv_edgefriction
	else
		friction = sv_friction+ifelse(gPlayerSyncTable[m.playerIndex].playerCrouching,sv_crouchfriction_scale,0)
	end
	friction = friction*SV_GetSurfaceStandableFrictionMultiplier(m.floor.type,m.area.terrainType)
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

local function SV_Accelerate(m,wishVel,wishDir,wishspeed)
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


local function SV_AirAccelerate(m,wishVel,wishDir,wishspeed)
	-- if (m.playerIndex ~= 0) then return end
	local addspeed,wishspd,accelspeed,currentspeed = 0,0,0,0
	wishspd = wishspeed
	if (wishspd > sv_playerclamp_air) then wishspd = sv_playerclamp_air end
	currentspeed = vec3f_dot(m.vel,wishDir)
	addspeed = wishspd - currentspeed
	if (addspeed <= 0) then return end
	accelspeed = (sv_airaccelerate_value * wishspd) * sv_tickrate
	if (accelspeed > addspeed) then accelspeed = addspeed end
	m.vel.x = m.vel.x + (accelspeed * wishDir.x)
	m.vel.y = m.vel.y + (accelspeed * wishDir.y)
	m.vel.z = m.vel.z + (accelspeed * wishDir.z)
end

-- Main movement functions

function SV_PlayerMovement(m)
	-- if (m.playerIndex ~= 0) then return end
	if (sv_stopmovement) then return end
	
	local isPrediction = m.playerIndex ~= 0
	
	-- if (isPrediction) then return end
	
	
	local playerSpeed = ifelse(gPlayerSyncTable[m.playerIndex].playerCrouching,sv_playerspeed_crouch,sv_playerspeed)
	
	local vecInput = {x=0,y=0,z=0}
	if ((not is_game_paused()) and m.health > 0xFF and not cl_bowserthrow and not cl_bowserthrow) then
		vecInput.x = m.controller.rawStickX
		vecInput.y = m.controller.rawStickY
	end
	
	-- if (not isPrediction) then
	vec3f_normalize(vecInput)
	vec3f_mul(vecInput,m.controller.stickMag)
	-- end
	
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
			vec3f_add(wishVel,vec3_scale(m.floor.normal, amount*0.1))
		end
	end
	end
	
	local wishspeed = vec3f_length(wishVel)
	vec3f_copy(wishDir, wishVel)
	vec3f_normalize(wishDir)
	if wishspeed > sv_maxspeed then 
		wishVel.x = wishVel.x * (sv_maxspeed / wishspeed)
		wishVel.y = wishVel.y * (sv_maxspeed / wishspeed)
		wishVel.z = wishVel.z * (sv_maxspeed / wishspeed)
		wishspeed = sv_maxspeed
	end
	if (m.action == ACT_DM_GROUNDED_MOVEMENT or m.action == ACT_DM_GROUNDED_MOVEMENT_METAL or m.action == ACT_DM_GROUNDED_IDLE) then
		SV_UserFriction(m,wishVel,wishDir,wishspeed)
		SV_Accelerate(m,wishVel,wishDir,wishspeed)
	elseif (m.action == ACT_DM_AIR_MOVEMENT or m.action == ACT_DM_AIR_MOVEMENT_METAL) then
		SV_AirAccelerate(m,wishVel,wishDir,wishspeed)
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
	if (m.controller.buttonDown & A_BUTTON ~= 0) then umove = 1 end
	
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
	
	local maxspeed = ifelse(shellSpeed,sv_playerspeed_water_shell,sv_maxspeed)
	
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
