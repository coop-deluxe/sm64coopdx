#ifndef GD_CONFIG_H
#define GD_CONFIG_H

/**
 * Goddard Engine Configuration
 * Adjust these values to support higher poly models
 */

// Maximum vertices and faces for shape loading (OBJ/3DG1 formats)
#define GD_CFG_MAX_SHAPE_VERTICES 100000
#define GD_CFG_MAX_SHAPE_FACES    100000

// Static display list allocation (gfx commands, vertices)
#define GD_CFG_STATIC_DL_GFX      50000
#define GD_CFG_STATIC_DL_VTX      100000

// Dynamic display list allocation (gfx commands, vertices)
#define GD_CFG_DYNAMIC_DL_GFX     50000
#define GD_CFG_DYNAMIC_DL_VTX     100000

// Triangle buffer size for vertex batching
#define GD_CFG_TRIANGLE_BUF_SIZE  200

// Vertex batch flush threshold
#define GD_CFG_VERTEX_BATCH_SIZE  30

#endif // GD_CONFIG_H
