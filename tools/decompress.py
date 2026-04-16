import sys
import zlib

with open(sys.argv[1], "rb") as f:
    data = f.read()

try:
    data = zlib.decompress(data)
except zlib.error:
    pass

with open(sys.argv[2], "wb") as f:
    f.write(data)