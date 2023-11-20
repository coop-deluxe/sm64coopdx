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

static const struct { const char *str; u8 c; } sSm64CharMap[] = {

    // Digits
    { "0", 0x00 }, { "1", 0x01 }, { "2", 0x02 }, { "3", 0x03 }, { "4", 0x04 },
    { "5", 0x05 }, { "6", 0x06 }, { "7", 0x07 }, { "8", 0x08 }, { "9", 0x09 },

    // Capital letters
    { "A", 0x0A }, { "B", 0x0B }, { "C", 0x0C }, { "D", 0x0D }, { "E", 0x0E },
    { "F", 0x0F }, { "G", 0x10 }, { "H", 0x11 }, { "I", 0x12 }, { "J", 0x13 },
    { "K", 0x14 }, { "L", 0x15 }, { "M", 0x16 }, { "N", 0x17 }, { "O", 0x18 },
    { "P", 0x19 }, { "Q", 0x1A }, { "R", 0x1B }, { "S", 0x1C }, { "T", 0x1D },
    { "U", 0x1E }, { "V", 0x1F }, { "W", 0x20 }, { "X", 0x21 }, { "Y", 0x22 },
    { "Z", 0x23 },

    // Letters
    { "a", 0x24 }, { "b", 0x25 }, { "c", 0x26 }, { "d", 0x27 }, { "e", 0x28 },
    { "f", 0x29 }, { "g", 0x2A }, { "h", 0x2B }, { "i", 0x2C }, { "j", 0x2D },
    { "k", 0x2E }, { "l", 0x2F }, { "m", 0x30 }, { "n", 0x31 }, { "o", 0x32 },
    { "p", 0x33 }, { "q", 0x34 }, { "r", 0x35 }, { "s", 0x36 }, { "t", 0x37 },
    { "u", 0x38 }, { "v", 0x39 }, { "w", 0x3A }, { "x", 0x3B }, { "y", 0x3C },
    { "z", 0x3D },

    // Punctuation
    { "...", 0xE6 }, // ellipsis
    { ")(",  0xE2 }, // close-open parentheses
    { "<<",  0xF5 }, // double quote open
    { ">>",  0xF6 }, // double quote close
    { "\'",  0x3E }, // apostrophe
    { ".",   0x3F }, // period
    { ",",   0x6F }, // comma
    { " ",   0x9E }, // space
    { "-",   0x9F }, // dash
    { "(",   0xE1 }, // open parentheses
    { ")",   0xE3 }, // close parentheses
    { "&",   0xE5 }, // ampersand
    { "!",   0xF2 }, // exclamation mark
    { "%",   0xF3 }, // percent
    { "?",   0xF4 }, // question mark
    { "~",   0xF7 }, // tilde

    // Symbols
    { "[A]", 0x54 }, // bold A
    { "[B]", 0x55 }, // bold B
    { "[C]", 0x56 }, // bold C
    { "[Z]", 0x57 }, // bold Z
    { "[R]", 0x58 }, // bold R
    { "<->", 0xE4 }, // left-right arrow
    { "^",   0x50 }, // up arrow
    { "|",   0x51 }, // down arrow
    { "<",   0x52 }, // left arrow
    { ">",   0x53 }, // right arrow
    { "+",   0xF9 }, // coin
    { "@",   0xFA }, // star filled
    { "*",   0xFB }, // multiply
    { "$",   0xFD }, // star empty
    { "\n",  0xFE }, // New line
    { NULL,  0xFF }, // Null terminator
};

static const char *ascii_to_sm64_char(u8 *str64, const char *strAscii) {
    for (s32 i = 0; sSm64CharMap[i].str != NULL; ++i) {
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

static void convert_string_ascii_to_sm64(u8 *str64, const char *strAscii) {
    for (; *strAscii != 0; str64++) {
        strAscii = ascii_to_sm64_char(str64, strAscii);
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

void *get_course_name_table() {
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

void *get_act_name_table() {
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
    convert_string_ascii_to_sm64(output, levelName);
    return output;
}

const char *get_level_name(s16 courseNum, s16 levelNum, s16 areaIndex) {
    return get_level_name_ascii(courseNum, levelNum, areaIndex, -1);
}

const char *get_star_name_ascii(s16 courseNum, s16 starNum, s16 charCase) {
    static char output[256];

    s16 starIndex = starNum - 1;
    if (starIndex >= 0 && starIndex < MAX_ACTS &&
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
    convert_string_ascii_to_sm64(output, starName);
    return output;
}

const char *get_star_name(s16 courseNum, s16 starNum) {
    return get_star_name_ascii(courseNum, starNum, -1);
}
