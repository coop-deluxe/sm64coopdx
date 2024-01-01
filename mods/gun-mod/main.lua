-- name: Gun Mod DX
-- incompatible: weapon
-- description: Gun Mod DX v3.0.2\nBy \\#ec7731\\Agent X\\#dcdcdc\\\nSpecial thanks to \\#f296af\\PeachyPeach\\#dcdcdc\\\n\nThis is a rewritten & overhauled version of my original Gun Mod for sm64ex-coop. I thought this would make a good mod to bundle with sm64coopdx. If you have two pistols, you are able to dual wield them as well!\n\nPress [\\#3040ff\\Y\\#dcdcdc\\] to shoot\nPress [\\#3040ff\\X\\#dcdcdc\\] to reload\nRun \\#00ffff\\/gm help\\#dcdcdc\\ for help
-- deluxe: true

if SM64COOPDX_VERSION == nil then return end

gGlobalSyncTable.gunModEnabled = true

local renderHud = true

gShootableHitboxes = {
    [id_bhvMario] = hurt_player,
    [id_bhvStar] = hurt_star,
    [id_bhvMessagePanel] = hurt_sign,
    [id_bhvToadMessage] = hurt_toad,
    [id_bhvExclamationBox] = hurt_exclamation_box,
    [id_bhvBreakableBox] = hurt_breakable_box,
    [id_bhvBreakableBoxSmall] = hurt_breakable_box_small,
    [id_bhvBowlingBall] = hurt_bowling_ball,
    [id_bhvWaterBomb] = hurt_water_bomb,
    [id_bhvTree] = hurt_tree,
    [id_bhvChainChomp] = hurt_chain_chomp,
    [id_bhvGoomba] = hurt_goomba,
    [id_bhvBobomb] = hurt_bobomb,
    [id_bhvHomingAmp] = hurt_amp,
    [id_bhvCirclingAmp] = hurt_amp,
    [id_bhvKoopa] = hurt_koopa,
    [id_bhvFlyGuy] = hurt_snufit,
    [id_bhvChuckya] = hurt_chuckya,
    [id_bhvPiranhaPlant] = hurt_piranha_plant,
    [id_bhvSnufit] = hurt_snufit,
    [id_bhvSwoop] = hurt_snufit,
    [id_bhvSpindrift] = hurt_spindrift,
    [id_bhvMrBlizzard] = hurt_mr_blizzard,
    [id_bhvMrI] = hurt_mr_i,
    [id_bhvScuttlebug] = hurt_scuttlebug,
    [id_bhvPokeyBodyPart] = hurt_pokey,
    [id_bhvSkeeter] = hurt_scuttlebug,
    [id_bhvSmallBully] = hurt_bully,
    [id_bhvBigBully] = hurt_bully,
    [id_bhvSmallChillBully] = hurt_bully,
    [id_bhvBigChillBully] = hurt_bully,
    [id_bhvMoneybag] = hurt_moneybag,
    [id_bhvKingBobomb] = hurt_king_bobomb,
    [id_bhvBowser] = hurt_bowser,
    [id_bhvYoshi] = hurt_yoshi
}

--- @param enable boolean
--- @return nil
--- Globally enables or disables Gun Mod
local function enable_gun_mod(enable)
    if not network_is_server() and not network_is_moderator() then return end
    if type(enable) ~= "boolean" then return end
    gGlobalSyncTable.gunModEnabled = enable
    djui_popup_create("Gun Mod has been " .. if_then_else(gGlobalSyncTable.gunModEnabled, "enabled.", "disabled."), 2)
end

--- @param weapon WeaponId
--- Returns a weapon by its ID
local function get_weapon(weapon)
    return gWeaponTable[weapon]
end

--- @return nil
--- Returns whether or not the Gun Mod HUD will render
local function get_render_hud()
    return renderHud
end

--- @param enable boolean
--- @return nil
--- Sets whether or not the Gun Mod HUD will render
local function set_render_hud(enable)
    if type(enable) ~= "boolean" then return end
    renderHud = enable
end

--- @param behavior BehaviorId
--- @param hurtFunc fun(obj:Object, bulletObj:Object)
--- @return nil
local function shootable_register(behavior, hurtFunc)
    if type(behavior) ~= "number" or type(hurtFunc) ~= "function" then return end
    gShootableHitboxes[behavior] = hurtFunc
end

--- @param m MarioState
local function mario_update(m)
    if active_player(m) == 0 then return end

    if gGlobalSyncTable.gunModEnabled and gPlayerSyncTable[m.playerIndex].curWeapon ~= nil then
        local spawned = false
        local held = obj_get_first_with_behavior_id(id_bhvHeldWeapon)
        while held ~= nil do
            if obj_get_weapon_owner(held) == gNetworkPlayers[m.playerIndex].globalIndex then
                spawned = true
                break
            end
            held = obj_get_next_with_same_behavior_id(held)
        end

        if not spawned then
            spawn_non_sync_object(
                id_bhvHeldWeapon,
                gWeaponTable[gPlayerSyncTable[m.playerIndex].curWeapon].model,
                0, 0, 0,
                --- @param o Object
                function(o)
                    obj_set_weapon_params(o, gNetworkPlayers[m.playerIndex].globalIndex, gPlayerSyncTable[m.playerIndex].curWeapon, 0, 0)
                end
            )

            if gPlayerSyncTable[m.playerIndex].curWeapon2 ~= nil then
                spawn_non_sync_object(
                    id_bhvHeldWeapon,
                    gWeaponTable[gPlayerSyncTable[m.playerIndex].curWeapon2].model,
                    0, 0, 0,
                    --- @param o Object
                    function(o)
                        obj_set_weapon_params(o, gNetworkPlayers[m.playerIndex].globalIndex, gPlayerSyncTable[m.playerIndex].curWeapon2, 1, 0)
                    end
                )
            end
        end
    end

    if m.playerIndex ~= 0 then return end

    if vec3f_dist(m.pos, m.area.camera.pos) < 500 and (m.action & ACT_GROUP_MASK) ~= ACT_GROUP_CUTSCENE then
        m.marioBodyState.modelState = m.marioBodyState.modelState | MODEL_STATE_NOISE_ALPHA
    end

    if get_first_person_enabled() then
        if gGlobalSyncTable.gunModEnabled and obj_get_first_with_behavior_id(id_bhvViewmodel) == nil and cur_weapon() ~= nil then
            spawn_viewmodels()
        end

        if (m.action & ACT_FLAG_IDLE) ~= 0 then
            m.faceAngle.y = gLakituState.yaw + 0x8000
        end

        -- movement
        -- if m.action ~= ACT_CUSTOM_MOVEMENT then
        --     set_mario_action(m, ACT_CUSTOM_MOVEMENT, 0)
        --     vec3f_copy(gPlayerFirstPerson.movement.pos, m.pos)
        -- end
    elseif not camera_config_is_mouse_look_enabled() then
        djui_hud_set_mouse_locked(false)
    end

    -- disable negative vertical speed conservation so guns don't appear lower than normal
    local group = (m.action & ACT_GROUP_MASK)
    if (group == ACT_GROUP_MOVING or group == ACT_GROUP_STATIONARY or group == ACT_GROUP_OBJECT) and (m.action & ACT_FLAG_AIR) == 0 and m.vel.y < 0 then
        m.vel.y = 0
    end

    if gGlobalSyncTable.gunModEnabled then
        weapon_update()
    end
end

local function on_level_init()
    local obj = obj_get_first(OBJ_LIST_SURFACE)
    while obj ~= nil do
        obj.header.gfx.skipInViewCheck = true
        obj = obj_get_next(obj)
    end

    spawn_dialog_arrow()

    if not mod_storage_load_bool("init") then
        mod_storage_save_bool("init", true)
        audio_sample_play(SOUND_CUSTOM_BAD_TO_THE_BONE, gMarioStates[0].pos, 1)
    end
end

local function on_hud_render_behind()
    local weapon = cur_weapon()
    if weapon == nil or not renderHud or not gGlobalSyncTable.gunModEnabled or gNetworkPlayers[0].currActNum == 99 or obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil then return end

    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_HUD)

    local width = djui_hud_get_screen_width()
    local height = djui_hud_get_screen_height()

    if get_first_person_enabled() and weapon ~= nil and not is_game_paused() then
        djui_hud_set_color(255, 255, 0, 127)
        djui_hud_render_texture(TEX_CROSSHAIR, width * 0.5 - 4, height * 0.5 - 4, 0.5, 0.5)
    end

    local y = height - 35
    djui_hud_set_color(255, 255, 255, 255)
    if weapon.maxAmmo ~= 0 then
        djui_hud_print_text(weapon.ammo .. "/" .. weapon.maxAmmo, width - 128, y, 1)
    end

    local weapon2 = cur_dual_wield_weapon()
    if weapon2 ~= nil and weapon2.maxAmmo ~= 0 then
        djui_hud_print_text(weapon2.ammo .. "/" .. weapon2.maxAmmo, 16, y, 1)
    end
end

function on_packet_receive(dataTable)
    if dataTable.packet == PACKET_ATTACK then
        if gNetworkPlayers[0].currLevelNum == dataTable.level and gNetworkPlayers[0].currAreaIndex == dataTable.area and gNetworkPlayers[0].currActNum == dataTable.act then
            audio_sample_play(SOUND_CUSTOM_IMPACT, gMarioStates[0].pos, 1)
        end

        if dataTable.yoshi then
            local pos = gMarioStates[network_local_index_from_global(dataTable.globalIndex)].pos
            spawn_non_sync_object(
                id_bhvExplosion,
                E_MODEL_TROLL_EXPLOSION,
                pos.x, pos.y + 80, pos.z,
                nil
            )
        end

        if gNetworkPlayers[0].globalIndex ~= dataTable.globalIndex then return end

        if dataTable.yoshi then
            set_health(0)
        else
            set_health(get_health() - gWeaponTable[dataTable.weaponId].damage)
        end
    elseif dataTable.packet == PACKET_SOUND then
        if gNetworkPlayers[0].currLevelNum == dataTable.level and gNetworkPlayers[0].currAreaIndex == dataTable.area and gNetworkPlayers[0].currActNum == dataTable.act then
            -- audio_sample_stop(gSoundTable[dataTable.sound])
            audio_sample_play(gSoundTable[dataTable.sound], { x = dataTable.x, y = dataTable.y, z = dataTable.z }, dataTable.volume)
        end
    end
end


--------------
-- commands --
--------------

local function on_fp_command()
    set_first_person_enabled(not gFirstPersonCamera.enabled)

    djui_chat_message_create("[Gun Mod] First person mode status: " .. on_or_off(gFirstPersonCamera.enabled))
    return true
end

local function on_fov_command(msg)
    local fov = tonumber(msg)
    if fov ~= nil then
        if fov <= 0 then
            fov = FIRST_PERSON_DEFAULT_FOV
        end
        mod_storage_save_number("fov", fov)
        gFirstPersonCamera.fov = fov
        djui_chat_message_create("[Gun Mod] Set FOV to " .. fov)
        return true
    end

    djui_chat_message_create("/gm \\#00ffff\\fov\\#ffff00\\ [number]\\#ffffff\\\nSets the first person camera FOV, default is \\#ffff00\\70\\#ffffff\\")
    return true
end

local function on_give_command(msg)
    -- if not network_is_server() and not network_is_moderator() then
    --     djui_chat_message_create("\\#ffa0a0\\You do not have permission to run this command.")
    --     return true
    -- end

    if not gGlobalSyncTable.gunModEnabled then
        djui_chat_message_create("\\#ffa0a0\\[Gun Mod] You need to enable Gun Mod to give yourself a weapon.")
        return true
    end

    for id, weapon in pairs(gWeaponTable) do
        if weapon.name:lower() == msg:lower() then
            pickup_weapon(id)
            local text = string.format("[Gun Mod] Gave %s %s", name_without_hex(gNetworkPlayers[0].name), weapon.name)
            djui_chat_message_create(text)
            return true
        end
    end

    djui_chat_message_create("/gm \\#00ffff\\give\\#ffff00\\ " .. get_weapon_list_string() .. "\\#ffffff\\\nGives yourself a gun")
    return true
end

local function on_gm_command(msg)
    local args = split(msg)
    if args[1] == "fp" then
        return on_fp_command()
    elseif args[1] == "fov" then
        return on_fov_command(args[2] or "")
    elseif args[1] == "give" then
        return on_give_command(args[2] or "")
    end

    if msg:gsub("%s+", "") == "" and (network_is_server() or network_is_moderator()) then
        gGlobalSyncTable.gunModEnabled = not gGlobalSyncTable.gunModEnabled
        djui_chat_message_create("[Gun Mod] Status: " .. on_or_off(gGlobalSyncTable.gunModEnabled))
    else
        djui_chat_message_create("/gm \\#00ffff\\[fp|fov|give]\\#7f7f7f\\ (leave blank to toggle Gun Mod on or off)")
    end
    return true
end

smlua_text_utils_dialog_replace(DIALOG_167, 1, 4, 30, 200, "Welcome to Gun Mod. After\
4 months in development,\
hopefully it will have\
been worth the wait.\
This mod has actually been\
in development for 16\
months, but progress was\
pretty slow until recently.\
I decided to rewrite the\
rewrite to make this\
mod's code less of a\
total mess.\
-- TUTORIAL --\
Press X to shoot\
Press Y to reload\
Run slash gm help\
Princess Toadstool's\
castle is just ahead.\
\
\
Press [A] to jump, [Z] to\
crouch, and [B] to punch,\
read a sign, or grab\
something.\
Press [B] again to throw\
something you're holding.")

gServerSettings.playerInteractions = PLAYER_INTERACTIONS_PVP

_G.gunModApi = {
    enable_gun_mod = enable_gun_mod,
    get_render_hud = get_render_hud,
    set_render_hud = set_render_hud,
    get_weapon = get_weapon,
    weapon_register = weapon_register,
    weapon_unregister = weapon_unregister,
    weapon_unregister_all = weapon_unregister_all,
    get_weapon_list_string = get_weapon_list_string,
    obj_set_weapon_params = obj_set_weapon_params,
    obj_get_weapon_owner = obj_get_weapon_owner,
    obj_get_weapon_id = obj_get_weapon_id,
    obj_get_weapon_dual_wield = obj_get_weapon_dual_wield,
    obj_get_weapon_extra = obj_get_weapon_extra,
    cur_weapon = cur_weapon,
    cur_dual_wield_weapon = cur_dual_wield_weapon,
    get_inventory_slot = get_inventory_slot,
    set_inventory_slot = set_inventory_slot,
    pickup_weapon = pickup_weapon,
    get_health = get_health,
    set_health = set_health,
    common_shoot = common_shoot,
    common_reload = common_reload,
    bullet_ricochet = bullet_ricochet,
    obj_generate_hitbox_multiply_func = obj_generate_hitbox_multiply_func,
    obj_generate_health_func = obj_generate_health_func,
    shootable_register = shootable_register
}

local fov = mod_storage_load_number("fov")
if fov == 0 then
    fov = FIRST_PERSON_DEFAULT_FOV
    mod_storage_save_number("fov", fov)
end
gFirstPersonCamera.fov = fov

if START_IN_FIRST_PERSON then
    set_first_person_enabled(true)
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_ON_PACKET_RECEIVE, on_packet_receive)
hook_event(HOOK_ON_HUD_RENDER_BEHIND, on_hud_render_behind)

gm_hook_behavior(id_bhvMessagePanel, false, obj_sign_hitbox)
gm_hook_behavior(id_bhvExclamationBox, false, nil, obj_generate_hitbox_multiply_func(1, 1.8))
gm_hook_behavior(id_bhvBreakableBox, false, obj_generate_health_func(HEALTH_BREAKABLE_BOX))
gm_hook_behavior(id_bhvBowlingBall, false, obj_generate_health_func(HEALTH_BOWLING_BALL))
gm_hook_behavior(id_bhvWaterBomb, false, nil, obj_generate_hitbox_multiply_func(1, 2))
gm_hook_behavior(id_bhvChainChomp, false, nil, obj_generate_hitbox_multiply_func(1.5, 1.5))
gm_hook_behavior(id_bhvHomingAmp, false, nil, obj_amp_hitbox)
gm_hook_behavior(id_bhvCirclingAmp, false, nil, obj_amp_hitbox)
gm_hook_behavior(id_bhvFlyGuy, false, nil, obj_generate_hitbox_multiply_func(0.75, 1.75))
gm_hook_behavior(id_bhvChuckya, false, obj_chuckya_hitbox)
gm_hook_behavior(id_bhvSnufit, false, nil, obj_snufit_hitbox)
gm_hook_behavior(id_bhvSpindrift, false, nil, obj_generate_hitbox_multiply_func(0.75, 2))
gm_hook_behavior(id_bhvKingBobomb, false, obj_king_bobomb_hitbox)
gm_hook_behavior(id_bhvBowser, false, obj_generate_health_func(HEALTH_BOWSER))

gm_hook_behavior(id_bhvStaticObject, false, obj_skip_in_view_check)

hook_chat_command("gm", "\\#00ffff\\[fp|fov|give]\\#7f7f7f\\ (leave blank to toggle Gun Mod on or off)", on_gm_command)

-- matches the function(s) below
for i = 0, MAX_PLAYERS - 1 do
    gPlayerSyncTable[i].curWeapon = WEAPON_MAGNUM
    gPlayerSyncTable[i].curWeapon2 = WEAPON_PISTOL
end

pickup_weapon(WEAPON_MAGNUM)
pickup_weapon(WEAPON_PISTOL)