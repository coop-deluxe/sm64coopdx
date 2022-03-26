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
        lines = file.readlines()

    # combine lines
    txt = ''
    for line in lines:
        txt += line

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
    for line in tmp.splitlines():
        line = line.strip()
        if '(' not in line:
            continue
        if ')' not in line:
            continue
        if '=' in line:
            continue
        #if '{' not in line:
        #    continue
        if line.startswith('static '):
            continue
        if line.startswith('extern '):
            continue
        txt += line + '\n'

    # normalize function ending
    txt = txt.replace(' {', ';')
    return txt

if __name__ == "__main__":
    print(extract_functions(sys.argv[1]))