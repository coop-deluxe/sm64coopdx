#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <stdbool.h>
#include "network.h"

enum DisconnectType {
    DC_LEAVE,
    DC_KICK,
    DC_BAN
};

/* |description|Gets a player's global index from their local index|descriptionEnd| */
u8 network_global_index_from_local(u8 localIndex);
/* |description|Gets a player's local index from their global index|descriptionEnd| */
u8 network_local_index_from_global(u8 globalIndex);

/* |description|Checks if you are hosting the current lobby, this value doesn't change|descriptionEnd| */
bool network_is_server(void);
/* |description|Checks if you are a moderator in the current lobby|descriptionEnd| */
bool network_is_moderator(void);

u8* network_get_player_text_color(u8 localIndex);
/* |description|Gets the DJUI hex color code string for the player corresponding to `localIndex`'s cap color|descriptionEnd| */
const char* network_get_player_text_color_string(u8 localIndex);
/* |description|Gets the complete player name, including the player's starting hex code.|descriptionEnd| */
const char* network_get_complete_player_name(u8 localIndex);

/* |description|Checks if the game can currently be paused in singleplayer|descriptionEnd| */
bool network_check_singleplayer_pause(void);

/* |description|Gets a Discord ID corresponding to the network player with `localIndex`|descriptionEnd| */
const char* network_discord_id_from_local_index(u8 localIndex);

/* |description|Disconnects the local player with DisconnectType `dcType` (default is DC_LEAVE) because of `reason` (optional).|descriptionEnd| */
void network_disconnect(OPTIONAL enum DisconnectType dcType, OPTIONAL const char* reason);

#endif