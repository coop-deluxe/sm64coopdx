#ifndef DIALOG_TABLE_H
#define DIALOG_TABLE_H

#include "PR/ultratypes.h"
#include "game/ingame_menu.h"

#define MAX_ALLOCATED_DIALOGS 0x8000

typedef struct GrowingArray DialogTable;

void dialog_table_init(void);
struct DialogEntry* dialog_table_alloc(s32 *dialogId);
struct DialogEntry* dialog_table_get(s32 dialogId);
void dialog_table_reset(void);
void dialog_table_shutdown(void);

extern DialogTable *gDialogTable;

#define IS_CUSTOM_DIALOG(dialogId) ((dialogId) >= DIALOG_COUNT)
#define IS_VALID_DIALOG(dialogId) ((dialogId) >= 0 && (u32)(dialogId) < gDialogTable->count)
#define IS_VALID_VANILLA_DIALOG(dialogId) ((dialogId) >= 0 && (dialogId) < DIALOG_COUNT)

#endif
