#ifdef __SWITCH__

#ifndef _NX_UTILS_H
#define _NX_UTILS_H

#ifdef __cplusplus

#include <switch.h>

AccountUid get_current_user(void);
int ensure_save_data(AccountUid uid);

extern "C" {
#endif

int ensure_current_user_save(void);
int mount_save_data(void);
int unmount_save_data(void);
int commit_save(void);

#ifdef __cplusplus
}
#endif

#endif // _NX_UTILS_H

#endif // __SWITCH__