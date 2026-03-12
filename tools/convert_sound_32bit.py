#!/usr/bin/env python3
"""
Convert 64-bit pointer layout sound binaries to 32-bit.

The sound_data.ctl, sound_data.tbl, sequences.bin, and bank_sets files
contain ALSeqFile headers where ALSeqData entries use pointer-sized offset
fields. On 64-bit hosts these are 8 bytes with 4 bytes padding per entry.
On 32-bit targets (WASM) they need to be 4 bytes with no padding.

ALSeqFile layout (non-SH, non-EU):
  s16 revision      (2 bytes)
  s16 seqCount      (2 bytes)
  -- 64-bit: 4 bytes padding here --
  ALSeqData[seqCount]:
    64-bit: { u64 offset (8), s32 len (4), pad (4) } = 16 bytes
    32-bit: { u32 offset (4), s32 len (4) }           =  8 bytes
  Then: raw bank/sequence data (byte-addressed, no pointer fields in header portion)

This script converts the ALSeqFile header from 64-bit to 32-bit layout,
adjusting the offset values to account for the shorter header, then
copies the remaining raw data verbatim.
"""
import struct
import sys


def convert_seqfile_64_to_32(data):
    if len(data) < 4:
        return data

    # Header: s16 revision, s16 seqCount (same on both)
    revision, seq_count = struct.unpack_from('<hh', data, 0)

    # 64-bit layout sizes
    header_64 = 8  # 4 bytes header + 4 bytes alignment padding
    entry_64 = 16  # 8 bytes ptr + 4 bytes len + 4 bytes padding
    entries_end_64 = header_64 + seq_count * entry_64

    # 32-bit layout sizes
    header_32 = 4  # 4 bytes header, no padding
    entry_32 = 8   # 4 bytes ptr + 4 bytes len
    entries_end_32 = header_32 + seq_count * entry_32

    # The difference in header size shifts all data offsets
    shift = entries_end_64 - entries_end_32

    # Write 32-bit header
    out = struct.pack('<hh', revision, seq_count)

    # Convert each ALSeqData entry
    for i in range(seq_count):
        pos = header_64 + i * entry_64
        if pos + entry_64 > len(data):
            # Pad missing entries
            out += struct.pack('<Ii', 0, 0)
            continue

        offset_val = struct.unpack_from('<Q', data, pos)[0]  # u64 offset
        len_val = struct.unpack_from('<i', data, pos + 8)[0]  # s32 len

        # Adjust offset to account for shorter header
        if offset_val > 0:
            adjusted_offset = offset_val - shift
        else:
            adjusted_offset = 0

        out += struct.pack('<Ii', adjusted_offset & 0xFFFFFFFF, len_val)

    # Append remaining data after entries (raw bank/sequence data)
    if entries_end_64 < len(data):
        out += data[entries_end_64:]

    return out


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input> <output>", file=sys.stderr)
        print("Convert 64-bit sound data layout to 32-bit for WASM targets.", file=sys.stderr)
        sys.exit(1)

    with open(sys.argv[1], 'rb') as f:
        data = f.read()

    converted = convert_seqfile_64_to_32(data)

    with open(sys.argv[2], 'wb') as f:
        f.write(converted)

    rev, count = struct.unpack_from('<hh', data, 0)
    print(f"Converted: {len(data)} -> {len(converted)} bytes "
          f"(revision={rev}, seqCount={count}, "
          f"header shrunk by {(8 + count*16) - (4 + count*8)} bytes)")


if __name__ == '__main__':
    main()
