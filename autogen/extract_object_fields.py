import os
import re
import sys
from extract_constants import *

object_field_types = {
    'OBJECT_FIELD_U32': 'u32',
    'OBJECT_FIELD_S32': 's32',
    'OBJECT_FIELD_S16': 's16',
    'OBJECT_FIELD_F32': 'f32',
    'OBJECT_FIELD_S16P': 's16*',
    'OBJECT_FIELD_S32P': 's32*',
    'OBJECT_FIELD_ANIMS': 'struct Animation**',
    'OBJECT_FIELD_WAYPOINT': 'struct Waypoint*',
    'OBJECT_FIELD_CHAIN_SEGMENT': 'struct ChainSegment*',
    'OBJECT_FIELD_OBJ': 'struct Object*',
    'OBJECT_FIELD_SURFACE': 'struct Surface*',
    'OBJECT_FIELD_VPTR': 'void*',
    'OBJECT_FIELD_CVPTR': 'const void*',
}

def extract_object_fields():
    fields = []
    for line in extract_constants("include/object_fields.h").splitlines():
        parts = line.split(' ', 3)
        if len(parts) < 3: continue
        field_id = parts[1]
        val = parts[2]

        if not field_id.startswith('o'):
            #print('REJECT: ' + line)
            continue

        field_type = object_field_types[val.split('(')[0]]

        field = {}
        field['type'] = field_type.strip()
        field['identifier'] = field_id.strip()
        field['object_field'] = True
        field['field_str'] = line
        fields.append(field)
    return fields
