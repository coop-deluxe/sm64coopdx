if SM64COOPDX_VERSION == nil then return end

define_custom_obj_fields({
    oGmHealth = "f32"
})

--- @return number
--- Gets the player's health in 0-100 format
function get_health()
    return clampf((gMarioStates[0].health - 0xFF) / (0x880 - 0xFF), 0, 1) * 100
end

--- @return nil
--- Sets the player's health in 0-100 format
function set_health(health)
    gMarioStates[0].health = (health * 19.21) + 0xFF
end

function packet_send(reliable, packet, dataTable)
    dataTable.packet = packet
    dataTable.level = gNetworkPlayers[0].currLevelNum
    dataTable.area = gNetworkPlayers[0].currAreaIndex
    dataTable.act = gNetworkPlayers[0].currActNum
    network_send(reliable, dataTable)
    on_packet_receive(dataTable)
end

------------------
-- synced audio --
------------------

gSoundTable = {}
local soundId = -1

function sync_audio_sample_load(filename)
    local sound = audio_sample_load(filename)
    if sound ~= nil then
        soundId = soundId + 1
        gSoundTable["snd" .. soundId] = sound
        return "snd" .. soundId
    end
    return nil
end

function sync_audio_sample_play(audio, position, volume)
    local packet = {
        sound = audio,
        x = position.x,
        y = position.y,
        z = position.z,
        volume = volume
    }
    packet_send(false, PACKET_SOUND, packet)
end


--------------------
-- misc functions --
--------------------

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

function if_then_else(cond, ifTrue, ifFalse)
    if cond then return ifTrue end
    return ifFalse
end

function handle_timer(timer)
    if timer > 0 then
        timer = timer - 1
    end
    return timer
end

function split(s)
    local result = {}
    for match in (s):gmatch(string.format("[^%s]+", " ")) do
        table.insert(result, match)
    end
    return result
end

function on_or_off(value)
    if value then return "\\#00ff00\\ON" end
    return "\\#ff0000\\OFF"
end

function name_without_hex(name)
    local s = ''
    local inSlash = false
    for i = 1, #name do
        local c = name:sub(i,i)
        if c == '\\' then
            inSlash = not inSlash
        elseif not inSlash then
            s = s .. c
        end
    end
    return s
end

function lerp(a,b,t) return a * (1-t) + b * t end

--- @param obj Object
function obj_set_animation(obj, name)
    if obj == nil then return end

    local animPointer = nil
    if obj.header.gfx.animInfo.curAnim ~= nil then animPointer = obj.header.gfx.animInfo.curAnim._pointer end
    smlua_anim_util_set_animation(obj, name)
    if obj.header.gfx.animInfo.curAnim._pointer ~= animPointer then
        obj.header.gfx.animInfo.animAccel = 0
        obj.header.gfx.animInfo.animFrame = obj.header.gfx.animInfo.curAnim.startFrame
    end
end

--- @param o1 Object
--- @param o2 Object
--- Basically `obj_check_hitbox_overlap()` except it uses 3 variables for object 1's X, Y and Z coordinates
function obj_check_hitbox_overlap_xyz(o1, o2, x2, y2, z2)
    if o1 == nil or o2 == nil then return false end

    local o1H = maxf(o1.hitboxHeight, o1.hurtboxHeight) -- object 1 hitbox height
    local o1R = maxf(o1.hitboxRadius, o1.hurtboxRadius) -- object 1 hitbox radius
    local o2H = maxf(o2.hitboxHeight, o2.hurtboxHeight) -- object 2 hitbox height
    local o2R = maxf(o2.hitboxRadius, o2.hurtboxRadius) -- object 2 hitbox radius

    -- calculate the distance between the cylinder centers in the xz-plane
    local distanceXZ = math.sqrt(sqrf(x2 - o1.oPosX) + sqrf(z2 - o1.oPosZ))

    -- check for collision in the xz-plane (ignoring height)
    if distanceXZ <= o1R + o2R then
        -- check for collision in the y-axis (height)
        if math.abs(y2 - o1.oPosY) <= maxf(o1H, o2H) * 0.5 then
            return true
        end
    end

    return false
end

--- @param obj Object
function obj_skip_in_view_check(obj)
    obj.header.gfx.skipInViewCheck = true
end

--- @param o Object
function obj_sign_hitbox(o)
    o.hitboxRadius = o.hitboxRadius * 0.75
    o.hitboxHeight = o.hitboxHeight * 1.5
    o.oGmHealth = HEALTH_SIGN
end

--- @param o Object
function obj_amp_hitbox(o)
    if o.oAction ~= AMP_ACT_ATTACK_COOLDOWN then
        o.hitboxHeight = o.hitboxHeight * 2
    end
end

--- @param o Object
function obj_chuckya_hitbox(o)
    o.hitboxHeight = o.hitboxHeight * 2
    o.oGmHealth = HEALTH_CHUCKYA
end

--- @param o Object
function obj_snufit_hitbox(o)
    o.hitboxRadius = o.hitboxRadius * 0.6
    o.hitboxHeight = o.hitboxHeight * 2
    o.hitboxDownOffset = 60
end

--- @param o Object
function obj_king_bobomb_hitbox(o)
    o.oGmHealth = HEALTH_KING_BOBOMB
    o.hitboxHeight = o.hitboxHeight * 3
end

-- generic
function obj_generate_hitbox_multiply_func(radius, height)
    --- @param o Object
    local func = function(o)
        o.hitboxRadius = o.hitboxRadius * radius
        o.hitboxHeight = o.hitboxHeight * height
    end
    return func
end

-- generic
function obj_generate_health_func(health)
    --- @param o Object
    local func = function(o)
        o.oGmHealth = health
    end
    return func
end

function gm_hook_behavior(id, override, init, loop)
    hook_behavior(
        id,
        get_object_list_from_behavior(get_behavior_from_id(id)), -- automatically get the correct object list
        override, init, loop,
        "bhvGm" .. get_behavior_name_from_id(id):sub(4) -- give the behavior a consistent behavior name (for example, bhvGoomba will become bhvGmGoomba)
    )
end