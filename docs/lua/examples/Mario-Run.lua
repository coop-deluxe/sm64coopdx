-- name: Mario RUN!
-- description: Mario is constantly running.

local speedThreshold = 50

local function mario_update(m)
    --Prevent mario from crouching or idling
    if m.action == ACT_IDLE or m.action == ACT_CROUCHING then
        set_mario_action(m, ACT_WALKING, 0)
    end

    -- Ensures that Mario moves at a speed greater than or equal to speedThreshold
    m.forwardVel = math.max(m.forwardVel,speedThreshold)
end

-- hooks --
hook_event(HOOK_MARIO_UPDATE, mario_update)
