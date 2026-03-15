----------------------
-- Toadette Moveset --
----------------------

if not charSelect then return end

function toadette_before_phys_step(m)
    local hScale = 1.0
    local vScale = 1.0

    -- faster ground movement
    if (m.action & ACT_FLAG_MOVING) ~= 0 then
        hScale = hScale * 1.05
    end

    -- slower holding item
    if m.heldObj then
        m.vel.y = m.vel.y - 2.0
        hScale = hScale * 0.9
        if (m.action & ACT_FLAG_AIR) ~= 0 then
            hScale = hScale * 0.9
        end
    end

    m.vel.x = m.vel.x * hScale
    m.vel.y = m.vel.y * vScale
    m.vel.z = m.vel.z * hScale
end

function toadette_on_set_action(m)
    local e = gCharacterStates[m.playerIndex]

    -- wall kick height based on how fast toadette is going
    if m.action == ACT_WALL_KICK_AIR and m.prevAction ~= ACT_HOLDING_POLE and m.prevAction ~= ACT_CLIMBING_POLE then
        m.vel.y = m.vel.y * 0.8
        m.vel.y = m.vel.y + e.toadette.averageForwardVel * 0.8
        return
    end

    -- more distance on dive and long jump
    if m.action == ACT_DIVE or m.action == ACT_LONG_JUMP then
        m.forwardVel = m.forwardVel * 1
    end

    -- less height on jumps
    if m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_TRIPLE_JUMP or m.action == ACT_SPECIAL_TRIPLE_JUMP or m.action == ACT_STEEP_JUMP or m.action == ACT_RIDING_SHELL_JUMP or m.action == ACT_BACKFLIP or m.action == ACT_WALL_KICK_AIR or m.action == ACT_LONG_JUMP then
        m.vel.y = m.vel.y * 1

        -- prevent from getting stuck on platform
        if m.marioObj.platform then
            m.pos.y = m.pos.y + 10
        end
    elseif m.action == ACT_SIDE_FLIP then
        m.vel.y = m.vel.y * 0.86

        -- prevent from getting stuck on platform
        if m.marioObj.platform then
            m.pos.y = m.pos.y + 10
        end
    end
end

function toadette_update(m)
    local e = gCharacterStates[m.playerIndex]

    -- track average forward velocity
    if e.toadette.averageForwardVel > m.forwardVel then
        e.toadette.averageForwardVel = e.toadette.averageForwardVel * 0.93 + m.forwardVel * 0.07
    else
        e.toadette.averageForwardVel = m.forwardVel
    end

    -- keep your momentum for a while
    if m.action == ACT_WALKING and m.forwardVel > 30 then
        mario_set_forward_vel(m, m.forwardVel + 0.8)
    end

    -- faster flip during ground pound
    if m.action == ACT_GROUND_POUND then
        m.marioObj.header.gfx.animInfo.animAccel = 32768 * 4
        if m.actionTimer < 10 then
            m.actionTimer = m.actionTimer + 1
        end
    end

    -- Floaty
    if m.vel.y < 0 and (m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_TRIPLE_JUMP or m.action == ACT_HOLD_JUMP) then
        m.vel.y = m.vel.y + 0.9
    end
end
