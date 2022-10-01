-- name: Shell Rush
-- description: Race around SM64 levels on shells.\n\nCollect powerups such as red shells, green shells, bananas, and mushrooms.
-- incompatible: gamemode moveset

DEBUG = false
UNST22 = true -- gotta work around unst 22 bugs :(

gPowerups = {}

gGlobalSyncTable.speed = 0.8

for i = 0, (MAX_PLAYERS - 1) do
    gPowerups[i] = {
        [0] = nil,
        [1] = nil,
        [2] = nil,
    }
    local s = gPlayerSyncTable[i]
    s.waypoint = 1
    s.lap = 0
    s.powerup = {}
    s.powerup[0] = POWERUP_NONE
    s.powerup[1] = POWERUP_NONE
    s.powerup[2] = POWERUP_NONE
    s.finish = 0
    s.random = 0
end

-------------------------------------------------------------------------------

function mario_update_local(m)
    local s = gPlayerSyncTable[m.playerIndex]

    -- crouch to use shell
    local pressZ = (m.controller.buttonPressed & Z_TRIG) ~= 0
    local blockShell = (m.action & (ACT_FLAG_INVULNERABLE | ACT_GROUP_CUTSCENE | ACT_FLAG_INTANGIBLE)) ~= 0
    local allowShell = (m.action & (ACT_FLAG_STATIONARY | ACT_FLAG_MOVING | ACT_FLAG_SWIMMING)) ~= 0
    if pressZ and not is_riding(m) and not blockShell and allowShell then
        set_mario_action(m, ACT_RIDING_SHELL_GROUND, 0)
        m.actionTimer = 0
        -- fix vanilla camera
        if m.area.camera.mode == CAMERA_MODE_WATER_SURFACE then
            set_camera_mode(m.area.camera, CAMERA_MODE_FREE_ROAM, 1)
        end
    end

    -- use powerups
    if (m.controller.buttonPressed & Z_TRIG) ~= 0 and ((is_riding(m) and m.actionTimer > 1) or DEBUG) then
        for i = 0, 2 do
            if s.powerup[i] ~= POWERUP_NONE then
                use_powerup(m, s.powerup[i])
                s.powerup[i] = POWERUP_NONE
                break
            end
        end
    end

    -- debug
    if DEBUG then
        if (m.controller.buttonPressed & D_JPAD) ~= 0 then
            warp_to_level(LEVEL_CASTLE_GROUNDS, 1, 16)
            print(m.pos.x, m.pos.y, m.pos.z, ' --- ', m.faceAngle.y)

            for i = 0, 2 do
                gPlayerSyncTable[0].powerup[i] = POWERUP_BANANA
            end
        end

        if (m.controller.buttonPressed & L_JPAD) ~= 0 then
            for i = 0, 2 do
                gPlayerSyncTable[0].powerup[i] = POWERUP_GREEN_SHELL
            end
        end

        if (m.controller.buttonPressed & R_JPAD) ~= 0 then
            for i = 0, 2 do
                gPlayerSyncTable[0].powerup[i] = POWERUP_RED_SHELL
            end
        end

        if (m.controller.buttonPressed & U_JPAD) ~= 0 then
            for i = 0, 2 do
                gPlayerSyncTable[0].powerup[i] = POWERUP_MUSHROOM
            end
        end
    end
end

function on_speed_command(msg)
    if tonumber(msg) > 0 then
        gGlobalSyncTable.speed = tonumber(msg)
        return true
    end
    return false
end

function mario_update(m)
    local s = gPlayerSyncTable[m.playerIndex]
    if not active_player(m) then
        return
    end

    if m.playerIndex == 0 then
        mario_update_local(m)
    end

    -- max health
    m.health = 0x880

    -- spawn powerups
    for i = 0, 2 do
        if gPowerups[m.playerIndex][i] == nil and s.powerup[i] ~= POWERUP_NONE then
            if s.powerup[i] ~= POWERUP_NONE then
                gPowerups[m.playerIndex][i] = spawn_powerup(m, s.powerup[i], i)
            end
        end
    end
end

function allow_pvp_attack(m1, m2)
    return false
end

function on_pause_exit(exitToCastle)
    return false
end

function on_update()
    spawn_custom_level_objects()
    race_update()
end

hook_event(HOOK_UPDATE, on_update)
hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ALLOW_PVP_ATTACK, allow_pvp_attack)
hook_event(HOOK_ON_PAUSE_EXIT, on_pause_exit)
if network_is_server() then
    hook_chat_command('speed', "[decimal number, default: 0.8]", on_speed_command)
 end
