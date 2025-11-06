# tools/

Helper scripts for msusacoop development.

Files:
- codegen.py  - generate generated/rom_offsets.c and .h from config/address_map.json
- rom_detector.py - fingerprint ROM files (size, CRC32, MD5, SHA1)
- patch_selector.py - detect ROM region and apply matching patch from patches/

Quick usage (from repo root):
- Generate rom_offsets for US:
    python3 tools/codegen.py --map config/address_map.json --region US --out-dir generated

- Fingerprint a ROM:
    python3 tools/rom_detector.py path/to/msusa_US.z64

- Apply a patch:
    python3 tools/patch_selector.py path/to/rom.z64 --out patched.z64

Notes:
- Do NOT commit ROM images.
- Keep patches/ small patch files (bps/xdelta) — those are safe to commit.
- If you cannot type backspace/arrow keys easily, use the GitHub web UI to create files: Add file → Create new file and paste the contents from the corresponding blocks.