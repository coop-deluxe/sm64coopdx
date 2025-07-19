#include "dialog_table.h"
#include "pc/debuglog.h"
#include "dialog_ids.h"
#include "PR/ultratypes.h"
#include "game/segment2.h"
#include <stdlib.h>
#include <stdio.h>

DialogTable gDialogTable;

static size_t next_power_of_two(size_t x) {
    if (x == 0) return 1;
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
#if SIZE_MAX > 0xFFFFFFFF
    x |= x >> 32;
#endif
    return x + 1;
}

void dialog_table_init(void) {
    DialogTable *table = &gDialogTable;

    table->capacity = next_power_of_two(DIALOG_COUNT);
    table->size = 0;
    table->data = malloc(sizeof(struct DialogEntry*) * table->capacity);

    if (!table->data) {
        LOG_ERROR("Failed to allocate dialog table");
        exit(EXIT_FAILURE);
    }

    void **dialogTable = NULL;

#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            dialogTable = segmented_to_virtual(dialog_table_eu_en);
            break;
        case LANGUAGE_FRENCH:
            dialogTable = segmented_to_virtual(dialog_table_eu_fr);
            break;
        case LANGUAGE_GERMAN:
            dialogTable = segmented_to_virtual(dialog_table_eu_de);
            break;
    }
#else
    dialogTable = segmented_to_virtual(seg2_dialog_table);
#endif

    for (unsigned int i = 0; i < DIALOG_COUNT; ++i) {
        dialog_table_add(segmented_to_virtual(dialogTable[i]));
    }
}

size_t dialog_table_add(struct DialogEntry *dialog) {
    DialogTable *table = &gDialogTable;

    if (table->size >= table->capacity) {
        size_t newCapacity = table->capacity * 2;
        struct DialogEntry **newData = realloc(table->data, sizeof(struct DialogEntry*) * newCapacity);

        if (!newData) {
            LOG_ERROR("Failed to resize dialog table");
            exit(EXIT_FAILURE);
        }

        table->data = newData;
        table->capacity = newCapacity;
    }

    size_t index = table->size;
    table->data[table->size++] = dialog;

    printf("capacity: %zu\tsize: %zu", table->capacity, table->size);
    return index;
}

struct DialogEntry* dialog_table_get(u32 dialogId) {
    if (dialogId >= gDialogTable.size) {
        LOG_ERROR("dialog_table_get: index %u out of bounds (size = %zu)", dialogId, gDialogTable.size);
        return NULL;
    }
    return gDialogTable.data[dialogId];
}

void dialog_table_reset(void) {
    DialogTable *table = &gDialogTable;

    for (size_t i = DIALOG_COUNT; i < table->size; i++) {
        struct DialogEntry *dialog = table->data[i];

        free((u8*)dialog->str);
        free(dialog->text);
        free(dialog);
    }
    table->size = DIALOG_COUNT;
}

void dialog_table_shutdown(void) {
    DialogTable *table = &gDialogTable;

    dialog_table_reset();
    free(table->data);
    table->data = NULL;
    table->size = 0;
    table->capacity = 0;
}