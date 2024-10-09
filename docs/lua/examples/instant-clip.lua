-- name: Instant Clip
-- description: Press L trigger, profit!

function mario_update(m)
    if (m.controller.buttonDown & L_TRIG) ~= 0 then -- If L pressed
        set_mario_action(m, ACT_WALKING, 0) --set mario to walking so his vel is used
        m.forwardVel = 400 --set Velocity to clip speed
    end
end

-- hooks --
hook_event(HOOK_MARIO_UPDATE, mario_update)