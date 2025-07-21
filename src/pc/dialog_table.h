#ifndef DIALOG_TABLE_H
#define DIALOG_TABLE_H

#include "PR/ultratypes.h"
#include "game/ingame_menu.h"

#define MAX_ALLOCATED_DIALOGS 2147483647 // max s32

typedef struct {
    struct DialogEntry **data;
    s32 size;
    s32 capacity;
} DialogTable;

void dialog_table_init(void);
s32 dialog_table_add(struct DialogEntry *dialog);
struct DialogEntry* dialog_table_get(s32 dialogId);
void dialog_table_reset(void);
void dialog_table_shutdown(void);

extern DialogTable gDialogTable;

#define IS_CUSTOM_DIALOG(dialogId) ((dialogId) >= DIALOG_COUNT)
#define IS_VALID_DIALOG(dialogId) ((dialogId) >= 0 && (dialogId) < gDialogTable.size)

#endif
