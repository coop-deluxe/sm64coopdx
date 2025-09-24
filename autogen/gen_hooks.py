import sys
import re
from vec_types import *


HOOK_RETURN_NEVER = "HOOK_RETURN_NEVER"
HOOK_RETURN_ON_SUCCESSFUL_CALL = "HOOK_RETURN_ON_SUCCESSFUL_CALL"
HOOK_RETURN_ON_OUTPUT_SET = "HOOK_RETURN_ON_OUTPUT_SET"


SMLUA_CALL_EVENT_HOOKS_BEGIN = """
bool smlua_call_event_hooks_{hook_type}({parameters}) {{
    lua_State *L = gLuaState;
    if (L == NULL) {{ return false; }}{define_hook_result}

    struct LuaHookedEvent *hook = &sHookedEvents[{hook_type}];
    for (int i = 0; i < hook->count; i++) {{{check_mod_index}
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);
"""

SMLUA_CALL_EVENT_HOOKS_DEFINE_HOOK_RESULT = """
    bool hookResult = false;"""

SMLUA_CALL_EVENT_HOOKS_SET_HOOK_RESULT = """
        hookResult = true;"""

SMLUA_CALL_EVENT_HOOKS_CALLBACK = """
        // call the callback
        if (0 != smlua_call_hook(L, {n_inputs}, {n_outputs}, 0, hook->mod[i], hook->modFile[i])) {{
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[{hook_type}]);
            continue;
        }}{set_hook_result}
"""

SMLUA_CALL_EVENT_HOOKS_RETURN_ON_OUTPUT_SET = """
            lua_settop(L, prevTop);
            return true;"""

SMLUA_CALL_EVENT_HOOKS_RETURN_ON_SUCCESSFUL_CALL = """
        return true;"""

SMLUA_CALL_EVENT_HOOKS_END = """
        lua_settop(L, prevTop);{return_on_successful_call}
    }}
    return {hook_result};
}}
"""

SMLUA_CALL_EVENT_HOOKS_MOD_INDEX_CHECK = """
        if (hook->mod[i]->index != modIndex) { continue; }"""

SMLUA_INTEGER_TYPES = {
"input": """
        // push {name}
        lua_pushinteger(L, {name});
""",
"output": """
        // return {name}
        if (lua_type(L, -{output_index}) == LUA_TNUMBER) {{
            *{name} = smlua_to_integer(L, -{output_index});{return_on_output_set}
        }}
"""
}

SMLUA_FLOAT_TYPES = {
"input": """
        // push {name}
        lua_pushnumber(L, {name});
""",
"output": """
        // return {name}
        if (lua_type(L, -{output_index}) == LUA_TNUMBER) {{
            *{name} = smlua_to_number(L, -{output_index});{return_on_output_set}
        }}
"""
}

SMLUA_TYPES = {
    **{
        type_name: {
"input": """
        // push {name}
        extern void smlua_new_%s(%s src);
        smlua_new_%s({name});
""" % (type_name.lower(), type_name, type_name.lower()),
"output": """
        // return {name}
        if (lua_type(L, -{output_index}) == LUA_TTABLE) {{
            extern void smlua_get_%s(%s dest, int index);
            smlua_get_%s(*{name}, -{output_index});{return_on_output_set}
        }}
""" % (type_name.lower(), type_name, type_name.lower())
        }
        for type_name in VEC_TYPES
    },
    "u8": SMLUA_INTEGER_TYPES,
    "u16": SMLUA_INTEGER_TYPES,
    "u32": SMLUA_INTEGER_TYPES,
    "u64": SMLUA_INTEGER_TYPES,
    "s8": SMLUA_INTEGER_TYPES,
    "s16": SMLUA_INTEGER_TYPES,
    "s32": SMLUA_INTEGER_TYPES,
    "s64": SMLUA_INTEGER_TYPES,
    "f32": SMLUA_FLOAT_TYPES,
    "f64": SMLUA_FLOAT_TYPES,
    "bool": {
"input": """
        // push {name}
        lua_pushboolean(L, {name});
""",
"output": """
        // return {name}
        if (lua_type(L, -{output_index}) == LUA_TBOOLEAN) {{
            *{name} = smlua_to_boolean(L, -{output_index});{return_on_output_set}
        }}
"""
    },
    "constchar*": {
"input": """
        // push {name}
        lua_pushstring(L, {name});
""",
"output": """
        // return {name}
        if (lua_type(L, -{output_index}) == LUA_TSTRING) {{
            *{name} = smlua_to_string(L, -{output_index});{return_on_output_set}
        }}
"""
    },
    "structMarioState*": {
"input": """
        // push {name}
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, {name}->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);
"""
    },
    "structWarpDest": {
"output": """
        // if the hook returns a table, use it to override the warp parameters
        if (lua_istable(L, -1)) {{

            lua_getfield(L, -1, "destLevel");
            if (lua_isnumber(L, -1)) {{
                {name}->levelNum = smlua_to_integer(L, -1);
            }}
            lua_pop(L, 1);

            lua_getfield(L, -1, "destArea");
            if (lua_isnumber(L, -1)) {{
                {name}->areaIdx = smlua_to_integer(L, -1);
            }}
            lua_pop(L, 1);

            lua_getfield(L, -1, "destWarpNode");
            if (lua_isnumber(L, -1)) {{
                {name}->nodeId = smlua_to_integer(L, -1);
            }}
            lua_pop(L, 1);
{return_on_output_set}
        }}
"""
    },
}

SMLUA_NAMES = {
    "valueIndex": {
        "input": """
        // push {name}
        lua_pushvalue(L, {name});
""",
        "output": ""
    },
    "modIndex": {
        "input": "",
        "output": ""
    },
}

def init():

    # HACK: build LOT types from smlua_cobject_autogen.c
    with open('src/pc/lua/smlua_cobject_autogen.c') as f:
        file = f.read()
        begin = file.find("const char *sLuaLotNames[] = {") + len("const char *sLuaLotNames[] = {")
        end = file.find("};", begin)
        types = [list(filter(None, re.split(r'\W+', line.strip()))) for line in file[begin:end].split('\n') if line.strip()]

    for lot, name in types:
        typename = f"struct{name}*"
        if typename not in SMLUA_TYPES:
            SMLUA_TYPES[typename] = {
"input": """
        // push {name}
        smlua_push_object(L, %s, {name}, NULL);
""" % (lot)
            }


def extract_hook_event(line: str):
    if line.startswith("//"):
        return None
    if not line.startswith("SMLUA_EVENT_HOOK"):
        return None

    tokens = [token.strip() for token in line.replace('(', ',').replace(')', ',').split(',') if token.strip()]
    if len(tokens) < 3:
        return None

    hook_event_type = tokens[1]
    if not hook_event_type.startswith("HOOK_"):
        return None

    hook_event_return = tokens[2]
    if not hook_event_return.startswith("HOOK_RETURN_"):
        return None

    parameters = ", ".join(token.replace("OUTPUT ", "") for token in tokens[3:])
    inputs = []
    outputs = []
    for token in tokens[3:]:
        param = [x.strip() for x in token.split() if x.strip()]
        if len(param) < 2:
            continue

        is_output = param[0] == "OUTPUT"
        if is_output:
            param = param[1:]
            if len(param) < 2:
                continue

        param_type = " ".join(param[:-1]) if param[0] != "enum" else "s32"
        param_name = param[-1]
        stars = param_name.count('*')
        param_name = param_name[stars:]
        param_type += "*" * stars
        param_type = "".join(param_type.split())

        if is_output:
            outputs.append({
                "type": param_type[:-1],
                "name": param_name
            })
        else:
            inputs.append({
                "type": param_type,
                "name": param_name
            })

    return {
        "type": hook_event_type,
        "return": hook_event_return,
        "parameters": parameters,
        "inputs": inputs,
        "outputs": outputs
    }


def main():
    verbose = len(sys.argv) > 1 and (sys.argv[1] == "-v" or sys.argv[1] == "--verbose")
    with open("src/pc/lua/smlua_hook_events.inl", "r") as f:
        lines = f.readlines()

    hook_events = []
    for line in lines:
        hook_event = extract_hook_event(line)
        if hook_event:
            if verbose:
                print(hook_event)
            hook_events.append(hook_event)

    generated = (
        "/* THIS FILE IS AUTO-GENERATED */\n" +
        "/*   DO NOT EDIT IT MANUALLY   */\n\n"
    )

    for hook_event in hook_events:
        hook_return = hook_event["return"]
        define_hook_result = SMLUA_CALL_EVENT_HOOKS_DEFINE_HOOK_RESULT if hook_return == HOOK_RETURN_NEVER else ""
        set_hook_result = SMLUA_CALL_EVENT_HOOKS_SET_HOOK_RESULT if hook_return == HOOK_RETURN_NEVER else ""
        return_on_successful_call = SMLUA_CALL_EVENT_HOOKS_RETURN_ON_SUCCESSFUL_CALL if hook_return == HOOK_RETURN_ON_SUCCESSFUL_CALL else ""
        return_on_output_set = SMLUA_CALL_EVENT_HOOKS_RETURN_ON_OUTPUT_SET if hook_return == HOOK_RETURN_ON_OUTPUT_SET else ""
        hook_result = "hookResult" if hook_return == HOOK_RETURN_NEVER else "false"

        mod_index_found = False
        for input in hook_event["inputs"]:
            if input["name"] == "modIndex":
                mod_index_found = True
                break

        generated += SMLUA_CALL_EVENT_HOOKS_BEGIN.format(
            hook_type=hook_event["type"],
            parameters=hook_event["parameters"],
            check_mod_index=SMLUA_CALL_EVENT_HOOKS_MOD_INDEX_CHECK if mod_index_found else "",
            define_hook_result=define_hook_result
        )

        for input in hook_event["inputs"]:
            if input["name"] in SMLUA_NAMES:
                generated += SMLUA_NAMES[input["name"]]["input"].format(
                    name=input["name"]
                )
                continue
            generated += SMLUA_TYPES[input["type"]]["input"].format(
                name=input["name"]
            )

        n_outputs = len(hook_event["outputs"])
        generated += SMLUA_CALL_EVENT_HOOKS_CALLBACK.format(
            n_inputs=len(hook_event["inputs"]) - mod_index_found,
            n_outputs=n_outputs,
            hook_type=hook_event["type"],
            set_hook_result=set_hook_result
        )

        # Note: relative indexes for return values are reversed in the Lua stack
        # -1 is the last value, -2 the penultimate, ... and -N the first
        for i, output in enumerate(hook_event["outputs"]):
            generated += SMLUA_TYPES[output["type"]]["output"].format(
                name=output["name"],
                output_index=n_outputs - i,
                return_on_output_set=return_on_output_set
            )

        generated += SMLUA_CALL_EVENT_HOOKS_END.format(
            return_on_successful_call=return_on_successful_call,
            hook_result=hook_result
        )

    with open("src/pc/lua/smlua_hook_events_autogen.inl", "w", encoding="utf-8", newline="\n") as f:
        f.write(generated)


if __name__ == "__main__":
    init()
    main()
