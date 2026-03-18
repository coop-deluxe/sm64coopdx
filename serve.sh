#!/bin/bash
# Start both the HTTP server and WebSocket proxy for testing
# Usage: ./serve.sh
# Stop: kill the process or Ctrl+C

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Kill any existing instances
pkill -f "python3 -m http.server 8083" 2>/dev/null || true
pkill -f "node.*proxy.js" 2>/dev/null || true
sleep 1

echo "Starting SM64CoopDX Web servers..."

# Start proxy
cd "$SCRIPT_DIR/src/pc/web/proxy"
node proxy.js &
PROXY_PID=$!

# Start HTTP server
cd "$SCRIPT_DIR/build/us_pc"
python3 -m http.server 8083 &
HTTP_PID=$!

echo ""
echo "  Game:  http://localhost:8083/sm64coopdx.html"
echo "  Proxy: ws://localhost:8765"
echo ""
echo "  PIDs: HTTP=$HTTP_PID Proxy=$PROXY_PID"
echo "  Press Ctrl+C to stop"

trap "kill $HTTP_PID $PROXY_PID 2>/dev/null; exit" INT TERM
wait
