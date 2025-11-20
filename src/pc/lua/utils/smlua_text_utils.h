#ifndef SMLUA_TEXT_UTILS_H
#define SMLUA_TEXT_UTILS_H

#include "types.h"
#include "dialog_ids.h"
#include "game/ingame_menu.h"

#define MAX_ACTS 6
#define MAX_ACTS_AND_100_COINS 7

struct NameTable {
    char value[256];
    void **(*get_table)(void);
    u32 offset;
};

struct ReplacedName {
    struct NameTable name;
    struct NameTable orig;
    u32 modNum; // modIndex + 1 (default value of 0 is more convenient than -1)
};

struct CourseActNames {
    struct ReplacedName courseName;
    struct ReplacedName actName[MAX_ACTS_AND_100_COINS]; // indexed by actIndex (actNum - 1)
};

extern struct CourseActNames gReplacedCourseActNameTable[]; // indexed by COURSE_* constants

void smlua_text_utils_init(void);
void smlua_text_utils_shutdown(void);
/* |description|Resets every modified dialog back to vanilla|descriptionEnd|*/
void smlua_text_utils_reset_all(void);
/* |description|Gets the DialogEntry struct for the given `dialogId`|descriptionEnd| */
struct DialogEntry* smlua_text_utils_dialog_get(enum DialogId dialogId);
const struct DialogEntry* smlua_text_utils_dialog_get_unmodified(enum DialogId dialogId);
/* |description|Replaces `dialogId` with a custom one|descriptionEnd| */
void smlua_text_utils_dialog_replace(enum DialogId dialogId, u32 unused, s8 linesPerBox, s16 leftOffset, s16 width, const char* str);
/* |description|Restores a replaced DialogEntry to its original state.|descriptionEnd| */
void smlua_text_utils_dialog_restore(enum DialogId dialogId);
/* |description|Returns whether the dialog with the given ID has been replaced|descriptionEnd| */
bool smlua_text_utils_dialog_is_replaced(enum DialogId dialogId);
/* |description|Allocates a new dialog entry|descriptionEnd|*/
s32 smlua_text_utils_allocate_dialog(void);
/* |description|Replaces the act names of `courseNum`|descriptionEnd| */
void smlua_text_utils_course_acts_replace(s16 courseNum, const char* courseName, const char* act1, const char* act2, const char* act3, const char* act4, const char* act5, const char* act6);
/* |description|Replaces the secret star course name of `courseNum` with `courseName`|descriptionEnd| */
void smlua_text_utils_secret_star_replace(s16 courseNum, const char* courseName);
/* |description|Replaces the name of `courseNum` with `name`|descriptionEnd| */
void smlua_text_utils_course_name_replace(s16 courseNum, const char* name);
/* |description|Gets the name of `courseNum`|descriptionEnd| */
const char* smlua_text_utils_course_name_get(s16 courseNum);
/* |description|Gets the index of the mod that replaced the name of `courseNum`|descriptionEnd| */
s32 smlua_text_utils_course_name_mod_index(s16 courseNum);
/* |description|Resets the name of `courseNum`|descriptionEnd| */
void smlua_text_utils_course_name_reset(s16 courseNum);
/* |description|Replaces the act name of `actNum` in `courseNum` with `name`|descriptionEnd| */
void smlua_text_utils_act_name_replace(s16 courseNum, u8 actNum, const char* name);
/* |description|Gets the act name of `actNum` in `courseNum`|descriptionEnd| */
const char* smlua_text_utils_act_name_get(s16 courseNum, u8 actNum);
/* |description|Gets the index of the mod that replaced the act name of `actNum` in `courseNum`|descriptionEnd| */
s32 smlua_text_utils_act_name_mod_index(s16 courseNum, u8 actNum);
/* |description|Resets the act name of `actNum` in `courseNum`|descriptionEnd| */
void smlua_text_utils_act_name_reset(s16 courseNum, u8 actNum);
/* |description|Replaces the castle secret stars text with `name`|descriptionEnd| */
void smlua_text_utils_castle_secret_stars_replace(const char* name);
/* |description|Gets the castle secret stars text|descriptionEnd| */
const char* smlua_text_utils_castle_secret_stars_get();
/* |description|Gets the index of the mod that replaced the castle secret stars text|descriptionEnd| */
s32 smlua_text_utils_castle_secret_stars_mod_index();
/* |description|Resets the castle secret stars text|descriptionEnd| */
void smlua_text_utils_castle_secret_stars_reset();
/* |description|Replace extra text (e.g. one of the castle's secret stars) with `text`|descriptionEnd| */
void smlua_text_utils_extra_text_replace(s16 index, const char* text);
/* |description|Gets the extra text at `index`|descriptionEnd| */
const char* smlua_text_utils_extra_text_get(s16 index);
/* |description|Gets the index of the mod that replaced the extra text at `index`|descriptionEnd| */
s32 smlua_text_utils_extra_text_mod_index(s16 index);
/* |description|Resets the extra text at `index`|descriptionEnd| */
void smlua_text_utils_extra_text_reset(s16 index);
/* |description|Gets the current language|descriptionEnd| */
const char* smlua_text_utils_get_language(void);

#endif
