#include "user.h"
#include "pc/configfile.h"
#include "pc/logfile.h"
#include "pc/crash_handler.h"

static void on_current_user_update(UNUSED void* data) {
    LOGFILE_INFO(LFT_DISCORD, "> on_current_user_update");
    struct DiscordUser user = { 0 };
    app.users->get_current_user(app.users, &user);

    // remember user id
    app.userId = user.id;
    gPcDebug.id = user.id;

    // copy over discord username if we haven't set one yet
    if (configPlayerName[0] == '\0' && strlen(user.username) > 0) {
        char* cname = configPlayerName;
        char* dname = user.username;
        for (int i = 0; i < MAX_PLAYER_STRING - 1; i++) {
            if (*dname >= '!' && *dname <= '~') {
                *cname = *dname;
                cname++;
            }
            dname++;
        }
    }
}

struct IDiscordUserEvents* discord_user_initialize(void) {
    LOGFILE_INFO(LFT_DISCORD, "> discord_user_intitialize");
    static struct IDiscordUserEvents events = { 0 };
    events.on_current_user_update = on_current_user_update;
    return &events;
}