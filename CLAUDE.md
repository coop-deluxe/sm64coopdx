# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

SM64CoopDX is an online multiplayer mod for Super Mario 64, originally a native C application. The `feature/emscripten-web-port` branch adds a browser-based version using Emscripten/WebAssembly with PeerJS (WebRTC) for peer-to-peer multiplayer networking.

## Build Commands

### Web (Emscripten) Build
```bash
# Prerequisites: Emscripten SDK installed at ~/emsdk or /usr/local/emsdk
./build_web.sh              # Incremental build (DEBUG=1, VERSION=us)
./build_web.sh clean        # Clean build (removes build/us_pc first)
```
Under the hood: `emmake make TARGET_WEB=1 VERSION=us DEBUG=1 -j$(nproc)`

### Serve Locally
```bash
./serve.sh   # Starts HTTP server (port 8083) + WebSocket proxy (port 8765)
# Game at: http://localhost:8083/sm64coopdx.html
```

The HTTP server (`python3 -m http.server`) does NOT set COOP/COEP headers needed for SharedArrayBuffer. Use `src/pc/web/serve.py` if you need those headers.

### Proxy Server (standalone)
```bash
cd src/pc/web/proxy && npm install
node proxy.js --target-host 127.0.0.1 --target-port 7777 --listen-port 8765
```

## Architecture: Web/Emscripten Port

### Platform Abstraction

The codebase uses conditional compilation (`#ifdef TARGET_WEB`) and pluggable backends via function-pointer structs:

- **Network:** `struct NetworkSystem` in `network.h` — on web, points to WebSocket/PeerJS implementation
- **Threading:** `src/pc/thread_web.c` — all no-ops (single-threaded on web)
- **Sockets:** `src/pc/network/socket/socket.h` conditionally includes `socket_websocket.h` instead of platform UDP headers

### PeerJS Networking (the key web-specific system)

**Two layers:**

1. **JavaScript side** (`src/pc/web/shell.html`, lines ~567-747): `PeerNetwork` object
   - Manages PeerJS Peer instances, DataConnections, slot ID assignment
   - Deterministic host peer ID: `'sm64-' + roomId + '-host'`
   - Auto-detection: tries to register as host first; falls back to client on `unavailable-id` error
   - Maintains `recvBuffer` array of `{slotId, data}` packets

2. **C side** (`src/pc/network/socket/socket_websocket.c`): EM_JS bridge functions
   - `peer_init(roomId)`, `peer_send(slotId, data, len)`, `peer_drain_recv()`, `peer_is_connected()`, `peer_shutdown()`
   - Ring buffer `sRecvBuf[128KB]` with packet format: `[u16 slotId LE][u16 length LE][data...]`

**Packet flow:**
```
PeerJS DataConnection → JS recvBuffer → peer_drain_recv() → C sRecvBuf
→ network_update() processes → peer_send() EM_JS → PeerNetwork.send() → DataConnection
```

**Host relay:** The host (whether web or native) relays packets between clients. Broadcast packets (slotId=0) go to all except sender. This is handled in `network.c` (~lines 206-245).

### WebSocket-to-UDP Proxy (`src/pc/web/proxy/proxy.js`)

Alternative transport for browser↔native server communication. Two modes via query params:
- **Client mode** (`?target=HOST:PORT`): 1:1 WebSocket↔UDP bridge
- **Host mode** (`?host=UDPPORT`): multiplexes clients with 2-byte slot prefix

### Game Loop on Web (`src/pc/pc_main.c`)

Uses `requestAnimationFrame` (not `emscripten_set_main_loop`) calling `web_one_iteration()` at 30 Hz. Each frame: handle SDL events → `network_update()` (drain PeerJS packets) → game logic → Lua scripting. Audio is disabled on web.

### Persistence

- **Config:** `localStorage['sm64coopdx_config']` restored to Emscripten VFS on startup
- **Save files:** `localStorage['sm64coopdx_save']` (base64), persisted via `web_save_savefile()`
- **ROM:** Cached in IndexedDB, validated by Z64 magic number, byte-swapped from N64/V64 formats

### Emscripten Linker Settings

Key flags in Makefile (~lines 941-952):
- `ASYNCIFY` with 65536 stack — allows C to call async JS
- `INITIAL_MEMORY=268435456` (256MB), `ALLOW_MEMORY_GROWTH`
- `FORCE_FILESYSTEM` + `libidbfs.js` for virtual filesystem
- Exported runtime: `ccall`, `cwrap`, `FS`, `allocateUTF8`

### Disabled on Web

Discord SDK, CoopNet (cloud hosting), Mumble voice, update checker, native threading.

## Key Files

| File | Role |
|------|------|
| `src/pc/web/shell.html` | Emscripten HTML shell + PeerNetwork JS (~857 lines) |
| `src/pc/network/socket/socket_websocket.c` | C↔JS bridge via EM_JS (~360 lines) |
| `src/pc/network/network.c` | Core networking, relay logic |
| `src/pc/network/network.h` | NetworkSystem struct, NetworkType enum |
| `src/pc/pc_main.c` | Game entry, `web_one_iteration()` |
| `src/pc/web/web_main.c` | ROM/config persistence, URL param handling |
| `src/pc/web/proxy/proxy.js` | WebSocket↔UDP proxy server |
| `src/pc/network/packets/packet.c` | Packet processing pipeline (45+ packet types) |

## URL Parameters

The web build supports auto-join/host via URL:
- `?room=NAME` — PeerJS room identifier
- `?join=HOST:PORT` — auto-join a server
- `?host=PORT` — auto-host a server

## CI/CD

`.github/workflows/build-web.yaml` builds on Ubuntu 22.04 with emsdk 3.1.64, deploys to GitHub Pages.
