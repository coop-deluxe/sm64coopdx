# Shaders

## Resources

- [Default C Shader in Lua](../examples/shader-demo/default-shader.lua)
- [Example Vertex Shader](../examples/shader-demo/mirror-shader.lua)
- [Example Fragment Shader](../examples/shader-demo/invert-color-shader.lua)

## Before Starting...

While this guide does go into a lot of detail, you should still have some basic knowledge on how writing mods in Lua works, and a bit of knowledge on how shaders work will also go a very long way.

When testing shaders, it is recommended to launch your game with the terminal. While technically the game will fallback on default shaders if a shader fails to compile, there are multiple cases that are common enough to where you will appreciate running the game via a terminal since the console will be unavailable/invisible.

## Creating Shaders

Shaders can be created via the `HOOK_ON_VERTEX_SHADER_CREATE` and `HOOK_ON_FRAGMENT_SHADER_CREATE` hooks. These hooks provides a [ColorCombiner](../structs.md#ColorCombiner) and shader index, and expects you to return a vertex shader back. The vertex shader allows for manipulating vertex data, whereas the fragment shader allows for manipulating color data. You do not have to provide both, but if you only use one, you are expected to send/receive the proper data back.

## Vertex Shaders

The bread and butter of vertex shaders are inputs. Inputs are given by the game's code and can be used for getting the vertex data. A list of inputs can be found [here](#Inputs). Something important about inputs is that a fragment shader cannot get inputs from C, so you need to pass inputs from the vertex shader as outputs for the fragment shader. An example of that would be the texture coords.

```lua
in vec2 aTexCoord;
out vec2 vTexCoord;
vTexCoord = aTexCoord;
```

As you can see, the input is gotten in the vertex shader, and the output is created, which will be received in the fragment shader.

```lua
in vec2 vTexCoord;
```

Here, the fragment shader takes the tex coord output we created in the vertex shader.

Getting back on track, for our vertex shader example, we are going to mirror the entire world. First, grab the [default C shader in Lua](../examples/shader-demo/default-shader.lua), specifically the vertex portion. Most of this shader will be passing inputs to the fragment shader, but what we care about is this portion:

```lua
gl_Position = aVtxPos;
```

This sets the vertex position in opengl to our vertex position provided by C. There are 4 main components to this position:

- `x` being the X coordinate
- `y` being the Y coordinate
- `z` being the Z coordinate
- `w` being the depth coordinate

Importantly, this position is not in world space, it is instead in clip space, but that does not matter for our example.

To get our mirror effect, we need to flip the `x` coordinate. So we need to create a vector 4 that flips our `x` component, and passes back our `y`, `z`, and `w` components as-is. This can be done via this syntax:

```lua
gl_Position = vec4(aVtxPos.x * -1.0, aVtxPos.yzw);
```

If you run the mod, you should now have a mirrored game! That's the basic rundown on vertex shaders! If something still isn't working, compare your code with [the example vertex shader](../examples/shader-demo/mirror-shader.lua) and try to figure out what you did wrong.

## Fragment Shaders

Fragment shaders are quite a bit more involved, but I'll try to keep it simple. First, grab the [default C shader in Lua](../examples/shader-demo/default-shader.lua), specifically the fragment shader portion, as well as the `shader_item_to_str` and `append_formula` functions. While we won't be explaining what those do right now, to summarize, they are there to handle the color combiner.

For our example fragment shader, we are going to be inverting the colors. Actually doing this is quite simple, but before we get to that, let's explain what we are working with:

First, unlike the vertex shader, you have to define the output manually in a fragment shader.

```lua
out vec4 fragColor;
```

In the fragment shader, we create an output for the fragment color. Unlike the vertex shader, an output does not go to another shader, instead, it goes to OpenGL to be used for color data.

All the outputs in the vertex shader can be read in the fragment shader as inputs. This allows data to be carried over from one to the other.

For our example, inverting the colors, we only have to look at 2 lines. One for if the color combiner specifies an alpha, and the other if it does not. If we do have an alpha, we want to preserve it when inverting the color. Colors in OpenGL, unlike the rest of sm64, are stored in between `0.0` and `1.0`. That means if I want to represent half of red, I would need to use `0.5` instead of `128`. For inverting a color this is simple. Combining these things, we need to subtract a full color, or `1.0`, by the rgb of `texel`, then pass in the alpha value as normal.

```lua
fragColor = vec4(1.0 - texel.rgb, texel.a);
```

If the color combiner does not have an alpha value, then the alpha should simply be `1.0`, or fully opaque.

```lua
fragColor = vec4(1.0 - texel.rgb, 1.0);
```

And that's it! All colors in your game should now be completely inverted! That's the basic rundown on fragment shaders! If something still isn't working, compare your code with [the example fragment shader](../examples/shader-demo/invert-color-shader.lua) and try to figure out what you did wrong.

## Uniforms

A shader may contain uniforms. As a naming convention, uniform variables typically start with a `u`, for instance, `uFrameCount`. There are multiple different uniforms already updated by C, but you can also update custom uniforms in Lua. First, here is a list of all the uniforms updated in C.

| Uniform Name | Type | Description |
| ---- | ---- | ---- |
| `uTex0` | `sampler2D` | The primary texture |
| `uTex1` | `sampler2D` | The secondary texture |
| `uTex0Size` | `vec2` | The width and height of the primary texture |
| `uTex1Size` | `vec2` | The width and height of the secondary texture |
| `uTex0Filter` | `bool` | True if the first texture is using linear filtering |
| `uTex1Filter` | `bool` | True if the second texture is using linear filtering |
| `uFilter` | `int` | The current global filtering mode (0 = Point, 1 = Linear, 2 = Three-point) |
| `uFrameCount` | `float` | A timer that increases every frame |
| `uLightmapColor` | `vec3` | The RGB color multiplier applied to the environment/lightmap |
| `uModelViewMatrix` | `mat4` | Transforms objects from world space to view space |
| `uProjectionMatrix` | `mat4` | Transforms view space to clip space |
| `uInverseViewMatrix` | `mat4` | The inverse of the view matrix |

For defining a custom uniform in lua, first, define the uniform and use the uniform as you intend in your shader code. Next you're going to want to store the shader index given by the hook. Create a table and store all your shader indexes. Then in lua, in any hook as seen fit, iterate through the list of shader indexes. Now, create a variable and set it to the returned value of `gfx_get_program_id_from_shader_index`. First, use that program with `gfx_use_program`, then get the uniform with `gfx_shader_get_uniform_location`. You should then set it with the appropriate `gfx_shader_set_` function. Here is an example:

```lua
local fogColor = { r = 168, g = 175, b = 195 }
-- iterate through the shader indexes
for _, index in pairs(sShaderIndexes) do
    -- get the program from the shader index
    local program = gfx_get_program_id_from_shader_index(index)
    -- use the program so we can set the uniforms
    gfx_use_program(program)

    -- get the uniform, which is a color of type vec4
    local uFogColor = gfx_shader_get_uniform_location(program, "uFogColor")
    -- set the vector 4 at that uniform location
    gfx_shader_set_vec4(uFogColor, fogColor.r / 255, fogColor.g / 255, fogColor.b / 255, 1.0)

    local uFogIntensity = gfx_shader_get_uniform_location(program, "uFogIntensity")
    gfx_shader_set_float(uFogIntensity, 5000.0)
end
```

That allows you to define your own uniforms and set your uniforms in Lua!

Lastly, if you have multiple shaders, you should cleanup the list of shader indexes on a shader refresh. Use the `HOOK_ON_REFRESH_SHADERS` hook to reset the shader indexes table, or do anything you need to when it comes to refreshing shaders.

```lua
hook_event(HOOK_ON_REFRESH_SHADERS, function ()
    sShaderIndexes = {}
end)
```

## Inputs

Inputs are passed into the vertex shader for further use. Here is a list of inputs provided by C.

| Input Name | Type | Description |
| ---- | ---- | ---- |
| `aVtxPos` | `vec4` | The vertex position (x, y, z, w) |
| `aTexCoord` | `vec2` | The standard UV mapping for the primary texture |
| `aNormal` | `vec3` | The direction the surface is facing |
| `aFog` | `vec4` | Fog data provided by C |
| `aLightMap` | `vec2` | UV coordinates for a light map |
| `aInputX` | `vec4` | Color/alpha input from the Color Combiner, with X being the input number |
| `aBarycentric` | `vec3` | The barycentric coordinates of the vertex within its triangle |

## Dealing with the HUD and Skybox

If you want to hide the HUD, you can by checking the vertex position. If the vertex position's z is greater than zero, it is not a hud element. By default the vertex position is not included in the fragment shader, so you may need to create a varying variable and send it over.

To check for the skybox, the skybox lives somewhere in between layer 0 and layer 2. You should do a range check to find it, for instance, `aVtxPos.z > 0 && aVtxPos.z < 2`.

Currently where the hud lives below 0 is a bit random, so right now it's best to either hide it all or none of it.

## Limitations

- No more than a single shader can be used at a time. This means that if 2 mods want to use their own shader, only one will be picked.
- Currently you can only do one shader pass. While for most cases a single shader pass works fine, for many types of shaders it is very limiting. This is a unfortunate limitation with the current system.
- There are only so many inputs. While I made sure to include as many as possible, there may still be some missing for your own shaders.
- DirectX and OpenGL Legacy support is non-existent.

While these limitations may improve in the future, this is where we are stuck for right now.