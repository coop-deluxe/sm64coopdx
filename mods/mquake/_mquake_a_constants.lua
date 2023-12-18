-- _mquake_a_constants
-- _mquake_b_actions_predefine
-- _mquake_c_actions
-- _mquake_d_physics
-- _mquake_e_hooks
-- localize functions to improve performance - _mquake_a_constants.lua
local clampf,allocate_mario_action,vec3f_copy,vec3f_add,set_mario_action,math_floor,obj_get_first,vec3f_dist,obj_get_next = clampf,allocate_mario_action,vec3f_copy,vec3f_add,set_mario_action,math.floor,obj_get_first,vec3f_dist,obj_get_next


sv_stopmovement = false
sv_playerheight = 160
sv_crouchoffset = 60
sv_playersubmergelevel = 100
sv_camerayoffset = 8
sv_waterfriction = 2.5
sv_friction = 4.75
sv_crouchfriction_scale = 2.0
sv_stopspeed = 2
sv_maxspeed = 200
sv_maxvelocity = 1200
sv_playerspeed = 120
sv_playerspeed_water = 120
sv_playerspeed_water_shell = 300
sv_upspeed_water = 160
sv_playerspeed_crouch = 60
sv_playerclamp_air = 25
sv_accelerate = 10
sv_airaccelerate_value = 80
sv_edgefriction = 2
sv_tickrate = 1/30
sv_scalerate = 0.25
cl_grounddefacto = 1.0 / 0.60
cl_localangles = {forward={x=0,y=0,z=0},right={x=0,y=0,z=0},rawForward={x=0,y=0,z=0}}
cl_speedbuffer = {x=0,y=0,z=0} --,w=0}
cl_upwarpfix_vel = {x=0,y=0,z=0}
cl_upwarpfix_pos = {x=0,y=0,z=0}
cl_bowserthrow = false
cl_bowserthrow_previousYaw = 0
cl_interacttimer = 0
cl_red = 0
cl_footstepTimer = 0
-- cl_watershelltimer = 0

-- Physics helpers
local SurfaceStandableMinimum = {
	[SURFACE_CLASS_NOT_SLIPPERY] = 0.01,
	[SURFACE_HARD_NOT_SLIPPERY] = 0.01,
	[SURFACE_CLASS_SLIPPERY] = 0.7,
	[SURFACE_HARD_SLIPPERY] = 0.7,
	[SURFACE_NO_CAM_COL_SLIPPERY] = 0.7,
	[SURFACE_NOISE_SLIPPERY] = 0.7,
	[SURFACE_SLIPPERY] = 0.7,
	[SURFACE_CLASS_VERY_SLIPPERY] = 0.85,
	[SURFACE_HARD_VERY_SLIPPERY] = 0.85,
	[SURFACE_NO_CAM_COL_VERY_SLIPPERY] = 0.85,
	[SURFACE_VERY_SLIPPERY] = 0.85,
	[SURFACE_NOISE_VERY_SLIPPERY] = 0.85,
	[SURFACE_NOISE_VERY_SLIPPERY_73] = 0.85,
	[SURFACE_NOISE_VERY_SLIPPERY_74] = 0.85
} 						     


local SurfaceFriction = {
	[SURFACE_CLASS_NOT_SLIPPERY] = 1.0,
	[SURFACE_HARD_NOT_SLIPPERY] = 1.0,
	[SURFACE_CLASS_SLIPPERY] = 0.8,
	[SURFACE_HARD_SLIPPERY] = 0.8,
	[SURFACE_NO_CAM_COL_SLIPPERY] = 0.8,
	[SURFACE_NOISE_SLIPPERY] = 0.8,
	[SURFACE_SLIPPERY] = 0.8,
	[SURFACE_CLASS_VERY_SLIPPERY] = 0.4,
	[SURFACE_HARD_VERY_SLIPPERY] = 0.4,
	[SURFACE_NO_CAM_COL_VERY_SLIPPERY] = 0.4,
	[SURFACE_VERY_SLIPPERY] = 0.4,
	[SURFACE_NOISE_VERY_SLIPPERY] = 0.4,
	[SURFACE_NOISE_VERY_SLIPPERY_73] = 0.4,
	[SURFACE_NOISE_VERY_SLIPPERY_74] = 0.4
}

local AreaTypeFriction = {
	[TERRAIN_SLIDE] = 0.225, -- incase i wanna give other types different friction values
	[TERRAIN_SNOW] = 0.90 -- incase i wanna give other types different friction values
}
local AreaTypeStandable = {
	[TERRAIN_SLIDE] = 2.75, 
	[TERRAIN_SNOW] = 1.10
}

local function SV_GetAreaFriction(type) 
	if AreaTypeFriction[type] ~= nil then return AreaTypeFriction[type] end
	return 1.0
end
local function SV_GetAreaStandable(type) 
	if AreaTypeStandable[type] ~= nil then return AreaTypeStandable[type] end
	return 1.0
end

function SV_GetSurfaceStandableMinimum(type,areaType) 
	areaFactor = SV_GetAreaStandable(areaType)
	standableMinimum = 0.675
	if SurfaceStandableMinimum[type] ~= nil then standableMinimum = SurfaceStandableMinimum[type] end
	return clampf(standableMinimum * areaFactor,0.01,0.999)
end

function SV_GetSurfaceStandableFrictionMultiplier(type,areaType)
	areaFactor = SV_GetAreaFriction(areaType)
	standableMinimum = 1.0
	if SurfaceFriction[type] ~= nil then standableMinimum = SurfaceFriction[type] end
	return clampf(standableMinimum * areaFactor,0.01,1.0)
end

sv_gunmod_loaded = (_G.gunModApi ~= nil)

-- Actions
ACT_DM_GROUNDED_MOVEMENT = allocate_mario_action(ACT_FLAG_MOVING | ACT_FLAG_CUSTOM_ACTION)
ACT_DM_GROUNDED_IDLE = allocate_mario_action(ACT_FLAG_MOVING | ACT_FLAG_IDLE | ACT_FLAG_CUSTOM_ACTION) -- fix for reading signs while moving on accident
ACT_DM_AIR_MOVEMENT = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_MOVING | ACT_FLAG_AIR | ACT_FLAG_CUSTOM_ACTION)
ACT_DM_GROUNDED_MOVEMENT_METAL = allocate_mario_action(ACT_GROUP_SUBMERGED | ACT_FLAG_MOVING | ACT_FLAG_WATER_OR_TEXT | ACT_FLAG_CUSTOM_ACTION)
ACT_DM_AIR_MOVEMENT_METAL = allocate_mario_action(ACT_GROUP_SUBMERGED | ACT_FLAG_MOVING | ACT_FLAG_WATER_OR_TEXT | ACT_FLAG_CUSTOM_ACTION)
ACT_DM_WATER_MOVEMENT = allocate_mario_action(ACT_GROUP_SUBMERGED | ACT_FLAG_MOVING | ACT_FLAG_WATER_OR_TEXT | ACT_FLAG_CUSTOM_ACTION)
ACT_DM_POLE_MOVEMENT = allocate_mario_action(ACT_GROUP_CUTSCENE | ACT_FLAG_MOVING | ACT_FLAG_CUSTOM_ACTION)

-- Predefine these for later calls
main_act_dm_grounded_movement = function() end
main_act_dm_air_movement = function() end
act_dm_water_movement_movement = function() end

-- Action helpers
DM_ACTIONS = {
	[ACT_DM_GROUNDED_MOVEMENT] = 1,
	[ACT_DM_GROUNDED_IDLE] = 1,
	[ACT_DM_AIR_MOVEMENT] = 1,
	[ACT_DM_GROUNDED_MOVEMENT_METAL] = 1,
	[ACT_DM_AIR_MOVEMENT_METAL] = 1,
	[ACT_DM_WATER_MOVEMENT] = 1,
	[ACT_DM_POLE_MOVEMENT] = 1,
	[ACT_ELECTROCUTION] = 1,
	[ACT_QUICKSAND_DEATH] = 1,
	[ACT_SHOCKED] = 1,
	[ACT_GRABBED] = 1,
	[ACT_UNINITIALIZED] = 1,
	[ACT_PULLING_DOOR] = 1,
	[ACT_PUSHING_DOOR] = 1,
	[ACT_EMERGE_FROM_PIPE] = 1,
	[ACT_ENTERING_STAR_DOOR] = 1,
	[ACT_DEATH_EXIT] = 1,
	[ACT_DEATH_EXIT_LAND] = 1,
	[ACT_SQUISHED] = 1,
	[ACT_DISAPPEARED] = 1,
	[ACT_EXIT_AIRBORNE] = 1,
	[ACT_EXIT_LAND_SAVE_DIALOG] = 1,
	[ACT_HARD_BACKWARD_GROUND_KB] = 1,
	[ACT_FALLING_DEATH_EXIT] = 1,
	[ACT_FALLING_EXIT_AIRBORNE] = 1,
	[ACT_DEATH_ON_BACK] = 1,
	[ACT_DEATH_ON_STOMACH] = 1,
	[ACT_DROWNING] = 1,
	-- [ACT_WATER_IDLE] = 1,
	-- [ACT_WATER_SHOCKED] = 1,
	[ACT_SPECIAL_DEATH_EXIT] = 1,
	[ACT_SPECIAL_EXIT_AIRBORNE] = 1,
	[ACT_IN_CANNON] = 1,
	[ACT_SHOT_FROM_CANNON] = 1,
	[ACT_WAITING_FOR_DIALOG] = 1,
	[ACT_READING_AUTOMATIC_DIALOG] = 1,
	[ACT_READING_NPC_DIALOG] = 1,
	[ACT_READING_SIGN] = 1,
	[ACT_GRAB_POLE_FAST] = 1,
	[ACT_GRAB_POLE_SLOW] = 1,
	[ACT_CLIMBING_POLE] = 1,
	[ACT_READING_SIGN] = 1,
	[ACT_HOLDING_POLE] = 1,
	[ACT_TOP_OF_POLE] = 1,
	[ACT_TOP_OF_POLE_JUMP] = 1,
	[ACT_WALL_KICK_AIR] = 1,
	[ACT_TOP_OF_POLE_TRANSITION] = 1,
	[ACT_GROUND_POUND] = 1, -- if marios y vel is low enough and you press crouch in the air while not holding jump, ground pound
	[ACT_GROUND_POUND_LAND] = 1, -- manually added, if this is detected we can do a ground pound jump :3
	[ACT_STANDING_DEATH] = 1,
	[ACT_INTRO_CUTSCENE] = 1,
	[ACT_JUMBO_STAR_CUTSCENE] = 1,
	[ACT_SPAWN_NO_SPIN_AIRBORNE] = 1,
	[ACT_HOLDING_BOWSER] = 1,
	[ACT_SPAWN_SPIN_AIRBORNE] = 1,
	[ACT_CRAZY_BOX_BOUNCE] = 1,
	[ACT_BBH_ENTER_JUMP] = 1,
	[ACT_BBH_ENTER_SPIN] = 1,
	[ACT_THROWN_FORWARD] = 1,
	[ACT_THROWN_BACKWARD] = 1,
	[ACT_GETTING_BLOWN] = 1,
	[ACT_TELEPORT_FADE_IN] = 1,
	[ACT_TELEPORT_FADE_OUT] = 1
}

DM_ACTIONS_CROUCHAIR = {
	[ACT_DM_AIR_MOVEMENT] = 1,
	[ACT_DM_AIR_MOVEMENT_METAL] = 1,
	[ACT_GROUND_POUND] = 1
}

DM_ACTIONS_ALLOWGRAB = {
	[ACT_DM_GROUNDED_MOVEMENT] = 1,
	[ACT_DM_GROUNDED_IDLE] = 1,
	[ACT_DM_AIR_MOVEMENT] = 1,
	[ACT_DM_GROUNDED_MOVEMENT_METAL] = 1,
	[ACT_DM_AIR_MOVEMENT_METAL] = 1,
	[ACT_DM_WATER_MOVEMENT] = 1,
	[ACT_DM_POLE_MOVEMENT] = 1,
	[ACT_GROUND_POUND_LAND] = 1
}

DM_ACTION_QPHYS = {
	[ACT_DM_GROUNDED_MOVEMENT] = 1,
	[ACT_DM_GROUNDED_IDLE] = 1,
	[ACT_DM_AIR_MOVEMENT] = 1,
	[ACT_DM_GROUNDED_MOVEMENT_METAL] = 1,
	[ACT_DM_AIR_MOVEMENT_METAL] = 1,
	[ACT_DM_WATER_MOVEMENT] = 1,
	[ACT_DM_POLE_MOVEMENT] = 1
}

DM_ACTION_FORCEANGLE = {
	[ACT_GRAB_POLE_FAST] = 1,
	[ACT_GRAB_POLE_SLOW] = 1,
	[ACT_CLIMBING_POLE] = 1,
	[ACT_HOLDING_POLE] = 1,
	[ACT_TOP_OF_POLE] = 1
}

DM_ACTION_TRANSFERS = {
	[ACT_TOP_OF_POLE_JUMP] = 1,
	[ACT_WALL_KICK_AIR] = 1
}

DM_ACTION_PREFUNCS = {
	[ACT_BURNING_JUMP] = function(m) 
		m.hurtCounter = 4
		m.invincTimer = 10
		if (m == gMarioStates[0]) then
			gLakituState.roll = 1000
			gLakituState.oldRoll = gLakituState.roll
			cl_red = 128
		end
		return 1
	end
}

DM_ACTION_PREFUNCS = {
	[ACT_SHOCKED] = function(m) 
		m.vel.y = m.vel.y * 0.25
	end
}

DM_ACTION_FUNCTIONS = {
	[ACT_GROUND_POUND_LAND] = function(m) 
		if (m.controller.buttonDown & A_BUTTON) ~= 0 and m.health > 0xFF then
			if m.floor ~= nil then
				SV_HandleSpecialFloors(m,true)
				local s = gPlayerSyncTable[m.playerIndex]
				local direction = GetAngleVectors(m).forward
				local yV = m.vel.y
				vec3f_copy(m.vel,vec3_scale(direction,m.forwardVel*3.5))
				vec3f_add(m.vel,vec3_qscale(m.floor.normal,-0.3,85 * clampf((m.forwardVel+math.abs(yV*0.32)) / 96, 0.5, 1.0),-0.3))
				m.vel.y = m.vel.y + (250 * clampf((m.forwardVel+math.abs(yV*0.32)) / 96, 0.65, 1.0))
				set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
				play_character_sound(m,CHAR_SOUND_YAHOO)
				return
			end
		end
	end,
	[ACT_HARD_BACKWARD_GROUND_KB] = function(m) 
		if (m.prevAction == ACT_SPECIAL_DEATH_EXIT) then m.healCounter = 32 end
		set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT, 0)
	end,
	[ACT_DEATH_EXIT_LAND] = function(m) 
		m.healCounter = 32 
		set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT, 0)
	end,
	[ACT_GETTING_BLOWN] = function(m) 
		vec3f_add(m.vel,{x=-coss(m.faceAngle.y)*75,y=50,z=-sins(m.faceAngle.y)*75})
		set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
	end,
	[ACT_DM_WATER_MOVEMENT] = function(m) 
		if (m.prevAction ~= ACT_DM_AIR_MOVEMENT and m.prevAction == ACT_DM_GROUNDED_MOVEMENT and m.prevAction ~= ACT_DM_AIR_MOVEMENT_METAL and m.prevAction == ACT_DM_GROUNDED_MOVEMENT_METAL and m.prevAction == ACT_DM_GROUNDED_IDLE) then SV_PlayerMovement_Store(m,false) end
	end
}

--- General helper functions
function ifelse(a,b,c)
	if (a) then return b else return c end
end

function vec3_invert(a)
	_x = a.x * -1.0
	_y = a.y * -1.0
	_z = a.z * -1.0
	return {x=_x,y=_y,z=_z}
end

function vec3_qscale(a,b,c,d)
	_x = a.x * b
	_y = a.y * c
	_z = a.z * d
	return {x=_x,y=_y,z=_z}
end

function vec3_scale(a,b)
	_x = a.x * b
	_y = a.y * b
	_z = a.z * b
	return {x=_x,y=_y,z=_z}
end

function s16(num)
    num = math.floor(num) & 0xFFFF
    if num >= 32768 then return num - 65536 end
    return num
end

function mario_holding_underwater_shell(m) -- direction is true then we're checking a small range behind, otherwise we're checking the inverse of that range
	if (m.heldObj == nil) then return false end
	return get_id_from_behavior(m.heldObj.behavior) == id_bhvKoopaShellUnderwater
end

function mario_is_within_object_angles(m, o, range, direction) -- direction is true then we're checking a small range behind, otherwise we're checking the inverse of that range
	local dx = o.oPosX - m.pos.x
    local dz = o.oPosZ - m.pos.z

    local dYaw = s16(o.oMoveAngleYaw - atan2s(dz, dx))
	
	if (dYaw >= -range and dYaw <= range) then
		return direction
	else
		return not direction
	end
end

function should_push_or_pull_door(m, o)
    local dx = o.oPosX - m.pos.x
    local dz = o.oPosZ - m.pos.z

    local dYaw = s16(o.oMoveAngleYaw - atan2s(dz, dx))
	
	if (dYaw >= -0x4000 and dYaw <= 0x4000) then
		return 0x00000001
	else
		return 0x00000002
	end
end

function get_object_closest_to_point(type,point) 
	local closestObj = nil
	local obj = obj_get_first(type)
	local minDist = 0x20000
	while obj ~= nil do
		local objDist = vec3f_dist({x=obj.oPosX,y=obj.oPosY,z=obj.oPosZ}, point)
		if objDist < minDist then
			local rad = obj.hitboxRadius+16
			local hei = obj.hitboxHeight+16
			if (vec3f_dist({x=obj.oPosX,y=0,z=obj.oPosZ}, {x=point.x,y=0,z=point.z}) <= rad and point.y >= obj.oPosY and point.y <= obj.oPosY+hei) then
				closestObj = obj
				minDist = objDist
			end
		end
		obj = obj_get_next(obj)
	end
	return closestObj
end				     

ObjectLists = {
	[0] = OBJ_LIST_PLAYER,
	[1] = OBJ_LIST_DESTRUCTIVE,
	[2] = OBJ_LIST_GENACTOR,
	[3] = OBJ_LIST_PUSHABLE,
	[4] = OBJ_LIST_LEVEL,
	[5] = OBJ_LIST_DEFAULT,
	[6] = OBJ_LIST_SURFACE,
	[7] = OBJ_LIST_POLELIKE,
	[8] = OBJ_LIST_SPAWNER,
	[9] = OBJ_LIST_UNIMPORTANT
}
ObjectHeightAddon = {
	[id_bhvPokey] = 30,
	[id_bhvPokeyBodyPart] = 50,
	[id_bhvGoomba] = 30,
	[id_bhvSmallBully] = 30,
	[id_bhvBobomb] = 30,
	[id_bhvBigBully] = 50,
	[id_bhvBigChillBully] = 50,
	[id_bhvBobombBuddy] = 50,
	[id_bhvMips] = 30,
	[id_bhvBoo] = 30,
	[id_bhvDoor] = 50,
	[id_bhvDoorWarp] = 50,
	[id_bhvStarDoor] = 50,
	[id_bhvBowser] = 80,
	[id_bhvKingBobomb] = 120,
	[id_bhvChuckya] = 120,
}

function get_any_object_closest_to_point(point) 
	local lastList = 0
	local closestObj = nil
	local obj = obj_get_first(ObjectLists[lastList])
	local minDist = 0x20000
	while obj ~= nil do
		if (obj_is_valid_for_interaction(obj)) then
			local objDist = vec3f_dist({x=obj.oPosX,y=obj.oPosY,z=obj.oPosZ}, point)
			if objDist < minDist then
				local offset = ObjectHeightAddon[get_id_from_behavior(obj.behavior)] ; if offset == nil then offset = 0 end
				local rad = obj.hitboxRadius+16
				local hei = obj.hitboxHeight+16+offset
				if (vec3f_dist({x=obj.oPosX,y=0,z=obj.oPosZ}, {x=point.x,y=0,z=point.z}) <= rad and point.y >= obj.oPosY and point.y <= obj.oPosY+hei) then
					closestObj = obj
					minDist = objDist
				end
			end
		end
		
		local nextObj = obj_get_next(obj)
		
		if (nextObj == nil) then
			while nextObj == nil and lastList < 9 do
				lastList = lastList + 1
				nextObj = obj_get_first(ObjectLists[lastList])
			end
		end
		
		obj = nextObj
	end
	return closestObj
end
