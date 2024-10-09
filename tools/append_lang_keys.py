import os
import sys

# I can't stand it anymore, editing like 9 different INI files and finding the right spot just to add 1 line and also translating them all at the same time too, I'm making a script for this!

def add_new_key(ini_path, section, search_key, new_key):
    new_value = input(f"{new_key} for {os.path.basename(ini_path)}: ")
    current_section = ""
    out = []

    with open(ini_path, "r", encoding="utf-8") as f:
        lines = f.readlines()
        added = False
        for line in lines:
            if line.startswith("["):
                current_section = line.replace("[", "").replace("]", "").replace("\n", "")
            elif line.startswith(search_key) and current_section == section and not added:
                added = True
                line += f'{new_key} = "{new_value}"\n'
            out.append(line)
    
    with open(ini_path, "w", encoding="utf-8") as f:
        f.writelines(out)

files = os.listdir("./lang/")
files.sort()
for file in files:
    if file.endswith(".ini"):
        add_new_key("./lang/" + file, sys.argv[1], sys.argv[2], sys.argv[3])