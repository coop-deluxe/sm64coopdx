#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "level_info.h"
#include "game/memory.h"

extern u8 seg2_course_name_table[];

static const char charset[0xFF + 1] = {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 7
    ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', // 15
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', // 23
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', // 31
    'w', 'x', 'y', 'z', ' ', ' ', ' ', ' ', // 39
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 49
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 55
    ' ', ' ', ' ', ' ', ' ', ' ', '\'', ' ', // 63
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 71
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 79
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 87
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 95
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 103
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ',', // 111
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 119
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 127
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 135
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 143
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 151
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-', // 159
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 167
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 175
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 183
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 192
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 199
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 207
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 215
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 223
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 231
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 239
    ' ', ' ', '!', ' ', ' ', ' ', ' ', ' ', // 247
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '  // 255
};

static void convert_string(const u8* str, char* output) {
    s32 strPos = 0;
    bool capitalizeChar = true;

    while (str[strPos] != 0xFF) {
        if (str[strPos] < 0xFF) {
            output[strPos] = charset[str[strPos]];

            // if the char is a letter we can capatalize it
            if (capitalizeChar && 0x0A <= str[strPos] && str[strPos] <= 0x23) {
                output[strPos] -= ('a' - 'A');
                capitalizeChar = false;
            }

        }
        else {
            output[strPos] = ' ';
        }

        // decide if the next character should be capitalized
        switch (output[strPos]) {
        case ' ':
            //if (str[strPos] != 158)
                //fprintf(stdout, "Unknown Character (%i)\n", str[strPos]); // inform that an unknown char was found
        case '-':
            capitalizeChar = true;
            break;
        default:
            capitalizeChar = false;
            break;
        }

        strPos++;
    }

    output[strPos] = '\0';
}

const char* get_level_name(s16 courseNum, s16 levelNum, s16 areaIndex) {
    static char stage[188];
    // overrides for castle locations
    if (courseNum == 0 && levelNum == 16) {
        strcpy(stage, "Castle Grounds");
        return stage;
    }
    if (courseNum == 0 && levelNum == 6) {
        if (areaIndex == 1) {
            strcpy(stage, "Castle Main Floor");
            return stage;
        }
        else if (areaIndex == 2) {
            strcpy(stage, "Castle Upper Floor");
            return stage;
        }
        else if (areaIndex == 3) {
            strcpy(stage, "Castle Basement");
            return stage;
        }
    }
    if (courseNum == 0 && levelNum == 26) {
        strcpy(stage, "Castle Courtyard");
        return stage;
    }

    // If we are in in Course 0 we are in the castle which doesn't have a string
    if (courseNum > 0 && courseNum < 27) {
        void** courseNameTbl;

#ifndef VERSION_EU
        courseNameTbl = segmented_to_virtual(seg2_course_name_table);
#else
        switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_en);
            break;
        case LANGUAGE_FRENCH:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_fr);
            break;
        case LANGUAGE_GERMAN:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_de);
            break;
        }
#endif
        u8* courseName = segmented_to_virtual(courseNameTbl[courseNum - 1]);

        convert_string(&courseName[3], stage);
    } else {
        strcpy(stage, "Peach's Castle");
    }

    return stage;
}
