
-------------------
-- replace stars --
-------------------

starPositions = gLevelValues.starPositions

vec3f_set(starPositions.KoopaBobStarPos,       1174.0,     0.0,  4091.0)
vec3f_set(starPositions.KoopaThiStarPos,       1107.0,   189.0, -4781.0)
vec3f_set(starPositions.EyerockStarPos,           0.0,  -900.0, -3700.0)
vec3f_set(starPositions.BigBullyStarPos,       3700.0,   600.0, -5500.0)
vec3f_set(starPositions.ChillBullyStarPos,      130.0,  1600.0, -4335.0)
vec3f_set(starPositions.BigPiranhasStarPos,   -6300.0, -1850.0, -6300.0)
vec3f_set(starPositions.TuxieMotherStarPos,    3167.0, -4300.0,  5108.0)
vec3f_set(starPositions.WigglerStarPos,           0.0,  2048.0,     0.0)
vec3f_set(starPositions.PssSlideStarPos,      -6358.0, -4300.0,  4700.0)
vec3f_set(starPositions.RacingPenguinStarPos, -7339.0, -5700.0, -6774.0)
vec3f_set(starPositions.TreasureJrbStarPos,    1800.0,  2500.0,  1700.0)
vec3f_set(starPositions.TreasureChestStarPos, -1900.0, -4000.0, -1400.0)
vec3f_set(starPositions.GhostHuntBooStarPos,    980.0,  1100.0,   250.0)
vec3f_set(starPositions.KleptoStarPos,        -5550.0,   300.0,  -930.0)
vec3f_set(starPositions.MerryGoRoundStarPos,  -1600.0, -2100.0,   205.0)
vec3f_set(starPositions.MrIStarPos,            1370.0,  2000.0,  -320.0)
vec3f_set(starPositions.BigBullyTrioStarPos,   5226.0,  -104.0, -4841.0)
vec3f_set(starPositions.MantaRayStarPos,      -3180.0, -3600.0,   120.0)
vec3f_set(starPositions.SnowmanHeadStarPos,   -4700.0, -1024.0,  1890.0)
vec3f_set(starPositions.CcmSlideStarPos,       2500.0, -4350.0,  5750.0)
vec3f_set(starPositions.UkikiCageStarPos,      2500.0, -1200.0,  1300.0)
vec3f_set(starPositions.UnagiStarPos,          6833.0, -3654.0,  2230.0)
vec3f_set(starPositions.JetstreamRingStarPos,  3400.0, -3200.0,  -500.0)

function star_areas_replace()
    local areaIndex = gNetworkPlayers[0].currAreaIndex
    if areaIndex == 1 then
        vec3f_set(starPositions.BalconyBooStarPos,   139.0,  2986.0,  -622.0)
        vec3f_set(starPositions.KingBobombStarPos,  4423.0,   150.0,  5607.0)
        vec3f_set(starPositions.KingWhompStarPos,   -313.0,   150.0, -4525.0)
    else
        vec3f_set(starPositions.BalconyBooStarPos,  1352.0,   636.0, -4037.0)
        vec3f_set(starPositions.KingBobombStarPos, -4635.0,   750.0,  5108.0)
        vec3f_set(starPositions.KingWhompStarPos,    427.0,   850.0, -4499.0)
    end
end
