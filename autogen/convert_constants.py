import os
from common import *

in_filename = os.path.dirname(os.path.realpath(__file__)) + "/lua_constants/constants.lua"
out_filename = os.path.dirname(os.path.realpath(__file__)) + '/../src/pc/lua/smlua_constants_autogen.c'
docs_lua_constants = 'docs/lua/constants.md'

############################################################################

def build_constants():
    built = "char gSmluaConstants[] = "
    with open(in_filename) as fp:
        lines = fp.readlines()
        for line in lines:
            if line.startswith('--'):
                continue
            if line.strip() == '':
                continue
            built += '"' + line.replace('\n', '').replace('\r', '') + '\\n"' + "\n"
    built += ';'

    with open(out_filename, 'w') as out:
        out.write(built)

############################################################################

def doc_process(lines):
    processed = []
    cur = None

    for line in lines:

        if line.startswith('--'):
            spl = line.split()
            if len(spl) == 3 and spl[0] == spl[2]:
                if cur != None:
                    processed.append(cur)
                cur = {}
                cur['category'] = spl[1].strip()
                cur['constants'] = []
            continue

        if len(line.strip()) == 0:
            if len(cur['constants']) == 0:
                continue

            if len(cur['constants'][-1]) == 0:
                continue

            cur['constants'].append('')
            continue

        if '=' not in line:
            continue

        if line[0] < 'A' or line[0] > 'Z':
            continue

        cur['constants'].append(line.strip().split(' ')[0])

    if cur != None:
        processed.append(cur)

    processed = sorted(processed, key=lambda d: d['category'])
    return processed

def doc_build_category(p):
    category = p['category']
    constants = p['constants']
    if len(constants[-1]) == 0:
        constants = constants[:-1]

    if len(constants) == 0:
        return

    s = '\n## [%s](%s)\n' % (category, category)

    for c in constants:
        if len(c) == 0:
            s += '\n<br />\n\n'
            continue

        s += '- %s\n' % c

    s += '\n[:arrow_up_small:](#)\n\n<br />\n'

    return s

def doc_build_index(processed):
    s = '# Supported Constants\n'
    for p in processed:
        s += '- [%s](#%s)\n' % (p['category'], p['category'])

    s += '\n<br />\n'

    return s

def doc_build(processed):
    s = '## [:rewind: Lua Reference](lua.md)\n\n'
    s += doc_build_index(processed)
    for p in processed:
        s += doc_build_category(p)

    with open(get_path(docs_lua_constants), 'w') as out:
        out.write(s)

def doc_constants():
    with open(in_filename) as fp:
        lines = fp.readlines()

    processed = doc_process(lines)
    doc_build(processed)


############################################################################

build_constants()
doc_constants()