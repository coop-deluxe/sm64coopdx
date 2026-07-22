-------------
-- globals --
-------------

--- @type MarioState[]
--- Array of `MarioState`s, from 0 to `MAX_PLAYERS` - 1
--- - Uses the local index, which is different between every player
--- - Index 0 always refers to the local player
gMarioStates = {}

--- @type NetworkPlayer[]
--- Array of `NetworkPlayer`s, from 0 to `MAX_PLAYERS` - 1
--- - Uses the local index, which is different between every player
--- - Index 0 always refers to the local player
gNetworkPlayers = {}

--- @type Mod[]
--- Array of all mods loaded, starting from 0
--- - All mods are loaded in the same order for every player
--- - Index 0 is the first mod in the list (the top of the mod list)
gActiveMods = {}

--- @type Character[]
--- Array of every character, from 0 to `CT_MAX` - 1
--- - The contents or order of the characters can never change
gCharacters = {}

--- @type Controller[]
--- Array of every controller, from 0 to `MAX_PLAYERS` - 1
--- - Uses the local index, which is different between every player
--- - Index 0 always refers to the local player
gControllers = {}

--- @type Pointer_Mat4[]
--- Matrix stack used during geo process
--- - Only has an effect when used in a geo process hook
gMatStack = {}

--- @type Pointer_Mat4[]
--- Matrix stack used during geo process
--- - Only has an effect when used in a geo process hook
gMatStackPrev = {}

--- @type GlobalTextures
--- Struct containing HUD glyph textures
gTextures = {}

--- @type GlobalObjectAnimations
--- Struct containing every object animation
gObjectAnimations = {}

--- @type GlobalObjectCollisionData
--- Struct containing all object collision data
gGlobalObjectCollisionData = {}

--- @type PaintingValues
--- Struct containing all paintings and their fields
gPaintingValues = {}

--- @alias SyncTable table

--- @type SyncTable
--- Any keys added and modified to this table will be synced among everyone.
--- - This shouldn't be used to sync player-specific values; Use `gPlayerSyncTable` for that
--- - Note: Does not support tables as keys
gGlobalSyncTable = {}

--- @type SyncTable[]
--- Array of sync tables. Any change to any sync tables will be synced to everyone else.
--- - This array takes in a local index, however it automatically translates to the global index
--- - Note: Does not support tables as keys
gPlayerSyncTable = {}

--- @type LevelValues
--- Struct containing fields that modify specific gameplay or level properties
gLevelValues = {}

--- @type BehaviorValues
--- Struct containing fields that modify specific object behavior properties
gBehaviorValues = {}

--- @type FirstPersonCamera
--- Struct that contains the fields for the first person camera
gFirstPersonCamera = {}

--- @type LakituState
--- The primary struct that controls the camera
--- - Local player only
gLakituState = {}

--- @type ServerSettings
--- Struct containing the settings for the server
--- - enablePlayersInLevelDisplay and enablePlayerList are not synced
gServerSettings = {}

--- @type NametagsSettings
--- Struct containing the settings for Nametags
gNametagsSettings = {}

--- @type HudDisplay
--- Struct containing the flags for the hud display
gHudDisplay = {}
