import os
from vec_types import *

usf_types = ['u8', 'u16', 'u32', 'u64', 's8', 's16', 's32', 's64', 'f32']
vec_types = list(VEC_TYPES.keys())
typedef_pointers = ['BehaviorScript', 'ObjectAnimPointer', 'Collision', 'LevelScript', 'Trajectory']

exclude_structs = [
    'SPTask',
    'VblankHandler',
    'GraphNodeRoot',
    'MarioAnimDmaRelatedThing',
    'UnusedArea28',
]

def get_path(p):
    return os.path.dirname(os.path.realpath(__file__)) + '/../' + p

def translate_type_to_lvt(ptype):
    pointerLvl = 0

    if ptype == "char":
        ptype = "u8"

    if "const " in ptype:
        ptype = ptype.replace("const ", "").strip()

    if ("char" in ptype and "[" in ptype):
        return "LVT_STRING"

    if "[" in ptype or "{" in ptype:
        return "LVT_???"

    # Strip out our pointer stars to get the true type.
    if "*" in ptype:
        # Count how many stars there is for our pointer level.
        pointerLvl = ptype.count("*")
        ptype = ptype.replace("*", "").strip()

    if ptype == "char" and pointerLvl == 1:
        return "LVT_STRING_P"

    if "enum " in ptype:
        if pointerLvl > 1:
            return "LVT_???"
        if pointerLvl == 1:
            return "LVT_S32_P"
        return "LVT_S32"

    if ptype == "bool":
        if pointerLvl > 1:
            return "LVT_???"
        if pointerLvl == 1:
            return "LVT_BOOL_P"
        return "LVT_BOOL"

    if ptype in usf_types:
        if pointerLvl > 1:
            return "LVT_???"
        if pointerLvl == 1:
            return "LVT_" + ptype.upper() + "_P"
        return "LVT_" + ptype.upper()

    if ptype in vec_types:
        if pointerLvl > 1:
            return "LVT_???"
        if pointerLvl == 1:
            return "LVT_COBJECT_P"
        return "LVT_COBJECT"

    if ptype == "float":
        if pointerLvl > 1:
            return "LVT_???"
        if pointerLvl == 1:
            return "LVT_F32_P"
        return "LVT_F32"

    if ptype == "LuaFunction":
        return "LVT_LUAFUNCTION"

    if "struct" in ptype:
        if pointerLvl > 1:
            return "LVT_???"
        if pointerLvl == 1:
            return "LVT_COBJECT_P"
        return "LVT_COBJECT"

    if pointerLvl == 1 and "(" not in ptype and "[" not in ptype:
        ptype = ptype.replace("const", "").replace("*", "").strip()
        if ptype in usf_types or ptype in typedef_pointers:
            return "LVT_%s_P" % ptype.upper()

    return "LVT_???"

def translate_type_to_lot(ptype):
    pointerLvl = 0
    lvt = translate_type_to_lvt(ptype)

    if ptype == 'void':
        return 'LOT_NONE'

    if ptype == 'const char*':
        return 'LOT_NONE'

    if ptype == 'char*' or ('char' in ptype and '[' in ptype):
        return 'LOT_NONE'

    if 'const ' in ptype:
        ptype = ptype.replace('const ', '')

    if ptype == 'char':
        ptype = 'u8'

    if '[' in ptype or '{' in ptype:
        return 'LOT_???'

    if 'enum ' in ptype:
        return 'LOT_NONE'

    if ptype in usf_types:
        return 'LOT_NONE'

    # Strip out our pointer stars to get the true type.
    if "*" in ptype:
        # Count how many stars there is for our pointer level.
        pointerLvl = ptype.count("*")
        ptype = ptype.replace("*", "").strip()

    if ptype == 'bool':
        return 'LOT_NONE'

    if ptype in vec_types:
        return 'LOT_' + ptype.upper()

    if ptype == 'float':
        return 'LOT_NONE'

    if ptype == 'LuaFunction':
        return 'LOT_NONE'

    if 'struct' in ptype:
        if pointerLvl > 1:
            return 'LOT_???'

        struct_id = ptype.split(' ')[1]

        if struct_id in exclude_structs:
            return 'LOT_???'

        return 'LOT_' + struct_id.upper()

    if pointerLvl > 0 and '???' not in lvt:
        # return 'LOT_POINTER /* ' + ptype + ' */'
        return 'LOT_POINTER'

    return 'LOT_???'

def translate_type_to_lua(ptype):
    if ptype.startswith('struct '):
        ptype = ptype.split(' ')[1].replace('*', '')
        return ptype, 'structs.md#%s' % ptype

    if ptype == 'const char*':
        return '`string`', None

    if ptype == 'char*' or ('char' in ptype and '[' in ptype):
        return '`string`', None

    ptype = ptype.replace('const ', '')

    if 'Vec3' in ptype:
        return ptype, 'structs.md#%s' % ptype

    if ptype.startswith('enum '):
        return ptype, 'constants.md#%s' % ptype.replace(' ', '-')

    if ptype in usf_types:
        if ptype.startswith('f'):
            return '`number`', None
        return '`integer`', None

    if ptype == 'char':
        return '`integer`', None

    if ptype == 'int':
        return '`integer`', None

    if ptype == 'float':
        return '`number`', None

    if ptype == 'double':
        return '`number`', None

    if ptype == 'bool':
        return '`boolean`', None

    if 'void' == ptype:
        return None, None

    if ptype == 'LuaFunction':
        return '`Lua Function` ()', None

    if ptype.count('*') == 1 and '???' not in translate_type_to_lvt(ptype):
        ptype = ptype.replace('const', '').replace('*', '').strip()
        s = '`Pointer` <%s>' % translate_type_to_lua(ptype)[0]
        return s, None

    if not ptype.startswith('`'):
        ptype = '`' + ptype + '`'

    return ptype, None

def translate_type_to_rnd(ltype):
    if 'enum ' in ltype:
        ltype = 'integer'
    elif '[' in ltype:
        ltype = 'null'
    elif '{' in ltype:
        ltype = 'null'
    elif '}' in ltype:
        ltype = 'null'
    elif 'void*' in ltype:
        ltype = 'null'

    return 'rnd_' + ltype.strip().replace('`', '').replace(' ', '').split('<')[-1].split('>')[0].split('(')[0].split('[')[0].split('*')[0] + '()'

def gen_comment_header(f):
    comment_h = "// " + f + " //"
    comment_l = "/" * len(comment_h)
    s = ""
    s += "  " + comment_l + "\n"
    s += " "  + comment_h + "\n"
    s += ""   + comment_l + "\n"
    s += "\n"
    return s

def translate_to_def(ptype):
    if ptype == None:
        return 'nil'
    if 'Lua Function' in ptype:
        return 'function'
    return ptype.replace('enum ', '').replace('const ', '').replace(' ', '').replace('`', '').replace('<', '_').replace('>', '')