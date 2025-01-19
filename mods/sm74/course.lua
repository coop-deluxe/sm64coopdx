sCourseNamesEE = false

local function course_names_swap_sm74()
    if not sCourseNamesEE then return end
    smlua_text_utils_course_acts_replace(COURSE_BOB, " 1 DICE-FORTRESS", "WALLJUMPING LESSON", "CONQUER THE PILLARS", "THE OBSERVATION TOWER", "COLLECT 8 RED COINS", "SECRETS OF THE SKY", "THE BOX'S TREASURE")
    smlua_text_utils_course_acts_replace(COURSE_WF,  " 2 SKYWARD SLOPES", "TO THE TOP OF THE TOWER", "8 DANGEROUS RED COINS", "THE OUTER WALL", "NO TIME TO WASTE", "FLOATATION TECHNOLOGY BOX", "MASTER OF JUMPING")
    smlua_text_utils_course_acts_replace(COURSE_JRB, " 3 AZURE-ABYSS", "THE DEEPEST DIVE", "CAVE EXPLORATION", "PRECISION PILLARS", "RED TREASURE HUNT", "HEAVY METAL REQUIRED", "WALL OF FAILURE?")
    smlua_text_utils_course_acts_replace(COURSE_CCM, " 4 SYSTEM OF A TOWN", "ROOFTOP CLIMBING", "INTO THE SEWER SYSTEM", "THE SECONDARY HOUSE ENTRANCE", "FIND THE SECRET ROOM", "THE VILLAGE'S RED COINS", "THE MANSION'S SECRET STAR")
    smlua_text_utils_course_acts_replace(COURSE_BBH, " 5 HAUNTED FACTORY", "EXPLORE THE FACTORY", "TOXIC RIDE", "WATCH YOUR STEP", "BLOCKS OF DOOM", "8 SPOOKY RED COINS", "THE HIDDEN ROOM")
    smlua_text_utils_course_acts_replace(COURSE_HMC, " 6 STALAGMITE CAVE", "DOWNWARDS", "BURNING-HOT TUNNEL", "RED COINS IN THE CAVERN", "HOT OBSTACLE COURSE", "CHUCKYA'S CHALLENGE", "CAP-COMBINATION")
    smlua_text_utils_course_acts_replace(COURSE_LLL, " 7 ICE CRYSTAL-TOWER", "REMATCH WITH KING WHOMP", "SCALDING WATERS", "ALMOST TO THE TOP", "FROZEN RED COINS", "HOW HIGH CAN YOU GO?", "DOWN-LOW SECRET STAR")
    smlua_text_utils_course_acts_replace(COURSE_SSL, " 8 OVERHEATING OASIS", "UNDER CONSTRUCTION", "HIDDEN INSIDE THE LABYRINTH", "THE PYRAMIDS OF TUTANPOKEY", "THUNDER MOUNTAIN", "8 HOT RED COINS", "THE PHARAOH'S SANDY SECRET")
    smlua_text_utils_course_acts_replace(COURSE_DDD, " 9 FLOWERY GARDENS", "KING BOB-OMB'S REVENGE", "RED COINS IN THE GARDENS", "VAST WOODEN STRUCTURE", "LUMBERJACK JUMPING", "THE WINDMILL'S STAR", "A HIDDEN CAVE")
    smlua_text_utils_course_acts_replace(COURSE_SL,  "10 SWAMPY SPRING", "KOOPA THE CHEATER", "GROUNDED RED COINS", "THE TOWER OF POWER", "THE OTHER POWER-TOWER", "FEARFUL FAILURE BLOCKS", "A CLIFF'S HIDDEN STAR")
    smlua_text_utils_course_acts_replace(COURSE_WDW, "11 SUNNY BEACH", "MYSTERY OF THE SAPPHIRES", "GOLDEN GLIMMER", "THING WITH SPIKES", "TREASURE HUNT", "SHINY OBJECT", "STARLIGHT")
    smlua_text_utils_course_acts_replace(COURSE_TTM, "12 CLIFF OF WRATH", "KING BOO'S INVASION", "TRICKY PILLARS", "RED COIN QUEST", "WALLJUMPING MADNESS", "PROBLEMATIC BOX", "LOOK OUT")
    smlua_text_utils_course_acts_replace(COURSE_THI, "13 MOLTEN TREASURE CHEST", "HIGH IN THE SKY", "RED COIN FLIGHT", "INSIDE A CAVE", "THE MOUNTAIN PEAKS", "HOT AND SPICY", "ACROBATIC FLYER")
    smlua_text_utils_course_acts_replace(COURSE_TTC, "14 LUMINIUM-SPHERE", "TOWER OF THE WEST", "JUMPING MAESTRO", "BOTTOMLESS FORTRESS", "BEHIND THE WALL", "TREASURE-TOWER", "RED FRUSTRATION")
    smlua_text_utils_course_acts_replace(COURSE_RR,  "15 OMBRU-SPHERE", "THE SAME PLACE AGAIN?", "TINY TOWER", "THE HIGH BUILDING", "INTENSE CHALLENGE", "FLIGHT FOR SIGHT", "MORE RED FRUSTRATION")

    smlua_text_utils_secret_star_replace(COURSE_BITDW,    "   BOWSER'S BADLANDS-BATTLEFIELD")
    smlua_text_utils_secret_star_replace(COURSE_BITFS,    "   BOWSER'S AQUATIC CASTLE")
    smlua_text_utils_secret_star_replace(COURSE_BITS,     "   BOWSER'S CRYSTAL PALACE")
    smlua_text_utils_secret_star_replace(COURSE_PSS,      "   FROZEN SLIDE")
    smlua_text_utils_secret_star_replace(COURSE_COTMC,    "   TOXIC-SWITCH OF DANGER")
    smlua_text_utils_secret_star_replace(COURSE_TOTWC,    "   LAVA-SWITCH OF ERUPTION")
    smlua_text_utils_secret_star_replace(COURSE_VCUTM,    "   DUST-SWITCH OF IDENTITY")
    smlua_text_utils_secret_star_replace(COURSE_WMOTR,    "   TOWER OF THE EAST")
    smlua_text_utils_secret_star_replace(COURSE_SA,       "   CHAMPION'S CHALLENGE")
    smlua_text_utils_secret_star_replace(COURSE_CAKE_END, "")

    smlua_text_utils_castle_secret_stars_replace("   BONUS STARS")
    smlua_text_utils_extra_text_replace(0, "YOU GOT A BONUS STAR!")
    smlua_text_utils_extra_text_replace(1, "")
    smlua_text_utils_extra_text_replace(2, "")
    smlua_text_utils_extra_text_replace(3, "")
    smlua_text_utils_extra_text_replace(4, "")
    smlua_text_utils_extra_text_replace(5, "")
    smlua_text_utils_extra_text_replace(6, "")
end

local function course_names_swap_sm74ee()
    if sCourseNamesEE then return end
    smlua_text_utils_course_acts_replace(COURSE_BOB, " 1 DEVIL'S DICE", "LITTLE WARM-UP", "LET'S-A-GO!", "SCALE THE TOWER", "FUNDAMENTAL TUNNEL PROBLEMS", "FIRST RED KATASTROPHE", "YOU WON'T FIND ME!")
    smlua_text_utils_course_acts_replace(COURSE_WF,  " 2 VIRUSVINE VERANDA", "THE VINE'S TREASURE", "TIME PRESSURE TRAVEL", "ON TOP OF THAT WALL!", "JUMPING-PARCOUR 1", "JUMPING-PARCOUR 2", "LIGHT RED COINS")
    smlua_text_utils_course_acts_replace(COURSE_JRB, " 3 DEEPRED DEPTHS", "THE UPPER END OF THE CRATER", "SMALL PILLAR TRAINING", "HOT STEP STONES", "DEEP WITHIN THE VOLCANO", "ARTISTIC COIN SEARCH", "PAINFUL EXPERIENCE")
    smlua_text_utils_course_acts_replace(COURSE_CCM, " 4 SYSTEM OF A DOWNTOWN", "GHOST ODYSSEE", "GUARDIAN OF THE VILLAGE", "EXPANDED SECRET ROOM", "DEATH PIT", "SO CLOSE AND YET SO FAR AWAY", "HIDDEN COWARD")
    smlua_text_utils_course_acts_replace(COURSE_BBH, " 5 DROWNED FACTORY", "PEARL DIVER", "THE TUNNEL LABYRINTH PART 1", "THE TUNNEL LABYRINTH PART 2", "THE TUNNEL LABYRINTH PART 3", "THE TUNNEL LABYRINTH PART 4", "THE TUNNEL LABYRINTH PART 5")
    smlua_text_utils_course_acts_replace(COURSE_HMC, " 6 INFERNOPIT CAVE", "DEEP WITHIN THE CALDRON", "BALLS OF STEEL AND FIRE", "BLUE CONTRAST BLOCKS", "SIDE CALDRON SHENANIGANS", "DANCE WITH THE HEAVE-HOS", "RED SIN")
    smlua_text_utils_course_acts_replace(COURSE_LLL, " 7 MELTING ICECRYSTAL-TOWER", "BRICK BATTLE", "FLOATATION IN BLOCK FORM", "SOUL OF A CLIMBER", "BLOOR-RED FINANCES", "ANNOYING SEARCH", "UNJUSTIFIABLE SEARCH")
    smlua_text_utils_course_acts_replace(COURSE_SSL, " 8 OVERGROWN OASIS", "STILL UNDER CONSTRUCTION", "FLOOD LANDING STAGE", "NOT SO SECRET SECRET ANYMORE", "DOUBTFUL PYRAMID", "HIDDEN HERMIT", "YOU SHALL DROWN!")
    smlua_text_utils_course_acts_replace(COURSE_DDD, " 9 FIREFLOWER FIELDS", "ANOTHER REMATCH WITH KING BOB-OMB", "WINDY MILL", "WAY TOO EASY COINS", "THE UNSTABLE WOODEN CONSTRUCTION", "NOT SO SECRET CAVERN", "BARK BEETLE JUMPS")
    smlua_text_utils_course_acts_replace(COURSE_SL,  "10 BREEZING BEACH", "SECRET OF THE SMARAGDS", "HOT POLE-DANCE", "SOMEWHERE IN THE NOWHERE", "NOWHERE IN THE SOMEWHERE", "COLD TOMB", "HEMOGLOBIN-COINS")
    smlua_text_utils_course_acts_replace(COURSE_WDW, "11 DRIED-OUT DEAD DESERT", "BURNING FEET", "AIRY STORED COINS", "THE OLD HIDEOUT", "GRAVE DIGGER", "CEMETARY ARTISTICS", "THE SAND PLATEAU'S TORTURE")
    smlua_text_utils_course_acts_replace(COURSE_TTM, "12 CLIFF OF PAIN", "MOVE YOUR BUTT UP THERE!", "WAY TOO HIGH", "ANOTHER PROBLEMATIC BOX", "HEAVE-HO CAVE", "YOU-CAN-GUESS-WHICH COINS", "BRAZENLY PLACED")
    smlua_text_utils_course_acts_replace(COURSE_THI, "13 ACID PEAKS", "WELCOME TO THE ACID SWAMP", "EYE TO EYE", "ACIDPROOF BOXES", "IN THE BIG CAVE", "ANOTHER CLIMBING CHALLENGE", "LAVA-COLORED GLITTER")
    smlua_text_utils_course_acts_replace(COURSE_TTC, "14 VENENO SPHERE", "THE SAME PLACE IN A WORSE WORLD", "THROUGH THE HEART OF THE WORLD", "THE EDGE OF THE WORLD", "THE ROOF OF THE WORLD", "WORLDWIDE PAIN", "BLOODRED COINS OF RUINATION")
    smlua_text_utils_course_acts_replace(COURSE_RR,  "15 CRUDELO SPHERE", "THE NIGHTMARE BEGINS", "JUST GO CRAZY", "STRAIGHT FROM HELL", "TRAUMATISING EXPERIENCE", "MORBID DEADLY PUZZLE", "BLOODY SCREAM OF RAGE")

    smlua_text_utils_secret_star_replace(COURSE_BITDW,    "   BOWSER'S BEAUTIFUL BACKYARD")
    smlua_text_utils_secret_star_replace(COURSE_BITFS,    "   BOWSER'S QUICKSAND PIT")
    smlua_text_utils_secret_star_replace(COURSE_BITS,     "   ZTAR ZANCTUARY")
    smlua_text_utils_secret_star_replace(COURSE_PSS,      "   OLD SUPPLY SLIDE")
    smlua_text_utils_secret_star_replace(COURSE_COTMC,    "   TOXIC TERRACE")
    smlua_text_utils_secret_star_replace(COURSE_TOTWC,    "   DEVIL'S PIT")
    smlua_text_utils_secret_star_replace(COURSE_VCUTM,    "   DUST DESTINATION")
    smlua_text_utils_secret_star_replace(COURSE_WMOTR,    "   LAKE OF THE LORDS")
    smlua_text_utils_secret_star_replace(COURSE_SA,       "   TRIARC-BRIDGE")
    smlua_text_utils_secret_star_replace(COURSE_CAKE_END, "")

    smlua_text_utils_castle_secret_stars_replace("   BONUSSTARS")
    smlua_text_utils_extra_text_replace(0, "BONUS STAR")
    smlua_text_utils_extra_text_replace(1, "")
    smlua_text_utils_extra_text_replace(2, "")
    smlua_text_utils_extra_text_replace(3, "")
    smlua_text_utils_extra_text_replace(4, "")
    smlua_text_utils_extra_text_replace(5, "")
    smlua_text_utils_extra_text_replace(6, "")
end

----------
-- main --
----------

function course_names_swap()
    local areaIndex = gNetworkPlayers[0].currAreaIndex
    if areaIndex == 1 then
        course_names_swap_sm74()
        sCourseNamesEE = false
    else
        course_names_swap_sm74ee()
        sCourseNamesEE = true
    end
end

-----------
-- setup --
-----------

-- do initial swap to sm74
sCourseNamesEE = true
course_names_swap_sm74()
sCourseNamesEE = false
