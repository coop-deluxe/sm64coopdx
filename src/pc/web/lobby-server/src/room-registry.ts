export interface RoomInfo {
  roomId: string;
  hostName: string;
  playerCount: number;
  maxPlayers: number;
  modList: string[];
  version: string;
  createdAt: number;
  lastHeartbeat: number;
  unlisted: boolean;
}

const ROOM_TTL_MS = 30_000;

// ---- PeerJS-compatible WebRTC signaling server ----
// Peers connect via WebSocket to /peerjs?id=PEER_ID
// Server routes {type, src, dst, payload} messages between peers.

export class RoomRegistry {
  private rooms: Map<string, RoomInfo> = new Map();
  private peers: Map<string, WebSocket> = new Map(); // peerId -> WebSocket

  constructor(private state: DurableObjectState, _env: unknown) {}

  // Called by Cloudflare when a WebSocket message arrives (hibernate API)
  async webSocketMessage(ws: WebSocket, message: string | ArrayBuffer): Promise<void> {
    try {
      const msg = JSON.parse(typeof message === "string" ? message : new TextDecoder().decode(message));
      const { type, dst, payload } = msg;
      const src = (ws as unknown as { _peerId: string })._peerId;
      if (!src) return;

      if (type === "HEARTBEAT") {
        ws.send(JSON.stringify({ type: "HEARTBEAT" }));
        return;
      }
      if (type === "LEAVE" || type === "EXPIRE") {
        this.peers.delete(src);
        return;
      }
      // Route OFFER, ANSWER, CANDIDATE, etc. to destination peer
      if (dst) {
        const dstWs = this.peers.get(dst);
        if (dstWs) {
          dstWs.send(JSON.stringify({ type, src, dst, payload }));
        } else {
          ws.send(JSON.stringify({ type: "EXPIRE", src: dst }));
        }
      }
    } catch (_) { /* ignore malformed */ }
  }

  async webSocketClose(ws: WebSocket): Promise<void> {
    const peerId = (ws as unknown as { _peerId: string })._peerId;
    if (peerId) this.peers.delete(peerId);
  }

  async webSocketError(ws: WebSocket): Promise<void> {
    const peerId = (ws as unknown as { _peerId: string })._peerId;
    if (peerId) this.peers.delete(peerId);
  }

  private handlePeerJS(request: Request): Response {
    const url = new URL(request.url);
    const peerId = url.searchParams.get("id");
    if (!peerId) return new Response("id required", { status: 400 });

    if (this.peers.has(peerId)) {
      // ID already taken — close existing and replace (handles page refresh)
      const existing = this.peers.get(peerId)!;
      existing.close(1000, "replaced");
      this.peers.delete(peerId);
    }

    const { 0: client, 1: server } = new WebSocketPair();
    this.state.acceptWebSocket(server);
    // Tag this WebSocket with the peer ID for routing
    (server as unknown as { _peerId: string })._peerId = peerId;
    this.peers.set(peerId, server);

    // Send OPEN to confirm registration
    server.send(JSON.stringify({ type: "OPEN" }));

    return new Response(null, { status: 101, webSocket: client });
  }

  async fetch(request: Request): Promise<Response> {
    const url = new URL(request.url);
    const path = url.pathname;

    // PeerJS WebRTC signaling — WebSocket upgrade
    if (path === "/peerjs" && request.headers.get("Upgrade") === "websocket") {
      return this.handlePeerJS(request);
    }

    if (request.method === "POST" && path === "/register") {
      return this.handleRegister(request);
    }
    if (request.method === "POST" && path === "/heartbeat") {
      return this.handleHeartbeat(request);
    }
    if (request.method === "POST" && path === "/unregister") {
      return this.handleUnregister(request);
    }
    if (request.method === "GET" && path === "/rooms") {
      return this.handleList();
    }

    return new Response("Not Found", { status: 404 });
  }

  private async handleRegister(request: Request): Promise<Response> {
    const body = await request.json() as Partial<RoomInfo>;
    if (!body.roomId || !body.hostName) {
      return new Response(JSON.stringify({ error: "roomId and hostName required" }), { status: 400 });
    }

    const now = Date.now();
    const room: RoomInfo = {
      roomId: body.roomId,
      hostName: body.hostName,
      playerCount: body.playerCount ?? 1,
      maxPlayers: body.maxPlayers ?? 16,
      modList: body.modList ?? [],
      version: body.version ?? "",
      createdAt: now,
      lastHeartbeat: now,
      unlisted: body.unlisted ?? false,
    };

    this.rooms.set(room.roomId, room);
    return new Response(JSON.stringify({ ok: true }), { status: 200 });
  }

  private async handleHeartbeat(request: Request): Promise<Response> {
    const body = await request.json() as { roomId: string; playerCount?: number };
    if (!body.roomId) {
      return new Response(JSON.stringify({ error: "roomId required" }), { status: 400 });
    }

    const room = this.rooms.get(body.roomId);
    if (!room) {
      return new Response(JSON.stringify({ error: "room not found" }), { status: 404 });
    }

    room.lastHeartbeat = Date.now();
    if (body.playerCount !== undefined) {
      room.playerCount = body.playerCount;
    }
    return new Response(JSON.stringify({ ok: true }), { status: 200 });
  }

  private async handleUnregister(request: Request): Promise<Response> {
    const body = await request.json() as { roomId: string };
    if (!body.roomId) {
      return new Response(JSON.stringify({ error: "roomId required" }), { status: 400 });
    }

    this.rooms.delete(body.roomId);
    return new Response(JSON.stringify({ ok: true }), { status: 200 });
  }

  private handleList(): Response {
    const now = Date.now();

    // Evict stale rooms
    for (const [id, room] of this.rooms) {
      if (now - room.lastHeartbeat > ROOM_TTL_MS) {
        this.rooms.delete(id);
      }
    }

    // Return only listed rooms
    const listed: RoomInfo[] = [];
    for (const room of this.rooms.values()) {
      if (!room.unlisted) {
        listed.push(room);
      }
    }

    return new Response(JSON.stringify(listed), {
      status: 200,
      headers: { "Content-Type": "application/json" },
    });
  }
}
