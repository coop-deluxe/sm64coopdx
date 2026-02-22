#pragma once

enum LobbySorting {
    LOBBY_SORTING_NONE,
    LOBBY_SORTING_NAME,
    LOBBY_SORTING_GAMEMODE,
    LOBBY_SORTING_PLAYERS,
    LOBBY_SORTING_COUNT,
};

struct LobbySortType {
    const char* langKey;
    enum LobbySorting sortType;
};

struct CoopnetLobby {
    uint64_t lobbyId;
    int playerCount;
    char* hostName;
    char* mode;
    char* playerText;
    char* description;
    bool disabled;
};

void djui_panel_join_lobbies_create(struct DjuiBase* caller, const char* password);
