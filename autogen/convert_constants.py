from common import *
from extract_constants import *
import sys

in_filename = 'autogen/lua_constants/built-in.lua'
out_filename = 'src/pc/lua/smlua_constants_autogen.c'
out_filename_docs = 'docs/lua/constants.md'
out_filename_defs = 'autogen/lua_definitions/constants.lua'

in_files = [
    "include/types.h",
    "include/sm64.h",
    "src/pc/lua/smlua_hooks.h",
    "src/game/area.h",
    "src/game/camera.h",
    "include/mario_animation_ids.h",
    "include/sounds.h",
    "src/game/characters.h",
    "src/pc/network/network.h",
    "src/pc/network/network_player.h",
    "include/PR/os_cont.h",
    "src/game/interaction.c",
    "src/game/interaction.h",
    "src/pc/djui/djui_hud_utils.h",
    "include/behavior_table.h",
    "src/pc/lua/utils/smlua_model_utils.h",
    "src/pc/lua/utils/smlua_misc_utils.h",
    "include/object_constants.h",
    "include/mario_geo_switch_case_ids.h",
    "src/game/object_list_processor.h",
    "src/engine/graph_node.h",
    "levels/level_defines.h",
    "src/game/obj_behaviors.c",
    "src/game/save_file.h",
    "src/game/obj_behaviors_2.h",
    "include/dialog_ids.h",
    "include/seq_ids.h",
    "include/surface_terrains.h",
    "src/game/level_update.h",
    "src/pc/network/version.h",
    "include/geo_commands.h",
    "include/level_commands.h",
    "src/audio/external.h",
    "src/game/envfx_snow.h",
    "src/pc/mods/mod_storage.h",
    "src/game/first_person_cam.h",
    "src/pc/djui/djui_console.h",
    "src/game/player_palette.h",
    "src/pc/network/lag_compensation.h",
    "src/pc/djui/djui_panel_menu.h",
    "include/PR/gbi.h"
]

exclude_constants = {
    "*": [ "^MAXCONTROLLERS$", "^AREA_[^T].*", "^AREA_T[HTO]", "^CONT_ERR.*", "^READ_MASK$", "^SIGN_RANGE$", ],
    "src/game/obj_behaviors.c": [ "^o$" ],
    "src/pc/djui/djui_console.h": [ "CONSOLE_MAX_TMP_BUFFER" ],
    "src/pc/lua/smlua_hooks.h": [ "MAX_HOOKED_MOD_MENU_ELEMENTS" ],
    "src/pc/djui/djui_panel_menu.h": [ "RAINBOW_TEXT_LEN" ],
    "include/PR/gbi.h": ["RM_AA_", "G_RM_", "G_CC_"]
}

include_constants = {
    "include/geo_commands.h": [ "BACKGROUND" ],
    "include/level_commands.h": [ "WARP_CHECKPOINT", "WARP_NO_CHECKPOINT" ],
    "src/audio/external.h": [ "SEQ_PLAYER", "DS_" ],
    "src/pc/mods/mod_storage.h": [ "MAX_KEYS", "MAX_KEY_VALUE_LENGTH" ]
}

pretend_find = [
    "SOUND_ARG_LOAD"
]
############################################################################

seen_constants = []
totalConstants = 0
verbose = len(sys.argv) > 1 and (sys.argv[1] == "-v" or sys.argv[1] == "--verbose")
overrideConstant = {
    'VERSION_REGION': '"US"',
}
forced_defines = ['F3DEX_GBI_2']

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
        global totalConstants
        totalConstants += 1
        seen_constants.append(identifier)
        return False

def allowed_identifier(filename, ident):
    exclude_list = exclude_constants['*']

    if filename in exclude_constants:
        exclude_list.extend(exclude_constants[filename])

    for exclude in exclude_list:
        if re.search(exclude, ident) != None:
            return False

    if filename in include_constants:
        for include in include_constants[filename]:
            if re.search(include, ident) != None:
                return True
        return False

    if ident in overrideConstant:
        return False

    return True

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

        if allowed_identifier(filename, field):
            constants.append([field, str(index)])

            if saw_constant(field, inIfBlock):
                print('>>> ' + line)

        index += 1

    ret['constants'] = constants

    return ret


def process_define(filename, line, inIfBlock):
    _, ident, val = line.split(' ', 2)

    val = val.replace('(u8)', '')
    val = val.replace('(u64)', '')
    val = re.sub(r'\.\d+f', '', val)

    for p in val.split(' '):
        if p.startswith('0x'):
            continue
        p = re.sub(r'0x[a-fA-F0-9]+', '', p)
        if re.search(r'[a-z]', p) != None and "VERSION_TEXT" not in line and "SM64COOPDX_VERSION" not in line:
            if 'gCurrentObject' not in line and verbose:
                print('UNRECOGNIZED DEFINE: ' + line)
            return None

    if not allowed_identifier(filename, ident):
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
    files = sorted(in_files, key=lambda d: d.split('/')[-1])
    for f in files:
        processed_files.append(process_file(f))
    for key, item in overrideConstant.items():
        processed_files[0]['constants'].append([key, item])
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
        if c[0].startswith('#'):
            s += '%s\n' % c[0]
            continue
        s += '%s=%s\n' % (c[0], c[1].replace('"', "'"))

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
        txt = ''
        for line in f.readlines():
            txt += line.strip() + '\n'
    txt += '\n' + built_files

    while ('\n\n' in txt):
        txt = txt.replace('\n\n', '\n')

    lines = txt.splitlines()
    txt = "".join(f"#define {item}\n" for item in forced_defines)
    txt += 'char gSmluaConstants[] = ""\n'
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
        constants = sorted(constants, key=lambda d: d['identifier'])
        for c in constants:
            s += '    - [enum %s](#enum-%s)\n' % (c['identifier'], c['identifier'])
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
        if c[0].startswith('#'):
            continue
        s += '- %s\n' % (c[0])

    return s

def doc_file(processed_file):
    s = '## [%s](#%s)\n' % (processed_file['filename'], processed_file['filename'])
    constants = sorted(processed_file['constants'], key=lambda d: 'zzz' + d['identifier'] if 'identifier' in d else d[0])
    for c in constants:
        s += doc_constant(c)

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

def def_constant(processed_constant):
    constants = processed_constant
    s = ''

    is_enum = 'identifier' in processed_constant
    if is_enum:
        constants = processed_constant['constants']
        if len(constants) == 0:
            return ''
        id = translate_to_def(processed_constant['identifier'])
        klen = 0
        vlen = 0
        s += '\n'
        for c in constants:
            klen = max(klen, len(c[0]))
            vlen = max(vlen, len(c[1]))
        for c in constants:
            s += c[0].ljust(klen) + ' = ' + c[1].rjust(vlen) + ' --- @type %s\n' % id
        s += '\n--- @alias %s\n' % id
        for c in constants:
            s += '--- | `%s`\n' % c[0]
        return s

    for c in [processed_constant]:
        if c[0].startswith('#'):
            continue
        if '"' in c[1]:
            s += '\n--- @type string\n'
        else:
            s += '\n--- @type integer\n'
        s += '%s = %s\n' % (c[0], c[1])

    return s

def build_to_def(processed_files):
    s = '-- AUTOGENERATED FOR CODE EDITORS --\n\n'
    with open(get_path(in_filename), 'r') as f:
        s += f.read()
        s += '\n'

    for file in processed_files:
        constants = sorted(file['constants'], key=lambda d: 'zzz' + d['identifier'] if 'identifier' in d else d[0])
        for c in constants:
            s += def_constant(c)

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

    defs = build_to_def(processed_files)
    with open(get_path(out_filename_defs), 'w') as out:
        out.write(defs)

    global totalConstants
    print("Total constants: " + str(totalConstants))

main()
