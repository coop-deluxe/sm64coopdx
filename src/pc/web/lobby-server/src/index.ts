import { RoomRegistry } from "./room-registry";

export { RoomRegistry };

interface Env {
  ROOM_REGISTRY: DurableObjectNamespace;
}

function corsHeaders(request: Request): Record<string, string> {
  // Allow any origin — this is a public game lobby
  const origin = request.headers.get("Origin") ?? "*";
  return {
    "Access-Control-Allow-Origin": origin,
    "Access-Control-Allow-Methods": "GET, POST, OPTIONS",
    "Access-Control-Allow-Headers": "Content-Type",
  };
}

function lobbyDashboardHTML(rooms: Array<Record<string, unknown>>): string {
  const now = Date.now();
  let rows = "";
  if (rooms.length === 0) {
    rows = `<tr><td colspan="6" style="text-align:center;color:#888;padding:2rem">No active rooms</td></tr>`;
  } else {
    for (const r of rooms) {
      const age = Math.round((now - (r.createdAt as number)) / 1000);
      const heartbeat = Math.round((now - (r.lastHeartbeat as number)) / 1000);
      const mods = (r.modList as string[]) || [];
      const modStr = mods.length > 0 ? mods.join(", ") : "<em>none</em>";
      rows += `<tr>
        <td><strong>${esc(r.roomId as string)}</strong></td>
        <td>${esc(r.hostName as string)}</td>
        <td>${r.playerCount}/${r.maxPlayers}</td>
        <td>${esc(r.version as string)}</td>
        <td style="font-size:0.85em">${modStr}</td>
        <td style="color:#888">${age}s ago / ${heartbeat}s</td>
      </tr>`;
    }
  }

  return `<!DOCTYPE html>
<html><head>
<meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>SM64CoopDX Lobby</title>
<style>
  body { font-family: -apple-system, system-ui, sans-serif; background: #0a0e1a; color: #e0e0e0; margin: 0; padding: 2rem; }
  h1 { color: #4fc3f7; margin-bottom: 0.25rem; }
  p.sub { color: #888; margin-top: 0; }
  table { width: 100%; border-collapse: collapse; margin-top: 1rem; }
  th { text-align: left; padding: 0.5rem; border-bottom: 2px solid #1a237e; color: #90caf9; font-size: 0.9em; }
  td { padding: 0.5rem; border-bottom: 1px solid #1a1a2e; }
  tr:hover { background: #16213e; }
  .refresh { color: #4fc3f7; cursor: pointer; text-decoration: underline; }
  em { color: #666; }
</style>
</head><body>
<h1>SM64CoopDX Web Lobby</h1>
<p class="sub">${rooms.length} active room${rooms.length !== 1 ? "s" : ""} &mdash; <span class="refresh" onclick="location.reload()">refresh</span></p>
<table>
  <tr><th>Room</th><th>Host</th><th>Players</th><th>Version</th><th>Mods</th><th>Age / Heartbeat</th></tr>
  ${rows}
</table>
<script>setTimeout(function(){location.reload()},10000);</script>
</body></html>`;
}

function esc(s: string): string {
  return s.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;").replace(/"/g, "&quot;");
}

export default {
  async fetch(request: Request, env: Env): Promise<Response> {
    // CORS preflight
    if (request.method === "OPTIONS") {
      return new Response(null, { status: 204, headers: corsHeaders(request) });
    }

    const url = new URL(request.url);

    // Root: serve a live lobby dashboard
    if (url.pathname === "/" || url.pathname === "") {
      const id = env.ROOM_REGISTRY.idFromName("global");
      const stub = env.ROOM_REGISTRY.get(id);
      const roomsResp = await stub.fetch(new Request(url.origin + "/rooms"));
      const rooms = await roomsResp.json() as Array<Record<string, unknown>>;
      return new Response(lobbyDashboardHTML(rooms), {
        headers: { "Content-Type": "text/html; charset=utf-8" },
      });
    }

    if (!url.pathname.startsWith("/api/")) {
      return new Response("Not Found", { status: 404 });
    }

    // Route to the single DO instance
    const id = env.ROOM_REGISTRY.idFromName("global");
    const stub = env.ROOM_REGISTRY.get(id);

    // Strip /api prefix for the DO
    const doUrl = new URL(request.url);
    doUrl.pathname = doUrl.pathname.replace(/^\/api/, "");
    const doRequest = new Request(doUrl.toString(), request);

    const response = await stub.fetch(doRequest);

    // Attach CORS headers
    const headers = new Headers(response.headers);
    for (const [k, v] of Object.entries(corsHeaders(request))) {
      headers.set(k, v);
    }

    return new Response(response.body, {
      status: response.status,
      headers,
    });
  },
};
