#!/usr/bin/env python3
"""
patch_selector.py

Detect ROM region using config/rom_profiles.json and apply the corresponding patch file.

Supports:
 - .bps patches (Flips CLI if on PATH)
 - .xdelta patches (xdelta3 if on PATH)

Usage:
  python3 tools/patch_selector.py path/to/rom.z64 --out patched.z64
"""
import argparse
import json
import shutil
import subprocess
from pathlib import Path
import sys

# Use the functions directly here to avoid import oddities across tools/ scripts
from hashlib import md5 as _md5, sha1 as _sha1
import binascii as _binascii

def compute_hashes(path):
    md5h = _md5()
    sha1h = _sha1()
    crc = 0
    size = 0
    with open(path, "rb") as f:
        while True:
            chunk = f.read(65536)
            if not chunk:
                break
            md5h.update(chunk)
            sha1h.update(chunk)
            crc = _binascii.crc32(chunk, crc)
            size += len(chunk)
    return {
        "size": size,
        "crc32": format(crc & 0xFFFFFFFF, "08X"),
        "md5": md5h.hexdigest().upper(),
        "sha1": sha1h.hexdigest().upper()
    }

def load_profiles(p):
    if not Path(p).exists():
        return {"profiles": []}
    with open(p, "r", encoding="utf-8") as f:
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

def find_matching_profile(rom_path, profiles_path):
    hashes = compute_hashes(rom_path)
    profiles = load_profiles(Path(profiles_path))
    matches = match_profile(hashes, profiles)
    if matches:
        matches.sort(key=lambda m: (0 if any(k in ["crc32","md5","sha1"] for k in m["reasons"]) else 1))
        return matches[0]["profile"], hashes
    return None, hashes

def apply_bps(patch_path, original_path, out_path):
    flips = shutil.which("flips") or shutil.which("flips.exe")
    if flips:
        cmd = [flips, "-a", str(patch_path), str(original_path), str(out_path)]
        print("Running:", " ".join(cmd))
        subprocess.check_call(cmd)
        return True
    else:
        print("Flips not found on PATH; cannot apply .bps. Please use Flips GUI or install flips CLI.")
        return False

def apply_xdelta(patch_path, original_path, out_path):
    xdelta = shutil.which("xdelta3")
    if xdelta:
        cmd = [xdelta, "-d", "-s", str(original_path), str(patch_path), str(out_path)]
        print("Running:", " ".join(cmd))
        subprocess.check_call(cmd)
        return True
    else:
        print("xdelta3 not found on PATH; cannot apply .xdelta patches.")
        return False

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("rom", help="Path to user ROM")
    ap.add_argument("--profiles", help="Path to rom_profiles.json", default="config/rom_profiles.json")
    ap.add_argument("--out", help="Output patched ROM path", default=None)
    args = ap.parse_args()

    rom_path = Path(args.rom)
    if not rom_path.exists():
        print("ROM not found:", rom_path)
        sys.exit(2)

    profile, hashes = find_matching_profile(rom_path, args.profiles)
    if not profile:
        print("No matching profile found for this ROM.")
        print("Detected hashes:")
        print(json.dumps(hashes, indent=2))
        sys.exit(3)

    region = profile.get("region", "unknown")
    print(f"Detected profile: {profile.get('name')} (region: {region})")
    patch_filename = profile.get("patch_filename")
    if not patch_filename:
        for ext in ("bps","xdelta"):
            candidate = Path(f"patches/msusacoop_{region}.{ext}")
            if candidate.exists():
                patch_filename = str(candidate)
                break

    if not patch_filename:
        print("No patch filename configured and no fallback patch found for region:", region)
        sys.exit(4)

    patch_path = Path(patch_filename)
    if not patch_path.exists():
        print("Expected patch file not found:", patch_path)
        sys.exit(5)

    out_path = Path(args.out) if args.out else rom_path.with_name(rom_path.stem + "_patched" + rom_path.suffix)
    print("Applying patch:", patch_path, "->", out_path)

    if patch_path.suffix.lower() == ".bps":
        ok = apply_bps(patch_path, rom_path, out_path)
        if not ok:
            sys.exit(6)
    elif patch_path.suffix.lower() in (".xdelta", ".xd3"):
        ok = apply_xdelta(patch_path, rom_path, out_path)
        if not ok:
            sys.exit(6)
    else:
        print("Unsupported patch format:", patch_path.suffix)
        sys.exit(7)

    print("Patched ROM saved to:", out_path)
    print("Re-run tools/rom_detector.py on the patched ROM to verify if desired.")

if __name__ == "__main__":
    main()