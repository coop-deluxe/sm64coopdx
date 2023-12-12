#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <stdbool.h>
#include "PR/ultratypes.h"
#include "game/characters.h"

#define CONFIGFILE_DEFAULT "sm64config.txt"
#define CONFIGFILE_BACKUP "sm64config-backup.txt"

#define MAX_BINDS  3
#define MAX_VOLUME 127
#define MAX_CONFIG_STRING 64
#define MAX_PLAYER_STRING 60
#define MAX_DESCRIPTION_STRING 20

#define DEFAULT_PORT 7777
#define DEFAULT_COOPNET_IP "net.coop64.us"
#define DEFAULT_COOPNET_PORT 34197

typedef struct {
    unsigned int x, y, w, h;
    bool vsync;
    bool reset;
    bool fullscreen;
    bool exiting_fullscreen;
    bool settings_changed;
    unsigned int msaa;
} ConfigWindow;

extern ConfigWindow configWindow;
extern unsigned int configFiltering;
extern unsigned int configMasterVolume;
extern unsigned int configMusicVolume;
extern unsigned int configSfxVolume;
extern unsigned int configEnvVolume;
extern unsigned int configKeyA[];
extern unsigned int configKeyB[];
extern unsigned int configKeyX[];
extern unsigned int configKeyY[];
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
extern unsigned int configKeyConsole[];
extern unsigned int configKeyPrevPage[];
extern unsigned int configKeyNextPage[];
extern unsigned int configKeyDisconnect[];
extern unsigned int configStickDeadzone;
extern unsigned int configRumbleStrength;
extern unsigned int configGamepadNumber;
extern bool         configBackgroundGamepad;
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
extern bool         configCameraCUp;
extern bool         configSkipIntro;
extern bool         configBubbleDeath;
extern unsigned int configAmountofPlayers;
extern char         configJoinIp[];
extern unsigned int configJoinPort;
extern unsigned int configHostPort;
extern unsigned int configHostSaveSlot;
extern unsigned int configPlayerInteraction;
extern unsigned int configPlayerKnockbackStrength;
extern unsigned int configStayInLevelAfterStar;
extern bool         configNametags;
extern unsigned int configBouncyLevelBounds;
extern unsigned int configNetworkSystem;
extern char         configPlayerName[];
extern unsigned int configPlayerModel;
extern bool         configMenuStaffRoll;
extern unsigned int configMenuLevel;
extern bool         configMenuSound;
extern bool         configMenuRandom;
extern bool         configMenuDemos;
extern struct PlayerPalette configPlayerPalette;
extern struct PlayerPalette configCustomPalette;
extern unsigned int configDisplayFPS;
extern bool         configUncappedFramerate;
extern unsigned int configFrameLimit;
extern unsigned int configDrawDistance;
extern bool         configDisablePopups;
extern bool configUseAlternativeChatBehaviour;
#if defined(DEVELOPMENT)
extern bool         configLuaProfiler;
extern bool         configCtxProfiler;
#endif
extern unsigned int configInterpolationMode;
extern bool         configDebugPrint;
extern bool         configDebugInfo;
extern bool         configDebugError;
extern char         configLanguage[];
extern bool         configForce4By3;
extern char         configCoopNetIp[];
extern unsigned int configCoopNetPort;
extern char         configPassword[];
extern char         configDestId[];
extern bool         configFadeoutDistantSounds;
extern unsigned int configDjuiTheme;
extern bool         configDjuiThemeCenter;
extern unsigned int configDjuiScale;
extern bool         configCoopCompatibility;

void enable_queued_mods();
void configfile_load(void);
void configfile_save(const char *filename);
const char *configfile_name(void);
const char *configfile_backup_name(void);

#endif // CONFIGFILE_H
