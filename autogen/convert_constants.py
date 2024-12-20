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
    "src/pc/djui/djui_panel_menu.h"
]

exclude_constants = {
    "*": [ "^MAXCONTROLLERS$", "^AREA_[^T].*", "^AREA_T[HTO]", "^CONT_ERR.*", "^READ_MASK$", "^SIGN_RANGE$", ],
    "src/game/obj_behaviors.c": [ "^o$" ],
    "src/pc/djui/djui_console.h": [ "CONSOLE_MAX_TMP_BUFFER" ],
    "src/pc/lua/smlua_hooks.h": [ "MAX_HOOKED_MOD_MENU_ELEMENTS" ],
    "src/pc/djui/djui_panel_menu.h": [ "RAINBOW_TEXT_LEN" ]
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

    return True

def process_enum(filename, line):
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

            if saw_constant(field):
                print('>>> ' + line)

        index += 1

    ret['constants'] = constants

    return ret


def process_define(filename, line):
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

    if saw_constant(ident):
        print('>>> ' + line)

    return [ident, val]


def process_line(filename, line):
    if line.startswith('enum '):
        return process_enum(filename, line)
    elif line.startswith('#define '):
        return process_define(filename, line)
    else:
        print("UNRECOGNIZED LINE: " + line)
        return None

def process_file(filename):
    processed_file = {}
    processed_file['filename'] = filename.replace('\\', '/').split('/')[-1]

    constants = []
    lines = extract_constants(get_path(filename)).splitlines()
    for line in lines:
        c = process_line(filename, line)
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
        s += '%s = %s\n' % (c[0], c[1].replace('"', "'"))

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
        s += '\n--- @class %s\n' % translate_to_def(processed_constant['identifier'])
        constants = processed_constant['constants']
        if len(constants) == 0:
            return ''
        for c in constants:
            s += '\n--- @type %s\n' % translate_to_def(processed_constant['identifier'])
            s += '%s = %s\n' % (c[0], c[1])
        return s

    for c in [processed_constant]:
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
