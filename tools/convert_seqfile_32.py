"""
Convert an ALSeqFile binary from 64-bit LE to 32-bit LE pointer layout.

Only the header/entry-table needs conversion; per-entry data blobs are opaque.
Used for sequences.bin (and TBL if not regenerated via assemble_sound.py).

64-bit layout:
  Header: pack("HHX", magic, count) = HH(4) + xxxx(4) = 8 bytes
  Per entry: pack("P", offset) = Q(8), pack("IX", len) = I(4) + xxxx(4)
  So each entry = 16 bytes.
  Data starts at align16(8 + count * 16).

32-bit layout:
  Header: pack("HH", magic, count) = 4 bytes
  Per entry: pack("P", offset) = I(4), pack("I", len) = I(4)
  So each entry = 8 bytes.
  Data starts at align16(4 + count * 8).

Usage:
  python3 convert_seqfile_32.py <input> <output>
"""

import struct
import sys
import zlib


def align16(x):
    return (x + 15) & ~15


def convert(data):
    magic = struct.unpack_from('<H', data, 0)[0]
    count = struct.unpack_from('<H', data, 2)[0]

    # Parse 64-bit entries
    header_64 = 8  # HH + X
    entries = []
    for i in range(count):
        off = header_64 + i * 16
        ptr = struct.unpack_from('<Q', data, off)[0]
        length = struct.unpack_from('<I', data, off + 8)[0]
        entries.append((ptr, length))

    data_start_64 = align16(header_64 + count * 16)

    # Build 32-bit output
    header_32 = 4  # HH, no X
    data_start_32 = align16(header_32 + count * 8)

    out = bytearray()
    out += struct.pack('<HH', magic, count)

    for old_offset, length in entries:
        # Adjust offset: old_offset is relative to file start.
        # new_offset = data_start_32 + (old_offset - data_start_64)
        new_offset = data_start_32 + (old_offset - data_start_64)
        out += struct.pack('<I', new_offset)
        out += struct.pack('<I', length)

    # Pad header to alignment
    while len(out) < data_start_32:
        out += b'\x00'

    # Copy data section verbatim
    data_section = data[data_start_64:]
    out += data_section

    return bytes(out)


def main():
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)

    with open(sys.argv[1], 'rb') as f:
        raw = f.read()

    # Detect if compressed (zlib)
    compressed = raw[:2] == b'\x78\x9c' or raw[:2] == b'\x78\x01'
    if compressed:
        data = zlib.decompress(raw)
    else:
        data = raw

    result = convert(data)

    if compressed:
        result = zlib.compress(result)

    with open(sys.argv[2], 'wb') as f:
        f.write(result)

    print(f"Converted {sys.argv[1]} -> {sys.argv[2]}")


if __name__ == '__main__':
    main()
