## [:rewind: C Reference](../c.md)

# Enums

In C, enums are the best tool to map a type to a list of named constant values.<br>
[Autogen](./smlua.md#autogen) even recognizes enums and associate their values to their underlying type.

However, enums are usually used as indices or entries in look-up tables to map them to other values.<br>
Writing manually those tables can fragment the code and make it harder to maintain (for example, when adding a new entry, you would need to find where the enum is used and can easily miss a spot).

A solution is to define such tables in a separate `.inl` file, then include that file where it's needed. That way, you have only one file to maintain.

## `.inl` file

First, let's define the enum. We need an identifier we can use as a C preprocessor macro.<br>
The `GraphNodeType`s will serve as an example.

```c
// src/engine/graph_node_types.inl

GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_ROOT)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_ORTHO_PROJECTION)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_PERSPECTIVE)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_MASTER_LIST)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_START)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_LEVEL_OF_DETAIL)
...
```
First column is the constant name.

If needed, define explicitly the value of each:
```c
// src/engine/graph_node_types.inl

GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_ROOT,             0x001)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_ORTHO_PROJECTION, 0x002)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_PERSPECTIVE,      0x003 | GRAPH_NODE_TYPE_FUNCTIONAL)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_MASTER_LIST,      0x004)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_START,            0x00A)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_LEVEL_OF_DETAIL,  0x00B)
...
```
Second column becomes the constant value.

## Enum definition

Now, we have enough data to define the enum. We'll make the C preprocessor build the enum itself.

```c
// src/engine/graph_node.h

enum GraphNodeType {
#define GRAPH_NODE_TYPE(_name_, _value_, ...) _name_ = _value_,
#include "src/engine/graph_node_types.inl"
#undef GRAPH_NODE_TYPE
};
```

## Enum usage

From now on, we can start using the enum in all sorts of look-up tables.<br>
For example, a function that returns the size of a `GraphNode` struct from its type.

First, let's add the relevant data to the `.inl` file:
```c
// src/engine/graph_node_types.inl

GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_ROOT,             0x001,                              GraphNodeRoot)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_ORTHO_PROJECTION, 0x002,                              GraphNodeOrthoProjection)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_PERSPECTIVE,      0x003 | GRAPH_NODE_TYPE_FUNCTIONAL, GraphNodePerspective)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_MASTER_LIST,      0x004,                              GraphNodeMasterList)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_START,            0x00A,                              GraphNodeStart)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_LEVEL_OF_DETAIL,  0x00B,                              GraphNodeLevelOfDetail)
...
```
Third column holds the C type of the `GraphNode`.

Now, create the function using these:
```c
// src/engine/graph_node.c

u32 get_graph_node_type_size(s16 type) {
#define GRAPH_NODE_TYPE(_name_, _value_, _type_, ...) { if (type == _name_) { return (u32) sizeof(struct _type_); } }
#include "src/engine/graph_node_types.inl"
#undef GRAPH_NODE_TYPE
    return 0;
}
```

<br>

Another example is the function `cast_graph_node` in the Lua API, which builds and returns the correct `CObject` depending on the `GraphNode` type.

But for that, we need to map each type to its corresponding Lua Object Type:
```c
// src/engine/graph_node_types.inl

GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_ROOT,             0x001,                              GraphNodeRoot,            LOT_GRAPHNODEROOT)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_ORTHO_PROJECTION, 0x002,                              GraphNodeOrthoProjection, LOT_GRAPHNODEORTHOPROJECTION)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_PERSPECTIVE,      0x003 | GRAPH_NODE_TYPE_FUNCTIONAL, GraphNodePerspective,     LOT_GRAPHNODEPERSPECTIVE)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_MASTER_LIST,      0x004,                              GraphNodeMasterList,      LOT_GRAPHNODEMASTERLIST)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_START,            0x00A,                              GraphNodeStart,           LOT_GRAPHNODESTART)
GRAPH_NODE_TYPE(GRAPH_NODE_TYPE_LEVEL_OF_DETAIL,  0x00B,                              GraphNodeLevelOfDetail,   LOT_GRAPHNODELEVELOFDETAIL)
...
```
Fourth column gives the Lua Object Type.

And that's it! The mapping table now looks like this:
```c
// src/pc/lua/smlua_functions.c

typedef struct { s16 type; u16 lot; } GraphNodeLOT;
static GraphNodeLOT sGraphNodeTypeToLOT[] = {
#define GRAPH_NODE_TYPE(_name_, _value_, _type_, _lot_) { _name_, _lot_ },
#include "src/engine/graph_node_types.inl"
#undef GRAPH_NODE_TYPE
};
```

## Autogen

By default, autogen cannot parse enums defined in `.inl` files properly. But don't worry! This is just a matter of adding an entry in the `constants_enums_with_include` dict in `autogen/exposed_lists.py`:

```py
constants_enums_with_include = {
    "src/engine/graph_node.h": {        # Filepath
        "GraphNodeType": {              # Enum type
            "GRAPH_NODE_TYPE": [1,2],   # Enum identifier: [ index of name, index of value ]
        }
    },
}
```
