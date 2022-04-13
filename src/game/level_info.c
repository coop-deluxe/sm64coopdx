#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "course_table.h"
#include "game/memory.h"
#include "level_info.h"
#include "level_table.h"
#include "types.h"

extern u8* seg2_course_name_table[];

static const char charset[0xFF + 1] = {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7
    ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',  // 15
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',  // 23
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',  // 31
    'w', 'x', 'y', 'z', ' ', ' ', ' ', ' ',  // 39
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 49
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 55
    ' ', ' ', ' ', ' ', ' ', ' ', '\'', ' ', // 63
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 71
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 79
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 87
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 95
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 103
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ',',  // 111
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 119
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 127
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 135
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 143
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 151
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-',  // 159
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 167
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 175
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 183
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 192
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 199
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 207
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 215
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 223
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 231
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 239
    ' ', ' ', '!', ' ', ' ', ' ', ' ', ' ',  // 247
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '   // 255
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

const char *get_level_name(s16 courseNum, s16 levelNum, s16 areaIndex) {
    static char stage[188] = { 0 };
    
    //printf("get_level_name: %i %i %i, COURSE_MAX: %u COURSE_MIN: %u.\n", courseNum, levelNum, areaIndex, COURSE_MAX, COURSE_MIN);
    
    // Overrides for non-course based locations.
    if (courseNum == COURSE_NONE) {
        // A switch case is much more effective here
        // then a if statement, It allows for the
        // same results for a different level much easier.
        // It also auto-covers if none of the cases match 
        // with a default.
        switch (levelNum) {
            case LEVEL_CASTLE_GROUNDS:
                strcpy(stage, "Castle Grounds");
                break;
            case LEVEL_CASTLE:
                // Switch case inside a switch case,
                // I think it looks ugly but it works.
                switch (areaIndex) {
                    case 1:
                        strcpy(stage, "Castle Main Floor");
                        break;
                    case 2:
                        strcpy(stage, "Castle Upper Floor");
                        break;
                    case 3:
                        strcpy(stage, "Castle Basement");
                        break;
                    default: // If we don't have a proper corresponding area, We return the default.
                        strcpy(stage, "Castle Purgatory");
                        break;
                }
                break;
            case LEVEL_CASTLE_COURTYARD:
                strcpy(stage, "Castle Courtyard");
                break;
            default: // If we don't have a proper corresponding level, We return the default.
                strcpy(stage, "Peach's Castle");
                break;
        }
        return stage;
    }

    // If we are in in Course 0 we are in the castle which doesn't have a string.
    if (COURSE_IS_VALID_COURSE(courseNum)) {
        void **courseNameTbl = NULL;

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
        u8 *courseName = segmented_to_virtual(courseNameTbl[courseNum - 1]);

        convert_string(&courseName[3], stage);
    } else {
        strcpy(stage, "Peach's Castle");
    }

    return stage;
}
