# How to use `gMarioStates`

## Section 1: What is `gMarioStates`?

gMarioStates is an array that goes from 0 to the maximum amount of players, or 16, subtracted by 1, 0 being your mario, that contains a `MarioState` struct. The reason the end of the range is the max players subtracted by 1 instead of just the max players is because arrays are 0 indexed, which means that instead of starting at 1, arrays start at 0, so the total numbers of entries in that array is 16, which is the maximum amount of players. 

## Section 2: What is the `MarioState` Structure?

The `MarioState` structure contains 76 different variables, this guide will try to make it as easy as possible to understand.

| Field | Type | Notes |
| ----- | ---- | ----- |
| `playerIndex`|`integer`| This is the local index of the Mario you are modifying out of all of the 16 different Mario's.
| `input`|`integer`| Mario's current input. This can be the `INPUT_A_BUTTON `constant, etc.
| `flags`| `integer`| Includes things such as the current cap mario has on, and similar properties.
| `particleFlags`| `integer`|This can be used to add particles to Mario, such as the one you see with the star dance.
|`action`|`integer`| Mario's current action, this includes `ACT_IDLE`, `ACT_JUMP`, etc.
|`prevAction`|`integer`|Mario's previous action, similar to above.
|`terrainSoundAddend`|`integer`|Used to see what sound for the terrain is being used.
|`actionState`|`integer`|Typically used within actions, can be useful for deciding whether or not to return a specific action by reading this variable set within the action.
|`actionTimer`|`integer`|How long it has been since the action was set.
|`actionArg`|`integer`|This var is typically set when the action is set, i.e when setting the action to `ACT_STAR_DANCE`, decide whether or not the animation should be the water star dance animation or not, if yes, set `actionArg` to 1, else, set `actionArg` to 0
|`intendedMag`|`integer`|The intended magnitude. Without smoothening, this is the magnitude 
|`intendedYaw`|`integer`|The intended yaw, similar to above, except the yaw, or y axis.
|`invincTimer`|`integer`|How long Mario will be invincible, if 0 or less than 0, there will be no invincibility for Mario. 
|`framesSinceA`|`integer`|How long it has been since the controller last hit the A button.
|`framesSinceB`|`integer`|How long it has been since the controller last hit the B button.
|`wallKickTimer`|`integer`|When you bonk on a wall, this timer is set to 5, if you press A before the timer comes down to 0, then the walljump action can be set.
|`doubleJumpTimer`|`integer`|Similar to the `wallKickTimer`, except for being able to do a double jump.
|`faceAngle`|`Vec3s`|Which direction mario is looking in every axis.
|`angleVel`|`Vec3s`|Mario's angle velocity, how slow or fast Mario's angle will change.
|`slideYaw`|`integer`|Mario's yaw face angle when sliding.
|`twirlYaw`|`integer`|Mario's yaw face angle when twirling.
|`pos`|`Vec3f`|Mario's current location.
|`vel`|`Vec3f`|Mario's velocity, this is different from mario's `forwardVel` below, and more advanced. This is typically used to adjust Mario's overall speed.
|`forwardVel`|`integer`|Mario's forward velocity, used in most of Mario's actions.
|`slideVelX`|`integer`|Mario's x velocity for sliding. Typically use this with `slideVelZ` for best results.
|`slideVelZ`|`integer`|Mario's z velocity for sliding. Typically use this with `slideVelX` for best results.
|`wall`|`Surface`|The wall mario is currently touching.
|`ceil`|`Surface`|The ceiling mario is currently touching.
|`floor`|`Surface`|The floor mario is currently touching.
|`ceilHeight`|`integer`|The height of mario's current ceiling.
|`floorHeight`|`integer`|The height of mario's current floor.
|`floorAngle`|`integer`|The angle of mario's current floor.
|`waterLevel`|`integer`|The height of mario's current water.
|`interactObj`|`Object`|The object mario has interacted with.
|`heldObj`|`Object`|The object mario is holding.
|`usedObj`|`Object`|The object mario is "using" i.e stomping a goomba, or grabbing the hoot in Whomp's Fortress.
|`riddenObj`|`Object`|The object mario is riding, for instance, if he is riding a shell, then mario's `riddenObj` will be set to the shell object.
|`marioObj`|`Object`|Mario's object, Mario himself is an object, so the `MarioState` structure contains the Mario object.
|`spawnInfo`|`SpawnInfo`|Mario's Spawn Info, this is much more advanced, and should not need to be changed.
|`area`|`Area`|Mario's current area. You can use this var to access the camera, music params, warp nodex, etc.
|`statusForCamera`|`PlayerCameraState`|This is a bit more complicated, but is generally used to handle cutscenes, and other things such as cannons.
|`marioBodyState`|`MarioBodyState`|This var contains multiple visual variables, such as Mario's head position, if Mario should look like he has the vanish, metal, or wing cap on, etc.
|`controller`|`Controller`|This contains the button Mario is pressing, holding, the stick position, etc. Similar to input, except easier to change this variable and see results.
|`animation`|`MarioAnimation`|Contains Mario's animation data, you usually don't have to touch this, but rather use functions such as `set_mario_animation`.
|`collidedObjInteractTypes`|`integer`|If Mario is interacting with an object, then the type will be in this variable, i.e when interacting with a door, this variable will be set to `INTERACT_DOOR`, assuming it's not `INTERACT_WARP_DOOR`.
|`numCoins`|`integer`|How many coins Mario has.
|`numStars`|`integer`|How many stars Mario has. **NOTE: Changing this variable will NOT change the save file**, if you need to do that, refer to the function `save_file_set_star_flags`.
|`numKeys`|`integer`|*\[UNUSED\]* How many keys mario has.
|`numLives`|`integer`|How many lives mario has.
|`health`|`integer`|Mario's health in hex value. Full health is 0x880.
|`unkB0`|`integer`|Something you wont have to modify, seems to be used for animations and such.
|`hurtCounter`|`integer`|How much health mario should lose.
|`healCounter`|`integer`|How much health mario should gain.
|`squishTimer`|`integer`|How long mario should stay squished for. It should be noted that if the `squishTimer` is less than or equal to 16 that mario's size will rubberband. It should also be noted that if mario's `squishTimer` is equal to 0, then mario's size will be normal.
|`fadeWarpOpacity`|`integer`|Mario's opacity when using a fading warp.
|`capTimer`|`integer`|How much time should the current cap last for.
|`prevNumStarsForDialog`|`integer`|This var is used to decide if the star dialog should be played or not.
|`peakHeight`|`integer`|Mario's highest point, or y value. Mainly used for fall damage to see how far Mario has fallen since his peak height.
|`quicksandDepth`|`integer`|How deep mario is into the quicksand.
|`unkC4`|`integer`|You probably wont need to modify this variable, seems to be used for `ACT_GETTING_BLOWN`.
|`currentRoom`|`integer`|The room mario is in, used for handling the rendering of rooms.
|`heldByObj`|`Object`|The object mario is being held by, mainly used for King Bob-omb and Chuckya.
|`isSnoring`|`integer`|Stores if Mario is snoring or not, can be used as a bool.
|`bubbleObj`|`Object`|The bubble object for Mario, this is almost always the bubble you see when bubbling is enabled in the host settings.
|`freeze`|`integer`|Stores if Mario is frozen or not, can be used as a bool.
|`splineKeyframe`|`Vec4s`|Used in the flight path for the grand star.
|`splineKeyframeFraction`|`integer`|Used in the flight path for the grand star.
|`splineState`|`integer`|Used in the flight path for the grand star.
|`nonInstantWarpPos`|`Vec3f`|Mario's non instant warp position, not used in many places, you should not have to change this var.
|`character`|`Character`|Contains all of Mario's \(or the current character's\) sounds, like snoring, dying, being attacked, etc.
|`wasNetworkVisible`|`bool`|A more advanced variable, this var should not be changed unless you know what your doing.
|`minimumBoneY`|`integer`|Used for animations.
|`curAnimOffset`|`integer`|Used to offset an animation.
|`knockbackTimer`|`integer`|Used for invincibilty when flying through the air after a bonk or being hit by another player.
|`specialTripleJump`|`integer`|Can be used as a bool, sets whether or not to use the special triple jump unlocked after talking to Yoshi.
|`wallNormal`|`Vec3f`|The angle of the current wall on the x, y, and z axis.
|`cap`|`integer`|Where Mario's cap is meant to be. Can be on Mario's head, the snowman's head in Snowman's Land, held by Klepto, or on Ukiki's head.
|`dialogID`|`integer`|The id of the current dialog Mario is in. The default value for not being in any dialog is -1.

## Section 3: When should I use `gMarioStates`?
Most of the time you won't be using `gMarioStates[0]` to access your Mario, but rather use a hook. A lot of hooks pass `m` through the function. What does this mean? Well, here is a example with comments to explain it as well as possible:

```lua
-- m here is gMarioStates with the index being 0...16, one of those, so you are not always modifying your own mario.
function mario_update(m)
	-- Refer to section 2 of this guide to know what playerIndex is

	-- Remember how gMarioStates[0] is the local mario? Well the playerIndex is the same way! This means that if the playerIndex is not 0, then it's not the local mario, thus we can't do anything with it! So, when we return here, that means that we dont do anything below the return within that function

	-- This means, if not the local Mario, stop executing the function (return nothing).
	if m.playerIndex ~= 0 then return end
end

-- Create the hook here, to understand this better, refer to the guide on hooks. NOTE: There are more hooks you can use to do specific things, however HOOK_MARIO_UPDATE is the most common hook to be used.

-- While it isn't mandatory to use "mario_update" as the function name, it is highly recommended and a common practice.
hook_event(HOOK_MARIO_UPDATE, mario_update)
```

The only time you should use `gMarioStates[0]` is if the hook you are using does not have `m` as a parameter, otherwise, do as shown above with your own function names.

## Section 4: Wrapping Up
Hopefully, you were now able to learn more about how `gMarioStates` works.
