#include "dynos.cpp.h"
extern "C" {
#include "object_fields.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
#include "pc/configfile.h"
}

//
// Update animations
//

// Retrieve the current Mario's animation index
static s32 RetrieveCurrentMarioAnimationIndex() {
    struct MarioAnimDmaRelatedThing *_AnimDmaTable = gMarioState->animation->animDmaTable;
    for (s32 i = 0; i != (s32) _AnimDmaTable->count; ++i) {
        void *_AnimAddr = _AnimDmaTable->srcAddr + _AnimDmaTable->anim[i].offset;
        if (_AnimAddr == gMarioState->animation->currentAnimAddr) {
            return i;
        }
    }
    return -1;
}

// Retrieve the current animation index
// As we don't know the length of the table, let's hope that we'll always find the animation...
static s32 RetrieveCurrentAnimationIndex(struct Object *aObject) {
    if (!aObject->oAnimations || !aObject->header.gfx.animInfo.curAnim) {
        return -1;
    }
    for (s32 i = 0; aObject->oAnimations[i] != NULL; ++i) {
        if (aObject->oAnimations[i] == aObject->header.gfx.animInfo.curAnim) {
            return i;
        }
    }
    return -1;
}

// Must be called twice, before and after geo_set_animation_globals
void DynOS_Gfx_SwapAnimations(void *aPtr) {
    static Animation *pDefaultAnimation = NULL;
    static Animation  sGfxDataAnimation;

    // Does the object has a model?
    struct Object *_Object = (struct Object *) aPtr;
    if (!_Object->header.gfx.sharedChild) {
        return;
    }

    // Swap the current animation with the one from the Gfx data
    if (!pDefaultAnimation) {
        pDefaultAnimation = _Object->header.gfx.animInfo.curAnim;

        // Actor index
        s32 _ActorIndex = DynOS_Actor_GetIndex(_Object->header.gfx.sharedChild->georef);
        if (_ActorIndex == -1) {
            return;
        }

        // Gfx data
        GfxData *_GfxData = DynOS_Gfx_GetActorList()[_ActorIndex].mGfxData;
        if (!_GfxData) {
            return;
        }

        // Animation table
        if (_GfxData->mAnimationTable.Empty()) {
            return;
        }

        // Animation index
        s32 _AnimIndex = (_Object == gMarioObject ? RetrieveCurrentMarioAnimationIndex() : RetrieveCurrentAnimationIndex(_Object));
        if (_AnimIndex == -1) {
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
            sGfxDataAnimation.values = _AnimData->mValues.second.begin();
            sGfxDataAnimation.index = _AnimData->mIndex.second.begin();
            sGfxDataAnimation.length = _AnimData->mLength;
            _Object->header.gfx.animInfo.curAnim = &sGfxDataAnimation;
        }

    // Restore the default animation
    } else {
        _Object->header.gfx.animInfo.curAnim = pDefaultAnimation;
        pDefaultAnimation = NULL;
    }
}

//
// Update models
//

void DynOS_Gfx_Update() {
    if (!gObjectLists) { return; }

    // Check packs
    Array<bool> &_Enabled = DynOS_Gfx_GetPacksEnabled();
    const Array<PackData *> &pDynosPacks = DynOS_Gfx_GetPacks();
    while (_Enabled.Count() < pDynosPacks.Count()) {
        _Enabled.Add(true);
    }

    // Loop through all object lists
    for (s32 list : { OBJ_LIST_PLAYER, OBJ_LIST_DESTRUCTIVE, OBJ_LIST_GENACTOR, OBJ_LIST_PUSHABLE, OBJ_LIST_LEVEL, OBJ_LIST_DEFAULT, OBJ_LIST_SURFACE, OBJ_LIST_POLELIKE, OBJ_LIST_UNIMPORTANT }) {
        struct Object *_Head = (struct Object *) &gObjectLists[list];
        for (struct Object *_Object = (struct Object *) _Head->header.next; _Object != _Head; _Object = (struct Object *) _Object->header.next) {
            // Make sure it's non-null
            if (!_Object->header.gfx.sharedChild) { continue; }

            // Actor index
            s32 _ActorIndex = DynOS_Actor_GetIndex(_Object->header.gfx.sharedChild->georef);
            if (_ActorIndex == -1) { continue; }

            // Replace the object's model and animations
            ActorGfx *_ActorGfx = &DynOS_Gfx_GetActorList()[_ActorIndex];

            // Check for disabled downloaded models
            if (configDisableDownloadedModels && _ActorGfx->mPackIndex == 99) {
                extern const GeoLayout error_model_geo[];
                s32 actorIndex = DynOS_Actor_IsCustom(_ActorIndex) ? DynOS_Actor_GetIndex(error_model_geo) : _ActorIndex;
                const void* geoLayout = DynOS_Actor_GetLayoutFromIndex(actorIndex);
                _ActorGfx->mPackIndex = -1;
                _ActorGfx->mGfxData   = NULL;
                _ActorGfx->mGraphNode = (GraphNode *) DynOS_Geo_GetGraphNode(geoLayout, true);
            }

            for (s32 i = 0; i != pDynosPacks.Count(); ++i) {
                // If enabled and no pack is selected
                // load the pack's model and replace the default actor's model
                if (_Enabled[i] && _ActorGfx->mPackIndex == -1) {

                    // Load Gfx data from binary
                    SysPath _Filename = fstring("%s/%s.bin", pDynosPacks[i]->mPath.begin(), DynOS_Actor_GetName(_ActorIndex));
                    GfxData *_GfxData = DynOS_Actor_LoadFromBinary(pDynosPacks[i]->mPath, DynOS_Actor_GetName(_ActorIndex), _Filename);
                    if (_GfxData) {
                        _ActorGfx->mPackIndex = i;
                        _ActorGfx->mGfxData   = _GfxData;
                        _ActorGfx->mGraphNode = (GraphNode *) DynOS_Geo_GetGraphNode((*(_GfxData->mGeoLayouts.end() - 1))->mData, true);
                        _ActorGfx->mGraphNode->georef = DynOS_Actor_GetLayoutFromIndex(_ActorIndex);
                        DynOS_Tex_Valid(_GfxData);
                        break;
                    }
                }

                // If disabled and this pack is the one selected
                // replace the actor's model by the default one
                else if (!_Enabled[i] && _ActorGfx->mPackIndex == i) {
                    DynOS_Tex_Invalid(_ActorGfx->mGfxData);
                    _ActorGfx->mPackIndex = -1;
                    _ActorGfx->mGfxData   = NULL;
                    _ActorGfx->mGraphNode = (GraphNode *) DynOS_Geo_GetGraphNode(DynOS_Actor_GetLayoutFromIndex(_ActorIndex), true);
                }
            }

            // Update object
            _Object->header.gfx.sharedChild = _ActorGfx->mGraphNode;
        }
    }
}
