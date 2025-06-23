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

void convert_string_sm64_to_ascii(char *strAscii, const u8 *str64);

/*
---------------------------------------------------
Mapping gReplacedCourseActNameTable <-> seg2 tables
---------------------------------------------------

For courseNum from COURSE_BOB to COURSE_RR:
- gReplacedCourseActNameTable[courseNum].courseName     <->  seg2_course_name_table[courseNum - 1]
- gReplacedCourseActNameTable[courseNum].actName[0..5]  <->  seg2_act_name_table[(courseNum - 1) * 6 + (0..5)]
  (7th act name doesn't map to anything, but can be retrieved with `smlua_text_utils_act_name_get`)

For courseNum from COURSE_BITDW to COURSE_CAKE_END:
- gReplacedCourseActNameTable[courseNum].courseName  <->  seg2_course_name_table[courseNum - 1]
- gReplacedCourseActNameTable[courseNum].actName[0..6] don't map to anything, but they can be retrieved with `smlua_text_utils_act_name_get`

For castle secret stars and extra text:
- gReplacedCourseActNameTable[COURSE_END].courseName     <->  seg2_course_name_table[COURSE_MAX] (which is seg2_course_name_table_castle_secret_stars)
- gReplacedCourseActNameTable[COURSE_END].actName[0..6]  <->  seg2_act_name_table[COURSE_STAGES_MAX * 6 + (0..6)] (which are extra_text_0~6)
*/
struct CourseActNames gReplacedCourseActNameTable[COURSE_END + 1] = { 0 };

static bool sSmluaTextUtilsInited = false;

#define smlua_text_utils_init_from_vanilla(obj, tableFunc, tableOrigFunc, tableOffset) { \
    char buffer[50]; \
    convert_string_sm64_to_ascii(buffer, tableOrigFunc()[tableOffset]); \
    snprintf(obj.name.value, sizeof(obj.name.value), "%s", buffer); \
    obj.name.get_table = tableFunc; \
    obj.name.offset = tableOffset; \
    snprintf(obj.orig.value, sizeof(obj.orig.value), "%s", buffer); \
    obj.orig.get_table = tableOrigFunc; \
    obj.orig.offset = tableOffset; \
    tableFunc()[tableOffset] = tableOrigFunc()[tableOffset]; \
}

// Save all vanilla act names and course names
void smlua_text_utils_init(void) {
    memset(gReplacedCourseActNameTable, 0, sizeof(gReplacedCourseActNameTable));

    // Vanilla courses
    for (s16 courseNum = COURSE_MIN; courseNum <= COURSE_MAX; ++courseNum) {
        smlua_text_utils_init_from_vanilla(
            gReplacedCourseActNameTable[courseNum].courseName,
            get_course_name_table,
            get_course_name_table_original,
            courseNum - 1
        );

        // Vanilla acts
        if (COURSE_IS_MAIN_COURSE(courseNum)) {
            for (s16 actIndex = 0; actIndex < MAX_ACTS; ++actIndex) {
                smlua_text_utils_init_from_vanilla(
                    gReplacedCourseActNameTable[courseNum].actName[actIndex],
                    get_act_name_table,
                    get_act_name_table_original,
                    (courseNum - 1) * MAX_ACTS + actIndex
                );
            }
        }
    }

    // Vanilla castle secrets and extras
    smlua_text_utils_init_from_vanilla(
        gReplacedCourseActNameTable[COURSE_END].courseName,
        get_course_name_table,
        get_course_name_table_original,
        COURSE_MAX
    );
    for (s16 actIndex = 0; actIndex < MAX_ACTS_AND_100_COINS; ++actIndex) {
        smlua_text_utils_init_from_vanilla(
            gReplacedCourseActNameTable[COURSE_END].actName[actIndex],
            get_act_name_table,
            get_act_name_table_original,
            COURSE_STAGES_MAX * MAX_ACTS + actIndex
        );
    }

    sSmluaTextUtilsInited = true;
}

void smlua_text_utils_shutdown(void) {
    if (sSmluaTextUtilsInited) {
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

static void smlua_text_utils_reset_course_or_act_name(struct ReplacedName *name) {
    if (name->name.get_table && name->orig.get_table) {
        void **tblName = name->name.get_table() + name->name.offset;
        void **tblOrig = name->orig.get_table() + name->orig.offset;
        if (*tblName != *tblOrig) {
            free(*tblName);
            *tblName = *tblOrig;
        }
    }
    memcpy(name->name.value, name->orig.value, sizeof(name->name.value));
    name->modNum = 0;
}

static void smlua_text_utils_replace_course_or_act_name(struct ReplacedName *name, const char *replacement, s32 modIndex) {
    replacement += 3 * str_starts_with_spaces(replacement);
    if (name->name.get_table && name->orig.get_table) {
        void **tblName = name->name.get_table() + name->name.offset;
        void **tblOrig = name->orig.get_table() + name->orig.offset;
        if (*tblName != *tblOrig) {
            free(*tblName);
        }
        *tblName = smlua_text_utils_convert(replacement);
    }
    snprintf(name->name.value, sizeof(name->name.value), "%s", replacement);
    name->modNum = modIndex + 1;
}

void smlua_text_utils_reset_all(void) {
    void **dialogTable = NULL;
    void **dialogTableOrg = NULL;

#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            dialogTable = segmented_to_virtual(dialog_table_eu_en);
            dialogTableOrg = segmented_to_virtual(dialog_table_eu_en_original);
            break;
        case LANGUAGE_FRENCH:
            dialogTable = segmented_to_virtual(dialog_table_eu_fr);
            dialogTableOrg = segmented_to_virtual(dialog_table_eu_fr_original);
            break;
        case LANGUAGE_GERMAN:
            dialogTable = segmented_to_virtual(dialog_table_eu_de);
            dialogTableOrg = segmented_to_virtual(dialog_table_eu_de_original);
            break;
    }
#else
    dialogTable = segmented_to_virtual(seg2_dialog_table);
    dialogTableOrg = segmented_to_virtual(seg2_dialog_original);
#endif

    for (s32 i = 0; i < DIALOG_COUNT; i++) {
        if (!sReplacedDialog[i]) { continue; }
        struct DialogEntry *dialog = segmented_to_virtual(dialogTable[i]);
        free((u8*)dialog->str);
        dialog->str = dialogTableOrg[i];
        sReplacedDialog[i] = false;
    }

    if (sSmluaTextUtilsInited) {
        for (s16 courseNum = 0; courseNum < COURSE_END; courseNum++) {

            // Restore vanilla course names
            struct ReplacedName *courseName = &gReplacedCourseActNameTable[courseNum].courseName;
            smlua_text_utils_reset_course_or_act_name(courseName);

            // Restore vanilla act names
            for (s16 actIndex = 0; actIndex < MAX_ACTS_AND_100_COINS; actIndex++) {
                struct ReplacedName *actName = &gReplacedCourseActNameTable[courseNum].actName[actIndex];
                smlua_text_utils_reset_course_or_act_name(actName);
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
    if (!COURSE_IS_VALID_COURSE(courseNum)) { return; }

    struct CourseActNames *courseActNames = &gReplacedCourseActNameTable[courseNum];
    smlua_text_utils_replace_course_or_act_name(&courseActNames->courseName, courseName, gLuaActiveMod->index);

#define REPLACE_ACT_NAME(i) { \
        smlua_text_utils_replace_course_or_act_name(&courseActNames->actName[i - 1], act##i, gLuaActiveMod->index); \
    }

    REPLACE_ACT_NAME(1);
    REPLACE_ACT_NAME(2);
    REPLACE_ACT_NAME(3);
    REPLACE_ACT_NAME(4);
    REPLACE_ACT_NAME(5);
    REPLACE_ACT_NAME(6);
}

void smlua_text_utils_course_name_replace(s16 courseNum, const char* name) {
    if (!COURSE_IS_VALID_COURSE(courseNum)) { return; }

    struct CourseActNames *courseActNames = &gReplacedCourseActNameTable[courseNum];
    smlua_text_utils_replace_course_or_act_name(&courseActNames->courseName, name, gLuaActiveMod->index);
}

const char* smlua_text_utils_course_name_get(s16 courseNum) {
    if (!COURSE_IS_VALID_COURSE(courseNum)) { return NULL; }

    return gReplacedCourseActNameTable[courseNum].courseName.name.value;
}

s32 smlua_text_utils_course_name_mod_index(s16 courseNum) {
    if (!COURSE_IS_VALID_COURSE(courseNum)) { return -1; }

    return (s32) gReplacedCourseActNameTable[courseNum].courseName.modNum - 1;
}

void smlua_text_utils_course_name_reset(s16 courseNum) {
    if (!COURSE_IS_VALID_COURSE(courseNum)) { return; }

    struct CourseActNames *courseActNames = &gReplacedCourseActNameTable[courseNum];
    smlua_text_utils_reset_course_or_act_name(&courseActNames->courseName);
}

void smlua_text_utils_act_name_replace(s16 courseNum, u8 actNum, const char* name) {
    if (!COURSE_IS_VALID_COURSE(courseNum)) { return; }
    if (actNum < 1 || actNum > MAX_ACTS_AND_100_COINS) { return; }

    struct CourseActNames *courseActNames = &gReplacedCourseActNameTable[courseNum];
    smlua_text_utils_replace_course_or_act_name(&courseActNames->actName[actNum - 1], name, gLuaActiveMod->index);
}

const char* smlua_text_utils_act_name_get(s16 courseNum, u8 actNum) {
    if (!COURSE_IS_VALID_COURSE(courseNum)) { return NULL; }
    if (actNum < 1 || actNum > MAX_ACTS_AND_100_COINS) { return NULL; }

    return gReplacedCourseActNameTable[courseNum].actName[actNum - 1].name.value;
}

s32 smlua_text_utils_act_name_mod_index(s16 courseNum, u8 actNum) {
    if (!COURSE_IS_VALID_COURSE(courseNum)) { return -1; }
    if (actNum < 1 || actNum > MAX_ACTS_AND_100_COINS) { return -1; }

    return (s32) gReplacedCourseActNameTable[courseNum].actName[actNum - 1].modNum - 1;
}

void smlua_text_utils_act_name_reset(s16 courseNum, u8 actNum) {
    if (!COURSE_IS_VALID_COURSE(courseNum)) { return; }
    if (actNum < 1 || actNum > MAX_ACTS_AND_100_COINS) { return; }

    struct CourseActNames *courseActNames = &gReplacedCourseActNameTable[courseNum];
    smlua_text_utils_reset_course_or_act_name(&courseActNames->actName[actNum - 1]);
}

void smlua_text_utils_secret_star_replace(s16 courseNum, const char* courseName) {
    if (courseNum <= COURSE_STAGES_MAX || courseNum > COURSE_MAX) { return; }

    smlua_text_utils_course_name_replace(courseNum, courseName);
}

void smlua_text_utils_castle_secret_stars_replace(const char* name) {
    struct CourseActNames *courseActNames = &gReplacedCourseActNameTable[COURSE_END];
    smlua_text_utils_replace_course_or_act_name(&courseActNames->courseName, name, gLuaActiveMod->index);
}

const char* smlua_text_utils_castle_secret_stars_get() {
    return gReplacedCourseActNameTable[COURSE_END].courseName.name.value;
}

s32 smlua_text_utils_castle_secret_stars_mod_index() {
    return (s32) gReplacedCourseActNameTable[COURSE_END].courseName.modNum - 1;
}

void smlua_text_utils_castle_secret_stars_reset() {
    struct CourseActNames *courseActNames = &gReplacedCourseActNameTable[COURSE_END];
    smlua_text_utils_reset_course_or_act_name(&courseActNames->courseName);
}

void smlua_text_utils_extra_text_replace(s16 index, const char* text) {
    if (index < 0 || index > MAX_ACTS_AND_100_COINS) { return; }

    struct CourseActNames *courseActNames = &gReplacedCourseActNameTable[COURSE_END];
    smlua_text_utils_replace_course_or_act_name(&courseActNames->actName[index], text, gLuaActiveMod->index);
}

const char* smlua_text_utils_extra_text_get(s16 index) {
    if (index < 0 || index > MAX_ACTS_AND_100_COINS) { return NULL; }

    return gReplacedCourseActNameTable[COURSE_END].actName[index].name.value;
}

s32 smlua_text_utils_extra_text_mod_index(s16 index) {
    if (index < 0 || index > MAX_ACTS_AND_100_COINS) { return -1; }

    return (s32) gReplacedCourseActNameTable[COURSE_END].actName[index].modNum - 1;
}

void smlua_text_utils_extra_text_reset(s16 index) {
    if (index < 0 || index > MAX_ACTS_AND_100_COINS) { return; }

    struct CourseActNames *courseActNames = &gReplacedCourseActNameTable[COURSE_END];
    smlua_text_utils_reset_course_or_act_name(&courseActNames->actName[index]);
}

const char* smlua_text_utils_get_language(void) {
    return configLanguage;
}
