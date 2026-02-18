## [:rewind: Lua Reference](../lua.md)

# How to add, edit, and remove Characters

## Section 1: What is a `Character`?

A `Character` is a player's model, sounds, and animations that are used. Here is a watered down version of the `Character` struct, only showing relevant entries.

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
| torsoRotMult | `number` |  | No notes |
| animOffsetEnabled | `integer` |  | No notes |
| animOffsetLowYPoint | `number` |  | No notes |
| animOffsetFeet | `number` |  | No notes |
| animOffsetHand | `number` |  | No notes |

## Section 2: How to create a new character for a slot

Creating a new character starts with allocating a new character. You can allocate a character with the `character_allocate`. This function takes in the name of the character, and returns a `Character`, that can be used to edit all the stuff of your character, and it also returns a `characterIndex`, this is the index it has been allocated to in `gCharacters` for access later. If you wish to change the name of your character afterwards, you can use the `character_set_name` function.

Past this point, any mutable variables in `character` may be changed to your liking. You're going to want to set `modelId`, `capModelId`, etc. as the first thing. You can change the hud head texture with `character_set_hud_head_texture`

### Animations

#### TODO: I do not know where a player gets the data to register an animation, so this is super barebornes

Adding an animation to a character first requires the animation to be registered with the `smlua_anim_util_register_animation` function. With this done, you can set your animation to the name you set when you called `smlua_anim_util_register_animation` with `character_set_animation`. This function takes in your `Character`, and more importantly, your animation id, which is the animation you want to replace, for example `CHAR_ANIM_SINGLE_JUMP`. The last parameter is the name of the animation registered with `smlua_anim_util_register_animation`. Animations may also be removed with

### Sounds

Sounds are done using sound files, like `.mp3`, `.aiff`, or `.ogg`. The function for adding a sound is `character_add_sound`. This function takes in your `Character`, the sound id you want to replace, for instance, `CHAR_SOUND_YAH_WAH_HOO`, and the name of your sound file. Multiple sounds can be added to a single sound id. If there are multiple sounds on one id, it picks between these sounds randomly. You can remove all sounds associated with an id with `character_remove_sounds`.

## Section 3: Modifying and removing characters

The `gCharacters` table is exposed to Lua, and fully modifiable. You should only modify characters if you absolutely have to, it's almost always better to create a new character. The `characterIndex` provided when you allocate a character with `character_allocate` is the index for `gCharacters` that points to your provided `character`. So, if for some reason you wanted to modify your character using the `gCharacters` table, you could. Removing a character can be done by simply calling `character_deallocate`, and passing in your `Character`.