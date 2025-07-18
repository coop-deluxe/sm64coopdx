import os, sys, re


MOD_FS_MAGIC        = "MODFSSM64COOPDX"
MOD_FS_HEADER_SIZE  = 32
MOD_FS_EXTENSION    = ".modfs"
MOD_FS_VERSION      = 1
MOD_FS_MAX_SIZE     = 0x1000000
MOD_FS_MAX_FILES    = 0x100
MOD_FS_MAX_PATH     = 0x100


def usage():
    print("""
Directory to modfs:

    python dir2modfs.py <dirpath> [--set-public] [--set-file-public <files>...]

    Parameters:
        dirpath                         Path to directory to turn into a .modfs file

    Options:
        --set-public                    Set modfs file as public (readable by other mods)
        --set-file-public <files>       Set the provided files as public (readable by other mods)

modfs to directory:

    python dir2modfs.py <filepath> --extract

    Parameters:
        filepath                        Path to modfs file to extract files from
""")
    exit(0)


def is_binary_file(bytes: bytes):
    textchars = bytearray({0x07, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x1B} | set(range(0x20, 0x100)) - {0x7F})
    return bool(bytes.translate(None, textchars))


def get_files(dirpath: str, public_files: list):
    files = []
    for root, _, filenames in os.walk(dirpath):
        for filename in filenames:
            relpath = os.path.join(root, filename)
            filepath = relpath.removeprefix(dirpath).strip("/\\").replace('\\', '/')
            is_public = False
            for public_file in public_files:
                if re.match(public_file, relpath) or re.match(public_file, filepath):
                    is_public = True
                    break
            files.append({
                "relpath": relpath,
                "filepath": filepath,
                "is_public": is_public,
                "is_text": False,
                "data": None
            })
    return files


def convert(dirpath: str, set_public: bool, public_files: list):
    dirpath = dirpath.rstrip("/\\")
    files = sorted(get_files(dirpath, public_files), key=lambda file: file["filepath"])
    if len(files) > MOD_FS_MAX_FILES:
        raise Exception(f"Max number of files exceeded: {len(files)} (max is: {MOD_FS_MAX_FILES})")

    total_size = 0
    for file in files:
        filepath = file["filepath"]
        if len(filepath) >= MOD_FS_MAX_PATH:
            raise Exception(f"{filepath} - Exceeded filepath length: {len(filepath)} (max is: {MOD_FS_MAX_PATH-1})")
        
        with open(file["relpath"], "rb") as f:
            data = f.read()
            total_size += len(data)
            if total_size > MOD_FS_MAX_SIZE:
                raise Exception(f"{filepath} - Total size exceeded: {total_size} (max is: {MOD_FS_MAX_SIZE})")

        file["data"] = data
        file["is_text"] = not is_binary_file(data)

    # write file
    destpath = dirpath + MOD_FS_EXTENSION
    with open(destpath, "wb") as f:

        # magic + version
        f.write(MOD_FS_MAGIC.encode())
        f.write(MOD_FS_VERSION.to_bytes(1, byteorder="little", signed=False))

        # header
        f.write(len(files).to_bytes(2, byteorder="little", signed=False))
        f.write(set_public.to_bytes(1, byteorder="little", signed=False))

        # padding (empty space for future versions)
        padding = MOD_FS_HEADER_SIZE - f.tell()
        f.write(b'\0' * padding)

        # files
        for file in files:

            # filepath
            f.write(len(file["filepath"]).to_bytes(2, byteorder="little", signed=False))
            f.write(file["filepath"].encode())

            # data
            f.write(len(file["data"]).to_bytes(4, byteorder="little", signed=False))
            f.write(file["is_public"].to_bytes(1, byteorder="little", signed=False))
            f.write(file["is_text"].to_bytes(1, byteorder="little", signed=False))
            f.write(file["data"])

    # summary
    print("")
    print(f"Directory:     {dirpath}")
    print(f"Num files:     {len(files)}")
    print(f"Total size:    {total_size}")
    print(f"Is public:     {set_public}")

    filepaths_max = max(8, len(max([file["filepath"] for file in files], key=len)))
    sizes_max = max(4, len(max([str(len(file["data"])) for file in files], key=len)))
    print("")
    print(f"{'FILEPATH'.ljust(filepaths_max)}  {'SIZE'.rjust(sizes_max)}  {'TEXT'.rjust(5)}  {'PUBLIC'.rjust(6)}")
    print(f"{'--------'.ljust(filepaths_max)}  {'----'.rjust(sizes_max)}  {'----'.rjust(5)}  {'------'.rjust(6)}")
    for file in files:
        filepath = file["filepath"]
        size = str(len(file["data"]))
        is_text = str(file["is_text"])
        is_public = str(file["is_public"])
        print(f"{filepath.ljust(filepaths_max)}  {size.rjust(sizes_max)}  {is_text.rjust(5)}  {is_public.rjust(6)}")


def extract(filepath: str):
    if not filepath.endswith(MOD_FS_EXTENSION):
        raise Exception("Not a modfs file")

    with open(filepath, "rb") as f:

        # magic + version
        magic = f.read(len(MOD_FS_MAGIC)).decode()
        if magic != MOD_FS_MAGIC:
            raise Exception("Not a modfs file")
        version = int.from_bytes(f.read(1), byteorder="little", signed=False)
        if version != MOD_FS_VERSION:
            raise Exception("Version mismatch")

        # header
        num_files = int.from_bytes(f.read(2), byteorder="little", signed=False)
        is_public = bool.from_bytes(f.read(1), byteorder="little", signed=False)

        # padding (empty space for future versions)
        f.seek(MOD_FS_HEADER_SIZE, 0)

        # create directory
        dirpath = filepath.removesuffix(MOD_FS_EXTENSION)
        os.makedirs(dirpath, exist_ok=True)

        # files
        for _ in range(num_files):

            # filepath
            filepath_len = int.from_bytes(f.read(2), byteorder="little", signed=False)
            filepath = os.path.join(dirpath, f.read(filepath_len).decode())

            # data
            file_size = int.from_bytes(f.read(4), byteorder="little", signed=False)
            file_is_public = bool.from_bytes(f.read(1), byteorder="little", signed=False)
            file_is_text = bool.from_bytes(f.read(1), byteorder="little", signed=False)
            file_data = f.read(file_size)

            # write file
            os.makedirs(os.path.dirname(filepath), exist_ok=True)
            with open(filepath, "wb") as g:
                g.write(file_data)
            print(f"Extracted file of size {file_size} to: {filepath}")


def main(argc: int, argv: list):
    if argc < 2:
        usage()

    if "--extract" in argv:
        extract(argv[1])
    else:
        set_public = "--set-public" in argv
        set_file_public_index = argv.index("--set-file-public") if "--set-file-public" in argv else argc
        convert(argv[1], set_public, argv[set_file_public_index+1:])


if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
