-- Custom Geo Functions --

--- @param m MarioState
--- @return integer
--- Returns from directions between 1-8 depending on the camera angle
function mario_yaw_from_camera(m)
    local l = gLakituState
    local tau = math.pi * 2

    local vector = {X = l.pos.x - m.pos.x, Y = l.pos.y - m.pos.y,  Z = l.pos.z - m.pos.z}
    local r0 = math.rad((m.faceAngle.y * 360) / 0x10000)
    local r1 = r0 < 0 and tau - math.abs(r0) or r0
    local a0 = math.atan(vector.Z, vector.X) + math.pi * 0.5

    local a1
    a1 = ((a0 < 0 and tau - math.abs(a0) or a0) + r1)

    local a2 = (a1 % tau) * 8 / tau
    local angle = (math.round(a2) % 8) + 1
    return angle
end

-- Sonic Spin/Ball Acts --

local sSonicSpinBallActs = {
    [ACT_SPIN_JUMP]        = true,
    [ACT_SPIN_DASH]        = true,
    [ACT_AIR_SPIN]         = true,
    [ACT_HOMING_ATTACK]    = true,
}


local sSonicInstashieldActs = {
    [ACT_SPIN_JUMP]        = true,
    [ACT_AIR_SPIN]         = true,
}

local sSonicSpinDashActs = {
    [ACT_SPIN_DASH_CHARGE] = true,
}

--- @param n GraphNode | FnGraphNode
--- Switches between the spin and ball models during a spin/ball actions
function geo_ball_switch(n)
    local switch = cast_graph_node(n)
    local m = geo_get_mario_state()
    local e = gCharacterStates[m.playerIndex]

    if sSonicSpinBallActs[m.action] then
        if sSonicInstashieldActs[m.action] and e.sonic.instashieldTimer > 0 then
            switch.selectedCase = 4
        else
            switch.selectedCase = ((m.actionTimer - 1) % 4 // 2 + 1)
        end
    elseif sSonicSpinDashActs[m.action] then
        switch.selectedCase = 3
    elseif m.action == ACT_GROUND_POUND and m.actionTimer > 15 then
        switch.selectedCase = 1
    else
        switch.selectedCase = 0
    end
end

-- Spindash States --

--- @param n GraphNode | FnGraphNode
--- Switches the spindash states
function geo_custom_spindash_states(n)
    local switch = cast_graph_node(n)
    local m = geo_get_mario_state()
    local e = gCharacterStates[m.playerIndex]

    switch.selectedCase = math.floor(e.sonic.spindashState)
end

-- Mouth Switch --

SONIC_MOUTH_NORMAL    = 0 --- @type SonicMouthGSCId
SONIC_MOUTH_FROWN     = 1 --- @type SonicMouthGSCId
SONIC_MOUTH_GRIMACING = 2 --- @type SonicMouthGSCId
SONIC_MOUTH_HAPPY     = 3 --- @type SonicMouthGSCId
SONIC_MOUTH_GRIN      = 4 --- @type SonicMouthGSCId
SONIC_MOUTH_ATTACKED  = 5 --- @type SonicMouthGSCId
SONIC_MOUTH_SHOCKED   = 6 --- @type SonicMouthGSCId
SONIC_MOUTH_SURPRISED = 7 --- @type SonicMouthGSCId
SONIC_MOUTH_NEUTRAL   = 8 --- @type SonicMouthGSCId

local sGrimacingActs = {
    [ACT_HOLD_HEAVY_IDLE]    = true,
    [ACT_SHIVERING]          = true,
    [ACT_HOLD_HEAVY_WALKING] = true,
    [ACT_SHOCKED]            = true,
    [ACT_HEAVY_THROW]        = true,
}

local sSurprisedEyeStates = {
    [MARIO_EYES_LOOK_LEFT]  = true,
    [MARIO_EYES_LOOK_RIGHT] = true,
    [MARIO_EYES_LOOK_UP]    = true,
    [MARIO_EYES_LOOK_DOWN]  = true,
}

--- @param n GraphNode | FnGraphNode
--- Switches the mouth state
function geo_switch_mario_mouth(n)
    local switch = cast_graph_node(n)
    local m = geo_get_mario_state()
    local o = geo_get_current_object()

    if m.marioBodyState.eyeState == MARIO_EYES_DEAD then
        switch.selectedCase = SONIC_MOUTH_ATTACKED
    elseif sGrimacingActs[m.action] then
        switch.selectedCase = SONIC_MOUTH_GRIMACING
    elseif m.action == ACT_PANTING then
        switch.selectedCase = SONIC_MOUTH_SURPRISED
    elseif m.marioBodyState.eyeState == MARIO_EYES_HALF_CLOSED and m.action == ACT_START_SLEEPING then
        switch.selectedCase = SONIC_MOUTH_SHOCKED
        m.actionTimer = 0
    elseif m.marioBodyState.handState == MARIO_HAND_PEACE_SIGN then
        switch.selectedCase = SONIC_MOUTH_GRIN
    else
        switch.selectedCase = SONIC_MOUTH_NORMAL
    end
end

-- Mouth Side Switch --

SONIC_MOUTH_LEFT  = 0 --- @type SonicMouthSideGSCId
SONIC_MOUTH_RIGHT = 1 --- @type SonicMouthSideGSCId

--- @param n GraphNode | FnGraphNode
--- Switches the side that the mouth is being displayed on
function geo_switch_mario_mouth_side(n)
    local switch = cast_graph_node(n)
    local m = geo_get_mario_state()
    local o = geo_get_current_object()
    local angle = mario_yaw_from_camera(m)

    if angle <= 4 or m.marioBodyState.handState == MARIO_HAND_PEACE_SIGN then
        switch.selectedCase = SONIC_MOUTH_RIGHT
    else
        switch.selectedCase = SONIC_MOUTH_LEFT
    end
end

-- Custom Hand Switch --

    -- Hand Params

SONIC_HAND_RIGHT = 0 --- @type HandParam
SONIC_HAND_LEFT  = 1 --- @type HandParam
WAPEACH_HAND_AXE = 2 --- @type HandParam

    -- Wapeach Hand

local sWapeachAxeActs = {
    [ACT_AXE_CHOP]       = true,
    [ACT_AXE_SPIN]       = true,
    [ACT_AXE_SPIN_AIR]   = true,
    [ACT_AXE_SPIN_DIZZY] = true,
}

    -- Sonic Hand

local sSonicHandCopies = {
    [MARIO_HAND_FISTS]            = true,
    [MARIO_HAND_OPEN]             = true,
    [MARIO_HAND_HOLDING_CAP]      = true,
    [MARIO_HAND_HOLDING_WING_CAP] = true,
    [MARIO_HAND_RIGHT_OPEN]       = true,
}

local sSonicHandStateActs = {
    [ACT_STAR_DANCE_EXIT]    = { [SONIC_HAND_LEFT] = MARIO_HAND_PEACE_SIGN, [SONIC_HAND_RIGHT] = MARIO_HAND_FISTS },
    [ACT_STAR_DANCE_NO_EXIT] = { [SONIC_HAND_LEFT] = MARIO_HAND_PEACE_SIGN, [SONIC_HAND_RIGHT] = MARIO_HAND_FISTS },
}

--- @param n GraphNode | FnGraphNode
--- Switches the hand state
function geo_custom_hand_switch(n)
    local switch = cast_graph_node(n)
    local m = geo_get_mario_state()
    local bodyState = geo_get_body_state()
    local param = switch.parameter

    if param == WAPEACH_HAND_AXE then
        if sWapeachAxeActs[m.action] or m.marioObj.header.gfx.animInfo.animID == CS_ANIM_MENU then
            switch.selectedCase = 1
        else
            switch.selectedCase = 0
        end
    else
        if sSonicHandStateActs[m.action] and m.marioObj.header.gfx.animInfo.animFrame >= 58 then
            switch.selectedCase = sSonicHandStateActs[m.action][param]
        elseif sSonicHandCopies[bodyState.handState] then
            if bodyState.handState == MARIO_HAND_OPEN or bodyState.handState == MARIO_HAND_RIGHT_OPEN then
                if bodyState.handState == MARIO_HAND_OPEN then
                    if param == SONIC_HAND_LEFT then
                        switch.selectedCase = MARIO_HAND_OPEN
                    end
                end
                if bodyState.handState == MARIO_HAND_RIGHT_OPEN then
                    if param == SONIC_HAND_RIGHT then
                        switch.selectedCase = MARIO_HAND_OPEN
                    end
                end
            elseif (bodyState.action & ACT_FLAG_SWIMMING_OR_FLYING) ~= 0 then
                switch.selectedCase = MARIO_HAND_OPEN
            else
                switch.selectedCase = bodyState.handState
            end
        end
    end
end

-- Donkey Kong Angry Acts --

local sDonkeyKongAngryActs = {
    [ACT_DONKEY_KONG_POUND] =     true,
    [ACT_DONKEY_KONG_POUND_HIT] = true,
}

--- @param n GraphNode | FnGraphNode
--- Switches between normal head and angry head during angry actions
function geo_custom_dk_head_switch(n)
    local switch = cast_graph_node(n)
    local m = geo_get_mario_state()
    if sDonkeyKongAngryActs[m.action] then
        switch.selectedCase = 1
    else
        switch.selectedCase = 0
    end
end

local sDonkeyKongRollActs = {
    [ACT_DONKEY_KONG_ROLL] =     true,
    [ACT_DONKEY_KONG_ROLL_AIR] = true,
}

--- @param n GraphNode | FnGraphNode
--- Switches between the spin and main model.
function custom_dkroll_switch(n)
    local switch = cast_graph_node(n)
    local m = geo_get_mario_state()

    if sDonkeyKongRollActs[m.action] and (m.action ~= ACT_DONKEY_KONG_ROLL or
    m.actionState ~= 0) then
        switch.selectedCase = 1
    else
        switch.selectedCase = 0
    end
end