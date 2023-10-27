#ifndef LEVEL_INFO_H
#define LEVEL_INFO_H

#include <PR/ultratypes.h>

void *get_course_name_table();
void *get_act_name_table();
const char *get_level_name_ascii(s16 courseNum, s16 levelNum, s16 areaIndex, s16 charCase);
const u8   *get_level_name_sm64(s16 courseNum, s16 levelNum, s16 areaIndex, s16 charCase);
const char *get_level_name(s16 courseNum, s16 levelNum, s16 areaIndex);
const char *get_star_name_ascii(s16 courseNum, s16 starNum, s16 charCase);
const u8   *get_star_name_sm64(s16 courseNum, s16 starNum, s16 charCase);
const char *get_star_name(s16 courseNum, s16 starNum);

#endif // LEVEL_INFO_H
