import re

rejects = ""
integer_types = ["u8", "u16", "u32", "u64", "s8", "s16", "s32", "s64", "int"]
number_types = ["f32", "float"]
cobject_types = ["struct MarioState*", "Vec3s", "Vec3f"]
cobject_lot_types = ["LOT_MARIO_STATE", "LOT_VEC3S", "LOT_VEC3F"]

header_h = """
s32 is_anim_at_end(struct MarioState *m);
s32 is_anim_past_end(struct MarioState *m);
s16 set_mario_animation(struct MarioState *m, s32 targetAnimID);
s16 set_mario_anim_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel);
void set_anim_to_frame(struct MarioState *m, s16 animFrame);
s32 is_anim_past_frame(struct MarioState *m, s16 animFrame);
s16 find_mario_anim_flags_and_translation(struct Object *o, s32 yaw, Vec3s translation);
void update_mario_pos_for_anim(struct MarioState *m);
s16 return_mario_anim_y_translation(struct MarioState *m);
void play_sound_if_no_flag(struct MarioState *m, u32 soundBits, u32 flags);
void play_mario_jump_sound(struct MarioState *m);
void adjust_sound_for_speed(struct MarioState *m);
void play_sound_and_spawn_particles(struct MarioState *m, u32 soundBits, u32 waveParticleType);
void play_mario_action_sound(struct MarioState *m, u32 soundBits, u32 waveParticleType);
void play_mario_landing_sound(struct MarioState *m, u32 soundBits);
void play_mario_landing_sound_once(struct MarioState *m, u32 soundBits);
void play_mario_heavy_landing_sound(struct MarioState *m, u32 soundBits);
void play_mario_heavy_landing_sound_once(struct MarioState *m, u32 soundBits);
void play_mario_sound(struct MarioState *m, s32 primarySoundBits, s32 scondarySoundBits);
void mario_set_bubbled(struct MarioState* m);
void mario_set_forward_vel(struct MarioState *m, f32 speed);
s32 mario_get_floor_class(struct MarioState *m);
u32 mario_get_terrain_sound_addend(struct MarioState *m);
struct Surface *resolve_and_return_wall_collisions(Vec3f pos, f32 offset, f32 radius);
f32 vec3f_find_ceil(Vec3f pos, f32 height, struct Surface **ceil);
s32 mario_facing_downhill(struct MarioState *m, s32 turnYaw);
u32 mario_floor_is_slippery(struct MarioState *m);
s32 mario_floor_is_slope(struct MarioState *m);
s32 mario_floor_is_steep(struct MarioState *m);
f32 find_floor_height_relative_polar(struct MarioState *m, s16 angleFromMario, f32 distFromMario);
s16 find_floor_slope(struct MarioState *m, s16 yawOffset);
void update_mario_sound_and_camera(struct MarioState *m);
void set_steep_jump_action(struct MarioState *m);
u32 set_mario_action(struct MarioState *m, u32 action, u32 actionArg);
s32 set_jump_from_landing(struct MarioState *m);
s32 set_jumping_action(struct MarioState *m, u32 action, u32 actionArg);
s32 drop_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg);
s32 hurt_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg, s16 hurtCounter);
s32 check_common_action_exits(struct MarioState *m);
s32 check_common_hold_action_exits(struct MarioState *m);
s32 transition_submerged_to_walking(struct MarioState *m);
s32 set_water_plunge_action(struct MarioState *m);
s32 execute_mario_action(UNUSED struct Object *o);
s32 force_idle_state(struct MarioState* m);
void init_mario(void);
void init_mario_from_save_file(void);
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
        for param_str in params_str.split(','):
            param = {}
            param_str = param_str.strip()
            match = re.search('[a-zA-Z0-9_]+$', param_str)
            param['type'] = normalize_type(param_str[0:match.span()[0]])
            param['identifier'] = match.group()
            function['params'].append(param)

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