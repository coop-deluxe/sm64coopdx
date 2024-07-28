#ifndef MUMBLE_H
#define MUMBLE_H

#include <stdint.h>
#include <wchar.h>
#include <stdbool.h>

struct LinkedMem {

	uint32_t uiVersion;
	uint32_t uiTick;

	float	fAvatarPosition[3];
	float	fAvatarFront[3];
	float	fAvatarTop[3];
	wchar_t	name[256];
	float	fCameraPosition[3];
	float	fCameraFront[3];
	float	fCameraTop[3];
	wchar_t	identity[256];

	uint32_t	context_len;

	unsigned char context[256];
	wchar_t description[2048];
};

void mumble_init(void);
void mumble_update(void);
void mumble_update_menu(void);

bool should_update_context(void);

#endif /* MUMBLE_H */