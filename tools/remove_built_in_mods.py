import os
import sys

if not os.path.exists("build/us_pc/mods"):
    sys.exit(0)

built_in_mods = []

for mod in os.listdir("mods"):
    if os.path.isdir(mod) or (os.path.isfile(mod) and mod.endswith(".lua")):
        built_in_mods.append(mod)

for mod in os.listdir("build/us_pc/mods"):
    if mod in built_in_mods:
        os.remove(mod)