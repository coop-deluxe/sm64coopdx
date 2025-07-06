#ifndef MIRROR_H
#define MIRROR_H

#include "types.h"

void bhv_mirror_init(void);

bool geo_is_mirror_object(struct Object *obj);
void geo_invert_culling(bool invert);
void geo_process_mirrors(struct Object *obj);
void geo_reset_mirrors();
f32 geo_process_shadow_apply_mirror_transform(struct GraphNodeObject *node, Vec3f outScale);

#endif // MIRROR_H
