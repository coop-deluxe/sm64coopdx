#ifndef MOD_FASTDL_H
#define MOD_FASTDL_H

#include <stdbool.h>
#include <PR/ultratypes.h>

enum FastDlMode {
    FDLM_ALWAYS_OFF    = 0,
    FDLM_LET_ME_CHOOSE = 1,
    FDLM_ALWAYS_ON     = 2,
};

// called by the mod list packet handlers
bool fastdl_set_url(const char* url); // empty string clears
void fastdl_clear_url(void);

// returns true when FastDL took over the join flow (caller must not start the chunk path)
bool fastdl_on_mod_list_done(void);

// per-frame main-thread poll; applies finished downloads and continues the join flow
void fastdl_update(void);

// aborts any running downloads; call from network_shutdown
// (a sticky "let me choose" answer survives reconnects but not full disconnects)
void fastdl_shutdown(bool reconnecting);

#endif // MOD_FASTDL_H
