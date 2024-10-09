#ifndef OBJECT_COLLISION_H
#define OBJECT_COLLISION_H

int detect_player_hitbox_overlap(struct MarioState* local, struct MarioState* remote, f32 scale);
void detect_object_collisions(void);

#endif // OBJECT_COLLISION_H
