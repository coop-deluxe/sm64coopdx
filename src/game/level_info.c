#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "course_table.h"
#include "game/hardcoded.h"
#include "game/memory.h"
#include "game/segment2.h"
#include "level_info.h"
#include "level_table.h"
#include "save_file.h"
#include "types.h"
#include "pc/lua/utils/smlua_level_utils.h"
#include "pc/lua/utils/smlua_text_utils.h"

#ifdef VERSION_EU
extern s32 gInGameLanguage;
#include "eu_translation.h"
#endif

struct Sm64Char {
    const char *str;
    u32 len;
    u8 c;
    bool menu;
};

#define SM64_CHAR(_str, _c, _menu) { \
    .str = _str, \
    .len = sizeof(_str) - 1, \
    .c = _c, \
    .menu = _menu, \
}

static const struct Sm64Char sSm64CharMap[] = {

    // Digits
    SM64_CHAR("0", 0x00, true),
    SM64_CHAR("1", 0x01, true),
    SM64_CHAR("2", 0x02, true),
    SM64_CHAR("3", 0x03, true),
    SM64_CHAR("4", 0x04, true),
    SM64_CHAR("5", 0x05, true),
    SM64_CHAR("6", 0x06, true),
    SM64_CHAR("7", 0x07, true),
    SM64_CHAR("8", 0x08, true),
    SM64_CHAR("9", 0x09, true),

    // Capital letters
    SM64_CHAR("A", 0x0A, true),
    SM64_CHAR("B", 0x0B, true),
    SM64_CHAR("C", 0x0C, true),
    SM64_CHAR("D", 0x0D, true),
    SM64_CHAR("E", 0x0E, true),
    SM64_CHAR("F", 0x0F, true),
    SM64_CHAR("G", 0x10, true),
    SM64_CHAR("H", 0x11, true),
    SM64_CHAR("I", 0x12, true),
    SM64_CHAR("J", 0x13, true),
    SM64_CHAR("K", 0x14, true),
    SM64_CHAR("L", 0x15, true),
    SM64_CHAR("M", 0x16, true),
    SM64_CHAR("N", 0x17, true),
    SM64_CHAR("O", 0x18, true),
    SM64_CHAR("P", 0x19, true),
    SM64_CHAR("Q", 0x1A, true),
    SM64_CHAR("R", 0x1B, true),
    SM64_CHAR("S", 0x1C, true),
    SM64_CHAR("T", 0x1D, true),
    SM64_CHAR("U", 0x1E, true),
    SM64_CHAR("V", 0x1F, true),
    SM64_CHAR("W", 0x20, true),
    SM64_CHAR("X", 0x21, true),
    SM64_CHAR("Y", 0x22, true),
    SM64_CHAR("Z", 0x23, true),

    // Letters
    SM64_CHAR("a", 0x24, false),
    SM64_CHAR("b", 0x25, false),
    SM64_CHAR("c", 0x26, false),
    SM64_CHAR("d", 0x27, false),
    SM64_CHAR("e", 0x28, false),
    SM64_CHAR("f", 0x29, false),
    SM64_CHAR("g", 0x2A, false),
    SM64_CHAR("h", 0x2B, false),
    SM64_CHAR("i", 0x2C, false),
    SM64_CHAR("j", 0x2D, false),
    SM64_CHAR("k", 0x2E, false),
    SM64_CHAR("l", 0x2F, false),
    SM64_CHAR("m", 0x30, false),
    SM64_CHAR("n", 0x31, false),
    SM64_CHAR("o", 0x32, false),
    SM64_CHAR("p", 0x33, false),
    SM64_CHAR("q", 0x34, false),
    SM64_CHAR("r", 0x35, false),
    SM64_CHAR("s", 0x36, false),
    SM64_CHAR("t", 0x37, false),
    SM64_CHAR("u", 0x38, false),
    SM64_CHAR("v", 0x39, false),
    SM64_CHAR("w", 0x3A, false),
    SM64_CHAR("x", 0x3B, false),
    SM64_CHAR("y", 0x3C, false),
    SM64_CHAR("z", 0x3D, false),

    // Punctuation
    SM64_CHAR(":",   0xE6, false), // colon
    SM64_CHAR(")(",  0xE2, false), // close-open parentheses
    SM64_CHAR("<<",  0xF5, false), // double quote open
    SM64_CHAR(">>",  0xF6, false), // double quote close
    SM64_CHAR("\'",  0x3E, true ), // apostrophe
    SM64_CHAR(".",   0x3F, true ), // period
    SM64_CHAR(",",   0x6F, true ), // comma
    SM64_CHAR(" ",   0x9E, true ), // space
    SM64_CHAR("-",   0x9F, true ), // dash
    SM64_CHAR("(",   0xE1, false), // open parentheses
    SM64_CHAR(")",   0xE3, false), // close parentheses
    SM64_CHAR("&",   0xE5, true ), // ampersand
    SM64_CHAR("!",   0xF2, true ), // exclamation mark
    SM64_CHAR("%",   0xF3, false), // percent
    SM64_CHAR("?",   0xF4, true ), // question mark
    SM64_CHAR("~",   0xF7, false), // tilde

    // Symbols
    SM64_CHAR("/",   0xD0, false),
    SM64_CHAR("the", 0xD1, false),
    SM64_CHAR("you", 0xD2, false),
    SM64_CHAR("[%]", 0xE0, false), // The number of extra stars required to unlock a star door
    SM64_CHAR("[A]", 0x54, false), // bold A
    SM64_CHAR("[B]", 0x55, false), // bold B
    SM64_CHAR("[C]", 0x56, false), // bold C
    SM64_CHAR("[Z]", 0x57, false), // bold Z
    SM64_CHAR("[R]", 0x58, false), // bold R
    SM64_CHAR("+",   0xE4, false), // left-right arrow
    SM64_CHAR("^",   0x50, false), // up arrow
    SM64_CHAR("|",   0x51, false), // down arrow
    SM64_CHAR("<",   0x52, false), // left arrow
    SM64_CHAR(">",   0x53, false), // right arrow
    SM64_CHAR("$",   0xF9, true ), // coin
    SM64_CHAR("★",   0xFA, true ), // star filled
    SM64_CHAR("@",   0xFA, true ), // star filled (both ★ and @ match 0xFA)
    SM64_CHAR("*",   0xFB, true ), // multiply
    SM64_CHAR("•",   0xFC, false), // interpunct (unused)
    SM64_CHAR("=",   0xFD, false), // star empty
    SM64_CHAR("\n",  0xFE, true ), // New line
//  SM64_CHAR(NULL,  0xFF, true ), // Null terminator
};

#define ASCII_TO_SM64_MAX_CHAR_SIZE     1
#define SM64_TO_ASCII_MAX_CHAR_SIZE     4

static const char *ascii_to_sm64_char(u8 *str64, const char *strAscii, bool menu) {
    for (u32 i = 0; i < ARRAY_COUNT(sSm64CharMap); ++i) {
        const struct Sm64Char *ch = &sSm64CharMap[i];
        if (menu && !ch->menu) {
            continue;
        }
        if (memcmp(strAscii, ch->str, ch->len) == 0) {
            *str64 = ch->c;
            return strAscii + ch->len;
        }
    }
    *str64 = 0x9E;
    return strAscii + 1;
}

static char *sm64_to_ascii_char(char *strAscii, u8 c) {
    for (u32 i = 0; i < ARRAY_COUNT(sSm64CharMap); ++i) {
        const struct Sm64Char *ch = &sSm64CharMap[i];
        if (ch->c == c) {
            memcpy(strAscii, ch->str, ch->len);
            return strAscii + ch->len;
        }
    }
    *strAscii = ' ';
    return strAscii + 1;
}

u8 *convert_string_ascii_to_sm64(u8 *str64, const char *strAscii, bool menu) {
    if (!strAscii) { return str64; }

    // allocate string with maximum size
    bool shouldResizeString = false;
    if (!str64) {
        str64 = malloc(ASCII_TO_SM64_MAX_CHAR_SIZE * strlen(strAscii) + 1);
        if (!str64) {
            return NULL;
        }
        shouldResizeString = true;
    }

    // convert string
    u8 *str64End = str64;
    for (; *strAscii != 0; str64End++) {
        strAscii = ascii_to_sm64_char(str64End, strAscii, menu);
    }
    *(str64End++) = 0xFF;

    // resize string if it was allocated by this function
    if (shouldResizeString) {
        u8 *resizedStr64 = realloc(str64, (size_t) (str64End - str64));
        if (resizedStr64) {
            str64 = resizedStr64;
        }
    }

    return str64;
}

static inline size_t strlen64(const u8 *str64) {
    const u8 *str64Begin = str64;
    for (; *str64 != 0xFF; str64++);
    return (size_t) (str64 - str64Begin);
}

char *convert_string_sm64_to_ascii(char *strAscii, const u8 *str64) {
    if (!str64) { return strAscii; }

    // allocate string with maximum size
    bool shouldResizeString = false;
    if (!strAscii) {
        strAscii = malloc(SM64_TO_ASCII_MAX_CHAR_SIZE * strlen64(str64) + 1);
        if (!strAscii) {
            return NULL;
        }
        shouldResizeString = true;
    }

    // convert string
    char *strAsciiEnd = strAscii;
    for (; *str64 != 0xFF; str64++) {
        strAsciiEnd = sm64_to_ascii_char(strAsciiEnd, *str64);
    }
    *(strAsciiEnd++) = 0;

    // resize string if it was allocated by this function
    if (shouldResizeString) {
        char *resizedStrAscii = realloc(strAscii, (size_t) (strAsciiEnd - strAscii));
        if (resizedStrAscii) {
            strAscii = resizedStrAscii;
        }
    }

    return strAscii;
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

void **get_course_name_table(void) {
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

void **get_course_name_table_original(void) {
    void **courseNameTblOrig = segmented_to_virtual(seg2_course_name_table_original);

#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH: courseNameTblOrig = segmented_to_virtual(course_name_table_eu_en_original); break;
        case LANGUAGE_FRENCH:  courseNameTblOrig = segmented_to_virtual(course_name_table_eu_fr_original); break;
        case LANGUAGE_GERMAN:  courseNameTblOrig = segmented_to_virtual(course_name_table_eu_de_original); break;
    }
#endif

    return courseNameTblOrig;
}

void **get_act_name_table(void) {
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

void **get_act_name_table_original(void) {
    void **actNameTblOrig = segmented_to_virtual(seg2_act_name_table_original);

#ifdef VERSION_EU
    switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH: actNameTblOrig = segmented_to_virtual(act_name_table_eu_en_original); break;
        case LANGUAGE_FRENCH:  actNameTblOrig = segmented_to_virtual(act_name_table_eu_fr_original); break;
        case LANGUAGE_GERMAN:  actNameTblOrig = segmented_to_virtual(act_name_table_eu_de_original); break;
    }
#endif

    return actNameTblOrig;
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

    if (courseNum >= 0 && courseNum <= COURSE_MAX && gReplacedCourseActNameTable[courseNum].courseName.modNum != 0) {
        snprintf(output, 256, "%s", gReplacedCourseActNameTable[courseNum].courseName.name.value);
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
        courseNum >= 0 && courseNum <= COURSE_MAX &&
        gReplacedCourseActNameTable[courseNum].actName[starIndex].modNum != 0) {
        snprintf(output, 256, "%s", gReplacedCourseActNameTable[courseNum].actName[starIndex].name.value);
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
