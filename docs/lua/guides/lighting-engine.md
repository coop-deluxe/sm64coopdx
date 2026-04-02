## [:rewind: Lua Reference](../lua.md)

# How to use the Lighting Engine

## Section 1: Preparation

The Lighting Engine is a vertex point lighting system built directly into sm64coopdx and its renderer. It works on all backends and is relatively easy to use.

To use the Lighting Engine, you need to figure out how you want to approach using it given the different modes it has. There are also 2 methods to enable the lighting engine, either by setting the ambient color, or spawning a point light in.

## Section 2: Modes

The lighting engine has 3 modes you can switch between using `le_set_mode(mode)`.

1. `LE_MODE_AFFECT_ALL_SHADED_AND_COLORED`: (Default) Applies lighting to every shaded and vertex colored surface minus some geometry and menus.

2. `LE_MODE_AFFECT_ALL_SHADED`: Applies lighting to every shaded surface minus some geometry and menus.

3. `LE_MODE_AFFECT_ONLY_GEOMETRY_MODE`: Only applies lighting to geometry that has the `G_LIGHTING_ENGINE_EXT` geometry mode.

`LE_MODE_AFFECT_ONLY_GEOMETRY_MODE` was the only "mode" until djoslin0 improved the lighting engine and came up with a system for affecting shaded surfaces without needing to apply the lighting engine geometry mode to every actor and level manually.

## Section 3: Tonemapping

The lighting engine has 4 tonemapping modes you can switch between using `le_set_tone_mapping(toneMapping)`.

1. `LE_TONE_MAPPING_TOTAL_WEIGHTED`: Weighs the combined ambient color and lights together, can look slightly dim.

2. `LE_TONE_MAPPING_WEIGHTED`: (Default) Weights the lights on top of the ambient color instead of with it, generally looks the best with good color balance.

3. `LE_TONE_MAPPING_CLAMP`: The sum of the lights and ambient color clamped between 0 and 255. Colors can look overexposed if lights are too bright.

4. `LE_TONE_MAPPING_REINHARD`: The sum of the lights and ambient color divided by itself + 255, multiplied by 255, and then clamped between 0 and 255. Looks like clamped but dimmed.

You can see the visual differences of the different tonemappings in [this video](https://youtu.be/TJ_qnzi8YHA?t=25).

## Section 4: Ambient Light

There are two ways you can set the ambient color for the scene.

### 1. `le_set_ambient_color(r, g, b)`
To set the ambient color directly through code.

### 2. `bhvAmbientLight` object with `0xRRGGBB00` behavior parameters
The first 3 bytes are for the red, green, and blue values. This will set the ambient color once on init but not on loop so changing the ambient color is possible.

**Be mindful of an annoying SM64 engine quirk**: If you set the third byte to 255, which the game uses to store respawn bit information, it will think the light has already been spawned and it won't spawn. There isn't really a way around this except using 254 instead of 255, but `le_set_ambient_color` does not have this quirk and you can use 255 for the third value.

## Section 5: Point Lights

There are two ways you can add point lights in the scene.

### 1. `le_add_light(x, y, z, r, g, b, radius, intensity)` 
To spawn a point light directly through code.

| Parameter | Description |
| --------- | ----------- |
| `x` | X coordinate |
| `y` | Y coordinate |
| `z` | Z coordinate |
| `r` | Red value |
| `g` | Green value |
| `b` | Blue value |
| `radius` | How many units out the light should spread, 500-1000 units recommended. |
| `intensity` | How much influence/brightness the light has, 2.0 recommended. |

### 2. `bhvPointLight` object with `0xRRGGBBWW` behavior parameters
The first 3 bytes are for the red, green, and blue values. The Ws are an arbitrary letter I picked for the fourth byte to represent radius. Due to only having one byte to represent radius, I opted to make it so whatever you have for radius in the 4th byte gets multiplied by 10 for a bigger range. If you have `0x64` (100) then your light will have a radius of 1000. The default intensity is 2.

The point light object has some special exclusive behavior made possible from it being tied to the object system instead of a separate list. If you give it a parent object, the light will copy its position to the parent and delete itself when the parent is deleted. Other than that, changing the position of the light object will change the actual light's position but you are able to modify the other properties without it being forced by the object.

Initially, I made it so it always copied the color and radius to match behavior parameters but I figured it would be easier if you could just edit the properties directly without having to go through tedious behavior parameter bit shifting and whatnot.

You can also make your own light behavior and call `bhv_point_light_init()` and or `bhv_point_light_loop()` if you just want to add onto the behavior for your version.

## Section 6: Light Functions

| Function | Description |
| -------- | ----------- |
| `le_is_enabled()` | Gets whether the lighting engine has been enabled or not. It becomes enabled once a light is added or the ambient color is set |
| `le_calculate_lighting_color(pos, out, lightIntensityScalar)` | In case you wanted to calculate lighting color in Lua for whatever reason. Calculates the lighting with `lightIntensityScalar` at a position and outputs the color in `out` |
| `le_calculate_lighting_color_with_normal(pos, normal, out, lightIntensityScalar)` | Calculates the lighting with `lightIntensityScalar` at a position and with a normal and outputs the color in `out` |
| `le_calculate_lighting_dir(pos, out)` | An additional function not used by the lighting engine. Calculates the lighting direction from a position and outputs the result in `out` |
| `le_remove_light()` | Removes a lighting engine point light corresponding to `id` |
| `le_get_light_count()` | Gets the total number of lights currently loaded in the lighting engine |
| `le_light_exists()` | Checks if a lighting engine point light corresponding to `id` exists |
| `le_get_ambient_color(out)` | Outputs the lighting engine's ambient color to `out` |
| `le_get_light_pos(id, out)` | Outputs a lighting engine point light's position to `out` |
| `le_set_light_pos(id, x, y, z)` | Sets a lighting engine point light's position to `x`, `y`, `z` |
| `le_get_light_color(id, out)` | Outputs a lighting engine point light's color to `out` |
| `le_set_light_color(id, r, g, b)` | Sets a lighting engine point light's color to `r`, `g`, `b` |
| `le_get_light_radius(id)` | Gets a lighting engine point light's `radius` |
| `le_set_light_radius(id, radius)` | Sets a lighting engine point light's `radius` |
| `le_get_light_intensity(id)` | Gets a lighting engine point light's `intensity` |
| `le_set_light_intensity(id, intensity)` | Sets a lighting engine point light's `intensity` |
| `le_get_light_use_surface_normals(id)` | Gets whether a lighting engine point light will use a surface's normals to determine its brightness with `useSurfaceNormals` |
| `le_set_light_use_surface_normals(id, useSurfaceNormals)` | Sets whether a lighting engine point light will use a surface's normals to determine its brightness with `useSurfaceNormals` |