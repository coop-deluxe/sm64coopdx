#ifndef DIALOG_TABLE_H
#define DIALOG_TABLE_H

#include <stddef.h>
#include "PR/ultratypes.h"

struct DialogEntry;

typedef struct {
    struct DialogEntry **data;
    size_t size;
    size_t capacity;
} DialogTable;

void dialog_table_init(void);
size_t dialog_table_add(struct DialogEntry *dialog);
struct DialogEntry* dialog_table_get(u32 dialogId);
void dialog_table_reset(void);
void dialog_table_shutdown(void);

extern DialogTable gDialogTable;

#endif
