import os

usf_types = ['u8', 'u16', 'u32', 'u64', 's8', 's16', 's32', 's64', 'f32']
vec3_types = ['Vec3s', 'Vec3f']

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
    if ('char' in ptype and '[' in ptype):
        return 'LVT_STRING'
    if ptype == 'char*':
        return 'LVT_STRING_P'

    if '[' in ptype or '{' in ptype:
        return 'LOT_???'
    if 'enum ' in ptype:
        return 'LVT_S32'
    if ptype == 'bool':
        return 'LVT_BOOL'
    if ptype in usf_types:
        return 'LVT_' + ptype.upper()
    if ptype in vec3_types:
        return 'LVT_COBJECT'
    if ptype == 'float':
        return 'LVT_F32'
    if 'struct' in ptype:
        if ptype.count('*') > 1:
            return 'LVT_???'
        if '*' in ptype:
            return 'LVT_COBJECT_P'
        return 'LVT_COBJECT'

    return 'LVT_???'

def translate_type_to_lot(ptype):
    if ptype == 'const char*':
        return 'LOT_NONE'
    if ptype == 'char*' or ('char' in ptype and '[' in ptype):
        return 'LOT_NONE'

    if '[' in ptype or '{' in ptype:
        return 'LOT_???'
    if 'enum ' in ptype:
        return 'LOT_NONE'
    if ptype == 'bool':
        return 'LOT_NONE'
    if ptype in usf_types:
        return 'LOT_NONE'
    if ptype in vec3_types:
        return 'LOT_' + ptype.upper()
    if ptype == 'float':
        return 'LOT_NONE'
    if 'struct' in ptype:
        if ptype.count('*') > 1:
            return 'LVT_???'
        struct_id = ptype.split(' ')[1].replace('*', '')
        if struct_id in exclude_structs:
            return 'LOT_???'
        return 'LOT_' + struct_id.upper()

    return 'LOT_???'

def gen_comment_header(f):
    comment_h = "// " + f + " //"
    comment_l = "/" * len(comment_h)
    s = ""
    s += "  " + comment_l + "\n"
    s += " "  + comment_h + "\n"
    s += ""   + comment_l + "\n"
    s += "\n"
    return s

def translate_type_to_lua(ptype):
    if ptype.startswith('struct '):
        return ptype.split(' ')[1].replace('*', ''), True

    if ptype == 'const char*':
        return 'string', False

    if ptype == 'char*' or ('char' in ptype and '[' in ptype):
        return 'string', False

    if 'Vec3' in ptype:
        return ptype, True

    if ptype.startswith('enum '):
        return 'integer', False

    if ptype in usf_types:
        if ptype.startswith('f'):
            return 'number', False
        else:
            return 'integer', False

    if 'void' == ptype:
        return None, False

    return ptype, False
