
gMarioStateExtras = {}
for i=0,(MAX_PLAYERS-1) do
    gMarioStateExtras[i] = {}
    local m = gMarioStates[i]
    local e = gMarioStateExtras[i]
    e.actionLastFrame = m.action
end

-----------
-- luigi --
-----------

function luigi_action_on_change(m)
    local e = gMarioStateExtras[m.playerIndex]

    -- extra height to the backflip
    if m.action == ACT_BACKFLIP then
        m.vel.y = m.vel.y + 25
    end
end

function luigi_update(m)
    local e = gMarioStateExtras[m.playerIndex]
    -- backflip turns into twirl
    if m.action == ACT_BACKFLIP and m.marioObj.header.gfx.animInfo.animFrame > 18 then
        m.angleVel.y = 0x1800
        set_mario_action(m, ACT_TWIRLING, 1)
    end
end

----------
-- main --
----------

function mario_action_on_change(m)
    -- if luigi then
    luigi_update(m)
    -- end
end

function mario_update(m)
    local e = gMarioStateExtras[m.playerIndex]

    -- if luigi then
    luigi_update(m)
    -- end

    -- action change event
    if e.actionLastFrame ~= m.action then
        mario_action_on_change(m)
    end
    e.actionLastFrame = m.action
end

-----------
-- hooks --
-----------

hook_event(HOOK_MARIO_UPDATE, mario_update)
