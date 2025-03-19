#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <stdbool.h>
#include <PR/ultratypes.h>
#include "game/player_palette.h"

#define CONFIGFILE_DEFAULT "sm64config.txt"
#define CONFIGFILE_BACKUP "sm64config-backup.txt"

#define MAX_BINDS  3
#define MAX_VOLUME 127
#define MAX_CONFIG_STRING 64
#define MAX_SAVE_NAME_STRING 32

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

extern char configSaveNames[4][MAX_SAVE_NAME_STRING];

// display settings
extern ConfigWindow configWindow;
extern unsigned int configFiltering;
extern bool         configShowFPS;
extern bool         configUncappedFramerate;
extern unsigned int configFrameLimit;
extern unsigned int configInterpolationMode;
extern unsigned int configDrawDistance;
// sound settings
extern unsigned int configMasterVolume;
extern unsigned int configMusicVolume;
extern unsigned int configSfxVolume;
extern unsigned int configEnvVolume;
extern bool         configFadeoutDistantSounds;
extern bool         configMuteFocusLoss;
// control binds
extern unsigned int configKeyA[MAX_BINDS];
extern unsigned int configKeyB[MAX_BINDS];
extern unsigned int configKeyX[MAX_BINDS];
extern unsigned int configKeyY[MAX_BINDS];
extern unsigned int configKeyStart[MAX_BINDS];
extern unsigned int configKeyL[MAX_BINDS];
extern unsigned int configKeyR[MAX_BINDS];
extern unsigned int configKeyZ[MAX_BINDS];
extern unsigned int configKeyCUp[MAX_BINDS];
extern unsigned int configKeyCDown[MAX_BINDS];
extern unsigned int configKeyCLeft[MAX_BINDS];
extern unsigned int configKeyCRight[MAX_BINDS];
extern unsigned int configKeyStickUp[MAX_BINDS];
extern unsigned int configKeyStickDown[MAX_BINDS];
extern unsigned int configKeyStickLeft[MAX_BINDS];
extern unsigned int configKeyStickRight[MAX_BINDS];
extern unsigned int configKeyChat[MAX_BINDS];
extern unsigned int configKeyPlayerList[MAX_BINDS];
extern unsigned int configKeyDUp[MAX_BINDS];
extern unsigned int configKeyDDown[MAX_BINDS];
extern unsigned int configKeyDLeft[MAX_BINDS];
extern unsigned int configKeyDRight[MAX_BINDS];
extern unsigned int configKeyConsole[MAX_BINDS];
extern unsigned int configKeyPrevPage[MAX_BINDS];
extern unsigned int configKeyNextPage[MAX_BINDS];
extern unsigned int configKeyDisconnect[MAX_BINDS];
extern unsigned int configStickDeadzone;
extern unsigned int configRumbleStrength;
extern unsigned int configGamepadNumber;
extern bool         configBackgroundGamepad;
extern bool         configDisableGamepads;
extern bool         configUseStandardKeyBindingsChat;
// free camera settings
extern bool         configEnableFreeCamera;
extern bool         configFreeCameraAnalog;
extern bool         configFreeCameraLCentering;
extern bool         configFreeCameraDPadBehavior;
extern bool         configFreeCameraHasCollision;
extern bool         configFreeCameraMouse;
extern unsigned int configFreeCameraXSens;
extern unsigned int configFreeCameraYSens;
extern unsigned int configFreeCameraAggr;
extern unsigned int configFreeCameraPan;
extern unsigned int configFreeCameraDegrade;
// romhack camera settings
extern unsigned int configEnableRomhackCamera;
extern bool         configRomhackCameraBowserFights;
extern bool         configRomhackCameraHasCollision;
extern bool         configRomhackCameraHasCentering;
extern bool         configRomhackCameraDPadBehavior;
extern bool         configRomhackCameraSlowFall;
// common camera settings
extern bool         configCameraInvertX;
extern bool         configCameraInvertY;
extern bool         configCameraToxicGas;
// debug
extern bool         configLuaProfiler;
extern bool         configDebugPrint;
extern bool         configDebugInfo;
extern bool         configDebugError;
#ifdef DEVELOPMENT
extern bool         configCtxProfiler;
#endif
// player settings
extern char         configPlayerName[MAX_CONFIG_STRING];
extern unsigned int configPlayerModel;
extern struct PlayerPalette configPlayerPalette;
// coop settings
extern unsigned int configAmountOfPlayers;
extern bool         configBubbleDeath;
extern unsigned int configHostPort;
extern unsigned int configHostSaveSlot;
extern char         configJoinIp[MAX_CONFIG_STRING];
extern unsigned int configJoinPort;
extern unsigned int configNetworkSystem;
extern unsigned int configPlayerInteraction;
extern unsigned int configPlayerKnockbackStrength;
extern unsigned int configStayInLevelAfterStar;
extern bool         configNametags;
extern unsigned int configBouncyLevelBounds;
extern bool         configSkipIntro;
extern bool         configPauseAnywhere;
extern bool         configMenuStaffRoll;
extern unsigned int configMenuLevel;
extern unsigned int configMenuSound;
extern bool         configMenuRandom;
extern bool         configMenuDemos;
extern bool         configDisablePopups;
extern char         configLanguage[MAX_CONFIG_STRING];
extern bool         configDynosLocalPlayerModelOnly;
extern unsigned int configPvpType;
// CoopNet settings
extern char         configCoopNetIp[MAX_CONFIG_STRING];
extern unsigned int configCoopNetPort;
extern char         configPassword[MAX_CONFIG_STRING];
extern char         configDestId[MAX_CONFIG_STRING];
// DJUI settings
extern unsigned int configDjuiTheme;
extern bool         configDjuiThemeCenter;
extern unsigned int configDjuiThemeFont;
extern unsigned int configDjuiScale;
// other
extern unsigned int configRulesVersion;
extern bool         configCompressOnStartup;
extern bool         configSkipPackGeneration;

// secrets
extern bool configExCoopTheme;

void enable_queued_mods(void);
void enable_queued_dynos_packs(void);
void configfile_load(void);
void configfile_save(const char *filename);
const char *configfile_name(void);
const char *configfile_backup_name(void);

#endif // CONFIGFILE_H
