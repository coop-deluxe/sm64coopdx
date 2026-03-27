import os, configparser

LANG_DIR = "./lang/"

def pass_string(optionstr): return optionstr

def open_lang(name):
    parser = configparser.ConfigParser(interpolation=None)
    parser.optionxform = pass_string
    parser.read(LANG_DIR + name)
    return parser

DEF_NAME = "English.ini"
DEF_LANG = open_lang(DEF_NAME)

# Edit this dictionary when revising entries
verified_entries = {
    "Spanish.ini": {
        "MENU": ("NO"),
        "CONTROLS": ("CHAT", "X", "Y", "A", "B", "START", "L", "R", "Z"),
        "DISPLAY": ("MANUAL", "D0P5X", "D1X", "D1P5X", "D3X", "D10X", "D100X"),
        "DJUI_THEMES": ("FONT_NORMAL", "MARIO_THEME", "ODYSSEY_THEME"),
        "DYNOS": ("DYNOS"),
        "HOST_MESSAGE": ("INFO_TITLE"),
        "HOST_MODS": ("MODS"),
        "HOST_MOD_CATEGORIES": ("ROMHACKS", "CHARACTER_SELECT"),
        "HOST_SETTINGS": ("NORMAL"),
        "HOST": ("DISCORD", "COOPNET", "MODS"),
        "MENU_OPTIONS": ("MENU_TITLE"),
        "MODLIST": ("MODS"),
    }
}

for file in os.listdir(os.fsencode(LANG_DIR)):
    filename = os.fsdecode(file)
    if filename == DEF_NAME: continue

    lang = open_lang(filename)
    warned = False
    sections = []

    for section in DEF_LANG.sections():
        warnings = {
            "Name": section,
            "Untranslated": [],
            "Missing": [],
            "Extra": [],
        }

        if lang.has_section(section):
            entries = list(dict.fromkeys(lang.options(section) + DEF_LANG.options(section)))
            for entry in entries:
                if lang.has_option(section, entry):
                    if not DEF_LANG.has_option(section, entry):
                        warnings["Extra"].append(entry)
                        continue
                else:
                    warnings["Missing"].append(entry)
                    continue

                verified = verified_entries.get(filename)
                if verified is not None:
                    verified = verified.get(section)
                    if verified is not None:
                        verified = entry in verified

                if lang.get(section, entry) == DEF_LANG.get(section, entry) \
                    and not verified:
                    warnings["Untranslated"].append(entry)
        else: warnings["Missing"].append("Section")

        if len(warnings["Extra"] + warnings["Missing"] + warnings["Untranslated"]) > 0:
            sections.append(warnings)

    if len(sections) > 0:
        print(filename)
        for warnings in sections:
            print(f"  [{warnings.pop("Name")}]")

            for level, entries in warnings.items():
                if len(entries) > 0:
                    print(f"    {level}: " + ", ".join(entries))
        print()

    