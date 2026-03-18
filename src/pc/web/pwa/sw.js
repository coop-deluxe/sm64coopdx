// SM64CoopDX Service Worker — enables PWA install only.
// Minimal fetch handler: never intercept network requests.
// This avoids breaking PeerJS signaling, lobby API, WebSocket connections,
// or any dynamic content. The SW exists purely to satisfy PWA install criteria.

self.addEventListener('install', () => self.skipWaiting());
self.addEventListener('activate', (e) => e.waitUntil(self.clients.claim()));

// Pass all fetches straight through to the network — no caching
self.addEventListener('fetch', () => {});
