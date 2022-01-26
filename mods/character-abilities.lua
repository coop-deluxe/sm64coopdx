
-- TODO:

-- Luigi: runs on water
-- Luigi: tune swim and holding item speeds
-- Luigi: low friction
-- Luigi: BUG - can't jump off tree normally

-- Mario: wall kick slide all the way down wall


gStateExtras = {}
for i=0,(MAX_PLAYERS-1) do
    gStateExtras[i] = {}
    local m = gMarioStates[i]
    local e = gStateExtras[i]
    e.lastAction = m.action
    e.animFrame = 0
    e.scuttle = 0
end

-----------
-- luigi --
-----------

function luigi_before_phys_step(m)
    local e = gStateExtras[m.playerIndex]

    local hScale = 1.0
    local vScale = 1.0

    -- faster swimming
    if (m.action & ACT_FLAG_SWIMMING) ~= 0 then
        hScale = hScale * 1.25
    end

    -- slower holding item
    if m.heldObj ~= nil then
        m.vel.y = m.vel.y - 2.0
        hScale = hScale * 0.9
        if (m.action & ACT_FLAG_AIR) ~= 0 then
            hScale = hScale * 0.9
        end
    end
    m.forwardVel = m.forwardVel * 0.99

    m.vel.x = m.vel.x * hScale
    m.vel.y = m.vel.y * vScale
    m.vel.z = m.vel.z * hScale
end

function luigi_on_set_action(m)
    local e = gStateExtras[m.playerIndex]

    -- extra height to the backflip
    if m.action == ACT_BACKFLIP then
        m.vel.y = m.vel.y + 18

    -- nerf wall kicks
    elseif m.action == ACT_WALL_KICK_AIR and m.prevAction ~= ACT_HOLDING_POLE and m.prevAction ~= ACT_CLIMBING_POLE then
        if m.vel.y > 15 then m.vel.y = 15 end
        return

    -- turn dive into kick when holding jump
    elseif m.action == ACT_DIVE and (m.controller.buttonDown & A_BUTTON) ~= 0 and e.scuttle > 0 then
        return set_mario_action(m, ACT_JUMP_KICK, 0)

    -- extra height on jumps
    elseif m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP or m.action == ACT_TRIPLE_JUMP or m.action == ACT_SPECIAL_TRIPLE_JUMP or m.action == ACT_STEEP_JUMP or m.action == ACT_SIDE_FLIP or m.action == ACT_RIDING_SHELL_JUMP then
        m.vel.y = m.vel.y + 6

    end

    e.lastAction = action
end

function luigi_update(m)
    local e = gStateExtras[m.playerIndex]

    -- air scuttle
    e.scuttle = 0
    if m.action == ACT_JUMP or m.action == ACT_DOUBLE_JUMP then
        if (m.controller.buttonDown & A_BUTTON) ~= 0 and m.vel.y < -5 then
            m.vel.y = m.vel.y + 2.5
            set_mario_animation(m, MARIO_ANIM_RUNNING_UNUSED)
            set_anim_to_frame(m, e.animFrame)
            e.animFrame = e.animFrame + 10
            if e.animFrame >= m.marioObj.header.gfx.animInfo.curAnim.loopEnd then
                e.animFrame = e.animFrame - m.marioObj.header.gfx.animInfo.curAnim.loopEnd
            end
            e.scuttle = 1
        end
    end

    -- backflip turns into twirl
    if m.action == ACT_BACKFLIP and m.marioObj.header.gfx.animInfo.animFrame > 18 then
        m.angleVel.y = 0x1800
        set_mario_action(m, ACT_TWIRLING, 1)
    end
end

----------
-- main --
----------
function mario_before_phys_step(m)
    if (m.character == gCharacters[CT_LUIGI]) then
        luigi_before_phys_step(m)
    end
end

function mario_on_set_action(m)
    if (m.character == gCharacters[CT_LUIGI]) then
        luigi_on_set_action(m)
    end
end

function mario_action_on_change(m)
    if (m.character == gCharacters[CT_LUIGI]) then
        luigi_update(m)
    end
end

function mario_update(m)
    if (m.character == gCharacters[CT_LUIGI]) then
        luigi_update(m)
    end
end

-----------
-- hooks --
-----------

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ON_SET_MARIO_ACTION, mario_on_set_action)
hook_event(HOOK_BEFORE_PHYS_STEP, mario_before_phys_step)
