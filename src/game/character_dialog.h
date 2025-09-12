#ifndef CHARACTER_DIALOG_H
#define CHARACTER_DIALOG_H

#include <PR/ultratypes.h>
#include "characters.h"
#include "dialog_ids.h"

struct MarioState;

struct CharacterDialogVariant {
    enum CharacterType character;
    const char* text;
};
struct CharacterDialogEntry {
    enum DialogId dialogId;
    struct CharacterDialogVariant variants[CT_MAX];
};

extern struct CharacterDialogEntry* gCharacterDialogs;
extern s32 gCharacterDialogCount;

void init_character_dialog_system(void);
void update_character_dialogs(void);
void apply_character_dialog_replacement(struct MarioState* m, enum DialogId dialogId);

const char* get_character_dialog_text(enum DialogId dialogId, enum CharacterType characterType);

#endif // CHARACTER_DIALOG_H