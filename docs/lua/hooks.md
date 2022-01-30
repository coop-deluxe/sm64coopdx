## [:rewind: Lua Reference](lua.md)

# Hooks
Hooks are a way for SM64 to trigger Lua code, whereas the functions listed in [functions](functions.md) allow Lua to trigger SM64 code.

<br />

## [Hook Event Types](#Hook-Event-Types)
| Type | Description | Parameters |
| :--- | :---------- | :--------- |
| HOOK_UPDATE | Called once per frame | None |
| HOOK_MARIO_UPDATE | Called once per player per frame at the end of a mario update | [MarioState](structs.md#MarioState) |
| HOOK_BEFORE_MARIO_UPDATE | Called once per player per frame at the beginning of a mario update | [MarioState](structs.md#MarioState) |
| HOOK_ON_SET_MARIO_ACTION | Called every time a player's current action is changed | [MarioState](structs.md#MarioState) |
| HOOK_BEFORE_PHYS_STEP | Called once per player per frame before physics code is run | [MarioState](structs.md#MarioState) |

<br />

## [hook_event](#hook_event)

The lua functions sent to `hook_event()` will be automatically called by SM64 when certain events occur.

### Parameters

| Field | Type |
| ----- | ---- |
| hook_event_type | [HookEventType](#Hook-Event-Types) |
| func | Lua Function |

### Lua Example

The following example will print out a message 16 times per frame (once for every possible player).
```lua
function mario_update(m)
    print('Mario update was called for player index ', m.playerIndex)
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
```

[:arrow_up_small:](#)

<br />

## [hook_mario_action](#hook_mario_action)
`hook_mario_action()` allows Lua mods to create new actions or override existing ones.

### Parameters

| Field | Type |
| ----- | ---- |
| action_id | integer |
| func | Lua Function |

### Lua Example

```lua

ACT_WALL_SLIDE = (0x0BF | ACT_FLAG_AIR | ACT_FLAG_MOVING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)

function act_wall_slide(m)
    if (m.input & INPUT_A_PRESSED) ~= 0 then
        local rc = set_mario_action(m, ACT_TRIPLE_JUMP, 0)
        m.vel.y = 72.0

        if m.forwardVel < 20.0 then
            m.forwardVel = 20.0
        end
        m.wallKickTimer = 0
        return rc
    end

    -- attempt to stick to the wall a bit. if it's 0, sometimes you'll get kicked off of slightly sloped walls
    mario_set_forward_vel(m, -1.0)

    m.particleFlags = m.particleFlags | PARTICLE_DUST

    play_sound(SOUND_MOVING_TERRAIN_SLIDE + m.terrainSoundAddend, m.marioObj.header.gfx.cameraToObject)
    set_mario_animation(m, MARIO_ANIM_START_WALLKICK)

    if perform_air_step(m, 0) == AIR_STEP_LANDED then
        mario_set_forward_vel(m, 0.0)
        if check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0 then
            return set_mario_action(m, ACT_FREEFALL_LAND, 0)
        end
    end

    m.actionTimer = m.actionTimer + 1
    if m.wall == nil and m.actionTimer > 2 then
        mario_set_forward_vel(m, 0.0)
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    -- gravity
    m.vel.y = m.vel.y + 2

    return 0
end

function mario_on_set_action(m)
    -- wall slide
    if m.action == ACT_SOFT_BONK then
        m.faceAngle.y = m.faceAngle.y + 0x8000
        set_mario_action(m, ACT_WALL_SLIDE, 0)
    end
end

hook_event(HOOK_ON_SET_MARIO_ACTION, mario_on_set_action)
hook_mario_action(ACT_WALL_SLIDE, act_wall_slide)
```

[:arrow_up_small:](#)
