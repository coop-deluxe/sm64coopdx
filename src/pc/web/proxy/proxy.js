#!/usr/bin/env node
"use strict";
/**
 * SM64CoopDX WebSocket-to-UDP Proxy
 *
 * Supports two modes based on WebSocket URL query parameters:
 *
 * CLIENT MODE (default): ws://proxy:PORT/?target=HOST:PORT
 *   Browser joins a native UDP server. 1:1 WebSocket <-> UDP mapping.
 *
 * HOST MODE: ws://proxy:PORT/?host=UDPPORT
 *   Browser hosts a game. Proxy opens a UDP listener on UDPPORT.
 *   Native clients connect to the proxy's UDP port. All client traffic
 *   is multiplexed over the single WebSocket with a 2-byte slot prefix:
 *     [u16 LE slotId][packetData]
 *   slotId 0 = broadcast to all clients
 */

const dgram = require("dgram");
const http = require("http");
const { WebSocketServer } = require("ws");

// Configuration
const LISTEN_PORT = parseInt(process.env.LISTEN_PORT || "8765");
for (let i = 2; i < process.argv.length; i++) {
    if (process.argv[i] === "--listen-port" && process.argv[i + 1]) {
        LISTEN_PORT = parseInt(process.argv[++i]);
    }
}

// HTTP server with CORS
const httpServer = http.createServer((req, res) => {
    res.setHeader("Access-Control-Allow-Origin", "*");
    res.setHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
    res.setHeader("Access-Control-Allow-Headers", "*");
    if (req.method === "OPTIONS") { res.writeHead(204); res.end(); return; }
    res.writeHead(200, { "Content-Type": "text/plain" });
    res.end("SM64CoopDX WebSocket-UDP Proxy\nClient: ws://HOST:PORT/?target=SERVER:PORT\nHost:   ws://HOST:PORT/?host=UDPPORT\n");
});

const wss = new WebSocketServer({ server: httpServer, perMessageDeflate: false });

// ============================================================================
// CLIENT MODE: Browser joins native server
// ============================================================================
function handleClientMode(ws, targetHost, targetPort, label) {
    const udp = dgram.createSocket("udp6");
    let sent = 0, recv = 0, closed = false;

    function cleanup() {
        if (closed) return; closed = true;
        console.log(`[${label}] Ended (sent:${sent} recv:${recv})`);
        try { udp.close(); } catch(_) {}
        if (ws.readyState <= 1) try { ws.close(); } catch(_) {}
    }

    udp.bind(0);
    console.log(`[${label}] Forwarding to ${targetHost}:${targetPort}`);

    // WS -> UDP
    ws.on("message", (data, isBinary) => {
        if (!isBinary || closed) return;
        sent++;
        udp.send(data, targetPort, targetHost, (err) => { if (err) cleanup(); });
    });

    // UDP -> WS
    udp.on("message", (msg) => {
        if (closed) return;
        recv++;
        try { ws.send(msg, { binary: true }); } catch(_) { cleanup(); }
    });

    udp.on("error", (e) => { console.error(`[${label}] UDP err: ${e.message}`); cleanup(); });
    ws.on("close", cleanup);
    ws.on("error", (e) => { console.error(`[${label}] WS err: ${e.message}`); cleanup(); });
}

// ============================================================================
// HOST MODE: Browser hosts, native clients join via UDP
// ============================================================================
function handleHostMode(ws, hostPort, label) {
    const udp = dgram.createSocket({ type: "udp6", reuseAddr: true });
    let closed = false;

    // Client tracking: addr -> slot, slot -> addr
    const addrToSlot = new Map();
    const slotToAddr = new Map();
    let nextSlot = 1; // 0 = broadcast

    function cleanup() {
        if (closed) return; closed = true;
        console.log(`[${label}] Host ended (${slotToAddr.size} clients connected)`);
        try { udp.close(); } catch(_) {}
        if (ws.readyState <= 1) try { ws.close(); } catch(_) {}
    }

    // Set dual-stack and bind
    udp.on("listening", () => {
        const a = udp.address();
        console.log(`[${label}] UDP listening on ${a.address}:${a.port}`);
    });

    udp.on("error", (e) => {
        console.error(`[${label}] UDP error: ${e.message}`);
        cleanup();
    });

    // Bind to the requested port
    try {
        udp.bind(hostPort, "::");
    } catch (e) {
        console.error(`[${label}] Failed to bind port ${hostPort}: ${e.message}`);
        ws.close();
        return;
    }

    // Native UDP client -> WebSocket host (with slot prefix)
    udp.on("message", (msg, rinfo) => {
        if (closed) return;
        const key = rinfo.address + ":" + rinfo.port;
        let slot = addrToSlot.get(key);
        if (slot === undefined) {
            slot = nextSlot++;
            addrToSlot.set(key, slot);
            slotToAddr.set(slot, { address: rinfo.address, port: rinfo.port });
            console.log(`[${label}] Client slot ${slot}: ${key}`);
        }
        // Prepend 2-byte LE slot ID
        const buf = Buffer.alloc(2 + msg.length);
        buf.writeUInt16LE(slot, 0);
        msg.copy(buf, 2);
        try { ws.send(buf, { binary: true }); } catch(_) { cleanup(); }
    });

    // WebSocket host -> Native UDP client (strip slot prefix)
    ws.on("message", (data, isBinary) => {
        if (!isBinary || closed || data.length < 3) return;
        const slot = data.readUInt16LE(0);
        const payload = data.slice(2);

        if (slot === 0) {
            // Broadcast to all clients
            for (const [, c] of slotToAddr) {
                udp.send(payload, c.port, c.address);
            }
        } else {
            const client = slotToAddr.get(slot);
            if (client) {
                udp.send(payload, client.port, client.address, (err) => {
                    if (err) console.error(`[${label}] Send to slot ${slot} err: ${err.message}`);
                });
            }
        }
    });

    ws.on("close", cleanup);
    ws.on("error", (e) => { console.error(`[${label}] WS err: ${e.message}`); cleanup(); });
}

// ============================================================================
// Connection router
// ============================================================================
let connId = 0;
wss.on("connection", (ws, req) => {
    const id = ++connId;
    const url = new URL(req.url, `http://${req.headers.host}`);
    const hostPort = url.searchParams.get("host");
    const target = url.searchParams.get("target");

    if (hostPort) {
        handleHostMode(ws, parseInt(hostPort), `#${id} Host:${hostPort}`);
    } else {
        let tHost = "127.0.0.1", tPort = 7777;
        if (target) {
            const [h, p] = target.split(":");
            if (h) tHost = h;
            if (p) tPort = parseInt(p);
        }
        handleClientMode(ws, tHost, tPort, `#${id} Client`);
    }
});

httpServer.listen(LISTEN_PORT, () => {
    console.log("==============================================");
    console.log("  SM64CoopDX WebSocket-UDP Proxy");
    console.log("==============================================");
    console.log(`  Listening: ws://localhost:${LISTEN_PORT}`);
    console.log(`  Client:    ws://localhost:${LISTEN_PORT}/?target=HOST:PORT`);
    console.log(`  Host:      ws://localhost:${LISTEN_PORT}/?host=PORT`);
    console.log("==============================================");
});
