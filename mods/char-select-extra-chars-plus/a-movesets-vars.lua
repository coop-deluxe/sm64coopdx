--- Vars that all movesets use --

--- @type CharacterState[]
gCharacterStates = {}
for i = 0, (MAX_PLAYERS - 1) do
    gCharacterStates[i] = {
        mario = gMarioStates[i],
        luigi = {
            scuttle = 0,
            lastHurtCounter = 0
        },
        toad = {},
        wario = {},
        waluigi = {},
        toadette = {
            averageForwardVel = 0
        },
        peach = {},
        daisy = {},
        yoshi = {},
        birdo = {
            spitTimer = 0,
            framesSinceShoot = 255,
            flameCharge = 0
        },
        spike = {},
        pauline = {},
        rosalina = {
            canSpin = true,
            orbitObjActive = false,
            orbitObjDist = 0,
            orbitObjAngle = 0
        },
        wapeach = {},
        donkeyKong = {},
        sonic = {
            spinCharge = 0,
            groundYVel = 0,
            prevForwardVel = 0,
            peakHeight = 0,
            actionADone = false,
            actionBDone = false,
            bounceCooldown = 0,
            spindashState = 0,
            instashieldTimer = 0,
            oxygen = 900, -- 30 seconds
            prevVelY = 0,
            prevHeight = 0,
            physTimer = 0,
            lastforwardPos = gVec3fZero(),
            realFVel = 0,
            wallSpam = 0,
            prevWallAngle = -1
        }
    }

    gPlayerSyncTable[i].rings = 0
end
