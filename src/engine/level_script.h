#ifndef LEVEL_SCRIPT_H
#define LEVEL_SCRIPT_H

#include <PR/ultratypes.h>

#define MAX_PAINTING_WARP_NODES 45

struct LevelCommand;

extern struct DynamicPool *gLevelPool;

extern s32 gLevelScriptModIndex;
extern LevelScript* gLevelScriptActive;

extern u8 level_script_entry[];

struct LevelCommand *level_script_execute(struct LevelCommand *cmd);

#endif // LEVEL_SCRIPT_H
