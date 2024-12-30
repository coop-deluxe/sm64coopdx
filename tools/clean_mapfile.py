#!/usr/bin/env python3
# "tools/clean_mapfile.py"

import sys
import os
import re
import json

def extract_int(b: bytes, offset: int, size: int) -> int:
    return int.from_bytes(b[offset:(offset+size)], 'little')

def parse_exe_sections(exe_path: str) -> list[dict]:
    print(f'* Parsing sections from EXE: "{exe_path}"')

    with open(exe_path, 'rb') as f:
        b: bytes = f.read(4096)

    if b[0:(0+2)] != b'MZ':
        raise ValueError(f'"{exe_path}": no MZ header')

    pe_offset = extract_int(b, 0x3C, 4)
    if (pe_offset < 0x40) or (pe_offset > 4096) or (pe_offset & 7):
        raise ValueError(f'"{exe_path}": bad LfaNew address')
    if b[pe_offset:(pe_offset+4)] != b'PE\0\0':
        raise ValueError(f'"{exe_path}": not a valid PE file')

    x = extract_int(b, pe_offset + 4, 2)
    if x != 0x8664:
        raise ValueError(f'"{exe_path}": not a x86_64 executable')

    num_sections = extract_int(b, pe_offset + 6, 2)
    if (num_sections <= 0) or (num_sections > 64):
        raise ValueError(f'"{exe_path}: bad NumberOfSections')

    x = extract_int(b, pe_offset + 20, 2)
    if (x <= 0) or (x > 256):
        raise ValueError(f'"{exe_path}: bad SizeOfOptionalHeader.')

    if extract_int(b, pe_offset + 24, 2) != 0x020B:
        raise ValueError(f'"{exe_path}": invalid PE32+ signature')

    sections = []
    section_table = pe_offset + 24 + x
    for i in range(num_sections):
        x = section_table + i * 40
        # virtual_size = extract_int(b, x + 8, 4)
        virtual_addr = extract_int(b, x + 12, 4)
        # size_of_raw_data = extract_int(b, x + 16, 4)
        # ptr_to_raw_data = extract_int(b, x + 20, 4)
        flags = extract_int(b, x + 36, 4)

        discardable = bool(0x02000000 & flags)
        sections.append({ 'virtual_addr': virtual_addr, 'discardable': discardable })

    return sections

def parse_map_file(map_path: str, module_name: str, sections: list[dict]) -> dict:
    print(f'* Parsing and cleaning the MAP file: "{map_path}"')

    with open(map_path, 'rt', encoding='ascii') as f:
        map_content = f.read()

    pattern = re.compile(r'^\[ *\d+\]\(sec +(\d+)\)\(fl 0x00\)\(ty +(\d+)\)\(scl +(\d+)\) \(nx 0\) 0x([0-9a-f]+) (.+)$', re.MULTILINE)
    matches = pattern.findall(map_content)

    symbols = []
    with open(map_path, 'wt', encoding='ascii', newline='\n') as f:
        for m in matches:
            section_id = int(m[0])
            symbol_type = int(m[1])
            storage_class = int(m[2])
            relative_addr = int(m[3], 16)
            symbol_name = m[4]

            # Target section is not discardable
            if sections[section_id - 1]['discardable']: continue

            # Debug symbol, accepted type
            # - IMAGE_SYM_DTYPE_NULL     ("0")  | scalar
            # - IMAGE_SYM_DTYPE_FUNCTION ("20") | subroutine
            if symbol_type not in (0, 20): continue

            # Debug symbol, accepted class
            # - C_EXT  = 2 | external, global
            # - C_STAT = 3 | static
            if storage_class not in (2, 3): continue

            # Debug symbol, accepted name
            if symbol_name.startswith('.') and not symbol_name.startswith('.refptr.'): continue

            # Calculate Relative Virtual Address
            section_start = sections[section_id - 1]['virtual_addr']
            rva = hex(section_start + relative_addr)

            # Save back only the function labels, loaded on the crash screen
            if (section_id == 1) and (symbol_type == 20):
                f.write(f'(sec{section_id})(fl0x00)(ty{symbol_type})(scl{storage_class})(nx 0)0x{relative_addr:016x} {symbol_name}\n')

            symbols.append({ 'module': module_name, 'address': rva, 'text': symbol_name })

    return { 'labels': symbols }

def main():
    if len(sys.argv) != 3:
        print(f'Usage: "{sys.argv[0]}" <exe_path> <map_path>"')
        sys.exit(1)

    exe_path = sys.argv[1]
    map_path = sys.argv[2]

    module_name = os.path.basename(exe_path)
    sections = parse_exe_sections(exe_path)
    symbols = parse_map_file(map_path, module_name, sections)

    output_path = exe_path + '.dd64'
    print(f'* Saving symbol database for x64dbg to "{output_path}"')
    with open(output_path, 'wt', newline='\n') as f:
        json.dump(symbols, f, indent=0, separators=(',', ':'))

if __name__ == "__main__":
    main()
