--- Vars that all movesets use --

--- @type CharacterState[]
gCharacterStates = {}
for i = 0, (MAX_PLAYERS - 1) do
    gCharacterStates[i] = {}
    local m = gMarioStates[i]
    local e = gCharacterStates[i]
    e.mario      = m
    e.luigi      = {}
    e.toad       = {}
    e.wario      = {}
    e.waluigi    = {}
    e.toadette   = {}
    e.peach      = {}
    e.daisy      = {}
    e.yoshi      = {}
    e.birdo      = {}
    e.spike      = {}
    e.pauline    = {}
    e.rosalina   = {}
    e.wapeach    = {}
    e.donkeyKong = {}
    e.sonic      = {}

    e.toadette.averageForwardVel = 0

    e.birdo.spitTimer = 0
    e.birdo.framesSinceShoot = 255
    e.birdo.flameCharge = 0

    e.rosalina.canSpin = true
    e.rosalina.orbitObjActive = false
    e.rosalina.orbitObjDist = 0
    e.rosalina.orbitObjAngle = 0

    e.sonic.spinCharge = 0
    e.sonic.groundYVel = 0
    e.sonic.prevForwardVel = 0
    e.sonic.peakHeight = 0
    e.sonic.actionADone = false
    e.sonic.actionBDone = false
    e.sonic.bounced = false
    e.sonic.spindashState = 0
    e.sonic.instashieldTimer = 0
    e.sonic.oxygen = 900 -- 30 seconds
    e.sonic.prevVelY = 0
    e.sonic.prevHeight = 0
    e.sonic.physTimer = 0
    e.sonic.lastforwardPos = gVec3fZero()
    e.sonic.realFVel = 0
end
