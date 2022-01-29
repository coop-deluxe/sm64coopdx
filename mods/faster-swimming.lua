-- name: Faster Swimming
-- incompatible:
-- description: Everyone swims faster.

function mario_before_phys_step(m)
    local hScale = 1.0
    local vScale = 1.0

    -- faster swimming
    if (m.action & ACT_FLAG_SWIMMING) ~= 0 then
        hScale = hScale * 2.0
        if m.action ~= ACT_WATER_PLUNGE then
            vScale = vScale * 2.0
        end
    end

    m.vel.x = m.vel.x * hScale
    m.vel.y = m.vel.y * vScale
    m.vel.z = m.vel.z * hScale
end

-----------
-- hooks --
-----------

hook_event(HOOK_BEFORE_PHYS_STEP, mario_before_phys_step)
