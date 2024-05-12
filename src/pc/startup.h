#include "types.h"

extern bool gUserFolderCopied;
extern bool gRomIsValid;
extern char gRomFilename[];

void old_user_folder_handler(void);

bool main_rom_handler(void);
void rom_on_drop_file(const char *path);
