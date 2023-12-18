if SM64COOPDX_VERSION == nil then return end

---------------------------------------
-- API and other important functions --
---------------------------------------

--- @class Weapon
--- @field public id integer
--- @field public name string
--- @field public dualWield boolean
--- @field public model ModelExtendedId
--- @field public armModel ModelExtendedId
--- @field public bulletModel ModelExtendedId
--- @field public primarySounds integer[]
--- @field public secondarySounds integer[]
--- @field public strong boolean
--- @field public rapidFire boolean
--- @field public spread number
--- @field public damage number
--- @field public bulletCount integer
--- @field public bulletScale number
--- @field public bulletSpeed number
--- @field public bulletSteps integer
--- @field public maxAmmo integer
--- @field public ammo integer
--- @field public deployTime integer
--- @field public cooldownTime integer
--- @field public reloadTime integer
--- @field public deployTimer integer
--- @field public cooldownTimer integer
--- @field public reloadTimer integer
--- @field public primaryFireFunc fun(weapon:Weapon)
--- @field public secondaryFireFunc fun(weapon:Weapon)
--- @field public reqCheck fun(m:MarioState)

--- @class WeaponId

--- @type Weapon[]
gWeaponTable = {}
--- @type Weapon[]
gInventory = {}
for i = 1, MAX_INVENTORY_SLOTS do gInventory[i] = nil end
inventorySlot = 1
useDualWieldWeapon = false

local weaponObtained = false
local weaponId = -1

local sMutableWeaponFields = {
    ["ammo"] = true,
    ["deployTimer"] = true,
    ["cooldownTimer"] = true,
    ["reloadTimer"] = true
}

local sReadonlyMetatable = {
    __index = function(table, key)
        return rawget(table, key)
    end,

    __newindex = function()
        error("attempt to update a read-only table", 2)
    end
}

local sWeaponMetatable = {
    __index = function(table, key)
        return rawget(table, key)
    end,

    __newindex = function(table, key, value)
        if sMutableWeaponFields[key] then
            rawset(table, key, value)
        else
            error("attempt to update an immutable weapon field", 2)
        end
    end
}

--- @param name string
--- @param dualWield boolean
--- @param model ModelExtendedId
--- @param armModel ModelExtendedId
--- @param bulletModel ModelExtendedId
--- @param primarySounds integer[]
--- @param secondarySounds integer[]
--- @param strong boolean
--- @param rapidFire boolean
--- @param spread number
--- @param damage number
--- @param bulletCount integer
--- @param bulletScale number
--- @param bulletSpeed number
--- @param bulletSteps integer
--- @param maxAmmo integer
--- @param deployTime integer
--- @param cooldownTime integer
--- @param reloadTime integer
--- @param primaryFireFunc fun(weapon:Weapon)
--- @param secondaryFireFunc fun(weapon:Weapon)
--- @param reqCheck function
--- @return integer
--- Registers a weapon metatable into existence
function weapon_register(name, dualWield, model, armModel, bulletModel, primarySounds, secondarySounds, strong, rapidFire, spread, damage, bulletCount, bulletScale, bulletSpeed, bulletSteps, maxAmmo, deployTime, cooldownTime, reloadTime, primaryFireFunc, secondaryFireFunc, reqCheck)
    weaponId = weaponId + 1
    gWeaponTable[weaponId] = {
        id = weaponId,
        name = name,
        dualWield = dualWield,
        model = model,
        armModel = armModel,
        bulletModel = bulletModel,
        primarySounds = primarySounds,
        secondarySounds = secondarySounds,
        strong = strong,
        rapidFire = rapidFire,
        spread = spread,
        damage = damage,
        bulletCount = bulletCount,
        bulletScale = bulletScale,
        bulletSpeed = bulletSpeed,
        bulletSteps = bulletSteps,
        maxAmmo = maxAmmo,
        ammo = maxAmmo,
        deployTime = deployTime,
        cooldownTime = cooldownTime,
        reloadTime = reloadTime,
        deployTimer = deployTime,
        cooldownTimer = 0,
        reloadTimer = 0,
        primaryFireFunc = primaryFireFunc,
        secondaryFireFunc = secondaryFireFunc,
        reqCheck = reqCheck
    }
    setmetatable(gWeaponTable[weaponId], sReadonlyMetatable)
    return weaponId
end

--- @param id integer
--- @return nil
--- Unregisters a weapon from existence by ID
function weapon_unregister(id)
    if type(id) ~= "number" then return end
    gWeaponTable[id] = nil
end

--- @return nil
--- Unregisters all weapons from existence
function weapon_unregister_all()
    gWeaponTable = {}
end

--- @return string
--- Properly formatted weapon list string for commands
function get_weapon_list_string()
    local string = "["
    for id, weapon in pairs(gWeaponTable) do
        string = string .. weapon.name:lower()
        if id < weaponId then
            string = string .. "|"
        end
    end
    string = string .. "]"
    return string
end

--- @param obj Object
--- @param owner integer
--- @param id integer
--- @param dualWield integer
--- @param extra integer
--- @return nil
--- Returns a 4 byte behavior parameter integer for weapon objects.
function obj_set_weapon_params(obj, owner, id, dualWield, extra)
    if obj == nil then return end
    if type(owner) ~= "number" or type(id) ~= "number" or type(dualWield) ~= "number" or type(extra) ~= "number" then return end
    obj.oBehParams = owner | (id << 8) | (dualWield << 16) | (extra << 24)
    obj.oBehParams2ndByte = id
end

--- @param obj Object
--- @return integer
--- Returns the owner parameter (first parameter) of a weapon object.
function obj_get_weapon_owner(obj)
    if obj == nil then return 0 end
    return obj.oBehParams & 0xFF
end

--- @param obj Object
--- @return integer
--- Returns the id parameter (second parameter) of a weapon object.
function obj_get_weapon_id(obj)
    if obj == nil then return 0 end
    return obj.oBehParams2ndByte
end

--- @param obj Object
--- @return integer
--- Returns the dual wield parameter (third parameter) of a weapon object.
function obj_get_weapon_dual_wield(obj)
    if obj == nil then return 0 end
    return (obj.oBehParams >> 16) & 0xFF
end

--- @param obj Object
--- @return integer
--- Returns the extra parameter (fourth parameter) of a weapon object.
function obj_get_weapon_extra(obj)
    if obj == nil then return 0 end
    return (obj.oBehParams >> 24) & 0xFF
end

--- @return Weapon|nil
--- Returns the table of the current weapon
function cur_weapon()
    return gInventory[inventorySlot]
end

--- @return Weapon|nil
--- Returns the table of the current dual wielding weapon
function cur_dual_wield_weapon()
    local weapon = cur_weapon()
    if weapon == nil or not weapon.dualWield then return nil end

    local weaponBefore = gInventory[inventorySlot - 1]
    if weaponBefore ~= nil and weaponBefore.dualWield and weaponBefore.id == weapon.id then return weaponBefore end

    local weaponAfter = gInventory[inventorySlot + 1]
    if weaponAfter ~= nil and weaponAfter.dualWield and weaponAfter.id == weapon.id then return weaponAfter end

    return nil
end

--- @return integer
--- Returns the current inventory slot
function get_inventory_slot()
    return inventorySlot
end

--- @param slot integer
--- @return nil
--- Sets the current inventory slot
function set_inventory_slot(slot)
    if type(slot) ~= "number" then return end

    -- reset fields
    gInventory[slot].deployTimer = gInventory[slot].deployTime
    gInventory[slot].cooldownTimer = 0
    gInventory[slot].reloadTimer = if_then_else(gInventory[slot].ammo <= 0 and gInventory[slot].maxAmmo > 0, gInventory[slot].reloadTime, 0)

    inventorySlot = clamp(slot, 1, MAX_INVENTORY_SLOTS)
    sync_current_weapons()
    delete_held_weapon()
    if get_first_person_enabled() then
        delete_viewmodels()
        spawn_viewmodels()
    end
end

local function table_clone(table)
    local cloned = {}
    for k, v in pairs(table) do
        if type(v) == "table" then
            cloned[k] = table_clone(v)
        else
            cloned[k] = v
        end
    end
    return cloned
end

--- @param weapon WeaponId
local function inventory_clone(weapon)
    local table = table_clone(gWeaponTable[weapon])
    setmetatable(table, sWeaponMetatable)
    return table
end

local function get_inventory_slots_used()
    local count = 0
    for i = 1, MAX_INVENTORY_SLOTS do
        if gInventory[i] ~= nil then
            count = count + 1
        end
    end
    return count
end

--- @param weapon WeaponId
--- @return boolean
--- Picks up a weapon by ID
function pickup_weapon(weapon)
    if type(weapon) ~= "number" then return false end
    for i = 1, MAX_INVENTORY_SLOTS do
        if gInventory[i] == weapon then
            return false
        elseif gInventory[i] == nil or get_inventory_slots_used() == MAX_INVENTORY_SLOTS then
            if not weaponObtained then
                play_sound(SOUND_MENU_STAR_SOUND, gMarioStates[0].marioObj.header.gfx.cameraToObject)
                weaponObtained = true
            else
                play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gMarioStates[0].marioObj.header.gfx.cameraToObject)
            end

            gInventory[i] = inventory_clone(weapon)
            set_inventory_slot(i)

            return true
        end
    end

    return false
end

function sync_current_weapons()
    gPlayerSyncTable[0].curWeapon = nil
    gPlayerSyncTable[0].curWeapon2 = nil

    local weapon = cur_weapon()
    if weapon ~= nil then
        gPlayerSyncTable[0].curWeapon = weapon.id
    end
    local weapon2 = cur_dual_wield_weapon()
    if weapon2 ~= nil then
        gPlayerSyncTable[0].curWeapon2 = weapon2.id
    end
end

--- @param weapon Weapon
function handle_reloading(weapon)
    if weapon == nil then return end

    if weapon.reloadTimer > 0 then
        weapon.reloadTimer = weapon.reloadTimer - 1
        if weapon.name == "Shotgun" then
            weapon.ammo = math.floor(lerp(weapon.maxAmmo, 0, weapon.reloadTimer / weapon.reloadTime))
        end
        if weapon.reloadTimer == 0 then
            weapon.ammo = weapon.maxAmmo
        end
    end
end

function weapon_update()
    --- @type MarioState
    local m = gMarioStates[0]

    -- update inventory slot
    if (m.controller.buttonPressed & U_JPAD) ~= 0 then
        inventorySlot = inventorySlot + 1
        if inventorySlot > MAX_INVENTORY_SLOTS then
            inventorySlot = 1
        end
        set_inventory_slot(inventorySlot)
    elseif (m.controller.buttonPressed & D_JPAD) ~= 0 then
        inventorySlot = inventorySlot - 1
        if inventorySlot < 1 then
            inventorySlot = MAX_INVENTORY_SLOTS
        end
        set_inventory_slot(inventorySlot)
    end

    local weapon1 = cur_weapon()
    local weapon2 = cur_dual_wield_weapon()
    --- @type Weapon
    local weapon = if_then_else(weapon2 ~= nil and useDualWieldWeapon, weapon2, weapon1)
    if weapon1 == nil then return end -- if the player isn't holding a weapon

    if weapon.deployTimer <= 0 and weapon.cooldownTimer <= 0 then
        local buttonFlags = if_then_else(weapon.rapidFire, m.controller.buttonDown, m.controller.buttonPressed)
        if (buttonFlags & Y_BUTTON) ~= 0 and weapon.primaryFireFunc ~= nil then
            weapon.cooldownTimer = weapon.cooldownTime
            weapon.primaryFireFunc(weapon)
        elseif (buttonFlags & X_BUTTON) ~= 0 and weapon.secondaryFireFunc ~= nil then
            weapon.cooldownTimer = weapon.cooldownTime
            weapon.secondaryFireFunc(weapon)
        end
    end

    weapon1.deployTimer = handle_timer(weapon1.deployTimer)
    weapon1.cooldownTimer = handle_timer(weapon1.cooldownTimer)
    if weapon2 ~= nil then
        weapon2.deployTimer = handle_timer(weapon2.deployTimer)
        weapon2.cooldownTimer = handle_timer(weapon2.cooldownTimer)
    end
    handle_reloading(weapon1)
    handle_reloading(weapon2)
end

function delete_held_weapon()
    local held = obj_get_first_with_behavior_id(id_bhvHeldWeapon)
    while held ~= nil do
        if obj_get_weapon_owner(held) == gNetworkPlayers[0].globalIndex then
            obj_mark_for_deletion(held)
        end
        held = obj_get_next_with_same_behavior_id(held)
    end
end


-------------
-- objects --
-------------

--- @param o Object
local function bhv_held_weapon_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oGraphYOffset = 10
    cur_obj_scale(0.6)
    cur_obj_hide()
end

--- @param o Object
local function bhv_held_weapon_loop(o)
    local np = network_player_from_global_index(obj_get_weapon_owner(o))
    if np == nil or not gGlobalSyncTable.gunModEnabled then
        obj_mark_for_deletion(o)
        return
    end
    local m = gMarioStates[np.localIndex]
    local dualWield = obj_get_weapon_dual_wield(o)
    --- @type Weapon|nil
    local weapon = if_then_else(dualWield ~= 0, cur_dual_wield_weapon(), cur_weapon())
    if active_player(m) == 0 or weapon == nil then
        obj_mark_for_deletion(o)
        return
    end

    local index = if_then_else(dualWield ~= 0, 1, 0)
    if m.marioBodyState.updateTorsoTime == gMarioStates[0].marioBodyState.updateTorsoTime and m.marioBodyState.handState == MARIO_HAND_FISTS and weapon.reqCheck(m) then
        cur_obj_unhide()
        o.oPosX = get_hand_foot_pos_x(m, index) + m.vel.x - (sins(m.faceAngle.y) * 30)
        o.oPosY = get_hand_foot_pos_y(m, index) + m.vel.y + if_then_else(m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP, 20, 0)
        o.oPosZ = get_hand_foot_pos_z(m, index) + m.vel.z - (coss(m.faceAngle.y) * 30)
        o.oFaceAngleYaw = m.faceAngle.y - 0x4000
        o.oFaceAnglePitch = 0
        o.oFaceAngleRoll = 0
    else
        cur_obj_hide()
        o.oPosX = m.pos.x
        o.oPosY = m.pos.y + 60
        o.oPosZ = m.pos.z
    end

    if m.playerIndex == 0 and get_first_person_enabled() then
        cur_obj_hide()
    end

    obj_set_model_extended(o, weapon.model)
end

id_bhvHeldWeapon = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_held_weapon_init, bhv_held_weapon_loop, "bhvGmHeldWeapon")


--- @param o Object
local function bhv_pickup_weapon_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oIntangibleTimer = 0
    obj_scale(o, 0.75)

    o.hitboxRadius = 90
    o.hitboxHeight = 90

    network_init_object(o, true, {})
end

--- @param o Object
local function bhv_pickup_weapon_loop(o)
    cur_obj_update_floor_height()
    o.oPosY = o.oFloorHeight + 130

    o.oFaceAngleYaw = o.oFaceAngleYaw + 0x800

    local nearest = nearest_mario_state_to_object(o)
    if obj_check_hitbox_overlap(o, nearest.marioObj) and o.oIntangibleTimer == 0 and nearest.playerIndex == 0 then
        o.oIntangibleTimer = 450
        pickup_weapon(o.oBehParams)
    end

    if o.oIntangibleTimer ~= 0 then
        cur_obj_hide()
    else
        cur_obj_unhide()
        o.oGraphYOffset = math.sin(o.oTimer * 0.5) * 5
    end
end

id_bhvWeaponPickup = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_pickup_weapon_init, bhv_pickup_weapon_loop, "bhvGmWeaponPickup")


-------------
-- weapons --
-------------

WEAPON_PISTOL = weapon_register(
    "Pistol", -- name
    true, -- dual wieldable
    E_MODEL_PISTOL, -- weapon model
    E_MODEL_SINGLE_ARM, -- arm model
    E_MODEL_YELLOW_COIN, -- bullet model
    { sync_audio_sample_load("pistol_shoot.mp3") }, -- primary sounds
    { sync_audio_sample_load("pistol_reload.mp3") }, -- secondary sounds
    false, -- strong weapon
    false, -- rapid fire
    10, -- spread
    15, -- damage
    1, -- bullet count
    0.2, -- bullet scale
    500, -- bullet speed
    10, -- bullet steps
    18, -- max ammo
    15, -- deploy time
    5, -- cooldown time
    60, -- reload time
    common_shoot, -- primary fire
    common_reload, -- secondary fire
    check_common_gun_requirements -- requirement checks function
)

WEAPON_MAGNUM = weapon_register(
    "Magnum", -- name
    true, -- dual wieldable
    E_MODEL_MAGNUM, -- weapon model
    E_MODEL_SINGLE_ARM, -- arm model
    E_MODEL_METALLIC_BALL, -- bullet model
    { sync_audio_sample_load("magnum_shoot.mp3") }, -- primary sounds
    { sync_audio_sample_load("magnum_reload.mp3") }, -- secondary sounds
    false, -- strong weapon
    false, -- rapid fire
    0, -- spread
    50, -- damage
    1, -- bullet count
    0.2, -- bullet scale
    2000, -- bullet speed
    40, -- bullet steps
    6, -- max ammo
    15, -- deploy time
    30, -- cooldown time
    90, -- reload time
    common_shoot, -- primary fire
    common_reload, -- secondary fire
    check_common_gun_requirements -- requirement checks function
)

WEAPON_AK47 = weapon_register(
    "AK47", -- name
    false, -- dual wieldable
    E_MODEL_AK47, -- weapon model
    E_MODEL_SINGLE_ARM, -- arm model
    E_MODEL_YELLOW_COIN, -- bullet model
    { sync_audio_sample_load("ak47_shoot.mp3") }, -- primary sounds
    { sync_audio_sample_load("pistol_reload.mp3") }, -- secondary sounds
    false, -- strong weapon
    true, -- rapid fire
    30, -- spread
    10, -- damage
    1, -- bullet count
    0.2, -- bullet scale
    500, -- bullet speed
    10, -- bullet steps
    40, -- max ammo
    30, -- deploy time
    4, -- cooldown time
    70, -- reload time
    common_shoot, -- primary fire
    common_reload, -- secondary fire
    check_common_gun_requirements -- requirement checks function
)

--[[WEAPON_SHOTGUN = weapon_register(
    "Shotgun", -- name
    false, -- dual wieldable
    E_MODEL_SHOTGUN, -- weapon model
    E_MODEL_SINGLE_ARM, -- arm model
    E_MODEL_RED_COIN, -- bullet model
    { sync_audio_sample_load("shotgun_shoot.mp3") }, -- primary sounds
    {}, -- secondary sounds
    true, -- strong weapon
    false, -- rapid fire
    50, -- spread
    6, -- damage
    5, -- bullet count
    0.2, -- bullet scale
    1000, -- bullet speed
    20, -- bullet steps
    7, -- max ammo
    15, -- deploy time
    30, -- cooldown time
    120, -- reload time
    common_shoot, -- primary fire
    common_reload, -- secondary fire
    check_common_gun_requirements -- requirement checks function
)]]