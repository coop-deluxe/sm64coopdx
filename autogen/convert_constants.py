import sys
from common import *
from extract_constants import *
from vec_types import *
from exposed_lists import \
    constants_files, \
    constants_whitelist, \
    constants_blacklist, \
    constants_hidden

verbose = len(sys.argv) > 1 and (sys.argv[1] == "-v" or sys.argv[1] == "--verbose")

in_filenames = ['autogen/lua_constants/built-in.lua', 'autogen/lua_constants/math.lua']
deprecated_filename = 'autogen/lua_constants/deprecated.lua'
out_filename = 'src/pc/lua/smlua_constants_autogen.c'
out_filename_docs = 'docs/lua/constants.md'
out_filename_defs = 'autogen/lua_definitions/constants.lua'

############################################################################

seen_constants = []
totalConstants = 0
overrideConstant = {
    'VERSION_REGION': '"US"',
}
defined_values = {
    'VERSION_US': True,
    'VERSION_EU': False,
    'VERSION_JP': False,
    'VERSION_SH': False,
    'F3DEX_GBI_2': True,
    'DEVELOPMENT': False,
}
pretend_find = [
    "SOUND_ARG_LOAD",
]

############################################################################

def validate_identifiers(built_files):
    files = ''
    for f in built_files.splitlines():
        if f.startswith('#'):
            continue
        files += f + '\n'
    all_identifiers = [x.group()[1:] for x in re.finditer(r'[(, ][A-Z_][A-Z0-9_]*', files)]
    all_identifiers = set(all_identifiers)
    for ident in all_identifiers:
        if ident in pretend_find:
            continue
        if ident + '=' not in built_files:
            print('COULD NOT FIND ' + ident)

############################################################################

def saw_constant(identifier, inIfBlock):
    if inIfBlock:
        return False
    if identifier in seen_constants:
        print("SAW DUPLICATE CONSTANT: " + identifier)
        return True
    else:
        seen_constants.append(identifier)
        return False

def get_constant(filename, line, inIfBlock, field, index, set_to, set_to_val):
    if set_to is not None:
        if allowed_identifier(constants_whitelist, constants_blacklist, filename, field):
            if set_to_val is not None:
                return [field, str(set_to_val + index)]
            return [field, '((%s) + %d)' % (set_to, index)]

    elif allowed_identifier(constants_whitelist, constants_blacklist, filename, field):
        if saw_constant(field, inIfBlock):
            print('>>> ' + line)
        return [field, str(index)]

    return None

def process_enum(filename, line, inIfBlock):
    _, ident, val = line.split(' ', 2)

    if '{' not in val or '}' not in val:
        #print('UNRECOGNIZED ENUM: ' + line)
        return None

    # grab inside body
    val = val.split('{', 1)[-1].rsplit('}', 1)[0]

    ret = {}
    ret['identifier'] = ident

    constants = []
    set_to = None
    set_to_val = None
    index = 0
    fields = val.split(',')
    for field in fields:
        field = field.strip()
        if len(field) == 0:
            continue

        if '=' in field:
            ident, val = field.split('=', 1)
            ident = ident.strip()
            val = val.strip()

            try:
                set_to_val = int(eval(val, {}, {}))
            except Exception:
                set_to_val = None

            if allowed_identifier(constants_whitelist, constants_blacklist, filename, field):
                constants.append([ident, val])
            set_to = ident
            index = 1
            continue

        constant = get_constant(filename, line, inIfBlock, field, index, set_to, set_to_val)
        if constant is not None:
            constants.append(constant)

        index += 1

    ret['constants'] = constants

    return ret


def process_define(filename, line, inIfBlock):
    _, ident, val = line.split(' ', 2)

    val = val.replace('(u8)', '')
    val = val.replace('(u64)', '')
    val = re.sub(r'\.\d+f', '', val)
    val = val.strip()

    if not (val.startswith('"') and val.endswith('"') and '"' not in val[1:-1]):
        for p in val.split(' '):
            if p.startswith('0x'):
                continue
            p = re.sub(r'0x[a-fA-F0-9]+', '', p)
            if re.search(r'[a-z]', p) != None and "VERSION_TEXT" not in line and "SM64COOPDX_VERSION" not in line:
                if 'gCurrentObject' not in line and verbose:
                    print('UNRECOGNIZED DEFINE: ' + line)
                return None

    if not allowed_identifier(constants_whitelist, constants_blacklist, filename, ident):
        return None

    if saw_constant(ident, inIfBlock):
        print('>>> ' + line)

    return [ident, val]


def process_line(filename, line, inIfBlock):
    if line.startswith('enum '):
        return process_enum(filename, line, inIfBlock)
    elif line.startswith('#define '):
        return process_define(filename, line, inIfBlock)
    else:
        print("UNRECOGNIZED LINE: " + line)
        return None

def process_file(filename):
    processed_file = {}
    processed_file['filename'] = filename.replace('\\', '/').split('/')[-1]

    constants = []
    lines = extract_constants(get_path(filename)).splitlines()

    block_stack = None

    for line in lines:
        if line.startswith('#if'):
            if not block_stack: block_stack = []
            block_stack.append({
                'if_line': line,
                'then': [],
                'else': None,
                'else_line': None,
                'ignore': line.endswith('_H') or line.endswith('_H_')
            })
        elif line.startswith("#else"):
            if not block_stack: continue
            current = block_stack[-1]
            if current['ignore']: continue
            current['else_line'] = line
            current['else'] = []
        elif line.startswith("#endif"):
            if not block_stack: continue
            block = block_stack.pop()
            if not block['ignore'] and len(block['then']) > 0 and block['else']:
                block['then'].append([block['else_line'] + ' // ' + block['if_line']]) # append else line
                block['else'].append([line + ' // ' + block['if_line']]) # append endif line
                constants.append([block['if_line']])
            constants.extend(block['then'])
            if block['else']:
                constants.extend(block['else'])
        else:
            c = process_line(filename, line, block_stack is not None)
            if c is not None:
                if block_stack and not block_stack[-1]['ignore']:
                    current = block_stack[-1]
                    if current['else'] is not None:
                        current['else'].append(c)
                    else:
                        current['then'].append(c)
                else:
                    constants.append(c)

    processed_file['constants'] = constants
    return processed_file

def process_files():
    seen_constants = []
    processed_files = []
    files = sorted(constants_files, key=lambda d: d.split('/')[-1])
    for f in files:
        processed_files.append(process_file(f))
    for key, item in overrideConstant.items():
        processed_files[0]['constants'].append([key, item])
    return processed_files

############################################################################

def build_constant(processed_constant, skip_constant):
    constants = processed_constant
    s = ''

    is_enum = 'identifier' in processed_constant
    if is_enum:
        constants = processed_constant['constants']
    else:
        constants = [processed_constant]

    for c in constants:
        if c[0].startswith('#'):
            if c[0].startswith('#ifdef'):
                skip_constant = not defined_values[c[0].split()[1]]
            elif c[0].startswith('#else'):
                skip_constant = not skip_constant
            elif c[0].startswith('#endif'):
                skip_constant = False
            continue
        if skip_constant:
            continue
        s += '%s=%s\n' % (c[0], c[1].replace('"', "'"))

    return s, skip_constant

def build_file(processed_file):
    s = ''
    skip_constant = False
    for c in processed_file['constants']:
        cs, skip_constant = build_constant(c, skip_constant)
        s += cs

    return s

def build_files(processed_files):
    s = ''
    for file in processed_files:
        s += build_file(file)

    return s

def build_vec_type_constant(type_name, vec_type, constant, values):
    txt = 'g%s%s = create_read_only_table({' % (type_name, constant)
    txt += ','.join([
        '%s=%s' % (lua_field, str(values[i]))
        for i, lua_field in enumerate(vec_type["fields_mapping"])
    ])
    txt += '})'
    return txt

def build_to_c(built_files):
    txt = ''

    # Built-in and deprecated
    for filename in [*in_filenames, deprecated_filename]:
        with open(get_path(filename), 'r') as f:
            for line in f.readlines():
                txt += line.strip() + '\n'

    # Vec types constants
    for type_name, vec_type in VEC_TYPES.items():
        for constant, values in vec_type.get("constants", {}).items():
            txt += build_vec_type_constant(type_name, vec_type, constant, values) + '\n'

    # Source files
    txt += '\n' + built_files

    while ('\n\n' in txt):
        txt = txt.replace('\n\n', '\n')

    lines = txt.splitlines()
    txt = 'const char gSmluaConstants[] = ""\n'
    for line in lines:
        if line.startswith("#"):
            txt += '%s\n' % line
            continue
        txt += '"%s\\n"\n' % line
    txt += ';'
    return txt

############################################################################

def doc_constant_index(processed_files):
    s = '# Supported Constants\n'
    for processed_file in processed_files:
        s += '- [%s](#%s)\n' % (processed_file['filename'], processed_file['filename'].replace('.', ''))
        constants = [x for x in processed_file['constants'] if 'identifier' in x]
        for c in constants:
            if len(c['constants']) > 0:
                s += '    - [enum %s](#enum-%s)\n' % (c['identifier'], c['identifier'])
    s += '\n<br />\n\n'
    return s

def doc_constant(fname, processed_constant):
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
        if c[0].startswith('#'):
            continue
        if not allowed_identifier(None, constants_hidden, fname, c[0]):
            continue
        s += '- %s\n' % (c[0])

    return s

def doc_file(processed_file):
    s = '## [%s](#%s)\n' % (processed_file['filename'], processed_file['filename'])
    constants = processed_file['constants']
    for c in constants:
        s += doc_constant(processed_file['filename'], c)

    s += '\n[:arrow_up_small:](#)\n'
    s += '\n<br />\n\n'
    return s

def doc_files(processed_files):
    s = '## [:rewind: Lua Reference](lua.md)\n\n'
    s += doc_constant_index(processed_files)
    for file in processed_files:
        s += doc_file(file)

    return s

############################################################################

def def_constant(fname, processed_constant, skip_constant):
    global totalConstants
    constants = processed_constant
    s = ''

    is_enum = 'identifier' in processed_constant
    if is_enum:
        constants = processed_constant['constants']
        if len(constants) == 0:
            return '', skip_constant
        id = translate_to_def(processed_constant['identifier'])
        klen = 0
        vlen = 0
        s += '\n'
        for c in constants:
            klen = max(klen, len(c[0]))
            vlen = max(vlen, len(c[1]))
        for c in constants:
            s += c[0].ljust(klen) + ' = ' + c[1].rjust(vlen) + ' --- @type %s\n' % id
            totalConstants += 1
        s += '\n--- @alias %s\n' % id
        for c in constants:
            s += '--- | `%s`\n' % c[0]
        return s, skip_constant

    for c in [processed_constant]:
        if c[0].startswith('#'):
            if c[0].startswith('#ifdef'):
                skip_constant = not defined_values[c[0].split()[1]]
            elif c[0].startswith('#else'):
                skip_constant = not skip_constant
            elif c[0].startswith('#endif'):
                skip_constant = False
            continue
        if skip_constant:
            continue
        if not allowed_identifier(None, constants_hidden, fname, c[0]):
            continue
        if '"' in c[1]:
            s += '\n--- @type string\n'
        elif "." in c[1]:
            s += '\n--- @type number\n'
        else:
            s += '\n--- @type integer\n'
        s += '%s = %s\n' % (c[0], c[1])
        totalConstants += 1

    return s, skip_constant

def build_to_def(processed_files):
    s = '-- AUTOGENERATED FOR CODE EDITORS --\n\n'
    for filename in in_filenames:
        with open(get_path(filename), 'r') as f:
            s += f.read()
            s += '\n'

    s += '\n\n-------------------------\n'
    s += '-- vec types constants --\n'
    s += '-------------------------\n\n'
    for type_name, vec_type in VEC_TYPES.items():
        for constant, values in vec_type.get("constants", {}).items():
            s += '--- @type %s\n' % (type_name)
            s += build_vec_type_constant(type_name, vec_type, constant, values) + '\n\n'

    for file in processed_files:
        constants = file['constants']
        skip_constant = False
        for c in constants:
            cs, skip_constant = def_constant(file['filename'], c, skip_constant)
            s += cs

    return s

############################################################################

def main():
    processed_files = process_files()
    built_files = build_files(processed_files)
    validate_identifiers(built_files)

    built_c = build_to_c(built_files)

    with open(get_path(out_filename), 'w', encoding='utf-8', newline='\n') as out:
        out.write(built_c)

    doc = doc_files(processed_files)
    with open(get_path(out_filename_docs), 'w', encoding='utf-8', newline='\n') as out:
        out.write(doc)

    defs = build_to_def(processed_files)
    with open(get_path(out_filename_defs), 'w', encoding='utf-8', newline='\n') as out:
        out.write(defs)

    global totalConstants
    print("Total constants: " + str(totalConstants))

main()
