// adapted from https://www.mumble.info/documentation/developer/positional-audio/link-plugin/
#include "mumble.h"

#include "engine/math_util.h"

#include "game/level_update.h"
#include "game/camera.h"
#include "game/area.h"

#include "pc/configfile.h"



#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/mman.h>
	#include <fcntl.h> /* For O_* constants */
	#include <libc.h>
#endif // _WIN32

struct LinkedMem *lm = NULL;

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

    // The hitbox is 160.0 for standing and 100.0 for crouching
    // Also subtract a bit to go from top of the head to the middle
    float headHeight = gMarioState->marioObj->hitboxHeight - 60;

    // divide by 100 to convert units to meters as mumble expects
	lm->fAvatarPosition[0] = gMarioState->pos[0] / 100;
	lm->fAvatarPosition[1] = (gMarioState->pos[1] + headHeight) / 100;
	lm->fAvatarPosition[2] = gMarioState->pos[2] / 100;

    // mumble expects a unit vector so we need to convert the face angle
    // it also seems to have x and z inverted
    Vec3f faceVector;
    faceVector[0] = coss(gMarioState->faceAngle[0]) * sins(gMarioState->faceAngle[1]);
    faceVector[1] = sins(gMarioState->faceAngle[0]);
    faceVector[2] = coss(gMarioState->faceAngle[0]) * coss(gMarioState->faceAngle[1]);
    vec3f_normalize(faceVector);

	lm->fAvatarFront[0] = -faceVector[0];
	lm->fAvatarFront[1] = faceVector[1];
	lm->fAvatarFront[2] = -faceVector[2];

	// camera position
	lm->fCameraPosition[0] = gLakituState.pos[0] / 100;
	lm->fCameraPosition[1] = gLakituState.pos[1] / 100;
	lm->fCameraPosition[2] = gLakituState.pos[2] / 100;

    // get the unit vector direction of the camera
    Vec3f normal;
    vec3f_dif(normal, gLakituState.focus, gLakituState.pos);
    vec3f_normalize(normal);

	lm->fCameraFront[0] = -normal[0];
	lm->fCameraFront[1] = normal[1];
	lm->fCameraFront[2] = -normal[2];

    // players with the same context can hear eachother, and is a concat of:
    // level, area, and room
    //
    // some rooms are just small areas around doors which is a bit annoying as
    // audio will cut out for players standing close to them or walking between,
    // but I haven't found a good way to detect such rooms. It is better than 
    // hearing through walls though, so a minor inconvience for now.
    // 
    // I might go through manually map levels and rooms which are not 'rooms' to
    // and skip over them here as a work around if there is nothing better.
    // JR - 2024-Jul-27

    char context[20];
    snprintf(context, 20, "%d-%d-%d", gCurrLevelNum, gCurrAreaIndex, gMarioState->currentRoom);
    memcpy(lm->context, (unsigned char*)context, 20);
}