import os
import re
import sys


DIRECTORIES = [
    "actors",
    "bin",
    "levels",
]

FILE_EXTENSIONS = [
    ".c",
    ".h",
]

CUSTOM_DEFINED = [
    "dl_billboard_num3_0",
    "dl_billboard_num3_1",
    "dl_billboard_num3_2",
    "dl_billboard_num3_3",
    "dl_billboard_num3_4",
    "dl_billboard_num3_5",
    "dl_billboard_num3_6",
    "dl_billboard_num3_7",
    "dl_billboard_num3_8",
    "dl_billboard_num3_9",
    "dl_billboard_num3_0x",
    "dl_billboard_num3_1x",
    "dl_billboard_num3_2x",
    "dl_billboard_num3_3x",
    "dl_billboard_num3_4x",
    "dl_billboard_num3_5x",
    "dl_billboard_num3_6x",
    "dl_billboard_num3_7x",
    "dl_billboard_num3_8x",
    "dl_billboard_num3_9x",
    "dl_billboard_num3_x0",
    "dl_billboard_num3_x1",
    "dl_billboard_num3_x2",
    "dl_billboard_num3_x3",
    "dl_billboard_num3_x4",
    "dl_billboard_num3_x5",
    "dl_billboard_num3_x6",
    "dl_billboard_num3_x7",
    "dl_billboard_num3_x8",
    "dl_billboard_num3_x9",
    "dl_billboard_num3_0xx",
    "dl_billboard_num3_1xx",
    "dl_billboard_num3_2xx",
    "dl_billboard_num3_3xx",
    "dl_billboard_num3_4xx",
    "dl_billboard_num3_5xx",
    "dl_billboard_num3_6xx",
    "dl_billboard_num3_7xx",
    "dl_billboard_num3_8xx",
    "dl_billboard_num3_9xx",
    "dl_billboard_num3_x0x",
    "dl_billboard_num3_x1x",
    "dl_billboard_num3_x2x",
    "dl_billboard_num3_x3x",
    "dl_billboard_num3_x4x",
    "dl_billboard_num3_x5x",
    "dl_billboard_num3_x6x",
    "dl_billboard_num3_x7x",
    "dl_billboard_num3_x8x",
    "dl_billboard_num3_x9x",
    "dl_billboard_num3_xx0",
    "dl_billboard_num3_xx1",
    "dl_billboard_num3_xx2",
    "dl_billboard_num3_xx3",
    "dl_billboard_num3_xx4",
    "dl_billboard_num3_xx5",
    "dl_billboard_num3_xx6",
    "dl_billboard_num3_xx7",
    "dl_billboard_num3_xx8",
    "dl_billboard_num3_xx9",
]


def main():
    verbose = len(sys.argv) > 1 and (sys.argv[1] == "-v" or sys.argv[1] == "--verbose")
    pattern = re.compile(r"[\W]+")
    display_lists = set()
    for dir in DIRECTORIES:
        for root, dirs, filenames in os.walk(dir):
            dirs.sort()
            filenames.sort()
            for filename in filenames:
                if filename[filename.rfind("."):] in FILE_EXTENSIONS:
                    display_lists_in_file = []
                    filepath = os.path.join(root, filename)
                    with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
                        lines = f.readlines()
                    ignore = False
                    for line in lines:
                        if ("#ifdef VERSION_EU" in line or
                            "#ifdef VERSION_SH" in line or
                            "#ifdef VERSION_JP" in line):
                            ignore = True
                        if "#endif" in line:
                            ignore = False
                        if not ignore and "Gfx" in line and "static " not in line and "extern" not in line and "#" not in line:
                            identifiers = pattern.sub(" ", line).split()
                            index_gfx = identifiers.index("Gfx")
                            name = identifiers[index_gfx + 1]
                            if name not in display_lists:
                                display_lists.add(name)
                                if verbose:
                                    display_lists_in_file.append(name)
                    if verbose and display_lists_in_file:
                        print("%s\n    %s" % (filepath, "\n    ".join(display_lists_in_file)))

    # Add these manually because they are defined by a macro
    display_lists.update(CUSTOM_DEFINED)

    with open("include/display_lists.inl", "w", encoding="utf-8", newline="\n") as f:
        for name in sorted(display_lists):
            f.write("DISPLAY_LIST(%s)\n" % (name))

    print("Total display lists: %d" % (len(display_lists)))


if __name__ == "__main__":
    main()
