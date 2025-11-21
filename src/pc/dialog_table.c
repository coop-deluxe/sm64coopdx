#include "dialog_table.h"
#include "pc/lua/smlua.h"
#include "dialog_ids.h"
#include "PR/ultratypes.h"
#include "game/segment2.h"
#include "pc/lua/utils/smlua_text_utils.h"
#include "game/memory.h"
#include "game/level_info.h"
#include "pc/platform.h"
#include <stdlib.h>

DialogTable *gDialogTable = NULL;

void dialog_table_init(void) {
    gDialogTable = growing_array_init(gDialogTable, 256, malloc, free);

    for (u32 i = 0; i < DIALOG_COUNT; i++) {
        const struct DialogEntry* dialogOrig = smlua_text_utils_dialog_get_unmodified(i);
        struct DialogEntry* dialog = dialog_table_alloc(NULL);

        if (!dialog) {
            sys_fatal("Failed to allocate DialogEntry for dialog ID %d", i);
        }

        memcpy(dialog, dialogOrig, sizeof(struct DialogEntry));
        dialog->text = convert_string_sm64_to_ascii(NULL, dialog->str);
    }
}

struct DialogEntry* dialog_table_alloc(s32 *dialogId) {
    DialogTable *table = gDialogTable;

    if (table->count >= MAX_ALLOCATED_DIALOGS) {
        LOG_LUA_LINE_WARNING("Dialog limit reached! (%d max)", MAX_ALLOCATED_DIALOGS);
        if (dialogId) *dialogId = DIALOG_NONE;
        return NULL;
    }

    struct DialogEntry* dialog = growing_array_alloc(table, sizeof(struct DialogEntry));

    if (!dialog) {
        LOG_LUA_LINE_WARNING("Failed to allocate DialogEntry");
        if (dialogId) *dialogId = DIALOG_NONE;
        return NULL;
    }

    if (dialogId) *dialogId = table->count - 1;

    return dialog;
}

struct DialogEntry* dialog_table_get(s32 dialogId) {
    if (!IS_VALID_DIALOG(dialogId)) {
        return NULL;
    }

    return gDialogTable->buffer[dialogId];
}

void dialog_table_reset(void) {
    DialogTable *table = gDialogTable;

    if (!table) return;

    for (u32 i = 0; i < table->count; i++) {
        struct DialogEntry *dialog = table->buffer[i];

        if (!dialog->replaced) continue;

        if (!IS_CUSTOM_DIALOG(i)) {
            smlua_text_utils_dialog_restore(i);
        } else {
            free((u8*)dialog->str);
            free(dialog->text);
            free(dialog);
            table->buffer[i] = NULL;
        }
    }

    table->count = DIALOG_COUNT;
}

void dialog_table_shutdown(void) {
    DialogTable *table = gDialogTable;

    if (!table) return;

    dialog_table_reset();

    for (u32 i = 0; i < DIALOG_COUNT; i++) {
        struct DialogEntry *dialog = table->buffer[i];

        free(dialog->text);
        free(dialog);
    }

    free(table->buffer);
    free(table);
    gDialogTable = NULL;
}