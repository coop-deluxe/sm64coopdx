--- @type integer
FONT_TINY = -1

--- @type integer
ANIM_FLAG_FORWARD = (1 << 1)


--------------------
-- Math functions --
--------------------
--- Note: These functions were originally in smlua_math_utils.h,
--- but performed worse (~2x slower) than built-in Lua math functions

min = math.min
minf = math.min
max = math.max
maxf = math.max
sqr = math.sqr
sqrf = math.sqr
clamp = math.clamp
clampf = math.clamp
hypotf = math.hypot