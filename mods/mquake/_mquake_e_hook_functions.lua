-- _mquake_a_constants
-- _mquake_b_actions_predefine
-- _mquake_c_actions
-- _mquake_d_physics
-- _mquake_e_hooks
-- localize functions to improve performance - _mquake_e_hook_functions.lua
local sins,coss,vec3f_copy,set_mario_action,perform_air_step,vec3f_dot,get_id_from_behavior,obj_get_first,obj_get_next,obj_get_nearest_object_with_behavior_id,vec3f_length,obj_check_hitbox_overlap = sins,coss,vec3f_copy,set_mario_action,perform_air_step,vec3f_dot,get_id_from_behavior,obj_get_first,obj_get_next,obj_get_nearest_object_with_behavior_id,vec3f_length,obj_check_hitbox_overlap

--- @param m MarioState
function active_player(m)
    local np = gNetworkPlayers[m.playerIndex]
    if m.playerIndex == 0 then
        return 1
    end
    if not np.connected then
        return 0
    end
    if np.currCourseNum ~= gNetworkPlayers[0].currCourseNum then
        return 0
    end
    if np.currActNum ~= gNetworkPlayers[0].currActNum then
        return 0
    end
    if np.currLevelNum ~= gNetworkPlayers[0].currLevelNum then
        return 0
    end
    if np.currAreaIndex ~= gNetworkPlayers[0].currAreaIndex then
        return 0
    end
    return is_player_active(m)
end

function on_set_mario_action(m) 
	if (m.playerIndex == 0) then 
		if (DM_ACTION_TRANSFERS[m.action] == 1) then
			local yVel = m.vel.y * 4
			local fVel = m.forwardVel * 4
			local s = gPlayerSyncTable[m.playerIndex]
			local direction = GetAngleVectors(m).forward
			vec3f_copy(m.vel,vec3_scale(direction,m.forwardVel*4))
			m.vel.y = yVel
			local is_underwater = m.pos.y <= m.waterLevel-sv_playersubmergelevel
			local metal_underwater = (m.flags & MARIO_METAL_CAP) ~= 0
			if ((m.action & ACT_FLAG_AIR) ~= 0) then
				set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
				return 1
			elseif ((m.action & ACT_GROUP_SUBMERGED) ~= 0) then
				if (not metal_underwater) and (is_underwater) then 
					set_mario_action(m, ACT_DM_WATER_MOVEMENT, 0) 
					return 1
				end
				if (metal_underwater) and (is_underwater) then 
					set_mario_action(m, ACT_DM_AIR_MOVEMENT_METAL, 0) 
					return 1
				end
			end 
			set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT, 0)
			return 1
		end
		if (DM_ACTION_FUNCTIONS[m.action] ~= nil) then
			DM_ACTION_FUNCTIONS[m.action](m)
			return 1
		end
	end
end

function allow_voice(m,s) 
	if (s == CHAR_SOUND_ON_FIRE or s == CHAR_SOUND_ATTACKED or s == CHAR_SOUND_EEUH) then
		return 0
	end
end

function override_defacto(m) 
	if m.action == ACT_DM_AIR_MOVEMENT or m.action == ACT_DM_GROUNDED_MOVEMENT or 
	m.action == ACT_DM_AIR_MOVEMENT_METAL or m.action == ACT_DM_GROUNDED_MOVEMENT_METAL or m.action == ACT_DM_GROUNDED_IDLE then 
		return 1 
	end 
end

function on_player_connected(m)
    gPlayerSyncTable[m.playerIndex].playerCrouching = false
    gPlayerSyncTable[m.playerIndex].playerFacingX = 1
    gPlayerSyncTable[m.playerIndex].playerFacingY = 0
    gPlayerSyncTable[m.playerIndex].playerFacingZ = 0
end

function before_set_mario_action(m,incoming) 
	if (m.playerIndex == 0) then 
		if (DM_ACTION_PREFUNCS[incoming] ~= nil) then
			return DM_ACTION_PREFUNCS[incoming](m)
		elseif (DM_ACTIONS[incoming] ~= 1) then
			m.controller.buttonPressed = 0
			local is_underwater = m.pos.y <= m.waterLevel-sv_playersubmergelevel
			local metal_underwater = (m.flags & MARIO_METAL_CAP) ~= 0
			if ((incoming & ACT_FLAG_AIR) ~= 0) then
				set_mario_action(m, ACT_DM_AIR_MOVEMENT, 0)
				return 1
			elseif ((incoming & ACT_FLAG_SWIMMING) ~= 0) or ((incoming & ACT_GROUP_SUBMERGED) ~= 0) then
				if (not metal_underwater) and (is_underwater) then 
					set_mario_action(m, ACT_DM_WATER_MOVEMENT, 0) 
					return 1
				end
				if (metal_underwater) and (is_underwater) then 
					set_mario_action(m, ACT_DM_AIR_MOVEMENT_METAL, 0) 
					return 1
				end
			end 
			set_mario_action(m, ACT_DM_GROUNDED_MOVEMENT, 0)
			return 1
		end
	end
end

function before_phys_step(m) 
	local act = m.action
	if (DM_ACTIONS[act] ~= 1) then return 0 end
	if ((act == ACT_DM_AIR_MOVEMENT or act == ACT_DM_AIR_MOVEMENT_METAL or act == ACT_DM_WATER_MOVEMENT) and m.playerIndex == 0 and m.ceil ~= nil) then
		local h = m.marioObj.hitboxHeight
		if (m.ceilHeight <= m.pos.y+(h*0.5)) then
			m.pos.y = m.ceilHeight - h
			return 0
		end
		
		if (m.pos.y + h + 4 + sv_camerayoffset  > m.ceilHeight and m.ceilHeight > m.pos.y + 16) then
			SV_PlayerMovement_Scale(m,true)
			vec3f_copy(m.vel, PHYS_CollideWithNormal(m.vel,m.ceil.normal,-1.0,0.05))
			SV_PlayerMovement_Scale(m,false)
			m.pos.y = m.pos.y - 1
			return perform_air_step(m,0)
		end
	end
end

function on_interact(m,o,i,b) 
	if DM_ACTION_QPHYS[m.action] == 1 then
		if (i == INTERACT_BOUNCE_TOP or i == INTERACT_BOUNCE_TOP2) then
			if (o.oInteractStatus & INT_STATUS_WAS_ATTACKED) ~= 0 then
				m.vel.y = 160
			end
		end
		if (o.oInteractStatus & INT_STATUS_ATTACKED_MARIO) ~= 0 and m.health > 0xFF then
			m.invincTimer = 30
			gLakituState.roll = 2730*(m.hurtCounter*0.25)
			gLakituState.oldRoll = gLakituState.roll
			cl_red = 128
		end
	end
end

function allow_interact(m,o,i) 
	if DM_ACTION_QPHYS[m.action] == 1 then
		if (i == INTERACT_POLE) then
			if (vec3f_dot({x=o.oPosX-m.pos.x,y=0,z=o.oPosZ-m.pos.z},{x=m.vel.x,y=0,z=m.vel.z}) <= 0) then 
				return false 
			end 
		end
		if (i == INTERACT_IGLOO_BARRIER) then
			if (m.controller.buttonDown & Z_TRIG ~= 0) then 
				return false 
			end 
		end
	end
end

function on_pvp(m,v) 
	if DM_ACTION_QPHYS[v.action] == 1 then
		v.invincTimer = 30
		if (v == gMarioStates[0]) then
			gLakituState.roll = 2730*(v.hurtCounter*0.25)
			gLakituState.oldRoll = gLakituState.roll
			cl_red = 128
		end
	end
end

local function render_speed(w2,h2,textWidth,h_offset,hspeed_text,scale,height) 
	local scale1 = scale*0.5
	djui_hud_set_color(0,0,0,100)
	djui_hud_render_rect((w2*0.5) - (textWidth*scale1) - 1,(h2*h_offset),textWidth*scale + 2,height)
	djui_hud_set_color(255,255,255,255)
	djui_hud_print_text(hspeed_text, (w2*0.5) - (textWidth*scale1),(h2*h_offset),scale)
end

function render_hud_effects() 
	local m = gMarioStates[0]
	if (m ~= nil) then
	
		djui_hud_set_resolution(RESOLUTION_DJUI)
		local w = djui_hud_get_screen_width()
		local h = djui_hud_get_screen_height()
		if (cl_red > 0) then 
			djui_hud_set_color(255,0,0,cl_red)
			djui_hud_render_rect(0,0,w,h)
		end
		local c = m.area.camera
		if (c ~= nil) then 
			if (c.pos.y < m.waterLevel) then
				djui_hud_set_color(38,139,255,100)
				djui_hud_render_rect(0,0,w,h)
			end
		end
		
		if (m.health <= 0xFF or m.action == ACT_UNINITIALIZED or m.action == ACT_DISAPPEARED) then return end
		
		djui_hud_set_resolution(RESOLUTION_N64)
		djui_hud_set_font(FONT_NORMAL)
		
		local w2 = djui_hud_get_screen_width()
		local h2 = djui_hud_get_screen_height()
		
		local hspeed = m.forwardVel*4 ; if (DM_ACTION_QPHYS[m.action] == 1) then hspeed = vec3f_length({x=m.vel.x,y=0,z=m.vel.z}) end
		local hspeed_text = tostring(math.floor(hspeed))
		local textWidth = djui_hud_measure_text(hspeed_text)
		render_speed(w2,h2,textWidth,0.8,hspeed_text,0.5,15)
		
		local vspeed = m.vel.y ; if (DM_ACTION_QPHYS[m.action] ~= 1) then vspeed = vspeed*4 end
		local vspeed_text = tostring(math.floor(vspeed))
		local vTextWidth = djui_hud_measure_text(vspeed_text)
		render_speed(w2,h2,vTextWidth,0.75,vspeed_text,0.25,7.5)
		
		if (m.capTimer > 0) then
			local capTimer_Seconds = math.floor(m.capTimer * 0.03333333333333333)
			local capText = "Cap Timer: " .. tostring(capTimer_Seconds)
			local capWidth = djui_hud_measure_text(capText)
			render_speed(w2,h2,capWidth,0.875,capText,0.5,15)
		end
		
		if (not sv_gunmod_loaded) then -- crosshair
			-- djui_hud_set_color(0,0,0,255)
			-- djui_hud_render_rect((w2*0.5) - 6,(h2*0.5) - 1,11,3)
			-- djui_hud_render_rect((w2*0.5) - 2,(h2*0.5) - 5,3,11)
			
			djui_hud_set_color(255,255,255,255)
			djui_hud_render_rect((w2*0.5) - 5,(h2*0.5),9,1)
			djui_hud_render_rect((w2*0.5) - 1,(h2*0.5) - 4,1,9)
		end
	end
end

function allow_pvp(m,v) 
	if (m.action == ACT_DM_AIR_MOVEMENT or m.action == ACT_DM_AIR_MOVEMENT_METAL or m.action == ACT_DM_WATER_MOVEMENT) then
		return false
	end
end

function on_object_render(o) 
	if (get_id_from_behavior(o.behavior) == id_bhvMario) then
		local m = gMarioStates[0]
		if (o == m.marioObj) then
			o.header.gfx.shadowInvisible = true
			o.header.gfx.disableAutomaticShadowPos = true
		
			if (m.heldObj ~= nil) then
				local cYaw = m.area.camera.yaw + 0x8000
				local fA = m.faceAngle.y + 0x4000
			
				local offsetX_FaceAngle = 40 * sins(fA)
				local offsetZ_FaceAngle = 40 * coss(fA)
				
				local factorY_CameraAngle = sins(gLakituState.oldPitch)
				
				local offsetX_CameraAngle_Fixup = (sins(cYaw)) * factorY_CameraAngle
				local offsetZ_CameraAngle_Fixup = (coss(cYaw)) * factorY_CameraAngle
				
				local finalOffsetX = offsetX_FaceAngle + offsetX_CameraAngle_Fixup
				local finalOffsetY = -60
				local finalOffsetZ = offsetZ_FaceAngle + offsetZ_CameraAngle_Fixup
				
			
				m.marioObj.header.gfx.pos.x = m.marioBodyState.heldObjLastPosition.x + finalOffsetX
				m.marioObj.header.gfx.pos.y = m.marioBodyState.heldObjLastPosition.y + finalOffsetY
				m.marioObj.header.gfx.pos.z = m.marioBodyState.heldObjLastPosition.z + finalOffsetZ
			end
		end
	end
end
function on_level_init()
	gLakituState.roll = 0 -- fix death angles through paintings
	local lastList = 0
	local obj = obj_get_first(ObjectLists[lastList])
	while obj ~= nil do
		obj.header.gfx.skipInViewCheck = true
		local nextObj = obj_get_next(obj)
		if (nextObj == nil) then
			while nextObj == nil and lastList < 9 do
				lastList = lastList + 1
				nextObj = obj_get_first(ObjectLists[lastList])
			end
		end
		obj = nextObj
	end
end

function local_update() 
	local m = gMarioStates[0]
	if (m == nil) then return end
	
	if (cl_interacttimer > 0) then cl_interacttimer = cl_interacttimer - 1 end
	if (cl_red > 0) then cl_red = cl_red - 32 end
	
	-- set_override_fov(90)

	m.marioObj.hookRender = 1
	m.peakHeight = m.pos.y
	
	set_first_person_enabled(true)
	gFirstPersonCamera.fov = 90
	
	if (m.heldObj ~= nil) then
		held_obj_update(m)
	end
	
	if (DM_ACTION_QPHYS[m.action] == 1) then
		if (m.controller.buttonDown & B_BUTTON) ~= 0 and (m.flags & MARIO_UNKNOWN_31) == 0 then
			m.flags = m.flags | MARIO_UNKNOWN_31
		elseif (m.flags & MARIO_UNKNOWN_31) ~= 0 then
			m.flags = m.flags & ~MARIO_UNKNOWN_31
		end
	end
	
	if ((m.flags & MARIO_CAP_IN_HAND) ~= 0) then
		m.flags = (m.flags | MARIO_CAP_ON_HEAD) & ~MARIO_CAP_IN_HAND
	end
	
	if (cl_bowserthrow) then 
		cl_bowserthrow_previousYaw = m.faceAngle.y
		cl_bowserthrow = m.heldObj ~= nil 
		m.faceAngle.y = m.area.camera.yaw + 0x8000
	end
	
	SV_HandleSpecialFloors(m,false)
	
	local shouldCrouch = ((m.controller.buttonDown & Z_TRIG) ~= 0 and m.health > 0xFF) or m.action == ACT_GROUND_POUND
	if (DM_ACTION_FORCEANGLE[m.action] ~= nil and not cl_bowserthrow) then 
		m.faceAngle.y = m.area.camera.yaw + (0x8000*DM_ACTION_FORCEANGLE[m.action])
	end
	
	if (DM_ACTIONS_CROUCHAIR[m.action] == 1) then
		if (shouldCrouch ~= gPlayerSyncTable[m.playerIndex].playerCrouching) then
			if (shouldCrouch) then 
				m.pos.y = m.pos.y + sv_crouchoffset 
			else 
				if (m.pos.y - sv_crouchoffset < m.floorHeight) then
					m.pos.y = m.floorHeight
				else
					m.pos.y = m.pos.y - sv_crouchoffset 
				end
			end
		end
	end
	
	gPlayerSyncTable[m.playerIndex].playerCrouching = shouldCrouch
	
	gFirstPersonCamera.offset.y = ifelse(shouldCrouch, sv_camerayoffset-sv_crouchoffset, sv_camerayoffset)
	
	if (m.health <= 0xFF) then
		gFirstPersonCamera.offset.y = -110
		gLakituState.roll = 0
		m.invincTimer = 0
		cl_red = 192
	else
		gLakituState.roll = gLakituState.roll * 0.75
		if (DM_ACTIONS_ALLOWGRAB[m.action] == 1) then
			mario_handle_grab_and_punch_custom(m) 
		end
	end
	
	m.marioObj.hitboxHeight = ifelse(shouldCrouch, sv_playerheight-sv_crouchoffset, sv_playerheight)

	local warp = obj_get_nearest_object_with_behavior_id(m.marioObj, id_bhvFadingWarp)
	if warp ~= nil and m.heldObj == nil and m.action ~= ACT_TELEPORT_FADE_OUT and m.action ~= ACT_TELEPORT_FADE_IN and obj_check_hitbox_overlap(m.marioObj, warp) and vec3f_length(m.vel) < 1 and gPlayerSyncTable[m.playerIndex].playerCrouching then
		m.interactObj = warp
		m.usedObj = warp
		set_mario_action(m, ACT_TELEPORT_FADE_OUT, 0)
	end
end