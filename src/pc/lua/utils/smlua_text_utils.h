#ifndef SMLUA_TEXT_UTILS_H
#define SMLUA_TEXT_UTILS_H

#include "types.h"
#include "dialog_ids.h"

#define MAX_ACTS 6
#define MAX_ACTS_AND_100_COINS 7

struct ActName {
    char name[256];
    char orig[256];
    s32 modIndex;
};

struct CourseName {
    struct ActName *actName;
    char name[256];
    char orig[256];
    s32 modIndex;
};

extern struct CourseName *gReplacedActNameTable[];

void smlua_text_utils_init(void);
void smlua_text_utils_shutdown(void);
/* |description|Resets every modified dialog back to vanilla|descriptionEnd|*/
void smlua_text_utils_reset_all(void);
/* |description|Replaces `dialogId` with a custom one|descriptionEnd| */
void smlua_text_utils_dialog_replace(enum DialogId dialogId, u32 unused, s8 linesPerBox, s16 leftOffset, s16 width, const char* str);
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
/* |description|Replace extra text (e.g. one of the castle's secret stars) with `text`|descriptionEnd| */
void smlua_text_utils_extra_text_replace(s16 index, const char* text);
/* |description|Gets the current language|descriptionEnd| */
const char* smlua_text_utils_get_language(void);

#endif
