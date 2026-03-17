// SM64CoopDX Service Worker — enables PWA install and offline caching
const CACHE_NAME = 'sm64coopdx-v1';
const PRECACHE = [
  './',
  './sm64coopdx.html',
  './sm64coopdx.js',
  './sm64coopdx.wasm',
  './icons/icon-192.png',
  './icons/icon-512.png',
];

self.addEventListener('install', (e) => {
  e.waitUntil(
    caches.open(CACHE_NAME).then((cache) => cache.addAll(PRECACHE))
  );
  self.skipWaiting();
});

self.addEventListener('activate', (e) => {
  e.waitUntil(
    caches.keys().then((keys) =>
      Promise.all(keys.filter((k) => k !== CACHE_NAME).map((k) => caches.delete(k)))
    )
  );
  self.clients.claim();
});

self.addEventListener('fetch', (e) => {
  // Network-first for API calls
  if (e.request.url.includes('/api/')) return;

  e.respondWith(
    fetch(e.request).then((resp) => {
      // Cache successful responses
      if (resp.ok) {
        const clone = resp.clone();
        caches.open(CACHE_NAME).then((cache) => cache.put(e.request, clone));
      }
      return resp;
    }).catch(() => caches.match(e.request))
  );
});
