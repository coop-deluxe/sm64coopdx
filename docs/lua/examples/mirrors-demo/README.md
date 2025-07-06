# Mirrors

This example mod features three different levels with mirrors.<br>
Open the mod menu to warp directly to them.

- First level has three mirrors, two on walls and one on ceiling.
- Second level has three mirrors, two on walls and one on floor.
- Third level is the SM64 mirror room, but with a twist (enable "Strange reflections" in mod menu).

Also features a debug display toggle to show mirror hitboxes.

<br>

## How to place mirrors in a level

Mirrors are objects with one of the two behaviors:

- `bhvHorizontalMirror`: A mirror that reflects objects horizontally, i.e. from one side to the other side or it.
  - Position (`oPosX/Y/Z`) is the center of the mirror.
  - Width (`oMirrorWidth`) is the length of the mirror on the XZ plane.
  - Height (`oMirrorHeight`) is the length of the mirror on the Y axis.
  - Max distance (`oMirrorMaxDistance`) is the maximum distance along the mirror normal (determined by `oFaceAngleYaw`) before an object stops being reflected by this mirror.

- `bhvVerticalMirror`: A mirror that reflects objects vertically, i.e. above or below it.
  - Position (`oPosX/Y/Z`) is the center of the mirror.
  - Width (`oMirrorWidth`) is the length of the mirror perpendicularly to the direction of the mirror (determined by `oFaceAngleYaw`).
  - Height (`oMirrorHeight`) is the length of the mirror along the direction of the mirror (determined by `oFaceAngleYaw`).
  - Max distance (`oMirrorMaxDistance`) is the maximum distance on the Y axis before an object stops being reflected by this mirror.

The combination of all these parameters define a box inside which an object can be reflected by the mirror.<br>
In this example mod, enable "Show mirror hitboxes" to visualize these boxes.

<br>

To define a mirror in a level script, use the following macro:
```c
OBJECT(MODEL_NONE, center_x, center_y, center_z, 0, dir_yaw, 0, ((((width / 10) & 0x7FF) << 21) | (((height / 10) & 0x7FF) << 10) | (((max_distance / 10) & 0x3FF) << 0)), behavior)
```
and replace `center_x`, `center_y`, `center_z`, `dir_yaw`, `width`, `height`, `max_distance` and `behavior`.

<br>

## How to use mirrors in Lua

In Lua scripts though, mirrors have all the same behavior: `bhvMirror`.<br>
To retrieve the type of a mirror, do `mirror.oMirrorType`:
|Value|Behavior|
|--|--|
|MIRROR_TYPE_HORIZONTAL|bhvHorizontalMirror|
|MIRROR_TYPE_VERTICAL|bhvVerticalMirror|

Mirror object fields can be modified anytime and changes are reflected automatically.

Additionally, a new hook has been added: `HOOK_ON_MIRROR_OBJECT_RENDER`.<br>
This hook is called when a reflection (mirror object) is about to be rendered:

- `hookRender` must be set to a non-zero value on the original object.
- The callback cannot return a boolean, but unsetting the `GRAPH_RENDER_ACTIVE` flag of a mirror object prevents it to be rendered and reflected.
- Mirror objects have the following object fields (all these fields are immutable):
  - `oMirrorObjPrevObj`: The reflected object. Can be either a real object or a reflection.
  - `oMirrorObjRealObj`: The original object.
  - `oMirrorObjMirror`: The mirror that created this reflection.

Finally, the global setting `gBehaviorValues.MirrorsMaxReflections` controls how many times a real object can be reflected through mirrors. Defaults to `8`.

<br>

## Limitations

- Only objects are reflected through mirrors. Level geometry must be manually reflected by the level designer to create the illusion of mirroring.
- Shadows are not reflected by vertical mirrors. Shadow code is too hard to deal with.
- Supports frame interpolation, to some extent. Don't stack too much mirrors in the same place.
