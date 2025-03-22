#ifdef __SWITCH__

#include "nx_utils.h"

AccountUid get_current_user() {
    AccountUid uid;
    uid.uid[0] = 0;
    uid.uid[1] = 0;
    accountGetPreselectedUser(&uid);
    
    return uid;
}

int ensure_save_data(AccountUid uid) {
    return serviceDispatchIn(appletGetServiceSession_Functions(), 20, uid);
}

int ensure_current_user_save() {
    return ensure_save_data(get_current_user());
}

int mount_save_data() {
    FsFileSystem fileSystem;

    if(fsOpen_SaveData(&fileSystem, FS_SAVEDATA_CURRENT_APPLICATIONID, get_current_user())) {
        return 1;
    }

    if(fsdevMountDevice("sv", fileSystem) == -1) {
        fsdevUnmountDevice("sv");
        return 2;
    }

    return 0;
}

int unmount_save_data() {
    if(fsdevUnmountDevice("sv") == -1) { return 1; }
    return 0;
}

int commit_save() {
    return fsdevCommitDevice("sv");
}

#endif // __SWITCH__