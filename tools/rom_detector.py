#!/usr/bin/env python3
"""
rom_detector.py

Compute size, CRC32, MD5, SHA1 for a ROM file and try to match entries from config/rom_profiles.json.

Usage: python3 tools/rom_detector.py path/to/rom.z64
"""
import argparse
import hashlib
import binascii
import json
import sys
from pathlib import Path

def compute_hashes(path):
    md5 = hashlib.md5()
    sha1 = hashlib.sha1()
    crc = 0
    size = 0
    with open(path, "rb") as f:
        while True:
            chunk = f.read(65536)
            if not chunk:
                break
            md5.update(chunk)
            sha1.update(chunk)
            crc = binascii.crc32(chunk, crc)
            size += len(chunk)
    return {
        "size": size,
        "crc32": format(crc & 0xFFFFFFFF, "08X"),
        "md5": md5.hexdigest().upper(),
        "sha1": sha1.hexdigest().upper()
    }

def load_profiles(profiles_path):
    if not profiles_path.exists():
        return {"profiles": []}
    with open(profiles_path, "r", encoding="utf-8") as f:
        return json.load(f)

def match_profile(hashes, profiles):
    matches = []
    for p in profiles.get("profiles", []):
        p_size = p.get("size", 0)
        p_hashes = p.get("hashes", {})
        matched = False
        reasons = []
        if p_size and p_size == hashes["size"]:
            matched = True
            reasons.append("size")
        for k in ("crc32", "md5", "sha1"):
            if p_hashes.get(k) and p_hashes.get(k).upper() == hashes[k].upper():
                matched = True
                reasons.append(k)
        if matched:
            matches.append({"profile": p, "reasons": reasons})
    return matches

def dump_header(path, length=64):
    with open(path, "rb") as f:
        header = f.read(length)
    hexpart = " ".join(f"{b:02X}" for b in header)
    asciipart = "".join((chr(b) if 32 <= b < 127 else ".") for b in header)
    return hexpart, asciipart

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("rom", help="Path to ROM file (z64, n64, etc.)")
    ap.add_argument("--profiles", help="Path to rom_profiles.json", default="config/rom_profiles.json")
    args = ap.parse_args()

    rom_path = Path(args.rom)
    if not rom_path.exists():
        print("ROM not found:", rom_path)
        sys.exit(2)

    print("Reading ROM:", rom_path)
    hashes = compute_hashes(rom_path)
    print("Size:   {:,} bytes".format(hashes["size"]))
    print("CRC32:  ", hashes["crc32"])
    print("MD5:    ", hashes["md5"])
    print("SHA1:   ", hashes["sha1"])

    hexhdr, asciihdr = dump_header(rom_path)
    print("\nFirst 64 bytes (hex):")
    print(hexhdr)
    print("\nFirst 64 bytes (ASCII where printable):")
    print(asciihdr)

    profiles = load_profiles(Path(args.profiles))
    matches = match_profile(hashes, profiles)
    if matches:
        print("\nMatched profiles:")
        for m in matches:
            p = m["profile"]
            print("- {} (region: {}) matched by: {}".format(p.get("name","<unnamed>"), p.get("region","?"), ", ".join(m["reasons"])))
            if p.get("notes"):
                print("  notes:", p.get("notes"))
            if p.get("patch_filename"):
                print("  recommended patch filename:", p.get("patch_filename"))
    else:
        print("\nNo profile matched. If you own the clean ROMs, add their size and at least one hash to config/rom_profiles.json.")
        print("You can paste the following values into rom_profiles.json:")
        print(json.dumps({
            "size": hashes["size"],
            "crc32": hashes["crc32"],
            "md5": hashes["md5"],
            "sha1": hashes["sha1"]
        }, indent=2))

if __name__ == "__main__":
    main()