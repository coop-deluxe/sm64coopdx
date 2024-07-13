-- name: MoonJump
-- description: Hold the A button to Moonjump

local function mario_update(m)
    if (m.controller.buttonDown & A_BUTTON) ~= 0 then --If the A button is held
        m.vel.y = 25 --Set Y velocity to 25
    end
end

-- hooks --
hook_event(HOOK_MARIO_UPDATE, mario_update)