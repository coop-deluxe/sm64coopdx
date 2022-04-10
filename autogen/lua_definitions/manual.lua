-------------
-- globals --
-------------

--- @type MarioState[]
gMarioStates = {}

--- @type NetworkPlayer[]
gNetworkPlayers = {}

--- @type Character[]
gCharacter = {}

--- @type GlobalTextures
gTextures = {}

--- @type GlobalObjectAnimations
gObjectAnimations = {}

--- @type GlobalObjectCollisionData
gGlobalObjectCollisionData = {}

--- @alias SyncTable table

--- @type SyncTable
gGlobalSyncTable = {}

--- @type SyncTable[]
gPlayerSyncTable = {}

--- @type LevelValues
gLevelValues = {}

--- @type BehaviorValues
gBehaviorValues = {}

---------------
-- constants --
---------------

--- @type integer
COURSE_NONE     = 0
--- @type integer
COURSE_BOB      = 1
--- @type integer
COURSE_WF       = 2
--- @type integer
COURSE_JRB      = 3
--- @type integer
COURSE_CCM      = 4
--- @type integer
COURSE_BBH      = 5
--- @type integer
COURSE_HMC      = 6
--- @type integer
COURSE_LLL      = 7
--- @type integer
COURSE_SSL      = 8
--- @type integer
COURSE_DDD      = 9
--- @type integer
COURSE_SL       = 10
--- @type integer
COURSE_WDW      = 11
--- @type integer
COURSE_TTM      = 12
--- @type integer
COURSE_THI      = 13
--- @type integer
COURSE_TTC      = 14
--- @type integer
COURSE_RR       = 15
--- @type integer
COURSE_BITDW    = 16
--- @type integer
COURSE_BITFS    = 17
--- @type integer
COURSE_BITS     = 18
--- @type integer
COURSE_PSS      = 19
--- @type integer
COURSE_COTMC    = 20
--- @type integer
COURSE_TOTWC    = 21
--- @type integer
COURSE_VCUTM    = 22
--- @type integer
COURSE_WMOTR    = 23
--- @type integer
COURSE_SA       = 24
--- @type integer
COURSE_CAKE_END = 25

-----------
-- hooks --
-----------

--- @param behaviorId BehaviorId
--- @param objectList ObjectList
--- @param replaceBehavior boolean
--- @param initFunction fun(obj:Object)
--- @param loopFunction fun(obj:Object)
--- @return BehaviorId
function hook_behavior(behaviorId, objectList, replaceBehavior, initFunction, loopFunction)
    -- ...
end

--- @param command string
--- @param description string
--- @param func fun(msg:string)
function hook_chat_command(command, description, func)
    -- ...
end

--- @param hookEventType LuaHookedEventType
--- @param func function
function hook_event(hookEventType, func)
    -- ...
end

--- @param actionId integer
--- @param func fun(m:MarioState):integer
--- @param interactionType InteractionFlag
function hook_mario_action(actionId, func, interactionType)
    -- ...
end

--- @param syncTable SyncTable
--- @param field any
--- @param tag any
--- @param func fun(tag:any, oldVal:any, newVal:any)
function hook_on_sync_table_change(syncTable, field, tag, func)
    -- ...
end

---------------
-- functions --
---------------

--- @param t number
--- @return number
function sins(t)
    -- ...
end

--- @param t number
--- @return number
function coss(t)
    -- ...
end

--- @param y number
--- @param x number
--- @return integer
function atan2s(y, x)
    -- ...
end

--- @param objFieldTable table
--- @return nil
function define_custom_obj_fields(objFieldTable)
    -- ...
end

--- @param object Object
--- @param standardSync boolean
--- @param fieldTable table
--- @return nil
function network_init_object(object, standardSync, fieldTable)
    -- ...
end

--- @param object Object
--- @param reliable boolean
--- @return nil
function network_send_object(object, reliable)
    -- ...
end

