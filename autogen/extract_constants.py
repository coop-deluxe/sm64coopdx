import os
import re
import sys

def extract_constants(filename):
    with open(filename) as file:
        txt = file.read()

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
        if inside != 0 and character == '\n':
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

    # BAD culling of ifdef version
    tmp = txt
    txt = ''
    inside = 0
    for line in tmp.splitlines():
        line = line.strip()
        if line == '#ifdef VERSION_JP':
            inside = 1
            continue
        if line == '#ifdef VERSION_EU':
            inside = 1
            continue
        if line == '#else':
            inside = 0
            continue
        if line == '#endif':
            inside = 0
            continue
        if inside == 0:
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

    return txt

#print(extract_constants("include/audio_defines.h"))
