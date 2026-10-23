import sys, os, zlib

build = sys.argv[1]
cache = 'sound/compressed/%s/%se%s/' % (sys.argv[2], sys.argv[4][0], sys.argv[6])

for file in os.listdir(cache):
    with open(cache + file, "rb") as f:
        data = zlib.decompress(f.read())
    with open(build + file, "wb") as f:
        f.write(data)
