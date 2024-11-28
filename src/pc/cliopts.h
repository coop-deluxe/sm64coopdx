#ifndef _CLIOPTS_H
#define _CLIOPTS_H

#include "platform.h"
#include "pc/configfile.h"

enum NetworkType {
    NT_NONE,
    NT_SERVER,
    NT_CLIENT
};

#define IP_MAX_LEN 32
#define PORT_MAX_LEN 16

struct CLIOptions {
#if defined(_WIN32) || defined(_WIN64)
    bool console;
#endif
    char savePath[SYS_MAX_PATH];
    char configFile[SYS_MAX_PATH];
    unsigned int fullscreen;
    bool skipIntro;
    enum NetworkType network;
    unsigned int networkPort;
    char joinIp[IP_MAX_LEN];
    char playerName[MAX_CONFIG_STRING];
    bool hideLoadingScreen;
    bool skipUpdateCheck;
    bool noDiscord;
};

extern struct CLIOptions gCLIOpts;

bool parse_cli_opts(int argc, char* argv[]);

#endif // _CLIOPTS_H
