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
    if ptype in usf_types:
        return 'LVT_' + ptype.upper()
    if ptype in vec3_types:
        return 'LVT_COBJECT'
    if ptype == 'float':
        return 'LVT_F32'
    if 'struct' in ptype:
        if '*' in ptype:
            return 'LVT_COBJECT_P'
        return 'LVT_COBJECT'
    return 'LVT_???'

def translate_type_to_lot(ptype):
    if '[' in ptype or '{' in ptype:
        return 'LOT_???'
    if ptype in usf_types:
        return 'LOT_NONE'
    if ptype in vec3_types:
        return 'LOT_' + ptype.upper()
    if ptype == 'float':
        return 'LOT_NONE'
    if 'struct' in ptype:
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
