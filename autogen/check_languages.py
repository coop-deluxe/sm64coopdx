import os, configparser

LANG_DIR = "./lang/"

def pass_string(optionstr): return optionstr

def open_lang(name):
    parser = configparser.ConfigParser(interpolation=None)
    parser.optionxform = pass_string
    parser.read(LANG_DIR + name, "utf-8")
    return parser

DEF_NAME = "English.ini"
DEF_LANG = open_lang(DEF_NAME)

for file in os.listdir(os.fsencode(LANG_DIR)):
    filename = os.fsdecode(file)
    if filename == DEF_NAME: continue

    lang = open_lang(filename)
    sections = {}

    for section in DEF_LANG.sections():
        warnings = { "Missing": [], "Extra:": [] }

        if lang.has_section(section):
            entries = list(dict.fromkeys(lang.options(section) + DEF_LANG.options(section)))
            for entry in entries:
                if lang.has_option(section, entry):
                    if not DEF_LANG.has_option(section, entry):
                        warnings["Extra:"].append(entry)
                else:
                    warnings["Missing"].append(entry)

        else: warnings["Missing"].append("Section")

        if len(warnings["Extra:"] + warnings["Missing"]) > 0:
            sections[section] = warnings

    if len(sections) > 0:
        print(filename)
        for section, warnings in sections.items():
            print(f"  [{section}]", end="")

            s = " "
            for level, entries in warnings.items():
                if len(entries) > 0:
                    print(f"{s}{level} " + ", ".join(entries))
                    s = "    "
        print()

    