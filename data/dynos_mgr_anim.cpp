#include "dynos.cpp.h"
extern "C" {
#include "object_fields.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
#include "pc/configfile.h"
#include "pc/lua/utils/smlua_anim_utils.h"
}

//
// Update animations
//

// Retrieve the current Mario's animation index
static s32 RetrieveCurrentMarioAnimationIndex(u32 aPlayerIndex) {
    static struct MarioAnimDmaRelatedThing *_MarioAnims = (struct MarioAnimDmaRelatedThing *) gMarioAnims;
    for (s32 i = 0; i != (s32) _MarioAnims->count; ++i) {
        void *_AnimAddr = gMarioAnims + _MarioAnims->anim[i].offset;
        if (_AnimAddr == gMarioStates[aPlayerIndex].animation->currentAnimAddr) {
            return i;
        }
    }
    return -1;
}

// Retrieve the current animation index
// As we don't know the length of the table, let's hope that we'll always find the animation...
static s32 RetrieveCurrentAnimationIndex(struct Object *aObject) {
    if (!aObject->oAnimations || !aObject->header.gfx.animInfo.curAnim || smlua_anim_util_get_current_animation_name(aObject)) {
        return -1;
    }
    struct AnimationTable* animations = aObject->oAnimations;
    for (s32 i = 0; i < animations->count; ++i) {
        if (animations->anims[i] == aObject->header.gfx.animInfo.curAnim) {
            return i;
        }
    }
    return -1;
}

// Must be called twice, before and after geo_set_animation_globals
void DynOS_Anim_Swap(void *aPtr) {
    if (!aPtr) { return; }

    static Animation *pDefaultAnimation = NULL;
    static Animation  sGfxDataAnimation;

    // Does the object have a model?
    struct Object *_Object = (struct Object *) aPtr;
    if (!_Object->header.gfx.sharedChild || !_Object->header.gfx.animInfo.curAnim) {
        return;
    }

    // Swap the current animation with the one from the Gfx data
    if (!pDefaultAnimation) {
        pDefaultAnimation = _Object->header.gfx.animInfo.curAnim;

        // ActorGfx data
        ActorGfx* _ActorGfx = DynOS_Actor_GetActorGfx(_Object->header.gfx.sharedChild);
        if (!_ActorGfx) {
            return;
        }

        // GfxData
        GfxData* _GfxData = _ActorGfx->mGfxData;
        if (!_GfxData) {
            return;
        }

        // Animation table
        if (_GfxData->mAnimationTable.Empty()) {
            return;
        }

        // Animation index
        s32 _AnimIndex = -1;
        for (u32 i = 0; i < MAX_PLAYERS; i++) {
            if (gMarioStates[i].marioObj == NULL) { continue; }
            if (_Object == gMarioStates[i].marioObj) {
                _AnimIndex = RetrieveCurrentMarioAnimationIndex(i);
                break;
            }
        }
        if (_AnimIndex == -1) {
            _AnimIndex = RetrieveCurrentAnimationIndex(_Object);
        }
        if (_AnimIndex == -1) {
            return;
        }
        if (_AnimIndex >= _GfxData->mAnimationTable.Count()) {
            return;
        }

        // Animation data
        const AnimData *_AnimData = (const AnimData *) _GfxData->mAnimationTable[_AnimIndex].second;
        if (_AnimData) {
            sGfxDataAnimation.flags = _AnimData->mFlags;
            sGfxDataAnimation.animYTransDivisor = _AnimData->mUnk02;
            sGfxDataAnimation.startFrame = _AnimData->mUnk04;
            sGfxDataAnimation.loopStart = _AnimData->mUnk06;
            sGfxDataAnimation.loopEnd = _AnimData->mUnk08;
            sGfxDataAnimation.unusedBoneCount = _AnimData->mUnk0A.second;
            sGfxDataAnimation.values = (u16*)_AnimData->mValues.second.begin();
            sGfxDataAnimation.index = (u16*)_AnimData->mIndex.second.begin();
            sGfxDataAnimation.valuesLength = _AnimData->mValues.second.Count();
            sGfxDataAnimation.indexLength = _AnimData->mIndex.second.Count();
            sGfxDataAnimation.length = _AnimData->mLength;
            _Object->header.gfx.animInfo.curAnim = &sGfxDataAnimation;
        }

    // Restore the default animation
    } else {
        _Object->header.gfx.animInfo.curAnim = pDefaultAnimation;
        pDefaultAnimation = NULL;
    }
}
