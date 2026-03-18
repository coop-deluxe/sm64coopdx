# SM64CoopDX WebSocket-to-UDP Proxy

A lightweight proxy that allows the SM64CoopDX web port (browser) to connect to native game servers. Browsers cannot use UDP directly, so this proxy bridges WebSocket connections to the UDP-based game server.

Each WebSocket connection is mapped 1:1 to a dedicated UDP socket that communicates with the target server.

## Setup

```bash
cd src/pc/web/proxy
npm install
```

## Usage

Start a native SM64CoopDX server on its default port (7777), then run:

```bash
node proxy.js --target-host 127.0.0.1 --target-port 7777 --listen-port 8765
```

In the web client, connect to: `ws://localhost:8765`

All three flags are optional and fall back to environment variables or built-in defaults:

| Flag             | Env var       | Default     |
|------------------|---------------|-------------|
| `--target-host`  | `TARGET_HOST` | `127.0.0.1` |
| `--target-port`  | `TARGET_PORT` | `7777`       |
| `--listen-port`  | `LISTEN_PORT` | `8765`       |

You can also use environment variables instead of flags:

```bash
TARGET_HOST=192.168.1.50 TARGET_PORT=7777 LISTEN_PORT=9000 node proxy.js
```

## How It Works

1. A browser opens a WebSocket connection to the proxy.
2. The proxy creates a UDP socket bound to an ephemeral port.
3. Binary WebSocket frames are forwarded as UDP packets to the target server.
4. UDP responses from the server are sent back to the browser over WebSocket.
5. When the WebSocket closes, the UDP socket is cleaned up.

Text WebSocket frames are ignored; only binary frames are forwarded.
