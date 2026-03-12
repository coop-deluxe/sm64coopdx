#!/usr/bin/env node
"use strict";

const dgram = require("dgram");
const http = require("http");
const { WebSocketServer } = require("ws");

// ---------------------------------------------------------------------------
// Configuration: CLI args take precedence over env vars, then defaults.
// ---------------------------------------------------------------------------
function parseArgs() {
  const args = process.argv.slice(2);
  const opts = {};
  for (let i = 0; i < args.length; i++) {
    if (args[i] === "--target-host" && args[i + 1]) {
      opts.targetHost = args[++i];
    } else if (args[i] === "--target-port" && args[i + 1]) {
      opts.targetPort = parseInt(args[++i], 10);
    } else if (args[i] === "--listen-port" && args[i + 1]) {
      opts.listenPort = parseInt(args[++i], 10);
    }
  }
  return opts;
}

const cliOpts = parseArgs();
const TARGET_HOST = cliOpts.targetHost || process.env.TARGET_HOST || "127.0.0.1";
const TARGET_PORT = cliOpts.targetPort || parseInt(process.env.TARGET_PORT, 10) || 7777;
const LISTEN_PORT = cliOpts.listenPort || parseInt(process.env.LISTEN_PORT, 10) || 8765;

// ---------------------------------------------------------------------------
// HTTP server — serves only as the WebSocket upgrade target and responds to
// plain HTTP requests with CORS-aware 426 (Upgrade Required).
// ---------------------------------------------------------------------------
const httpServer = http.createServer((req, res) => {
  res.setHeader("Access-Control-Allow-Origin", "*");
  res.setHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
  res.setHeader("Access-Control-Allow-Headers", "Content-Type");

  if (req.method === "OPTIONS") {
    res.writeHead(204);
    res.end();
    return;
  }

  res.writeHead(426, { "Content-Type": "text/plain" });
  res.end("426 Upgrade Required — connect via WebSocket\n");
});

// ---------------------------------------------------------------------------
// WebSocket server
// ---------------------------------------------------------------------------
const wss = new WebSocketServer({
  server: httpServer,
  // Accept only binary frames by default; we will filter in the handler.
  perMessageDeflate: false,
});

let connectionId = 0;

wss.on("connection", (ws, req) => {
  const id = ++connectionId;
  const clientAddr = req.socket.remoteAddress + ":" + req.socket.remotePort;
  let packetsToServer = 0;
  let packetsToClient = 0;

  console.log(`[${id}] WebSocket connected from ${clientAddr}`);

  // Create a dedicated UDP socket for this WebSocket session.
  const udp = dgram.createSocket("udp4");

  // Track whether we have already cleaned up.
  let closed = false;
  function cleanup() {
    if (closed) return;
    closed = true;
    console.log(
      `[${id}] Session ended — packets sent: ${packetsToServer}, received: ${packetsToClient}`
    );
    try { udp.close(); } catch (_) { /* ignore */ }
    if (ws.readyState === ws.OPEN || ws.readyState === ws.CONNECTING) {
      try { ws.close(); } catch (_) { /* ignore */ }
    }
  }

  // --- UDP -> WebSocket ---------------------------------------------------
  udp.on("message", (msg) => {
    if (closed) return;
    packetsToClient++;
    try {
      ws.send(msg, { binary: true });
    } catch (err) {
      console.error(`[${id}] Error sending to WebSocket: ${err.message}`);
      cleanup();
    }
  });

  udp.on("error", (err) => {
    console.error(`[${id}] UDP error: ${err.message}`);
    cleanup();
  });

  // Bind to an ephemeral port so we can receive responses.
  udp.bind(0);

  // --- WebSocket -> UDP ---------------------------------------------------
  ws.on("message", (data, isBinary) => {
    // Ignore text frames; only forward binary data.
    if (!isBinary) return;

    packetsToServer++;
    udp.send(data, TARGET_PORT, TARGET_HOST, (err) => {
      if (err) {
        console.error(`[${id}] UDP send error: ${err.message}`);
        cleanup();
      }
    });
  });

  ws.on("close", () => {
    console.log(`[${id}] WebSocket closed`);
    cleanup();
  });

  ws.on("error", (err) => {
    console.error(`[${id}] WebSocket error: ${err.message}`);
    cleanup();
  });
});

// ---------------------------------------------------------------------------
// Start listening
// ---------------------------------------------------------------------------
httpServer.listen(LISTEN_PORT, () => {
  console.log("===========================================");
  console.log(" SM64CoopDX WebSocket-to-UDP Proxy");
  console.log("===========================================");
  console.log(` Listening on     : ws://0.0.0.0:${LISTEN_PORT}`);
  console.log(` Target UDP server: ${TARGET_HOST}:${TARGET_PORT}`);
  console.log("===========================================");
});
