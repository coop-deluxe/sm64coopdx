import os
import re
import sys

replacements = {
    'BAD_RETURN(s8)':  'void',
    'BAD_RETURN(s16)': 'void',
    'BAD_RETURN(s32)': 'void',
    'BAD_RETURN(s64)': 'void',
    'BAD_RETURN(u8)':  'void',
    'BAD_RETURN(u16)': 'void',
    'BAD_RETURN(u32)': 'void',
    'BAD_RETURN(u64)': 'void',
    'BAD_RETURN(f32)': 'void',
    'BAD_RETURN(f64)': 'void',
}

def extract_functions(filename):
    with open(filename) as file:
        raw_lines = file.readlines()

    # combine lines
    txt = ''.join(raw_lines)

    # convert multi-line stuff
    txt = txt.replace('\r', ' ')
    txt = txt.replace('\\\n', ' ')

    # deal with certain ifdefs
    gobbling = False
    tmp = txt
    txt = ''
    for line in tmp.splitlines():
        if line.strip() == '#ifdef AVOID_UB':
            gobbling = True
        if line.strip() == '#ifdef __cplusplus':
            gobbling = True
        if line.strip() == '#else':
            gobbling = False
        if line.strip() == '#endif':
            gobbling = False
        if not gobbling:
            txt += line + '\n'

    # do string replacements
    for replacement in replacements:
        txt = txt.replace(replacement, replacements[replacement])

    # strip directives and comments
    in_directive = False
    tmp = txt
    txt = ''
    for line in tmp.splitlines():
        if line.strip().startswith('#') or in_directive:
            in_directive = line.strip().endswith('\\')
            continue
        if line.strip().startswith('typedef'):
            continue
        if '//' in line:
            line = line.split('//', 1)[0]
        txt += line

    while ('/*' in txt):
        s1 = txt.split('/*', 1)
        s2 = s1[1].split('*/', 1)
        txt = s1[0] + s2[-1]

    # normalize newlines
    txt = txt.replace('\n', ' ')
    txt = txt.replace(';', ';\n')
    txt = txt.replace('{', '{\n')
    while ('  ' in txt):
        txt = txt.replace('  ', ' ')

    # strip macros
    txt = re.sub(r'[^a-zA-Z0-9_][A-Z0-9_]+\(.*\)', '', txt)

    # strip blocks
    tmp = txt
    txt = ''
    inside = 0
    for character in tmp:
        if inside == 0:
            txt += character
        if character == '{':
            txt += '\n'
            inside += 1
        if character == '}':
            inside -= 1

    # cull obvious non-functions, statics, and externs
    tmp = txt
    txt = ''
    functions = []
    descriptions = {}

    # use raw lines to find descriptions for identified functions
    for line in tmp.splitlines():
        line = line.strip()
        if '(' not in line or ')' not in line or '=' in line:
            continue
        if line.startswith('static ') or line.startswith('extern '):
            continue

        # add function
        functions.append(line)

        # look for a description above the function in raw lines
        function_without_semicolon = line.rstrip(';')
        for i, raw_line in enumerate(raw_lines):
            if function_without_semicolon in raw_line:
                if i - 1 >= 0:
                    prev_line = raw_lines[i - 1].rstrip()
                    if not prev_line.endswith('*/'):
                        break

                # found the function in raw_lines, now look above for |descriptionEnd|
                # We'll scan upwards until we find |descriptionEnd| and then keep going until |description| is found.
                description_end_line_index = None
                for j in range(i - 1, -1, -1):
                    if '|descriptionEnd|' in raw_lines[j]:
                        description_end_line_index = j
                        break

                if description_end_line_index is not None:
                    # Now collect lines upwards until |description| is found, or we hit the top
                    description_lines = []
                    found_description_start = False
                    for k in range(description_end_line_index, -1, -1):
                        if '|description|' in raw_lines[k]:
                            # Found the start marker
                            # Extract text after |description| marker on this line
                            start_match = re.search(r'\|description\|(.*)$', raw_lines[k])
                            if start_match:
                                # Insert this line's text at the start
                                description_lines.insert(0, start_match.group(1).strip())
                            found_description_start = True
                            break
                        else:
                            # These lines are part of the description block
                            description_lines.insert(0, raw_lines[k].strip())

                    if found_description_start and description_lines:
                        # Combine all lines, remove trailing |descriptionEnd| and normalize whitespace
                        combined_description = ' '.join(description_lines)
                        combined_description = re.sub(r'\|\s*descriptionEnd\s*\|.*', '', combined_description).strip()
                        # Normalize whitespace
                        combined_description = re.sub(r'\s+', ' ', combined_description).strip()
                        descriptions[re.sub(r'\)\s*\{', ');', line)] = combined_description
                break

    # normalize function ending
    txt = '\n'.join(functions).replace(' {', ';')
    return txt, descriptions

if __name__ == "__main__":
    functions, descriptions = extract_functions(sys.argv[1])
    print(f"Functions:\n{functions}\n")
    print("Descriptions:")
    for func, desc in descriptions.items():
        print(f"Function: {func}")
        print(f"    Description: {desc}\n")
