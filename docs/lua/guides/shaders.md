# Shaders

## Resources

- [Default C Shader in Lua](../examples/shader-demo/default-shader.lua)
- [Example Vertex Shader](../examples/shader-demo/mirror-shader.lua)
- [Example Fragment Shader](../examples/shader-demo/invert-color-shader.lua)

## Before Starting...

You should have some basic knowledge on how writing mods in Lua works, and for more advanced shaders you should know how to work with shaders, specifically GLSL 410 or even GLSL 330. But even if you are a beginner, you may find use in this guide.

When testing shaders, it is recommended to launch your game with the terminal. While technically the game will fallback on default shaders if a shader fails to compile, there are multiple cases that are common enough to where you will appreciate running the game via a terminal since the console will be unavailable/invisible.

## Types of Shaders

There are two types of shaders, post process shaders and "scene" shaders. Post process shaders are significantly easier than scene shaders, but scene shaders give you significantly more power since they run on each triangle rendered in the scene. We will mainly be going over post process shaders in this guide.

The [default C scene shader converted to Lua can be found here](../examples/shader-demo/default-shader.lua). It does all of the boilerplate for you.
The [default C post process shader converted to Lua can be found here](../examples/shader-demo/default-post-process-shader.lua)

## Creating Shaders

Scene shaders can be created via the `HOOK_ON_VERTEX_SHADER_CREATE` and `HOOK_ON_FRAGMENT_SHADER_CREATE` hooks. These hooks provides a [ColorCombiner](../structs.md#ColorCombiner), and the hooks expects you to return a shader back.

Post process shaders can be created via the `HOOK_ON_POST_PROCESS_VERTEX_SHADER_CREATE` and `HOOK_ON_POST_PROCESS_FRAGMENT_SHADER_CREATE` hooks. These hooks provide no parameters, and expect you to return a shader back.

The vertex shader allows for manipulating vertex data, whereas the fragment shader allows for manipulating color data. You do not have to provide both, but if you only use one, you are expected to send/receive data back as expected by their respective default shaders.

## Shader Language

Coop uses GLSL 410 core, or GLSL 4.1 core, or `#version 410 core`. It uses a custom system that does a lot of work for you to ensure shaders work on DirectX, Metal, and any other render apis that get added in the future. The custom system automatically assigns input locations, uniform buffers, uniform bindings, and other backend-specific details so that the same GLSL works across OpenGL, DirectX 11, and Metal. Because of this, you should avoid manually specifying input/uniform/sampler locations or uniform blocks.

As a list, things **not** to do are:

- Define explicit locations
- Define custom uniform blocks

And as a list of things to **always** do:

- Define every input passed from C to the vertex shader (see [inputs](#inputs))
- For every output in the vertex shader must be a corresponding input in the fragment shader. They must have matching names

Failure in any of the above will result in either a failed to sanitize shader error or a failed to compile shader to SPIR-V cross error.

## Vertex Shaders

The bread and butter of vertex shaders are inputs. Inputs are given by the game's code and can be used for getting the vertex data. A list of inputs for shaders can be found [here](#Inputs). Something important about inputs is that a fragment shader cannot get inputs from C, so you need to pass inputs from the vertex shader as outputs for the fragment shader. An example of that would be the vertex position.

```lua
in vec4 aVtxPos;
out vec4 vVtxPos;
vVtxPos = aVtxPos;
```

The input `aVtxPos` is provided by C, and the output is created, which will be received in the fragment shader.

```lua
in vec4 vVtxPos;
```

The fragment shader takes in the vertex pos we exported in the vertex shader.

For a post process vertex shader example, we are going to mirror the entire world. First, grab the [default C post process shader converted to Lua](../examples/shader-demo/default-post-process-shader.lua), specifically the vertex portion.

*Note: While the format shown in the default shaders use `table.insert(xShader, "line")`, this is not at all required. You may use any method you'd like. This method was picked for it's ease to inject any if statement checks anywhere you'd like that's outside the shader.*

```lua
gl_Position = aVtxPos;
```

This sets the vertex position to be passed to the GPU to our vertex position provided by C. There are 4 main components to this position:

- `x` being the X coordinate
- `y` being the Y coordinate
- `z` being the Z coordinate
- `w` being the depth coordinate

This position in clip space, which means that it is already ready to be inserted into the GPU which is why we send it with no modifications. Go [here](#coordinate-spaces) for a more detailed explanation on coordinate spaces.

To get our mirror effect, we need to flip the `x` coordinate. So we need to create a vector 4 that flips our `x` component, and passes back our `y`, `z`, and `w` components as-is. This can be done via this syntax:

```lua
gl_Position = vec4(aVtxPos.x * -1.0, aVtxPos.yzw);
```

If you run the mod, you should now have a mirrored game! That's the basic rundown on vertex shaders! If something still isn't working, compare your code with [the example vertex shader](../examples/shader-demo/mirror-shader.lua) and try to figure out what you did wrong.

<img width="640" height="416" alt="Screenshot 2026-04-24 at 7 09 03 PM" src="https://github.com/user-attachments/assets/4218e701-1a71-4420-bf0f-fd8fff8baf81" />

*Note: Alternatively, to accomplish the same effect, you can flip the texture coordinate in the fragment shader.*

## Fragment Shaders

First, grab the [default C post process shader converted to Lua](../examples/shader-demo/default-post-process-shader.lua), specifically the fragment shader portion.

For our example fragment shader, we are going to be inverting the colors. Actually doing this is quite simple, but before we get to that, let's explain what we are working with:

First, unlike the vertex shader, you have to define the output manually in a fragment shader.

```lua
out vec4 fragColor;
```

In the fragment shader, we create an output for the fragment color. Unlike the vertex shader, an output does not go to another shader, instead, it goes to the GPU to be used as the color for the pixel.

All the outputs in the vertex shader can be read in the fragment shader as inputs. This allows data to be carried over from one to the other. What was `out` in the vertex shader becomes `in` in the fragment shader.

For our example, inverting the colors, it's quite simple.

```lua
fragColor = texture(uPassTex, vTexCoord);
```

Currently, this is what the frag color is set to. Instead of setting `fragColor` directly, we should first take the color outputted by the `texture` function and insert it into it's own variable.

```lua
vec4 texColor = texture(uPassTex, vTexCoord);
```

Then, inverting that color becomes trivial. When we set `fragColor`, all we need to do is invert `texColor.rgb` and preserve `texColor.a`. This can be done with the following syntax:

```lua
fragColor = vec4(1.0 - texColor.rgb, texColor.a);
```

And that's it! All colors in your game should now be completely inverted! That's the basic rundown on fragment shaders! If something still isn't working, compare your code with [the example fragment shader](../examples/shader-demo/invert-color-shader.lua) and try to figure out what you did wrong.

<img width="640" height="416" alt="Screenshot 2026-04-24 at 7 07 43 PM" src="https://github.com/user-attachments/assets/1b25a55d-082a-447d-8c75-a33ef143f2e2" />

## Uniforms

A shader may contain uniforms. As per the GLSL naming convention, uniform variables typically start with a `u`, for instance, `uFrameCount`. There are multiple different uniforms already updated by C, but you can also update custom uniforms in Lua. First, here is a list of all the uniforms updated in C. You can override these uniforms and shove in your own data, but beware, behavior is undefined.

| Uniform Name | Type | Description |
| ------------ | ---- | ----------- |
| `uTex0` | `sampler2D` | The primary texture |
| `uTex1` | `sampler2D` | The secondary texture |
| `uPassTex` | `sampler2D` | The rendered output texture produced by the previous frame pass |
| `uPassTexX` | `sampler2D` | The rendered output texture from frame pass X, where X is the pass index. |
| `uTex0Size` | `vec2` | The width and height of the primary texture |
| `uTex1Size` | `vec2` | The width and height of the secondary texture |
| `uTex0Filter` | `bool` | `true` if the primary texture uses linear filtering |
| `uTex1Filter` | `bool` | `true` if the secondary texture uses linear filtering |
| `uFilter` | `int` | The current global filtering mode (`0` = Point, `1` = Linear, `2` = Three-point) |
| `uFrameCount` | `uint` | The current frame we are on since the lifetime of the program, acts as a timer |
| `uLightmapColor` | `vec3` | RGB multiplier applied to the environment/light map |
| `uAspectRatio` | `float` | The current viewport aspect ratio (`width`/`height`) |
| `uXAdjustRatio` | `float` | The horizontal clip-space scaling factor used for widescreen rendering |
| `uScreenWidth` | `float` | The width of the screen in pixels |
| `uScreenHeight` | `float` | The height of the screen in pixels |
| `uModelViewProjectionMatrix` | `mat4` | Transforms local space directly to clip space |
| `uModelViewMatrix` | `mat4` | Transforms local space to view space |
| `uModelMatrix` | `mat4` | Transforms local space to world space |
| `uViewMatrix` | `mat4` | Transforms world space to view space |
| `uProjectionMatrix` | `mat4` | Transforms view space to clip space |
| `uShaderFlags` | `int[]` | Array of shader feature flags provided by the engine |
| `uShaderFlagValues` | `float[]` | Array of values associated with `uShaderFlags` |
| `uFogMul` | `float` | The multiplier for fog |
| `uFogIntensity` | `float` | The intensity of fog |
| `uFogOffset` | `float` | The offset of fog |
| `uFogColor` | `vec3` | The color of the fog |
| `uDepthZSub` | `float` | Value from CPU for calculating fog check |
| `uDepthZMult` | `float` | Value from CPU for calculating fog check |
| `uDepthZAdd` | `float` | Value from CPU for calculating fog check |
| `uFogEnabled` | `float` | Whether or not fog is currently enabled |

For defining a custom uniform in lua, use the `HOOK_ON_SET_SHADER_PROGRAM`, hook and use the appropriate `gfx_shader_set_*` function. If you need to set a uniform every triangle draw, do note there is a lot of performance overhead, but if it is necessary, use `HOOK_ON_DRAW_TRIANGLE`.

You can also define uniform buffers with no explicit locations, such as:

```lua
uniform LightData {
    vec3 uLightPositions[64];
    vec3 uLightColor[64];
    int uLightCount;
};
```

These allow you to pass more data. To utilize this, set the current uniform block to your custom one, and set the data accordingly:

```lua
function on_set_shader_program() {
    gfx_shader_set_uniform_buffer("LightData")
    gfx_shader_set_vec3_array("uLightPositions", lightPositions)
    gfx_shader_set_vec3_array("uLightColor", lightColors)
    gfx_shader_set_int("uLightCount", #lightPositions)
}
```

If your light data in the vertex shader does not match the light shader in the fragment shader, you can explicitly set uniforms for a specific shader using `gfx_shader_set_shader_stage`.

```lua
local sceneBrightness = 0.5

local function on_set_shader_uniforms()
    -- if necessary, check frame pass index using this code
    -- local framePass = gfx_shader_get_current_frame_pass_index()
    -- if framePass ~= FRAME_PASS_REQ then return end

    gfx_shader_set_float("uSceneBrightness", sceneBrightness)
end

hook_event(HOOK_ON_SET_SHADER_PROGRAM, on_set_shader_uniforms)
```

That allows you to define your own uniforms and set your uniforms in Lua!

## Inputs

Inputs are passed into the vertex shader for further use. Here is a list of inputs provided by C.

### Scene Shader Inputs

| Input Name     | Type   | Description |
| -------------- | ------ | ----------- |
| `aVtxPos`      | `vec4` | The vertex position in clip space |
| `aLocalSpace`  | `vec4` | The vertex position in local space. This is where you should use matrices to transform the space you are currently in. For more info on coordinate spaces, go [here](#coordinate-spaces) |
| `aTexCoord0`   | `vec2` | UV coordinates for the primary texture |
| `aTexCoord1`   | `vec2` | UV coordinates for the secondary texture |
| `aLightMap`    | `vec2` | UV coordinates for the light map |
| `aInputX`      | `vec4` | Color/alpha input from the Color Combiner, with X being the input number. There are 8 color combiner inputs, or `CC_MAX_INPUTS`. |
| `aNormal`      | `vec3` | The surface normal |
| `aBarycentric` | `vec3` | The barycentric coordinates of the vertex within its triangle |

### Post Process Shader Inputs

| Input Name | Type | Description |
| ---- | ---- | ---- |
| `aVtxPos` | `vec4` | The vertex position in clip space (x, y, z, w) |
| `aTexCoord` | `vec2` | The UV mapping for the pass texture |

## Dealing with the HUD

First of all, you can't filter out the HUD in a post process shader, you need to use a scene shader in order to do that. Secondly, the best option is to use the world geometry flag provided by the [ColorCombiner](../structs.md#ColorCombiner)

```lua
local worldGeometry = cc.cm.flags & CM_FLAG_WORLD_GEOMETRY ~= 0
```

If it is world geometry, it's not the hud, if it's not world geometry, it is the hud. This is the best solution by far. Other solutions exist, such as checking the depth of the Z coord in the clip pos, but they are a lot more convoluted and less efficent.

## Multipass Shaders

Multipass shaders allow you to draw the world multiple times in a single frame. It's where custom scene shaders can do the most work. Whether you're creating a minimap, adding lighting, wanting multiple cameras, and more, you'll want to use multipass shaders.

## Creating a frame pass

A frame pass can be created with `gfx_shader_create_frame_pass`. This function returns the frame pass index, and the frame pass itself. The frame pass index is anywhere from zero to `MAX_FRAME_PASSES`. A frame pass may also be removed with `gfx_shader_remove_frame_pass`, which takes in the frame pass index.

Frame passes can be configured by modifying the `FramePass` provided by `gfx_shader_create_frame_pass`.

## Using frame passes

In your shader hooks, you can access which frame pass you are currently on with the `gfx_shader_get_current_frame_pass` and `gfx_shader_get_current_frame_pass_index`. For unique identification, which is the main reason you would get the current frame pass, you should use `gfx_shader_get_current_frame_pass_index`. This is needed if you need to change your shader depending on the current frame pass.

Sometimes you may need to configure things before you redraw the world. For instance, on some shaders you may want to disable culling before you redraw the world. You can use `HOOK_BEFORE_DRAW_GEOMETRY` to achieve this. Check your current frame pass index using `gfx_shader_get_current_frame_pass`, and run code accordingly in this hook. This hook isn't unique to frame passes, it's called anytime the world geometry is about to be drawn.

## Coordinate Spaces

The vertex position (`aVtxPos`) provided by C is in clip space stretched for widescreen support, which isn't really suitable for matrix transformations, so instead use `aLocalSpace`, which is in local space, also known as object space, or model space. As shown in the [uniforms](#Uniforms) section, many matrices are provided by C to transform `aLocalSpace` to other spaces. There are enough matrices to get to nearly any space you need. Each uniform explains what it transforms to, but here are some examples of the most common ones:

**Getting to world space from local space:**

```lua
vec4 worldPos = uModelMatrix * localPos;
```

**Getting to view space from world space:**

```lua
vec4 viewPos = uViewMatrix * worldPos;
```

**Getting to clip space from view space:**

```lua
vec4 clipPos = uProjectionMatrix * worldPos;
```

A sweet visualtion of these matrices can be found [here](https://bitly.com/98K8eH)

To reiterate, `aVtxPos` is in clip space, but it also has adjustments made to it to ensure that it has widescreen adjustments, and accounts for MSAA in the HUD properly. So it's not *pure* clip space. If you were to get to clip space using the `uModelViewProjectionMatrix` on `aLocalPos`, it would be different from `aVtxPos`. Uniforms such as `uXAdjustRatio` exist to help with that if necessary.

Some devices are stuck on legacy renderers. That means that the NDC Z range is from -1 to 1 when normally it is from 0 to 1. Lua can detect and modify shaders accordingly with `gfx_is_legacy_renderer`. This is an unfortunate limitation that can't really be fixed unless we stop supporting a bunch of devices. This may change in the future, but for now this is the case.

## A Note on GLSL Extensions

Avoid them. Unless you know what you are doing and know the list of devices supported, don't bother. That's all :D
