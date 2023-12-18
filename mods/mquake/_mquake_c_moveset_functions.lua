-- _mquake_a_constants
-- _mquake_b_actions_predefine
-- _mquake_c_actions
-- _mquake_d_physics
-- _mquake_e_hooks
-- localize functions to improve performance - _mquake_c_moveset_functions.lua
local get_id_from_behavior,mario_grab_used_object,mario_throw_held_object,obj_is_grabbable,obj_is_attackable,obj_is_breakable_object,mario_drop_held_object,obj_get_nearest_object_with_behavior_id,vec3f_dot,vec3f_length,obj_check_hitbox_overlap,max,level_trigger_warp,absf_2 = get_id_from_behavior,mario_grab_used_object,mario_throw_held_object,obj_is_grabbable,obj_is_attackable,obj_is_breakable_object,mario_drop_held_object,obj_get_nearest_object_with_behavior_id,vec3f_dot,vec3f_length,obj_check_hitbox_overlap,max,level_trigger_warp,absf_2
local vec3f_add = vec3f_add
local set_mario_action = set_mario_action

function obj_activate_door(m,door,bhv)
	if (m.action == ACT_DM_WATER_MOVEMENT) then return true end
	
	if door ~= nil then
		local flags = save_file_get_flags()
		-- local bhv = get_id_from_behavior(door)
		if bhv == id_bhvDoor then
			local doorStars = door.oBehParams >> 24
			if (doorStars <= save_file_get_total_star_count(get_current_save_file_num()-1,0,255)) then
				door.oAction = 1
				door.header.gfx.animInfo.animFrame = max(door.header.gfx.animInfo.animFrame, 25)
			end
			return true
		elseif bhv == id_bhvDoorWarp then
			local wDoorID = door.oBehParams >> 24
			if (wDoorID == 1 and (flags & SAVE_FLAG_HAVE_KEY_2) == 0) then
				return true
			end
			if (wDoorID == 2 and (flags & SAVE_FLAG_HAVE_KEY_1) == 0) then
				return true
			end
			door.oAction = 2
			door.header.gfx.animInfo.animFrame = max(door.header.gfx.animInfo.animFrame, 10)
			m.interactObj = door
			m.usedObj = door
			m.actionArg = should_push_or_pull_door(m, door)
			level_trigger_warp(m, WARP_OP_WARP_DOOR)
			return true
		elseif bhv == id_bhvStarDoor and door.oAction == 0 then
			local doorStars = door.oBehParams >> 24
			if (doorStars <= save_file_get_total_star_count(get_current_save_file_num()-1,0,255)) then
				door.oInteractStatus = 0x00010000
			end
			return true
		end
	end
	return false
end

function held_obj_update(m)
	local obj = m.heldObj
	local bhv = get_id_from_behavior(obj.behavior)
	
	if (bhv == id_bhvBobomb) then
		if (obj.oBobombFuseTimer >= 151) then
			mario_drop_held_object(m)
		end
	end
	
	if (bhv == id_bhvKoopaShellUnderwater) then
		if (obj.oTimer >= 601 or m.action ~= ACT_DM_WATER_MOVEMENT) then
			mario_drop_held_object(m)
		end
		obj.oTimer = obj.oTimer + 1
	end
end

function mario_throw_object_ext(m,ang)
	local obj = m.heldObj
	local bhv = get_id_from_behavior(obj.behavior)
	
	if (bhv == id_bhvBowser and cl_bowserthrow) then
		local curFaceAngle = m.faceAngle.y
		m.faceAngle.y = m.area.camera.yaw + 0x8000
		mario_drop_held_object(m)
		obj.oPosX = m.marioBodyState.heldObjLastPosition.x
		obj.oPosY = m.marioBodyState.heldObjLastPosition.y
		obj.oPosZ = m.marioBodyState.heldObjLastPosition.z
		
		-- Todo ; How do we fix this shit maintaining the velocity?
		
		m.marioObj.oAngleVelYaw = 0
		m.marioObj.oMoveAnglePitch = 0
		obj.oForwardVel = 0
		obj.oVelY = 0
		obj.oBowserHeldAngleVelYaw = clampf(absf_2(s16(cl_bowserthrow_previousYaw-curFaceAngle)),0x10,0x1000)
		obj.oBowserHeldAnglePitch = clampf(-absf_2(s16(cl_bowserthrow_previousYaw-curFaceAngle)),-0x1000,-0x400)
		
		network_send_object(obj,true)
		return true
	end
	
	if (bhv == id_bhvJumpingBox) then
		mario_drop_held_object(m)
		
		set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
		
		vec3f_add(m.vel,vec3_scale(ang.forward,300))
		vec3f_add(m.vel,{x=0,y=500,z=0})
		
		obj.oPosX = m.pos.x
		obj.oPosY = m.pos.y
		obj.oPosZ = m.pos.z
		
		return true
	end
	
	return false
end

function mario_drop_object_ext(m,ang)
	local obj = m.heldObj
	local bhv = get_id_from_behavior(obj.behavior)
	
	if (bhv == id_bhvJumpingBox) then
		return mario_throw_object_ext(m,ang)
	end
	
	return false
end

function mario_grab_used_object_ext(m,ang)
	local o = m.usedObj
	local bhv = get_id_from_behavior(o.behavior)
	
	if (bhv == id_bhvBowser) then
		if (not mario_is_within_object_angles(m, o, 0x2000, true)) then return false end
		cl_bowserthrow = true
		o.oForwardVel = 0
		o.oVelY = 0
		
		o.oBowserHeldAngleVelYaw = 0
		o.oBowserHeldAnglePitch = 0
		o.oMoveAnglePitch = 0
		o.oMoveAngleYaw = 0
		o.oForwardVelS32 = 0
		o.oForwardVel = 0
		
		m.marioObj.oAngleVelYaw = 0
		m.marioObj.oMoveAnglePitch = 0
		m.marioObj.oMoveAngleYaw = 0
		m.marioObj.oForwardVelS32 = 0
		m.marioObj.oForwardVel = 0
	end
	
	if (bhv == id_bhvKingBobomb) then
		if (not mario_is_within_object_angles(m, o, 0x2000, true)) then return false end
		
		mario_grab_used_object(m)
		
		return false
	end
	
	if (bhv == id_bhvChuckya) then
		if (not mario_is_within_object_angles(m, o, 0x2000, true)) then return false end
		
		mario_grab_used_object(m)
		
		return false
	end
	
	if (bhv == id_bhvKoopaShellUnderwater) then
		if (m.action ~= ACT_DM_WATER_MOVEMENT) then return false end
		o.oTimer = 0 -- ten seconds
	end
	
	mario_grab_used_object(m)
	return o == m.heldObj
end

function mario_handle_grab_and_punch_custom(m) 
	if m.heldByObj ~= nil then return end
	if m == nil then return end
	
	local pressedB = (m.controller.buttonPressed & B_BUTTON) ~= 0
	local pressedZ = (m.controller.buttonPressed & Z_TRIG) ~= 0
	
	local ang = nil
	
	if m.heldObj ~= nil then 
		if (ang == nil) then ang = GetAngleVectors(m) end
		local obj = m.heldObj
		if (cl_bowserthrow) then
			m.marioBodyState.heldObjLastPosition.x = m.area.camera.pos.x + (ang.forward.x * (160+(obj.hitboxRadius*0.5)))
			m.marioBodyState.heldObjLastPosition.y = m.area.camera.pos.y + (ang.forward.y * (160+(obj.hitboxRadius*0.5))) - (obj.hitboxHeight*0.5) + 64
			m.marioBodyState.heldObjLastPosition.z = m.area.camera.pos.z + (ang.forward.z * (160+(obj.hitboxRadius*0.5)))
		else
			m.marioBodyState.heldObjLastPosition.x = m.area.camera.pos.x + (ang.rawForward.x * (160+(obj.hitboxRadius*0.5))) + (m.vel.x*0.25)
			m.marioBodyState.heldObjLastPosition.y = m.area.camera.pos.y + ((ang.rawForward.y * (160+(obj.hitboxRadius*0.5))) + (m.vel.y*0.25)) - (obj.hitboxHeight*0.5)
			m.marioBodyState.heldObjLastPosition.z = m.area.camera.pos.z + (ang.rawForward.z * (160+(obj.hitboxRadius*0.5))) + (m.vel.z*0.25)
		end
	end
		
	m.controller.buttonPressed = m.controller.buttonPressed & ~(B_BUTTON|Z_TRIG)
	if (pressedB) then 
		if (ang == nil) then ang = GetAngleVectors(m) end
		if m.heldObj ~= nil then 
			if not mario_throw_object_ext(m,ang) then
				local curFaceAngle = m.faceAngle.y
				local obj = m.heldObj
				m.faceAngle.y = m.area.camera.yaw + 0x8000
				mario_throw_held_object(m)
				obj.oPosX = m.marioBodyState.heldObjLastPosition.x
				obj.oPosY = m.marioBodyState.heldObjLastPosition.y
				obj.oPosZ = m.marioBodyState.heldObjLastPosition.z
				obj.oVelX = (ang.rawForward.x * 160) + (m.vel.x*0.25)
				obj.oVelY = (ang.rawForward.y * 160) + (m.vel.x*0.25)
				obj.oVelZ = (ang.rawForward.z * 160) + (m.vel.x*0.25)
				obj.oMoveAnglePitch = gLakituState.oldPitch
				obj.oMoveAngleYaw = m.faceAngle.y
				obj.oMoveAngleRoll = 0
				obj.oFaceAnglePitch = 0
				obj.oFaceAngleYaw = m.faceAngle.y
				obj.oFaceAngleRoll = 0
				m.faceAngle.y = curFaceAngle
			end
		elseif (cl_interacttimer == 0) then
			-- play_character_sound(m,CHAR_SOUND_PUNCH_HOO)
			cl_interacttimer = 15
			m.marioBodyState.heldObjLastPosition.x = m.area.camera.pos.x + (ang.rawForward.x * 160)
			m.marioBodyState.heldObjLastPosition.y = m.area.camera.pos.y + (ang.rawForward.y * 160)
			m.marioBodyState.heldObjLastPosition.z = m.area.camera.pos.z + (ang.rawForward.z * 160)
			local target = get_any_object_closest_to_point(m.marioBodyState.heldObjLastPosition)
			if (target ~= nil) then
				local bhv = get_id_from_behavior(target.behavior)
				if (not obj_activate_door(m,target,bhv)) then
					if (obj_is_grabbable(target)) then
						m.interactObj = target
						m.usedObj = target
						if (not mario_grab_used_object_ext(m,ang)) then
							m.interactObj = nil
							m.usedObj = nil
						end
					elseif (obj_is_attackable(target) or obj_is_exclamation_box(target) or obj_is_bully(target) or obj_is_breakable_object(target)) then
						m.interactObj = target
						m.usedObj = target
						target.oInteractStatus = INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED | ATTACK_PUNCH
					-- elseif (bhv == id_bhvMario) then
					
					end
				end
			else
				play_sound(CAM_SOUND_UNUSED_SELECT_FIXED, m.marioObj.header.gfx.cameraToObject)
			end
		end
	end
	if (pressedZ) then 
		if m.heldObj ~= nil then 
			if (not mario_drop_object_ext(m,ang)) then
				local curFaceAngle = m.faceAngle.y
				local obj = m.heldObj
				m.faceAngle.y = m.area.camera.yaw + 0x8000
				mario_drop_held_object(m)
				obj.oPosX = m.marioBodyState.heldObjLastPosition.x
				obj.oPosY = m.marioBodyState.heldObjLastPosition.y
				obj.oPosZ = m.marioBodyState.heldObjLastPosition.z
				obj.oMoveAnglePitch = gLakituState.oldPitch
				obj.oMoveAngleYaw = m.faceAngle.y
				obj.oMoveAngleRoll = 0
				obj.oFaceAnglePitch = 0
				obj.oFaceAngleYaw = m.faceAngle.y
				obj.oFaceAngleRoll = 0
				m.faceAngle.y = curFaceAngle
			end
		end
	end
end

-- function obj_affect_nearest_door(m,bhv)
	-- local door = obj_get_nearest_object_with_behavior_id(m.marioObj, bhv)
	-- if door ~= nil and obj_check_hitbox_overlap(m.marioObj, door) and vec3f_dot(m.vel,{x=m.pos.x-door.oPosX,y=0,z=m.pos.z-door.oPosZ}) <= -0.1 and vec3f_length(m.vel) > 20 then
		-- if bhv == id_bhvDoor then
			-- door.oAction = 1
			-- door.header.gfx.animInfo.animFrame = max(door.header.gfx.animInfo.animFrame, 20)
		-- elseif bhv == id_bhvDoorWarp then
			-- door.oAction = 2
			-- door.header.gfx.animInfo.animFrame = max(door.header.gfx.animInfo.animFrame, 10)
			-- m.interactObj = door
			-- m.usedObj = door
			-- m.actionArg = should_push_or_pull_door(m, door)
			-- level_trigger_warp(m, WARP_OP_WARP_DOOR)
		-- elseif bhv == id_bhvStarDoor and door.oAction == 0 then
			-- door.oInteractStatus = 0x00010000
		-- end
	-- end
-- end