#include <inttypes.h>
#include "types.h"
#ifdef DISCORD_SDK
#include "pc/discord/discord.h"
#endif

char* network_discord_id_from_local_index(u8 localIndex) {
#ifdef DISCORD_SDK
    static char sDiscordId[64] = "";
    if (localIndex == 0) {
        snprintf(sDiscordId, 64, "%" PRIu64 "", (uint64_t)discord_get_user_id());
        return sDiscordId;
    }
#endif
    return NULL;
}
