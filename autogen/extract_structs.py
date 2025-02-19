import os
import re
import sys

def extract_structs(filename):
    with open(filename) as file:
        lines = file.readlines()

    txt = ''
    # strip line continuation
    for line in lines:
        if line.strip().endswith('\\'):
            txt += line.strip()[:-1] + ' '
        else:
            txt += line

    # strip directives and comments
    tmp = txt
    txt = ''
    for line in tmp.splitlines():
        if line.strip().startswith('#'):
            continue
        if '//' in line:
            line = line.split('//', 1)[0]
        txt += line + '\n'

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
        if character == '\n':
            if inside == 0:
                txt += character
        else:
            txt += character

        if character == '{':
            inside += 1

        if character == '}':
            inside -= 1

    # extract structs
    tmp = txt
    txt = ''
    for line in tmp.splitlines():
        line = line.strip()
        if '{' not in line:
            continue
        if '}' not in line:
            continue
        if ';' not in line:
            continue
        if not line.startswith('struct ') and not line.startswith('typedef struct '):
            continue
        txt += line + '\n'

    return txt.splitlines()

if __name__ == "__main__":
    print(extract_structs(sys.argv[1]))