## [:rewind: Lua Reference](lua.md)

# Hooks
Hooks are a way for SM64 to trigger Lua code, whereas the functions listed in [functions](functions.md) allow Lua to trigger SM64 code.

# Supported Hooks
- [hook_behavior](#hook_behavior)
- [hook_chat_command](#hook_chat_command)
- [hook_event](#hook_event)
- [hook_mario_action](#hook_mario_action)
- [hook_on_sync_table_change](#hook_on_sync_table_change)

<br />

## [hook_behavior](#hook_behavior)
`hook_behavior()` allows Lua mods to override existing behaviors or create new ones.

### Parameters

| Field | Type | Notes |
| ----- | ---- | ----- |
| behaviorId | [enum BehaviorId](constants.md#enum-BehaviorId) | Set to `nil` to create a new behavior |
| objectList | [enum ObjectList](constants.md#enum-ObjectList) |  |
| replaceBehavior | `bool` | Prevents the original behavior code from running |
| initFunction | `Lua Function` ([Object](structs.md#Object) obj) | Runs once per object |
| loopFunction | `Lua Function` ([Object](structs.md#Object) obj) | Runs once per frame per object |

### Returns
- [enum BehaviorId](constants.md#enum-BehaviorId)

### Lua Example

```lua
function bhv_example_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    network_init_object(obj, true, nil)
end

function bhv_example_loop(obj)
    obj.oPosY = obj.oPosY + 1
end

id_bhvExample = hook_behavior(0, OBJ_LIST_DEFAULT, bhv_example_init, bhv_example_loop)
```

[:arrow_up_small:](#)

<br />

## [hook_chat_command](#hook_chat_command)
`hook_chat_command()` allows Lua mods to react and respond to chat commands. Chat commands start with the `/` character. The function the mod passes to the hook should return `true` when the command was valid and `false` otherwise.

### Parameters

| Field | Type |
| ----- | ---- |
| command | `string` |
| description | `string` |
| func | `Lua Function` (`string` message) -> `bool` |

### Lua Example

```lua
function on_test_command(msg)
    if msg == 'on' then
        djui_chat_message_create('Test: enabled')
        return true
    elseif msg == 'off' then
        djui_chat_message_create('Test: disabled')
        return true
    end
    return false
end

hook_chat_command('test', "[on|off] turn test on or off", on_hide_and_seek_command)
```

[:arrow_up_small:](#)

<br />

## [hook_event](#hook_event)

The lua functions sent to `hook_event()` will be automatically called by SM64 when certain events occur.

### [Hook Event Types](#Hook-Event-Types)
| Type | Description | Parameters |
| :--- | :---------- | :--------- |
| HOOK_UPDATE | Called once per frame | None |
| HOOK_MARIO_UPDATE | Called once per player per frame at the end of a mario update | [MarioState](structs.md#MarioState) mario |
| HOOK_BEFORE_MARIO_UPDATE | Called once per player per frame at the beginning of a mario update | [MarioState](structs.md#MarioState) mario |
| HOOK_ON_SET_MARIO_ACTION | Called every time a player's current action is changed | [MarioState](structs.md#MarioState) mario |
| HOOK_BEFORE_PHYS_STEP | Called once per player per frame before physics code is run | [MarioState](structs.md#MarioState) mario |
| HOOK_ALLOW_PVP_ATTACK | Called when one player attacks another, return `true` to allow the attack | [MarioState](structs.md#MarioState) attacker, [MarioState](structs.md#MarioState) victim |
| HOOK_ON_PVP_ATTACK | Called when one player attacks another | [MarioState](structs.md#MarioState) attacker, [MarioState](structs.md#MarioState) victim |
| HOOK_ON_PLAYER_CONNECTED | Called when a player connects | [MarioState](structs.md#MarioState) connector |
| HOOK_ON_PLAYER_DISCONNECTED | Called when a player disconnects | [MarioState](structs.md#MarioState) disconnector |
| HOOK_ON_HUD_RENDER | Called when the HUD is being rendered | None |
| HOOK_ALLOW_INTERACT | Called before mario interacts with an object, return `true` to allow the interaction | [MarioState](structs.md#MarioState) interactor, [Object](structs.md#Object) interactee, [enum InteractionType](constants.md#enum-InteractionType) interactType |
| HOOK_ON_INTERACT | Called when mario interacts with an object | [MarioState](structs.md#MarioState) interactor, [Object](structs.md#Object) interactee, [enum InteractionType](constants.md#enum-InteractionType) interactType, bool interactValue |
| HOOK_ON_LEVEL_INIT | Called when the level is initialized | None |
| HOOK_ON_WARP | Called when the local player warps | None |
| HOOK_ON_SYNC_VALID | Called when the current area is synchronized | None |
| HOOK_ON_OBJECT_UNLOAD | Called when any object is unloaded | [Object](structs.md#Object) unloadedObject |
| HOOK_ON_SYNC_OBJECT_UNLOAD | Called when any networked object is unloaded | [Object](structs.md#Object) unloadedObject |
| HOOK_ON_PAUSE_EXIT | Called when the local player exits through the pause screen, return `false` to prevent the exit |  `boolean` usedExitToCastle |
| HOOK_GET_STAR_COLLECTION_DIALOG | Called when the local player collects a star, return a [DialogId](constants.md#enum-DialogId) to show a message | None |
| HOOK_ON_SET_CAMERA_MODE | Called when the camera mode gets set, return `false` to prevent the camera mode from being set | [Camera](structs.md#Camera), `integer` mode, `integer` frames |
| HOOK_ON_OBJECT_RENDER | Called right before an object is rendered. **Note:** You must set the `hookRender` field of the object to a non-zero value | [Object](structs.md#Object) renderedObj |
| HOOK_ON_DEATH | Called when the local player dies, return `false` to prevent normal death sequence | [MarioState](structs.md#MarioState) localMario |
| HOOK_ON_PACKET_RECEIVE | Called when the mod receives a packet that used `network_send()` or `network_send_to()` | `table` dataTable |
| HOOK_USE_ACT_SELECT | Called when the level changes, return `true` to show act selection screen and `false` otherwise | `integer` levelNum |
| HOOK_ON_CHANGE_CAMERA_ANGLE | Called when the player changes the camera mode to Lakitu cam or Mario cam, return `false` to prevent the change. | `integer` mode |
| HOOK_ON_SCREEN_TRANSITION | Called when the game is about to play a transition, returun `false` to prevent the transition from playing. | `integer` type |

### Parameters

| Field | Type |
| ----- | ---- |
| hook_event_type | [HookEventType](#Hook-Event-Types) |
| func | `Lua Function` (`...`) |

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
| action_id | `integer` |
| func | Table with entries for [Action Hook Types](#action-hook-types) of `Lua Function` ([MarioState](structs.md#MarioState) m) |
| interaction_type | [enum InteractionFlag](constants.md#enum-InteractionFlag) <optional> |

#### [Action Hook Types](#action-hook-types)

| Type | Description | Returns |
| :--- | :---------- | :------ |
| every_frame | Main action code, called once per frame | `true` if action cancelled, else `false` |
| gravity | Called inside `apply_gravity` when in action | Unused |

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

    return 0
end

function act_wall_slide_gravity(m)
    m.vel.y = m.vel.y - 2

    if m.vel.y < -15 then
        m.vel.y = -15
    end
end

function mario_on_set_action(m)
    -- wall slide
    if m.action == ACT_SOFT_BONK then
        m.faceAngle.y = m.faceAngle.y + 0x8000
        set_mario_action(m, ACT_WALL_SLIDE, 0)
    end
end

hook_event(HOOK_ON_SET_MARIO_ACTION, mario_on_set_action)
hook_mario_action(ACT_WALL_SLIDE, { every_frame = act_wall_slide, gravity = act_wall_slide_gravity } )
```

[:arrow_up_small:](#)

<br />

## [hook_on_sync_table_change](#hook_on_sync_table_change)
`hook_on_sync_table_change()` allows Lua mods to react to sync table changes.
 - `syncTable` parameter must be a sync table, e.g. [gGlobalSyncTable](globals.md#gGlobalSyncTable), [gPlayerSyncTable[]](globals.md#gPlayerSyncTable), or one of their child tables.
 - `field` parameter must be one of the fields in the `SyncTable`.
 - `tag` parameter can be any type, and is automatically passed to the callback.
 - `func` parameter must be a function with three parameters: `tag`, `oldVal`, and `newVal`.
   - `tag` will be the same `tag` passed into `hook_on_sync_table_change()`.
   - `oldVal` will be the value before it was set.
   - `newVal` will be the value that it was set to.

### Parameters

| Field | Type |
| ----- | ---- |
| syncTable | `SyncTable` |
| field | `value` |
| tag | `value` |
| func | `Lua Function` (`value` tag, `value` oldValue, `value` newValue) |

### Lua Example

```lua
function on_testing_field_changed(tag, oldVal, newVal)
    print('testingField changed:', tag, ',', oldVal, '->', newVal)
end

hook_on_sync_table_change(gGlobalSyncTable, 'testingField', 'tag', on_testing_field_changed)

-- now when testingField is set, either locally or over the network, on_testing_field_changed() will be called
gGlobalSyncTable.testingField = 'hello'

```

[:arrow_up_small:](#)
