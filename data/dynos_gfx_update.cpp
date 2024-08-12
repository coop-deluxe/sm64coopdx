#include "dynos.cpp.h"
extern "C" {
#include "object_fields.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
#include "pc/gfx/gfx_pc.h"
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
    if (!aObject->oAnimations || !aObject->header.gfx.curAnim.curAnim) {
        return -1;
    }
    for (s32 i = 0; aObject->oAnimations[i] != NULL; ++i) {
        if (aObject->oAnimations[i] == aObject->header.gfx.curAnim.curAnim) {
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
        pDefaultAnimation = _Object->header.gfx.curAnim.curAnim;

        // Actor index
        s32 _ActorIndex = DynOS_Geo_GetActorIndex(_Object->header.gfx.sharedChild->georef);
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
            sGfxDataAnimation.unk02 = _AnimData->mUnk02;
            sGfxDataAnimation.unk04 = _AnimData->mUnk04;
            sGfxDataAnimation.unk06 = _AnimData->mUnk06;
            sGfxDataAnimation.unk08 = _AnimData->mUnk08;
            sGfxDataAnimation.unk0A = _AnimData->mUnk0A.second;
            sGfxDataAnimation.values = _AnimData->mValues.second.begin();
            sGfxDataAnimation.index = _AnimData->mIndex.second.begin();
            sGfxDataAnimation.length = _AnimData->mLength;
            _Object->header.gfx.curAnim.curAnim = &sGfxDataAnimation;
        }

    // Restore the default animation
    } else {
        _Object->header.gfx.curAnim.curAnim = pDefaultAnimation;
        pDefaultAnimation = NULL;
    }
}

//
// Update models
//

void DynOS_Gfx_Update() {
    if (gObjectLists) {

        // Check packs
        Array<bool> _Enabled;
        const Array<PackData *> &pDynosPacks = DynOS_Gfx_GetPacks();
        for (s32 i = 0; i != pDynosPacks.Count(); ++i) {
            _Enabled.Add(DynOS_Opt_GetValue(String("dynos_pack_%d", i)));
        }
        
        // Loop through all object lists
        for (s32 list : { OBJ_LIST_PLAYER, OBJ_LIST_DESTRUCTIVE, OBJ_LIST_GENACTOR, OBJ_LIST_PUSHABLE, OBJ_LIST_LEVEL, OBJ_LIST_DEFAULT, OBJ_LIST_SURFACE, OBJ_LIST_POLELIKE, OBJ_LIST_UNIMPORTANT }) {
            struct Object *_Head = (struct Object *) &gObjectLists[list];
            for (struct Object *_Object = (struct Object *) _Head->header.next; _Object != _Head; _Object = (struct Object *) _Object->header.next) {
                if (_Object->header.gfx.sharedChild) {
                    
                    // Actor index
                    s32 _ActorIndex = DynOS_Geo_GetActorIndex(_Object->header.gfx.sharedChild->georef);
                    if (_ActorIndex != -1) {
                        
                        // Replace the object's model and animations
                        ActorGfx *_ActorGfx = &DynOS_Gfx_GetActorList()[_ActorIndex];
                        for (s32 i = 0; i != pDynosPacks.Count(); ++i) {

                            // If enabled and no pack is selected
                            // load the pack's model and replace the default actor's model
                            if (_Enabled[i] && _ActorGfx->mPackIndex == -1) {

                                // Load Gfx data from binary
                                GfxData *_GfxData = DynOS_Gfx_LoadFromBinary(pDynosPacks[i]->mPath, DynOS_Geo_GetActorName(_ActorIndex));
                                if (_GfxData) {
                                    _ActorGfx->mPackIndex = i;
                                    _ActorGfx->mGfxData   = _GfxData;
                                    _ActorGfx->mGraphNode = (GraphNode *) DynOS_Geo_GetGraphNode((*(_GfxData->mGeoLayouts.end() - 1))->mData, true);
                                    _ActorGfx->mGraphNode->georef = DynOS_Geo_GetActorLayout(_ActorIndex);
#ifdef GFX_ENABLE_GRAPH_NODE_MODS
                                    gfx_register_layout_graph_node((void *)(_ActorGfx->mGraphNode->georef), _ActorGfx->mGraphNode);
#endif
                                    break;
                                }
                            }

                            // If disabled and this pack is the one selected
                            // replace the actor's model by the default one
                            else if (!_Enabled[i] && _ActorGfx->mPackIndex == i) {
                                _ActorGfx->mPackIndex = -1;
                                _ActorGfx->mGfxData   = NULL;
                                _ActorGfx->mGraphNode = (GraphNode *) DynOS_Geo_GetGraphNode(DynOS_Geo_GetActorLayout(_ActorIndex), true);
#ifdef GFX_ENABLE_GRAPH_NODE_MODS
                                gfx_register_layout_graph_node((void *)(_ActorGfx->mGraphNode->georef), _ActorGfx->mGraphNode);
#endif
                            }
                        }

                        // Update object
                        _Object->header.gfx.sharedChild = _ActorGfx->mGraphNode;
                    }
                }
            }
        }
    }
}