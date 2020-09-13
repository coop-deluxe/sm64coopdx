#include "user.h"
#include "pc/debuglog.h"

static void on_current_user_update(UNUSED void* data) {
    LOG_INFO("> on_current_user_update");
    struct DiscordUser user;
    app.users->get_current_user(app.users, &user);
    app.userId = user.id;
}

struct IDiscordUserEvents* discord_user_initialize(void) {
    static struct IDiscordUserEvents events = { 0 };
    events.on_current_user_update = on_current_user_update;
    return &events;
}