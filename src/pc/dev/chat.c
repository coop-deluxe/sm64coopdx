#include "pc/network/network.h"
#include "pc/network/socket/socket.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_chat_message.h"
#include "pc/chat_commands.h"
#include "pc/network/ban_list.h"
#include "pc/network/moderator_list.h"
#include "pc/debuglog.h"
#include "pc/lua/utils/smlua_level_utils.h"
#include "level_table.h"
#include "game/save_file.h"

#ifdef DEVELOPMENT

static bool str_starts_with(const char* pre, char* str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

// For case insensitivity
static const char *upper(char *str) {
    static char buffer[50];
    if (strlen(str) > 50) { return NULL; }
    memset(buffer, 0, 50);
    s16 i = 0;
    while (str[i] != '\0' && i < 49) {
        buffer[i] = toupper((unsigned char) str[i]);
        i++;
    }
    buffer[i] = '\0';
    return buffer;
}

static s32 get_level_abbreviation_alt(const char *str) {

    // c + course number translates to that level
    // e.g. c11 is wdw
    if (str[0] == 'C' && strlen(str) > 1) {
        s32 course = -1;
        if (sscanf(&str[1], "%d", &course) > 0) {
            s32 level = get_level_num_from_course_num(course);
            if (level == LEVEL_NONE) { return -1; } // Failed!
            return level;
        }
    }

    if (strcmp(str, "S1") == 0) { return LEVEL_PSS; }
    if (strcmp(str, "S2") == 0) { return LEVEL_WMOTR; }
    if (strcmp(str, "S3") == 0) { return LEVEL_SA; }
    if (strcmp(str, "S4") == 0) { return LEVEL_ENDING; }

    if (strcmp(str, "WC") == 0) { return LEVEL_TOTWC; }
    if (strcmp(str, "VC") == 0) { return LEVEL_VCUTM; }
    if (strcmp(str, "MC") == 0) { return LEVEL_COTMC; }

    if (strcmp(str, "B1") == 0) { return LEVEL_BITDW; }
    if (strcmp(str, "B2") == 0) { return LEVEL_BITFS; }
    if (strcmp(str, "B3") == 0) { return LEVEL_BITS; }

    if (strcmp(str, "B1F") == 0) { return LEVEL_BOWSER_1; }
    if (strcmp(str, "B2F") == 0) { return LEVEL_BOWSER_2; }
    if (strcmp(str, "B3F") == 0) { return LEVEL_BOWSER_3; }

    if (strcmp(str, "OW1") == 0) { return LEVEL_CASTLE_GROUNDS; }
    if (strcmp(str, "OW2") == 0) { return LEVEL_CASTLE; }
    if (strcmp(str, "OW3") == 0) { return LEVEL_CASTLE_COURTYARD; }

    return -1;
}

bool exec_dev_chat_command(char* command) {
    if (strcmp("/warp", command) == 0) {
        djui_chat_message_create("Missing parameters: [LEVEL] [AREA] [ACT]");
        return true;
    }

    if (str_starts_with("/warp ", command)) {
        static const struct { const char *name; s32 num; } sLevelNumByName[] = {
#undef STUB_LEVEL
#undef DEFINE_LEVEL
#define STUB_LEVEL(...)
#define DEFINE_LEVEL(_0, levelnum, _2, levelname, ...) { #levelname, levelnum },
#include "levels/level_defines.h"
#undef STUB_LEVEL
#undef DEFINE_LEVEL
        };
        s32 area = 1;
        s32 act = 0;

        // Params
        char *paramLevel = command + 6;
        if (*paramLevel == 0 || *paramLevel == ' ') {
            djui_chat_message_create("Missing parameters: [LEVEL]");
            return true;
        }
        char *paramArea = strchr(paramLevel, ' ');
        char *paramAct = NULL;
        if (paramArea++ == NULL || *paramArea == 0 || *paramArea == ' ') {
            paramArea = NULL;
        } else {
            *(paramArea - 1) = 0;
            paramAct = strchr(paramArea, ' ');
            if (paramAct++ == NULL || *paramAct == 0 || *paramAct == ' ') {
                paramAct = NULL;
            } else {
                *(paramAct - 1) = 0;
            }
        }

        // Level
        s32 level = -1;
        if (sscanf(paramLevel, "%d", &level) <= 0) {
            for (s32 i = 0; i != (s32) (sizeof(sLevelNumByName) / sizeof(sLevelNumByName[0])); ++i) {
                if (strstr(paramLevel, sLevelNumByName[i].name) == paramLevel) {
                    level = sLevelNumByName[i].num;
                    break;
                }
            }
            if (level == -1) {
                struct CustomLevelInfo* info = smlua_level_util_get_info_from_short_name(paramLevel);
                if (info != NULL) {
                    level = info->levelNum;
                }
            }
            if (level == -1) {
                level = get_level_abbreviation_alt(upper(paramLevel));
            }
            if (level == -1) {
                char message[256];
                snprintf(message, 256, "Invalid [LEVEL] parameter: %s", paramLevel);
                djui_chat_message_create(message);
                return true;
            }
        }

        // Area
        if (paramArea && sscanf(paramArea, "%d", &area) <= 0) {
            char message[256];
            snprintf(message, 256, "Invalid [AREA] parameter: %s", paramArea);
            djui_chat_message_create(message);
            return true;
        }

        // Act
        if (paramAct && sscanf(paramAct, "%d", &act) <= 0) {
            char message[256];
            snprintf(message, 256, "Invalid [ACT] parameter: %s", paramAct);
            djui_chat_message_create(message);
            return true;
        }

        // Warp
        if (!dynos_warp_to_level(level, area, act)) {
            char message[256];
            snprintf(message, 256, "Unable to warp to: %s %d %d", paramLevel, area, act);
            djui_chat_message_create(message);
            return true;
        }

        // OK
        char message[256];
        snprintf(message, 256, "Warping to: %s %d %d...", paramLevel, area, act);
        djui_chat_message_create(message);
        return true;
    }

    if (strcmp("/lua", command) == 0) {
        djui_chat_message_create("Missing parameter: [LUA]");
        return true;
    }

    if (str_starts_with("/lua ", command)) {
        smlua_exec_str(&command[5]);
        return true;
    }

    if (strcmp("/luaf", command) == 0) {
        djui_chat_message_create("Missing parameter: [FILENAME]");
        return true;
    }

    if (str_starts_with("/luaf ", command)) {
        smlua_exec_file(&command[6]);
        return true;
    }

    return false;
}

void dev_display_chat_commands(void) {
    djui_chat_message_create("/warp [LEVEL] [AREA] [ACT] - Level can be either a numeric value or a shorthand name");
    djui_chat_message_create("/lua [LUA] - Execute Lua code from a string");
    djui_chat_message_create("/luaf [FILENAME] - Execute Lua code from a file");
}
#endif