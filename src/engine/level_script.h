#ifndef LEVEL_SCRIPT_H
#define LEVEL_SCRIPT_H

#include <PR/ultratypes.h>

#define MAX_PAINTING_WARP_NODES 45

struct LevelCommand;

extern struct DynamicPool *gLevelPool;

extern s32 gLevelScriptModIndex;
extern LevelScript* gLevelScriptActive;

extern u8 level_script_entry[];

/* |description|
Creates a warp node in the current level and area with id `id` that goes to the warp node `destNode` in level `destLevel` and area `destArea`, and attach it to the object `o`.
To work properly, object `o` must be able to trigger a warp (for example, with interact type set to `INTERACT_WARP`.)
`checkpoint` should be set only to WARP_NO_CHECKPOINT (0x00) or WARP_CHECKPOINT (0x80.) If `checkpoint` is set to `0x80`, Mario will warp directly to this node if he enters the level again (after a death for example)
|descriptionEnd| */
struct ObjectWarpNode *area_create_warp_node(u8 id, u8 destLevel, u8 destArea, u8 destNode, u8 checkpoint, struct Object *o);

struct LevelCommand *level_script_execute(struct LevelCommand *cmd);

#endif // LEVEL_SCRIPT_H
