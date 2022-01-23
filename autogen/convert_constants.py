import os

in_filename = os.path.dirname(os.path.realpath(__file__)) + "/lua_constants/constants.lua"
out_filename = os.path.dirname(os.path.realpath(__file__)) + '/../src/pc/lua/smlua_constants_autogen.c'

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
