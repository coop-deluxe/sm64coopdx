#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <stdbool.h>

#define CONFIGFILE_DEFAULT "sm64config.txt"

#define MAX_BINDS  3
#define MAX_VOLUME 127
#define MAX_CONFIG_STRING 64
#define MAX_PLAYER_STRING 20

#define DEFAULT_PORT 7777

typedef struct {
    unsigned int x, y, w, h;
    bool vsync;
    bool reset;
    bool fullscreen;
    bool exiting_fullscreen;
    bool settings_changed;
} ConfigWindow;

extern ConfigWindow configWindow;
extern unsigned int configFiltering;
extern unsigned int configMasterVolume;
extern unsigned int configMusicVolume;
extern unsigned int configSfxVolume;
extern unsigned int configEnvVolume;
extern unsigned int configKeyA[];
extern unsigned int configKeyB[];
extern unsigned int configKeyStart[];
extern unsigned int configKeyL[];
extern unsigned int configKeyR[];
extern unsigned int configKeyZ[];
extern unsigned int configKeyCUp[];
extern unsigned int configKeyCDown[];
extern unsigned int configKeyCLeft[];
extern unsigned int configKeyCRight[];
extern unsigned int configKeyStickUp[];
extern unsigned int configKeyStickDown[];
extern unsigned int configKeyStickLeft[];
extern unsigned int configKeyStickRight[];
extern unsigned int configKeyChat[];
extern unsigned int configKeyPlayerList[];
extern unsigned int configKeyDUp[];
extern unsigned int configKeyDDown[];
extern unsigned int configKeyDLeft[];
extern unsigned int configKeyDRight[];
extern unsigned int configStickDeadzone;
extern unsigned int configRumbleStrength;
#ifdef EXTERNAL_DATA
extern bool         configPrecacheRes;
#endif
#ifdef BETTERCAMERA
extern unsigned int configCameraXSens;
extern unsigned int configCameraYSens;
extern unsigned int configCameraAggr;
extern unsigned int configCameraPan;
extern unsigned int configCameraDegrade;
extern bool         configCameraInvertX;
extern bool         configCameraInvertY;
extern bool         configEnableCamera;
extern bool         configCameraMouse;
extern bool         configCameraAnalog;
#endif
extern bool         configHUD;
extern bool         configSkipIntro;
extern bool         configShareLives;
extern bool         configEnableCheats;
extern bool         configBubbleDeath;
#ifdef DISCORDRPC
extern bool         configDiscordRPC;
#endif
extern char         configJoinIp[];
extern unsigned int configJoinPort;
extern unsigned int configHostPort;
extern unsigned int configHostSaveSlot;
extern unsigned int configPlayerInteraction;
extern unsigned int configPlayerKnockbackStrength;
extern bool         configStayInLevelAfterStar;
extern unsigned int configNetworkSystem;
extern char         configPlayerName[];
extern unsigned int configPlayerModel;
extern unsigned int configPlayerPalette;
extern unsigned int config60Fps;
extern unsigned int configDrawDistance;

void configfile_load(const char *filename);
void configfile_save(const char *filename);
const char *configfile_name(void);

#endif
