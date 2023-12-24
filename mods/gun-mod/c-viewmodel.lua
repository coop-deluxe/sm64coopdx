if SM64COOPDX_VERSION == nil then return end

local CAP_FLICKER_FRAMES = 0x4444449249255555 -- this is beyond my comprehension

gFirstPersonViewmodels = {
    armObjs = { nil, nil },
    gunObjs = { nil, nil }
}

--- @param o Object
local function bhv_viewmodel_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oGraphYOffset = 0
end

--- @param o Object
local function bhv_viewmodel_loop(o)
    if not gGlobalSyncTable.gunModEnabled or not get_first_person_enabled() then
        obj_mark_for_deletion(o)
        return
    end

    local dualWield = obj_get_weapon_dual_wield(o) ~= 0
    --- @type Weapon
    local weapon = if_then_else(dualWield, cur_dual_wield_weapon(), cur_weapon())

    if not weapon.reqCheck(gMarioStates[0]) then
        cur_obj_hide()
    else
        cur_obj_unhide()
    end

    local horizontalOffset = 30
    if cur_dual_wield_weapon() ~= nil then
        horizontalOffset = if_then_else(obj_get_weapon_dual_wield(o) ~= 0, -50, 50)
    end

    -- math to calculate staying in the same screen position no matter what
    o.oPosX = gLakituState.pos.x - 35 * coss(gFirstPersonCamera.pitch) * sins(gFirstPersonCamera.yaw)
    o.oPosY = gLakituState.pos.y - 35 * sins(gFirstPersonCamera.pitch)
    o.oPosZ = gLakituState.pos.z - 35 * coss(gFirstPersonCamera.pitch) * coss(gFirstPersonCamera.yaw)

    -- math to offset it to the left or right
    o.oPosX = o.oPosX + sins(gFirstPersonCamera.yaw + 0x4000) * horizontalOffset
    o.oPosZ = o.oPosZ + coss(gFirstPersonCamera.yaw + 0x4000) * horizontalOffset

    o.oFaceAnglePitch = 0
    o.oFaceAngleYaw = gFirstPersonCamera.yaw + 0x4000
    o.oFaceAngleRoll = -gFirstPersonCamera.pitch

    if weapon ~= nil then
        if weapon.deployTimer > 0 then
            obj_set_animation(o, "arm_reload_end")
            -- freeze animation if the time hasn't come to show the arm rising up
            if o.header.gfx.animInfo.animFrame > 0 and weapon.deployTimer - o.header.gfx.animInfo.curAnim.loopEnd > 0 then
                o.header.gfx.animInfo.animFrame = 0
            end
        else
            local half = math.floor(weapon.reloadTime * 0.5)
            if weapon.reloadTimer <= 0 then
                if weapon.cooldownTimer > 0 then
                    obj_set_animation(o, "arm_shoot")
                else
                    obj_set_animation(o, "arm_idle")
                    -- *try* keep both arms in sync
                    if dualWield then
                        o.header.gfx.animInfo.animFrame = gFirstPersonViewmodels.armObjs[1].header.gfx.animInfo.animFrame
                    end
                end
            elseif weapon.reloadTimer < half then
                obj_set_animation(o, "arm_reload_end")
            else
                obj_set_animation(o, "arm_reload_start")
            end
        end
    end


    o.globalPlayerIndex = gNetworkPlayers[0].globalIndex

    --- @type MarioState
    local m = gMarioStates[0]
    if m.capTimer < 64 and ((1 << m.capTimer) & CAP_FLICKER_FRAMES) ~= 0 then
        o.oAnimState = 0
    else
        local vanishCap = if_then_else((gMarioStates[0].flags & MARIO_VANISH_CAP) ~= 0, 2, 0)
        local metalCap = if_then_else((gMarioStates[0].flags & MARIO_METAL_CAP) ~= 0, 1, 0)
        o.oAnimState = metalCap + vanishCap
    end
end

id_bhvViewmodel = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_viewmodel_init, bhv_viewmodel_loop, "bhvGmViewmodel")


--- @param weapon Weapon
local function spawn_viewmodel(weapon, dualWield)
    local index = if_then_else(dualWield, 1, 2)
    dualWield = if_then_else(dualWield, 1, 0)

    gFirstPersonViewmodels.armObjs[index] = spawn_non_sync_object(
        id_bhvViewmodel,
        weapon.armModel,
        0, -10000, 0,
        --- @param o Object
        function(o)
            obj_set_weapon_params(o, 0, 0, dualWield, 0)
        end
    )

    gFirstPersonViewmodels.gunObjs[index] = spawn_non_sync_object(
        id_bhvViewmodel,
        weapon.model,
        0, -10000, 0,
        --- @param o Object
        function(o)
            obj_set_weapon_params(o, 0, 0, dualWield, 0)
        end
    )
end

function spawn_viewmodels()
    local weapon1 = cur_weapon()
    local weapon2 = cur_dual_wield_weapon()
    if weapon1 == nil then return end

    spawn_viewmodel(weapon1, false)
    if weapon2 ~= nil then spawn_viewmodel(weapon2, true) end
end

function delete_viewmodels()
    gFirstPersonViewmodels.armObjs[1] = obj_mark_for_deletion(gFirstPersonViewmodels.armObjs[1])
    gFirstPersonViewmodels.armObjs[2] = obj_mark_for_deletion(gFirstPersonViewmodels.armObjs[2])
    gFirstPersonViewmodels.gunObjs[1] = obj_mark_for_deletion(gFirstPersonViewmodels.gunObjs[1])
    gFirstPersonViewmodels.gunObjs[2] = obj_mark_for_deletion(gFirstPersonViewmodels.gunObjs[2])
end