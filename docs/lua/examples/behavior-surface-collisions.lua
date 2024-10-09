-- name: Custom Box with collisions
-- description: Press DPAD+down to spawn a box

function bhv_custom_box_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.collisionData = gGlobalObjectCollisionData.breakable_box_seg8_collision_08012D70
    obj.oCollisionDistance = 500
end

function bhv_custom_box_loop(obj)
    load_object_collision_model()
end

-- hook the behavior
id_bhvCustomBox = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_custom_box_init, bhv_custom_box_loop)

------------------------

function mario_update_local(m)
    if (m.controller.buttonPressed & D_JPAD) ~= 0 then
        -- spawn breakable box
        spawn_non_sync_object(
            id_bhvCustomBox,
            E_MODEL_BREAKABLE_BOX,
            m.pos.x, m.pos.y, m.pos.z,
            nil)
    end
end

function mario_update(m)
    if m.playerIndex == 0 then
        mario_update_local(m)
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
