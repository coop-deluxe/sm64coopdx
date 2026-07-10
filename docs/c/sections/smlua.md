## [:rewind: C Reference](../c.md)

# SMLua

SMLua is what allows Lua to communicate with SM64. It's the backbone of the modding API, and it contains multiple features that makes development in C convenient.

## Autogen

Autogen is the system in place to allow C constants, functions and structs to be exposed to the Lua API automatically.

Autogen can be ran by running `autogen/autogen.sh` in the root directory of your project.

Autogen may need a rerun when changes are made to:
- Functions
- Structs
- Enums
- Hooks
- etc.

## Adding functions, structs, and constants to autogen

Constants, functions, and structs are each handled in their own files.

- `convert_constants.py`
- `convert_functions.py`
- `convert_structs.py`

But thankfully, one does not need to know how it works but rather focus on a single file: `exposed_lists.py`.<br>
In this file, you will find numerous options sorted in three categories: `constants`, `functions` and `structs`.<br>
Note that all `whitelist`, `blacklist` and `hidden` dicts support regular expressions.

### Constants

Let's start with the constants options:

- `constants_files` defines in which files autogen should look into to expose constants.<br>
  All filepaths are relative to the root of the repository.
- `constants_whitelist` defines for each file which constants should be exposed and ignore every other constant in that file.<br>
  For example, in `mod_storage.h`, there's a bunch of constants we don't want exposed to Lua, so instead of excluding them, we include the few we actually need.
- `constants_blacklist` defines for each file which constants should not be exposed.<br>
  For example, in `djui_console.h`, we don't want to include `CONSOLE_MAX_TMP_BUFFER`, Lua has no need for that constant, so we exclude it.
- `constants_hidden` defines for each file which constants should be exposed, but not appear in the documentation.<br>
  It is usually done for deprecated constants or ones that have a temporary or placeholder name but some mods already use them, so they can't be removed completely.<br>
  For example, in `interaction.h`, `INTERACT_UNKNOWN_08` is not a very explicit name, but since mods use it, it must exist in the API.

### Functions

Functions have quite a bit of options, so let's go over it:

- `functions_files` defines in which files autogen should look into to expose functions.<br>
  All filepaths are relative to the root of the repository.
- `functions_whitelist` defines for each file which functions should be exposed and ignore every other function in that file.<br>
  It proves especially useful for functions since frequently files contains tons of functions that shouldn't be exposed to Lua.
- `functions_blacklist` defines for each file which functions should not be exposed.
- `functions_hidden` defines for each file which functions should be exposed, but not appear in the documentation.<br>
  This is typically used for deprecated or renamed functions.
- `functions_version_excludes` excludes functions from a specific version of the game.<br>
  It doesn't have too much of a use anymore, so you can ignore it.

Functions have a unique feature of being able to be documented. In a header file where autogen reads the function and generates documentation and generates an SMLua implementation, you can define a description for the function above it. An example of it and the syntax is as the following:

```c
/* |description|Behavior init function for NPC Toad|descriptionEnd| */
void bhv_toad_message_init(void);
```

It can also be multiline:

```c
/* |description|
Checks if Mario's current animation has reached its final frame (i.e., the last valid frame in the animation).
Useful for deciding when to transition out of an animation-driven action
|descriptionEnd| */
s32 is_anim_at_end(struct MarioState *m);
```

### Structs

Structs have the most options, so let's go through it:

- `structs_files` defines in which files autogen should look into to expose structs.<br>
  All filepaths are relative to the root of the repository.
- `structs_whitelist` defines for each file which structs should be exposed and ignore every other struct in that file.
- `structs_blacklist` defines for each file which structs should not be exposed at all.
- `structs_excluded` is a list of struct names that should never be exposed from any file, including as another struct fields.
- `structs_fields_whitelist` defines for each struct which fields should be exposed and ignore every other field in that struct.
- `structs_fields_blacklist` defines for each struct which fields should not be exposed to Lua.
- `structs_fields_hidden` defines for each struct which fields should be exposed, but not appear in the documentation.<br>
  Like constants and functions, this is usually done for deprecated or renamed fields.
- `structs_fields_version_excludes` tells autogen to exclude specific fields depending on your version.<br>
  Similarly to `functions_version_excludes`, it doesn't have too much of a use anymore, so you can ignore it.
- `structs_fields_types` changes the type of a field in a struct to something else.<br>
  It pretty much lies to Lua about what it actually is. This usually isn't useful, but in specific scenarios it can be.
- `structs_fields_mutable` defines which fields should be mutable (read and write), but turn every other field of the struct immutable (read-only).
- `structs_fields_immutable` defines which fields should be immutable (read-only).<br>
  By default, all fields are mutable, except pointers.

## Hook Events

Hook events are partially done through autogen and manual C code. Documentation for hooks is manually written out in [hooks.md](../../lua/guides/hooks.md), and sometimes the implementation of a hook event is done manually.

### Defining a hook event

Hook events are defined in 2 places, `smlua_hooks.h`, found in `src/pc/lua`, and `smlua_hook_events.inl`, also found in `src/pc/lua`.

If you want to create a hook, first go to `smlua_hooks.h` and find the `LuaHookedEventType` enum.

Scroll down to the bottom until you find `HOOK_MAX`. `HOOK_MAX` should always be at the very bottom of the enum, so move your custom hook one spot above it. Add your custom hook there.

Next, go to `smlua_hook_events.inl`. This is where the magic happens.

You can define your custom hook with `SMLUA_EVENT_HOOK`. Let's go over how it works and what the parameters are:

- The very first parameter is your hook defined in `smlua_hook.h`
- The next parameter is the hook event return type, here are the options:

```c
enum LuaHookedEventReturn {
    HOOK_RETURN_NEVER,              // Never returns before calling all hooks for a given event, returns true if there is at least one successful callback call
    HOOK_RETURN_ON_SUCCESSFUL_CALL, // Returns true on first successful callback call, skipping next hooks for a given event
    HOOK_RETURN_ON_OUTPUT_SET,      // Returns true on output set after a successful call, skipping next hooks for a given event
};
```

- To reiterate, `HOOK_RETURN_NEVER` should be used if your hook should always go to every single mod. If you don't use `HOOK_RETURN_NEVER`, your hook may only be ran for one instance.
- `HOOK_RETURN_ON_SUCCESSFUL_CALL` should be used if you don't want any other mods to use a hook call if the call succeeds for the first mod handling it. It's only used a few times, but it can come in handy.
- `HOOK_RETURN_ON_OUTPUT_SET` should be used if you don't want any mod to access a hook that had it's output set by Lua.
- If these 3 hook return types don't cover what you are looking for, you need to make a custom implementation, mark this parameter with an `_` if you want to do a custom implementation.
- Every argument after is the parameters and return values for Lua, and they are optional. Parameters come first, insert the parameters you want Lua to receive, for instance, `struct MarioState *m` to allow Lua to receive a mario state in the hook event call.
- After parameters comes output, or return values. This is optional. To define an output parameter, use the `OUTPUT` macro.
- Here is an example hook showcasing this:

```c
// Never end the hook early, so use HOOK_RETURN_NEVER, pass in the current mario state and the hazard types as parameters to lua. Request a boolean from Lua to decide if the hazard should be registered or not.
SMLUA_EVENT_HOOK(HOOK_ALLOW_HAZARD_SURFACE, HOOK_RETURN_NEVER, struct MarioState *m, s32 hazardType, OUTPUT bool *allowHazard)
```

### Calling a hook event from C

Hook events can be called via the `smlua_call_event_hooks`. The best way to explain this function is with an example. Let's use that same hook, `HOOK_ALLOW_HAZARD_SURFACE`.

```c
bool allowHazard = true;
smlua_call_event_hooks(HOOK_ALLOW_HAZARD_SURFACE, m, HAZARD_TYPE_LAVA_WALL, &allowHazard);
```

- First, the hook name defined in the `LuaHookedEventType` is inserted.
- Each parameter that comes after that follows the same layout as defined in the `SMLUA_EVENT_HOOK` call, including the output.
- The output should be a reference so the function can properly set the variable.
- If Lua doesn't return anything, the output passed into the function stays as what it was originally, so it serves as a default value. That's why `allowHazard` is set to true.

After all these changes, remember to rerun autogen. Once that's done, you should have your hook into the game, test it and make sure everything works!
