#include "user.h"
#include "pc/debuglog.h"
#include "pc/configfile.h"

static void on_current_user_update(UNUSED void* data) {
    LOG_INFO("> on_current_user_update");
    struct DiscordUser user;
    app.users->get_current_user(app.users, &user);
    app.userId = user.id;

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
    LOG_INFO("> discord_user_intitialize");
    static struct IDiscordUserEvents events = { 0 };
    events.on_current_user_update = on_current_user_update;
    return &events;
}