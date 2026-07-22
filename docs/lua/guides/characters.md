## [:rewind: Lua Reference](../lua.md)

# How to add, edit, and remove Characters

## Section 1: What is a [Character](../structs.md#Character)?

A [Character](../structs.md#Character) is a player's model, sounds, and animations that are used. Here is a watered down version of the [Character](../structs.md#Character) struct, only showing relevant entries.

| Field | Type | Access | Notes |
| ----- | ---- | ------ | ----- |
| type | [enum CharacterType](../constants.md#enum-CharacterType) or `integer` | | What type of character it is. An example usecase would be a modder adding their own custom type to keep track of what characters use a specific moveset. |
| name | `string` | read-only | The name of the character shown in the player customization menu. May be read from here, but should be modified with the `character_set_name` function. |
| hudHeadTexture | [TextureInfo](../structs.md#TextureInfo) | read-only | The texture shown as the player head. Used as the lives icon, mario cam icon, and more. Should not be set directly, but should be set with `character_set_hud_head_texture`. |
| modelId | `integer` |  | This is the model id used for the character. An example model would be `E_MODEL_MARIO`. |
| capModelId | `integer` |  | This is the model id used for the character's cap, specifically the cap lying on the ground. (i.e. `E_MODEL_MARIOS_CAP`). |
| capMetalModelId | `integer` |  | The same as the `capModelId`, but for a metal cap. |
| capWingModelId | `integer` |  | The same as the `capModelId`, but for a cap with wings. |
| capMetalWingModelId | `integer` |  | The same as `capModelId`, but for a metal cap with wings. |
| capEnemyLayer | `integer` |  | This is the layer to render the cap that's put on enemies (like ukiki, or the monkey on ttm). Default is `LayerAlpha` |
| capEnemyGfx | `string` | read-only | This is the GFX name to be used to render the cap put on enemies. Default's to mario's cap gfx.
| capEnemyDecalGfx | `string` | read-only | This is the GFX name to be used to render the cap decal put on enemies. Default's to mario's cap decal gfx.

## Section 2: How to create a new character for a slot

Creating a new character starts with allocating a new character. You can allocate a character with the `character_allocate`. This function takes in the name of the character, and returns a [Character](../structs.md#Character), that can be used to edit all the stuff of your character, and it also returns a `characterIndex`, this is the index it has been allocated to in `gCharacters` for access later. If you wish to change the name of your character afterwards, you can use the `character_set_name` function.

Past this point, any mutable variables in `character` may be changed to your liking. You're going to want to set `modelId`, `capModelId`, etc. as the first thing. You can change the hud head texture with `character_set_hud_head_texture`

### Animations

Adding an animation to a character first requires the animation to be registered with the `smlua_anim_util_register_animation` function. The data needed for this can be obtained from multiple differente places, but the easiest for custom animations for models using fast64 is using [fast64-gart](https://github.com/maniscat2/fast64-gart). With this done, you can set your animation to the name you set when you called `smlua_anim_util_register_animation` with `character_set_animation`. This function takes in your [Character](../structs.md#Character), and more importantly, your animation id, which is the animation you want to replace, for example `CHAR_ANIM_SINGLE_JUMP`. The last parameter is the name of the animation registered with `smlua_anim_util_register_animation`. Animations may also be removed with `character_remove_animation`, which takes in your `Character`, and the animation id you want to remove the animation for, for example, `CHAR_ANIM_SINGLE_JUMP`.

### Sounds

Sounds are done using sound files, like `.mp3`, `.aiff`, or `.ogg`. The function for adding a sound is `character_add_sound`. This function takes in your [Character](../structs.md#Character), the sound id you want to replace, for instance, `CHAR_SOUND_YAH_WAH_HOO`, and the name of your sound file. Multiple sounds can be added to a single sound id. If there are multiple sounds on one id, it picks between these sounds randomly. You can remove all sounds associated with an id with `character_remove_sounds`.

## Section 3: Modifying and removing characters

The `gCharacters` table is exposed to Lua, and fully modifiable. You should only modify characters if you absolutely have to, it's almost always better to create a new character. The `characterIndex` provided when you allocate a character with `character_allocate` is the index for `gCharacters` that points to your provided `character`. So, if for some reason you wanted to modify your character using the `gCharacters` table, you could. Removing a character can be done by simply calling `character_deallocate`, and passing in your [Character](../structs.md#Character).

## Section 4: Syncing

Characters don't actually have to be allocated in order for them to show up on other player's screens. For the most part syncing just works, but there's a few things that you have to consider:

1. Always allocate your models, i.e `local E_MODEL_NEW_CHARACTER = smlua_model_util_get_id('new_character_geo')` in a predictable manner for every user. That means don't nest the initialization in a if statement, or anything like that. Doing so may lead to desynced player id's, and will cause syncing to not work.
2. Your animations registered with `smlua_anim_util_register_animation` also has to be deterministic. Don't put those in if statements, always register the animation at the same time, or you risk an animation index desync.

Following these steps, you should end up fine. These are unfortunate limitations with the current system, and ideally everything would just sync over the network, but we aren't there yet.

## Section 5: An example for adding a [Character](../structs.md#Character)

Here's a code example of adding a [Character](../structs.md#Character).

```lua
-- name: Example Character Mod!

-- This is allocated in the file with no if statements around.
-- This is deterministic, and so is safe
local E_MODEL_NEW_CHARACTER = smlua_model_util_get_id('new_character_geo')
-- This is also deterministic, even though it's in a table, every model is allocated in the same order everytime
local CAPS_NEW_CHARACTER = {
    normal = smlua_model_util_get_id("new_character_cap_geo"),
    wing = smlua_model_util_get_id("new_character_wing_cap_geo"),
    metal = smlua_model_util_get_id("new_character_metal_cap_geo"),
    metalWing = smlua_model_util_get_id("new_character_metal_wing_cap_geo")
}

-- These are all the different sound files we will allocate later. You can have multiple sounds, so we do on some of them.
local VOICETABLE_NEW_CHARACTER = {
    [CHAR_SOUND_ATTACKED] = 'new_character_ouch.ogg',
    [CHAR_SOUND_DOH] = 'new_character_bonk0.ogg',
    [CHAR_SOUND_DROWNING] = 'new_character_death.ogg',
    [CHAR_SOUND_DYING] = 'new_character_death.ogg',
    [CHAR_SOUND_GROUND_POUND_WAH] = 'new_character_shaa.ogg',
    [CHAR_SOUND_HAHA] = { 'new_character_laugh1.ogg', 'new_character_laugh0.ogg' },
    [CHAR_SOUND_HAHA_2] = 'new_character_laugh1.ogg',
    [CHAR_SOUND_HERE_WE_GO] = 'new_character_victory.ogg',
    [CHAR_SOUND_HOOHOO] = 'new_character_att0.ogg',
    [CHAR_SOUND_HRMM] = 'new_character_flourish.ogg',
    [CHAR_SOUND_LETS_A_GO] = 'new_character_letsago.ogg',
    [CHAR_SOUND_MAMA_MIA] = { 'new_character_speak0.ogg', 'new_character_speak1.ogg' },
    [CHAR_SOUND_ON_FIRE] = 'new_character_ouch.ogg',
    [CHAR_SOUND_OOOF] = 'new_character_bonk1.ogg',
    [CHAR_SOUND_OOOF2] = 'new_character_bonk1.ogg',
    [CHAR_SOUND_PUNCH_HOO] = 'new_character_att1.ogg',
    [CHAR_SOUND_PUNCH_WAH] = 'new_character_jump1.ogg',
    [CHAR_SOUND_PUNCH_YAH] = 'new_character_att0.ogg',
    [CHAR_SOUND_SO_LONGA_BOWSER] = 'new_character_flourish.ogg',
    [CHAR_SOUND_TWIRL_BOUNCE] = 'new_character_flourish.ogg',
    [CHAR_SOUND_UH] = 'new_character_bonk1.ogg',
    [CHAR_SOUND_UH2] = 'new_character_jump0.ogg',
    [CHAR_SOUND_UH2_2] = 'new_character_bonk1.ogg',
    [CHAR_SOUND_WAAAOOOW] = 'new_character_death.ogg',
    [CHAR_SOUND_WAH2] = 'new_character_att0.ogg',
    [CHAR_SOUND_WHOA] = 'new_character_bonk1.ogg',
    [CHAR_SOUND_YAHOO] = 'new_character_shaa.ogg',
    [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = { 'new_character_yell0.ogg', 'new_character_yell1.ogg' },
    [CHAR_SOUND_YAH_WAH_HOO] = { 'new_character_jump0.ogg', 'new_character_jump1.ogg' },
}

-- This is done deterministically, as it is not done in an if statement, and there is no code stopping execution of this file
-- This is not real data, this is empty, as I don't want this file to be 700 lines long :D
smlua_anim_util_register_animation('new_character_single_jump', 0, 0, 0, 0, 0, {})
smlua_anim_util_register_animation('new_character_triple_jump', 0, 0, 0, 0, 0, {})

-- These are your registered animation names, we put it in a table for easier use
local NEW_CHARACTER_ANIMS = {
    [CHAR_ANIM_SINGLE_JUMP] = 'new_character_single_jump',
    [CHAR_ANIM_TRIPLE_JUMP] = 'new_character_triple_jump',
}

-- Allocate a character, we dismiss the index as we won't be using it
local character, _ = character_allocate("NewChar!")

-- set models
character.modelId = E_MODEL_NEW_CHARACTER
character.capModelId = CAPS_NEW_CHARACTER.normal
character.capWingModelId = CAPS_NEW_CHARACTER.wing
character.capMetalModelId = CAPS_NEW_CHARACTER.metal
character.capMetalWingModelId = CAPS_NEW_CHARACTER.metalWing

-- set sounds according to table above
for k, v in pairs(VOICETABLE_NEW_CHARACTER) do
    if type(v) == "string" then
        character_add_sound(character, k, v)
    elseif type(v) == "table" then
        for i = 1, #v do
            if type(v[i]) == "string" then
                character_add_sound(character, k, v[i])
            end
        end
    end
end

-- set animations according to table above
for k, v in pairs(NEW_CHARACTER_ANIMS) do
    character_set_animation(character, k, v)
end

-- and that's it! You should have an allocated character in your menu that works fine!

```