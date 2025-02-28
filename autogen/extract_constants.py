import os
import re
import sys

def extract_level_defines(txt):
    tmp = txt
    txt = 'enum LevelNum {\n    LEVEL_NONE,\n'
    for line in tmp.splitlines():
        if line.startswith('STUB_LEVEL') or line.startswith('DEFINE_LEVEL'):
            txt += '    ' + line.split(',')[1].strip() + ',\n'
    txt += '    LEVEL_COUNT,\n };'
    return txt

extra_steps = {
    "levels/level_defines.h": extract_level_defines,
}

def extract_constants(filename):
    with open(filename) as file:
        txt = file.read()

    # perform special functions
    short_filename = filename.split('/../', 1)[-1]
    if short_filename in extra_steps:
        txt = extra_steps[short_filename](txt)

    # strip comments
    txt = re.sub('//.*', ' ', txt)
    while ('/*' in txt):
        s1 = txt.split('/*', 1)
        s2 = s1[1].split('*/', 1)
        txt = s1[0] + s2[-1]

    # strip multiline continues
    txt = re.sub(r'\\\n', ' ', txt)

    # strip extern C
    txt = re.sub(r'extern "C" {', ' ', txt)

    # single-line blocks
    txt = re.sub(r'{\n', '{ ', txt)
    txt = re.sub(r'\n{', ' {', txt)
    tmp = txt
    txt = ''
    inside = 0
    for character in tmp:
        if inside > 0 and character == '\n':
            continue

        txt += character

        if character == '{':
            inside += 1

        if character == '}':
            inside -= 1

    # normalize whitespace
    txt = txt.replace('\t', ' ')
    while ('  ' in txt):
        txt = txt.replace('  ', ' ')
    while ('\n\n' in txt):
        txt = txt.replace('\n\n', '\n')

    # Cull false ifdef blocks
    tmp = txt
    txt = ''
    inside_false = 0
    for line in tmp.splitlines():
        line = line.strip()
        if line == '#ifdef _LANGUAGE_ASSEMBLY' or line.startswith('#if '):
            inside_false += 1
            continue
        if line.startswith('#else') and inside_false > 0:
            continue
        if line.startswith('#endif') and inside_false > 0:
            inside_false -= 1
            continue
        if inside_false == 0:
            txt += line + '\n'

    # cull obvious non-enums, non-defines
    tmp = txt
    txt = ''
    for line in tmp.splitlines():
        line = line.strip()
        if line.startswith('enum '):
            txt += line + '\n'
        if line.startswith('#define '):
            pieces = line.split(' ')
            if len(pieces) < 3:
                continue
            if '(' in pieces[1]:
                continue
            txt += line + '\n'
        if line.startswith('#if') or line == '#else' or line == '#endif':
            txt += line + '\n'

    return txt

if __name__ == "__main__":
    print(extract_constants(sys.argv[1]))