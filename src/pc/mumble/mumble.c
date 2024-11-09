// adapted from https://www.mumble.info/documentation/developer/positional-audio/link-plugin/

#include "mumble.h"

#include "engine/math_util.h"

#include "game/level_update.h"
#include "game/camera.h"
#include "game/area.h"

#include "pc/configfile.h"
#include "pc/djui/djui.h"

#include <stdbool.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/mman.h>
	#include <fcntl.h> /* For O_* constants */
	#include <unistd.h>
#endif // _WIN32

struct LinkedMem *lm = NULL;

extern bool gIsDemoActive;

s16 sPrevCheckLevel;
s16 sPrevCheckArea;

void mumble_init(void) {

#ifdef _WIN32
	HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (hMapObject == NULL)
		return;

	lm = (struct LinkedMem *) MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(struct LinkedMem));
	if (lm == NULL) {
		CloseHandle(hMapObject);
		hMapObject = NULL;
		return;
	}
#else
	char memname[256];
	snprintf(memname, 256, "/MumbleLink.%d", getuid());

	int shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);

	if (shmfd < 0) {
		return;
	}

	lm = (struct LinkedMem *)(mmap(NULL, sizeof(struct LinkedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd,0));

	if (lm == (void *)(-1)) {
		lm = NULL;
		return;
	}
#endif

	if(lm->uiVersion != 2) {
		wcsncpy(lm->name, L"SM64 Coop Deluxe", 256);
		wcsncpy(lm->description, L"SM64 Coop Deluxe support via the Link plugin.", 2048);
		lm->uiVersion = 2;
	}

    // not necessary, but we can set it here and forget about it
    mbstowcs(lm->identity, configPlayerName, 256);

    lm->context_len = 20;
}

void mumble_update(void) {

	if (! lm) {
		return;
    }

	lm->uiTick++;

    if (gDjuiInMainMenu)
    {
        mumble_update_menu();
        return;
    }

    // The hitbox is 160.0 for standing and 100.0 for crouching
    // Also subtract a bit to go from top of the head to the middle
    float headHeight = gMarioState->marioObj->hitboxHeight - 60;

    // divide by 100 to convert units to meters as mumble expects
	lm->fAvatarPosition[0] = gMarioState->pos[0] / 100;
	lm->fAvatarPosition[1] = (gMarioState->pos[1] + headHeight) / 100;
	lm->fAvatarPosition[2] = gMarioState->pos[2] / 100;

    // mumble expects a unit vector so we need to convert the face angle
    Vec3f faceVector;
    faceVector[0] = coss(gMarioState->faceAngle[0]) * sins(gMarioState->faceAngle[1]);
    faceVector[1] = sins(gMarioState->faceAngle[0]);
    faceVector[2] = coss(gMarioState->faceAngle[0]) * coss(gMarioState->faceAngle[1]);
    vec3f_normalize(faceVector);

    // mumble also seems to have x and z inverted
    lm->fAvatarFront[0] = -faceVector[0];
    lm->fAvatarFront[1] = faceVector[1];
    lm->fAvatarFront[2] = -faceVector[2];

    // the actual camera can move too far away, and players will be louder near
    // the camera, which can be diorienting, so we use the player pos instead.
	lm->fCameraPosition[0] = gMarioState->pos[0] / 100;
	lm->fCameraPosition[1] = (gMarioState->pos[1] + headHeight) / 100;
	lm->fCameraPosition[2] = gMarioState->pos[2] / 100;

    // still use the direction of the camera, so make it into a unit vector
    Vec3f normal;
    vec3f_dif(normal, gLakituState.focus, gLakituState.pos);
    vec3f_normalize(normal);

    lm->fCameraFront[0] = -normal[0];
    lm->fCameraFront[1] = normal[1];
    lm->fCameraFront[2] = -normal[2];

    // players with the same context can hear eachother, and is a concat of:
    // level, area, and room. 
	if (should_update_context()) {
		char context[20];
		snprintf(context, 20, "%d-%d-%d", gCurrLevelNum, gCurrAreaIndex, gMarioState->currentRoom);
		memcpy(lm->context, (unsigned char *) context, 20);
	}
}

void mumble_update_menu() {

	lm->fAvatarPosition[0] = 0.0f;
	lm->fAvatarPosition[1] = 0.0f;
	lm->fAvatarPosition[2] = 1.0f;

	lm->fAvatarFront[0] = 0.0f;
	lm->fAvatarFront[1] = 0.0f;
	lm->fAvatarFront[2] = 1.0f;

	lm->fCameraPosition[0] = 0.0f;
	lm->fCameraPosition[1] = 0.0f;
	lm->fCameraPosition[2] = 0.0f;

	lm->fCameraFront[0] = 0.0f;
	lm->fCameraFront[1] = 0.0f;
	lm->fCameraFront[2] = 1.0f;

    memcpy(lm->context, "mainmenu\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 20);
}

bool should_update_context() {

	// room 0 is an object like an elevator on hmc, but ALSO the only room
	// for levels without rooms. So we only want to ignore room zero if we 
	// haven't changed maps at the same time 

	if (gMarioState->currentRoom == 0 && gCurrLevelNum == sPrevCheckLevel && gCurrAreaIndex == sPrevCheckArea) {
		return false;
	}

	sPrevCheckLevel = gCurrLevelNum;
	sPrevCheckArea = gCurrAreaIndex;
	
    // some rooms are just small areas around doors which is a bit annoying as
    // audio will cut out for players standing close to them or walking between.
    // There only seem to be a few, so I've mapped them below
	// JR - 2024-Jul-28

	// castle interior
	if (gCurrLevelNum == LEVEL_CASTLE) {
		// main floor
		if (gCurrAreaIndex == 1) {
			return  gMarioState->currentRoom < 10;
		}
		// upstairs
		if (gCurrAreaIndex == 2) {
			return gMarioState->currentRoom < 7;
		}
		// basement
		if (gCurrAreaIndex == 3) {
			return gMarioState->currentRoom < 6;
		}
	}

	// big boos haunt
	if (gCurrLevelNum == LEVEL_BBH) {
		return gMarioState->currentRoom < 14;
	}
	
	// hazy maze cave
	if (gCurrLevelNum == LEVEL_HMC) {
		return gMarioState->currentRoom < 9;
	}

	return true;
}
