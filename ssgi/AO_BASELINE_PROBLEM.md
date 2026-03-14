# AO Baseline Brightness Problem

## The Issue

In the AO-only shader (`gfx_ssgi.c`, embedded `ao_frag_src`), flat unoccluded surfaces produce AO values significantly below 1.0, causing the entire scene to be uniformly darkened even where there is no occlusion. The AO output is used as a multiplier: `scene.rgb * ao`, so ao=1.0 means no darkening and ao=0.0 means fully dark.

## Current Shader Logic

The AO computation works per-pixel:

1. For each of `SLICE_COUNT` (2) slices through the hemisphere:
   - Compute a slice direction in screen space
   - Project the surface normal onto the slice plane → get angle `n`
   - Sample the horizon in both directions (left/right) along the slice

2. `horizonAO()` function samples `STEP_COUNT` (6) depth samples along one direction:
   - For each sample, read depth, reconstruct view-space position
   - Compute `horizonCos = dot(normalize(samplePos - currentPos), viewDir)`
   - Track `maxHorizonCos` (initialized to -1.0)
   - Thickness rejection: `fade = 1.0 - clamp(len/thickness, 0, 1)`, `hc = mix(-1.0, hc, fade)`
   - Returns: `clamp((horizonAngle - nAngle) / PI, 0.0, 1.0)` where `horizonAngle = acos(maxHorizonCos)`

3. The two sides per slice are averaged, then raised to `uAoIntensity` power.

## The Math Problem

For a flat floor with the camera looking at an angle:
- The surface normal projects onto the slice with angle `n ≈ 0`
- In the "right" direction, samples hit the floor plane extending away. The horizon stays near the surface level, giving `maxHorizonCos ≈ 0`, so `horizonAngle ≈ PI/2`
- Result: `(PI/2 - 0) / PI = 0.5`

Both sides return ~0.5, averaged = 0.5. The scene is at 50% brightness.

This is because `(horizonAngle) / PI` maps the range [0, PI] to [0, 1], but the physically meaningful range for occlusion is [0, PI/2]:
- `horizonAngle = 0`: horizon at the camera direction → fully occluded
- `horizonAngle = PI/2`: horizon at the tangent plane → unoccluded (the ground plane itself is not "occlusion")
- `horizonAngle > PI/2`: horizon behind the surface → still unoccluded

## Attempted Fixes

### Fix 1: `ao * 2.0` remap
```glsl
ao = clamp(ao * 2.0, 0.0, 1.0);
```
Maps 0.5 → 1.0. Works visually but clips the upper half of the dynamic range (values between 0.5 and 1.0 all become 1.0).

### Fix 2: Divide by HALF_PI instead of PI
```glsl
float ha = min(acos(clamp(mhc, -1.0, 1.0)), HALF_PI);
return clamp((ha - na) / HALF_PI, 0.0, 1.0);
```
Clamps horizon to [0, PI/2] and normalizes by PI/2. This gives 1.0 for unoccluded flat surfaces. But testing shows this doesn't look right either — the AO distribution changes in unexpected ways.

### Fix 3: GTAO cosine-weighted formula
```glsl
ao += 0.25 * (-cos(2.0*h - n) + cos(n) + 2.0*h*sin(n));
```
Where h is the horizon angle per side, n is the projected normal angle. This is the proper GTAO paper formula. But it produced inverted results because the horizon angles from our `horizonAO` function use a different convention (0=occluded, PI=unoccluded) than what GTAO expects (0=occluded, PI/2=unoccluded).

## What I Need

A correct formulation that:
1. Produces ao≈1.0 for flat unoccluded surfaces (no uniform darkening)
2. Produces ao<1.0 only in actual concavities, corners, and contact shadows
3. Preserves the full [0, 1] dynamic range without clamping hacks
4. Works with the existing `horizonAO` function's convention where `maxHorizonCos` starts at -1 and gets pushed toward +1 by occluders

## Relevant Code Context

The `horizonAO` function signature and return value:
```glsl
float horizonAO(float samplingDir, vec2 uvDir, float RADIUS, vec3 viewPosition,
                vec2 slideDirTexelSize, float initialRayStep, vec2 uvCoord,
                vec3 viewDir, float n)
```

Called as:
```glsl
// Right side of slice
ao += horizonAO(1.0, vec2(1.0,1.0), uRadius, vp, sdt, irs, vUv, vd, n);
// Left side of slice
ao += horizonAO(-1.0, vec2(-1.0,-1.0), uRadius, vp, sdt, irs, vUv, vd, n);
```

The `n` parameter is the projected normal angle within the slice:
```glsl
vec3 planeNormal = normalize(cross(sliceDir, viewDir));
vec3 tangent = cross(viewDir, planeNormal);
vec3 projectedNormal = viewNormal - planeNormal * dot(viewNormal, planeNormal);
vec3 projectedNormalNorm = normalize(projectedNormal);
float cos_n = clamp(dot(projectedNormalNorm, viewDir), -1.0, 1.0);
float n = -sign(dot(projectedNormal, tangent)) * acos(cos_n);
```

## Files
- Embedded AO shader: `src/pc/gfx/gfx_ssgi.c` (search for `ao_frag_src`)
- Original reference shader: `ssgi/ssgi_ao_only_120.frag`
- Integration notes: `ssgi/INTEGRATION_NOTES.md` and `ssgi/INTEGRATION_RESPONSE.md`
