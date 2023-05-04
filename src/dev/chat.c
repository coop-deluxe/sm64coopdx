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

#ifdef DEVELOPMENT

static bool str_starts_with(const char* pre, char* str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

bool exec_dev_chat_command(char* command) {
    if (gNetworkSystem == &gNetworkSystemSocket && str_starts_with("/warp ", command)) {
        static const struct { const char *name; s32 num; } sLevelNumByName[] = {
#undef STUB_LEVEL
#undef DEFINE_LEVEL
#define STUB_LEVEL(...)
#define DEFINE_LEVEL(_0, levelnum, _2, levelname, ...) { #levelname, levelnum },
#include "levels/level_defines.h"
#undef STUB_LEVEL
#undef DEFINE_LEVEL
        };

        // Params
        char *paramLevel = command + 6;
        if (*paramLevel == 0 || *paramLevel == ' ') {
            djui_chat_message_create("Missing parameters: [LEVEL] [AREA] [ACT]");
            return true;
        }
        char *paramArea = strchr(paramLevel, ' ');
        if (paramArea++ == NULL || *paramArea == 0 || *paramArea == ' ') {
            djui_chat_message_create("Missing parameters: [AREA] [ACT]");
            return true;
        }
        char *paramAct = strchr(paramArea, ' ');
        if (paramAct++ == NULL || *paramAct == 0 || *paramAct == ' ') {
            djui_chat_message_create("Missing parameters: [ACT]");
            return true;
        }
        *(paramArea - 1) = 0;
        *(paramAct - 1) = 0;

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
                char message[256];
                snprintf(message, 256, "Invalid [LEVEL] parameter: %s", paramLevel);
                djui_chat_message_create(message);
                return true;
            }
        }

        // Area
        s32 area = -1;
        if (sscanf(paramArea, "%d", &area) <= 0) {
            char message[256];
            snprintf(message, 256, "Invalid [AREA] parameter: %s", paramArea);
            djui_chat_message_create(message);
            return true;
        }

        // Act
        s32 act = -1;
        if (sscanf(paramAct, "%d", &act) <= 0) {
            char message[256];
            snprintf(message, 256, "Invalid [ACT] parameter: %s", paramAct);
            djui_chat_message_create(message);
            return true;
        }

        // Warp
        if (!dynos_warp_to_level(level, area, act)) {
            char message[256];
            snprintf(message, 256, "Unable to warp to: %s %s %s", paramLevel, paramArea, paramAct);
            djui_chat_message_create(message);
            return true;
        }

        // OK
        char message[256];
        snprintf(message, 256, "Warping to: %s %s %s...", paramLevel, paramArea, paramAct);
        djui_chat_message_create(message);
        return true;
    }

    if (str_starts_with("/lua ", command)) {
        smlua_exec_str(&command[5]);
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
