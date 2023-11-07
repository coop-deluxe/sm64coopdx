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

struct PCCLIOptions gCLIOpts;

static void print_help(void) {
    printf("\nsm64ex-coop\n");
    printf("%-20s\tSaves the configuration file as CONFIGNAME.\n", "--configfile CONFIGNAME");
    printf("%-20s\tSets additional data directory name (only 'res' is used by default).\n", "--gamedir DIRNAME");
    printf("%-20s\tOverrides the default save/config path ('!' expands to executable path).\n", "--savepath SAVEPATH");
    printf("%-20s\tStarts the game in full screen mode.\n", "--fullscreen");
    printf("%-20s\tSkips the Peach and Castle intro when starting a new game.\n", "--skip-intro");
    printf("%-20s\tStarts the game in windowed mode.\n", "--windowed");
    printf("%-20s\tStarts the game and creates a new server.\n", "--server PORT");
    printf("%-20s\tStarts the game and joins an existing server.\n", "--client IP PORT");
    printf("%-20s\tStarts the game using a poolsize of your choice.\n", "--poolsize POOLSIZE");
    printf("%-20s\tStarts the game with a specific playername.\n", "--playername PLAYERNAME");
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

    // Initialize options with false values.
    memset(&gCLIOpts, 0, sizeof(gCLIOpts));

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--skip-intro") == 0) // Skip Peach Intro
            gCLIOpts.SkipIntro = 1;

        else if (strcmp(argv[i], "--fullscreen") == 0) // Open game in fullscreen
            gCLIOpts.FullScreen = 1;

        else if (strcmp(argv[i], "--windowed") == 0) // Open game in windowed mode
            gCLIOpts.FullScreen = 2;

        else if (strcmp(argv[i], "--server") == 0 && (i + 1) < argc) { // Host server
            gCLIOpts.Network = NT_SERVER;
            arg_uint("--server <port>", argv[++i], &gCLIOpts.NetworkPort);

        } else if (strcmp(argv[i], "--client") == 0 && (((i + 1) < argc) || (i + 2) < argc)) { // Join server
            gCLIOpts.Network = NT_CLIENT;
            arg_string("--client <ip>", argv[++i], gCLIOpts.JoinIp, IP_MAX_LEN);
            if ((i + 2) < argc) {
                arg_uint("--client <port>", argv[++i], &gCLIOpts.NetworkPort);
            } else {
                gCLIOpts.NetworkPort = 7777;
            }

        } else if (strcmp(argv[i], "--poolsize") == 0) // Main pool size
            arg_uint("--poolsize", argv[++i], &gCLIOpts.PoolSize);

        else if (strcmp(argv[i], "--configfile") == 0 && (i + 1) < argc)
            arg_string("--configfile", argv[++i], gCLIOpts.ConfigFile, SYS_MAX_PATH);

        else if (strcmp(argv[i], "--gamedir") == 0 && (i + 1) < argc)
            arg_string("--gamedir", argv[++i], gCLIOpts.GameDir, SYS_MAX_PATH);

        else if (strcmp(argv[i], "--savepath") == 0 && (i + 1) < argc)
            arg_string("--savepath", argv[++i], gCLIOpts.SavePath, SYS_MAX_PATH);

        else if (strcmp(argv[i], "--playername") == 0 && (i + 1) < argc)
            arg_string("--playername", argv[++i], gCLIOpts.PlayerName, MAX_PLAYER_STRING);

        // Print help
        else if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return false;
        }
    }

    return true;
}
