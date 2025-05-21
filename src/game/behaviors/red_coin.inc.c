/**
 * This file contains the initialization and behavior for red coins.
 * Behavior controls audio and the orange number spawned, as well as interacting with
 * the course's red coin star.
 */

/**
 * Red coin's hitbox details.
 */
static struct ObjectHitbox sRedCoinHitbox = {
    .interactType = INTERACT_COIN,
    .downOffset = 0,
    .damageOrCoinValue = 2,
    .health = 0,
    .numLootCoins = 0,
    .radius = 100,
    .height = 64,
    .hurtboxRadius = 0,
    .hurtboxHeight = 0,
};

/**
 * Red coin initialization function. Sets the coin's hitbox and parent object.
 */
void bhv_red_coin_init(void) {
    // Set the red coins to have a parent of the closest red coin star.
    struct Object *hiddenRedCoinStar = cur_obj_nearest_object_with_behavior(bhvHiddenRedCoinStar);
    // If it's not a typical red coin star, it's a Bowser one.
    if (hiddenRedCoinStar == NULL) {
        hiddenRedCoinStar = cur_obj_nearest_object_with_behavior(bhvBowserCourseRedCoinStar);
    }
    
    // If we found a red coin star, It's our parent.
    if (hiddenRedCoinStar != NULL) {
        o->parentObj = hiddenRedCoinStar;
    } else {
        o->parentObj = NULL;
    }

    obj_set_hitbox(o, &sRedCoinHitbox);
}

/**
 * Main behavior for red coins. Primarily controls coin collection noise and spawning
 * the orange number counter.
 */
void bhv_red_coin_loop(void) {
    // If Mario interacted with the object...
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        // ...and there is a red coin star in the level...
        if (o->parentObj != NULL) {
            s16 redCoins = count_objects_with_behavior(bhvRedCoin) - 1;
            if (gCurrentArea) {
                o->parentObj->oHiddenStarTriggerCounter = gCurrentArea->numRedCoins - redCoins;
            }
            
            // Set the last person who interacted with a red coin to the 
            // parent so only they get the star cutscene.
            struct MarioState *player = nearest_mario_state_to_object(o);
            if (player) {
                o->parentObj->oHiddenStarLastInteractedObject = player;
            }

            // For JP version, play an identical sound for all coins.
#ifdef VERSION_JP
            create_sound_spawner(SOUND_GENERAL_RED_COIN);
#endif
            // Spawn the orange number counter
            spawn_orange_number(o->parentObj->oHiddenStarTriggerCounter, 0, 0, 0);

            // On all versions but the JP version, each coin collected plays a higher noise.
#ifndef VERSION_JP
            if (redCoins < 8) {
                play_sound(SOUND_MENU_COLLECT_RED_COIN + ((7 - redCoins) << 16), gGlobalSoundSource);
            } else {
                play_sound(SOUND_MENU_COLLECT_RED_COIN, gGlobalSoundSource);
            }
#endif
        }

        coin_collected();
        // Despawn the coin.
        o->oInteractStatus = 0;
    }
}
