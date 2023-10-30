if unsupported then return end

local MARIO_HEAD_POS = 120

local sPlayerFirstPerson = {
    pos = { x = 0, y = 0, z = 0 },
    freecam = camera_config_is_free_cam_enabled(),
    pitch = 0,
    yaw = 0,
    fov = 70
}

-- localize functions to improve performance - spectator.lua
local camera_config_get_x_sensitivity,camera_config_get_y_sensitivity,camera_config_is_x_inverted,camera_config_is_y_inverted,is_game_paused,djui_hud_get_raw_mouse_y,clamp,djui_hud_get_raw_mouse_x,vec3f_copy,mario_drop_held_object,set_mario_animation,vec3f_set,vec3f_mul,djui_hud_set_mouse_locked,camera_freeze,maxf,camera_config_is_free_cam_enabled,set_override_near,set_override_fov,camera_unfreeze,camera_config_is_mouse_look_enabled,allocate_mario_action = camera_config_get_x_sensitivity,camera_config_get_y_sensitivity,camera_config_is_x_inverted,camera_config_is_y_inverted,is_game_paused,djui_hud_get_raw_mouse_y,clamp,djui_hud_get_raw_mouse_x,vec3f_copy,mario_drop_held_object,set_mario_animation,vec3f_set,vec3f_mul,djui_hud_set_mouse_locked,camera_freeze,maxf,camera_config_is_free_cam_enabled,set_override_near,set_override_fov,camera_unfreeze,camera_config_is_mouse_look_enabled,allocate_mario_action

--- @param m MarioState
local function update_fp_camera(m)
    gLakituState.mode = CAMERA_MODE_FREE_ROAM
    gLakituState.defMode = CAMERA_MODE_FREE_ROAM

    local sensX = 0.3 * camera_config_get_x_sensitivity()
    local sensY = 0.4 * camera_config_get_y_sensitivity()
    local invX = if_then_else(camera_config_is_x_inverted(), 1, -1)
    local invY = if_then_else(camera_config_is_y_inverted(), 1, -1)

    if not is_game_paused() then
        -- update pitch
        sPlayerFirstPerson.pitch = sPlayerFirstPerson.pitch - sensY * (invY * m.controller.extStickY - 1.5 * djui_hud_get_raw_mouse_y())
        sPlayerFirstPerson.pitch = clamp(sPlayerFirstPerson.pitch, -0x3F00, 0x3F00)

        -- update yaw
        if (m.controller.buttonPressed & L_TRIG) ~= 0 then
            sPlayerFirstPerson.yaw = m.faceAngle.y + 0x8000
        else
            sPlayerFirstPerson.yaw = sPlayerFirstPerson.yaw + sensX * (invX * m.controller.extStickX - 1.5 * djui_hud_get_raw_mouse_x())
        end
        sPlayerFirstPerson.yaw = (sPlayerFirstPerson.yaw + 0x10000) % 0x10000
    end

    gLakituState.yaw = sPlayerFirstPerson.yaw
    m.area.camera.yaw = sPlayerFirstPerson.yaw

    -- update pos
    gLakituState.pos.x = sPlayerFirstPerson.pos.x + coss(sPlayerFirstPerson.pitch) * sins(sPlayerFirstPerson.yaw)
    gLakituState.pos.y = sPlayerFirstPerson.pos.y + sins(sPlayerFirstPerson.pitch) + MARIO_HEAD_POS
    gLakituState.pos.z = sPlayerFirstPerson.pos.z + coss(sPlayerFirstPerson.pitch) * coss(sPlayerFirstPerson.yaw)
    vec3f_copy(m.area.camera.pos, gLakituState.pos)
    vec3f_copy(gLakituState.curPos, gLakituState.pos)
    vec3f_copy(gLakituState.goalPos, gLakituState.pos)

    -- update focus
    gLakituState.focus.x = sPlayerFirstPerson.pos.x - 100 * coss(sPlayerFirstPerson.pitch) * sins(sPlayerFirstPerson.yaw)
    gLakituState.focus.y = sPlayerFirstPerson.pos.y - 100 * sins(sPlayerFirstPerson.pitch) + MARIO_HEAD_POS
    gLakituState.focus.z = sPlayerFirstPerson.pos.z - 100 * coss(sPlayerFirstPerson.pitch) * coss(sPlayerFirstPerson.yaw)
    vec3f_copy(m.area.camera.focus, gLakituState.focus)
    vec3f_copy(gLakituState.curFocus, gLakituState.focus)
    vec3f_copy(gLakituState.goalFocus, gLakituState.focus)

    -- set other values
    gLakituState.posHSpeed = 0
    gLakituState.posVSpeed = 0
    gLakituState.focHSpeed = 0
    gLakituState.focVSpeed = 0
end

--- @param m MarioState
function set_mario_spectator(m)
    if m.action ~= ACT_SPECTATOR then
        sPlayerFirstPerson.pos = { x = m.pos.x, y = if_then_else(m.health > 0xff, m.pos.y, gGlobalSyncTable.waterLevel), z = m.pos.z }
    end
    m.action = ACT_SPECTATOR
end

--- @param m MarioState
local function act_spectator(m)
    mario_drop_held_object(m)
    m.squishTimer = 0

    set_mario_animation(m, MARIO_ANIM_DROWNING_PART2)
    m.marioBodyState.eyeState = MARIO_EYES_DEAD
    m.faceAngle.x = 0
    m.faceAngle.z = 0

    if gPlayerSyncTable[m.playerIndex].finished then
        m.marioObj.header.gfx.node.flags = m.marioObj.header.gfx.node.flags & ~GRAPH_RENDER_ACTIVE
        local goalPos = gLevels[gGlobalSyncTable.level].goalPos
        vec3f_set(m.pos, goalPos.x, goalPos.y + 600, goalPos.z)
        mario_set_full_health(m)
    else
        m.pos.y = gGlobalSyncTable.waterLevel - 70
        vec3f_copy(m.marioObj.header.gfx.pos, m.pos)
        vec3f_copy(m.marioObj.header.gfx.angle, m.faceAngle)
        m.marioObj.header.gfx.angle.y = 0
        m.health = 0xff
        m.healCounter = 0
        m.hurtCounter = 0
    end

    if m.playerIndex ~= 0 then return end

    if not is_game_paused() then
        local forward = { x = sins(m.faceAngle.y), y = 0, z = coss(m.faceAngle.y) }
        local right = { x = sins(m.faceAngle.y - 0x4000), y = 0, z = coss(m.faceAngle.y - 0x4000) }
        local dir = { x = forward.x * m.controller.stickY + right.x * m.controller.stickX, y = 0, z = forward.z * m.controller.stickY + right.z * m.controller.stickX }
        local speed = if_then_else((m.controller.buttonDown & B_BUTTON) ~= 0, 2, 1)
        dir = vec3f_mul(dir, speed)

        sPlayerFirstPerson.pos.x = sPlayerFirstPerson.pos.x + dir.x
        sPlayerFirstPerson.pos.z = sPlayerFirstPerson.pos.z + dir.z

        if (m.input & INPUT_A_DOWN) ~= 0 then
            sPlayerFirstPerson.pos.y = sPlayerFirstPerson.pos.y + (50 * speed)
        end
        if (m.input & INPUT_Z_DOWN) ~= 0 then
            sPlayerFirstPerson.pos.y = sPlayerFirstPerson.pos.y - (50 * speed)
        end
    end

    m.faceAngle.y = m.area.camera.yaw + 0x8000

    djui_hud_set_mouse_locked(not is_game_paused())

    camera_freeze()
    update_fp_camera(m)
end

--- @param m MarioState
local function on_set_mario_action(m)
    if m.action == ACT_VERTICAL_WIND then
        m.vel.y = maxf(m.vel.y, 0)
    end

    if m.playerIndex ~= 0 then return end

    if m.action == ACT_SPECTATOR then
        sPlayerFirstPerson.freecam = camera_config_is_free_cam_enabled()
        camera_freeze()
        set_override_near(45)
        set_override_fov(sPlayerFirstPerson.fov)
        sPlayerFirstPerson.pitch = 0
        sPlayerFirstPerson.yaw = m.faceAngle.y + 0x8000
    else
        if sPlayerFirstPerson.freecam then
            gLakituState.mode = CAMERA_MODE_NEWCAM
            gLakituState.defMode = CAMERA_MODE_NEWCAM
        end
        camera_unfreeze()
        set_override_near(0)
        set_override_fov(0)
        sPlayerFirstPerson.pitch = 0
        sPlayerFirstPerson.yaw = 0
        if not camera_config_is_mouse_look_enabled() then
            djui_hud_set_mouse_locked(false)
        end
    end
end

ACT_SPECTATOR = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_INVULNERABLE)

hook_event(HOOK_ON_SET_MARIO_ACTION, on_set_mario_action)

---@diagnostic disable-next-line: missing-parameter
hook_mario_action(ACT_SPECTATOR, act_spectator)