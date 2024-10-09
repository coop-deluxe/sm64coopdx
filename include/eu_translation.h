#ifndef EU_TRANSLATION_H
#define EU_TRANSLATION_H

#include "types.h"

// EU changes most text to arrays for each language. This define allows these
// differences to be combined.
#ifdef VERSION_EU
    #define LANGUAGE_ARRAY(cmd) cmd[LANGUAGE_FUNCTION]
#else
    #define LANGUAGE_ARRAY(cmd) cmd
#endif

extern u8 *dialog_table_eu_en[];
extern u8 *course_name_table_eu_en[];
extern u8 *act_name_table_eu_en[];
extern u8 *dialog_table_eu_en_original[];
extern u8 *course_name_table_eu_en_original[];
extern u8 *act_name_table_eu_en_original[];

extern u8 *dialog_table_eu_fr[];
extern u8 *course_name_table_eu_fr[];
extern u8 *act_name_table_eu_fr[];
extern u8 *dialog_table_eu_fr_original[];
extern u8 *course_name_table_eu_fr_original[];
extern u8 *act_name_table_eu_fr_original[];

extern u8 *dialog_table_eu_de[];
extern u8 *course_name_table_eu_de[];
extern u8 *act_name_table_eu_de[];
extern u8 *dialog_table_eu_de_original[];
extern u8 *course_name_table_eu_de_original[];
extern u8 *act_name_table_eu_de_original[];

#endif // EU_TRANSLATION_H
