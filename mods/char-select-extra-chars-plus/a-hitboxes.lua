local colObjLists = { OBJ_LIST_GENACTOR, OBJ_LIST_PUSHABLE, OBJ_LIST_SURFACE, OBJ_LIST_DESTRUCTIVE }

local bhvBlacklist = {
    [id_bhvBowser] = true,
    [id_bhvDoor] = true,
    [id_bhvDoorWarp] = true,
    [id_bhvStarDoor] = true,
    [id_bhvUnlockDoorStar] = true,
    [id_bhvToadMessage] = true,
    [id_bhvFireSpitter] = true,
    [id_bhvExplosion] = true
}

---@param o Object
---@param o2 Object
local function attack_bounce(o, o2)
    o2.oVelY = 15.0
    play_sound(SOUND_ACTION_BONK, o2.header.gfx.cameraToObject)
end

---@param o Object
---@param o2 Object
local function attack_bully(o, o2)
    o2.oBullyLastNetworkPlayerIndex = o.globalPlayerIndex
    o2.oMoveAngleYaw = o.oMoveAngleYaw
    o2.oForwardVel = 30.0

    o2.oInteractStatus = o2.oInteractStatus | ATTACK_FAST_ATTACK | INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED
end

---@param o Object
---@param o2 Object
local function attack_bully_strong(o, o2)
    o2.oBullyLastNetworkPlayerIndex = o.globalPlayerIndex
    o2.oMoveAngleYaw = o.oMoveAngleYaw
    o2.oForwardVel = 50.0
    o2.oVelY = 30.0

    o2.oInteractStatus = o2.oInteractStatus | ATTACK_FAST_ATTACK | INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED
end

---@param o Object
---@param o2 Object
local function attack_mrblizzard(o, o2)
    if o2.prevObj then
        o2.prevObj.oAction = 2
        o2.prevObj = nil
        o2.oMrBlizzardHeldObj = nil
    end
    o2.oAction = MR_BLIZZARD_ACT_DEATH
end

---@param o Object
---@param o2 Object
local function attack_bullet_bill(o, o2)
    spawn_mist_particles_with_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION)
    o2.oAction = 4
    o2.oTimer = 0
end

---@param o Object
---@param o2 Object
local function attack_chuckya(o, o2)
    o2.oAction = 2
    o2.oVelY = 30
    o2.oMoveAngleYaw = o.oMoveAngleYaw
    o2.oForwardVel = 25
end

---@param o Object
---@param o2 Object
local function attack_whomp(o, o2)
    o2.oAction = 8
end

---@param o Object
---@param o2 Object
local function attack_kingbobomb(o, o2)
    if o2.oFlags & OBJ_FLAG_HOLDABLE ~= 0 and o2.oAction ~= 8 then
        o2.oVelY = 30
        o2.oForwardVel = 30
        o2.oMoveAngleYaw = o.oMoveAngleYaw
        o2.oMoveFlags = 0
        o2.oAction = 4
    end
end

---@param o Object
---@param o2 Object
local function attack_wooden_post(o, o2)
    o2.oWoodenPostMarioPounding = 1
    o2.oWoodenPostSpeedY = -100.0
    cur_obj_play_sound_2(SOUND_GENERAL_POUND_WOOD_POST)
end

-- lists for edge case interactions

bhvWapeachAxeAttacks = {
    [id_bhvSmallBully] = attack_bully_strong,
    [id_bhvBigBully] = attack_bully_strong,
    [id_bhvBigBullyWithMinions] = attack_bully_strong,
    [id_bhvSmallChillBully] = attack_bully_strong,
    [id_bhvBigChillBully] = attack_bully_strong,
    [id_bhvMrBlizzard] = attack_mrblizzard,
    [id_bhvBulletBill] = attack_bullet_bill,
    [id_bhvSmallWhomp] = attack_whomp,
    [id_bhvChuckya] = attack_chuckya,
    [id_bhvWoodenPost] = attack_wooden_post,
}

---@param o Object
---@param spAttacksList table<BehaviorId,function>
---@param getTarget? boolean
function obj_process_attacks(o, spAttacksList, getTarget)
    -- players
    if o.oInteractType == 0 then
        local m = nearest_mario_state_to_object(o)
        if m and m.playerIndex == 0 and m.marioObj.globalPlayerIndex ~= o.globalPlayerIndex
            and m.action & (ACT_FLAG_INVULNERABLE | ACT_FLAG_INTANGIBLE) == 0 and m.invincTimer == 0
            and obj_check_hitbox_overlap(m.marioObj, o) then
            if spAttacksList[id_bhvMario] then
                spAttacksList[id_bhvMario](o, m)
            else
                take_damage_and_knock_back(m, o)
            end
            if getTarget then return m.marioObj end
        end
    end
    -- other objects
    for i, list in ipairs(colObjLists) do
        local o2 = obj_get_first(list)
        while o2 do
            if o ~= o2 and o2.oInteractStatus & INT_STATUS_INTERACTED == 0 and o2.oIntangibleTimer == 0 and obj_check_hitbox_overlap(o, o2) then
                local bhv = get_id_from_behavior(o2.behavior)
                if not bhvBlacklist[bhv] then
                    if spAttacksList[bhv] then
                        spAttacksList[bhv](o, o2)
                    else
                        o2.oInteractStatus = o2.oInteractStatus | ATTACK_FAST_ATTACK | INT_STATUS_WAS_ATTACKED |
                            INT_STATUS_INTERACTED
                    end
                    if getTarget then return o2 end
                end
            end
            o2 = obj_get_next(o2)
        end
    end
end