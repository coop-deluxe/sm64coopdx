if SM64COOPDX_VERSION == nil then return end

--- @param weapon Weapon
--- @return nil
function common_shoot(weapon)
    --- @type MarioState
    local m = gMarioStates[0]

    if not weapon.reqCheck(m) then return end

    if weapon.ammo <= 0 and weapon.maxAmmo > 0 then
        audio_sample_play(SOUND_CUSTOM_DRY, gMarioStates[0].pos, 1)
        return
    end

    local enabled = get_first_person_enabled()
    local x = if_then_else(enabled, gLakituState.pos.x, m.pos.x)
    local y = if_then_else(enabled, gLakituState.pos.y, m.pos.y + FIRST_PERSON_MARIO_HEAD_POS_SHORT)
    local z = if_then_else(enabled, gLakituState.pos.z, m.pos.z)

    spawn_bullets_player(x, y, z, weapon.bulletCount)
    if #weapon.primarySounds > 0 then
        sync_audio_sample_play(weapon.primarySounds[math.random(#weapon.primarySounds)], gMarioStates[0].pos, 1)
    end

    if weapon.maxAmmo > 0 then
        weapon.ammo = weapon.ammo - 1
        if weapon.ammo == 0 then common_reload(weapon) end
    end

    useDualWieldWeapon = not useDualWieldWeapon
end

--- @param weapon Weapon
--- @return nil
function common_reload(weapon)
    --- @type MarioState
    local m = gMarioStates[0]
    if weapon.reloadTimer > 0 or not weapon.reqCheck(m) then return end

    local weapon2 = if_then_else(useDualWieldWeapon, cur_weapon(), cur_dual_wield_weapon())
    if weapon.ammo >= weapon.maxAmmo then
        weapon.cooldownTimer = 0
        if weapon2 ~= nil then
            if weapon2.ammo >= weapon2.maxAmmo then
                weapon2.cooldownTimer = 0
            else
                if #weapon.secondarySounds > 0 then
                    sync_audio_sample_play(weapon.secondarySounds[math.random(#weapon.secondarySounds)], m.pos, 1)
                end
                weapon2.ammo = 0
                weapon2.reloadTimer = weapon2.reloadTime
            end
        end
        return
    end

    if weapon2 ~= nil then
        if weapon2.ammo >= weapon2.maxAmmo then
            weapon2.cooldownTimer = 0
        else
            if #weapon.secondarySounds > 0 then
                sync_audio_sample_play(weapon.secondarySounds[math.random(#weapon.secondarySounds)], m.pos, 1)
            end
            weapon2.ammo = 0
            weapon2.reloadTimer = weapon2.reloadTime
        end
    end

    if #weapon.secondarySounds > 0 then
        sync_audio_sample_play(weapon.secondarySounds[math.random(#weapon.secondarySounds)], m.pos, 1)
    end
    weapon.ammo = 0
    weapon.reloadTimer = weapon.reloadTime
end

--- @param m MarioState
function check_common_gun_requirements(m)
    return m.health > 0xFF and
        m.action ~= ACT_STAR_DANCE_EXIT and
        m.action ~= ACT_STAR_DANCE_NO_EXIT and
        m.action ~= ACT_STAR_DANCE_WATER and
        m.action ~= ACT_LEDGE_GRAB and
        m.action ~= ACT_LEDGE_CLIMB_FAST and
        m.action ~= ACT_LEDGE_CLIMB_SLOW_1 and
        m.action ~= ACT_LEDGE_CLIMB_SLOW_2 and
        (m.action & ACT_GROUP_MASK) ~= ACT_GROUP_SUBMERGED and
        m.action ~= ACT_DISAPPEARED
end