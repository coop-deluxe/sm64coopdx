-- name: Mario RUN!
-- description: Mario is constantly running.

Threshold = 50 --set Threshold to 50

function mario_update(m)
    --Prevent mario from ideling
    if m.action == ACT_IDLE then --If idle
        set_mario_action(m, ACT_WALKING, 0) --Make Mario walk
    end

    --Crouching doesnt apply vel so prevent that
    if m.action == ACT_CROUCHING then --If crouching
        set_mario_action(m, ACT_WALKING, 0) --Make Mario walk
    end

    --Speed floor
    if (m.forwardVel > Threshold) and (m.forwardVel < Threshold) then --If Mario isn't moveing fast enough
        m.forwardVel = Threshold --set forwards velocity to whatevet the threashold is set to
    end
end

-- hooks --
hook_event(HOOK_MARIO_UPDATE, mario_update)
