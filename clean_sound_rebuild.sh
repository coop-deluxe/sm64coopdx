#!/bin/bash
# Clean stale 64-bit sound data and rebuild with 32-bit layout for web
set -e
cd "$(dirname "$0")"

echo "Removing stale sound intermediates..."
rm -f build/us_pc/sound/sound_data.ctl*
rm -f build/us_pc/sound/sound_data.tbl*
rm -f build/us_pc/sound/sequences.bin*
rm -f build/us_pc/sound/sound_data.o

echo "Rebuilding..."
./build_web.sh
