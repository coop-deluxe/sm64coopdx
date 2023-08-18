#include "sm64.h"
#include "types.h"
#include "course_table.h"
#include "game/memory.h"
#include "game/ingame_menu.h"
#include "game/save_file.h"
#include "game/segment2.h"

#ifdef VERSION_EU
extern s32 gInGameLanguage;
#include "eu_translation.h"
#endif

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
    void **dialogTable = NULL;
    void **actNameTbl = NULL;
    void **courseNameTbl = NULL;
    void **dialogTableOrg = NULL;
    void **actNameTblOrg = NULL;
    void **courseNameTblOrg = NULL;
    
#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            dialogTable = segmented_to_virtual(dialog_table_eu_en);
            actNameTbl = segmented_to_virtual(act_name_table_eu_en);
            courseNameTbl = segmented_to_virtual(course_name_table_eu_en);
            dialogTableOrg = segmented_to_virtual(dialog_table_eu_en_original);
            actNameTblOrg = segmented_to_virtual(act_name_table_eu_en_original);
            courseNameTblOrg = segmented_to_virtual(course_name_table_eu_en_original);
            break;
        case LANGUAGE_FRENCH:
            dialogTable = segmented_to_virtual(dialog_table_eu_fr);
            actNameTbl = segmented_to_virtual(act_name_table_eu_fr);
            courseNameTbl = segmented_to_virtual(course_name_table_eu_fr);
            dialogTableOrg = segmented_to_virtual(dialog_table_eu_fr_original);
            actNameTblOrg = segmented_to_virtual(act_name_table_eu_fr_original);
            courseNameTblOrg = segmented_to_virtual(course_name_table_eu_fr_original);
            break;
        case LANGUAGE_GERMAN:
            dialogTable = segmented_to_virtual(dialog_table_eu_de);
            actNameTbl = segmented_to_virtual(act_name_table_eu_de);
            courseNameTbl = segmented_to_virtual(course_name_table_eu_de);
            dialogTableOrg = segmented_to_virtual(dialog_table_eu_de_original);
            actNameTblOrg = segmented_to_virtual(act_name_table_eu_de_original);
            courseNameTblOrg = segmented_to_virtual(course_name_table_eu_de_original);
            break;
    }
#else
    dialogTable = segmented_to_virtual(seg2_dialog_table);
    actNameTbl = segmented_to_virtual(seg2_act_name_table);
    courseNameTbl = segmented_to_virtual(seg2_course_name_table);
    dialogTableOrg = segmented_to_virtual(seg2_dialog_original);
    actNameTblOrg = segmented_to_virtual(seg2_act_name_table_original);
    courseNameTblOrg = segmented_to_virtual(seg2_course_name_table_original);
#endif

    for (s32 i = 0; i < DIALOG_COUNT; i++) {
        if (!sReplacedDialog[i]) { continue; }
        struct DialogEntry *dialog = segmented_to_virtual(dialogTable[i]);
        free((u8*)dialog->str);
        dialog->str = dialogTableOrg[i];
        sReplacedDialog[i] = false;
    }

    for (s32 i = 0; i < COURSE_COUNT+2; i++) {
        if (!sReplacedCourseName[i]) { continue; }
        free((u8*)courseNameTbl[i]);
        courseNameTbl[i] = segmented_to_virtual(courseNameTblOrg[i]);
        sReplacedCourseName[i] = false;
    }

    for (s32 i = 0; i < (COURSE_RR+2)*6; i++) {
        if (!sReplacedActName[i]) { continue; }
        free((u8*)actNameTbl[i]);
        actNameTbl[i] = segmented_to_virtual(actNameTblOrg[i]);
        sReplacedActName[i] = false;
    }
}

void smlua_text_utils_dialog_replace(enum DialogId dialogId, UNUSED u32 unused, s8 linesPerBox, s16 leftOffset, s16 width, const char* str) {
    if (dialogId >= DIALOG_COUNT) { return; }
    
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
    
    void **actNameTbl = NULL;
    void **courseNameTbl = NULL;
    
#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            actNameTbl = segmented_to_virtual(act_name_table_eu_en);
            courseNameTbl = segmented_to_virtual(course_name_table_eu_en);
            break;
        case LANGUAGE_FRENCH:
            actNameTbl = segmented_to_virtual(act_name_table_eu_fr);
            courseNameTbl = segmented_to_virtual(course_name_table_eu_fr);
            break;
        case LANGUAGE_GERMAN:
            actNameTbl = segmented_to_virtual(act_name_table_eu_de);
            courseNameTbl = segmented_to_virtual(course_name_table_eu_de);
            break;
    }
#else
    actNameTbl = segmented_to_virtual(seg2_act_name_table);
    courseNameTbl = segmented_to_virtual(seg2_course_name_table);
#endif

    // replace course name
    if (sReplacedCourseName[courseOffset]) {
        free(courseNameTbl[courseOffset]);
    }
    courseNameTbl[courseOffset] = smlua_text_utils_convert(courseName);
    sReplacedCourseName[courseOffset] = true;

    // replace act names
    const char* newActs[] = { act1, act2, act3, act4, act5, act6 };
    for (s32 i = 0; i < 6; i++) {
        s32 index = (courseOffset * 6 + i);

        if (sReplacedActName[index]) {
            free(actNameTbl[index]);
        }

        actNameTbl[index] = smlua_text_utils_convert(newActs[i]);
        sReplacedActName[index] = true;
    }
}

void smlua_text_utils_secret_star_replace(s16 courseNum, const char* courseName) {
    if (courseNum <= COURSE_RR || courseNum > COURSE_COUNT) { return; }
    s16 courseOffset = courseNum - 1;
    
    void **courseNameTbl = NULL;
    
#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_en);
            break;
        case LANGUAGE_FRENCH:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_fr);
            break;
        case LANGUAGE_GERMAN:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_de);
            break;
    }
#else
    courseNameTbl = segmented_to_virtual(seg2_course_name_table);
#endif

    if (sReplacedCourseName[courseOffset]) {
        free(courseNameTbl[courseOffset]);
    }

    courseNameTbl[courseOffset] = smlua_text_utils_convert(courseName);
    sReplacedCourseName[courseOffset] = true;
}

void smlua_text_utils_castle_secret_stars_replace(const char* name) {
    s16 courseOffset = COURSE_COUNT;
    
    void **courseNameTbl = NULL;
    
#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_en);
            break;
        case LANGUAGE_FRENCH:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_fr);
            break;
        case LANGUAGE_GERMAN:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_de);
            break;
    }
#else
    courseNameTbl = segmented_to_virtual(seg2_course_name_table);
#endif

    if (sReplacedCourseName[courseOffset]) {
        free(courseNameTbl[courseOffset]);
    }

    courseNameTbl[courseOffset] = smlua_text_utils_convert(name);
    sReplacedCourseName[courseOffset] = true;
}

void smlua_text_utils_extra_text_replace(s16 index, const char* text) {
    if (index < 0 || index > 6) { return; }
    index = (COURSE_RR * 6 + index);
    
    void **actNameTbl = NULL;
    
#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            actNameTbl = segmented_to_virtual(act_name_table_eu_en);
            break;
        case LANGUAGE_FRENCH:
            actNameTbl = segmented_to_virtual(act_name_table_eu_fr);
            break;
        case LANGUAGE_GERMAN:
            actNameTbl = segmented_to_virtual(act_name_table_eu_de);
            break;
    }
#else
    actNameTbl = segmented_to_virtual(seg2_act_name_table);
#endif

    if (sReplacedActName[index]) {
        free(actNameTbl[index]);
    }

    actNameTbl[index] = smlua_text_utils_convert(text);
    sReplacedActName[index] = true;
}

const char* smlua_text_utils_get_language(void) {
    return configLanguage;
}