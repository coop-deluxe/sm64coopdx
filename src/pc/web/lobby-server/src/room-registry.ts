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

export class RoomRegistry {
  private rooms: Map<string, RoomInfo> = new Map();

  constructor(_state: DurableObjectState, _env: unknown) {}

  async fetch(request: Request): Promise<Response> {
    const url = new URL(request.url);
    const path = url.pathname;

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
