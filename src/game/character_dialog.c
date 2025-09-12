#include "character_dialog.h"
#include "pc/lua/utils/smlua_text_utils.h"
#include "mario_actions_cutscene.h"
#include "mario.h"
#include "level_update.h"
#include "segment2.h"
#include "sm64.h"
#include <stdio.h>
#include <string.h>

/* This is a dialog variant system implemented to track te player model and change the in-game dialog to the player being used
this can be better by making it work with charecter select but i dont think making the game compatible with specific mods will be implemented?
^maybe i can make it so it just tracks any model and pulls the name?*/
static struct CharacterDialogEntry sCharacterDialogs[] = {

    {
        .dialogId = DIALOG_003,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Thank you, Mario! The Big\nBob-omb is nothing but a\nbig dud now! But the\nbattle for the castle has\njust begun.\nOther enemies are holding\nthe other Power Stars. If\nyou recover more Stars,\nyou can open new doors\nthat lead to new worlds!\nMy Bob-omb Buddies are\nwaiting for you. Be sure\nto talk to them--they'll\nset up cannons for you." },
            [CT_LUIGI] = { CT_LUIGI, "Thank you, Luigi! The Big\nBob-omb is nothing but a\nbig dud now! But the\nbattle for the castle has\njust begun.\nOther enemies are holding\nthe other Power Stars. If\nyou recover more Stars,\nyou can open new doors\nthat lead to new worlds!\nMy Bob-omb Buddies are\nwaiting for you. Be sure\nto talk to them--they'll\nset up cannons for you." },
            [CT_WARIO] = { CT_WARIO, "Thank you, Wario. The Big\nBob-omb is nothing but a\nbig dud now! But the\nbattle for the castle has\njust begun.\nOther enemies are holding\nthe other Power Stars. If\nyou recover more Stars,\nyou can open new doors\nthat lead to new worlds!\nMy Bob-omb Buddies are\nwaiting for you. Be sure\nto talk to them--they'll\nset up cannons for you." },
            [CT_WALUIGI] = { CT_WALUIGI, "Thank you, Waluigi, The Big\nBob-omb is nothing but a\nbig dud now! But the\nbattle for the castle has\njust begun.\nOther enemies are holding\nthe other Power Stars. If\nyou recover more Stars,\nyou can open new doors\nthat lead to new worlds!\nMy Bob-omb Buddies are\nwaiting for you. Be sure\nto talk to them--they'll\nset up cannons for you." },
            [CT_TOAD] = { CT_TOAD, "Thank you, Toad! The Big\nBob-omb is nothing but a\nbig dud now! But the\nbattle for the castle has\njust begun.\nOther enemies are holding\nthe other Power Stars. If\nyou recover more Stars,\nyou can open new doors\nthat lead to new worlds!\nMy Bob-omb Buddies are\nwaiting for you. Be sure\nto talk to them--they'll\nset up cannons for you." }
        }
    },
    
    {
        .dialogId = DIALOG_005,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Hey, Mario! Is it true\nthat you beat the Big\nBob-omb? Cool!\nYou must be strong and\npretty fast. So, how fast\nare you anyway?\nFast enough to beat me...\nKoopa the Quick? I don't\nthink so. Just try me.\nHow about a race to the\nmountaintop, where the\nBig Bob-omb was?\nWhaddya say? When I say\nGo, let the race begin!\n\nReady....\n\n//Go!////Don't Go" },
            [CT_LUIGI] = { CT_LUIGI, "Hey, Luigi! Is it true\nthat you beat the Big\nBob-omb? Cool!\nYou must be strong and\npretty fast. So, how fast\nare you anyway?\nFast enough to beat me...\nKoopa the Quick? I don't\nthink so. Just try me.\nHow about a race to the\nmountaintop, where the\nBig Bob-omb was?\nWhaddya say? When I say\nGo, let the race begin!\n\nReady....\n\n//Go!////Don't Go" },
            [CT_WARIO] = { CT_WARIO, "Hey, Wario! Is it true\nthat you beat the Big\nBob-omb? Cool!\nYou must be strong and\npretty fast. So, how fast\nare you anyway?\nFast enough to beat me...\nKoopa the Quick? I don't\nthink so. Just try me.\nHow about a race to the\nmountaintop, where the\nBig Bob-omb was?\nWhaddya say? When I say\nGo, let the race begin!\n\nReady....\n\n//Go!////Don't Go" },
            [CT_WALUIGI] = { CT_WALUIGI, "Hey, Waluigi! Is it true\nthat you beat the Big\nBob-omb? Cool!\nYou must be strong and\npretty fast. So, how fast\nare you anyway?\nFast enough to beat me...\nKoopa the Quick? I don't\nthink so. Just try me.\nHow about a race to the\nmountaintop, where the\nBig Bob-omb was?\nWhaddya say? When I say\nGo, let the race begin!\n\nReady....\n\n//Go!////Don't Go" },
            [CT_TOAD] = { CT_TOAD, "Hey, Toad! Is it true\nthat you beat the Big\nBob-omb? Cool!\nYou must be strong and\npretty fast. So, how fast\nare you anyway?\nFast enough to beat me...\nKoopa the Quick? I don't\nthink so. Just try me.\nHow about a race to the\nmountaintop, where the\nBig Bob-omb was?\nWhaddya say? When I say\nGo, let the race begin!\n\nReady....\n\n//Go!////Don't Go" }
        }
    },
    
    {
        .dialogId = DIALOG_011,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "You've just stepped on\nthe Metal Cap Switch!\nThe Metal Cap makes\nMario invincible.\nNow Metal Caps will\npop out of all of the\ngreen blocks you find.\n\nWould you like to Save?\n\n//Yes////No" },
            [CT_LUIGI] = { CT_LUIGI, "You've just stepped on\nthe Metal Cap Switch!\nThe Metal Cap makes\nLuigi invincible.\nNow Metal Caps will\npop out of all of the\ngreen blocks you find.\n\nWould you like to Save?\n\n//Yes////No" },
            [CT_WARIO] = { CT_WARIO, "You've just stepped on\nthe Metal Cap Switch!\nThe Metal Cap makes\nWario invincible.\nNow Metal Caps will\npop out of all of the\ngreen blocks you find.\n\nWould you like to Save?\n\n//Yes////No" },
            [CT_WALUIGI] = { CT_WALUIGI, "You've just stepped on\nthe Metal Cap Switch!\nThe Metal Cap makes\nWaluigi invincible.\nNow Metal Caps will\npop out of all of the\ngreen blocks you find.\n\nWould you like to Save?\n\n//Yes////No" },
            [CT_TOAD] = { CT_TOAD, "You've just stepped on\nthe Metal Cap Switch!\nThe Metal Cap makes\nToad invincible.\nNow Metal Caps will\npop out of all of the\ngreen blocks you find.\n\nWould you like to Save?\n\n//Yes////No" }
        }
    },
    
    {
        .dialogId = DIALOG_012,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "You've just stepped on\nthe Vanish Cap Switch.\nThe Vanish Cap makes\nMario disappear.\nNow Vanish Caps will pop\nfrom all of the blue\nblocks you find.\n\nWould you like to Save?\n\n//Yes////No" },
            [CT_LUIGI] = { CT_LUIGI, "You've just stepped on\nthe Vanish Cap Switch.\nThe Vanish Cap makes\nLuigi disappear.\nNow Vanish Caps will pop\nfrom all of the blue\nblocks you find.\n\nWould you like to Save?\n\n//Yes////No" },
            [CT_WARIO] = { CT_WARIO, "You've just stepped on\nthe Vanish Cap Switch.\nThe Vanish Cap makes\nWario disappear.\nNow Vanish Caps will pop\nfrom all of the blue\nblocks you find.\n\nWould you like to Save?\n\n//Yes////No" },
            [CT_WALUIGI] = { CT_WALUIGI, "You've just stepped on\nthe Vanish Cap Switch.\nThe Vanish Cap makes\nWaluigi disappear.\nNow Vanish Caps will pop\nfrom all of the blue\nblocks you find.\n\nWould you like to Save?\n\n//Yes////No" },
            [CT_TOAD] = { CT_TOAD, "You've just stepped on\nthe Vanish Cap Switch.\nThe Vanish Cap makes\nToad disappear.\nNow Vanish Caps will pop\nfrom all of the blue\nblocks you find.\n\nWould you like to Save?\n\n//Yes////No" }
        }
    },
    
    {
        .dialogId = DIALOG_013,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "You've collected 100\ncoins! Mario gains more\npower from the castle.\nDo you want to Save?\n//Yes////No" },
            [CT_LUIGI] = { CT_LUIGI, "You've collected 100\ncoins! Luigi gains more\npower from the castle.\nDo you want to Save?\n//Yes////No" },
            [CT_WARIO] = { CT_WARIO, "You've collected 100\ncoins! Wario gains more\npower from the castle.\nDo you want to Save?\n//Yes////No" },
            [CT_WALUIGI] = { CT_WALUIGI, "You've collected 100\ncoins! Waluigi gains more\npower from the castle.\nDo you want to Save?\n//Yes////No" },
            [CT_TOAD] = { CT_TOAD, "You've collected 100\ncoins! Toad gains more\npower from the castle.\nDo you want to Save?\n//Yes////No" }
        }
    },
    
    {
        .dialogId = DIALOG_014,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Wow! Another Power Star!\nMario gains more courage\nfrom the power of the\ncastle.\nDo you want to Save?\n\n//You Bet//Not Now" },
            [CT_LUIGI] = { CT_LUIGI, "Wow! Another Power Star!\nLuigi gains more courage\nfrom the power of the\ncastle.\nDo you want to Save?\n\n//You Bet//Not Now" },
            [CT_WARIO] = { CT_WARIO, "Wow! Another Power Star!\nWario gains more courage\nfrom the power of the\ncastle.\nDo you want to Save?\n\n//You Bet//Not Now" },
            [CT_WALUIGI] = { CT_WALUIGI, "Wow! Another Power Star!\nWaluigi gains more courage\nfrom the power of the\ncastle.\nDo you want to Save?\n\n//You Bet//Not Now" },
            [CT_TOAD] = { CT_TOAD, "Wow! Another Power Star!\nToad gains more courage\nfrom the power of the\ncastle.\nDo you want to Save?\n\n//You Bet//Not Now" }
        }
    },
    
    {
        .dialogId = DIALOG_017,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "I'm the Big Bob-omb, lord\nof all blasting matter,\nking of ka-booms the\nworld over!\nHow dare you scale my\nmountain? By what right\ndo you set foot on my\nimperial mountaintop?\nYou may have eluded my\nguards, but you'll never\nescape my grasp...\n\n...and you'll never take\naway my Power Star. I\nhereby challenge you,\nMario!\nIf you want the Star I\nhold, you must prove\nyourself in battle.\n\nCan you pick me up from\nthe back and hurl me to\nthis royal turf? I think\nthat you cannot!" },
            [CT_LUIGI] = { CT_LUIGI, "I'm the Big Bob-omb, lord\nof all blasting matter,\nking of ka-booms the\nworld over!\nHow dare you scale my\nmountain? By what right\ndo you set foot on my\nimperial mountaintop?\nYou may have eluded my\nguards, but you'll never\nescape my grasp...\n\n...and you'll never take\naway my Power Star. I\nhereby challenge you,\nLuigi!\nIf you want the Star I\nhold, you must prove\nyourself in battle.\n\nCan you pick me up from\nthe back and hurl me to\nthis royal turf? I think\nthat you cannot!" },
            [CT_WARIO] = { CT_WARIO, "I'm the Big Bob-omb, lord\nof all blasting matter,\nking of ka-booms the\nworld over!\nHow dare you scale my\nmountain? By what right\ndo you set foot on my\nimperial mountaintop?\nYou may have eluded my\nguards, but you'll never\nescape my grasp...\n\n...and you'll never take\naway my Power Star. I\nhereby challenge you,\nWario!\nIf you want the Star I\nhold, you must prove\nyourself in battle.\n\nCan you pick me up from\nthe back and hurl me to\nthis royal turf? I think\nthat you cannot!" },
            [CT_WALUIGI] = { CT_WALUIGI, "I'm the Big Bob-omb, lord\nof all blasting matter,\nking of ka-booms the\nworld over!\nHow dare you scale my\nmountain? By what right\ndo you set foot on my\nimperial mountaintop?\nYou may have eluded my\nguards, but you'll never\nescape my grasp...\n\n...and you'll never take\naway my Power Star. I\nhereby challenge you,\nWaluigi!\nIf you want the Star I\nhold, you must prove\nyourself in battle.\n\nCan you pick me up from\nthe back and hurl me to\nthis royal turf? I think\nthat you cannot!" },
            [CT_TOAD] = { CT_TOAD, "I'm the Big Bob-omb, lord\nof all blasting matter,\nking of ka-booms the\nworld over!\nHow dare you scale my\nmountain? By what right\ndo you set foot on my\nimperial mountaintop?\nYou may have eluded my\nguards, but you'll never\nescape my grasp...\n\n...and you'll never take\naway my Power Star. I\nhereby challenge you,\nToad!\nIf you want the Star I\nhold, you must prove\nyourself in battle.\n\nCan you pick me up from\nthe back and hurl me to\nthis royal turf? I think\nthat you cannot!" }
        }
    },

    {
        .dialogId = DIALOG_020,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Dear Mario:\nPlease come to the\ncastle. I've baked\na cake for you.\nYours truly--\nPrincess Toadstool" },
            [CT_LUIGI] = { CT_LUIGI, "Dear Luigi:\nPlease come to the\ncastle. I've baked\na cake for you.\nYours truly--\nPrincess Toadstool" },
            [CT_WARIO] = { CT_WARIO, "Dear Wario:\nPlease come to the\ncastle. I've baked\na cake for you.\nYours truly--\nPrincess Toadstool" },
            [CT_WALUIGI] = { CT_WALUIGI, "Dear Waluigi:\nPlease come to the\ncastle. I've baked\na cake for you.\nYours truly--\nPrincess Toadstool" },
            [CT_TOAD] = { CT_TOAD, "Dear Toad:\nPlease come to the\ncastle. I've baked\na cake for you.\nYours truly--\nPrincess Toadstool" }
        }
    },

    {
        .dialogId = DIALOG_030,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Hello! The Lakitu Bros.,\ncutting in with a live\nupdate on Mario's\nprogress. He's about to\nlearn a technique for\nsneaking up on enemies.\nThe trick is this: He has\nto walk very slowly in\norder to walk quietly.\n\n\n\nAnd wrapping up filming\ntechniques reported on\nearlier, you can take a\nlook around using [C]▶ and\n[C]◀. Press [C]▼ to view the\naction from a distance.\nWhen you can't move the\ncamera any farther, the\nbuzzer will sound. This is\nthe Lakitu Bros.,\nsigning off." },
            [CT_LUIGI] = { CT_LUIGI, "Hello! The Lakitu Bros.,\ncutting in with a live\nupdate on Luigi's\nprogress. He's about to\nlearn a technique for\nsneaking up on enemies.\nThe trick is this: He has\nto walk very slowly in\norder to walk quietly.\n\n\n\nAnd wrapping up filming\ntechniques reported on\nearlier, you can take a\nlook around using [C]▶ and\n[C]◀. Press [C]▼ to view the\naction from a distance.\nWhen you can't move the\ncamera any farther, the\nbuzzer will sound. This is\nthe Lakitu Bros.,\nsigning off." },
            [CT_WARIO] = { CT_WARIO, "Hello! The Lakitu Bros.,\ncutting in with a live\nupdate on Wario's\nprogress. He's about to\nlearn a technique for\nsneaking up on enemies.\nThe trick is this: He has\nto walk very slowly in\norder to walk quietly.\n\n\n\nAnd wrapping up filming\ntechniques reported on\nearlier, you can take a\nlook around using [C]▶ and\n[C]◀. Press [C]▼ to view the\naction from a distance.\nWhen you can't move the\ncamera any farther, the\nbuzzer will sound. This is\nthe Lakitu Bros.,\nsigning off." },
            [CT_WALUIGI] = { CT_WALUIGI, "Hello! The Lakitu Bros.,\ncutting in with a live\nupdate on Waluigi's\nprogress. He's about to\nlearn a technique for\nsneaking up on enemies.\nThe trick is this: He has\nto walk very slowly in\norder to walk quietly.\n\n\n\nAnd wrapping up filming\ntechniques reported on\nearlier, you can take a\nlook around using [C]▶ and\n[C]◀. Press [C]▼ to view the\naction from a distance.\nWhen you can't move the\ncamera any farther, the\nbuzzer will sound. This is\nthe Lakitu Bros.,\nsigning off." },
            [CT_TOAD] = { CT_TOAD, "Hello! The Lakitu Bros.,\ncutting in with a live\nupdate on Toad's\nprogress. He's about to\nlearn a technique for\nsneaking up on enemies.\nThe trick is this: He has\nto walk very slowly in\norder to walk quietly.\n\n\n\nAnd wrapping up filming\ntechniques reported on\nearlier, you can take a\nlook around using [C]▶ and\n[C]◀. Press [C]▼ to view the\naction from a distance.\nWhen you can't move the\ncamera any farther, the\nbuzzer will sound. This is\nthe Lakitu Bros.,\nsigning off." }
        }
    },

    {
        .dialogId = DIALOG_031,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "No way! You beat me...\nagain!! And I just spent\nmy entire savings on\nthese new Koopa\nMach 1 Sprint shoes!\nHere, I guess I have to\nhand over this Star to\nthe winner of the race.\nCongrats, Mario!" },
            [CT_LUIGI] = { CT_LUIGI, "No way! You beat me...\nagain!! And I just spent\nmy entire savings on\nthese new Koopa\nMach 1 Sprint shoes!\nHere, I guess I have to\nhand over this Star to\nthe winner of the race.\nCongrats, Luigi!" },
            [CT_WARIO] = { CT_WARIO, "No way! You beat me...\nagain!! And I just spent\nmy entire savings on\nthese new Koopa\nMach 1 Sprint shoes!\nHere, I guess I have to\nhand over this Star to\nthe winner of the race.\nCongrats, Wario!" },
            [CT_WALUIGI] = { CT_WALUIGI, "No way! You beat me...\nagain!! And I just spent\nmy entire savings on\nthese new Koopa\nMach 1 Sprint shoes!\nHere, I guess I have to\nhand over this Star to\nthe winner of the race.\nCongrats, Waluigi!" },
            [CT_TOAD] = { CT_TOAD, "No way! You beat me...\nagain!! And I just spent\nmy entire savings on\nthese new Koopa\nMach 1 Sprint shoes!\nHere, I guess I have to\nhand over this Star to\nthe winner of the race.\nCongrats, Toad!" }
        }
    },

    {
        .dialogId = DIALOG_033,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Ciao! You've reached\nPrincess Toadstool's\ncastle via a warp pipe.\nUsing the controller is a\npiece of cake. Press [A] to\njump and [B] to attack.\nPress [B] to read signs,\ntoo. Use the Control Stick\nin the center of the\ncontroller to move Mario\naround. Now, head for\nthe castle." },
            [CT_LUIGI] = { CT_LUIGI, "Ciao! You've reached\nPrincess Toadstool's\ncastle via a warp pipe.\nUsing the controller is a\npiece of cake. Press [A] to\njump and [B] to attack.\nPress [B] to read signs,\ntoo. Use the Control Stick\nin the center of the\ncontroller to move Luigi\naround. Now, head for\nthe castle." },
            [CT_WARIO] = { CT_WARIO, "Ciao! You've reached\nPrincess Toadstool's\ncastle via a warp pipe.\nUsing the controller is a\npiece of cake. Press [A] to\njump and [B] to attack.\nPress [B] to read signs,\ntoo. Use the Control Stick\nin the center of the\ncontroller to move Wario\naround. Now, head for\nthe castle." },
            [CT_WALUIGI] = { CT_WALUIGI, "Ciao! You've reached\nPrincess Toadstool's\ncastle via a warp pipe.\nUsing the controller is a\npiece of cake. Press [A] to\njump and [B] to attack.\nPress [B] to read signs,\ntoo. Use the Control Stick\nin the center of the\ncontroller to move Waluigi\naround. Now, head for\nthe castle." },
            [CT_TOAD] = { CT_TOAD, "Ciao! You've reached\nPrincess Toadstool's\ncastle via a warp pipe.\nUsing the controller is a\npiece of cake. Press [A] to\njump and [B] to attack.\nPress [B] to read signs,\ntoo. Use the Control Stick\nin the center of the\ncontroller to move Toad\naround. Now, head for\nthe castle." }
        }
    },
    
    {
        .dialogId = DIALOG_034,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Good afternoon. The\nLakitu Bros., here,\nreporting live from just\noutside the Princess's\ncastle.\n\nMario has just arrived\non the scene, and we'll\nbe filming the action live\nas he enters the castle\nand pursues the missing\nPower Stars.\nAs seasoned cameramen,\nwe'll be shooting from the\nrecommended angle, but\nyou can change the\ncamera angle by pressing\nthe [C] Buttons.\nIf we can't adjust the\nview any further, we'll\nbuzz. To take a look at\nthe surroundings, stop\nand press [C]▲.\n\nPress [A] to resume play.\nSwitch camera modes with\nthe [R] Button. Signs along\nthe way will review these\ninstructions.\n\nFor now, reporting live,\nthis has been the\nLakitu Bros." },
            [CT_LUIGI] = { CT_LUIGI, "Good afternoon. The\nLakitu Bros., here,\nreporting live from just\noutside the Princess's\ncastle.\n\nLuigi has just arrived\non the scene, and we'll\nbe filming the action live\nas he enters the castle\nand pursues the missing\nPower Stars.\nAs seasoned cameramen,\nwe'll be shooting from the\nrecommended angle, but\nyou can change the\ncamera angle by pressing\nthe [C] Buttons.\nIf we can't adjust the\nview any further, we'll\nbuzz. To take a look at\nthe surroundings, stop\nand press [C]▲.\n\nPress [A] to resume play.\nSwitch camera modes with\nthe [R] Button. Signs along\nthe way will review these\ninstructions.\n\nFor now, reporting live,\nthis has been the\nLakitu Bros." },
            [CT_WARIO] = { CT_WARIO, "Good afternoon. The\nLakitu Bros., here,\nreporting live from just\noutside the Princess's\ncastle.\n\nWario has just arrived\non the scene, and we'll\nbe filming the action live\nas he enters the castle\nand pursues the missing\nPower Stars.\nAs seasoned cameramen,\nwe'll be shooting from the\nrecommended angle, but\nyou can change the\ncamera angle by pressing\nthe [C] Buttons.\nIf we can't adjust the\nview any further, we'll\nbuzz. To take a look at\nthe surroundings, stop\nand press [C]▲.\n\nPress [A] to resume play.\nSwitch camera modes with\nthe [R] Button. Signs along\nthe way will review these\ninstructions.\n\nFor now, reporting live,\nthis has been the\nLakitu Bros." },
            [CT_WALUIGI] = { CT_WALUIGI, "Good afternoon. The\nLakitu Bros., here,\nreporting live from just\noutside the Princess's\ncastle.\n\nWaluigi has just arrived\non the scene, and we'll\nbe filming the action live\nas he enters the castle\nand pursues the missing\nPower Stars.\nAs seasoned cameramen,\nwe'll be shooting from the\nrecommended angle, but\nyou can change the\ncamera angle by pressing\nthe [C] Buttons.\nIf we can't adjust the\nview any further, we'll\nbuzz. To take a look at\nthe surroundings, stop\nand press [C]▲.\n\nPress [A] to resume play.\nSwitch camera modes with\nthe [R] Button. Signs along\nthe way will review these\ninstructions.\n\nFor now, reporting live,\nthis has been the\nLakitu Bros." },
            [CT_TOAD] = { CT_TOAD, "Good afternoon. The\nLakitu Bros., here,\nreporting live from just\noutside the Princess's\ncastle.\n\nToad has just arrived\non the scene, and we'll\nbe filming the action live\nas he enters the castle\nand pursues the missing\nPower Stars.\nAs seasoned cameramen,\nwe'll be shooting from the\nrecommended angle, but\nyou can change the\ncamera angle by pressing\nthe [C] Buttons.\nIf we can't adjust the\nview any further, we'll\nbuzz. To take a look at\nthe surroundings, stop\nand press [C]▲.\n\nPress [A] to resume play.\nSwitch camera modes with\nthe [R] Button. Signs along\nthe way will review these\ninstructions.\n\nFor now, reporting live,\nthis has been the\nLakitu Bros." }
        }
    },

    {
        .dialogId = DIALOG_035,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "There are four camera, or\n『[C],』 Buttons. Press [C]▲\nto look around using the\nControl Stick.\n\nYou'll usually see Mario\nthrough Lakitu's camera.\nIt is the camera\nrecommended for normal\nplay.\nYou can change angles by\npressing [C]▶. If you press\n[R], the view switches to\nMario's camera, which\nis directly behind him.\nPress [R] again to return\nto Lakitu's camera. Press\n[C]▼ to see Mario from\nafar, using either\nLakitu's or Mario's view." },
            [CT_LUIGI] = { CT_LUIGI, "There are four camera, or\n『[C],』 Buttons. Press [C]▲\nto look around using the\nControl Stick.\n\nYou'll usually see Luigi\nthrough Lakitu's camera.\nIt is the camera\nrecommended for normal\nplay.\nYou can change angles by\npressing [C]▶. If you press\n[R], the view switches to\nLuigi's camera, which\nis directly behind him.\nPress [R] again to return\nto Lakitu's camera. Press\n[C]▼ to see Luigi from\nafar, using either\nLakitu's or Luigi's view." },
            [CT_WARIO] = { CT_WARIO, "There are four camera, or\n『[C],』 Buttons. Press [C]▲\nto look around using the\nControl Stick.\n\nYou'll usually see Wario\nthrough Lakitu's camera.\nIt is the camera\nrecommended for normal\nplay.\nYou can change angles by\npressing [C]▶. If you press\n[R], the view switches to\nWario's camera, which\nis directly behind him.\nPress [R] again to return\nto Lakitu's camera. Press\n[C]▼ to see Wario from\nafar, using either\nLakitu's or Wario's view." },
            [CT_WALUIGI] = { CT_WALUIGI, "There are four camera, or\n『[C],』 Buttons. Press [C]▲\nto look around using the\nControl Stick.\n\nYou'll usually see Waluigi\nthrough Lakitu's camera.\nIt is the camera\nrecommended for normal\nplay.\nYou can change angles by\npressing [C]▶. If you press\n[R], the view switches to\nWaluigi's camera, which\nis directly behind him.\nPress [R] again to return\nto Lakitu's camera. Press\n[C]▼ to see Waluigi from\nafar, using either\nLakitu's or Waluigi's view." },
            [CT_TOAD] = { CT_TOAD, "There are four camera, or\n『[C],』 Buttons. Press [C]▲\nto look around using the\nControl Stick.\n\nYou'll usually see Toad\nthrough Lakitu's camera.\nIt is the camera\nrecommended for normal\nplay.\nYou can change angles by\npressing [C]▶. If you press\n[R], the view switches to\nToad's camera, which\nis directly behind him.\nPress [R] again to return\nto Lakitu's camera. Press\n[C]▼ to see Toad from\nafar, using either\nLakitu's or Toad's view." }
        }
    },

    {
        .dialogId = DIALOG_036,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "OBSERVATION PLATFORM\nPress [C]▲ to take a look\naround. Don't miss\nanything!\n\nPress [R] to switch to\nMario's camera. It\nalways follows Mario.\nPress [R] again to switch\nto Lakitu's camera.\nPause the game and\nswitch the mode to 『fix』\nthe camera in place while\nholding [R]. Give it a try!" },
            [CT_LUIGI] = { CT_LUIGI, "OBSERVATION PLATFORM\nPress [C]▲ to take a look\naround. Don't miss\nanything!\n\nPress [R] to switch to\nLuigi's camera. It\nalways follows Luigi.\nPress [R] again to switch\nto Lakitu's camera.\nPause the game and\nswitch the mode to 『fix』\nthe camera in place while\nholding [R]. Give it a try!" },
            [CT_WARIO] = { CT_WARIO, "OBSERVATION PLATFORM\nPress [C]▲ to take a look\naround. Don't miss\nanything!\n\nPress [R] to switch to\nWario's camera. It\nalways follows Wario.\nPress [R] again to switch\nto Lakitu's camera.\nPause the game and\nswitch the mode to 『fix』\nthe camera in place while\nholding [R]. Give it a try!" },
            [CT_WALUIGI] = { CT_WALUIGI, "OBSERVATION PLATFORM\nPress [C]▲ to take a look\naround. Don't miss\nanything!\n\nPress [R] to switch to\nWaluigi's camera. It\nalways follows Waluigi.\nPress [R] again to switch\nto Lakitu's camera.\nPause the game and\nswitch the mode to 『fix』\nthe camera in place while\nholding [R]. Give it a try!" },
            [CT_TOAD] = { CT_TOAD, "OBSERVATION PLATFORM\nPress [C]▲ to take a look\naround. Don't miss\nanything!\n\nPress [R] to switch to\nToad's camera. It\nalways follows Toad.\nPress [R] again to switch\nto Lakitu's camera.\nPause the game and\nswitch the mode to 『fix』\nthe camera in place while\nholding [R]. Give it a try!" }
        }
    },

    {
        .dialogId = DIALOG_042,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Caution! Narrow Bridge!\nCross slowly!\n\n\nYou can jump to the edge\nof the cliff and hang on,\nand you can climb off the\nedge if you move slowly.\nWhen you want to let go,\neither press [Z] or press\nthe Control Stick in the\ndirection of Mario's back.\nTo climb up, press Up on\nthe Control Stick. To\nscurry up quickly, press\nthe [A] Button." },
            [CT_LUIGI] = { CT_LUIGI, "Caution! Narrow Bridge!\nCross slowly!\n\n\nYou can jump to the edge\nof the cliff and hang on,\nand you can climb off the\nedge if you move slowly.\nWhen you want to let go,\neither press [Z] or press\nthe Control Stick in the\ndirection of Luigi's back.\nTo climb up, press Up on\nthe Control Stick. To\nscurry up quickly, press\nthe [A] Button." },
            [CT_WARIO] = { CT_WARIO, "Caution! Narrow Bridge!\nCross slowly!\n\n\nYou can jump to the edge\nof the cliff and hang on,\nand you can climb off the\nedge if you move slowly.\nWhen you want to let go,\neither press [Z] or press\nthe Control Stick in the\ndirection of Wario's back.\nTo climb up, press Up on\nthe Control Stick. To\nscurry up quickly, press\nthe [A] Button." },
            [CT_WALUIGI] = { CT_WALUIGI, "Caution! Narrow Bridge!\nCross slowly!\n\n\nYou can jump to the edge\nof the cliff and hang on,\nand you can climb off the\nedge if you move slowly.\nWhen you want to let go,\neither press [Z] or press\nthe Control Stick in the\ndirection of Waluigi's back.\nTo climb up, press Up on\nthe Control Stick. To\nscurry up quickly, press\nthe [A] Button." },
            [CT_TOAD] = { CT_TOAD, "Caution! Narrow Bridge!\nCross slowly!\n\n\nYou can jump to the edge\nof the cliff and hang on,\nand you can climb off the\nedge if you move slowly.\nWhen you want to let go,\neither press [Z] or press\nthe Control Stick in the\ndirection of Toad's back.\nTo climb up, press Up on\nthe Control Stick. To\nscurry up quickly, press\nthe [A] Button." }
        }
    },

    {
        .dialogId = DIALOG_045,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Whew! I'm just about\nflapped out. You should\nlay off the pasta, Mario!\nThat's it for now. Press\n[A] to let go. Okay,\nbye byyyyyyeeee!" },
            [CT_LUIGI] = { CT_LUIGI, "Whew! I'm just about\nflapped out. You should\nlay off the pasta, Luigi!\nThat's it for now. Press\n[A] to let go. Okay,\nbye byyyyyyeeee!" },
            [CT_WARIO] = { CT_WARIO, "Whew! I'm just about\nflapped out. You should\nlay off the pasta, Wario!\nThat's it for now. Press\n[A] to let go. Okay,\nbye byyyyyyeeee!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Whew! I'm just about\nflapped out. You should\nlay off the pasta, Waluigi!\nThat's it for now. Press\n[A] to let go. Okay,\nbye byyyyyyeeee!" },
            [CT_TOAD] = { CT_TOAD, "Whew! I'm just about\nflapped out. You should\nlay off the pasta, Toad!\nThat's it for now. Press\n[A] to let go. Okay,\nbye byyyyyyeeee!" }
        }
    },

    {
        .dialogId = DIALOG_055,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Hey-ey, Mario, buddy,\nhowzit goin'? Step right\nup. You look like a fast\nsleddin' kind of guy.\nI know speed when I see\nit, yes siree--I'm the\nworld champion sledder,\nyou know. Whaddya say?\nHow about a race?\nReady...\n\n//Go//// Don't Go" },
            [CT_LUIGI] = { CT_LUIGI, "Hey-ey, Luigi, buddy,\nhowzit goin'? Step right\nup. You look like a fast\nsleddin' kind of guy.\nI know speed when I see\nit, yes siree--I'm the\nworld champion sledder,\nyou know. Whaddya say?\nHow about a race?\nReady...\n\n//Go//// Don't Go" },
            [CT_WARIO] = { CT_WARIO, "Hey-ey, Wario, buddy,\nhowzit goin'? Step right\nup. You look like a fast\nsleddin' kind of guy.\nI know speed when I see\nit, yes siree--I'm the\nworld champion sledder,\nyou know. Whaddya say?\nHow about a race?\nReady...\n\n//Go//// Don't Go" },
            [CT_WALUIGI] = { CT_WALUIGI, "Hey-ey, Waluigi, buddy,\nhowzit goin'? Step right\nup. You look like a fast\nsleddin' kind of guy.\nI know speed when I see\nit, yes siree--I'm the\nworld champion sledder,\nyou know. Whaddya say?\nHow about a race?\nReady...\n\n//Go//// Don't Go" },
            [CT_TOAD] = { CT_TOAD, "Hey-ey, Toad, buddy,\nhowzit goin'? Step right\nup. You look like a fast\nsleddin' kind of guy.\nI know speed when I see\nit, yes siree--I'm the\nworld champion sledder,\nyou know. Whaddya say?\nHow about a race?\nReady...\n\n//Go//// Don't Go" }
        }
    },

    {
        .dialogId = DIALOG_058,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "You found my precious,\nprecious baby! Where\nhave you been? How can\nI ever thank you, Mario?\nOh, I do have this...\n...Star. Here, take it\nwith my eternal\ngratitude." },
            [CT_LUIGI] = { CT_LUIGI, "You found my precious,\nprecious baby! Where\nhave you been? How can\nI ever thank you, Luigi?\nOh, I do have this...\n...Star. Here, take it\nwith my eternal\ngratitude." },
            [CT_WARIO] = { CT_WARIO, "You found my precious,\nprecious baby! Where\nhave you been? How can\nI ever thank you, Wario?\nOh, I do have this...\n...Star. Here, take it\nwith my eternal\ngratitude." },
            [CT_WALUIGI] = { CT_WALUIGI, "You found my precious,\nprecious baby! Where\nhave you been? How can\nI ever thank you, Waluigi?\nOh, I do have this...\n...Star. Here, take it\nwith my eternal\ngratitude." },
            [CT_TOAD] = { CT_TOAD, "You found my precious,\nprecious baby! Where\nhave you been? How can\nI ever thank you, Toad?\nOh, I do have this...\n...Star. Here, take it\nwith my eternal\ngratitude." }
        }
    },

    {
        .dialogId = DIALOG_064,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "When you put on the Wing\nCap that comes from a\nred block, do the Triple\nJump to soar high into\nthe sky.\nUse the Control Stick to\nguide Mario. Pull back to\nfly up, press forward to\nnose down, and press [Z]\nto land." },
            [CT_LUIGI] = { CT_LUIGI, "When you put on the Wing\nCap that comes from a\nred block, do the Triple\nJump to soar high into\nthe sky.\nUse the Control Stick to\nguide Luigi. Pull back to\nfly up, press forward to\nnose down, and press [Z]\nto land." },
            [CT_WARIO] = { CT_WARIO, "When you put on the Wing\nCap that comes from a\nred block, do the Triple\nJump to soar high into\nthe sky.\nUse the Control Stick to\nguide Wario. Pull back to\nfly up, press forward to\nnose down, and press [Z]\nto land." },
            [CT_WALUIGI] = { CT_WALUIGI, "When you put on the Wing\nCap that comes from a\nred block, do the Triple\nJump to soar high into\nthe sky.\nUse the Control Stick to\nguide Waluigi. Pull back to\nfly up, press forward to\nnose down, and press [Z]\nto land." },
            [CT_TOAD] = { CT_TOAD, "When you put on the Wing\nCap that comes from a\nred block, do the Triple\nJump to soar high into\nthe sky.\nUse the Control Stick to\nguide Toad. Pull back to\nfly up, press forward to\nnose down, and press [Z]\nto land." }
        }
    },

    {
        .dialogId = DIALOG_065,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Swimming Lessons!\nTap [A] to do the breast\nstroke. If you time the\ntaps right, you'll swim\nfast.\n\nPress and hold [A] to do a\nslow, steady flutter kick.\nPress Up on the Control\nStick to dive, and pull\nback on the stick to head\nfor the surface.\nTo jump out of the water,\nhold Down on the Control\nStick, then press [A].\nEasy as pie, right?\n\n\nBut remember:\nMario can't breathe under\nthe water! Return to the\nsurface for air when the\nPower Meter runs low.\n\nAnd one last thing: You\ncan't open doors that\nare underwater." },
            [CT_LUIGI] = { CT_LUIGI, "Swimming Lessons!\nTap [A] to do the breast\nstroke. If you time the\ntaps right, you'll swim\nfast.\n\nPress and hold [A] to do a\nslow, steady flutter kick.\nPress Up on the Control\nStick to dive, and pull\nback on the stick to head\nfor the surface.\nTo jump out of the water,\nhold Down on the Control\nStick, then press [A].\nEasy as pie, right?\n\n\nBut remember:\nLuigi can't breathe under\nthe water! Return to the\nsurface for air when the\nPower Meter runs low.\n\nAnd one last thing: You\ncan't open doors that\nare underwater." },
            [CT_WARIO] = { CT_WARIO, "Swimming Lessons!\nTap [A] to do the breast\nstroke. If you time the\ntaps right, you'll swim\nfast.\n\nPress and hold [A] to do a\nslow, steady flutter kick.\nPress Up on the Control\nStick to dive, and pull\nback on the stick to head\nfor the surface.\nTo jump out of the water,\nhold Down on the Control\nStick, then press [A].\nEasy as pie, right?\n\n\nBut remember:\nWario can't breathe under\nthe water! Return to the\nsurface for air when the\nPower Meter runs low.\n\nAnd one last thing: You\ncan't open doors that\nare underwater." },
            [CT_WALUIGI] = { CT_WALUIGI, "Swimming Lessons!\nTap [A] to do the breast\nstroke. If you time the\ntaps right, you'll swim\nfast.\n\nPress and hold [A] to do a\nslow, steady flutter kick.\nPress Up on the Control\nStick to dive, and pull\nback on the stick to head\nfor the surface.\nTo jump out of the water,\nhold Down on the Control\nStick, then press [A].\nEasy as pie, right?\n\n\nBut remember:\nWaluigi can't breathe under\nthe water! Return to the\nsurface for air when the\nPower Meter runs low.\n\nAnd one last thing: You\ncan't open doors that\nare underwater." },
            [CT_TOAD] = { CT_TOAD, "Swimming Lessons!\nTap [A] to do the breast\nstroke. If you time the\ntaps right, you'll swim\nfast.\n\nPress and hold [A] to do a\nslow, steady flutter kick.\nPress Up on the Control\nStick to dive, and pull\nback on the stick to head\nfor the surface.\nTo jump out of the water,\nhold Down on the Control\nStick, then press [A].\nEasy as pie, right?\n\n\nBut remember:\nToad can't breathe under\nthe water! Return to the\nsurface for air when the\nPower Meter runs low.\n\nAnd one last thing: You\ncan't open doors that\nare underwater." }
        }
    },

    {
        .dialogId = DIALOG_066,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Mario, it's Peach!\nPlease be careful! Bowser\nis so wicked! He will try\nto burn you with his\nhorrible flame breath.\nRun around behind and\ngrab him by the tail with\nthe [B] Button. Once you\ngrab hold, swing him\naround in great circles.\nRotate the Control Stick\nto go faster and faster.\nThe faster you swing him,\nthe farther he'll fly.\n\nUse the [C] Buttons to look\naround, Mario. You have\nto throw Bowser into one\nof the bombs in the four\ncorners.\nAim well, then press [B]\nagain to launch Bowser.\nGood luck, Mario! Our\nfate is in your hands." },
            [CT_LUIGI] = { CT_LUIGI, "Luigi, it's Peach!\nPlease be careful! Bowser\nis so wicked! He will try\nto burn you with his\nhorrible flame breath.\nRun around behind and\ngrab him by the tail with\nthe [B] Button. Once you\ngrab hold, swing him\naround in great circles.\nRotate the Control Stick\nto go faster and faster.\nThe faster you swing him,\nthe farther he'll fly.\n\nUse the [C] Buttons to look\naround, Luigi. You have\nto throw Bowser into one\nof the bombs in the four\ncorners.\nAim well, then press [B]\nagain to launch Bowser.\nGood luck, Luigi! Our\nfate is in your hands." },
            [CT_WARIO] = { CT_WARIO, "Wario, it's Peach!\nPlease be careful! Bowser\nis so wicked! He will try\nto burn you with his\nhorrible flame breath.\nRun around behind and\ngrab him by the tail with\nthe [B] Button. Once you\ngrab hold, swing him\naround in great circles.\nRotate the Control Stick\nto go faster and faster.\nThe faster you swing him,\nthe farther he'll fly.\n\nUse the [C] Buttons to look\naround, Wario. You have\nto throw Bowser into one\nof the bombs in the four\ncorners.\nAim well, then press [B]\nagain to launch Bowser.\nGood luck, Wario! Our\nfate is in your hands." },
            [CT_WALUIGI] = { CT_WALUIGI, "Waluigi, it's Peach!\nPlease be careful! Bowser\nis so wicked! He will try\nto burn you with his\nhorrible flame breath.\nRun around behind and\ngrab him by the tail with\nthe [B] Button. Once you\ngrab hold, swing him\naround in great circles.\nRotate the Control Stick\nto go faster and faster.\nThe faster you swing him,\nthe farther he'll fly.\n\nUse the [C] Buttons to look\naround, Waluigi. You have\nto throw Bowser into one\nof the bombs in the four\ncorners.\nAim well, then press [B]\nagain to launch Bowser.\nGood luck, Waluigi! Our\nfate is in your hands." },
            [CT_TOAD] = { CT_TOAD, "Toad, it's Peach!\nPlease be careful! Bowser\nis so wicked! He will try\nto burn you with his\nhorrible flame breath.\nRun around behind and\ngrab him by the tail with\nthe [B] Button. Once you\ngrab hold, swing him\naround in great circles.\nRotate the Control Stick\nto go faster and faster.\nThe faster you swing him,\nthe farther he'll fly.\n\nUse the [C] Buttons to look\naround, Toad. You have\nto throw Bowser into one\nof the bombs in the four\ncorners.\nAim well, then press [B]\nagain to launch Bowser.\nGood luck, Toad! Our\nfate is in your hands." }
        }
    },

    {
        .dialogId = DIALOG_067,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Tough luck, Mario!\nPrincess Toadstool isn't\nhere...Gwa ha ha!! Go\nahead--just try to grab\nme by the tail!\nYou'll never be able to\nswing ME around! A wimp\nlike you won't throw me\nout of here! Never! Ha!" },
            [CT_LUIGI] = { CT_LUIGI, "Tough luck, Luigi!\nPrincess Toadstool isn't\nhere...Gwa ha ha!! Go\nahead--just try to grab\nme by the tail!\nYou'll never be able to\nswing ME around! A wimp\nlike you won't throw me\nout of here! Never! Ha!" },
            [CT_WARIO] = { CT_WARIO, "Tough luck, Wario!\nPrincess Toadstool isn't\nhere...Gwa ha ha!! Go\nahead--just try to grab\nme by the tail!\nYou'll never be able to\nswing ME around! A wimp\nlike you won't throw me\nout of here! Never! Ha!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Tough luck, Waluigi!\nPrincess Toadstool isn't\nhere...Gwa ha ha!! Go\nahead--just try to grab\nme by the tail!\nYou'll never be able to\nswing ME around! A wimp\nlike you won't throw me\nout of here! Never! Ha!" },
            [CT_TOAD] = { CT_TOAD, "Tough luck, Toad!\nPrincess Toadstool isn't\nhere...Gwa ha ha!! Go\nahead--just try to grab\nme by the tail!\nYou'll never be able to\nswing ME around! A wimp\nlike you won't throw me\nout of here! Never! Ha!" }
        }
    },

    {
        .dialogId = DIALOG_068,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "It's Lethal Lava Land!\nIf you catch fire or fall\ninto a pool of flames,\nyou'll be hopping mad, but\ndon't lose your cool.\nYou can still control\nMario--just try to keep\ncalm!" },
            [CT_LUIGI] = { CT_LUIGI, "It's Lethal Lava Land!\nIf you catch fire or fall\ninto a pool of flames,\nyou'll be hopping mad, but\ndon't lose your cool.\nYou can still control\nLuigi--just try to keep\ncalm!" },
            [CT_WARIO] = { CT_WARIO, "It's Lethal Lava Land!\nIf you catch fire or fall\ninto a pool of flames,\nyou'll be hopping mad, but\ndon't lose your cool.\nYou can still control\nWario--just try to keep\ncalm!" },
            [CT_WALUIGI] = { CT_WALUIGI, "It's Lethal Lava Land!\nIf you catch fire or fall\ninto a pool of flames,\nyou'll be hopping mad, but\ndon't lose your cool.\nYou can still control\nWaluigi--just try to keep\ncalm!" },
            [CT_TOAD] = { CT_TOAD, "It's Lethal Lava Land!\nIf you catch fire or fall\ninto a pool of flames,\nyou'll be hopping mad, but\ndon't lose your cool.\nYou can still control\nToad--just try to keep\ncalm!" }
        }
    },

    {
        .dialogId = DIALOG_074,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "You can grab on to the\nedge of a cliff or ledge\nwith your fingertips and\nhang down from it.\n\nTo drop from the edge,\neither press the Control\nStick in the direction of\nMario's back or press the\n[Z] Button.\nTo get up onto the ledge,\neither press Up on the\nControl Stick or press [A]\nas soon as you grab the\nledge to climb up quickly." },
            [CT_LUIGI] = { CT_LUIGI, "You can grab on to the\nedge of a cliff or ledge\nwith your fingertips and\nhang down from it.\n\nTo drop from the edge,\neither press the Control\nStick in the direction of\nLuigi's back or press the\n[Z] Button.\nTo get up onto the ledge,\neither press Up on the\nControl Stick or press [A]\nas soon as you grab the\nledge to climb up quickly." },
            [CT_WARIO] = { CT_WARIO, "You can grab on to the\nedge of a cliff or ledge\nwith your fingertips and\nhang down from it.\n\nTo drop from the edge,\neither press the Control\nStick in the direction of\nWario's back or press the\n[Z] Button.\nTo get up onto the ledge,\neither press Up on the\nControl Stick or press [A]\nas soon as you grab the\nledge to climb up quickly." },
            [CT_WALUIGI] = { CT_WALUIGI, "You can grab on to the\nedge of a cliff or ledge\nwith your fingertips and\nhang down from it.\n\nTo drop from the edge,\neither press the Control\nStick in the direction of\nWaluigi's back or press the\n[Z] Button.\nTo get up onto the ledge,\neither press Up on the\nControl Stick or press [A]\nas soon as you grab the\nledge to climb up quickly." },
            [CT_TOAD] = { CT_TOAD, "You can grab on to the\nedge of a cliff or ledge\nwith your fingertips and\nhang down from it.\n\nTo drop from the edge,\neither press the Control\nStick in the direction of\nToad's back or press the\n[Z] Button.\nTo get up onto the ledge,\neither press Up on the\nControl Stick or press [A]\nas soon as you grab the\nledge to climb up quickly." }
        }
    },

    {
        .dialogId = DIALOG_075,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Mario!! My castle is in\ngreat peril. I know that\nBowser is the cause...and\nI know that only you can\nstop him!\nThe doors in the castle\nthat have been sealed by\nBowser can be opened only\nwith Star Power.\n\nBut there are secret\npaths in the castle,\npaths that Bowser hasn't\nfound.\n\nOne of those paths is in\nthis room, and it holds\none of the castle's Secret\nStars!\n\nFind that Secret Star,\nMario! It will help you\non your quest. Please,\nMario, you have to\nhelp us!\nRetrieve all of the\nPower Stars in the castle\nand free us from this\nawful prison!\nPlease!" },
            [CT_LUIGI] = { CT_LUIGI, "Luigi!! My castle is in\ngreat peril. I know that\nBowser is the cause...and\nI know that only you can\nstop him!\nThe doors in the castle\nthat have been sealed by\nBowser can be opened only\nwith Star Power.\n\nBut there are secret\npaths in the castle,\npaths that Bowser hasn't\nfound.\n\nOne of those paths is in\nthis room, and it holds\none of the castle's Secret\nStars!\n\nFind that Secret Star,\nLuigi! It will help you\non your quest. Please,\nLuigi, you have to\nhelp us!\nRetrieve all of the\nPower Stars in the castle\nand free us from this\nawful prison!\nPlease!" },
            [CT_WARIO] = { CT_WARIO, "Wario!! My castle is in\ngreat peril. I know that\nBowser is the cause...and\nI know that only you can\nstop him!\nThe doors in the castle\nthat have been sealed by\nBowser can be opened only\nwith Star Power.\n\nBut there are secret\npaths in the castle,\npaths that Bowser hasn't\nfound.\n\nOne of those paths is in\nthis room, and it holds\none of the castle's Secret\nStars!\n\nFind that Secret Star,\nWario! It will help you\non your quest. Please,\nWario, you have to\nhelp us!\nRetrieve all of the\nPower Stars in the castle\nand free us from this\nawful prison!\nPlease!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Waluigi!! My castle is in\ngreat peril. I know that\nBowser is the cause...and\nI know that only you can\nstop him!\nThe doors in the castle\nthat have been sealed by\nBowser can be opened only\nwith Star Power.\n\nBut there are secret\npaths in the castle,\npaths that Bowser hasn't\nfound.\n\nOne of those paths is in\nthis room, and it holds\none of the castle's Secret\nStars!\n\nFind that Secret Star,\nWaluigi! It will help you\non your quest. Please,\nWaluigi, you have to\nhelp us!\nRetrieve all of the\nPower Stars in the castle\nand free us from this\nawful prison!\nPlease!" },
            [CT_TOAD] = { CT_TOAD, "Toad!! My castle is in\ngreat peril. I know that\nBowser is the cause...and\nI know that only you can\nstop him!\nThe doors in the castle\nthat have been sealed by\nBowser can be opened only\nwith Star Power.\n\nBut there are secret\npaths in the castle,\npaths that Bowser hasn't\nfound.\n\nOne of those paths is in\nthis room, and it holds\none of the castle's Secret\nStars!\n\nFind that Secret Star,\nToad! It will help you\non your quest. Please,\nToad, you have to\nhelp us!\nRetrieve all of the\nPower Stars in the castle\nand free us from this\nawful prison!\nPlease!" }
        }
    },
    
    {
        .dialogId = DIALOG_076,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Mario, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting. Oh, by the\nway, look what I found!" },
            [CT_LUIGI] = { CT_LUIGI, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Luigi, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting. Oh, by the\nway, look what I found!" },
            [CT_WARIO] = { CT_WARIO, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Wario, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting. Oh, by the\nway, look what I found!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Waluigi, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting. Oh, by the\nway, look what I found!" },
            [CT_TOAD] = { CT_TOAD, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Toad, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting. Oh, by the\nway, look what I found!" }
        }
    },

    {
        .dialogId = DIALOG_082,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Hold on to your hat! If\nyou lose it, you'll be\ninjured easily.\n\nIf you do lose your Cap,\nyou'll have to find it in\nthe course where you\nlost it.\nOh, boy, it's not looking\ngood for Peach. She's\nstill trapped somewhere\ninside the walls.\nPlease, Mario, you have\nto help her! Did you know\nthat there are enemy\nworlds inside the walls?\nYup. It's true. Bowser's\ntroops are there, too.\nOh, here, take this. I've\nbeen keeping it for you." },
            [CT_LUIGI] = { CT_LUIGI, "Hold on to your hat! If\nyou lose it, you'll be\ninjured easily.\n\nIf you do lose your Cap,\nyou'll have to find it in\nthe course where you\nlost it.\nOh, boy, it's not looking\ngood for Peach. She's\nstill trapped somewhere\ninside the walls.\nPlease, Luigi, you have\nto help her! Did you know\nthat there are enemy\nworlds inside the walls?\nYup. It's true. Bowser's\ntroops are there, too.\nOh, here, take this. I've\nbeen keeping it for you." },
            [CT_WARIO] = { CT_WARIO, "Hold on to your hat! If\nyou lose it, you'll be\ninjured easily.\n\nIf you do lose your Cap,\nyou'll have to find it in\nthe course where you\nlost it.\nOh, boy, it's not looking\ngood for Peach. She's\nstill trapped somewhere\ninside the walls.\nPlease, Wario, you have\nto help her! Did you know\nthat there are enemy\nworlds inside the walls?\nYup. It's true. Bowser's\ntroops are there, too.\nOh, here, take this. I've\nbeen keeping it for you." },
            [CT_WALUIGI] = { CT_WALUIGI, "Hold on to your hat! If\nyou lose it, you'll be\ninjured easily.\n\nIf you do lose your Cap,\nyou'll have to find it in\nthe course where you\nlost it.\nOh, boy, it's not looking\ngood for Peach. She's\nstill trapped somewhere\ninside the walls.\nPlease, Waluigi, you have\nto help her! Did you know\nthat there are enemy\nworlds inside the walls?\nYup. It's true. Bowser's\ntroops are there, too.\nOh, here, take this. I've\nbeen keeping it for you." },
            [CT_TOAD] = { CT_TOAD, "Hold on to your hat! If\nyou lose it, you'll be\ninjured easily.\n\nIf you do lose your Cap,\nyou'll have to find it in\nthe course where you\nlost it.\nOh, boy, it's not looking\ngood for Peach. She's\nstill trapped somewhere\ninside the walls.\nPlease, Toad, you have\nto help her! Did you know\nthat there are enemy\nworlds inside the walls?\nYup. It's true. Bowser's\ntroops are there, too.\nOh, here, take this. I've\nbeen keeping it for you." }
        }
    },

    {
        .dialogId = DIALOG_083,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "There's something strange\nabout that clock. As you\njump inside, watch the\nposition of the big hand.\nOh, look what I found!\nHere, Mario, catch!" },
            [CT_LUIGI] = { CT_LUIGI, "There's something strange\nabout that clock. As you\njump inside, watch the\nposition of the big hand.\nOh, look what I found!\nHere, Luigi, catch!" },
            [CT_WARIO] = { CT_WARIO, "There's something strange\nabout that clock. As you\njump inside, watch the\nposition of the big hand.\nOh, look what I found!\nHere, Wario, catch!" },
            [CT_WALUIGI] = { CT_WALUIGI, "There's something strange\nabout that clock. As you\njump inside, watch the\nposition of the big hand.\nOh, look what I found!\nHere, Waluigi, catch!" },
            [CT_TOAD] = { CT_TOAD, "There's something strange\nabout that clock. As you\njump inside, watch the\nposition of the big hand.\nOh, look what I found!\nHere, Toad, catch!" }
        }
    },

    {
        .dialogId = DIALOG_092,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Pestering me again, are\nyou, Mario? Can't you see\nthat I'm having a merry\nlittle time, making\nmischief with my minions?\nNow, return those Stars!\nMy troops in the walls\nneed them! Bwa ha ha!" },
            [CT_LUIGI] = { CT_LUIGI, "Pestering me again, are\nyou, Luigi? Can't you see\nthat I'm having a merry\nlittle time, making\nmischief with my minions?\nNow, return those Stars!\nMy troops in the walls\nneed them! Bwa ha ha!" },
            [CT_WARIO] = { CT_WARIO, "Pestering me again, are\nyou, Wario? Can't you see\nthat I'm having a merry\nlittle time, making\nmischief with my minions?\nNow, return those Stars!\nMy troops in the walls\nneed them! Bwa ha ha!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Pestering me again, are\nyou, Waluigi? Can't you see\nthat I'm having a merry\nlittle time, making\nmischief with my minions?\nNow, return those Stars!\nMy troops in the walls\nneed them! Bwa ha ha!" },
            [CT_TOAD] = { CT_TOAD, "Pestering me again, are\nyou, Toad? Can't you see\nthat I'm having a merry\nlittle time, making\nmischief with my minions?\nNow, return those Stars!\nMy troops in the walls\nneed them! Bwa ha ha!" }
        }
    },
    
    {
        .dialogId = DIALOG_093,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Mario! You again! Well\nthat's just fine--I've\nbeen looking for something\nto fry with my fire\nbreath!\nYour Star Power is\nuseless against me!\nYour friends are all\ntrapped within the\nwalls...\nAnd you'll never see the\nPrincess again!\nBwa ha ha ha!" },
            [CT_LUIGI] = { CT_LUIGI, "Luigi! You again! Well\nthat's just fine--I've\nbeen looking for something\nslimy to roast with my\nfire breath!\nYour Star Power is\nuseless against me!\nYour friends are all\ntrapped within the\nwalls...\nAnd you'll never see the\nPrincess again!\nBwa ha ha ha!" },
            [CT_WARIO] = { CT_WARIO, "Wario! You again! Well\nthat's just fine--I've\nbeen looking for something\nfat to roast with my\nfire breath!\nYour Star Power is\nuseless against me!\nYour friends are all\ntrapped within the\nwalls...\nAnd you'll never see the\nPrincess again!\nBwa ha ha ha!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Waluigi! You again! Well\nthat's just fine--I've\nbeen looking for something\ntall to roast with my\nfire breath!\nYour Star Power is\nuseless against me!\nYour friends are all\ntrapped within the\nwalls...\nAnd you'll never see the\nPrincess again!\nBwa ha ha ha!" },
            [CT_TOAD] = { CT_TOAD, "Toad! You again! Well\nthat's just fine--I've\nbeen looking for something\nsmall to roast with my\nfire breath!\nYour Star Power is\nuseless against me!\nYour friends are all\ntrapped within the\nwalls...\nAnd you'll never see the\nPrincess again!\nBwa ha ha ha!" }
        }
    },

    {
        .dialogId = DIALOG_116,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Whaaa....Whaaat?\nCan it be that a\npipsqueak like you has\ndefused the Bob-omb\nking????\nYou might be fast enough\nto ground me, but you'll\nhave to pick up the pace\nif you want to take King\nBowser by the tail.\nMethinks my troops could\nlearn a lesson from you!\nHere is your Star, as I\npromised, Mario.\n\nIf you want to see me\nagain, select this Star\nfrom the menu. For now,\nfarewell." },
            [CT_LUIGI] = { CT_LUIGI, "Whaaa....Whaaat?\nCan it be that a\npipsqueak like you has\ndefused the Bob-omb\nking????\nYou might be fast enough\nto ground me, but you'll\nhave to pick up the pace\nif you want to take King\nBowser by the tail.\nMethinks my troops could\nlearn a lesson from you!\nHere is your Star, as I\npromised, Luigi.\n\nIf you want to see me\nagain, select this Star\nfrom the menu. For now,\nfarewell." },
            [CT_WARIO] = { CT_WARIO, "Whaaa....Whaaat?\nCan it be that a\npipsqueak like you has\ndefused the Bob-omb\nking????\nYou might be fast enough\nto ground me, but you'll\nhave to pick up the pace\nif you want to take King\nBowser by the tail.\nMethinks my troops could\nlearn a lesson from you!\nHere is your Star, as I\npromised, Wario.\n\nIf you want to see me\nagain, select this Star\nfrom the menu. For now,\nfarewell." },
            [CT_WALUIGI] = { CT_WALUIGI, "Whaaa....Whaaat?\nCan it be that a\npipsqueak like you has\ndefused the Bob-omb\nking????\nYou might be fast enough\nto ground me, but you'll\nhave to pick up the pace\nif you want to take King\nBowser by the tail.\nMethinks my troops could\nlearn a lesson from you!\nHere is your Star, as I\npromised, Waluigi.\n\nIf you want to see me\nagain, select this Star\nfrom the menu. For now,\nfarewell." },
            [CT_TOAD] = { CT_TOAD, "Whaaa....Whaaat?\nCan it be that a\npipsqueak like you has\ndefused the Bob-omb\nking????\nYou might be fast enough\nto ground me, but you'll\nhave to pick up the pace\nif you want to take King\nBowser by the tail.\nMethinks my troops could\nlearn a lesson from you!\nHere is your Star, as I\npromised, Toad.\n\nIf you want to see me\nagain, select this Star\nfrom the menu. For now,\nfarewell." }
        }
    },

    {
        .dialogId = DIALOG_121,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Nooo! It can't be!\nYou've really beaten me,\nMario?!! I gave those\ntroops power, but now\nit's fading away!\nArrgghh! I can see peace\nreturning to the world! I\ncan't stand it! Hmmm...\nIt's not over yet...\n\nC'mon troops! Let's watch\nthe ending together!\nBwa ha ha!" },
            [CT_LUIGI] = { CT_LUIGI, "Nooo! It can't be!\nYou've really beaten me,\nLuigi?!! I gave those\ntroops power, but now\nit's fading away!\nArrgghh! I can see peace\nreturning to the world! I\ncan't stand it! Hmmm...\nIt's not over yet...\n\nC'mon troops! Let's watch\nthe ending together!\nBwa ha ha!" },
            [CT_WARIO] = { CT_WARIO, "Nooo! It can't be!\nYou've really beaten me,\nWario?!! I gave those\ntroops power, but now\nit's fading away!\nArrgghh! I can see peace\nreturning to the world! I\ncan't stand it! Hmmm...\nIt's not over yet...\n\nC'mon troops! Let's watch\nthe ending together!\nBwa ha ha!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Nooo! It can't be!\nYou've really beaten me,\nWaluigi?!! I gave those\ntroops power, but now\nit's fading away!\nArrgghh! I can see peace\nreturning to the world! I\ncan't stand it! Hmmm...\nIt's not over yet...\n\nC'mon troops! Let's watch\nthe ending together!\nBwa ha ha!" },
            [CT_TOAD] = { CT_TOAD, "Nooo! It can't be!\nYou've really beaten me,\nToad?!! I gave those\ntroops power, but now\nit's fading away!\nArrgghh! I can see peace\nreturning to the world! I\ncan't stand it! Hmmm...\nIt's not over yet...\n\nC'mon troops! Let's watch\nthe ending together!\nBwa ha ha!" }
        }
    },

    {
        .dialogId = DIALOG_132,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Whoa, Mario, pal, you\naren't trying to cheat,\nare you? Shortcuts aren't\nallowed.\nNow, I know that you\nknow better. You're\ndisqualified! Next time,\nplay fair!" },
            [CT_LUIGI] = { CT_LUIGI, "Whoa, Luigi, pal, you\naren't trying to cheat,\nare you? Shortcuts aren't\nallowed.\nNow, I know that you\nknow better. You're\ndisqualified! Next time,\nplay fair!" },
            [CT_WARIO] = { CT_WARIO, "Whoa, Wario, pal, you\naren't trying to cheat,\nare you? Shortcuts aren't\nallowed.\nNow, I know that you\nknow better. You're\ndisqualified! Next time,\nplay fair!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Whoa, Waluigi, pal, you\naren't trying to cheat,\nare you? Shortcuts aren't\nallowed.\nNow, I know that you\nknow better. You're\ndisqualified! Next time,\nplay fair!" },
            [CT_TOAD] = { CT_TOAD, "Whoa, Toad, pal?\nYou aren't trying to cheat,\nare you? Shortcuts aren't\nallowed.\nNow, I know that you\nknow better. You're\ndisqualified! Next time,\nplay fair!" }
        }
    },

    {
        .dialogId = DIALOG_136,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Wow! You've already\nrecovered that many\nStars? Way to go, Mario!\nI'll bet you'll have us out\nof here in no time!\n\nBe careful, though.\nBowser and his band\nwrote the book on bad.\nTake my advice: When you\nneed to recover from\ninjuries, collect coins.\nYellow Coins refill one\npiece of the Power Meter,\nRed Coins refill two\npieces, and Blue Coins\nrefill five.\n\nTo make Blue Coins\nappear, pound on Blue\nCoin Blocks.\n\n\n\nAlso, if you fall from\nhigh places, you'll\nminimize damage if you\nPound the Ground as you\nland." },
            [CT_LUIGI] = { CT_LUIGI, "Wow! You've already\nrecovered that many\nStars? Way to go, Luigi!\nI'll bet you'll have us out\nof here in no time!\n\nBe careful, though.\nBowser and his band\nwrote the book on bad.\nTake my advice: When you\nneed to recover from\ninjuries, collect coins.\nYellow Coins refill one\npiece of the Power Meter,\nRed Coins refill two\npieces, and Blue Coins\nrefill five.\n\nTo make Blue Coins\nappear, pound on Blue\nCoin Blocks.\n\n\n\nAlso, if you fall from\nhigh places, you'll\nminimize damage if you\nPound the Ground as you\nland." },
            [CT_WARIO] = { CT_WARIO, "Wow! You've already\nrecovered that many\nStars? Way to go, Wario!\nI'll bet you'll have us out\nof here in no time!\n\nBe careful, though.\nBowser and his band\nwrote the book on bad.\nTake my advice: When you\nneed to recover from\ninjuries, collect coins.\nYellow Coins refill one\npiece of the Power Meter,\nRed Coins refill two\npieces, and Blue Coins\nrefill five.\n\nTo make Blue Coins\nappear, pound on Blue\nCoin Blocks.\n\n\n\nAlso, if you fall from\nhigh places, you'll\nminimize damage if you\nPound the Ground as you\nland." },
            [CT_WALUIGI] = { CT_WALUIGI, "Wow! You've already\nrecovered that many\nStars? Way to go, Waluigi!\nI'll bet you'll have us out\nof here in no time!\n\nBe careful, though.\nBowser and his band\nwrote the book on bad.\nTake my advice: When you\nneed to recover from\ninjuries, collect coins.\nYellow Coins refill one\npiece of the Power Meter,\nRed Coins refill two\npieces, and Blue Coins\nrefill five.\n\nTo make Blue Coins\nappear, pound on Blue\nCoin Blocks.\n\n\n\nAlso, if you fall from\nhigh places, you'll\nminimize damage if you\nPound the Ground as you\nland." },
            [CT_TOAD] = { CT_TOAD, "Wow! You've already\nrecovered that many\nStars? Way to go, Toad!\nI'll bet you'll have us out\nof here in no time!\n\nBe careful, though.\nBowser and his band\nwrote the book on bad.\nTake my advice: When you\nneed to recover from\ninjuries, collect coins.\nYellow Coins refill one\npiece of the Power Meter,\nRed Coins refill two\npieces, and Blue Coins\nrefill five.\n\nTo make Blue Coins\nappear, pound on Blue\nCoin Blocks.\n\n\n\nAlso, if you fall from\nhigh places, you'll\nminimize damage if you\nPound the Ground as you\nland." }
        }
    },

    {
        .dialogId = DIALOG_137,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Thanks, Mario! The castle\nis recovering its energy\nas you retrieve Power\nStars, and you've chased\nBowser right out of here,\non to some area ahead.\nOh, by the by, are you\ncollecting coins? Special\nStars appear when you\ncollect 100 coins in each\nof the 15 courses!" },
            [CT_LUIGI] = { CT_LUIGI, "Thanks, Luigi! The castle\nis recovering its energy\nas you retrieve Power\nStars, and you've chased\nBowser right out of here,\non to some area ahead.\nOh, by the by, are you\ncollecting coins? Special\nStars appear when you\ncollect 100 coins in each\nof the 15 courses!" },
            [CT_WARIO] = { CT_WARIO, "Thanks, Wario! The castle\nis recovering its energy\nas you retrieve Power\nStars, and you've chased\nBowser right out of here,\non to some area ahead.\nOh, by the by, are you\ncollecting coins? Special\nStars appear when you\ncollect 100 coins in each\nof the 15 courses!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Thanks, Waluigi! The castle\nis recovering its energy\nas you retrieve Power\nStars, and you've chased\nBowser right out of here,\non to some area ahead.\nOh, by the by, are you\ncollecting coins? Special\nStars appear when you\ncollect 100 coins in each\nof the 15 courses!" },
            [CT_TOAD] = { CT_TOAD, "Thanks, Toad! The castle\nis recovering its energy\nas you retrieve Power\nStars, and you've chased\nBowser right out of here,\non to some area ahead.\nOh, by the by, are you\ncollecting coins? Special\nStars appear when you\ncollect 100 coins in each\nof the 15 courses!" }
        }
    },

    {
        .dialogId = DIALOG_141,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "You've recovered one of\nthe stolen Power Stars!\nNow you can open some of\nthe sealed doors in the\ncastle.\nTry the Princess's room\non the second floor and\nthe room with the\npainting of Whomp's\nFortress on Floor 1.\nBowser's troops are still\ngaining power, so you\ncan't give up. Save us,\nMario! Keep searching for\nStars!" },
            [CT_LUIGI] = { CT_LUIGI, "You've recovered one of\nthe stolen Power Stars!\nNow you can open some of\nthe sealed doors in the\ncastle.\nTry the Princess's room\non the second floor and\nthe room with the\npainting of Whomp's\nFortress on Floor 1.\nBowser's troops are still\ngaining power, so you\ncan't give up. Save us,\nLuigi! Keep searching for\nStars!" },
            [CT_WARIO] = { CT_WARIO, "You've recovered one of\nthe stolen Power Stars!\nNow you can open some of\nthe sealed doors in the\ncastle.\nTry the Princess's room\non the second floor and\nthe room with the\npainting of Whomp's\nFortress on Floor 1.\nBowser's troops are still\ngaining power, so you\ncan't give up. Save us,\nWario! Keep searching for\nStars!" },
            [CT_WALUIGI] = { CT_WALUIGI, "You've recovered one of\nthe stolen Power Stars!\nNow you can open some of\nthe sealed doors in the\ncastle.\nTry the Princess's room\non the second floor and\nthe room with the\npainting of Whomp's\nFortress on Floor 1.\nBowser's troops are still\ngaining power, so you\ncan't give up. Save us,\nWaluigi! Keep searching for\nStars!" },
            [CT_TOAD] = { CT_TOAD, "You've recovered one of\nthe stolen Power Stars!\nNow you can open some of\nthe sealed doors in the\ncastle.\nTry the Princess's room\non the second floor and\nthe room with the\npainting of Whomp's\nFortress on Floor 1.\nBowser's troops are still\ngaining power, so you\ncan't give up. Save us,\nToad! Keep searching for\nStars!" }
        }
    },

    {
        .dialogId = DIALOG_154,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Hold on to your hat! If\nyou lose it, you'll be\neasily injured. If you\nlose it, look for it in the\ncourse where you lost it.\nSpeaking of lost, the\nPrincess is still stuck in\nthe walls somewhere.\nPlease help, Mario!\n\nOh, you know that there\nare secret worlds in the\nwalls as well as in the\npaintings, right?" },
            [CT_LUIGI] = { CT_LUIGI, "Hold on to your hat! If\nyou lose it, you'll be\neasily injured. If you\nlose it, look for it in the\ncourse where you lost it.\nSpeaking of lost, the\nPrincess is still stuck in\nthe walls somewhere.\nPlease help, Luigi!\n\nOh, you know that there\nare secret worlds in the\nwalls as well as in the\npaintings, right?" },
            [CT_WARIO] = { CT_WARIO, "Hold on to your hat! If\nyou lose it, you'll be\neasily injured. If you\nlose it, look for it in the\ncourse where you lost it.\nSpeaking of lost, the\nPrincess is still stuck in\nthe walls somewhere.\nPlease help, Wario!\n\nOh, you know that there\nare secret worlds in the\nwalls as well as in the\npaintings, right?" },
            [CT_WALUIGI] = { CT_WALUIGI, "Hold on to your hat! If\nyou lose it, you'll be\neasily injured. If you\nlose it, look for it in the\ncourse where you lost it.\nSpeaking of lost, the\nPrincess is still stuck in\nthe walls somewhere.\nPlease help, Waluigi!\n\nOh, you know that there\nare secret worlds in the\nwalls as well as in the\npaintings, right?" },
            [CT_TOAD] = { CT_TOAD, "Hold on to your hat! If\nyou lose it, you'll be\neasily injured. If you\nlose it, look for it in the\ncourse where you lost it.\nSpeaking of lost, the\nPrincess is still stuck in\nthe walls somewhere.\nPlease help, Toad!\n\nOh, you know that there\nare secret worlds in the\nwalls as well as in the\npaintings, right?" }
        }
    },

    {
        .dialogId = DIALOG_155,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Mario, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting." },
            [CT_LUIGI] = { CT_LUIGI, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Luigi, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting." },
            [CT_WARIO] = { CT_WARIO, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Wario, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting." },
            [CT_WALUIGI] = { CT_WALUIGI, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Waluigi, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting." },
            [CT_TOAD] = { CT_TOAD, "Thanks to the power of\nthe Stars, life is\nreturning to the castle.\nPlease, Toad, you have\nto give Bowser the boot!\n\nHere, let me tell you a\nlittle something about the\ncastle. In the room with\nthe mirrors, look carefully\nfor anything that's not\nreflected in the mirror.\nAnd when you go to the\nwater town, you can flood\nit with a high jump into\nthe painting." }
        }
    },

    {
        .dialogId = DIALOG_161,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Mario!!!\nIt that really you???\nIt has been so long since\nour last adventure!\nThey told me that I might\nsee you if I waited here,\nbut I'd just about given\nup hope!\nIs it true? Have you\nreally beaten Bowser? And\nrestored the Stars to the\ncastle?\nAnd saved the Princess?\nI knew you could do it!\nNow I have a very special\nmessage for you.\nThanks for playing Super\nMario 64! This is the\nend of the game, but not\nthe end of the fun.\n\nThe Super Mario 64 Team" },
            [CT_LUIGI] = { CT_LUIGI, "Luigi!!!\nIt that really you???\nIt has been so long since\nour last adventure!\nThey told me that I might\nsee you if I waited here,\nbut I'd just about given\nup hope!\nIs it true? Have you\nreally beaten Bowser? And\nrestored the Stars to the\ncastle?\nAnd saved the Princess?\nI knew you could do it!\nNow I have a very special\nmessage for you.\nThanks for playing Super\nMario 64! This is the\nend of the game, but not\nthe end of the fun.\n\nThe Super Mario 64 Team" },
            [CT_WARIO] = { CT_WARIO, "Wario!!!\nIt that really you???\nIt has been so long since\nour last adventure!\nThey told me that I might\nsee you if I waited here,\nbut I'd just about given\nup hope!\nIs it true? Have you\nreally beaten Bowser? And\nrestored the Stars to the\ncastle?\nAnd saved the Princess?\nI knew you could do it!\nNow I have a very special\nmessage for you.\nThanks for playing Super\nMario 64! This is the\nend of the game, but not\nthe end of the fun.\n\nThe Super Mario 64 Team" },
            [CT_WALUIGI] = { CT_WALUIGI, "Waluigi!!!\nIt that really you???\nIt has been so long since\nour last adventure!\nThey told me that I might\nsee you if I waited here,\nbut I'd just about given\nup hope!\nIs it true? Have you\nreally beaten Bowser? And\nrestored the Stars to the\ncastle?\nAnd saved the Princess?\nI knew you could do it!\nNow I have a very special\nmessage for you.\nThanks for playing Super\nMario 64! This is the\nend of the game, but not\nthe end of the fun.\n\nThe Super Mario 64 Team" },
            [CT_TOAD] = { CT_TOAD, "Toad!!!\nIt that really you???\nIt has been so long since\nour last adventure!\nThey told me that I might\nsee you if I waited here,\nbut I'd just about given\nup hope!\nIs it true? Have you\nreally beaten Bowser? And\nrestored the Stars to the\ncastle?\nAnd saved the Princess?\nI knew you could do it!\nNow I have a very special\nmessage for you.\nThanks for playing Super\nMario 64! This is the\nend of the game, but not\nthe end of the fun.\n\nThe Super Mario 64 Team" }
        }
    },

    {
        .dialogId = DIALOG_163,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Noooo! You've really\nbeaten me this time,\nMario! I can't stand\nlosing to you!\n\nMy troops...worthless!\nThey've turned over all\nthe Power Stars! What?!\nThere are 120 in all???\n\nAmazing! There were some\nin the castle that I\nmissed??!!\n\n\nNow I see peace\nreturning to the world...\nOooo! I really hate that!\nI can't watch--\nI'm outta here!\nJust you wait until next\ntime. Until then, keep\nthat Control Stick\nsmokin'!\nBuwaa ha ha!" },
            [CT_LUIGI] = { CT_LUIGI, "Noooo! You've really\nbeaten me this time,\nLuigi! I can't stand\nlosing to you!\n\nMy troops...worthless!\nThey've turned over all\nthe Power Stars! What?!\nThere are 120 in all???\n\nAmazing! There were some\nin the castle that I\nmissed??!!\n\n\nNow I see peace\nreturning to the world...\nOooo! I really hate that!\nI can't watch--\nI'm outta here!\nJust you wait until next\ntime. Until then, keep\nthat Control Stick\nsmokin'!\nBuwaa ha ha!" },
            [CT_WARIO] = { CT_WARIO, "Noooo! You've really\nbeaten me this time,\nWario! I can't stand\nlosing to you!\n\nMy troops...worthless!\nThey've turned over all\nthe Power Stars! What?!\nThere are 120 in all???\n\nAmazing! There were some\nin the castle that I\nmissed??!!\n\n\nNow I see peace\nreturning to the world...\nOooo! I really hate that!\nI can't watch--\nI'm outta here!\nJust you wait until next\ntime. Until then, keep\nthat Control Stick\nsmokin'!\nBuwaa ha ha!" },
            [CT_WALUIGI] = { CT_WALUIGI, "Noooo! You've really\nbeaten me this time,\nWaluigi! I can't stand\nlosing to you!\n\nMy troops...worthless!\nThey've turned over all\nthe Power Stars! What?!\nThere are 120 in all???\n\nAmazing! There were some\nin the castle that I\nmissed??!!\n\n\nNow I see peace\nreturning to the world...\nOooo! I really hate that!\nI can't watch--\nI'm outta here!\nJust you wait until next\ntime. Until then, keep\nthat Control Stick\nsmokin'!\nBuwaa ha ha!" },
            [CT_TOAD] = { CT_TOAD, "Noooo! You've really\nbeaten me this time,\nToad! I can't stand\nlosing to you!\n\nMy troops...worthless!\nThey've turned over all\nthe Power Stars! What?!\nThere are 120 in all???\n\nAmazing! There were some\nin the castle that I\nmissed??!!\n\n\nNow I see peace\nreturning to the world...\nOooo! I really hate that!\nI can't watch--\nI'm outta here!\nJust you wait until next\ntime. Until then, keep\nthat Control Stick\nsmokin'!\nBuwaa ha ha!" }
        }
    },

    {
        .dialogId = DIALOG_164,
        .variants = {
            [CT_MARIO] = { CT_MARIO, "Mario! What's up, pal?\nI haven't been on the\nslide lately, so I'm out\nof shape.\nStill, I'm always up for a\ngood race, especially\nagainst an old sleddin'\nbuddy.\nWhaddya say?\nReady...set...\n\n//Go//// Don't Go" },
            [CT_LUIGI] = { CT_LUIGI, "Luigi! What's up, pal?\nI haven't been on the\nslide lately, so I'm out\nof shape.\nStill, I'm always up for a\ngood race, especially\nagainst an old sleddin'\nbuddy.\nWhaddya say?\nReady...set...\n\n//Go//// Don't Go" },
            [CT_WARIO] = { CT_WARIO, "Wario! What's up, pal?\nI haven't been on the\nslide lately, so I'm out\nof shape.\nStill, I'm always up for a\ngood race, especially\nagainst an old sleddin'\nbuddy.\nWhaddya say?\nReady...set...\n\n//Go//// Don't Go" },
            [CT_WALUIGI] = { CT_WALUIGI, "Waluigi! What's up, pal?\nI haven't been on the\nslide lately, so I'm out\nof shape.\nStill, I'm always up for a\ngood race, especially\nagainst an old sleddin'\nbuddy.\nWhaddya say?\nReady...set...\n\n//Go//// Don't Go" },
            [CT_TOAD] = { CT_TOAD, "Toad! What's up, pal?\nI haven't been on the\nslide lately, so I'm out\nof shape.\nStill, I'm always up for a\ngood race, especially\nagainst an old sleddin'\nbuddy.\nWhaddya say?\nReady...set...\n\n//Go//// Don't Go" }
        }
    }
};

/*this all below is the dialog registering to find out what what player model is being used
instead of having the mario model dialog varient checked maybe i can make it check if there isnt a model being used and have a better fallback to mario pulled from the rom?
^this might work better if i add custom model support?*/
struct CharacterDialogEntry* gCharacterDialogs = sCharacterDialogs;
s32 gCharacterDialogCount = sizeof(sCharacterDialogs) / sizeof(sCharacterDialogs[0]);

void init_character_dialog_system(void) {
}

static struct CharacterDialogEntry* find_dialog_entry(enum DialogId dialogId) {
    if (gCharacterDialogCount == 0) {
        return NULL;
    }
    if (dialogId < sCharacterDialogs[0].dialogId || 
        dialogId > sCharacterDialogs[gCharacterDialogCount - 1].dialogId) {
        return NULL;
    }
    
    s32 left = 0;
    s32 right = gCharacterDialogCount - 1;
    
    while (left <= right) {
        s32 mid = left + ((right - left) >> 1);
        if (sCharacterDialogs[mid].dialogId == dialogId) {
            return &sCharacterDialogs[mid];
        } else if (sCharacterDialogs[mid].dialogId < dialogId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return NULL;
}

const char* get_character_dialog_text(enum DialogId dialogId, enum CharacterType characterType) {
    if (dialogId < 0) {
        return NULL;
    }
    struct CharacterDialogEntry* entry = find_dialog_entry(dialogId);
    if (entry && entry->variants[characterType].text) {
        return entry->variants[characterType].text;
    }
    return NULL;
}

struct CharacterDialogEntry* get_character_dialog_entry(enum DialogId dialogId) {
    if (dialogId < 0) {
        return NULL;
    }
    return find_dialog_entry(dialogId);
}

void update_character_dialogs(void) {
    extern s16 gDialogID;

    if (gDialogID == -1) {
        return;
    }
    struct MarioState* m = &gMarioStates[0];
    if (!m || !m->character) {
        return;
    }
    enum CharacterType characterType = m->character->type;
    if (characterType < 0 || characterType >= CT_MAX) {
        characterType = CT_MARIO;
    }

    struct CharacterDialogEntry* entry = find_dialog_entry(gDialogID);
    if (entry) {
        const char* characterText = entry->variants[characterType].text;
        if (characterText) {
            void **dialogTable = segmented_to_virtual(seg2_dialog_table);
            struct DialogEntry *originalDialog = segmented_to_virtual(dialogTable[gDialogID]);

            smlua_text_utils_dialog_replace(entry->dialogId, originalDialog->unused, 
                                          originalDialog->linesPerBox, originalDialog->leftOffset, 
                                          originalDialog->width, characterText);
        }
    }
}
