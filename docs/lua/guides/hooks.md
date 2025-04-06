## [:rewind: Lua Reference](../lua.md)

# Hooks
Hooks are a way for SM64 to trigger Lua code, whereas the functions listed in [functions](../functions.md) allow Lua to trigger SM64 code.

# Supported Hooks
- [hook_behavior](#hook_behavior)
- [hook_chat_command](#hook_chat_command)
- [hook_event](#hook_event)
- [hook_mario_action](#hook_mario_action)
- [hook_on_sync_table_change](#hook_on_sync_table_change)
- [hook_mod_menu_text](#hook_mod_menu_text)
- [hook_mod_menu_button](#hook_mod_menu_button)
- [hook_mod_menu_checkbox](#hook_mod_menu_checkbox)
- [hook_mod_menu_slider](#hook_mod_menu_slider)
- [hook_mod_menu_inputbox](#hook_mod_menu_inputbox)

<br />

## [hook_behavior](#hook_behavior)
`hook_behavior()` allows Lua mods to override existing behaviors or create new ones.

### Parameters

| Field | Type | Notes |
| ----- | ---- | ----- |
| behaviorId | [enum BehaviorId](../constants.md#enum-BehaviorId) | Set to `nil` to create a new behavior |
| objectList | [enum ObjectList](../constants.md#enum-ObjectList) |  |
| replaceBehavior | `bool` | Prevents the original behavior code from running |
| initFunction | `Lua Function` ([Object](../structs.md#Object) obj) | Runs once per object |
| loopFunction | `Lua Function` ([Object](../structs.md#Object) obj) | Runs once per frame per object |
| behaviorName | `string` | Optional, name to give to the behavior |

### Returns
- [enum BehaviorId](../constants.md#enum-BehaviorId)

### Lua Example

```lua
function bhv_example_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    network_init_object(obj, true, nil)
end

function bhv_example_loop(obj)
    obj.oPosY = obj.oPosY + 1
end

id_bhvExample = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_example_init, bhv_example_loop, "bhvExample")
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
    if msg == "on" then
        djui_chat_message_create("Test: enabled")
        return true
    elseif msg == "off" then
        djui_chat_message_create("Test: disabled")
        return true
    end
    return false
end

hook_chat_command("test", "[on|off] turn test on or off", on_hide_and_seek_command)
```

[:arrow_up_small:](#)

<br />

## [hook_event](#hook_event)

The lua functions sent to `hook_event()` will be automatically called by SM64 when certain events occur.

### [Hook Event Types](#Hook-Event-Types)
| Type | Description | Parameters |
| :--- | :---------- | :--------- |
| HOOK_UPDATE | Called once per frame | None |
| HOOK_MARIO_UPDATE | Called once per player per frame at the end of a mario update | [MarioState](../structs.md#MarioState) mario |
| HOOK_BEFORE_MARIO_UPDATE | Called once per player per frame at the beginning of a mario update | [MarioState](../structs.md#MarioState) mario |
| HOOK_ON_SET_MARIO_ACTION | Called every time a player's current action is changed | [MarioState](../structs.md#MarioState) mario |
| HOOK_BEFORE_PHYS_STEP | Called once per player per frame before physics code is run, return an integer to cancel it with your own step result | [MarioState](../structs.md#MarioState) mario, `integer` stepType |
| HOOK_ALLOW_PVP_ATTACK | Called when one player attacks another, return `true` to allow the attack | [MarioState](../structs.md#MarioState) attacker, [MarioState](../structs.md#MarioState) victim, `integer` interaction |
| HOOK_ON_PVP_ATTACK | Called when one player attacks another | [MarioState](../structs.md#MarioState) attacker, [MarioState](../structs.md#MarioState) victim, `integer` interaction |
| HOOK_ON_PLAYER_CONNECTED | Called when a player connects | [MarioState](../structs.md#MarioState) connector |
| HOOK_ON_PLAYER_DISCONNECTED | Called when a player disconnects | [MarioState](../structs.md#MarioState) disconnector |
| HOOK_ON_HUD_RENDER | Called when the HUD is being rendered | None |
| HOOK_ON_HUD_RENDER_BEHIND | Called when the HUD is being rendered, every HUD call in this hook renders behind the vanilla HUD | None |
| HOOK_ALLOW_INTERACT | Called before mario interacts with an object, return `true` to allow the interaction | [MarioState](../structs.md#MarioState) interactor, [Object](../structs.md#Object) interactee, [enum InteractionType](../constants.md#enum-InteractionType) interactType |
| HOOK_ON_INTERACT | Called when mario interacts with an object | [MarioState](../structs.md#MarioState) interactor, [Object](../structs.md#Object) interactee, [enum InteractionType](../constants.md#enum-InteractionType) interactType, bool interactValue |
| HOOK_ON_LEVEL_INIT | Called when the level is initialized | None |
| HOOK_ON_WARP | Called when the local player warps | None |
| HOOK_ON_SYNC_VALID | Called when the current area is synchronized | None |
| HOOK_ON_OBJECT_UNLOAD | Called when any object is unloaded | [Object](../structs.md#Object) unloadedObject |
| HOOK_ON_SYNC_OBJECT_UNLOAD | Called when any networked object is unloaded | [Object](../structs.md#Object) unloadedObject |
| HOOK_ON_PAUSE_EXIT | Called when the local player exits through the pause screen, return `false` to prevent the exit |  `boolean` usedExitToCastle |
| HOOK_GET_STAR_COLLECTION_DIALOG | Called when the local player collects a star, return a [DialogId](../constants.md#enum-DialogId) to show a message | None |
| HOOK_ON_SET_CAMERA_MODE | Called when the camera mode gets set, return `false` to prevent the camera mode from being set | [Camera](../structs.md#Camera), `integer` mode, `integer` frames |
| HOOK_ON_OBJECT_RENDER | Called right before an object is rendered **Note:** You must set the `hookRender` field of the object to a non-zero value | [Object](../structs.md#Object) renderedObj |
| HOOK_ON_DEATH | Called when the local player dies, return `false` to prevent normal death sequence | [MarioState](../structs.md#MarioState) localMario |
| HOOK_ON_PACKET_RECEIVE | Called when the mod receives a packet that used `network_send()` or `network_send_to()` | `table` dataTable |
| HOOK_USE_ACT_SELECT | Called when the level changes, return `true` to show act selection screen and `false` otherwise | `integer` levelNum |
| HOOK_ON_CHANGE_CAMERA_ANGLE | Called when the player changes the camera mode to Lakitu cam or Mario cam, return `false` to prevent the change | `integer` mode |
| HOOK_ON_SCREEN_TRANSITION | Called when the game is about to play a transition, return `false` to prevent the transition from playing | `integer` type |
| HOOK_ALLOW_HAZARD_SURFACE | Called once per player per frame. Return `false` to prevent the player from being affected by lava, quicksand, or wind | [MarioState](../structs.md#MarioState) mario, `integer` hazardType |
| HOOK_ON_CHAT_MESSAGE | Called when a chat message gets sent. Return `false` to prevent the message from being sent | [MarioState](../structs.md#MarioState) messageSender, `string` messageSent |
| HOOK_OBJECT_SET_MODEL | Called when a behavior changes models. Also runs when a behavior spawns | [Object](../structs.md#Object) obj, `integer` modelID |
| HOOK_CHARACTER_SOUND | Called when mario retrieves a character sound to play, return a character sound or `0` to override it | [MarioState](../structs.md#MarioState) mario, [enum CharacterSound](../constants.md#enum-CharacterSound) characterSound |
| HOOK_BEFORE_SET_MARIO_ACTION | Called before Mario's action changes Return an action to change the incoming action or `1` to cancel the action change | [MarioState](../structs.md#MarioState) mario, `integer` incomingAction |
| HOOK_JOINED_GAME | Called when the local player finishes the join process (if the player isn't the host) | None |
| HOOK_ON_OBJECT_ANIM_UPDATE | Called when an object's animation is updated | [Object](../structs.md#Object) objNode |
| HOOK_ON_DIALOG | Called when a dialog appears. Return `false` to prevent it from appearing. Return a second parameter as any string to override the text in the textbox | `integer` dialogId |
| HOOK_ON_EXIT | Called before the game shuts down | None |
| HOOK_DIALOG_SOUND | Called when a dialog box sound is going to play, return a `DS_*` constant to override the sound | `integer` dialogSound |
| HOOK_ON_COLLIDE_LEVEL_BOUNDS | Called when a mario collides with the level boundaries | [MarioState](../structs.md#MarioState) mario |
| HOOK_MIRROR_MARIO_RENDER | Called when a Mirror Mario is rendered | [GraphNodeObject](../structs.md#GraphNodeObject) mirrorMario | `integer` mirrorMarioIndex |
| HOOK_MARIO_OVERRIDE_PHYS_STEP_DEFACTO_SPEED | Called when slope defacto speed for walking is being calculated, overrides the floor normal in the equation | [MarioState](../structs.md#MarioState) mario |
| HOOK_ON_OBJECT_LOAD | Called when an object is spawned in | [Object](../structs.md#Object) obj |
| HOOK_ON_PLAY_SOUND | Called when a sound is going to play, return a `SOUND_*` constant or `NO_SOUND` to override the sound | `integer` soundBits, `Vec3f` pos |
| HOOK_ON_SEQ_LOAD | Called when a sequence is going to play, return a `SEQ_*` constant to override the sequence. `SEQ_SOUND_PLAYER` (0) is silence. | `integer` player, `integer` seqID |
| HOOK_ON_ATTACK_OBJECT | Called when a player attacks an object. May be double-fired in some cases, you'll need to write special code for this | [MarioState](../structs.md#MarioState) attacker, [Object](../structs.md#Object) victim, `integer` interactionId |
| HOOK_ON_LANGUAGE_CHANGED | Called when the language is changed | `string` language |
| HOOK_ON_MODS_LOADED | Called directly after every mod file is loaded in by smlua | None |
| HOOK_ON_NAMETAGS_RENDER | Called when nametags are rendered. Return a `string` to change what renders on the nametag, return an empty `string` to render nothing. | `string` playerIndex |
| HOOK_ON_DJUI_THEME_CHANGED | Called when the DJUI theme is changed. Run `djui_menu_get_theme()` to get the new theme. | None |
| HOOK_ON_GEO_PROCESS | Called when a GeoLayout is processed **Note:** You must set the `hookProcess` field of the graph node to a non-zero value | [GraphNode](../structs.md#GraphNode) graphNode, `integer` matStackIndex |
| HOOK_BEFORE_GEO_PROCESS | Called before a GeoLayout is processed **Note:** You must set the `hookProcess` field of the graph node to a non-zero value | [GraphNode](../structs.md#GraphNode) graphNode, `integer` matStackIndex |
| HOOK_ON_GEO_PROCESS_CHILDREN | Called when the children of a GeoLayout node is processed **Note:** You must set the `hookProcess` field of the parent graph node to a non-zero value | [GraphNode](../structs.md#GraphNode) graphNode, `integer` matStackIndex |
| HOOK_ON_INTERACTIONS | Called when the Mario interactions are processed | [MarioState](../structs.md#MarioState) mario |

### Parameters

| Field | Type |
| ----- | ---- |
| hook_event_type | [HookEventType](#Hook-Event-Types) |
| func | `Lua Function` (`...`) |

### Lua Example

The following example will print out a message 16 times per frame (once for every possible player).
```lua
function mario_update(m)
    print("Mario update was called for player index ", m.playerIndex)
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
| func | Table with entries for [Action Hook Types](#action-hook-types) of `Lua Function` ([MarioState](../structs.md#MarioState) m) |
| interaction_type | [enum InteractionFlag](../constants.md#enum-InteractionFlag) <optional> |

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
 - `syncTable` parameter must be a sync table, e.g. [gGlobalSyncTable](../globals.md#gGlobalSyncTable), [gPlayerSyncTable[]](../globals.md#gPlayerSyncTable), or one of their child tables.
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
    print("testingField changed:", tag, ",", oldVal, "->", newVal)
end

hook_on_sync_table_change(gGlobalSyncTable, "testingField", "tag", on_testing_field_changed)

-- now when testingField is set, either locally or over the network on_testing_field_changed() will be called
gGlobalSyncTable.testingField = "hello"
```

[:arrow_up_small:](#)

<br />

## [hook_mod_menu_text](#hook_mod_menu_text)
`hook_mod_menu_text()` allows Lua to add text labels to their designated mod menu submenu.

### Parameters

| Field | Type |
| ----- | ---- |
| message | `string` |

### Lua Example

```lua
hook_mod_menu_text("Rise and shine, Mr. Freeman.")
```

[:arrow_up_small:](#)

<br />

## [hook_mod_menu_button](#hook_mod_menu_button)
`hook_mod_menu_button()` allows Lua to add buttons to their designated mod menu submenu.

### Parameters

| Field | Type |
| ----- | ---- |
| name | `string` |
| func | `Lua Function` (`integer` index) |

### Lua Example

```lua
local menu1Open = false
local menu2Open = false

--- @param index integer
local function on_open_menu(index)
    if index == 0 then
        menu1Open = true
        menu2Open = false
    else
        menu1Open = false
        menu2Open = true
    end
end

-- you can always do separate functions too!
hook_mod_menu_button("Open Menu 1", on_open_menu)
hook_mod_menu_button("Open Menu 2", on_open_menu)
```

[:arrow_up_small:](#)

<br />

## [hook_mod_menu_checkbox](#hook_mod_menu_checkbox)
`hook_mod_menu_checkbox()` allows Lua to add checkboxes to their designated mod menu submenu.

### Parameters

| Field | Type |
| ----- | ---- |
| name | `string` |
| defaultValue | `boolean` |
| func | `Lua Function` (`integer` index, `boolean` value) |

### Lua Example

```lua
local flyMode = false
local noclipMode = false

--- @param index integer
--- @param value boolean
local function on_set_player_mode(index, value)
    if index == 0 then
        flyMode = value
    else
        noclipMode = value
    end
end

-- you can always do separate functions too!
hook_mod_menu_checkbox("Fly Mode", false, on_set_player_mode)
hook_mod_menu_checkbox("Noclip Mode", false, on_set_player_mode)
```

[:arrow_up_small:](#)

<br />

## [hook_mod_menu_slider](#hook_mod_menu_slider)
`hook_mod_menu_slider()` allows Lua to add sliders to their designated mod menu submenu.

### Parameters

| Field | Type |
| ----- | ---- |
| name | `string` |
| defaultValue | `integer` |
| min | `integer` |
| max | `integer` |
| func | `Lua Function` (`integer` index, `integer` value) |

### Lua Example

```lua
local timeScale = 0.0

local function on_set_time_scale(index, value)
    timeScale = value
end

hook_mod_menu_slider("Time Scale", 1, 0, 10, on_set_time_scale)
```

[:arrow_up_small:](#)

<br />

## [hook_mod_menu_inputbox](#hook_mod_menu_inputbox)
`hook_mod_menu_inputbox()` allows Lua to add textboxes to their designated mod menu submenu.

### Parameters

| Field | Type |
| ----- | ---- |
| name | `string` |
| defaultValue | `string` |
| stringLength | `integer` |
| func | `Lua Function` (`integer` index, `string` value) |

### Lua Example

```lua
--- @param index integer
--- @param value string
local function on_set_network_player_description(index, value)
    network_player_set_description(gNetworkPlayers[0], value, 255, 255, 255, 255)
end

hook_mod_menu_inputbox("Network Player Description", on_set_network_player_description)
```
