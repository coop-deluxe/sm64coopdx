#include "dynos.cpp.h"
extern "C" {
#include "object_fields.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
#include "pc/configfile.h"
#include "pc/lua/utils/smlua_anim_utils.h"
#include "behavior_data.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/mods/mod_fs.h"

s8 geo_get_processing_mario_index(struct Object *obj);
}

static std::vector<std::pair<std::string, DataNode<Animation>*>> &DynosAnimations() {
    static std::vector<std::pair<std::string, DataNode<Animation>*>> sDynosAnimations;
    return sDynosAnimations;
}

static std::vector<std::pair<std::string, DataNode<AnimationTable>*>> &DynosAnimationTables() {
    static std::vector<std::pair<std::string, DataNode<AnimationTable>*>> sDynosAnimationTables;
    return sDynosAnimationTables;
}

bool DynOS_Anim_Activate(const SysPath &aFilename, const char *aAnimationName) {
    auto &_DynosAnimations = DynosAnimations();

    // check for duplicates
    for (auto &animation : _DynosAnimations) {
        if (animation.first == aAnimationName) {
            return true;
        }
    }

    std::string animationName = aAnimationName;

    DataNode<AnimData> *_Node = DynOS_Anim_LoadFromBinary(aFilename, animationName.c_str());
    if (!_Node) { return false; }

    DataNode<Animation> *_Animation      = New<DataNode<Animation>>();
    _Animation->mData                    = New<Animation>();
    _Animation->mData->flags             = _Node->mData->mFlags;
    _Animation->mData->animYTransDivisor = _Node->mData->mAnimYTransDivisor;
    _Animation->mData->startFrame        = _Node->mData->mStartFrame;
    _Animation->mData->loopStart         = _Node->mData->mLoopStart;
    _Animation->mData->loopEnd           = _Node->mData->mLoopEnd;
    _Animation->mData->unusedBoneCount   = _Node->mData->mNumParts.second;
    _Animation->mData->values            = (u16 *)_Node->mData->mValues.second.begin();
    _Animation->mData->index             = (u16 *)_Node->mData->mIndex.second.begin();
    _Animation->mData->length            = _Node->mData->mLength;
    _Animation->mData->valuesLength      = _Node->mData->mValues.second.Count();
    _Animation->mData->indexLength       = _Node->mData->mIndex.second.Count();

    // Add to animations
    _DynosAnimations.emplace_back(animationName, _Animation);
    return true;
}

Animation *DynOS_Anim_Get(const char *animationName) {
    auto& _DynosAnimations = DynosAnimations();

    // mod animations
    for (auto &animation : _DynosAnimations) {
        if (animation.first == animationName) {
            return animation.second->mData;
        }
    }

    // check modfs file
    if (is_mod_fs_file(animationName)) {
        if (DynOS_Anim_Activate(animationName, animationName)) {
            return DynOS_Anim_Get(animationName);
        }
    }

    // check builtin animations
    const Animation *builtInAnim = DynOS_Builtin_Anim_GetFromName(animationName);
    if (!builtInAnim) {
        return NULL;
    }

    return (Animation *)builtInAnim;
}

bool DynOS_Anim_Table_Activate(const SysPath &aFilename, const char *aAnimationTableName) {
    auto &_DynosAnimationTables = DynosAnimationTables();

    // check for duplicates
    for (auto &animationTable : _DynosAnimationTables) {
        if (animationTable.first == aAnimationTableName) {
            return true;
        }
    }

    std::string animationTableName = aAnimationTableName;

    DataNode<AnimTableData> *_Node = DynOS_Anim_Table_LoadFromBinary(aFilename, animationTableName.c_str());
    if (!_Node) { return false; }
    auto &_CustomAnimations = DynosAnimations();

    s32 count = _Node->mData->mAnimations.Count();
    size_t tableSize = sizeof(AnimationTable) + (count * sizeof(const Animation *));
    
    DataNode<AnimationTable> *_AnimationTable = New<DataNode<AnimationTable>>();
    _AnimationTable->mData                    = (AnimationTable *)New<u8>(tableSize);
    _AnimationTable->mData->count             = count;

    const Animation **_Animations = (const Animation **)_AnimationTable->mData->anims;
    for (s32 i = 0; i < _Node->mData->mAnimations.Count(); i++) {
        _Animations[i] = DynOS_Anim_Get(_Node->mData->mAnimations[i].first.begin());
    }

    // Add to animation tables
    _DynosAnimationTables.emplace_back(animationTableName, _AnimationTable);
    return false;
}

AnimationTable *DynOS_Anim_Table_Get(const char *animationTableName) {
    auto& _DynosAnimationTables = DynosAnimationTables();

    // mod animation tables
    for (auto &animationTable : _DynosAnimationTables) {
        if (animationTable.first == animationTableName) {
            return animationTable.second->mData;
        }
    }

    // check modfs file
    if (is_mod_fs_file(animationTableName)) {
        if (DynOS_Anim_Table_Activate(animationTableName, animationTableName)) {
            return DynOS_Anim_Table_Get(animationTableName);
        }
    }

    // check builtin animation tables
    const AnimationTable *builtInAnimTable = DynOS_Builtin_Anim_Table_GetFromName(animationTableName);
    if (!builtInAnimTable) {
        return NULL;
    }

    return (AnimationTable *)builtInAnimTable;
}

void DynOS_Anim_ModShutdown() {
    auto& _DynosAnimations = DynosAnimations();
    auto& _DynosAnimationTables = DynosAnimationTables();
    for (auto &pair : _DynosAnimations) {
        DeleteNode(pair.second);
    }
    for (auto &pair : _DynosAnimationTables) {
        DeleteNode(pair.second);
    }
    _DynosAnimations.clear();
    _DynosAnimationTables.clear();
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
            frame->gfxDataAnim.flags             = _AnimData->mFlags;
            frame->gfxDataAnim.animYTransDivisor = _AnimData->mAnimYTransDivisor;
            frame->gfxDataAnim.startFrame        = _AnimData->mStartFrame;
            frame->gfxDataAnim.loopStart         = _AnimData->mLoopStart;
            frame->gfxDataAnim.loopEnd           = _AnimData->mLoopEnd;
            frame->gfxDataAnim.unusedBoneCount   = _AnimData->mNumParts.second;
            frame->gfxDataAnim.values            = (u16*) _AnimData->mValues.second.begin();
            frame->gfxDataAnim.index             = (u16*) _AnimData->mIndex.second.begin();
            frame->gfxDataAnim.valuesLength      = _AnimData->mValues.second.Count();
            frame->gfxDataAnim.indexLength       = _AnimData->mIndex.second.Count();
            frame->gfxDataAnim.length            = _AnimData->mLength;
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
