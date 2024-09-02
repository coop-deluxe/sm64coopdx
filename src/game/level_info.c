#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "course_table.h"
#include "game/hardcoded.h"
#include "game/memory.h"
#include "level_info.h"
#include "level_table.h"
#include "save_file.h"
#include "types.h"
#include "pc/lua/utils/smlua_level_utils.h"
#include "pc/lua/utils/smlua_text_utils.h"

#ifdef VERSION_EU
extern s32 gInGameLanguage;
#include "eu_translation.h"
#else
extern u8 *seg2_course_name_table[];
extern u8 *seg2_act_name_table[];
#endif

static const struct { const char *str; u8 c; u8 menu; } sSm64CharMap[] = {

    // Digits
    { "0", 0x00, 1 }, { "1", 0x01, 1 }, { "2", 0x02, 1 }, { "3", 0x03, 1 }, { "4", 0x04, 1 },
    { "5", 0x05, 1 }, { "6", 0x06, 1 }, { "7", 0x07, 1 }, { "8", 0x08, 1 }, { "9", 0x09, 1 },

    // Capital letters
    { "A", 0x0A, 1 }, { "B", 0x0B, 1 }, { "C", 0x0C, 1 }, { "D", 0x0D, 1 }, { "E", 0x0E, 1 },
    { "F", 0x0F, 1 }, { "G", 0x10, 1 }, { "H", 0x11, 1 }, { "I", 0x12, 1 }, { "J", 0x13, 1 },
    { "K", 0x14, 1 }, { "L", 0x15, 1 }, { "M", 0x16, 1 }, { "N", 0x17, 1 }, { "O", 0x18, 1 },
    { "P", 0x19, 1 }, { "Q", 0x1A, 1 }, { "R", 0x1B, 1 }, { "S", 0x1C, 1 }, { "T", 0x1D, 1 },
    { "U", 0x1E, 1 }, { "V", 0x1F, 1 }, { "W", 0x20, 1 }, { "X", 0x21, 1 }, { "Y", 0x22, 1 },
    { "Z", 0x23, 1 },

    // Letters
    { "a", 0x24, 0 }, { "b", 0x25, 0 }, { "c", 0x26, 0 }, { "d", 0x27, 0 }, { "e", 0x28, 0 },
    { "f", 0x29, 0 }, { "g", 0x2A, 0 }, { "h", 0x2B, 0 }, { "i", 0x2C, 0 }, { "j", 0x2D, 0 },
    { "k", 0x2E, 0 }, { "l", 0x2F, 0 }, { "m", 0x30, 0 }, { "n", 0x31, 0 }, { "o", 0x32, 0 },
    { "p", 0x33, 0 }, { "q", 0x34, 0 }, { "r", 0x35, 0 }, { "s", 0x36, 0 }, { "t", 0x37, 0 },
    { "u", 0x38, 0 }, { "v", 0x39, 0 }, { "w", 0x3A, 0 }, { "x", 0x3B, 0 }, { "y", 0x3C, 0 },
    { "z", 0x3D, 0 },

    // Punctuation
    { "...", 0xE6, 0 }, // ellipsis
    { ")(",  0xE2, 0 }, // close-open parentheses
    { "<<",  0xF5, 0 }, // double quote open
    { ">>",  0xF6, 0 }, // double quote close
    { "\'",  0x3E, 1 }, // apostrophe
    { ".",   0x3F, 1 }, // period
    { ",",   0x6F, 1 }, // comma
    { " ",   0x9E, 1 }, // space
    { "-",   0x9F, 1 }, // dash
    { "(",   0xE1, 0 }, // open parentheses
    { ")",   0xE3, 0 }, // close parentheses
    { "&",   0xE5, 1 }, // ampersand
    { "!",   0xF2, 1 }, // exclamation mark
    { "%",   0xF3, 0 }, // percent
    { "?",   0xF4, 1 }, // question mark
    { "~",   0xF7, 0 }, // tilde

    // Symbols
    { "[A]", 0x54, 0 }, // bold A
    { "[B]", 0x55, 0 }, // bold B
    { "[C]", 0x56, 0 }, // bold C
    { "[Z]", 0x57, 0 }, // bold Z
    { "[R]", 0x58, 0 }, // bold R
    { "<->", 0xE4, 0 }, // left-right arrow
    { "^",   0x50, 0 }, // up arrow
    { "|",   0x51, 0 }, // down arrow
    { "<",   0x52, 0 }, // left arrow
    { ">",   0x53, 0 }, // right arrow
    { "+",   0xF9, 1 }, // coin
    { "@",   0xFA, 1 }, // star filled
    { "*",   0xFB, 1 }, // multiply
    { "$",   0xFD, 0 }, // star empty
    { "\n",  0xFE, 1 }, // New line
    { NULL,  0xFF, 1 }, // Null terminator
};

static const char *ascii_to_sm64_char(u8 *str64, const char *strAscii, bool menu) {
    for (s32 i = 0; sSm64CharMap[i].str != NULL; ++i) {
        if (menu && !sSm64CharMap[i].menu) { continue; }
        if (strstr(strAscii, sSm64CharMap[i].str) == strAscii) {
            *str64 = sSm64CharMap[i].c;
            return strAscii + strlen(sSm64CharMap[i].str);
        }
    }
    *str64 = 0x9E;
    return strAscii + 1;
}

static char *sm64_to_ascii_char(char *strAscii, const u8 *str64) {
    for (s32 i = 0; sSm64CharMap[i].str != NULL; ++i) {
        if (sSm64CharMap[i].c == *str64) {
            s32 l = strlen(sSm64CharMap[i].str);
            memcpy(strAscii, sSm64CharMap[i].str, l);
            return strAscii + l;
        }
    }
    *strAscii = ' ';
    return strAscii + 1;
}

void convert_string_ascii_to_sm64(u8 *str64, const char *strAscii, bool menu) {
    for (; *strAscii != 0; str64++) {
        strAscii = ascii_to_sm64_char(str64, strAscii, menu);
    }
    *str64 = 0xFF;
}

void convert_string_sm64_to_ascii(char *strAscii, const u8 *str64) {
    for (; *str64 != 0xFF; str64++) {
        strAscii = sm64_to_ascii_char(strAscii, str64);
    }
    *strAscii = 0;
}

static void capitalize_string_ascii(char *strAscii) {
    for (; *strAscii != 0; strAscii++) {
        if (*strAscii >= 'a' && *strAscii <= 'z') {
            *strAscii += ('A' - 'a');
        }
    }
}

static void capitalize_string_sm64(u8 *str64) {
    for (; *str64 != 0xFF; str64++) {
        if (*str64 >= 0x24 && *str64 <= 0x3D) {
            *str64 -= 26;
        }
    }
}

static void decapitalize_string_ascii(char *strAscii) {
    for (bool decap = false; *strAscii != 0; strAscii++) {
        if (*strAscii >= 'A' && *strAscii <= 'Z') {
            if (decap) {
                *strAscii += ('a' - 'A');
            } else {
                decap = true;
            }
        } else if (*strAscii < '0' && *strAscii != '\'') {
            decap = false;
        }
    }
}

static void decapitalize_string_sm64(u8 *str64) {
    for (bool decap = false; *str64 != 0xFF; str64++) {
        if (*str64 >= 0x0A && *str64 <= 0x23) {
            if (decap) {
                *str64 += 26;
            } else {
                decap = true;
            }
        } else if (*str64 >= 0x3F) {
            decap = false;
        }
    }
}

void *get_course_name_table(void) {
    void **courseNameTbl = segmented_to_virtual(seg2_course_name_table);

#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH: courseNameTbl = segmented_to_virtual(course_name_table_eu_en); break;
        case LANGUAGE_FRENCH:  courseNameTbl = segmented_to_virtual(course_name_table_eu_fr); break;
        case LANGUAGE_GERMAN:  courseNameTbl = segmented_to_virtual(course_name_table_eu_de); break;
    }
#endif

    return courseNameTbl;
}

void *get_act_name_table(void) {
    void **actNameTbl = segmented_to_virtual(seg2_act_name_table);

#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH: actNameTbl = segmented_to_virtual(act_name_table_eu_en); break;
        case LANGUAGE_FRENCH:  actNameTbl = segmented_to_virtual(act_name_table_eu_fr); break;
        case LANGUAGE_GERMAN:  actNameTbl = segmented_to_virtual(act_name_table_eu_de); break;
    }
#endif

    return actNameTbl;
}

const char *get_level_name_ascii(s16 courseNum, s16 levelNum, s16 areaIndex, s16 charCase) {
    static char output[256];

    // Custom course
    bool hasCustomName = false;
    if (levelNum >= CUSTOM_LEVEL_NUM_START) {
        struct CustomLevelInfo* info = smlua_level_util_get_info(levelNum);
        if (info) {
            hasCustomName = true;
            snprintf(output, 256, info->fullName);
        }
    }

    if (courseNum >= 0 && courseNum <= COURSE_MAX && gReplacedActNameTable[courseNum]->modIndex != -1) {
        snprintf(output, 256, "%s", gReplacedActNameTable[courseNum]->name);
    }

    else if (!hasCustomName) {
        if (courseNum >= COURSE_MIN && courseNum < COURSE_MAX) {
            void **courseNameTbl = get_course_name_table();
            const u8 *courseName = segmented_to_virtual(courseNameTbl[courseNum - COURSE_BOB]);
            convert_string_sm64_to_ascii(output, courseName + 3);
            charCase = MIN(charCase, 0); // Don't need to capitalize vanilla course names
        }

        // Castle level
        else if (courseNum == COURSE_NONE) {
            switch (levelNum) {
                case LEVEL_CASTLE: {
                    switch (areaIndex) {
                        case 1: snprintf(output, 256, "Castle Main Floor"); break;
                        case 2: snprintf(output, 256, "Castle Upper Floor"); break;
                        case 3: snprintf(output, 256, "Castle Basement"); break;
                        default: snprintf(output, 256, "Castle Purgatory"); break;
                    }
                } break;
                case LEVEL_CASTLE_GROUNDS: snprintf(output, 256, "Castle Grounds"); break;
                case LEVEL_CASTLE_COURTYARD: snprintf(output, 256, "Castle Courtyard"); break;
                default: snprintf(output, 256, "Peach's Castle");
            }
        }

        else if (courseNum == LEVEL_ENDING) { // LEVEL_ENDING has the same course number as the level number
            snprintf(output, 256, "Ending");
        }

        // Default
        else {
            snprintf(output, 256, "Peach's Castle");
        }
    }

    // Capitalize or decapitalize text
    if (charCase == -1) {
        decapitalize_string_ascii(output);
    } else if (charCase == +1) {
        capitalize_string_ascii(output);
    }
    return output;
}

const u8 *get_level_name_sm64(s16 courseNum, s16 levelNum, s16 areaIndex, s16 charCase) {
    static u8 output[256];
    char levelName[256];
    snprintf(levelName, 256, " %d %s", courseNum, get_level_name_ascii(courseNum, levelNum, areaIndex, charCase));
    convert_string_ascii_to_sm64(output, levelName, false);
    return output;
}

const char *get_level_name(s16 courseNum, s16 levelNum, s16 areaIndex) {
    return get_level_name_ascii(courseNum, levelNum, areaIndex, -1);
}

const char *get_star_name_ascii(s16 courseNum, s16 starNum, s16 charCase) {
    static char output[256];

    s16 starIndex = starNum - 1;
    if (starIndex >= 0 && starIndex < MAX_ACTS_AND_100_COINS &&
        courseNum >= 0 && courseNum < COURSE_END &&
        gReplacedActNameTable[courseNum]->actName && gReplacedActNameTable[courseNum]->actName[starIndex].modIndex != -1) {
        snprintf(output, 256, "%s", gReplacedActNameTable[courseNum]->actName[starIndex].name);
    }

    // Main courses: BOB to RR
    else if (COURSE_IS_MAIN_COURSE(courseNum)) {
        if (starIndex >= 0 && starIndex < MAX_ACTS) {
            void **actNameTable = get_act_name_table();
            const u8 *starName = segmented_to_virtual(actNameTable[(courseNum - COURSE_BOB) * MAX_ACTS + starIndex]);
            convert_string_sm64_to_ascii(output, starName);
            charCase = MIN(charCase, 0); // Don't need to capitalize vanilla act names
        } else if (starNum == 7) {
            snprintf(output, 256, "%d Coins Star", gLevelValues.coinsRequiredForCoinStar);
        } else {
            snprintf(output, 256, "A Secret Star!");
        }
    }

    // Castle stars: Toads' and Mips'
    else if (courseNum == COURSE_NONE) {
        switch (starNum) {
            case 1: snprintf(output, 256, "Toad Star 1"); break;
            case 2: snprintf(output, 256, "Toad Star 2"); break;
            case 3: snprintf(output, 256, "Toad Star 3"); break;
            case 4: snprintf(output, 256, "Mips Star 1"); break;
            case 5: snprintf(output, 256, "Mips Star 2"); break;
            default: snprintf(output, 256, "A Secret Star!");
        }
    }

    // Bonus courses: Bowser stages and Secret courses
    else if (courseNum <= COURSE_MAX) {
        snprintf(output, 256, "Star %d", starNum);
    }

    // Default
    else {
        snprintf(output, 256, "A Secret Star!");
    }

    // Capitalize or decapitalize text
    if (charCase == -1) {
        decapitalize_string_ascii(output);
    } else if (charCase == +1) {
        capitalize_string_ascii(output);
    }
    return output;
}

const u8 *get_star_name_sm64(s16 courseNum, s16 starNum, s16 charCase) {
    static u8 output[256];
    const char *starName = get_star_name_ascii(courseNum, starNum, charCase);
    convert_string_ascii_to_sm64(output, starName, true);
    return output;
}

const char *get_star_name(s16 courseNum, s16 starNum) {
    return get_star_name_ascii(courseNum, starNum, -1);
}
