import sys
import zlib

with open(sys.argv[1], "rb") as f:
    data = zlib.decompress(f.read())
with open(sys.argv[2], "wb") as f:
    f.write(data)
