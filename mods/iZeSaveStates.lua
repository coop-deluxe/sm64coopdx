-- name: iZeSaveStates v2.1.5
-- description: Adds SaveStates to SM64EX-COOP!\n\n-Save up to 4 states at the same time by using the 4 D-Pad buttons\n-To load states, hold down L and press the corresponding D-Pad button\n-Each player gets their own 4 local savestate slots (Global SaveStates maybe in the future)\n\n-Use /autoload or /al to toggle AutoLoading the latest savestate upon death\n-Use /autoheal or /ah to toggle AutoHealing after loading savestates\n-Use /savestates, /savestate, or /ss to get infos about your local settings and slots

local autoload_enabled = false
local autoheal_enabled = false
local latest_savestate = nil
local wait_until_inited = nil
local ready_to_load = nil
local savestates = {}
savestates.gNetworkPlayers_currLevelNum = { nil, nil, nil, nil }
savestates.gNetworkPlayers_currActNum = { nil, nil, nil, nil }
savestates.gNetworkPlayers_currAreaIndex = { nil, nil, nil, nil }
savestates.action = { nil, nil, nil, nil }
savestates.actionArg = { nil, nil, nil, nil }
savestates.actionState = { nil, nil, nil, nil }
savestates.actionTimer = { nil, nil, nil, nil }
savestates.angleVel_x = { nil, nil, nil, nil }
savestates.angleVel_y = { nil, nil, nil, nil }
savestates.angleVel_z = { nil, nil, nil, nil }
savestates.animation_targetAnim = { nil, nil, nil, nil }
savestates.area_camera = { nil, nil, nil, nil }
savestates.area_flags = { nil, nil, nil, nil }
savestates.area_index = { nil, nil, nil, nil }
savestates.area_instantWarps = { nil, nil, nil, nil }
savestates.area_musicParam = { nil, nil, nil, nil }
savestates.area_musicParam2 = { nil, nil, nil, nil }
savestates.area_numRedCoins = { nil, nil, nil, nil }
savestates.area_numSecrets = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_activeAreaIndex = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_areaIndex = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_behaviorArg = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_startAngle_x = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_startAngle_y = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_startAngle_z = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_startPos_x = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_startPos_y = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_startPos_z = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_unk18_extraFlags = { nil, nil, nil, nil }
savestates.area_objectSpawnInfos_unk18_flags = { nil, nil, nil, nil }
savestates.area_paintingWarpNodes_destArea = { nil, nil, nil, nil }
savestates.area_paintingWarpNodes_destLevel = { nil, nil, nil, nil }
savestates.area_paintingWarpNodes_destNode = { nil, nil, nil, nil }
savestates.area_paintingWarpNodes_id = { nil, nil, nil, nil }
savestates.area_terrainType = { nil, nil, nil, nil }
savestates.area_warpNodes_next = { nil, nil, nil, nil }
savestates.area_warpNodes_node_destArea = { nil, nil, nil, nil }
savestates.area_warpNodes_node_destLevel = { nil, nil, nil, nil }
savestates.area_warpNodes_node_destNode = { nil, nil, nil, nil }
savestates.area_warpNodes_node_id = { nil, nil, nil, nil }
savestates.area_warpNodes_object = { nil, nil, nil, nil }
savestates.bounceSquishTimer = { nil, nil, nil, nil }
savestates.bubbleObj = { nil, nil, nil, nil }
savestates.cap = { nil, nil, nil, nil }
savestates.capTimer = { nil, nil, nil, nil }
savestates.ceil = { nil, nil, nil, nil }
savestates.ceilHeight = { nil, nil, nil, nil }
savestates.character = { nil, nil, nil, nil }
savestates.collidedObjInteractTypes = { nil, nil, nil, nil }
savestates.controller_buttonDown = { nil, nil, nil, nil }
savestates.controller_buttonPressed = { nil, nil, nil, nil }
savestates.controller_extStickX = { nil, nil, nil, nil }
savestates.controller_extStickY = { nil, nil, nil, nil }
savestates.controller_port = { nil, nil, nil, nil }
savestates.controller_rawStickX = { nil, nil, nil, nil }
savestates.controller_rawStickY = { nil, nil, nil, nil }
savestates.controller_stickMag = { nil, nil, nil, nil }
savestates.controller_stickX = { nil, nil, nil, nil }
savestates.controller_stickY = { nil, nil, nil, nil }
savestates.curAnimOffset = { nil, nil, nil, nil }
savestates.currentRoom = { nil, nil, nil, nil }
savestates.doubleJumpTimer = { nil, nil, nil, nil }
savestates.faceAngle_x = { nil, nil, nil, nil }
savestates.faceAngle_y = { nil, nil, nil, nil }
savestates.faceAngle_z = { nil, nil, nil, nil }
savestates.fadeWarpOpacity = { nil, nil, nil, nil }
savestates.flags = { nil, nil, nil, nil }
savestates.floor = { nil, nil, nil, nil }
savestates.floorAngle = { nil, nil, nil, nil }
savestates.floorHeight = { nil, nil, nil, nil }
savestates.forwardVel = { nil, nil, nil, nil }
savestates.framesSinceA = { nil, nil, nil, nil }
savestates.framesSinceB = { nil, nil, nil, nil }
savestates.freeze = { nil, nil, nil, nil }
savestates.healCounter = { nil, nil, nil, nil }
savestates.health = { nil, nil, nil, nil }
savestates.heldByObj = { nil, nil, nil, nil }
savestates.heldObj = { nil, nil, nil, nil }
savestates.hurtCounter = { nil, nil, nil, nil }
savestates.input = { nil, nil, nil, nil }
savestates.intendedMag = { nil, nil, nil, nil }
savestates.intendedYaw = { nil, nil, nil, nil }
savestates.interactObj = { nil, nil, nil, nil }
savestates.invincTimer = { nil, nil, nil, nil }
savestates.isSnoring = { nil, nil, nil, nil }
savestates.knockbackTimer = { nil, nil, nil, nil }
savestates.marioBodyState_action = { nil, nil, nil, nil }
savestates.marioBodyState_capState = { nil, nil, nil, nil }
savestates.marioBodyState_eyeState = { nil, nil, nil, nil }
savestates.marioBodyState_grabPos = { nil, nil, nil, nil }
savestates.marioBodyState_handState = { nil, nil, nil, nil }
savestates.marioBodyState_headAngle_x = { nil, nil, nil, nil }
savestates.marioBodyState_headAngle_y = { nil, nil, nil, nil }
savestates.marioBodyState_headAngle_z = { nil, nil, nil, nil }
savestates.marioBodyState_headPos_x = { nil, nil, nil, nil }
savestates.marioBodyState_headPos_y = { nil, nil, nil, nil }
savestates.marioBodyState_headPos_z = { nil, nil, nil, nil }
savestates.marioBodyState_heldObjLastPosition_x = { nil, nil, nil, nil }
savestates.marioBodyState_heldObjLastPosition_y = { nil, nil, nil, nil }
savestates.marioBodyState_heldObjLastPosition_z = { nil, nil, nil, nil }
savestates.marioBodyState_modelState = { nil, nil, nil, nil }
savestates.marioBodyState_punchState = { nil, nil, nil, nil }
savestates.marioBodyState_torsoAngle_x = { nil, nil, nil, nil }
savestates.marioBodyState_torsoAngle_y = { nil, nil, nil, nil }
savestates.marioBodyState_torsoAngle_z = { nil, nil, nil, nil }
savestates.marioBodyState_torsoPos_x = { nil, nil, nil, nil }
savestates.marioBodyState_torsoPos_y = { nil, nil, nil, nil }
savestates.marioBodyState_torsoPos_z = { nil, nil, nil, nil }
savestates.marioBodyState_wingFlutter = { nil, nil, nil, nil }
savestates.marioObj_activeFlags = { nil, nil, nil, nil }
savestates.marioObj_areaTimer = { nil, nil, nil, nil }
savestates.marioObj_areaTimerDuration = { nil, nil, nil, nil }
savestates.marioObj_areaTimerType = { nil, nil, nil, nil }
savestates.marioObj_bhvDelayTimer = { nil, nil, nil, nil }
savestates.marioObj_collidedObjInteractTypes = { nil, nil, nil, nil }
savestates.marioObj_collisionData = { nil, nil, nil, nil }
savestates.marioObj_ctx = { nil, nil, nil, nil }
savestates.marioObj_globalPlayerIndex = { nil, nil, nil, nil }
savestates.marioObj_header_gfx_activeAreaIndex = { nil, nil, nil, nil }
savestates.marioObj_header_gfx_areaIndex = { nil, nil, nil, nil }
savestates.marioObj_header_gfx_disableAutomaticShadowPos = { nil, nil, nil, nil }
savestates.marioObj_header_gfx_shadowInvisible = { nil, nil, nil, nil }
savestates.marioObj_header_gfx_skipInViewCheck = { nil, nil, nil, nil }
savestates.marioObj_heldByPlayerIndex = { nil, nil, nil, nil }
savestates.marioObj_hitboxDownOffset = { nil, nil, nil, nil }
savestates.marioObj_hitboxHeight = { nil, nil, nil, nil }
savestates.marioObj_hitboxRadius = { nil, nil, nil, nil }
savestates.marioObj_hookRender = { nil, nil, nil, nil }
savestates.marioObj_hurtboxHeight = { nil, nil, nil, nil }
savestates.marioObj_hurtboxRadius = { nil, nil, nil, nil }
savestates.marioObj_parentObj = { nil, nil, nil, nil }
savestates.marioObj_platform = { nil, nil, nil, nil }
savestates.marioObj_prevObj = { nil, nil, nil, nil }
savestates.marioObj_setHome = { nil, nil, nil, nil }
savestates.marioObj_unused1 = { nil, nil, nil, nil }
savestates.marioObj_usingObj = { nil, nil, nil, nil }
savestates.minimumBoneY = { nil, nil, nil, nil }
savestates.nonInstantWarpPos_x = { nil, nil, nil, nil }
savestates.nonInstantWarpPos_y = { nil, nil, nil, nil }
savestates.nonInstantWarpPos_z = { nil, nil, nil, nil }
savestates.numCoins = { nil, nil, nil, nil }
savestates.numKeys = { nil, nil, nil, nil }
savestates.numLives = { nil, nil, nil, nil }
savestates.numStars = { nil, nil, nil, nil }
savestates.particleFlags = { nil, nil, nil, nil }
savestates.peakHeight = { nil, nil, nil, nil }
savestates.pos_x = { nil, nil, nil, nil }
savestates.pos_y = { nil, nil, nil, nil }
savestates.pos_z = { nil, nil, nil, nil }
savestates.prevAction = { nil, nil, nil, nil }
savestates.prevNumStarsForDialog = { nil, nil, nil, nil }
savestates.quicksandDepth = { nil, nil, nil, nil }
savestates.riddenObj = { nil, nil, nil, nil }
savestates.slideVelX = { nil, nil, nil, nil }
savestates.slideVelZ = { nil, nil, nil, nil }
savestates.slideYaw = { nil, nil, nil, nil }
savestates.spawnInfo = { nil, nil, nil, nil }
savestates.specialTripleJump = { nil, nil, nil, nil }
savestates.splineKeyframe = { nil, nil, nil, nil }
savestates.splineKeyframeFraction = { nil, nil, nil, nil }
savestates.splineState = { nil, nil, nil, nil }
savestates.squishTimer = { nil, nil, nil, nil }
savestates.statusForCamera_action = { nil, nil, nil, nil }
savestates.statusForCamera_cameraEvent = { nil, nil, nil, nil }
savestates.statusForCamera_faceAngle_x = { nil, nil, nil, nil }
savestates.statusForCamera_faceAngle_y = { nil, nil, nil, nil }
savestates.statusForCamera_faceAngle_z = { nil, nil, nil, nil }
savestates.statusForCamera_headRotation_x = { nil, nil, nil, nil }
savestates.statusForCamera_headRotation_y = { nil, nil, nil, nil }
savestates.statusForCamera_headRotation_z = { nil, nil, nil, nil }
savestates.statusForCamera_pos_x = { nil, nil, nil, nil }
savestates.statusForCamera_pos_y = { nil, nil, nil, nil }
savestates.statusForCamera_pos_z = { nil, nil, nil, nil }
savestates.statusForCamera_unused = { nil, nil, nil, nil }
savestates.statusForCamera_usedObj = { nil, nil, nil, nil }
savestates.terrainSoundAddend = { nil, nil, nil, nil }
savestates.twirlYaw = { nil, nil, nil, nil }
savestates.unkB0 = { nil, nil, nil, nil }
savestates.unkC4 = { nil, nil, nil, nil }
savestates.usedObj = { nil, nil, nil, nil }
savestates.vel_x = { nil, nil, nil, nil }
savestates.vel_y = { nil, nil, nil, nil }
savestates.vel_z = { nil, nil, nil, nil }
savestates.wall = { nil, nil, nil, nil }
savestates.wallKickTimer = { nil, nil, nil, nil }
savestates.wallNormal_x = { nil, nil, nil, nil }
savestates.wallNormal_y = { nil, nil, nil, nil }
savestates.wallNormal_z = { nil, nil, nil, nil }
savestates.wasNetworkVisible = { nil, nil, nil, nil }
savestates.waterLevel = { nil, nil, nil, nil }

function on_join(m)
    if m.playerIndex == 0 then
        reset_all(m)
    end
end

function on_leave(m)
    if m.playerIndex == 0 then
        reset_all(m)
    end
end

function on_death(m)
    if m.playerIndex == 0 then
        if autoload_enabled == true then
			if latest_savestate ~= nil and is_state_slot_not_empty(latest_savestate) then
			    local nCoins = m.numCoins
				local nRedCoins = m.area.numRedCoins
				local nSecrets = m.area.numSecrets
				init_single_mario(m)
				m.pos.x = 0
				m.pos.y = 0
				m.pos.z = 0
				m.health = 0x880
				m.numLives = m.numLives + 1
				m.numCoins = nCoins
				m.area.numRedCoins = nRedCoins
				m.area.numSecrets = nSecrets
				soft_reset_camera(m.area.camera)
				djui_popup_create("\\#ff80ff\\[AutoLoad] Loading latest state...", 1)
				load_state_slot(m, latest_savestate)
				return false
			else
				latest_savestate = nil
				play_sound(SOUND_GENERAL_FLAME_OUT, m.marioObj.header.gfx.cameraToObject)
				djui_popup_create("\\#a0a0a0\\[AutoLoad] 404 latest state not found!", 1)
				return true
			end
		else
			return true
		end
    end
end

function on_level_init()
	if wait_until_inited ~= nil then
		ready_to_load = wait_until_inited
		wait_until_inited = nil
	end
end

function on_mario_update(m)
    if m.playerIndex == 0 then
		if ready_to_load ~= nil then
			load_state_slot(m, ready_to_load)
		else
			if (m.controller.buttonDown & L_TRIG) == 0 then
				if (m.controller.buttonPressed & L_JPAD) ~= 0 then
					save_state_slot(m, 0, "\\#ff4040\\")
				elseif (m.controller.buttonPressed & U_JPAD) ~= 0 then
					save_state_slot(m, 1, "\\#40ff40\\")
				elseif (m.controller.buttonPressed & R_JPAD) ~= 0 then
					save_state_slot(m, 2, "\\#4040ff\\")
				elseif (m.controller.buttonPressed & D_JPAD) ~= 0 then
					save_state_slot(m, 3, "\\#ffff40\\")
				end
			else
				if (m.controller.buttonPressed & L_JPAD) ~= 0 then
					load_state_slot(m, 0)
				elseif (m.controller.buttonPressed & U_JPAD) ~= 0 then
					load_state_slot(m, 1)
				elseif (m.controller.buttonPressed & R_JPAD) ~= 0 then
					load_state_slot(m, 2)
				elseif (m.controller.buttonPressed & D_JPAD) ~= 0 then
					load_state_slot(m, 3)
				end
			end
		end
	end
end

function reset_all(m)
	delete_state_slot(m,0)
	delete_state_slot(m,1)
	delete_state_slot(m,2)
	delete_state_slot(m,3)
	autoload_enabled = false
	autoheal_enabled = false
	latest_savestate = nil
end

function save_state_slot(m, slot, color)
	savestates.gNetworkPlayers_currLevelNum[slot] = gNetworkPlayers[0].currLevelNum
	savestates.gNetworkPlayers_currActNum[slot] = gNetworkPlayers[0].currActNum
	savestates.gNetworkPlayers_currAreaIndex[slot] = gNetworkPlayers[0].currAreaIndex
	savestates.action[slot] = ((m and m.action) and m.action or nil)
	savestates.actionArg[slot] = ((m and m.actionArg) and m.actionArg or nil)
	savestates.actionState[slot] = ((m and m.actionState) and m.actionState or nil)
	savestates.actionTimer[slot] = ((m and m.actionTimer) and m.actionTimer or nil)
	savestates.angleVel_x[slot] = ((m and m.angleVel and m.angleVel.x) and m.angleVel.x or nil)
	savestates.angleVel_y[slot] = ((m and m.angleVel and m.angleVel.y) and m.angleVel.y or nil)
	savestates.angleVel_z[slot] = ((m and m.angleVel and m.angleVel.z) and m.angleVel.z or nil)
	savestates.animation_targetAnim[slot] = ((m and m.animation and m.animation.targetAnim) and m.animation.targetAnim or nil)
	savestates.area_camera[slot] = ((m and m.area and m.area.camera) and m.area.camera or nil)
	savestates.area_flags[slot] = ((m and m.area and m.area.flags) and m.area.flags or nil)
	savestates.area_index[slot] = ((m and m.area and m.area.index) and m.area.index or nil)
	savestates.area_instantWarps[slot] = ((m and m.area and m.area.instantWarps) and m.area.instantWarps or nil)
	savestates.area_musicParam[slot] = ((m and m.area and m.area.musicParam) and m.area.musicParam or nil)
	savestates.area_musicParam2[slot] = ((m and m.area and m.area.musicParam2) and m.area.musicParam2 or nil)
	savestates.area_numRedCoins[slot] = ((m and m.area and m.area.numRedCoins) and m.area.numRedCoins or nil)
	savestates.area_numSecrets[slot] = ((m and m.area and m.area.numSecrets) and m.area.numSecrets or nil)
	savestates.area_objectSpawnInfos_activeAreaIndex[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.activeAreaIndex) and m.area.objectSpawnInfos.activeAreaIndex or nil)
	savestates.area_objectSpawnInfos_areaIndex[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.areaIndex) and m.area.objectSpawnInfos.areaIndex or nil)
	savestates.area_objectSpawnInfos_behaviorArg[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.behaviorArg) and m.area.objectSpawnInfos.behaviorArg or nil)
	savestates.area_objectSpawnInfos_startAngle_x[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startAngle and m.area.objectSpawnInfos.startAngle.x) and m.area.objectSpawnInfos.startAngle.x or nil)
	savestates.area_objectSpawnInfos_startAngle_y[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startAngle and m.area.objectSpawnInfos.startAngle.y) and m.area.objectSpawnInfos.startAngle.y or nil)
	savestates.area_objectSpawnInfos_startAngle_z[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startAngle and m.area.objectSpawnInfos.startAngle.z) and m.area.objectSpawnInfos.startAngle.z or nil)
	savestates.area_objectSpawnInfos_startPos_x[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startPos and m.area.objectSpawnInfos.startPos.x) and m.area.objectSpawnInfos.startPos.x or nil)
	savestates.area_objectSpawnInfos_startPos_y[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startPos and m.area.objectSpawnInfos.startPos.y) and m.area.objectSpawnInfos.startPos.y or nil)
	savestates.area_objectSpawnInfos_startPos_z[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startPos and m.area.objectSpawnInfos.startPos.z) and m.area.objectSpawnInfos.startPos.z or nil)
	savestates.area_objectSpawnInfos_unk18_extraFlags[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.unk18 and m.area.objectSpawnInfos.unk18.extraFlags) and m.area.objectSpawnInfos.unk18.extraFlags or nil)
	savestates.area_objectSpawnInfos_unk18_flags[slot] = ((m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.unk18 and m.area.objectSpawnInfos.unk18.flags) and m.area.objectSpawnInfos.unk18.flags or nil)
	savestates.area_paintingWarpNodes_destArea[slot] = ((m and m.area and m.area.paintingWarpNodes and m.area.paintingWarpNodes.destArea) and m.area.paintingWarpNodes.destArea or nil)
	savestates.area_paintingWarpNodes_destLevel[slot] = ((m and m.area and m.area.paintingWarpNodes and m.area.paintingWarpNodes.destLevel) and m.area.paintingWarpNodes.destLevel or nil)
	savestates.area_paintingWarpNodes_destNode[slot] = ((m and m.area and m.area.paintingWarpNodes and m.area.paintingWarpNodes.destNode) and m.area.paintingWarpNodes.destNode or nil)
	savestates.area_paintingWarpNodes_id[slot] = ((m and m.area and m.area.paintingWarpNodes and m.area.paintingWarpNodes.id) and m.area.paintingWarpNodes.id or nil)
	savestates.area_terrainType[slot] = ((m and m.area and m.area.terrainType) and m.area.terrainType or nil)
	savestates.area_warpNodes_next[slot] = ((m and m.area and m.area.warpNodes and m.area.warpNodes.next) and m.area.warpNodes.next or nil)
	savestates.area_warpNodes_node_destArea[slot] = ((m and m.area and m.area.warpNodes and m.area.warpNodes.node and m.area.warpNodes.node.destArea) and m.area.warpNodes.node.destArea or nil)
	savestates.area_warpNodes_node_destLevel[slot] = ((m and m.area and m.area.warpNodes and m.area.warpNodes.node and m.area.warpNodes.node.destLevel) and m.area.warpNodes.node.destLevel or nil)
	savestates.area_warpNodes_node_destNode[slot] = ((m and m.area and m.area.warpNodes and m.area.warpNodes.node and m.area.warpNodes.node.destNode) and m.area.warpNodes.node.destNode or nil)
	savestates.area_warpNodes_node_id[slot] = ((m and m.area and m.area.warpNodes and m.area.warpNodes.node and m.area.warpNodes.node.id) and m.area.warpNodes.node.id or nil)
	savestates.area_warpNodes_object[slot] = ((m and m.area and m.area.warpNodes and m.area.warpNodes.object) and m.area.warpNodes.object or nil)
	savestates.bounceSquishTimer[slot] = ((m and m.bounceSquishTimer) and m.bounceSquishTimer or nil)
	savestates.bubbleObj[slot] = ((m and m.bubbleObj) and m.bubbleObj or nil)
	savestates.cap[slot] = ((m and m.cap) and m.cap or nil)
	savestates.capTimer[slot] = ((m and m.capTimer) and m.capTimer or nil)
	savestates.ceil[slot] = ((m and m.ceil) and m.ceil or nil)
	savestates.ceilHeight[slot] = ((m and m.ceilHeight) and m.ceilHeight or nil)
	savestates.character[slot] = ((m and m.character) and m.character or nil)
	savestates.collidedObjInteractTypes[slot] = ((m and m.collidedObjInteractTypes) and m.collidedObjInteractTypes or nil)
	savestates.controller_buttonDown[slot] = ((m and m.controller and m.controller.buttonDown) and m.controller.buttonDown or nil)
	savestates.controller_buttonPressed[slot] = ((m and m.controller and m.controller.buttonPressed) and m.controller.buttonPressed or nil)
	savestates.controller_extStickX[slot] = ((m and m.controller and m.controller.extStickX) and m.controller.extStickX or nil)
	savestates.controller_extStickY[slot] = ((m and m.controller and m.controller.extStickY) and m.controller.extStickY or nil)
	savestates.controller_port[slot] = ((m and m.controller and m.controller.port) and m.controller.port or nil)
	savestates.controller_rawStickX[slot] = ((m and m.controller and m.controller.rawStickX) and m.controller.rawStickX or nil)
	savestates.controller_rawStickY[slot] = ((m and m.controller and m.controller.rawStickY) and m.controller.rawStickY or nil)
	savestates.controller_stickMag[slot] = ((m and m.controller and m.controller.stickMag) and m.controller.stickMag or nil)
	savestates.controller_stickX[slot] = ((m and m.controller and m.controller.stickX) and m.controller.stickX or nil)
	savestates.controller_stickY[slot] = ((m and m.controller and m.controller.stickY) and m.controller.stickY or nil)
	savestates.curAnimOffset[slot] = ((m and m.curAnimOffset) and m.curAnimOffset or nil)
	savestates.currentRoom[slot] = ((m and m.currentRoom) and m.currentRoom or nil)
	savestates.doubleJumpTimer[slot] = ((m and m.doubleJumpTimer) and m.doubleJumpTimer or nil)
	savestates.faceAngle_x[slot] = ((m and m.faceAngle and m.faceAngle.x) and m.faceAngle.x or nil)
	savestates.faceAngle_y[slot] = ((m and m.faceAngle and m.faceAngle.y) and m.faceAngle.y or nil)
	savestates.faceAngle_z[slot] = ((m and m.faceAngle and m.faceAngle.z) and m.faceAngle.z or nil)
	savestates.fadeWarpOpacity[slot] = ((m and m.fadeWarpOpacity) and m.fadeWarpOpacity or nil)
	savestates.flags[slot] = ((m and m.flags) and m.flags or nil)
	savestates.floor[slot] = ((m and m.floor) and m.floor or nil)
	savestates.floorAngle[slot] = ((m and m.floorAngle) and m.floorAngle or nil)
	savestates.floorHeight[slot] = ((m and m.floorHeight) and m.floorHeight or nil)
	savestates.forwardVel[slot] = ((m and m.forwardVel) and m.forwardVel or nil)
	savestates.framesSinceA[slot] = ((m and m.framesSinceA) and m.framesSinceA or nil)
	savestates.framesSinceB[slot] = ((m and m.framesSinceB) and m.framesSinceB or nil)
	savestates.freeze[slot] = ((m and m.freeze) and m.freeze or nil)
	savestates.healCounter[slot] = ((m and m.healCounter) and m.healCounter or nil)
	savestates.health[slot] = ((m and m.health) and m.health or nil)
	savestates.heldByObj[slot] = ((m and m.heldByObj) and m.heldByObj or nil)
	savestates.heldObj[slot] = ((m and m.heldObj) and m.heldObj or nil)
	savestates.hurtCounter[slot] = ((m and m.hurtCounter) and m.hurtCounter or nil)
	savestates.input[slot] = ((m and m.input) and m.input or nil)
	savestates.intendedMag[slot] = ((m and m.intendedMag) and m.intendedMag or nil)
	savestates.intendedYaw[slot] = ((m and m.intendedYaw) and m.intendedYaw or nil)
	savestates.interactObj[slot] = ((m and m.interactObj) and m.interactObj or nil)
	savestates.invincTimer[slot] = ((m and m.invincTimer) and m.invincTimer or nil)
	savestates.isSnoring[slot] = ((m and m.isSnoring) and m.isSnoring or nil)
	savestates.knockbackTimer[slot] = ((m and m.knockbackTimer) and m.knockbackTimer or nil)
	savestates.marioBodyState_action[slot] = ((m and m.marioBodyState and m.marioBodyState.action) and m.marioBodyState.action or nil)
	savestates.marioBodyState_capState[slot] = ((m and m.marioBodyState and m.marioBodyState.capState) and m.marioBodyState.capState or nil)
	savestates.marioBodyState_eyeState[slot] = ((m and m.marioBodyState and m.marioBodyState.eyeState) and m.marioBodyState.eyeState or nil)
	savestates.marioBodyState_grabPos[slot] = ((m and m.marioBodyState and m.marioBodyState.grabPos) and m.marioBodyState.grabPos or nil)
	savestates.marioBodyState_handState[slot] = ((m and m.marioBodyState and m.marioBodyState.handState) and m.marioBodyState.handState or nil)
	savestates.marioBodyState_headAngle_x[slot] = ((m and m.marioBodyState and m.marioBodyState.headAngle and m.marioBodyState.headAngle.x) and m.marioBodyState.headAngle.x or nil)
	savestates.marioBodyState_headAngle_y[slot] = ((m and m.marioBodyState and m.marioBodyState.headAngle and m.marioBodyState.headAngle.y) and m.marioBodyState.headAngle.y or nil)
	savestates.marioBodyState_headAngle_z[slot] = ((m and m.marioBodyState and m.marioBodyState.headAngle and m.marioBodyState.headAngle.z) and m.marioBodyState.headAngle.z or nil)
	savestates.marioBodyState_headPos_x[slot] = ((m and m.marioBodyState and m.marioBodyState.headPos and m.marioBodyState.headPos.x) and m.marioBodyState.headPos.x or nil)
	savestates.marioBodyState_headPos_y[slot] = ((m and m.marioBodyState and m.marioBodyState.headPos and m.marioBodyState.headPos.y) and m.marioBodyState.headPos.y or nil)
	savestates.marioBodyState_headPos_z[slot] = ((m and m.marioBodyState and m.marioBodyState.headPos and m.marioBodyState.headPos.z) and m.marioBodyState.headPos.z or nil)
	savestates.marioBodyState_heldObjLastPosition_x[slot] = ((m and m.marioBodyState and m.marioBodyState.heldObjLastPosition and m.marioBodyState.heldObjLastPosition.x) and m.marioBodyState.heldObjLastPosition.x or nil)
	savestates.marioBodyState_heldObjLastPosition_y[slot] = ((m and m.marioBodyState and m.marioBodyState.heldObjLastPosition and m.marioBodyState.heldObjLastPosition.y) and m.marioBodyState.heldObjLastPosition.y or nil)
	savestates.marioBodyState_heldObjLastPosition_z[slot] = ((m and m.marioBodyState and m.marioBodyState.heldObjLastPosition and m.marioBodyState.heldObjLastPosition.z) and m.marioBodyState.heldObjLastPosition.z or nil)
	savestates.marioBodyState_modelState[slot] = ((m and m.marioBodyState and m.marioBodyState.modelState) and m.marioBodyState.modelState or nil)
	savestates.marioBodyState_punchState[slot] = ((m and m.marioBodyState and m.marioBodyState.punchState) and m.marioBodyState.punchState or nil)
	savestates.marioBodyState_torsoAngle_x[slot] = ((m and m.marioBodyState and m.marioBodyState.torsoAngle and m.marioBodyState.torsoAngle.x) and m.marioBodyState.torsoAngle.x or nil)
	savestates.marioBodyState_torsoAngle_y[slot] = ((m and m.marioBodyState and m.marioBodyState.torsoAngle and m.marioBodyState.torsoAngle.y) and m.marioBodyState.torsoAngle.y or nil)
	savestates.marioBodyState_torsoAngle_z[slot] = ((m and m.marioBodyState and m.marioBodyState.torsoAngle and m.marioBodyState.torsoAngle.z) and m.marioBodyState.torsoAngle.z or nil)
	savestates.marioBodyState_torsoPos_x[slot] = ((m and m.marioBodyState and m.marioBodyState.torsoPos and m.marioBodyState.torsoPos.x) and m.marioBodyState.torsoPos.x or nil)
	savestates.marioBodyState_torsoPos_y[slot] = ((m and m.marioBodyState and m.marioBodyState.torsoPos and m.marioBodyState.torsoPos.y) and m.marioBodyState.torsoPos.y or nil)
	savestates.marioBodyState_torsoPos_z[slot] = ((m and m.marioBodyState and m.marioBodyState.torsoPos and m.marioBodyState.torsoPos.z) and m.marioBodyState.torsoPos.z or nil)
	savestates.marioBodyState_wingFlutter[slot] = ((m and m.marioBodyState and m.marioBodyState.wingFlutter) and m.marioBodyState.wingFlutter or nil)
	savestates.marioObj_activeFlags[slot] = ((m and m.marioObj and m.marioObj.activeFlags) and m.marioObj.activeFlags or nil)
	savestates.marioObj_areaTimer[slot] = ((m and m.marioObj and m.marioObj.areaTimer) and m.marioObj.areaTimer or nil)
	savestates.marioObj_areaTimerDuration[slot] = ((m and m.marioObj and m.marioObj.areaTimerDuration) and m.marioObj.areaTimerDuration or nil)
	savestates.marioObj_areaTimerType[slot] = ((m and m.marioObj and m.marioObj.areaTimerType) and m.marioObj.areaTimerType or nil)
	savestates.marioObj_bhvDelayTimer[slot] = ((m and m.marioObj and m.marioObj.bhvDelayTimer) and m.marioObj.bhvDelayTimer or nil)
	savestates.marioObj_collidedObjInteractTypes[slot] = ((m and m.marioObj and m.marioObj.collidedObjInteractTypes) and m.marioObj.collidedObjInteractTypes or nil)
	savestates.marioObj_collisionData[slot] = ((m and m.marioObj and m.marioObj.collisionData) and m.marioObj.collisionData or nil)
	savestates.marioObj_ctx[slot] = ((m and m.marioObj and m.marioObj.ctx) and m.marioObj.ctx or nil)
	savestates.marioObj_globalPlayerIndex[slot] = ((m and m.marioObj and m.marioObj.globalPlayerIndex) and m.marioObj.globalPlayerIndex or nil)
	savestates.marioObj_header_gfx_activeAreaIndex[slot] = ((m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.activeAreaIndex) and m.marioObj.header.gfx.activeAreaIndex or nil)
	savestates.marioObj_header_gfx_areaIndex[slot] = ((m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.areaIndex) and m.marioObj.header.gfx.areaIndex or nil)
	savestates.marioObj_header_gfx_disableAutomaticShadowPos[slot] = ((m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.disableAutomaticShadowPos) and m.marioObj.header.gfx.disableAutomaticShadowPos or nil)
	savestates.marioObj_header_gfx_shadowInvisible[slot] = ((m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.shadowInvisible) and m.marioObj.header.gfx.shadowInvisible or nil)
	savestates.marioObj_header_gfx_skipInViewCheck[slot] = ((m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.skipInViewCheck) and m.marioObj.header.gfx.skipInViewCheck or nil)
	savestates.marioObj_heldByPlayerIndex[slot] = ((m and m.marioObj and m.marioObj.heldByPlayerIndex) and m.marioObj.heldByPlayerIndex or nil)
	savestates.marioObj_hitboxDownOffset[slot] = ((m and m.marioObj and m.marioObj.hitboxDownOffset) and m.marioObj.hitboxDownOffset or nil)
	savestates.marioObj_hitboxHeight[slot] = ((m and m.marioObj and m.marioObj.hitboxHeight) and m.marioObj.hitboxHeight or nil)
	savestates.marioObj_hitboxRadius[slot] = ((m and m.marioObj and m.marioObj.hitboxRadius) and m.marioObj.hitboxRadius or nil)
	savestates.marioObj_hookRender[slot] = ((m and m.marioObj and m.marioObj.hookRender) and m.marioObj.hookRender or nil)
	savestates.marioObj_hurtboxHeight[slot] = ((m and m.marioObj and m.marioObj.hurtboxHeight) and m.marioObj.hurtboxHeight or nil)
	savestates.marioObj_hurtboxRadius[slot] = ((m and m.marioObj and m.marioObj.hurtboxRadius) and m.marioObj.hurtboxRadius or nil)
	savestates.marioObj_parentObj[slot] = ((m and m.marioObj and m.marioObj.parentObj) and m.marioObj.parentObj or nil)
	savestates.marioObj_platform[slot] = ((m and m.marioObj and m.marioObj.platform) and m.marioObj.platform or nil)
	savestates.marioObj_prevObj[slot] = ((m and m.marioObj and m.marioObj.prevObj) and m.marioObj.prevObj or nil)
	savestates.marioObj_setHome[slot] = ((m and m.marioObj and m.marioObj.setHome) and m.marioObj.setHome or nil)
	savestates.marioObj_unused1[slot] = ((m and m.marioObj and m.marioObj.unused1) and m.marioObj.unused1 or nil)
	savestates.marioObj_usingObj[slot] = ((m and m.marioObj and m.marioObj.usingObj) and m.marioObj.usingObj or nil)
	savestates.minimumBoneY[slot] = ((m and m.minimumBoneY) and m.minimumBoneY or nil)
	savestates.nonInstantWarpPos_x[slot] = ((m and m.nonInstantWarpPos and m.nonInstantWarpPos.x) and m.nonInstantWarpPos.x or nil)
	savestates.nonInstantWarpPos_y[slot] = ((m and m.nonInstantWarpPos and m.nonInstantWarpPos.y) and m.nonInstantWarpPos.y or nil)
	savestates.nonInstantWarpPos_z[slot] = ((m and m.nonInstantWarpPos and m.nonInstantWarpPos.z) and m.nonInstantWarpPos.z or nil)
	savestates.numCoins[slot] = ((m and m.numCoins) and m.numCoins or nil)
	savestates.numKeys[slot] = ((m and m.numKeys) and m.numKeys or nil)
	savestates.numLives[slot] = ((m and m.numLives) and m.numLives or nil)
	savestates.numStars[slot] = ((m and m.numStars) and m.numStars or nil)
	savestates.particleFlags[slot] = ((m and m.particleFlags) and m.particleFlags or nil)
	savestates.peakHeight[slot] = ((m and m.peakHeight) and m.peakHeight or nil)
	savestates.pos_x[slot] = ((m and m.pos and m.pos.x) and m.pos.x or nil)
	savestates.pos_y[slot] = ((m and m.pos and m.pos.y) and m.pos.y or nil)
	savestates.pos_z[slot] = ((m and m.pos and m.pos.z) and m.pos.z or nil)
	savestates.prevAction[slot] = ((m and m.prevAction) and m.prevAction or nil)
	savestates.prevNumStarsForDialog[slot] = ((m and m.prevNumStarsForDialog) and m.prevNumStarsForDialog or nil)
	savestates.quicksandDepth[slot] = ((m and m.quicksandDepth) and m.quicksandDepth or nil)
	savestates.riddenObj[slot] = ((m and m.riddenObj) and m.riddenObj or nil)
	savestates.slideVelX[slot] = ((m and m.slideVelX) and m.slideVelX or nil)
	savestates.slideVelZ[slot] = ((m and m.slideVelZ) and m.slideVelZ or nil)
	savestates.slideYaw[slot] = ((m and m.slideYaw) and m.slideYaw or nil)
	savestates.spawnInfo[slot] = ((m and m.spawnInfo) and m.spawnInfo or nil)
	savestates.specialTripleJump[slot] = ((m and m.specialTripleJump) and m.specialTripleJump or nil)
	savestates.splineKeyframe[slot] = ((m and m.splineKeyframe) and m.splineKeyframe or nil)
	savestates.splineKeyframeFraction[slot] = ((m and m.splineKeyframeFraction) and m.splineKeyframeFraction or nil)
	savestates.splineState[slot] = ((m and m.splineState) and m.splineState or nil)
	savestates.squishTimer[slot] = ((m and m.squishTimer) and m.squishTimer or nil)
	savestates.statusForCamera_action[slot] = ((m and m.statusForCamera and m.statusForCamera.action) and m.statusForCamera.action or nil)
	savestates.statusForCamera_cameraEvent[slot] = ((m and m.statusForCamera and m.statusForCamera.cameraEvent) and m.statusForCamera.cameraEvent or nil)
	savestates.statusForCamera_faceAngle_x[slot] = ((m and m.statusForCamera and m.statusForCamera.faceAngle and m.statusForCamera.faceAngle.x) and m.statusForCamera.faceAngle.x or nil)
	savestates.statusForCamera_faceAngle_y[slot] = ((m and m.statusForCamera and m.statusForCamera.faceAngle and m.statusForCamera.faceAngle.y) and m.statusForCamera.faceAngle.y or nil)
	savestates.statusForCamera_faceAngle_z[slot] = ((m and m.statusForCamera and m.statusForCamera.faceAngle and m.statusForCamera.faceAngle.z) and m.statusForCamera.faceAngle.z or nil)
	savestates.statusForCamera_headRotation_x[slot] = ((m and m.statusForCamera and m.statusForCamera.headRotation and m.statusForCamera.headRotation.x) and m.statusForCamera.headRotation.x or nil)
	savestates.statusForCamera_headRotation_y[slot] = ((m and m.statusForCamera and m.statusForCamera.headRotation and m.statusForCamera.headRotation.y) and m.statusForCamera.headRotation.y or nil)
	savestates.statusForCamera_headRotation_z[slot] = ((m and m.statusForCamera and m.statusForCamera.headRotation and m.statusForCamera.headRotation.z) and m.statusForCamera.headRotation.z or nil)
	savestates.statusForCamera_pos_x[slot] = ((m and m.statusForCamera and m.statusForCamera.pos and m.statusForCamera.pos.x) and m.statusForCamera.pos.x or nil)
	savestates.statusForCamera_pos_y[slot] = ((m and m.statusForCamera and m.statusForCamera.pos and m.statusForCamera.pos.y) and m.statusForCamera.pos.y or nil)
	savestates.statusForCamera_pos_z[slot] = ((m and m.statusForCamera and m.statusForCamera.pos and m.statusForCamera.pos.z) and m.statusForCamera.pos.z or nil)
	savestates.statusForCamera_unused[slot] = ((m and m.statusForCamera and m.statusForCamera.unused) and m.statusForCamera.unused or nil)
	savestates.statusForCamera_usedObj[slot] = ((m and m.statusForCamera and m.statusForCamera.usedObj) and m.statusForCamera.usedObj or nil)
	savestates.terrainSoundAddend[slot] = ((m and m.terrainSoundAddend) and m.terrainSoundAddend or nil)
	savestates.twirlYaw[slot] = ((m and m.twirlYaw) and m.twirlYaw or nil)
	savestates.unkB0[slot] = ((m and m.unkB0) and m.unkB0 or nil)
	savestates.unkC4[slot] = ((m and m.unkC4) and m.unkC4 or nil)
	savestates.usedObj[slot] = ((m and m.usedObj) and m.usedObj or nil)
	savestates.vel_x[slot] = ((m and m.vel and m.vel.x) and m.vel.x or nil)
	savestates.vel_y[slot] = ((m and m.vel and m.vel.y) and m.vel.y or nil)
	savestates.vel_z[slot] = ((m and m.vel and m.vel.z) and m.vel.z or nil)
	savestates.wall[slot] = ((m and m.wall) and m.wall or nil)
	savestates.wallKickTimer[slot] = ((m and m.wallKickTimer) and m.wallKickTimer or nil)
	savestates.wallNormal_x[slot] = ((m and m.wallNormal and m.wallNormal.x) and m.wallNormal.x or nil)
	savestates.wallNormal_y[slot] = ((m and m.wallNormal and m.wallNormal.y) and m.wallNormal.y or nil)
	savestates.wallNormal_z[slot] = ((m and m.wallNormal and m.wallNormal.z) and m.wallNormal.z or nil)
	savestates.wasNetworkVisible[slot] = ((m and m.wasNetworkVisible) and m.wasNetworkVisible or nil)
	savestates.waterLevel[slot] = ((m and m.waterLevel) and m.waterLevel or nil)
    latest_savestate = slot
    m.particleFlags = PARTICLE_SPARKLES
    play_sound(SOUND_GENERAL_GRAND_STAR, m.marioObj.header.gfx.cameraToObject)
    djui_popup_create(color .. "State saved to Slot " .. tostring(latest_savestate + 1) .. "!", 1)
    return true
end

function load_state_slot(m, slot)
	ready_to_load = nil
    if (is_state_slot_not_empty(slot)) then
	    if (savestates.gNetworkPlayers_currLevelNum[slot] ~= gNetworkPlayers[0].currLevelNum or savestates.gNetworkPlayers_currAreaIndex[slot] ~= gNetworkPlayers[0].currAreaIndex or savestates.gNetworkPlayers_currActNum[slot] ~= gNetworkPlayers[0].currActNum) then
			warp_to_level(savestates.gNetworkPlayers_currLevelNum[slot], savestates.gNetworkPlayers_currAreaIndex[slot], savestates.gNetworkPlayers_currActNum[slot])
			wait_until_inited = slot
			return false
		else
			if (m and m.action) then m.action = savestates.action[slot] end
			if (m and m.actionArg) then m.actionArg = savestates.actionArg[slot] end
			if (m and m.actionState) then m.actionState = savestates.actionState[slot] end
			if (m and m.actionTimer) then m.actionTimer = savestates.actionTimer[slot] end
			if (m and m.angleVel and m.angleVel.x) then m.angleVel.x = savestates.angleVel_x[slot] end
			if (m and m.angleVel and m.angleVel.y) then m.angleVel.y = savestates.angleVel_y[slot] end
			if (m and m.angleVel and m.angleVel.z) then m.angleVel.z = savestates.angleVel_z[slot] end
			if (m and m.animation and m.animation.targetAnim) then m.animation.targetAnim = savestates.animation_targetAnim[slot] end
			if (m and m.area and m.area.camera) then m.area.camera = savestates.area_camera[slot] end
			if (m and m.area and m.area.flags) then m.area.flags = savestates.area_flags[slot] end
			if (m and m.area and m.area.index) then m.area.index = savestates.area_index[slot] end
			if (m and m.area and m.area.instantWarps) then m.area.instantWarps = savestates.area_instantWarps[slot] end
			if (m and m.area and m.area.musicParam) then m.area.musicParam = savestates.area_musicParam[slot] end
			if (m and m.area and m.area.musicParam2) then m.area.musicParam2 = savestates.area_musicParam2[slot] end
			--if (m and m.area and m.area.numRedCoins) then m.area.numRedCoins = savestates.area_numRedCoins[slot] end
			--if (m and m.area and m.area.numSecrets) then m.area.numSecrets = savestates.area_numSecrets[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.activeAreaIndex) then m.area.objectSpawnInfos.activeAreaIndex = savestates.area_objectSpawnInfos_activeAreaIndex[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.areaIndex) then m.area.objectSpawnInfos.areaIndex = savestates.area_objectSpawnInfos_areaIndex[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.behaviorArg) then m.area.objectSpawnInfos.behaviorArg = savestates.area_objectSpawnInfos_behaviorArg[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startAngle and m.area.objectSpawnInfos.startAngle.x) then m.area.objectSpawnInfos.startAngle.x = savestates.area_objectSpawnInfos_startAngle_x[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startAngle and m.area.objectSpawnInfos.startAngle.y) then m.area.objectSpawnInfos.startAngle.y = savestates.area_objectSpawnInfos_startAngle_y[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startAngle and m.area.objectSpawnInfos.startAngle.z) then m.area.objectSpawnInfos.startAngle.z = savestates.area_objectSpawnInfos_startAngle_z[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startPos and m.area.objectSpawnInfos.startPos.x) then m.area.objectSpawnInfos.startPos.x = savestates.area_objectSpawnInfos_startPos_x[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startPos and m.area.objectSpawnInfos.startPos.y) then m.area.objectSpawnInfos.startPos.y = savestates.area_objectSpawnInfos_startPos_y[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.startPos and m.area.objectSpawnInfos.startPos.z) then m.area.objectSpawnInfos.startPos.z = savestates.area_objectSpawnInfos_startPos_z[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.unk18 and m.area.objectSpawnInfos.unk18.extraFlags) then m.area.objectSpawnInfos.unk18.extraFlags = savestates.area_objectSpawnInfos_unk18_extraFlags[slot] end
			if (m and m.area and m.area.objectSpawnInfos and m.area.objectSpawnInfos.unk18 and m.area.objectSpawnInfos.unk18.flags) then m.area.objectSpawnInfos.unk18.flags = savestates.area_objectSpawnInfos_unk18_flags[slot] end
			--if (m and m.area and m.area.paintingWarpNodes and m.area.paintingWarpNodes.destArea) then m.area.paintingWarpNodes.destArea = savestates.area_paintingWarpNodes_destArea[slot] end
			--if (m and m.area and m.area.paintingWarpNodes and m.area.paintingWarpNodes.destLevel) then m.area.paintingWarpNodes.destLevel = savestates.area_paintingWarpNodes_destLevel[slot] end
			--if (m and m.area and m.area.paintingWarpNodes and m.area.paintingWarpNodes.destNode) then m.area.paintingWarpNodes.destNode = savestates.area_paintingWarpNodes_destNode[slot] end
			--if (m and m.area and m.area.paintingWarpNodes and m.area.paintingWarpNodes.id) then m.area.paintingWarpNodes.id = savestates.area_paintingWarpNodes_id[slot] end
			if (m and m.area and m.area.terrainType) then m.area.terrainType = savestates.area_terrainType[slot] end
			--if (m and m.area and m.area.warpNodes and m.area.warpNodes.next) then m.area.warpNodes.next = savestates.area_warpNodes_next[slot] end
			--if (m and m.area and m.area.warpNodes and m.area.warpNodes.node and m.area.warpNodes.node.destArea) then m.area.warpNodes.node.destArea = savestates.area_warpNodes_node_destArea[slot] end
			--if (m and m.area and m.area.warpNodes and m.area.warpNodes.node and m.area.warpNodes.node.destLevel) then m.area.warpNodes.node.destLevel = savestates.area_warpNodes_node_destLevel[slot] end
			--if (m and m.area and m.area.warpNodes and m.area.warpNodes.node and m.area.warpNodes.node.destNode) then m.area.warpNodes.node.destNode = savestates.area_warpNodes_node_destNode[slot] end
			--if (m and m.area and m.area.warpNodes and m.area.warpNodes.node and m.area.warpNodes.node.id) then m.area.warpNodes.node.id = savestates.area_warpNodes_node_id[slot] end
			--if (m and m.area and m.area.warpNodes and m.area.warpNodes.object) then m.area.warpNodes.object = savestates.area_warpNodes_object[slot] end
			if (m and m.bounceSquishTimer) then m.bounceSquishTimer = savestates.bounceSquishTimer[slot] end
			if (m and m.bubbleObj) then m.bubbleObj = savestates.bubbleObj[slot] end
			if (m and m.cap) then m.cap = savestates.cap[slot] end
			if (m and m.capTimer) then m.capTimer = savestates.capTimer[slot] end
			if (m and m.ceil) then m.ceil = savestates.ceil[slot] end
			if (m and m.ceilHeight) then m.ceilHeight = savestates.ceilHeight[slot] end
			if (m and m.character) then m.character = savestates.character[slot] end
			if (m and m.collidedObjInteractTypes) then m.collidedObjInteractTypes = savestates.collidedObjInteractTypes[slot] end
			--if (m and m.controller and m.controller.buttonDown) then m.controller.buttonDown = savestates.controller_buttonDown[slot] end
			--if (m and m.controller and m.controller.buttonPressed) then m.controller.buttonPressed = savestates.controller_buttonPressed[slot] end
			--if (m and m.controller and m.controller.extStickX) then m.controller.extStickX = savestates.controller_extStickX[slot] end
			--if (m and m.controller and m.controller.extStickY) then m.controller.extStickY = savestates.controller_extStickY[slot] end
			--if (m and m.controller and m.controller.port) then m.controller.port = savestates.controller_port[slot] end
			--if (m and m.controller and m.controller.rawStickX) then m.controller.rawStickX = savestates.controller_rawStickX[slot] end
			--if (m and m.controller and m.controller.rawStickY) then m.controller.rawStickY = savestates.controller_rawStickY[slot] end
			--if (m and m.controller and m.controller.stickMag) then m.controller.stickMag = savestates.controller_stickMag[slot] end
			--if (m and m.controller and m.controller.stickX) then m.controller.stickX = savestates.controller_stickX[slot] end
			--if (m and m.controller and m.controller.stickY) then m.controller.stickY = savestates.controller_stickY[slot] end
			if (m and m.curAnimOffset) then m.curAnimOffset = savestates.curAnimOffset[slot] end
			if (m and m.currentRoom) then m.currentRoom = savestates.currentRoom[slot] end
			if (m and m.doubleJumpTimer) then m.doubleJumpTimer = savestates.doubleJumpTimer[slot] end
			if (m and m.faceAngle and m.faceAngle.x) then m.faceAngle.x = savestates.faceAngle_x[slot] end
			if (m and m.faceAngle and m.faceAngle.y) then m.faceAngle.y = savestates.faceAngle_y[slot] end
			if (m and m.faceAngle and m.faceAngle.z) then m.faceAngle.z = savestates.faceAngle_z[slot] end
			if (m and m.fadeWarpOpacity) then m.fadeWarpOpacity = savestates.fadeWarpOpacity[slot] end
			if (m and m.flags) then m.flags = savestates.flags[slot] end
			if (m and m.floor) then m.floor = savestates.floor[slot] end
			if (m and m.floorAngle) then m.floorAngle = savestates.floorAngle[slot] end
			if (m and m.floorHeight) then m.floorHeight = savestates.floorHeight[slot] end
			if (m and m.forwardVel) then m.forwardVel = savestates.forwardVel[slot] end
			if (m and m.framesSinceA) then m.framesSinceA = savestates.framesSinceA[slot] end
			if (m and m.framesSinceB) then m.framesSinceB = savestates.framesSinceB[slot] end
			if (m and m.freeze) then m.freeze = savestates.freeze[slot] end
			if (m and m.healCounter) then m.healCounter = savestates.healCounter[slot] end
			if (m and m.health) then m.health = (autoheal_enabled and 0x880 or savestates.health[slot]) end
			if (m and m.heldByObj) then m.heldByObj = savestates.heldByObj[slot] end
			if (m and m.heldObj) then m.heldObj = savestates.heldObj[slot] end
			if (m and m.hurtCounter) then m.hurtCounter = savestates.hurtCounter[slot] end
			if (m and m.input) then m.input = savestates.input[slot] end
			if (m and m.intendedMag) then m.intendedMag = savestates.intendedMag[slot] end
			if (m and m.intendedYaw) then m.intendedYaw = savestates.intendedYaw[slot] end
			if (m and m.interactObj) then m.interactObj = savestates.interactObj[slot] end
			if (m and m.invincTimer) then m.invincTimer = savestates.invincTimer[slot] end
			if (m and m.isSnoring) then m.isSnoring = savestates.isSnoring[slot] end
			if (m and m.knockbackTimer) then m.knockbackTimer = savestates.knockbackTimer[slot] end
			if (m and m.marioBodyState and m.marioBodyState.action) then m.marioBodyState.action = savestates.marioBodyState_action[slot] end
			if (m and m.marioBodyState and m.marioBodyState.capState) then m.marioBodyState.capState = savestates.marioBodyState_capState[slot] end
			if (m and m.marioBodyState and m.marioBodyState.eyeState) then m.marioBodyState.eyeState = savestates.marioBodyState_eyeState[slot] end
			if (m and m.marioBodyState and m.marioBodyState.grabPos) then m.marioBodyState.grabPos = savestates.marioBodyState_grabPos[slot] end
			if (m and m.marioBodyState and m.marioBodyState.handState) then m.marioBodyState.handState = savestates.marioBodyState_handState[slot] end
			if (m and m.marioBodyState and m.marioBodyState.headAngle and m.marioBodyState.headAngle.x) then m.marioBodyState.headAngle.x = savestates.marioBodyState_headAngle_x[slot] end
			if (m and m.marioBodyState and m.marioBodyState.headAngle and m.marioBodyState.headAngle.y) then m.marioBodyState.headAngle.y = savestates.marioBodyState_headAngle_y[slot] end
			if (m and m.marioBodyState and m.marioBodyState.headAngle and m.marioBodyState.headAngle.z) then m.marioBodyState.headAngle.z = savestates.marioBodyState_headAngle_z[slot] end
			if (m and m.marioBodyState and m.marioBodyState.headPos and m.marioBodyState.headPos.x) then m.marioBodyState.headPos.x = savestates.marioBodyState_headPos_x[slot] end
			if (m and m.marioBodyState and m.marioBodyState.headPos and m.marioBodyState.headPos.y) then m.marioBodyState.headPos.y = savestates.marioBodyState_headPos_y[slot] end
			if (m and m.marioBodyState and m.marioBodyState.headPos and m.marioBodyState.headPos.z) then m.marioBodyState.headPos.z = savestates.marioBodyState_headPos_z[slot] end
			if (m and m.marioBodyState and m.marioBodyState.heldObjLastPosition and m.marioBodyState.heldObjLastPosition.x) then m.marioBodyState.heldObjLastPosition.x = savestates.marioBodyState_heldObjLastPosition_x[slot] end
			if (m and m.marioBodyState and m.marioBodyState.heldObjLastPosition and m.marioBodyState.heldObjLastPosition.y) then m.marioBodyState.heldObjLastPosition.y = savestates.marioBodyState_heldObjLastPosition_y[slot] end
			if (m and m.marioBodyState and m.marioBodyState.heldObjLastPosition and m.marioBodyState.heldObjLastPosition.z) then m.marioBodyState.heldObjLastPosition.z = savestates.marioBodyState_heldObjLastPosition_z[slot] end
			if (m and m.marioBodyState and m.marioBodyState.modelState) then m.marioBodyState.modelState = savestates.marioBodyState_modelState[slot] end
			if (m and m.marioBodyState and m.marioBodyState.punchState) then m.marioBodyState.punchState = savestates.marioBodyState_punchState[slot] end
			if (m and m.marioBodyState and m.marioBodyState.torsoAngle and m.marioBodyState.torsoAngle.x) then m.marioBodyState.torsoAngle.x = savestates.marioBodyState_torsoAngle_x[slot] end
			if (m and m.marioBodyState and m.marioBodyState.torsoAngle and m.marioBodyState.torsoAngle.y) then m.marioBodyState.torsoAngle.y = savestates.marioBodyState_torsoAngle_y[slot] end
			if (m and m.marioBodyState and m.marioBodyState.torsoAngle and m.marioBodyState.torsoAngle.z) then m.marioBodyState.torsoAngle.z = savestates.marioBodyState_torsoAngle_z[slot] end
			if (m and m.marioBodyState and m.marioBodyState.torsoPos and m.marioBodyState.torsoPos.x) then m.marioBodyState.torsoPos.x = savestates.marioBodyState_torsoPos_x[slot] end
			if (m and m.marioBodyState and m.marioBodyState.torsoPos and m.marioBodyState.torsoPos.y) then m.marioBodyState.torsoPos.y = savestates.marioBodyState_torsoPos_y[slot] end
			if (m and m.marioBodyState and m.marioBodyState.torsoPos and m.marioBodyState.torsoPos.z) then m.marioBodyState.torsoPos.z = savestates.marioBodyState_torsoPos_z[slot] end
			if (m and m.marioBodyState and m.marioBodyState.wingFlutter) then m.marioBodyState.wingFlutter = savestates.marioBodyState_wingFlutter[slot] end
			if (m and m.marioObj and m.marioObj.activeFlags) then m.marioObj.activeFlags = savestates.marioObj_activeFlags[slot] end
			if (m and m.marioObj and m.marioObj.areaTimer) then m.marioObj.areaTimer = savestates.marioObj_areaTimer[slot] end
			if (m and m.marioObj and m.marioObj.areaTimerDuration) then m.marioObj.areaTimerDuration = savestates.marioObj_areaTimerDuration[slot] end
			if (m and m.marioObj and m.marioObj.areaTimerType) then m.marioObj.areaTimerType = savestates.marioObj_areaTimerType[slot] end
			if (m and m.marioObj and m.marioObj.bhvDelayTimer) then m.marioObj.bhvDelayTimer = savestates.marioObj_bhvDelayTimer[slot] end
			if (m and m.marioObj and m.marioObj.collidedObjInteractTypes) then m.marioObj.collidedObjInteractTypes = savestates.marioObj_collidedObjInteractTypes[slot] end
			if (m and m.marioObj and m.marioObj.collisionData) then m.marioObj.collisionData = savestates.marioObj_collisionData[slot] end
			if (m and m.marioObj and m.marioObj.ctx) then m.marioObj.ctx = savestates.marioObj_ctx[slot] end
			if (m and m.marioObj and m.marioObj.globalPlayerIndex) then m.marioObj.globalPlayerIndex = savestates.marioObj_globalPlayerIndex[slot] end
			if (m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.activeAreaIndex) then m.marioObj.header.gfx.activeAreaIndex = savestates.marioObj_header_gfx_activeAreaIndex[slot] end
			if (m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.areaIndex) then m.marioObj.header.gfx.areaIndex = savestates.marioObj_header_gfx_areaIndex[slot] end
			if (m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.disableAutomaticShadowPos) then m.marioObj.header.gfx.disableAutomaticShadowPos = savestates.marioObj_header_gfx_disableAutomaticShadowPos[slot] end
			if (m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.shadowInvisible) then m.marioObj.header.gfx.shadowInvisible = savestates.marioObj_header_gfx_shadowInvisible[slot] end
			if (m and m.marioObj and m.marioObj.header and m.marioObj.header.gfx and m.marioObj.header.gfx.skipInViewCheck) then m.marioObj.header.gfx.skipInViewCheck = savestates.marioObj_header_gfx_skipInViewCheck[slot] end
			if (m and m.marioObj and m.marioObj.heldByPlayerIndex) then m.marioObj.heldByPlayerIndex = savestates.marioObj_heldByPlayerIndex[slot] end
			if (m and m.marioObj and m.marioObj.hitboxDownOffset) then m.marioObj.hitboxDownOffset = savestates.marioObj_hitboxDownOffset[slot] end
			if (m and m.marioObj and m.marioObj.hitboxHeight) then m.marioObj.hitboxHeight = savestates.marioObj_hitboxHeight[slot] end
			if (m and m.marioObj and m.marioObj.hitboxRadius) then m.marioObj.hitboxRadius = savestates.marioObj_hitboxRadius[slot] end
			if (m and m.marioObj and m.marioObj.hookRender) then m.marioObj.hookRender = savestates.marioObj_hookRender[slot] end
			if (m and m.marioObj and m.marioObj.hurtboxHeight) then m.marioObj.hurtboxHeight = savestates.marioObj_hurtboxHeight[slot] end
			if (m and m.marioObj and m.marioObj.hurtboxRadius) then m.marioObj.hurtboxRadius = savestates.marioObj_hurtboxRadius[slot] end
			if (m and m.marioObj and m.marioObj.parentObj) then m.marioObj.parentObj = savestates.marioObj_parentObj[slot] end
			if (m and m.marioObj and m.marioObj.platform) then m.marioObj.platform = savestates.marioObj_platform[slot] end
			if (m and m.marioObj and m.marioObj.prevObj) then m.marioObj.prevObj = savestates.marioObj_prevObj[slot] end
			if (m and m.marioObj and m.marioObj.setHome) then m.marioObj.setHome = savestates.marioObj_setHome[slot] end
			if (m and m.marioObj and m.marioObj.unused1) then m.marioObj.unused1 = savestates.marioObj_unused1[slot] end
			if (m and m.marioObj and m.marioObj.usingObj) then m.marioObj.usingObj = savestates.marioObj_usingObj[slot] end
			if (m and m.minimumBoneY) then m.minimumBoneY = savestates.minimumBoneY[slot] end
			if (m and m.nonInstantWarpPos and m.nonInstantWarpPos.x) then m.nonInstantWarpPos.x = savestates.nonInstantWarpPos_x[slot] end
			if (m and m.nonInstantWarpPos and m.nonInstantWarpPos.y) then m.nonInstantWarpPos.y = savestates.nonInstantWarpPos_y[slot] end
			if (m and m.nonInstantWarpPos and m.nonInstantWarpPos.z) then m.nonInstantWarpPos.z = savestates.nonInstantWarpPos_z[slot] end
			--if (m and m.numCoins) then m.numCoins = savestates.numCoins[slot] end
			--if (m and m.numKeys) then m.numKeys = savestates.numKeys[slot] end
			if (m and m.numLives) then m.numLives = savestates.numLives[slot] end
			--if (m and m.numStars) then m.numStars = savestates.numStars[slot] end
			if (m and m.particleFlags) then m.particleFlags = savestates.particleFlags[slot] end
			if (m and m.peakHeight) then m.peakHeight = savestates.peakHeight[slot] end
			if (m and m.pos and m.pos.x) then m.pos.x = savestates.pos_x[slot] end
			if (m and m.pos and m.pos.y) then m.pos.y = savestates.pos_y[slot] end
			if (m and m.pos and m.pos.z) then m.pos.z = savestates.pos_z[slot] end
			if (m and m.prevAction) then m.prevAction = savestates.prevAction[slot] end
			if (m and m.prevNumStarsForDialog) then m.prevNumStarsForDialog = savestates.prevNumStarsForDialog[slot] end
			if (m and m.quicksandDepth) then m.quicksandDepth = savestates.quicksandDepth[slot] end
			if (m and m.riddenObj) then m.riddenObj = savestates.riddenObj[slot] end
			if (m and m.slideVelX) then m.slideVelX = savestates.slideVelX[slot] end
			if (m and m.slideVelZ) then m.slideVelZ = savestates.slideVelZ[slot] end
			if (m and m.slideYaw) then m.slideYaw = savestates.slideYaw[slot] end
			if (m and m.spawnInfo) then m.spawnInfo = savestates.spawnInfo[slot] end
			if (m and m.specialTripleJump) then m.specialTripleJump = savestates.specialTripleJump[slot] end
			if (m and m.splineKeyframe) then m.splineKeyframe = savestates.splineKeyframe[slot] end
			if (m and m.splineKeyframeFraction) then m.splineKeyframeFraction = savestates.splineKeyframeFraction[slot] end
			if (m and m.splineState) then m.splineState = savestates.splineState[slot] end
			if (m and m.squishTimer) then m.squishTimer = savestates.squishTimer[slot] end
			if (m and m.statusForCamera and m.statusForCamera.action) then m.statusForCamera.action = savestates.statusForCamera_action[slot] end
			if (m and m.statusForCamera and m.statusForCamera.cameraEvent) then m.statusForCamera.cameraEvent = savestates.statusForCamera_cameraEvent[slot] end
			if (m and m.statusForCamera and m.statusForCamera.faceAngle and m.statusForCamera.faceAngle.x) then m.statusForCamera.faceAngle.x = savestates.statusForCamera_faceAngle_x[slot] end
			if (m and m.statusForCamera and m.statusForCamera.faceAngle and m.statusForCamera.faceAngle.y) then m.statusForCamera.faceAngle.y = savestates.statusForCamera_faceAngle_y[slot] end
			if (m and m.statusForCamera and m.statusForCamera.faceAngle and m.statusForCamera.faceAngle.z) then m.statusForCamera.faceAngle.z = savestates.statusForCamera_faceAngle_z[slot] end
			if (m and m.statusForCamera and m.statusForCamera.headRotation and m.statusForCamera.headRotation.x) then m.statusForCamera.headRotation.x = savestates.statusForCamera_headRotation_x[slot] end
			if (m and m.statusForCamera and m.statusForCamera.headRotation and m.statusForCamera.headRotation.y) then m.statusForCamera.headRotation.y = savestates.statusForCamera_headRotation_y[slot] end
			if (m and m.statusForCamera and m.statusForCamera.headRotation and m.statusForCamera.headRotation.z) then m.statusForCamera.headRotation.z = savestates.statusForCamera_headRotation_z[slot] end
			if (m and m.statusForCamera and m.statusForCamera.pos and m.statusForCamera.pos.x) then m.statusForCamera.pos.x = savestates.statusForCamera_pos_x[slot] end
			if (m and m.statusForCamera and m.statusForCamera.pos and m.statusForCamera.pos.y) then m.statusForCamera.pos.y = savestates.statusForCamera_pos_y[slot] end
			if (m and m.statusForCamera and m.statusForCamera.pos and m.statusForCamera.pos.z) then m.statusForCamera.pos.z = savestates.statusForCamera_pos_z[slot] end
			if (m and m.statusForCamera and m.statusForCamera.unused) then m.statusForCamera.unused = savestates.statusForCamera_unused[slot] end
			if (m and m.statusForCamera and m.statusForCamera.usedObj) then m.statusForCamera.usedObj = savestates.statusForCamera_usedObj[slot] end
			if (m and m.terrainSoundAddend) then m.terrainSoundAddend = savestates.terrainSoundAddend[slot] end
			if (m and m.twirlYaw) then m.twirlYaw = savestates.twirlYaw[slot] end
			if (m and m.unkB0) then m.unkB0 = savestates.unkB0[slot] end
			if (m and m.unkC4) then m.unkC4 = savestates.unkC4[slot] end
			if (m and m.usedObj) then m.usedObj = savestates.usedObj[slot] end
			if (m and m.vel and m.vel.x) then m.vel.x = savestates.vel_x[slot] end
			if (m and m.vel and m.vel.y) then m.vel.y = savestates.vel_y[slot] end
			if (m and m.vel and m.vel.z) then m.vel.z = savestates.vel_z[slot] end
			if (m and m.wall) then m.wall = savestates.wall[slot] end
			if (m and m.wallKickTimer) then m.wallKickTimer = savestates.wallKickTimer[slot] end
			if (m and m.wallNormal and m.wallNormal.x) then m.wallNormal.x = savestates.wallNormal_x[slot] end
			if (m and m.wallNormal and m.wallNormal.y) then m.wallNormal.y = savestates.wallNormal_y[slot] end
			if (m and m.wallNormal and m.wallNormal.z) then m.wallNormal.z = savestates.wallNormal_z[slot] end
			if (m and m.wasNetworkVisible) then m.wasNetworkVisible = savestates.wasNetworkVisible[slot] end
			if (m and m.waterLevel) then m.waterLevel = savestates.waterLevel[slot] end
			latest_savestate = slot
			m.particleFlags = PARTICLE_HORIZONTAL_STAR
			play_sound(SOUND_GENERAL_GRAND_STAR_JUMP, m.marioObj.header.gfx.cameraToObject)
			if slot == 0 then
				djui_popup_create("\\#ffa0a0\\State loaded from Slot 1!",1)
			elseif slot == 1 then
				djui_popup_create("\\#a0ffa0\\State loaded from Slot 2!",1)
			elseif slot == 2 then
				djui_popup_create("\\#a0a0ff\\State loaded from Slot 3!",1)
			elseif slot == 3 then
				djui_popup_create("\\#ffffa0\\State loaded from Slot 4!",1)
			end
			return true
		end
    else
		play_sound(SOUND_GENERAL_FLAME_OUT, m.marioObj.header.gfx.cameraToObject)
		if slot == 0 then
			djui_popup_create("\\#a0a0a0\\No State found in Slot 1!",1)
		elseif slot == 1 then
			djui_popup_create("\\#a0a0a0\\No State found in Slot 2!",1)
		elseif slot == 2 then
			djui_popup_create("\\#a0a0a0\\No State found in Slot 3!",1)
		elseif slot == 3 then
			djui_popup_create("\\#a0a0a0\\No State found in Slot 4!",1)
		end
        return false
    end
end

function delete_state_slot(m, slot)
    savestates.pos_x[slot] = nil
    savestates.pos_y[slot] = nil
    savestates.pos_z[slot] = nil
end

function is_state_slot_not_empty(slot) 
	return ((savestates.pos_x[slot] ~= nil and savestates.pos_y[slot] ~= nil and savestates.pos_z[slot] ~= nil) and true or false)
end

function on_cmd_autoload()
    if (autoload_enabled == true) then
        autoload_enabled = false
        djui_chat_message_create("\\#ff8080\\AutoLoad latest savestate on death is now \\#ff0000\\DISABLED")
    else
        autoload_enabled = true
        djui_chat_message_create("\\#80ff80\\AutoLoad latest savestate on death is now \\#00ff00\\ENABLED")
    end
    return true
end

function on_cmd_autoheal()
    if (autoheal_enabled == true) then
        autoheal_enabled = false
        djui_chat_message_create("\\#ff8080\\AutoHeal after loading savestate is now \\#ff0000\\DISABLED")
    else
        autoheal_enabled = true
        djui_chat_message_create("\\#80ff80\\AutoHeal after loading savestate is now \\#00ff00\\ENABLED")
    end
    return true
end

function on_cmd_savestate()
    djui_chat_message_create("\\#40b0ff\\[\\#40ffff\\LOCAL SAVESTATE-MOD SLOTS AND SETTINGS INFOS\\#40b0ff\\]")
    djui_chat_message_create("\\#b0b0b0\\AutoLoad\\#808080\\: " .. (autoload_enabled and "\\#80ff80\\ON" or "\\#ff8080\\OFF") .. " " .. (is_state_slot_not_empty(latest_savestate) and ("\\#ffff80\\(Latest: Slot " .. tostring(latest_savestate + 1) .. ")") or ("\\#ff8040\\(Latest: MissingNo)")) .. "    " .. "\\#b0b0b0\\AutoHeal\\#808080\\: " .. (autoheal_enabled and "\\#80ff80\\ON" or "\\#ff8080\\OFF"))
    djui_chat_message_create("\\#b0b0b0\\Save-Slot 1\\#808080\\: " .. (is_state_slot_not_empty(0) and "\\#80ff80\\SET" or "\\#ff8080\\EMPTY") .. "    " .. "\\#b0b0b0\\Save-Slot 2\\#808080\\: " .. (is_state_slot_not_empty(1) and "\\#80ff80\\SET" or "\\#ff8080\\EMPTY"))
    djui_chat_message_create("\\#b0b0b0\\Save-Slot 3\\#808080\\: " .. (is_state_slot_not_empty(2) and "\\#80ff80\\SET" or "\\#ff8080\\EMPTY") .. "    " .. "\\#b0b0b0\\Save-Slot 4\\#808080\\: " .. (is_state_slot_not_empty(3) and "\\#80ff80\\SET" or "\\#ff8080\\EMPTY"))
    return true
end

hook_event(HOOK_ON_PLAYER_CONNECTED, on_join)
hook_event(HOOK_ON_PLAYER_DISCONNECTED, on_leave)
hook_event(HOOK_ON_DEATH, on_death)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_MARIO_UPDATE, on_mario_update)

hook_chat_command("autoload", "Automatically load the latest savestate on death!", on_cmd_autoload)
hook_chat_command("al", "Automatically load the latest savestate on death!", on_cmd_autoload)

hook_chat_command("autoheal", "Automatically heal mario after loading a savestates!", on_cmd_autoheal)
hook_chat_command("ah", "Automatically heal mario after loading a savestates!", on_cmd_autoheal)

hook_chat_command("savestate", "List infos about your local savestates and settings!", on_cmd_savestate)
hook_chat_command("savestates", "List infos about your local savestates and settings!", on_cmd_savestate)
hook_chat_command("ss", "List infos about your local savestates and settings!", on_cmd_savestate)