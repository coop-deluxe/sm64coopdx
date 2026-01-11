-- Environment inclusions --
--[[
    We only need to include character select rn
]]

charSelect = charSelect

if not charSelect then return end
_ENV = setmetatable(_G, { __index = charSelect })

