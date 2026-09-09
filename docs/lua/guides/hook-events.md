## [:rewind: Lua Reference](../lua.md)

## [Hook Event Types](#Hook-Event-Types)

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
| HOOK_ON_LEVEL_INIT | Called when the level is initialized | `integer` type, `integer` levelNum, `integer` areaIdx, `integer` nodeId, `integer` arg |
| HOOK_ON_WARP | Called when the local player warps | `integer` type, `integer` levelNum, `integer` areaIdx, `integer` nodeId, `integer` arg |
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
| HOOK_OBJECT_SET_MODEL | Called when a behavior changes models. Also runs when a behavior spawns | [Object](../structs.md#Object) obj, `integer` modelID, `integer` modelExtendedId |
| HOOK_CHARACTER_SOUND | Called when mario retrieves a character sound to play, return a character sound or `0` to override it | [MarioState](../structs.md#MarioState) mario, [enum CharacterSound](../constants.md#enum-CharacterSound) characterSound |
| HOOK_BEFORE_SET_MARIO_ACTION | Called before Mario's action changes Return an action to change the incoming action or `1` to cancel the action change | [MarioState](../structs.md#MarioState) mario, `integer` incomingAction, `integer` actionArg |
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
| HOOK_ON_NAMETAGS_RENDER | Called when nametags are rendered. Return a table with `name` and/or `pos` to override the nametag text and/or position. | `integer` playerIndex, `Vec3f` pos |
| HOOK_ON_DJUI_THEME_CHANGED | Called when the DJUI theme is changed. Run `djui_menu_get_theme()` to get the new theme. | None |
| HOOK_ON_GEO_PROCESS | Called when a GeoLayout is processed **Note:** You must set the `hookProcess` field of the graph node to a non-zero value | [GraphNode](../structs.md#GraphNode) graphNode, `integer` matStackIndex |
| HOOK_BEFORE_GEO_PROCESS | Called before a GeoLayout is processed **Note:** You must set the `hookProcess` field of the graph node to a non-zero value | [GraphNode](../structs.md#GraphNode) graphNode, `integer` matStackIndex |
| HOOK_ON_GEO_PROCESS_CHILDREN | Called when the children of a GeoLayout node is processed **Note:** You must set the `hookProcess` field of the parent graph node to a non-zero value | [GraphNode](../structs.md#GraphNode) graphNode, `integer` matStackIndex |
| HOOK_MARIO_OVERRIDE_GEOMETRY_INPUTS | Called before running Mario's geometry input logic, return `false` to not run it. | [MarioState](../structs.md) m |
| HOOK_ON_INTERACTIONS | Called when the Mario interactions are processed | [MarioState](../structs.md#MarioState) mario |
| HOOK_ALLOW_FORCE_WATER_ACTION | Called when executing a non-water action while under the water's surface, or vice versa. Return `false` to prevent the player from being forced out of the action at the water's surface | [MarioState](../structs.md#MarioState) mario, `boolean` isInWaterAction |
| HOOK_BEFORE_WARP | Called before the local player warps. Return a table with `destLevel`, `destArea`, `destWarpNode`, to override the warp | `integer` destLevel, `integer` destArea, `integer` destWarpNode, `integer` arg |
| HOOK_ON_INSTANT_WARP | Called when the local player goes through an instant warp.| `integer` area, `integer` id, `Vec3s` displacement|
| HOOK_MARIO_OVERRIDE_FLOOR_CLASS | Called when Mario's floor class logic updates, return a `SURFACE_CLASS_*` constant to override the type. | [MarioState](../structs.md#MarioState) mario, `integer` surfaceClass |
| HOOK_ON_ADD_SURFACE | Called when collision surfaces are added. | [Surface](../structs.md#Surface) surface, `boolean` dynamic |
| HOOK_ON_CLEAR_AREAS | Called when a level's areas are unloaded. | None |
| HOOK_ON_FIND_WALL_COLLISION | Called after wall collision detection completes. You can modify the `colData` fields directly. Return a number to override `numCollisions` | `number` posX, `number` posY, `number` posZ, [WallCollisionData](../structs.md#WallCollisionData) colData |
| HOOK_ON_FIND_CEIL | Called after ceiling detection completes. Return `height` to override height, or `height, surface` to override both | `number` posX, `number` posY, `number` posZ, [Surface](../structs.md#Surface) ceil, `number` height |
| HOOK_ON_FIND_FLOOR | Called after floor detection completes. Return `height` to override height, or `height, surface` to override both | `number` posX, `number` posY, `number` posZ, [Surface](../structs.md#Surface) floor, `number` height |
| HOOK_ON_FIND_WATER_LEVEL | Called after water level detection completes. Return a number to override the water level | `number` x, `number` z, `number` waterLevel |
| HOOK_ON_FIND_POISON_GAS_LEVEL | Called after poison gas level detection completes. Return a number to override the gas level | `number` x, `number` z, `number` gasLevel |
| HOOK_ON_FIND_SURFACE_ON_RAY | Called after ray-surface intersection completes. Return `surface` to override the hit surface, or `surface, hitPos` to override both | `Vec3f` orig, `Vec3f` dir, [Surface](../structs.md#Surface) hitSurface, `Vec3f` hitPos |
| HOOK_ON_DYNOS_PACK_TOGGLED | Called after a DynOS pack is toggled | `string` dynosPackName, `boolean` enabled |
| HOOK_BEFORE_PLAY_MODE_UPDATE | Called before the play mode is ran. Return a number to override the play mode to be ran. | `number` playMode |
| HOOK_ON_PLAY_MODE_UPDATE | Called after the play mode is ran. Return a number to override the change level. | `number` playMode |
