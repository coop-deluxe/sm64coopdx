import configparser
import os

english = configparser.ConfigParser()
english.read("lang/English.ini", encoding="utf-8")

# get the sections and keys from the English INI file
english_sections = [section.upper() for section in english.sections()]
english_keys = {
    section.upper(): [key.upper() for key in english.options(section)]
    for section in english_sections
}

# function to compare an INI file against the English INI file
def compare_ini_file(file_path):
    config = configparser.ConfigParser()
    config.read(file_path, encoding="utf-8")

    config_sections = [section.upper() for section in config.sections()]

    missing_sections = set(english_sections) - set(config_sections)
    extra_sections = set(config_sections) - set(english_sections)

    missing_keys = {}
    for section in english_sections:
        if section in config_sections:
            section_keys = [key.upper() for key in config.options(section)]
            missing_keys[section] = set(english_keys[section]) - set(section_keys)

    return missing_sections, extra_sections, missing_keys

# iterate through all INI files in the directory
for filename in os.listdir("lang"):
    if filename.endswith(".ini"):
        ini_file_path = os.path.join("lang", filename)
        if filename != "English.ini":
            missing_sections, extra_sections, missing_keys = compare_ini_file(ini_file_path)

            print(f"\nComparing {filename}:")
            if not missing_sections and not extra_sections and not any(missing_keys.values()):
                print(f"{filename} is matching to English.ini.")
            else:
                if missing_sections:
                    print(f"Missing sections: {', '.join(missing_sections)}")
                if extra_sections:
                    print(f"Extra sections: {', '.join(extra_sections)}")
                for section, keys in missing_keys.items():
                    if keys:
                        print(f"Missing keys in section '{section}': {', '.join(keys)}")