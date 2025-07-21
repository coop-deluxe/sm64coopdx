#include "dialog_table.h"
#include "pc/debuglog.h"
#include "pc/lua/smlua.h"
#include "dialog_ids.h"
#include "PR/ultratypes.h"
#include "game/segment2.h"
#include <stdlib.h>

DialogTable gDialogTable;

void dialog_table_init(void) {
    DialogTable *table = &gDialogTable;

    table->capacity = 256;
    table->size = 0;
    table->data = malloc(sizeof(struct DialogEntry*) * table->capacity);

    if (!table->data) {
        LOG_ERROR("Failed to allocate dialog table");
        exit(EXIT_FAILURE);
    }

    void **dialogTableOrig = NULL;

#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            dialogTableOrig = segmented_to_virtual(dialog_table_eu_en_original);
            break;
        case LANGUAGE_FRENCH:
            dialogTableOrig = segmented_to_virtual(dialog_table_eu_fr_original);
            break;
        case LANGUAGE_GERMAN:
            dialogTableOrig = segmented_to_virtual(dialog_table_eu_de_original);
            break;
    }
#else
    dialogTableOrig = segmented_to_virtual(seg2_dialog_original);
#endif

    for (s32 i = 0; i < DIALOG_COUNT; ++i) {
        struct DialogEntry* dialogOrig = segmented_to_virtual(dialogTableOrig[i]);
        struct DialogEntry* dialog = malloc(sizeof(struct DialogEntry));
    
        memcpy(dialog, dialogOrig, sizeof(struct DialogEntry));

        dialog_table_add(dialog);
    }
}

s32 dialog_table_add(struct DialogEntry *dialog) {
    DialogTable *table = &gDialogTable;

    if (table->size >= MAX_ALLOCATED_DIALOGS) {
        LOG_LUA_LINE_WARNING("Dialog limit reached! (%d max)", MAX_ALLOCATED_DIALOGS);
        return -1;
    }

    if (table->size >= table->capacity) {
        s32 newCapacity = table->capacity * 2;
        struct DialogEntry **newData = realloc(table->data, sizeof(struct DialogEntry*) * newCapacity);

        if (!newData) {
            LOG_ERROR("Failed to resize dialog table");
            exit(EXIT_FAILURE);
        }

        table->data = newData;
        table->capacity = newCapacity;
    }

    s32 index = table->size;
    table->data[table->size++] = dialog;

    return index;
}

struct DialogEntry* dialog_table_get(s32 dialogId) {
    if (dialogId >= gDialogTable.size) {
        return NULL;
    }

    return gDialogTable.data[dialogId];
}

void dialog_table_reset(void) {
    DialogTable *table = &gDialogTable;

    for (s32 i = DIALOG_COUNT; i < table->size; i++) {
        struct DialogEntry *dialog = table->data[i];

        free((u8*)dialog->str);
        free(dialog->text);
        free(dialog);
    }

    table->size = DIALOG_COUNT;
}

void dialog_table_shutdown(void) {
    DialogTable *table = &gDialogTable;

    for (s32 i = 0; i < DIALOG_COUNT; i++) {
        free(table->data[i]);
    }

    dialog_table_reset();
    free(table->data);
    table->data = NULL;
    table->size = 0;
    table->capacity = 0;
}