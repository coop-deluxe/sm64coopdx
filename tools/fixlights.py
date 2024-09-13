#!/usr/bin/python3

import sys, subprocess, re, shutil

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} [folder to search]")
    sys.exit()

lightFiles = set()
has_rg = shutil.which("rg") is not None

def make_search_cmd(regex, include = None):
    cmd = None
    if has_rg:
        cmd = f"rg -lF {regex}"
    else:
        cmd = f"grep -Rl {regex}"

    if include:
        if has_rg:
            cmd += f" -g {include}"
        else:
            cmd += f" --include {include}"

    return cmd

# The original command that was run across the entire repo to convert all assets
# cmds = ("grep -Rl \"gsSPSetLight\" levels actors bin","grep -Rl \"gsSPLight\" levels actors bin","grep -Rl \"Lights1\" levels actors bin")

# Operate on the folder passed as an argument to this program
cmds = [
    make_search_cmd(f"\"gsSPSetLight\" {sys.argv[1]}"),
    make_search_cmd(f"\"gsSPLight\" {sys.argv[1]}"),
    make_search_cmd(f"\"Lights1\" {sys.argv[1]}")
]

for cmd in cmds:
    try:
        output = subprocess.check_output(cmd, shell=True).decode('UTF-8').split("\n")[:-1]
        lightFiles = set.union(lightFiles,set(output))
    except subprocess.CalledProcessError:
        continue

lightStructs = {}
# FIRST PASS: COLLECT LIGHT STRUCT INFO, REMOVE LIGHT STRUCTS
for file in lightFiles:
    changed = False
    with open(file, "r", encoding='utf-8') as f:
        fileLines = f.readlines()
        index = 0

        while index < len(fileLines):
            curLine = fileLines[index].strip()

            if "const Lights1" in curLine and "gdSPDefLights1" in curLine:
                structName = curLine.split("const Lights1")[1].strip().split(" ")[0] # Get string between Lights 1 and following space
                del fileLines[index] # Remove beginning
                args = ""
                while not ")" in fileLines[index]:
                    args += fileLines[index].strip()
                    del fileLines[index]
                del fileLines[index] # Remove ending line
                args = args.strip(");")
                args = [int(arg.strip()[2:],16) for arg in args.split(",")]
                lightStructs[structName] = args
                changed = True
            elif "Lights1" in curLine and "gdSPDefLights1" in curLine:
                structName = curLine.split("Lights1")[1].strip().split(" ")[0] # Get string between Lights 1 and following space
                del fileLines[index] # Remove beginning
                args = ""
                while True:
                    args += fileLines[index].strip()
                    if ")" in fileLines[index]:
                        break
                    del fileLines[index]
                del fileLines[index] # Remove ending line
                args = args.strip(");")
                args = [int(arg.strip()[2:],16) for arg in args.split(",")]
                lightStructs[structName] = args
                changed = True

            index += 1
    # Don't write to the file if the contents haven't been changed, as this will trigger a rebuild by Make
    if changed:
        with open(file, "w") as f:
            f.writelines(fileLines)

# material diffs at lines for correcting fast64 tile scroll exports
material_deltas = {}
def index_delta(mat_name, orig_index, delta):
    if mat_name not in material_deltas:
        material_deltas[mat_name] = []

    material_deltas[mat_name].append((orig_index, delta,))

# SECOND PASS - CHANGE LIGHT COMMANDS
for file in lightFiles:
    changed = False
    with open(file, "r", encoding='utf-8') as f:
        fileLines = f.readlines()
        index = 0
        dl_index = -1
        while index < len(fileLines):
            curLine = fileLines[index].strip()
            dl_index += 1

            match_result = re.search(r"Gfx\s*([A-Za-z_]\w+)\s*\[\s*\w*\s*\]\s*=\s*\{", curLine)
            if match_result is not None and len(match_result.groups()) >= 1:
                curDL = match_result.group(1)
                dl_index = -1
                index += 1
                continue

            if curLine.startswith("gsSPSetLights1("):
                structName = curLine.split("(")[1].split(")")[0] # Get string between ( and )
                if structName in lightStructs.keys():
                    changed = True
                    args = lightStructs[structName]
                    light1Args = args[3]*0x1000000 + args[4]*0x10000 + args[5]*0x100 + 0xFF
                    light2Args = args[0]*0x1000000 + args[1]*0x10000 + args[2]*0x100 + 0xFF
                    fileLines[index] = "    gsSPLightColor(LIGHT_1, 0x%x),\n" % light1Args
                    fileLines.insert(index+1,"    gsSPLightColor(LIGHT_2, 0x%x),\n" % light2Args)
                    index_delta(curDL, dl_index, 1)
                    dl_index += 2 # gsSPSetLights1 expands to 3 commands, gsSPLightColor is 2 commands each
                    index += 1
                else:
                    print("Missing light definition %s in file %s. Skipping..." % (structName, file))

            elif curLine.startswith("gsSPLight("):
                if not "&" in curLine or not "." in curLine:
                    print("Malformed gsSPLight command in file %s, line %d. Skipping..." % (file, index+1))
                    index += 1
                    continue
                structName = curLine.split("&")[1].split(".")[0] # Get string between & and . (&lightname.l or &lightname.a)
                if structName in lightStructs.keys():
                    changed = True
                    args = lightStructs[structName]
                    lightNum = int(curLine.split(",")[1].strip()[0]) # , 1),
                    argIndex = (3 if lightNum == 1 else 0)
                    lightArgs = args[argIndex]*0x1000000 + args[argIndex+1]*0x10000 + args[argIndex+2]*0x100 + 0xFF
                    fileLines[index] = "    gsSPLightColor(LIGHT_%d, 0x%x),\n" % (lightNum, lightArgs)
                else:
                    print("Missing light definition %s in file %s, line %d. Skipping..." % (structName, file, index+1))

            index += 1
    # Don't write to the file if the contents haven't been changed, as this will trigger a rebuild by Make
    if changed:
        with open(file, "w") as f:
            f.writelines(fileLines)

def get_texscroll_files():
    mat_grep_commands = []
    for mat in material_deltas.keys():
        mat_grep_commands.append(make_search_cmd("\"segmented_to_virtual(" + re.escape(mat) + rf"\" {sys.argv[1]}", "\"*texscroll*\""))

    texscroll_files = set()
    for cmd in mat_grep_commands:
        try:
            output = subprocess.check_output(cmd, shell=True).decode('UTF-8').split("\n")[:-1]
            texscroll_files = set.union(texscroll_files,set(output))
        except subprocess.CalledProcessError:
            continue

    return texscroll_files

t_files = get_texscroll_files()
t_mats = set(material_deltas.keys())

# 3RD PASS: Update fast64 generated texscroll files
for file in t_files:
    changed = False
    with open(file, "r") as f:
        fileLines = f.readlines()
        in_func = False
        found_mat_match = False
        mat_match = None
        for index in range(len(fileLines)):
            curLineFull = fileLines[index]
            curLine = curLineFull.strip()

            if not in_func:
                match_result = re.search(r"void \w+\(\) \{", curLine)
                in_func = match_result is not None
                found_mat_match = False
                continue
            elif curLineFull.startswith("}"):
                in_func = False
                found_mat_match = False
                continue

            if not found_mat_match:
                match_result = re.search(r"Gfx \*mat = segmented_to_virtual\((\w*)\)", curLine)
                if not match_result:
                    continue

                seg_mat = match_result.group(1)
                if seg_mat in t_mats:
                    found_mat_match = True
                    mat_match = seg_mat
                continue

            match_result = re.search(r"shift_\w*\(mat, (\d*),", curLine)
            if match_result is not None and len(match_result.groups()) >= 1:
                sts_index_str = match_result.group(1)
                sts_index = int(sts_index_str)
                print(sts_index, curLine)
                new_sts_index = sts_index
                for orig_index, delta in material_deltas[mat_match]:
                    if orig_index > sts_index:
                        break
                    new_sts_index += delta
                fileLines[index] = curLineFull.replace(f"mat, {sts_index_str}, ", f"mat, {new_sts_index}, ")
                changed = True

    # Don't write to the file if the contents haven't been changed, as this will trigger a rebuild by Make
    if changed:
        with open(file, "w") as f:
            f.writelines(fileLines)
