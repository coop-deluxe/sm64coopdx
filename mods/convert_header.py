import re

rejects = ""
integer_types = ["u8", "u16", "u32", "u64", "s8", "s16", "s32", "s64", "int"]
number_types = ["f32", "float"]
cobject_types = ["struct MarioState*", "Vec3s", "Vec3f"]
cobject_lot_types = ["LOT_MARIO_STATE", "LOT_VEC3S", "LOT_VEC3F"]

do_extern = False
header_h = """
s32 check_common_idle_cancels(struct MarioState *m);
s32 check_common_hold_idle_cancels(struct MarioState *m);
s32 act_idle(struct MarioState *m);
void play_anim_sound(struct MarioState *m, u32 actionState, s32 animFrame, u32 sound);
s32 act_start_sleeping(struct MarioState *m);
s32 act_sleeping(struct MarioState *m);
s32 act_waking_up(struct MarioState *m);
s32 act_shivering(struct MarioState *m);
s32 act_coughing(struct MarioState *m);
s32 act_standing_against_wall(struct MarioState *m);
s32 act_in_quicksand(struct MarioState *m);
s32 act_crouching(struct MarioState *m);
s32 act_panting(struct MarioState *m);
void stopping_step(struct MarioState *m, s32 animID, u32 action);
s32 act_braking_stop(struct MarioState *m);
s32 act_butt_slide_stop(struct MarioState *m);
s32 act_hold_butt_slide_stop(struct MarioState *m);
s32 act_slide_kick_slide_stop(struct MarioState *m);
s32 act_start_crouching(struct MarioState *m);
s32 act_stop_crouching(struct MarioState *m);
s32 act_start_crawling(struct MarioState *m);
s32 act_stop_crawling(struct MarioState *m);
s32 act_shockwave_bounce(struct MarioState *m);
s32 landing_step(struct MarioState *m, s32 arg1, u32 action);
s32 check_common_landing_cancels(struct MarioState *m, u32 action);
s32 act_jump_land_stop(struct MarioState *m);
s32 act_double_jump_land_stop(struct MarioState *m);
s32 act_side_flip_land_stop(struct MarioState *m);
s32 act_freefall_land_stop(struct MarioState *m);
s32 act_triple_jump_land_stop(struct MarioState *m);
s32 act_backflip_land_stop(struct MarioState *m);
s32 act_lava_boost_land(struct MarioState *m);
s32 act_long_jump_land_stop(struct MarioState *m);
s32 act_hold_jump_land_stop(struct MarioState *m);
s32 act_hold_freefall_land_stop(struct MarioState *m);
s32 act_air_throw_land(struct MarioState *m);
s32 act_twirl_land(struct MarioState *m);
s32 act_ground_pound_land(struct MarioState *m);
s32 act_first_person(struct MarioState *m);
s32 check_common_stationary_cancels(struct MarioState *m);
s32 mario_execute_stationary_action(struct MarioState *m);
"""

functions = []

def reject_line(line):
    if len(line) == 0:
        return True
    if '(' not in line:
        return True
    if ')' not in line:
        return True
    if ';' not in line:
        return True

def normalize_type(t):
    t = t.strip()
    if ' ' in t:
        parts = t.split(' ', 1)
        t = parts[0] + ' ' + parts[1].replace(' ', '')
    return t

def process_line(line):
    function = {}

    line = line.strip()
    function['line'] = line

    line = line.replace('UNUSED', '')

    match = re.search('[a-zA-Z0-9_]+\(', line)
    function['type'] = normalize_type(line[0:match.span()[0]])
    function['identifier'] = match.group()[0:-1]

    function['params'] = []
    params_str = line.split('(', 1)[1].rsplit(')', 1)[0].strip()
    if len(params_str) == 0 or params_str == 'void':
        pass
    else:
        param_index = 0
        for param_str in params_str.split(','):
            param = {}
            param_str = param_str.strip()
            if param_str.endswith('*') or ' ' not in param_str:
                param['type'] = normalize_type(param_str)
                param['identifier'] = 'arg%d' % param_index
            else:
                match = re.search('[a-zA-Z0-9_]+$', param_str)
                param['type'] = normalize_type(param_str[0:match.span()[0]])
                param['identifier'] = match.group()
            function['params'].append(param)
            param_index += 1

    functions.append(function)

def process_lines():
    for line in header_h.splitlines():
        if reject_line(line):
            global rejects
            rejects += line + '\n'
            continue
        process_line(line)

def build_param(param, i):
    ptype = param['type']
    pid = param['identifier']

    if ptype in integer_types:
        return '    %s %s = smlua_to_integer(L, %d);\n' % (ptype, pid, i)
    elif ptype in number_types:
        return '    %s %s = smlua_to_number(L, %d);\n' % (ptype, pid, i)
    elif ptype in cobject_types:
        index = cobject_types.index(ptype)
        return '    %s %s = (%s)smlua_to_cobject(L, %d, %s);\n' % (ptype, pid, ptype, i, cobject_lot_types[index])
    else:
        return '    ' + ptype + ' ' + pid + ' <--- UNIMPLEMENTED' + '\n'

def build_return(function):
    ftype = function['type']
    fid = function['identifier']

    ccall = '%s(%s)' % (fid, ', '.join([x['identifier'] for x in function['params']]))

    if ftype == 'void':
        return '    %s;\n' % ccall

    lfunc = 'UNIMPLEMENTED -->'
    if ftype in integer_types:
        lfunc = 'lua_pushinteger'
    elif ftype in number_types:
        lfunc = 'lua_pushnumber'

    return '    %s(L, %s);\n' % (lfunc, ccall)

def build_function(function):
    s = 'int smlua_func_%s(lua_State* L) {\n' % function['identifier']

    i = 1
    for param in function['params']:
        s += build_param(param, i)
        s += '    if (!gSmLuaConvertSuccess) { return 0; }\n'
        i += 1
    s += '\n'

    if do_extern:
        s += '    extern %s\n' % function['line']

    s += build_return(function)
    s += '    return 1;\n}\n'

    function['implemented'] = not ('UNIMPLEMENTED' in s)
    if 'UNIMPLEMENTED' in s:
        s = "/*\n" + s + "*/\n"

    print(s)

def build_functions():
    for function in functions:
        build_function(function)

process_lines()
build_functions()
print('')
print('-------------------')
for function in functions:
    s = 'smlua_bind_function(L, "%s", smlua_func_%s);' % (function['identifier'], function['identifier'])
    if function['implemented']:
        print('    ' + s)
    else:
        print('    //' + s + ' <--- UNIMPLEMENTED')
print('-------------------')
print('REJECTS:')
print(rejects)