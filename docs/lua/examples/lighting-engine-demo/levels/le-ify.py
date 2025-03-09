# This script is used for converting every vertex shaded material in a level to lighting engine

def fixModel(path):
    path += "/model.inc.c"
    contents = ""
    with open(path, "r") as f:
        contents = f.read()
    with open(path, "w") as f:
        contents = contents.replace("gsSPClearGeometryMode(G_LIGHTING),", "gsSPClearGeometryMode(G_LIGHTING),\n\tgsSPSetGeometryMode(G_LIGHTING_ENGINE_EXT),")
        contents = contents.replace("gsSPSetGeometryMode(G_LIGHTING),", "gsSPClearGeometryMode(G_LIGHTING_ENGINE_EXT),\n\tgsSPSetGeometryMode(G_LIGHTING),")
        f.write(contents)

fixModel("hl")