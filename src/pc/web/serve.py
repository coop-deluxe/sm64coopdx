#!/usr/bin/env python3
"""HTTP server with no-cache headers for development."""
import http.server
import sys

class NoCacheHandler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header('Cache-Control', 'no-cache, no-store, must-revalidate')
        self.send_header('Pragma', 'no-cache')
        self.send_header('Expires', '0')
        # Required for SharedArrayBuffer (pthreads) if ever needed
        self.send_header('Cross-Origin-Opener-Policy', 'same-origin')
        self.send_header('Cross-Origin-Embedder-Policy', 'require-corp')
        super().end_headers()

port = int(sys.argv[1]) if len(sys.argv) > 1 else 8083
print(f"Serving on http://0.0.0.0:{port} (no-cache)")
http.server.HTTPServer(('', port), NoCacheHandler).serve_forever()
