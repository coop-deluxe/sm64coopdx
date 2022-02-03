import os
import re
import sys

def extract_functions(filename):
    with open(filename) as file:
        lines = file.readlines()

    # strip directives and comments
    in_directive = False
    txt = ''
    for line in lines:
        if line.strip().startswith('#') or in_directive:
            in_directive = line.strip().endswith('\\')
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
