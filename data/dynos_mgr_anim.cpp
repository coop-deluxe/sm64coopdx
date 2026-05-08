#include "dynos.cpp.h"
extern "C" {
#include "object_fields.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
#include "pc/configfile.h"
#include "pc/lua/utils/smlua_anim_utils.h"
#include "behavior_data.h"
#include "pc/lua/smlua_hooks.h"

s8 geo_get_processing_mario_index(struct Object *obj);
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

    // Must support nested calls (held objects render inside other object render)
    // and interleaving objects without corrupting swap state.
    struct AnimSwapFrame {
        struct Object *obj;
        Animation *defaultAnim;
        Animation gfxDataAnim;
    };

    static AnimSwapFrame sAnimSwapFrames[32] = { 0 };
    static s32 sCurrAnimSwapIndex = 0;

    // Does the object have a model?
    struct Object *_Object = (struct Object *) aPtr;
    if (!_Object->header.gfx.sharedChild || !_Object->header.gfx.animInfo.curAnim) {
        return;
    }

    // Determine if this call is the "swap" phase or "restore" phase.
    // The engine calls DynOS_Anim_Swap twice around geo_set_animation_globals.
    const bool restoring = (sCurrAnimSwapIndex > 0 && sAnimSwapFrames[sCurrAnimSwapIndex - 1].obj == _Object);

    // Swap the current animation with the one from the Gfx data
    if (!restoring) {
        if (sCurrAnimSwapIndex >= (s32) ARRAY_COUNT(sAnimSwapFrames)) {
            return;
        }

        AnimSwapFrame *frame = &sAnimSwapFrames[sCurrAnimSwapIndex];
        frame->obj = _Object;
        frame->defaultAnim = _Object->header.gfx.animInfo.curAnim;
        sCurrAnimSwapIndex++;

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
        s8 index = geo_get_processing_mario_index(_Object);
        if (index != -1) {
            _AnimIndex = RetrieveCurrentMarioAnimationIndex(index);

            // Don't allow Mario animations to be treated as regular objects
            // because DynOS doesn't properly build an AnimationTable
            if (_AnimIndex == -1) {
                return;
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
            frame->gfxDataAnim.flags = _AnimData->mFlags;
            frame->gfxDataAnim.animYTransDivisor = _AnimData->mUnk02;
            frame->gfxDataAnim.startFrame = _AnimData->mUnk04;
            frame->gfxDataAnim.loopStart = _AnimData->mUnk06;
            frame->gfxDataAnim.loopEnd = _AnimData->mUnk08;
            frame->gfxDataAnim.unusedBoneCount = _AnimData->mUnk0A.second;
            frame->gfxDataAnim.values = (u16*) _AnimData->mValues.second.begin();
            frame->gfxDataAnim.index = (u16*) _AnimData->mIndex.second.begin();
            frame->gfxDataAnim.valuesLength = _AnimData->mValues.second.Count();
            frame->gfxDataAnim.indexLength = _AnimData->mIndex.second.Count();
            frame->gfxDataAnim.length = _AnimData->mLength;
            _Object->header.gfx.animInfo.curAnim = &frame->gfxDataAnim;
        }

    // Restore the default animation
    } else {
        sCurrAnimSwapIndex--;
        AnimSwapFrame *frame = &sAnimSwapFrames[sCurrAnimSwapIndex];
        _Object->header.gfx.animInfo.curAnim = frame->defaultAnim;
        frame->obj = NULL;
        frame->defaultAnim = NULL;
    }
}
