#include "sm64.h"
#include "types.h"
#include "course_table.h"
#include "game/memory.h"
#include "game/ingame_menu.h"
#include "game/save_file.h"
#include "game/segment2.h"
#include "game/level_info.h"
#include "pc/pc_main.h"
#include "../smlua.h"
#include "smlua_level_utils.h"
#include "smlua_text_utils.h"

#ifdef VERSION_EU
extern s32 gInGameLanguage;
#include "eu_translation.h"
#endif

static bool sReplacedDialog[DIALOG_COUNT] = { 0 };
static bool sReplacedCourseName[COURSE_COUNT+2] = { 0 };
static bool sReplacedActName[(COURSE_RR+2)*6] = { 0 };

#define INVALID_COURSE_NUM(courseNum) (smlua_level_util_get_info_from_course_num(courseNum) == NULL && !COURSE_IS_VALID_COURSE(courseNum))

void convert_string_sm64_to_ascii(char *strAscii, const u8 *str64);

struct CourseName *gReplacedActNameTable[COURSE_END];

static bool sSmluaTextUtilsInited = false;

// Save all vanilla act names and course names
void smlua_text_utils_init(void) {
    void **actNameTbl = get_act_name_table();
    void **courseNameTbl = get_course_name_table();
    char courseBuffer[50];
    char actBuffer[50];

    // Course/Star names
    for (s16 courseNum = 0; courseNum < COURSE_END; courseNum++) {
        gReplacedActNameTable[courseNum] = calloc(1, sizeof(struct CourseName));
        struct CourseName* courseActNames = gReplacedActNameTable[courseNum];
        convert_string_sm64_to_ascii(courseBuffer, segmented_to_virtual(courseNameTbl[courseNum]));
        snprintf(courseActNames->name, 50, "%s", courseBuffer);
        snprintf(courseActNames->orig, 50, "%s", courseBuffer);
        courseActNames->modIndex = -1;
        courseActNames->actName = NULL;

        // Individual acts
        if (COURSE_IS_MAIN_COURSE(courseNum)) {
            courseActNames->actName = calloc(MAX_ACTS_AND_100_COINS, sizeof(struct ActName));
            for (s16 actNum = 0; actNum < MAX_ACTS; actNum++) {
                convert_string_sm64_to_ascii(actBuffer, segmented_to_virtual(actNameTbl[courseNum * MAX_ACTS + actNum]));
                snprintf(courseActNames->actName[actNum].name, 50, "%s", actBuffer);
                snprintf(courseActNames->actName[actNum].orig, 50, "%s", actBuffer);
                courseActNames->actName[actNum].modIndex = -1;
            }
            courseActNames->actName[MAX_ACTS_AND_100_COINS - 1].modIndex = -1;
        }
    }
    sSmluaTextUtilsInited = true;
}

void smlua_text_utils_shutdown(void) {
    if (sSmluaTextUtilsInited) {
        for (s16 courseNum = 0; courseNum < COURSE_END; courseNum++) {
            free(gReplacedActNameTable[courseNum]->actName);
            free(gReplacedActNameTable[courseNum]);
        }
        sSmluaTextUtilsInited = false;
    }
}

static u8* smlua_text_utils_convert(const char* str) {
    s32 len = strlen(str);
    u8* dialogStr = calloc(len + 2, sizeof(u8));
    str_ascii_to_dialog(str, dialogStr, len + 1);
    return dialogStr;
}

// Checks the first 3 characters
static bool str_starts_with_spaces(const char* str) {
    for (u8 i = 0; i < 3; i++) {
        if (str[i] != ' ') { return false; }
    }
    return true;
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

    if (sSmluaTextUtilsInited) {
        for (s32 courseNum = 0; courseNum < COURSE_COUNT; courseNum++) {
            struct CourseName* courseActNames = gReplacedActNameTable[courseNum];
            snprintf(courseActNames->name, 50, "%s", courseActNames->orig);
            courseActNames->modIndex = -1;

            // Individual acts
            if (COURSE_IS_MAIN_COURSE(courseNum)) {
                for (s16 actNum = 0; actNum < MAX_ACTS_AND_100_COINS; actNum++) {
                    snprintf(courseActNames->actName[actNum].name, 50, "%s", courseActNames->actName[actNum].orig);
                    courseActNames->actName[actNum].modIndex = -1;
                }
            }
        }
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
    struct CourseName* courseActNames = gReplacedActNameTable[courseNum];
    snprintf(courseActNames->name, 256, "%s", courseName + (3 * (strlen(courseName) > 3)));
    courseActNames->modIndex = gLuaActiveMod->index;

#define REPLACE_ACT_NAME(i) { \
        snprintf(courseActNames->actName[i-1].name, 256, "%s", act##i); \
        courseActNames->actName[i-1].modIndex = gLuaActiveMod->index; \
    }

    REPLACE_ACT_NAME(1);
    REPLACE_ACT_NAME(2);
    REPLACE_ACT_NAME(3);
    REPLACE_ACT_NAME(4);
    REPLACE_ACT_NAME(5);
    REPLACE_ACT_NAME(6);
}

void smlua_text_utils_course_name_replace(s16 courseNum, const char* name) {
    if (INVALID_COURSE_NUM(courseNum)) { return; }

    struct CourseName* courseActNames = gReplacedActNameTable[courseNum];
    snprintf(courseActNames->name, 256, "%s", name);
    courseActNames->modIndex = gLuaActiveMod->index;
}

const char* smlua_text_utils_course_name_get(s16 courseNum) {
    if (INVALID_COURSE_NUM(courseNum)) { return NULL; }

    return gReplacedActNameTable[courseNum]->name;
}

s32 smlua_text_utils_course_name_mod_index(s16 courseNum) {
    if (INVALID_COURSE_NUM(courseNum)) { return -1; }

    return gReplacedActNameTable[courseNum]->modIndex;
}

void smlua_text_utils_course_name_reset(s16 courseNum) {
    if (INVALID_COURSE_NUM(courseNum)) { return; }

    struct CourseName* courseActNames = gReplacedActNameTable[courseNum];
    snprintf(courseActNames->name, 50, "%s", courseActNames->orig);
    courseActNames->modIndex = -1;
}

void smlua_text_utils_act_name_replace(s16 courseNum, u8 actNum, const char* name) {
    if (INVALID_COURSE_NUM(courseNum) || actNum >= MAX_ACTS_AND_100_COINS) { return; }

    struct CourseName* courseActNames = gReplacedActNameTable[courseNum];

    snprintf(courseActNames->actName[actNum].name, 256, "%s", name);
    courseActNames->actName[actNum].modIndex = gLuaActiveMod->index;
}

const char* smlua_text_utils_act_name_get(s16 courseNum, u8 actNum) {
    if (INVALID_COURSE_NUM(courseNum) || actNum >= MAX_ACTS_AND_100_COINS) { return NULL; }

    return gReplacedActNameTable[courseNum]->actName[actNum].name;
}

s32 smlua_text_utils_act_name_mod_index(s16 courseNum, u8 actNum) {
    if (INVALID_COURSE_NUM(courseNum) || actNum >= MAX_ACTS_AND_100_COINS) { return false; }

    return gReplacedActNameTable[courseNum]->actName[actNum].modIndex;
}

void smlua_text_utils_act_name_reset(s16 courseNum, u8 actNum) {
    if (INVALID_COURSE_NUM(courseNum) || actNum >= MAX_ACTS_AND_100_COINS) { return; }

    struct CourseName* courseActNames = gReplacedActNameTable[courseNum];
    snprintf(courseActNames->actName[actNum].name, 50, "%s", courseActNames->actName[actNum].orig);
    courseActNames->actName[actNum].modIndex = gLuaActiveMod->index;
}

void smlua_text_utils_secret_star_replace(s16 courseNum, const char* courseName) {
    if (courseNum <= COURSE_RR || courseNum > COURSE_COUNT) { return; }
    /*
    s16 courseOffset = courseNum - 1;

    void **courseNameTbl = get_course_name_table();

    if (sReplacedCourseName[courseOffset]) {
        free(courseNameTbl[courseOffset]);
    }

    courseNameTbl[courseOffset] = smlua_text_utils_convert(courseName);
    sReplacedCourseName[courseOffset] = true;
    */

    struct CourseName* courseActNames = gReplacedActNameTable[courseNum];
    snprintf(courseActNames->name, 256, "%s", courseName + (3 * str_starts_with_spaces(courseName)));
    courseActNames->modIndex = gLuaActiveMod->index;
}

void smlua_text_utils_castle_secret_stars_replace(const char* name) {
    s16 courseOffset = COURSE_COUNT;

    void **courseNameTbl = get_course_name_table();

    if (sReplacedCourseName[courseOffset]) {
        free(courseNameTbl[courseOffset]);
    }

    courseNameTbl[courseOffset] = smlua_text_utils_convert(name);
    sReplacedCourseName[courseOffset] = true;
}

void smlua_text_utils_extra_text_replace(s16 index, const char* text) {
    if (index < 0 || index > 6) { return; }
    index = (COURSE_RR * 6 + index);

    void **actNameTbl = get_act_name_table();

    if (sReplacedActName[index]) {
        free(actNameTbl[index]);
    }

    actNameTbl[index] = smlua_text_utils_convert(text);
    sReplacedActName[index] = true;
}

const char* smlua_text_utils_get_language(void) {
    return configLanguage;
}
