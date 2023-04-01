#include "sm64.h"
#include "types.h"
#include "course_table.h"
#include "game/memory.h"
#include "game/ingame_menu.h"
#include "game/segment2.h"

static bool sReplacedDialog[DIALOG_COUNT] = { 0 };
static bool sReplacedCourseName[COURSE_COUNT+2] = { 0 };
static bool sReplacedActName[(COURSE_RR+2)*6] = { 0 };

static u8* smlua_text_utils_convert(const char* str) {
    s32 len = strlen(str);
    u8* dialogStr = calloc(len + 2, sizeof(u8));
    str_ascii_to_dialog(str, dialogStr, len + 1);
    return dialogStr;
}

void smlua_text_utils_reset_all(void) {
    void **dialogTable = segmented_to_virtual(seg2_dialog_table);

    for (s32 i = 0; i < DIALOG_COUNT; i++) {
        if (!sReplacedDialog[i]) { continue; }
        struct DialogEntry *dialog = segmented_to_virtual(dialogTable[i]);
        free((u8*)dialog->str);
        dialog->str = seg2_dialog_original[i];
        sReplacedDialog[i] = false;
    }

    for (s32 i = 0; i < COURSE_COUNT+2; i++) {
        if (!sReplacedCourseName[i]) { continue; }
        free((u8*)seg2_course_name_table[i]);
        seg2_course_name_table[i] = seg2_course_name_table_original[i];
        sReplacedCourseName[i] = false;
    }

    for (s32 i = 0; i < (COURSE_RR+2)*6; i++) {
        if (!sReplacedActName[i]) { continue; }
        free((u8*)seg2_act_name_table[i]);
        seg2_act_name_table[i] = seg2_act_name_table_original[i];
        sReplacedActName[i] = false;
    }
}

void smlua_text_utils_dialog_replace(enum DialogId dialogId, UNUSED u32 unused, s8 linesPerBox, s16 leftOffset, s16 width, const char* str) {
    if (dialogId >= DIALOG_COUNT) { return; }

    void **dialogTable = segmented_to_virtual(seg2_dialog_table);
    struct DialogEntry *dialog = segmented_to_virtual(dialogTable[dialogId]);

    if (sReplacedDialog[dialogId]) {
        free((u8*)dialog->str);
    }

    dialog->unused = unused;
    dialog->linesPerBox = linesPerBox;
    dialog->leftOffset = leftOffset;
    dialog->width = width;
    dialog->str = smlua_text_utils_convert(str);
    sReplacedDialog[dialogId] = true;
}

void smlua_text_utils_course_acts_replace(s16 courseNum, const char* courseName, const char* act1, const char* act2, const char* act3, const char* act4, const char* act5, const char* act6) {
    if (courseNum <= 0 || courseNum > COURSE_RR) { return; }
    s16 courseOffset = courseNum - 1;

    // replace course name
    if (sReplacedCourseName[courseOffset]) {
        free(seg2_course_name_table[courseOffset]);
    }
    seg2_course_name_table[courseOffset] = smlua_text_utils_convert(courseName);
    sReplacedCourseName[courseOffset] = true;

    // replace act names
    const char* newActs[] = { act1, act2, act3, act4, act5, act6 };
    for (s32 i = 0; i < 6; i++) {
        s32 index = (courseOffset * 6 + i);

        if (sReplacedActName[index]) {
            free(seg2_act_name_table[index]);
        }

        seg2_act_name_table[index] = smlua_text_utils_convert(newActs[i]);
        sReplacedActName[index] = true;
    }
}

void smlua_text_utils_secret_star_replace(s16 courseNum, const char* courseName) {
    if (courseNum <= COURSE_RR || courseNum > COURSE_COUNT) { return; }
    s16 courseOffset = courseNum - 1;

    if (sReplacedCourseName[courseOffset]) {
        free(seg2_course_name_table[courseOffset]);
    }

    seg2_course_name_table[courseOffset] = smlua_text_utils_convert(courseName);
    sReplacedCourseName[courseOffset] = true;
}

void smlua_text_utils_castle_secret_stars_replace(const char* name) {
    s16 courseOffset = COURSE_COUNT;

    if (sReplacedCourseName[courseOffset]) {
        free(seg2_course_name_table[courseOffset]);
    }

    seg2_course_name_table[courseOffset] = smlua_text_utils_convert(name);
    sReplacedCourseName[courseOffset] = true;
}

void smlua_text_utils_extra_text_replace(s16 index, const char* text) {
    if (index < 0 || index > 6) { return; }
    index = (COURSE_RR * 6 + index);

    if (sReplacedActName[index]) {
        free(seg2_act_name_table[index]);
    }

    seg2_act_name_table[index] = smlua_text_utils_convert(text);
    sReplacedActName[index] = true;
}

char* smlua_text_utils_get_language(void) {
    return configLanguage;
}