function mario_update(index)
    local m = get_mario_state(index)
    if m.vel.y > 0 then
        m.vel.y = m.vel.y + 2
    end
    set_mario_state(index, m)
    if m.action == ACT_DIVE then
        set_mario_action(index, ACT_TWIRLING, 0);
    end
end

function update()
end

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_MARIO_UPDATE, mario_update)
