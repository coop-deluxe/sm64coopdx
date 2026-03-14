import { RoomRegistry } from "./room-registry";

export { RoomRegistry };

interface Env {
  ROOM_REGISTRY: DurableObjectNamespace;
}

const ALLOWED_ORIGINS = [
  "https://zalo.github.io",
  "http://localhost:8083",
];

function corsHeaders(request: Request): Record<string, string> {
  const origin = request.headers.get("Origin") ?? "";
  const allowed = ALLOWED_ORIGINS.includes(origin) ? origin : "";
  return {
    "Access-Control-Allow-Origin": allowed,
    "Access-Control-Allow-Methods": "GET, POST, OPTIONS",
    "Access-Control-Allow-Headers": "Content-Type",
  };
}

export default {
  async fetch(request: Request, env: Env): Promise<Response> {
    // CORS preflight
    if (request.method === "OPTIONS") {
      return new Response(null, { status: 204, headers: corsHeaders(request) });
    }

    const url = new URL(request.url);
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
