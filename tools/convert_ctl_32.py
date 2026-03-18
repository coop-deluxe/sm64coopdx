"""
Convert a CTL (audio bank control) binary from 64-bit LE to 32-bit LE layout.

The CTL file is an ALSeqFile header followed by bank data blobs. Unlike SEQ/TBL
where the data blobs are opaque, CTL bank blobs contain internal pointers (P)
and padding (X) that must be rewritten when converting from 64-bit to 32-bit.

64-bit LE layout: P = Q (8 bytes), X = xxxx (4 bytes padding)
32-bit LE layout: P = I (4 bytes), X = removed (0 bytes)

All internal pointer values within each bank blob must be remapped because
positions shift when P shrinks from 8->4 and X padding is removed.

Usage:
  python3 convert_ctl_32.py <input_compressed_ctl> <output_compressed_ctl>
"""

import struct
import sys
import zlib


def align16(x):
    return (x + 15) & ~15


class SegmentRecorder:
    """
    Records segments from a 64-bit bank body walk, then replays them
    as 32-bit output with pointer remapping.

    Segment types:
      ('P_internal', off64, value)  - internal pointer (body offset), remap value
      ('P_external', off64, value)  - external pointer (e.g. TBL offset), keep value
      ('X', off64, None)            - 4-byte padding, removed in 32-bit
      ('data', off64, raw_bytes)    - plain data, copied verbatim
      ('align16', off64, pad_bytes) - alignment padding, recalculated for 32-bit
    """

    def __init__(self, body64):
        self.body = body64
        self.pos = 0
        self.segments = []

    def cur(self):
        return self.pos

    def P_internal(self):
        """Read an 8-byte pointer whose value is an internal body offset."""
        off = self.pos
        val = struct.unpack_from('<Q', self.body, self.pos)[0]
        self.segments.append(('P_internal', off, val))
        self.pos += 8
        return val

    def P_external(self):
        """Read an 8-byte pointer whose value is external (not remapped)."""
        off = self.pos
        val = struct.unpack_from('<Q', self.body, self.pos)[0]
        self.segments.append(('P_external', off, val))
        self.pos += 8
        return val

    def X(self):
        """Skip 4-byte padding (removed in 32-bit)."""
        off = self.pos
        self.segments.append(('X', off, None))
        self.pos += 4

    def data(self, fmt_or_nbytes):
        """Read raw data (copied verbatim to 32-bit output)."""
        if isinstance(fmt_or_nbytes, int):
            n = fmt_or_nbytes
        else:
            n = struct.calcsize('<' + fmt_or_nbytes)
        off = self.pos
        raw = self.body[self.pos:self.pos + n]
        self.segments.append(('data', off, raw))
        self.pos += n
        return raw

    def data_vals(self, fmt, endian='<'):
        """Read raw data and also return unpacked values."""
        n = struct.calcsize(endian + fmt)
        off = self.pos
        raw = self.body[self.pos:self.pos + n]
        vals = struct.unpack_from(endian + fmt, self.body, self.pos)
        self.segments.append(('data', off, raw))
        self.pos += n
        return vals

    def align(self, boundary):
        old = self.pos
        new = (old + boundary - 1) & ~(boundary - 1)
        if new > old:
            self.segments.append(('align16', old, new - old))
            self.pos = new

    def build_32bit(self):
        """
        Build the 32-bit body from recorded segments.

        Returns (output_bytes, offset_map) where offset_map maps
        64-bit body offsets to 32-bit body offsets.
        """
        # Pass 1: compute offset map
        offset_map = {}
        out_pos = 0
        for seg in self.segments:
            kind, off64, value = seg
            offset_map[off64] = out_pos
            if kind in ('P_internal', 'P_external'):
                out_pos += 4
            elif kind == 'X':
                pass  # removed
            elif kind == 'data':
                out_pos += len(value)
            elif kind == 'align16':
                out_pos = align16(out_pos)

        # Map end position too
        offset_map[len(self.body)] = out_pos

        # Pass 2: emit 32-bit data
        out = bytearray()
        for seg in self.segments:
            kind, off64, value = seg
            if kind == 'P_internal':
                if value == 0:
                    out += struct.pack('<I', 0)
                else:
                    if value not in offset_map:
                        raise ValueError(
                            f"Internal pointer value {value} (at 64-bit offset {off64}) "
                            f"not found in offset map"
                        )
                    out += struct.pack('<I', offset_map[value])
            elif kind == 'P_external':
                # External pointers keep their value (truncated to 32-bit)
                out += struct.pack('<I', value & 0xFFFFFFFF)
            elif kind == 'X':
                pass
            elif kind == 'data':
                out += value
            elif kind == 'align16':
                while len(out) % 16 != 0:
                    out += b'\x00'

        return bytes(out), offset_map


def convert_bank(data64):
    """
    Parse a 64-bit LE bank blob and convert it to 32-bit LE layout.

    Bank blob layout:
      [16-byte header: IIII (numInstruments, numDrums, shared, date)]
      [body: structured data with P/X fields]

    Body layout (in byte order):
      1. drum_ptr: P (internal, points to drum position table) or 8 zero bytes
      2. inst_ptrs: P * numInstruments (internal, each points to an instrument)
      3. align16
      4. samples: per unique sample, each containing:
         - AudioBankSample: I + X + P(external,tbl) + P(internal,loop) + P(internal,book) + I + align16
         - Book: ii + h*n + align16
         - Loop: IIiI [+ h*16] + align16
      5. envelopes: per envelope, big-endian HH pairs terminated by H >= 0xFFF0, align16
      6. instruments: per instrument, BBBB + X + P(internal,env) + 3*(P(internal,sample) + f + X)
      7. align16
      8. drums: per drum, BBBB + X + P(internal,sample) + f + X + P(internal,env)
      9. align16
      10. drum position table: P(internal) * numDrums
      11. align16
    """
    HEADER_SIZE = 16
    num_instruments, num_drums, shared, date = struct.unpack_from('<IIII', data64, 0)
    header_bytes = data64[:HEADER_SIZE]
    body64 = data64[HEADER_SIZE:]

    rec = SegmentRecorder(body64)

    # --- 1. drum_ptr or zeros ---
    # Always a pointer-sized field (P), even when zero (no drums)
    drum_ptr_val = rec.P_internal()

    # --- 2. inst_ptrs ---
    inst_ptr_vals = []
    for _ in range(num_instruments):
        val = rec.P_internal()
        inst_ptr_vals.append(val)

    # --- 3. align16 ---
    rec.align(16)

    # Determine section boundaries from pointer values
    non_zero_inst_ptrs = sorted(set(v for v in inst_ptr_vals if v != 0))
    first_inst_off = non_zero_inst_ptrs[0] if non_zero_inst_ptrs else None

    # --- 4. Samples ---
    # Detect samples by checking if the loop_addr and book_addr pointers
    # point forward within the body and before the instrument section.
    while rec.cur() < len(body64):
        if first_inst_off is not None and rec.cur() >= first_inst_off:
            break

        # Peek: after I(4)+X(4)+P(8) = 16 bytes, the loop_addr P is at +16
        # and book_addr P is at +24. Both should be forward-pointing body offsets.
        cur = rec.cur()
        if cur + 36 > len(body64):
            break

        # loop_addr is at cur+16, book_addr at cur+24 (both are Q/8-byte)
        loop_addr_peek = struct.unpack_from('<Q', body64, cur + 16)[0]
        book_addr_peek = struct.unpack_from('<Q', body64, cur + 24)[0]

        # Both should point forward into the body, after the sample struct
        is_sample = (book_addr_peek > cur and book_addr_peek < len(body64) and
                     loop_addr_peek > cur and loop_addr_peek < len(body64))

        if not is_sample:
            break

        # AudioBankSample struct
        rec.data('I')          # sample_len or 0
        rec.X()                # padding
        rec.P_external()       # tbl_offset (external pointer into TBL bank)
        loop_addr = rec.P_internal()  # loop addr (internal)
        book_addr = rec.P_internal()  # book addr (internal)
        rec.data('I')          # sample_len (non-shindou)
        rec.align(16)

        # Book (should be at book_addr)
        assert rec.cur() == book_addr, \
            f"Book addr mismatch: expected {book_addr}, at {rec.cur()}"
        order, npredictors = rec.data_vals('ii')
        book_count = order * npredictors * 8
        for _ in range(book_count):
            rec.data('h')
        rec.align(16)

        # Loop (should be at loop_addr)
        assert rec.cur() == loop_addr, \
            f"Loop addr mismatch: expected {loop_addr}, at {rec.cur()}"
        _, _, loop_count, _ = rec.data_vals('IIiI')
        if loop_count != 0:
            for _ in range(16):
                rec.data('h')
        rec.align(16)

    # --- 5. Envelopes ---
    # Big-endian HH pairs. Terminated when first H >= 0xFFF0.
    while rec.cur() < len(body64):
        if first_inst_off is not None and rec.cur() >= first_inst_off:
            break

        # Parse one envelope: sequence of big-endian HH until terminator
        while rec.cur() + 4 <= len(body64):
            vals = rec.data_vals('HH', '>')
            if vals[0] >= 0xFFF0:
                break
        rec.align(16)

    # --- 6. Instruments ---
    # Each: BBBB + X + P(env) + 3*(P(sample) + f + X)
    for inst_off in sorted(set(v for v in inst_ptr_vals if v != 0)):
        assert rec.cur() == inst_off, \
            f"Instrument offset mismatch: expected {inst_off}, at {rec.cur()}"
        rec.data('BBBB')
        rec.X()
        rec.P_internal()   # envelope addr
        for _ in range(3):  # sound_lo, sound, sound_hi
            rec.P_internal()  # sample addr
            rec.data('f')     # tuning
            rec.X()           # padding

    # --- 7. align16 after instruments ---
    rec.align(16)

    # --- 8-11. Drums section ---
    if num_drums > 0:
        # Each drum: BBBB + X + P(sample) + f + X + P(env)
        for _ in range(num_drums):
            rec.data('BBBB')
            rec.X()
            rec.P_internal()   # sample addr (sound)
            rec.data('f')      # tuning (sound)
            rec.X()            # padding (sound)
            rec.P_internal()   # envelope addr

        rec.align(16)

        # Drum position table (drum_ptr points here)
        assert rec.cur() == drum_ptr_val, \
            f"Drum ptr mismatch: expected {drum_ptr_val}, at {rec.cur()}"

        for _ in range(num_drums):
            rec.P_internal()   # pointer to each drum struct

        rec.align(16)

    # Verify we consumed the entire body
    assert rec.cur() == len(body64), \
        f"Did not consume entire body: at {rec.cur()}, len={len(body64)}"

    # Build 32-bit output
    body32, offset_map = rec.build_32bit()
    return header_bytes + body32


def convert(data):
    """Convert a full CTL file (ALSeqFile header + bank blobs) from 64-bit to 32-bit."""
    # Parse ALSeqFile header (64-bit layout)
    # Header: pack("HHX", magic, count) = HH(4) + xxxx(4) = 8 bytes
    magic = struct.unpack_from('<H', data, 0)[0]
    count = struct.unpack_from('<H', data, 2)[0]

    # Per entry: pack("P", offset) = Q(8), pack("IX", len) = I(4) + xxxx(4) = 16 bytes
    header_64 = 8
    entries = []
    for i in range(count):
        off = header_64 + i * 16
        ptr = struct.unpack_from('<Q', data, off)[0]
        length = struct.unpack_from('<I', data, off + 8)[0]
        entries.append((ptr, length))

    # Extract and convert each bank blob
    converted_banks = []
    for i, (old_offset, length) in enumerate(entries):
        bank_data = data[old_offset:old_offset + length]
        num_inst = struct.unpack_from('<I', bank_data, 0)[0]
        num_drums = struct.unpack_from('<I', bank_data, 4)[0]
        print(f"  Bank {i}: numInstruments={num_inst}, numDrums={num_drums}, "
              f"size_64={length}")
        converted = convert_bank(bank_data)
        print(f"    -> size_32={len(converted)}")
        converted_banks.append(converted)

    # Build 32-bit ALSeqFile
    # Header: pack("HH", magic, count) = 4 bytes
    # Per entry: pack("P", offset)=I(4), pack("I", len)=I(4) = 8 bytes each
    header_32 = 4
    data_start_32 = align16(header_32 + count * 8)

    out = bytearray()
    out += struct.pack('<HH', magic, count)

    # Compute new offsets for each bank
    bank_offset = data_start_32
    new_entries = []
    for bank_data in converted_banks:
        new_entries.append((bank_offset, len(bank_data)))
        bank_offset += len(bank_data)

    for new_offset, new_length in new_entries:
        out += struct.pack('<I', new_offset)
        out += struct.pack('<I', new_length)

    # Pad header to alignment
    while len(out) < data_start_32:
        out += b'\x00'

    # Append converted bank data
    for bank_data in converted_banks:
        out += bank_data

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

    print(f"Input: {len(raw)} bytes compressed, {len(data)} bytes decompressed")
    result = convert(data)
    print(f"Output: {len(result)} bytes")

    if compressed:
        result = zlib.compress(result)
        print(f"Output compressed: {len(result)} bytes")

    with open(sys.argv[2], 'wb') as f:
        f.write(result)

    print(f"Converted {sys.argv[1]} -> {sys.argv[2]}")


if __name__ == '__main__':
    main()
