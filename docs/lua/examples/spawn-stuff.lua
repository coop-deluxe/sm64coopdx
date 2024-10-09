-- name: Spawn Stuff
-- description: Press DPAD, or L+DPAD to spawn things

function non_l_spawning(m)
    if (m.controller.buttonPressed & U_JPAD) ~= 0 then
        -- spawn TTC cube
        spawn_sync_object(
            id_bhvTTCRotatingSolid,
            E_MODEL_TTC_ROTATING_CUBE,
            m.pos.x, m.pos.y, m.pos.z,

            function(obj)
                obj.oBehParams2ndByte = 0
                obj.oOpacity = 255
            end)
    end

    if (m.controller.buttonPressed & D_JPAD) ~= 0 then
        -- spawn breakable box
        spawn_sync_object(
            id_bhvBreakableBox,
            E_MODEL_BREAKABLE_BOX,
            m.pos.x, m.pos.y, m.pos.z,
            nil)
    end

    if (m.controller.buttonPressed & L_JPAD) ~= 0 then
        -- spawn bobomb in hand
        local obj = spawn_sync_object(
            id_bhvBobomb,
            E_MODEL_BOBOMB_BUDDY,
            m.pos.x, m.pos.y, m.pos.z,

            function(obj)
                obj.oBehParams2ndByte = 0
                obj.oOpacity = 255
                obj.oFlags = OBJ_FLAG_HOLDABLE
                obj.oInteractType = obj.oInteractType | INTERACT_GRABBABLE
            end)

        if obj ~= nil then
            m.usedObj = obj
            mario_grab_used_object(m)
            m.marioBodyState.grabPos = GRAB_POS_LIGHT_OBJ
            set_mario_action(m, ACT_HOLD_IDLE, 0)
        end
    end

    if (m.controller.buttonPressed & R_JPAD) ~= 0 then
        -- spawn goomba
        spawn_sync_object(
            id_bhvGoomba,
            E_MODEL_GOOMBA,
            m.pos.x + 150, m.pos.y, m.pos.z,
            nil)
    end
end

function l_spawning(m)
    if (m.controller.buttonPressed & U_JPAD) ~= 0 then
        -- spawn TTC prism
        spawn_sync_object(
            id_bhvTTCRotatingSolid,
            E_MODEL_TTC_ROTATING_PRISM,
            m.pos.x, m.pos.y, m.pos.z,

            function(obj)
                obj.oBehParams2ndByte = 1
                obj.oOpacity = 255
            end)
    end

    if (m.controller.buttonPressed & D_JPAD) ~= 0 then
        -- spawn small breakable box in hand
        local obj = spawn_sync_object(
            id_bhvBreakableBoxSmall,
            E_MODEL_BREAKABLE_BOX_SMALL,
            m.pos.x, m.pos.y, m.pos.z,

            function(obj)
                obj.oBehParams2ndByte = 0
                obj.oOpacity = 255
                obj.oFlags = OBJ_FLAG_HOLDABLE
                obj.oInteractType = obj.oInteractType | INTERACT_GRABBABLE
            end)

        if obj ~= nil then
            m.usedObj = obj
            mario_grab_used_object(m)
            m.marioBodyState.grabPos = GRAB_POS_LIGHT_OBJ
            set_mario_action(m, ACT_HOLD_IDLE, 0)
        end
    end

    if (m.controller.buttonPressed & L_JPAD) ~= 0 then
        -- spawn boulder
        spawn_sync_object(
            id_bhvBigBoulder,
            E_MODEL_HMC_ROLLING_ROCK,
            m.pos.x, m.pos.y, m.pos.z,

            function(obj)
                obj.oBehParams2ndByte = 2
                obj.oMoveAngleYaw = m.marioObj.oMoveAngleYaw
            end)
        m.invincTimer = 5
    end

    if (m.controller.buttonPressed & R_JPAD) ~= 0 then
        -- spawn boulder
        spawn_sync_object(
            id_bhvKoopaShell,
            E_MODEL_KOOPA_SHELL,
            m.pos.x + 150, m.pos.y, m.pos.z,
            nil)
        m.invincTimer = 5
    end
    
end

function mario_update_local(m)
    if (m.controller.buttonDown & L_TRIG) ~= 0 then
        l_spawning(m)
    else
        non_l_spawning(m)
    end

end

function mario_update(m)
    if m.playerIndex == 0 then
        mario_update_local(m)
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)