#ifdef TARGET_WEB

#include <stdio.h>
#include <string.h>
#include <emscripten.h>
#include "web_lobby.h"
#include "pc/configfile.h"
#include "pc/network/version.h"
#include "pc/mods/mods.h"

// ---- Query (list rooms) ----

static WebLobbyQueryCallbackPtr sQueryCallback = NULL;
static WebLobbyQueryFinishCallbackPtr sQueryFinishCallback = NULL;

EMSCRIPTEN_KEEPALIVE
void web_lobby_on_room(uint64_t lobbyId, uint16_t connections, uint16_t maxConnections,
                       const char* version, const char* hostName, const char* description) {
    if (sQueryCallback) {
        sQueryCallback(lobbyId, 0, connections, maxConnections,
                       "sm64coopdx", version, hostName, "", description);
    }
}

EMSCRIPTEN_KEEPALIVE
void web_lobby_on_query_finish(void) {
    if (sQueryFinishCallback) {
        sQueryFinishCallback();
    }
}

EM_JS(void, web_lobby_fetch_rooms, (), {
    var baseUrl = (typeof window !== 'undefined' && window.LOBBY_API_URL)
        ? window.LOBBY_API_URL
        : 'https://sm64coopdx-lobby.makeshifted.workers.dev/api';

    fetch(baseUrl + '/rooms')
        .then(function(r) { return r.json(); })
        .then(function(rooms) {
            for (var i = 0; i < rooms.length; i++) {
                var r = rooms[i];
                // Build description from mod list
                var desc = '';
                if (r.modList && r.modList.length > 0) {
                    desc = 'Mods: ' + r.modList.join(', ');
                }
                // Use a hash of roomId as the numeric lobbyId
                var hash = 0;
                var rid = r.roomId || '';
                for (var j = 0; j < rid.length; j++) {
                    hash = ((hash << 5) - hash + rid.charCodeAt(j)) | 0;
                }
                if (hash < 0) hash = -hash;
                // Store roomId in a JS map so we can look it up when joining
                if (!window._webLobbyRoomMap) window._webLobbyRoomMap = {};
                window._webLobbyRoomMap[hash] = rid;

                Module.ccall('web_lobby_on_room', null,
                    ['number', 'number', 'number', 'string', 'string', 'string'],
                    [hash, r.playerCount || 1, r.maxPlayers || 16,
                     r.version || '', r.hostName || '', desc]);
            }
            Module.ccall('web_lobby_on_query_finish', null, [], []);
        })
        .catch(function(e) {
            console.error('[WebLobby] Failed to fetch rooms:', e);
            Module.ccall('web_lobby_on_query_finish', null, [], []);
        });
});

bool ns_web_lobby_query(WebLobbyQueryCallbackPtr callback, WebLobbyQueryFinishCallbackPtr finishCallback) {
    sQueryCallback = callback;
    sQueryFinishCallback = finishCallback;
    web_lobby_fetch_rooms();
    return true;
}

// ---- Register / Heartbeat / Unregister ----

static char sRegisteredRoomId[128] = { 0 };

EM_JS(void, web_lobby_do_register, (const char* roomIdC, const char* hostNameC,
                                     int playerCount, int maxPlayers,
                                     const char* modListJsonC, const char* versionC,
                                     int unlisted), {
    var baseUrl = (typeof window !== 'undefined' && window.LOBBY_API_URL)
        ? window.LOBBY_API_URL
        : 'https://sm64coopdx-lobby.makeshifted.workers.dev/api';

    var body = {
        roomId: UTF8ToString(roomIdC),
        hostName: UTF8ToString(hostNameC),
        playerCount: playerCount,
        maxPlayers: maxPlayers,
        modList: JSON.parse(UTF8ToString(modListJsonC)),
        version: UTF8ToString(versionC),
        unlisted: !!unlisted
    };

    fetch(baseUrl + '/register', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(body)
    }).then(function(r) {
        console.log('[WebLobby] Registered room: ' + body.roomId + ' (status ' + r.status + ')');
    }).catch(function(e) {
        console.warn('[WebLobby] Register failed:', e);
    });

    // Start heartbeat
    if (window._webLobbyHeartbeat) clearInterval(window._webLobbyHeartbeat);
    var rid = body.roomId;
    window._webLobbyHeartbeat = setInterval(function() {
        var pc = 1;
        if (typeof PeerNetwork !== 'undefined' && PeerNetwork.connections) {
            pc = Object.keys(PeerNetwork.connections).length + 1;
        }
        fetch(baseUrl + '/heartbeat', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ roomId: rid, playerCount: pc })
        }).catch(function(e) {
            console.warn('[WebLobby] Heartbeat failed:', e);
        });
    }, 10000);
});

EM_JS(void, web_lobby_do_unregister, (const char* roomIdC), {
    var baseUrl = (typeof window !== 'undefined' && window.LOBBY_API_URL)
        ? window.LOBBY_API_URL
        : 'https://sm64coopdx-lobby.makeshifted.workers.dev/api';

    if (window._webLobbyHeartbeat) {
        clearInterval(window._webLobbyHeartbeat);
        window._webLobbyHeartbeat = null;
    }

    var rid = UTF8ToString(roomIdC);
    var data = JSON.stringify({ roomId: rid });
    if (navigator.sendBeacon) {
        navigator.sendBeacon(baseUrl + '/unregister',
            new Blob([data], { type: 'application/json' }));
    } else {
        fetch(baseUrl + '/unregister', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: data
        }).catch(function() {});
    }
    console.log('[WebLobby] Unregistered room: ' + rid);
});

void ns_web_lobby_register(const char* roomId, bool unlisted) {
    snprintf(sRegisteredRoomId, sizeof(sRegisteredRoomId), "%s", roomId);

    // Build mod list JSON (simple array of strings)
    char modListJson[2048] = "[";
    int pos = 1;
    for (int i = 0; i < gActiveMods.entryCount && pos < 2000; i++) {
        if (i > 0) { modListJson[pos++] = ','; }
        modListJson[pos++] = '"';
        // Copy name, escaping quotes and backslashes
        const char* name = gActiveMods.entries[i]->name;
        for (int j = 0; name[j] && pos < 2040; j++) {
            if (name[j] == '"' || name[j] == '\\') {
                modListJson[pos++] = '\\';
            }
            modListJson[pos++] = name[j];
        }
        modListJson[pos++] = '"';
    }
    modListJson[pos++] = ']';
    modListJson[pos] = '\0';

    web_lobby_do_register(roomId, configPlayerName,
                          1, (int)configAmountOfPlayers,
                          modListJson, get_version(),
                          unlisted ? 1 : 0);
}

void ns_web_lobby_unregister(void) {
    if (sRegisteredRoomId[0] == '\0') return;
    web_lobby_do_unregister(sRegisteredRoomId);
    sRegisteredRoomId[0] = '\0';
}

// Called from beforeunload via shell.html
EMSCRIPTEN_KEEPALIVE
void web_lobby_shutdown(void) {
    ns_web_lobby_unregister();
}

#endif /* TARGET_WEB */
