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
        "CONTROLS": ("A", "B", "X", "Y", "Z", "L", "R", "CHAT", "START"),
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

    for section in DEF_LANG.sections():
        warnings = {
            "UNTRANSLATED": [],
            "MISSING": [],
            "EXTRA": [],
        }

        if lang.has_section(section):
            entries = list(dict.fromkeys(lang.options(section) + DEF_LANG.options(section)))
            for entry in entries:
                if lang.has_option(section, entry):
                    if not DEF_LANG.has_option(section, entry):
                        warnings["EXTRA"].append(entry)
                        continue
                else:
                    warnings["MISSING"].append(entry)
                    continue

                verified = verified_entries.get(filename)
                if verified is not None:
                    verified = verified.get(section)
                    if verified is not None:
                        verified = entry in verified

                if lang.get(section, entry) == DEF_LANG.get(section, entry) \
                    and not verified:
                    warnings["UNTRANSLATED"].append(entry)
        else: warnings["MISSING"].append("SECTION")

        if len(warnings["EXTRA"] + warnings["MISSING"] + warnings["UNTRANSLATED"]) > 0:
            if not warned: warned = True; print(filename+":")

            print(f"[{section}]")
            for level, entries in warnings.items():
                if len(entries) > 0:
                    print(level + ": " + ", ".join(entries))
            print()
    