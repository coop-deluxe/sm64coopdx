#ifndef SMLUA_TEXT_UTILS_H
#define SMLUA_TEXT_UTILS_H

#include "types.h"
#include "dialog_ids.h"

#define DIALOG_MAXIMUM_LENGTH 1024

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
void smlua_text_utils_reset_all(void);
struct DialogEntry* smlua_text_utils_dialog_get(enum DialogId dialogId);
void smlua_text_utils_dialog_replace(enum DialogId dialogId, u32 unused, s8 linesPerBox, s16 leftOffset, s16 width, const char* str);
void smlua_text_utils_course_acts_replace(s16 courseNum, const char* courseName, const char* act1, const char* act2, const char* act3, const char* act4, const char* act5, const char* act6);
void smlua_text_utils_secret_star_replace(s16 courseNum, const char* courseName);
void smlua_text_utils_course_name_replace(s16 courseNum, const char* name);
const char* smlua_text_utils_course_name_get(s16 courseNum);
s32 smlua_text_utils_course_name_mod_index(s16 courseNum);
void smlua_text_utils_course_name_reset(s16 courseNum);
void smlua_text_utils_act_name_replace(s16 courseNum, u8 actNum, const char* name);
const char* smlua_text_utils_act_name_get(s16 courseNum, u8 actNum);
s32 smlua_text_utils_act_name_mod_index(s16 courseNum, u8 actNum);
void smlua_text_utils_act_name_reset(s16 courseNum, u8 actNum);
void smlua_text_utils_castle_secret_stars_replace(const char* name);
void smlua_text_utils_extra_text_replace(s16 index, const char* text);
const char* smlua_text_utils_get_language(void);

void convert_string_sm64_to_ascii(char *strAscii, const u8 *str64);

#endif
