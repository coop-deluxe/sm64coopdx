#include <PR/ultratypes.h>

#include "sm64.h"
#include "debug.h"
#include "interaction.h"
#include "mario.h"
#include "object_list_processor.h"
#include "spawn_object.h"
#include "pc/network/network_player.h"

struct Object *debug_print_obj_collision(struct Object *a) {
    if (!a) { return NULL; }
    struct Object *sp24;

    for (s32 i = 0; i < a->numCollidedObjs; i++) {
        print_debug_top_down_objectinfo("ON", 0);
        sp24 = a->collidedObjs[i];
        if (sp24 != gMarioObject) {
            return sp24;
        }
    }
    return NULL;
}

int detect_player_hitbox_overlap(struct MarioState* local, struct MarioState* remote, f32 scale) {
    if (!local || !remote) { return FALSE; }
    if (local->marioObj == NULL || local->marioObj->oIntangibleTimer != 0) { return FALSE; }
    if (remote->marioObj == NULL || remote->marioObj->oIntangibleTimer != 0) { return FALSE; }
    if (local->marioBodyState->mirrorMario) { return FALSE; }
    if (remote->marioBodyState->mirrorMario) { return FALSE; }

    struct Object* a = local->marioObj;
    f32* aTorso = local->marioBodyState->torsoPos;

    struct Object* b = remote->marioObj;
    f32* bTorso = remote->marioBodyState->torsoPos;

    f32 sp3C = aTorso[1] - a->hitboxDownOffset;
    f32 sp38 = bTorso[1] - b->hitboxDownOffset;
    f32 dx = aTorso[0] - bTorso[0];
    f32 dz = aTorso[2] - bTorso[2];
    f32 collisionRadius = (a->hitboxRadius + b->hitboxRadius) * 1.75f; // slightly increased from 1.5f for the sake of it
    f32 distance = sqrtf(dx * dx + dz * dz);

    if (collisionRadius * scale > distance) {
        f32 sp20 = a->hitboxHeight + sp3C;
        f32 sp1C = b->hitboxHeight + sp38;

        if (sp3C > sp1C) {
            return FALSE;
        }
        if (sp20 < sp38) {
            return FALSE;
        }
        if (a->numCollidedObjs >= 4) {
            return FALSE;
        }
        if (b->numCollidedObjs >= 4) {
            return FALSE;
        }

        return TRUE;
    }

    return FALSE;
}

s32 detect_object_hitbox_overlap(struct Object *a, struct Object *b) {
    if (!a || !b) { return 0; }
    f32 sp3C = a->oPosY - a->hitboxDownOffset;
    f32 sp38 = b->oPosY - b->hitboxDownOffset;
    f32 dx = a->oPosX - b->oPosX;
    f32 dz = a->oPosZ - b->oPosZ;
    f32 collisionRadius = a->hitboxRadius + b->hitboxRadius;
    f32 distance = sqrtf(dx * dx + dz * dz);

    // do not check for player interactions here
    if ((a->oInteractType & INTERACT_PLAYER) && (b->oInteractType & INTERACT_PLAYER)) {
        return 0;
    }

    if (collisionRadius > distance) {
        f32 sp20 = a->hitboxHeight + sp3C;
        f32 sp1C = b->hitboxHeight + sp38;

        if (sp3C > sp1C) {
            return 0;
        }
        if (sp20 < sp38) {
            return 0;
        }
        if (a->numCollidedObjs >= 4) {
            return 0;
        }
        if (b->numCollidedObjs >= 4) {
            return 0;
        }
        a->collidedObjs[a->numCollidedObjs] = b;
        b->collidedObjs[b->numCollidedObjs] = a;
        a->collidedObjInteractTypes |= b->oInteractType;
        b->collidedObjInteractTypes |= a->oInteractType;
        a->numCollidedObjs++;
        b->numCollidedObjs++;
        return 1;
    }

    return 0;
}

s32 detect_object_hurtbox_overlap(struct Object *a, struct Object *b) {
    if (!a || !b) { return 0; }

    f32 sp3C = a->oPosY - a->hitboxDownOffset;
    f32 sp38 = b->oPosY - b->hitboxDownOffset;
    f32 sp34 = a->oPosX - b->oPosX;
    f32 sp2C = a->oPosZ - b->oPosZ;
    f32 sp28 = a->hurtboxRadius + b->hurtboxRadius;
    f32 sp24 = sqrtf(sp34 * sp34 + sp2C * sp2C);

    if ((a->oInteractType & INTERACT_PLAYER) && a->oBehParams == 1) {
        b->oInteractionSubtype |= INT_SUBTYPE_DELAY_INVINCIBILITY;
    }

    if (sp28 > sp24) {
        f32 sp20 = a->hitboxHeight + sp3C;
        f32 sp1C = b->hurtboxHeight + sp38;

        if (sp3C > sp1C) {
            return 0;
        }
        if (sp20 < sp38) {
            return 0;
        }
        if ((a->oInteractType & INTERACT_PLAYER) && a->oBehParams == 1) {
            b->oInteractionSubtype &= ~INT_SUBTYPE_DELAY_INVINCIBILITY;
        }
        return 1;
    }

    return 0;
}

void clear_object_collision(struct Object *a) {
    if (!a) { return; }
    struct Object *sp4 = (struct Object *) a->header.next;

    while (sp4 && sp4 != a) {
        sp4->numCollidedObjs = 0;
        sp4->collidedObjInteractTypes = 0;
        if (sp4->oIntangibleTimer > 0) {
            sp4->oIntangibleTimer--;
        }
        if (sp4 == (struct Object *)sp4->header.next) { break; }
        sp4 = (struct Object *) sp4->header.next;
    }
}

void check_collision_in_list(struct Object *a, struct Object *b, struct Object *c) {
    if (!a) { return; }
    if (a->oIntangibleTimer == 0) {
        while (b && b != c) {
            if (b->oIntangibleTimer == 0) {
                if (detect_object_hitbox_overlap(a, b) && b->hurtboxRadius != 0.0f) {
                    detect_object_hurtbox_overlap(a, b);
                }
            }
            if (b == (struct Object *)b->header.next) { break; }
            b = (struct Object *) b->header.next;
        }
    }
}

void check_player_object_collision(void) {
    struct Object *sp1C = (struct Object *) &gObjectLists[OBJ_LIST_PLAYER];
    struct Object *sp18 = (struct Object *) sp1C->header.next;

    while (sp18 && sp18 != sp1C) {
        check_collision_in_list(sp18, (struct Object *) sp18->header.next, sp1C);
        check_collision_in_list(sp18, (struct Object *) gObjectLists[OBJ_LIST_POLELIKE].next,
                      (struct Object *) &gObjectLists[OBJ_LIST_POLELIKE]);
        check_collision_in_list(sp18, (struct Object *) gObjectLists[OBJ_LIST_LEVEL].next,
                      (struct Object *) &gObjectLists[OBJ_LIST_LEVEL]);
        check_collision_in_list(sp18, (struct Object *) gObjectLists[OBJ_LIST_GENACTOR].next,
                      (struct Object *) &gObjectLists[OBJ_LIST_GENACTOR]);
        check_collision_in_list(sp18, (struct Object *) gObjectLists[OBJ_LIST_PUSHABLE].next,
                      (struct Object *) &gObjectLists[OBJ_LIST_PUSHABLE]);
        check_collision_in_list(sp18, (struct Object *) gObjectLists[OBJ_LIST_SURFACE].next,
                      (struct Object *) &gObjectLists[OBJ_LIST_SURFACE]);
        check_collision_in_list(sp18, (struct Object *) gObjectLists[OBJ_LIST_DESTRUCTIVE].next,
                      (struct Object *) &gObjectLists[OBJ_LIST_DESTRUCTIVE]);
        sp18 = (struct Object *) sp18->header.next;
    }

    extern struct MarioState gMarioStates[];
    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        if (detect_player_hitbox_overlap(&gMarioStates[0], &gMarioStates[i], 1.0f)) {
            struct Object* a = gMarioStates[0].marioObj;
            struct Object* b = gMarioStates[i].marioObj;
            a->collidedObjs[a->numCollidedObjs] = b;
            b->collidedObjs[b->numCollidedObjs] = a;
            a->collidedObjInteractTypes |= b->oInteractType;
            b->collidedObjInteractTypes |= a->oInteractType;
            a->numCollidedObjs++;
            b->numCollidedObjs++;
        }
    }
}

void check_pushable_object_collision(void) {
    struct Object *sp1C = (struct Object *) &gObjectLists[OBJ_LIST_PUSHABLE];
    struct Object *sp18 = (struct Object *) sp1C->header.next;

    while (sp18 && sp18 != sp1C) {
        check_collision_in_list(sp18, (struct Object *) sp18->header.next, sp1C);
        if (sp18 == (struct Object *)sp18->header.next) { break; }
        sp18 = (struct Object *) sp18->header.next;
    }
}

void check_destructive_object_collision(void) {
    struct Object *sp1C = (struct Object *) &gObjectLists[OBJ_LIST_DESTRUCTIVE];
    struct Object *sp18 = (struct Object *) sp1C->header.next;

    while (sp18 && sp18 != sp1C) {
        if (sp18->oDistanceToMario < 2000.0f && !(sp18->activeFlags & ACTIVE_FLAG_UNK9)) {
            check_collision_in_list(sp18, (struct Object *) sp18->header.next, sp1C);
            check_collision_in_list(sp18, (struct Object *) gObjectLists[OBJ_LIST_GENACTOR].next,
                          (struct Object *) &gObjectLists[OBJ_LIST_GENACTOR]);
            check_collision_in_list(sp18, (struct Object *) gObjectLists[OBJ_LIST_PUSHABLE].next,
                          (struct Object *) &gObjectLists[OBJ_LIST_PUSHABLE]);
            check_collision_in_list(sp18, (struct Object *) gObjectLists[OBJ_LIST_SURFACE].next,
                          (struct Object *) &gObjectLists[OBJ_LIST_SURFACE]);
        }
        if (sp18 == (struct Object *)sp18->header.next) { break; }
        sp18 = (struct Object *) sp18->header.next;
    }
}

void detect_object_collisions(void) {
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_POLELIKE]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_PLAYER]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_PUSHABLE]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_GENACTOR]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_LEVEL]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_SURFACE]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_DESTRUCTIVE]);
    check_player_object_collision();
    check_destructive_object_collision();
    check_pushable_object_collision();
}
