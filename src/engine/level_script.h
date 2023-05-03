#ifndef LEVEL_SCRIPT_H
#define LEVEL_SCRIPT_H

#include <PR/ultratypes.h>

#define MAX_PAINTING_WARP_NODES 45

struct LevelCommand;

extern s32 gLevelScriptModIndex;
extern LevelScript* gLevelScriptActive;

extern u8 level_script_entry[];

struct ObjectWarpNode *area_create_warp_node(u8 id, u8 destLevel, u8 destArea, u8 destNode, u8 checkpoint, struct Object *o);

struct LevelCommand *level_script_execute(struct LevelCommand *cmd);

#endif // LEVEL_SCRIPT_H
