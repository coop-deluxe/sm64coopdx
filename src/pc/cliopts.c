#include "cliopts.h"
#include "configfile.h"
#include "pc_main.h"
#include "platform.h"
#include "macros.h"

#include <strings.h>
#include <stdlib.h>
#define __NO_MINGW_LFS //Mysterious error in MinGW.org stdio.h
#include <stdio.h>
#include <string.h>

struct CLIOptions gCLIOpts;

static void print_help(void) {
    printf("sm64coopdx\n");
#if defined(_WIN32) || defined(_WIN64)
    printf("--console               Enables the Windows console.\n");
#endif
    printf("--savepath SAVEPATH     Overrides the default save/config path ('!' expands to executable path).\n");
    printf("--configfile CONFIGNAME Saves the configuration file as CONFIGNAME.\n");
    printf("--hide-loading-screen   Hides the loading screen before the menu boots up.\n");
    printf("--fullscreen            Starts the game in full screen mode.\n");
    printf("--windowed              Starts the game in windowed mode.\n");
    printf("--skip-intro            Skips the Peach and Lakitu intros when on a zero star save.\n");
    printf("--server PORT           Starts the game and creates a new server on PORT.\n");
    printf("--client IP PORT        Starts the game and joins an existing server.\n");
    printf("--playername PLAYERNAME Starts the game with a specific playername.\n");
    printf("--skip-update-check     Skips the update check when loading the game.\n");
    printf("--no-discord            Disables discord integration.");
}

static inline int arg_string(const char *name, const char *value, char *target, int maxLength) {
    const unsigned int arglen = strlen(value);
    if (arglen >= (unsigned int) maxLength) {
        fprintf(stderr, "Supplied value for `%s` is too long.\n", name);
        return 0;
    }
    snprintf(target, maxLength, "%s", value);
    return 1;
}

static inline int arg_uint(UNUSED const char *name, const char *value, unsigned int *target) {
    const unsigned long int v = strtoul(value, NULL, 0);
    *target = v;
    return 1;
}

bool parse_cli_opts(int argc, char* argv[]) {
    // initialize options with false values
    memset(&gCLIOpts, 0, sizeof(gCLIOpts));

    for (int i = 1; i < argc; i++) {
#if defined(_WIN32) || defined(_WIN64)
        if (!strcmp(argv[i], "--console")) {
            gCLIOpts.console = true;
        } else if (!strcmp(argv[i], "--savepath") && (i + 1) < argc) {
#else
        if (!strcmp(argv[i], "--savepath") && (i + 1) < argc) {
#endif
            arg_string("--savepath", argv[++i], gCLIOpts.savePath, SYS_MAX_PATH);
        } else if (!strcmp(argv[i], "--configfile") && (i + 1) < argc) {
            arg_string("--configfile", argv[++i], gCLIOpts.configFile, SYS_MAX_PATH);
        } else if (!strcmp(argv[i], "--hide-loading-screen")) {
            gCLIOpts.hideLoadingScreen = true;
        } else if (!strcmp(argv[i], "--fullscreen")) {
            gCLIOpts.fullscreen = 1;
        } else if (!strcmp(argv[i], "--windowed")) {
            gCLIOpts.fullscreen = 2;
        } else if (!strcmp(argv[i], "--skip-intro")) {
            gCLIOpts.skipIntro = true;
        } else if (!strcmp(argv[i], "--server") && (i + 1) < argc) {
            gCLIOpts.network = NT_SERVER;
            arg_uint("--server <port>", argv[++i], &gCLIOpts.networkPort);
        } else if (!strcmp(argv[i], "--client") && (((i + 1) < argc) || (i + 2) < argc)) {
            gCLIOpts.network = NT_CLIENT;
            arg_string("--client <ip>", argv[++i], gCLIOpts.joinIp, IP_MAX_LEN);
            if ((i + 2) < argc) {
                arg_uint("--client <port>", argv[++i], &gCLIOpts.networkPort);
            } else {
                gCLIOpts.networkPort = 7777;
            }
        } else if (!strcmp(argv[i], "--playername") && (i + 1) < argc) {
            arg_string("--playername", argv[++i], gCLIOpts.playerName, MAX_CONFIG_STRING);
        } else if (!strcmp(argv[i], "--skip-update-check")) {
            gCLIOpts.skipUpdateCheck = true;
        } else if (!strcmp(argv[i], "--no-discord")) {
            gCLIOpts.noDiscord = true;
        } else if (!strcmp(argv[i], "--help")) {
            print_help();
            return false;
        }
    }

    return true;
}
