import sys, os, zlib

build = sys.argv[1]
cache = 'sound/compressed/%s/%s%s/' % (sys.argv[2], sys.argv[4], sys.argv[6])

os.makedirs(cache, exist_ok=True)

for file in os.listdir(build):
    if os.path.isfile(build + file):
        with open(build + file, "rb") as f:
            data = zlib.compress(f.read(), level=9)
        with open(cache + file, "wb") as f:
            f.write(data)
