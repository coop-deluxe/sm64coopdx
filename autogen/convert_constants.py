import os
from common import *
from extract_constants import *

in_filename = 'autogen/lua_constants/built-in.lua'
out_filename = 'src/pc/lua/smlua_constants_autogen.c'
out_filename_docs = 'docs/lua/constants.md'

in_files = [
    "include/types.h",
    "include/sm64.h",
    "src/pc/lua/smlua_hooks.h",
    "src/game/camera.h",
    "include/mario_animation_ids.h",
    "include/audio_defines.h",
    "src/game/characters.h",
    "src/pc/network/network_player.h",
    "include/PR/os_cont.h",
]

exclude_constants = [
    '^MAXCONTROLLERS$',
    '^LEVEL_.*',
    '^AREA_.*',
    '^CONT_ERR.*',
]

pretend_find = [
    'SOUND_ARG_LOAD'
]
############################################################################

seen_constants = []
totalConstants = 0

############################################################################

def validate_identifiers(built_files):
    all_identifiers = [x.group()[1:] for x in re.finditer(r'[(, ][A-Z_][A-Z0-9_]*', built_files)]
    all_identifiers = set(all_identifiers)
    for ident in all_identifiers:
        if ident in pretend_find:
            continue
        if ident + ' = ' not in built_files:
            print('COULD NOT FIND ' + ident)


############################################################################

def saw_constant(identifier):
    if identifier in seen_constants:
        print("SAW DUPLICATE CONSTANT: " + identifier)
        return True
    else:
        global totalConstants
        totalConstants += 1
        seen_constants.append(identifier)
        return False

def process_enum(line):
    _, ident, val = line.split(' ', 2)

    if '{' not in val or '}' not in val:
        print('UNRECOGNIZED ENUM: ' + line)
        return None

    # grab inside body
    val = val.split('{', 1)[-1].rsplit('}', 1)[0]

    ret = {}
    ret['identifier'] = ident

    constants = []
    set_to = None
    index = 0
    fields = val.split(',')
    for field in fields:
        field = field.strip()
        if len(field) == 0:
            continue

        if '=' in field:
            ident, val = field.split('=', 2)
            constants.append([ident.strip(), val.strip()])
            set_to = ident
            index = 1
            continue

        if set_to is not None:
            constants.append([field, '((%s) + %d)' % (set_to, index)])
            index += 1
            continue

        excluded = False
        for exclude in exclude_constants:
            if re.search(exclude, field) != None:
                excluded = True

        if not excluded:
            constants.append([field, str(index)])

            if saw_constant(field):
                print('>>> ' + line)
        index += 1

    ret['constants'] = constants

    return ret


def process_define(line):
    _, ident, val = line.split(' ', 2)

    val = val.replace('(u8)', '')
    val = val.replace('(u64)', '')

    for p in val.split(' '):
        if p.startswith('0x'):
            continue
        p = re.sub(r'0x[a-fA-F0-9]+', '', p)
        if re.search('[a-z]', p) != None:
            print('UNRECOGNIZED DEFINE: ' + line)
            return None

    for exclude in exclude_constants:
        if re.search(exclude, ident) != None:
            return None

    if saw_constant(ident):
        print('>>> ' + line)

    return [ident, val]


def process_line(line):
    if line.startswith('enum '):
        return process_enum(line)
    elif line.startswith('#define '):
        return process_define(line)
    else:
        print("UNRECOGNIZED LINE: " + line)
        return None

def process_file(filename):
    processed_file = {}
    processed_file['filename'] = filename.replace('\\', '/').split('/')[-1]

    constants = []
    lines = extract_constants(get_path(filename)).splitlines()
    for line in lines:
        c = process_line(line)
        if c != None:
            constants.append(c)

    processed_file['constants'] = constants

    return processed_file

def process_files():
    seen_constants = []
    processed_files = []
    files = sorted(in_files, key=lambda d: d.split('/')[-1])
    for f in files:
        processed_files.append(process_file(f))
    return processed_files

############################################################################

def build_constant(processed_constant):
    constants = processed_constant
    s = ''

    is_enum = 'identifier' in processed_constant
    if is_enum:
        constants = processed_constant['constants']
    else:
        constants = [processed_constant]

    for c in constants:
        s += '%s = %s\n' % (c[0], c[1])

    return s

def build_file(processed_file):
    s = ''
    for c in processed_file['constants']:
        s += build_constant(c)

    return s

def build_files(processed_files):
    s = ''
    for file in processed_files:
        s += build_file(file)

    return s

def build_to_c(built_files):
    txt = ''
    with open(get_path(in_filename), 'r') as f:
        txt = f.read()
    txt += '\n' + built_files

    while ('\n\n' in txt):
        txt = txt.replace('\n\n', '\n')

    lines = txt.splitlines()
    txt = 'char gSmluaConstants[] = ""\n'
    for line in lines:
        txt += '"%s\\n"\n' % line
    txt += ';'
    return txt

############################################################################

def doc_constant_index(processed_files):
    s = '# Supported Constants\n'
    for processed_file in processed_files:
        s += '- [%s](#%s)\n' % (processed_file['filename'], processed_file['filename'])
        constants = [x for x in processed_file['constants'] if 'identifier' in x]
        constants = sorted(constants, key=lambda d: d['identifier'])
        for c in constants:
            s += '    - [%s](#%s)\n' % (c['identifier'], c['identifier'])
    s += '\n<br />\n\n'
    return s

def doc_constant(processed_constant):
    constants = processed_constant
    s = ''

    is_enum = 'identifier' in processed_constant
    if is_enum:
        constants = processed_constant['constants']
        if len(constants) == 0:
            return ''

        enum = 'enum ' + processed_constant['identifier']
        s += '\n### [%s](#%s)\n' % (enum, processed_constant['identifier'])
        s += '| Identifier | Value |\n'
        s += '| :--------- | :---- |\n'
        for c in constants:
            s += '| %s | %s |\n' % (c[0], c[1])
        return s

    for c in [processed_constant]:
        s += '- %s\n' % (c[0])

    return s

def doc_file(processed_file):
    s = '## [%s](#%s)\n' % (processed_file['filename'], processed_file['filename'])
    constants = sorted(processed_file['constants'], key=lambda d: 'zzz' + d['identifier'] if 'identifier' in d else d[0])
    for c in constants:
        s += doc_constant(c)

    s += '\n<br />\n\n'
    return s

def doc_files(processed_files):
    s = '## [:rewind: Lua Reference](lua.md)\n\n'
    s += doc_constant_index(processed_files)
    for file in processed_files:
        s += doc_file(file)

    return s

############################################################################

def main():
    processed_files = process_files()
    built_files = build_files(processed_files)
    validate_identifiers(built_files)

    built_c = build_to_c(built_files)

    with open(get_path(out_filename), 'w') as out:
        out.write(built_c)

    doc = doc_files(processed_files)
    with open(get_path(out_filename_docs), 'w') as out:
        out.write(doc)

    global totalConstants
    print("Total constants: " + str(totalConstants))

main()