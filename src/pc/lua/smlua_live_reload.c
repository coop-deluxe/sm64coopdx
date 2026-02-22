#include <stdbool.h>
#include "smlua.h"
#include "smlua_require.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"

#define LIVE_RELOAD_TICK_COUNT 15

typedef struct UpvalRecord {
    char *funcKeyStr;   // the table key under which the function lived
    int funcKeyRef;     // registry ref for the key
    char *name;         // the upvalue's name
    int   ref;          // registry reference to the upvalue's value
    const void *id;     // the opaque upvalue‐cell pointer
    int type;           // the Lua type code of that value (LUA_T*)
    struct UpvalRecord *next;
} UpvalRecord;

typedef struct UpvalReference {
    char *name;
    int reference;
    bool active;
    bool isOld;
    struct UpvalReference *next;
} UpvalReference;

static UpvalReference *sUpvalReferences = NULL;

static void upval_references_free(lua_State *L) {
    UpvalReference *ref = sUpvalReferences;
    while (ref) {
        UpvalReference *next = ref->next;

        if (ref->name) {
            free(ref->name);
        }

        if (!ref->active) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref->reference);
        }

        free(ref);
        ref = next;
    }
    sUpvalReferences = NULL;
}

static int upval_references_deduplicate(lua_State *L, char* name, int reference, bool isOld) {
    // push the candidate function onto the stack
    lua_rawgeti(L, LUA_REGISTRYINDEX, reference);  // stack: ..., newFunc
    int newIdx = lua_gettop(L);

    // iterate existing refs, compare each stored function
    for (UpvalReference *ref = sUpvalReferences; ref; ref = ref->next) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref->reference); // stack: ..., newFunc, existFunc
        int existIdx = lua_gettop(L);

        // raw-equal tests pointer identity for tables/functions
        if (lua_rawequal(L, newIdx, existIdx)) {
            lua_pop(L, 2); // pop existFunc and newFunc
            luaL_unref(L, LUA_REGISTRYINDEX, reference);
            return ref->reference;
        }

        lua_pop(L, 1); // pop only existFunc, leave newFunc for next iteration
    }

    lua_pop(L, 1); // pop newFunc

    // allocate
    UpvalReference *ref = malloc(sizeof(struct UpvalReference));
    ref->name      = name ? strdup(name) : NULL;
    ref->reference = reference;
    ref->active    = false;
    ref->isOld     = isOld;
    ref->next      = sUpvalReferences;
    sUpvalReferences = ref;

    return reference;
}

static void upval_references_mark_active(int reference) {
    for (UpvalReference *ref = sUpvalReferences; ref; ref = ref->next) {
        if (ref->reference == reference) {
            ref->active = true;
        }
    }
}

static void upvalues_free(lua_State *L, UpvalRecord *upvalsHead) {
    UpvalRecord *cur = upvalsHead;
    while (cur) {
        UpvalRecord *next = cur->next;

        // free the string
        if (cur->funcKeyStr) {
            free(cur->funcKeyStr);
        }

        // unref the upvalue's value
        luaL_unref(L, LUA_REGISTRYINDEX, cur->ref);

        // free the upvalue name
        free(cur->name);

        // finally free the record itself
        free(cur);

        cur = next;
    }
}

static void upvalues_collect_from_function(lua_State *L, UpvalRecord **upvalsHead, bool isOld) {
    LUA_STACK_CHECK_BEGIN(L);

    // stack: ..., key, val
    if (lua_type(L, -1) != LUA_TFUNCTION) {
        return;
    }

    // read key string
    static char sFuncKeyStr[128] = "";
    const char *kstr = lua_tostring(L, -2);
    if (kstr) {
        snprintf(sFuncKeyStr, 128, "%s", kstr);
    }
    // read key ref
    lua_pushvalue(L, -1);  // duplicate the function closure (val)
    // stack: ..., key, val, val_copy

    int refRegistered = luaL_ref(L, LUA_REGISTRYINDEX);
    // luaL_ref pops the copy, leaving the original 'val' in place
    // stack: ..., key, val

    int funcKeyRef = upval_references_deduplicate(L, sFuncKeyStr, refRegistered, isOld);

    int fnIdx = lua_gettop(L); // the stack index of the reference to the function we're processing

    // walk its upvalues
    for (int uv = 1;; uv++) {
        const char *uvName = lua_getupvalue(L, fnIdx, uv);
        if (!uvName) { break; }

        // get the upvalue‐cell identifier
        const void *upvalId = lua_upvalueid(L, fnIdx, uv);

        // get its type
        int uvType = lua_type(L, -1);

        // now on top of the stack is the upvalue's 'value'
        // we pin it in the registry
        lua_pushvalue(L, -1);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        // pop the original
        lua_pop(L, 1);

        // allocate a new record
        UpvalRecord *rec = malloc(sizeof(struct UpvalRecord));
        rec->funcKeyStr  = kstr ? strdup(sFuncKeyStr) : NULL;
        rec->funcKeyRef  = funcKeyRef;
        rec->name        = strdup(uvName);
        rec->ref         = ref;
        rec->id          = upvalId;
        rec->type        = uvType;
        rec->next        = *upvalsHead;
        *upvalsHead = rec;
    }

    LUA_STACK_CHECK_END(L);
}

static void upvalues_collect(lua_State *L, UpvalRecord **upvalsHead, int moduleIdx, bool isOld) {
    LUA_STACK_CHECK_BEGIN(L);

    // make moduleIdx absolute so pushes don't shift it
    int absMod = lua_absindex(L, moduleIdx);

    // iterate module metatable
    if (lua_getmetatable(L, absMod)) {
        lua_pushnil(L);  // first key
        while (lua_next(L, -2) != 0) {
            upvalues_collect_from_function(L, upvalsHead, isOld);
            lua_pop(L, 1);  // pop val, keep key
        }
        lua_pop(L, 1); // pop metatable
    }

    // iterate module table
    lua_pushnil(L);
    while (lua_next(L, absMod) != 0) {
        upvalues_collect_from_function(L, upvalsHead, isOld);
        lua_pop(L, 1);  // pop val, keep key
    }

    LUA_STACK_CHECK_END(L);
}

const UpvalRecord *upvalues_find(UpvalRecord *searchList, UpvalRecord *searchFor) {
    const UpvalRecord *best = NULL;
    int best_score = 0;

    for (const UpvalRecord *cur = searchList; cur; cur = cur->next) {
        // check if upval names match
        if (strcmp(cur->name, searchFor->name) != 0) { continue; }

        // if function names match too, we found it
        if (cur->funcKeyStr && searchFor->funcKeyStr && strcmp(cur->funcKeyStr, searchFor->funcKeyStr) == 0) {
            return (UpvalRecord *)cur;
        }

        // if types match, that's a pretty good indicator
        int score = (cur->type == searchFor->type) ? 2 : 1;
        if (score > best_score) {
            best = cur;
            best_score = score;
        }
    }

    return best;
}

static void upval_record_push_key(lua_State *L, const UpvalRecord *rec) {
    if (rec->funcKeyStr) {
        lua_pushstring(L, rec->funcKeyStr);
    } else {
        lua_rawgeti(L, LUA_REGISTRYINDEX, rec->funcKeyRef);
    }
}

static void upvalues_join(lua_State *L, UpvalRecord *upvalsOld, UpvalRecord *upvalsNew, int moduleIdxOld, int moduleIdxNew) {
    int absOld = lua_absindex(L, moduleIdxOld);
    int absNew = lua_absindex(L, moduleIdxNew);

    for (UpvalRecord *newrec = upvalsNew; newrec; newrec = newrec->next) {
        const UpvalRecord *oldrec = upvalues_find(upvalsOld, newrec);
        if (!oldrec) { continue; }

        // push closures
        upval_record_push_key(L, newrec);  // key
        lua_gettable(L, absNew);           // new closure
        int idxNewFn = lua_gettop(L);

        upval_record_push_key(L, oldrec);
        lua_gettable(L, absOld);           // old closure
        int idxOldFn = lua_gettop(L);

        // only look through functions
        if (!lua_isfunction(L, idxNewFn) || !lua_isfunction(L, idxOldFn)) {
            lua_pop(L, 2);
            continue;
        }

        // locate upvalue slot on each
        int slotNew = -1;
        int slotOld = -1;

        // find new slot
        for (int i = 1; ; ++i) {
            if (!lua_upvalueid(L, idxNewFn, i)) { break; }
            if (lua_upvalueid(L, idxNewFn, i) == newrec->id) {
                slotNew = i;
                break;
            }
        }

        // find old slot
        for (int i = 1; ; ++i) {
            if (!lua_upvalueid(L, idxOldFn, i)) { break; }
            if (lua_upvalueid(L, idxOldFn, i) == oldrec->id) {
                slotOld = i;
                break;
            }
        }

        // join the two upvalues
        if (slotNew > 0 && slotOld > 0) {
            lua_upvaluejoin(L, idxNewFn, slotNew, idxOldFn, slotOld);
        }

        lua_pop(L, 2);   // pop both closures
    }
}

static void upvalues_replace_hooks(lua_State *L) {
    for (UpvalReference *newRef = sUpvalReferences; newRef; newRef = newRef->next) {
        if (newRef->isOld) { continue; }
        if (!newRef->name) { continue; }

        for (UpvalReference *oldRef = newRef; oldRef; oldRef = oldRef->next) {
            if (!oldRef->isOld) { continue; }
            if (!oldRef->name) { continue; }

            if (strcmp(newRef->name, oldRef->name) == 0) {
                smlua_hook_replace_function_references(L, oldRef->reference, newRef->reference);
                newRef->active = true;
                break;
            }
        }
    }
}

static void upvalues_print(UpvalRecord *upvalsHead) {
    for (const UpvalRecord *cur = upvalsHead; cur; cur = cur->next) {
        LOG_INFO("upval: %s, %s, %d, %p", cur->funcKeyStr ? cur->funcKeyStr : "(non-string)", cur->name, cur->ref, cur->id);
    }
}

static void overwrite_module_functions(lua_State *L, int dstIdx, int srcIdx) {
    srcIdx = lua_absindex(L, srcIdx);
    dstIdx = lua_absindex(L, dstIdx);

    lua_pushnil(L);  // first key for iteration
    while (lua_next(L, srcIdx) != 0) {
        // stack: ..., dstTable?, srcTable?, key, newVal

        int typeNew = lua_type(L, -1);

        // lookup oldVal = dstTable[key]
        lua_pushvalue(L, -2);      // copy key
        lua_gettable(L, dstIdx);   // push oldVal
        int typeOld = lua_type(L, -1);

        bool shouldOverride =
          (typeNew == LUA_TFUNCTION && typeOld == LUA_TFUNCTION) ||
          (typeNew != LUA_TNIL     && typeOld == LUA_TNIL);

        if (shouldOverride) {
            int idxNewVal = lua_gettop(L) - 1; // index of newVal

            // overwrite oldMod[key] = newVal
            lua_pushvalue(L, -3); // key
            lua_pushvalue(L, idxNewVal); // newVal
            lua_settable(L, dstIdx);  // dstTable[key] = newVal
        }

        // pop oldVal and newVal (leave key for next lua_next)
        lua_pop(L, 2);
    }
}

static void smlua_reload_module(lua_State *L, struct Mod* mod, struct ModFile *file) {
    LUA_STACK_CHECK_BEGIN(L);

    // only handle loaded Lua modules
    if (!file->isLoadedLuaModule) { return; }

    // get per-mod "loaded" table
    smlua_get_or_create_mod_loaded_table(L, mod);

    // get the old module table: loadedTable[file->relativePath]
    lua_getfield(L, -1, file->relativePath);              // ..., loadedTable, oldMod
    if (!lua_istable(L, -1)) {
        lua_pop(L, 2);
        return;
    }
    int moduleIdxOld = lua_gettop(L);

    // load & execute the new script -> pushes new module table
    struct ModFile *prevFile = gLuaActiveModFile;
    gLuaActiveModFile = file;
    int rc = smlua_load_script(mod, file, mod->index, false);      // ..., loadedTable, oldMod, newMod
    gLuaActiveModFile = prevFile;

    // exit on error
    if (rc != LUA_OK) {
        lua_pop(L, 3);
        return;
    }

    int moduleIdxNew = lua_gettop(L);

    // merge functions and join upvalues
    if (lua_istable(L, moduleIdxOld) && lua_istable(L, moduleIdxNew)) {
        // collect old upvals
        UpvalRecord *upvalsOld = NULL;
        upvalues_collect(L, &upvalsOld, moduleIdxOld, true);

        // collect new upvals
        UpvalRecord *upvalsNew = NULL;
        upvalues_collect(L, &upvalsNew, moduleIdxNew, false);

        // join upvals
        upvalues_join(L, upvalsOld, upvalsNew, moduleIdxOld, moduleIdxNew);

        // replace hooks
        upvalues_replace_hooks(L);

        // free upval collections
        upvalues_free(L, upvalsOld);
        upvalues_free(L, upvalsNew);

        // free upval references
        upval_references_free(L);

        // overwrite any functions in oldMod with newMod equivalents
        overwrite_module_functions(L, moduleIdxOld, moduleIdxNew);

        // now do the same for metatables
        if (lua_getmetatable(L, moduleIdxNew)) {      // pushes newMod's metatable
            int mtNewIdx = lua_gettop(L);
            if (lua_getmetatable(L, moduleIdxOld)) {  // pushes oldMod's metatable
                int mtOldIdx = lua_gettop(L);
                overwrite_module_functions(L, mtOldIdx, mtNewIdx);
                lua_pop(L, 1);  // pop oldMod's mt
            }
            lua_pop(L, 1);      // pop newMod's mt
        }

        // cleanup: replace newMod on stack with oldMod as return value
        lua_pushvalue(L, moduleIdxOld);   // duplicate oldMod
        lua_replace(L, moduleIdxNew);     // overwrite newMod slot with oldMod
        lua_pop(L, 3);                    // pop loadedTable and extra oldMod
    } else {
        lua_pop(L, 3);                    // pop loadedTable, oldMod, newMod
    }

    LUA_STACK_CHECK_END(L);
}

void smlua_live_reload_update(lua_State* L) {
    // only refresh every LIVE_RELOAD_TICK_COUNT ticks
    static int refreshTimer = 0;
    refreshTimer++;
    if ((refreshTimer % LIVE_RELOAD_TICK_COUNT) != 0) { return; }

    // cache the active mod/file
    struct Mod* prevMod = gLuaActiveMod;
    struct ModFile* prevModFile = gLuaActiveModFile;

    // search for mod files to update
    for (int i = 0; i < gActiveMods.entryCount; i++) {
        struct Mod *mod = gActiveMods.entries[i];
        gLuaActiveMod = mod;

        for (int j = 0; j < mod->fileCount; j++) {
            struct ModFile* file = &mod->files[j];

            // check modified time
            u64 timestamp = fs_sys_get_modified_time(file->cachedPath);
            if (timestamp <= file->modifiedTimestamp) { continue; }

            // update modified time and reload the module
            file->modifiedTimestamp = timestamp;
            gLuaActiveModFile = file;
            smlua_reload_module(L, mod, file);
        }

    }

    // restore previous active mod/file
    gLuaActiveMod = prevMod;
    gLuaActiveModFile = prevModFile;
}
