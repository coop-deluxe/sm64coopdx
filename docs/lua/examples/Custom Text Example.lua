-- name: Custom Text
-- description: Replaces The King Bobomb Intro Dialog with custom text. Credit: ThePlayerRolo + ManIsCat2 (For fixing issues)

smlua_text_utils_dialog_replace(gBehaviorValues.dialogs.KingBobombIntroDialog, 1, 4, 100, 175, ("Hello.\
    I'm doing good,\
    Are you doing good?\
    No?\
    Then DIE!"
))

-- First parameter is what text you want to replace. To find the full table go to here: https://github.com/coop-deluxe/sm64coopdx/blob/main/docs/lua/functions-5.md
-- Second parameter is unused in the game.
-- Third parameter defines how many lines your dialog has per box.
-- Fourth parameter sets how much you want to offset you text to the left (higher number moves to the right- lower to the left.).
-- Fifth parameter is the width.
-- Sixth parameter is your text.
-- Have Fun!

-- The Function in C for Reference: #define DEFINE_DIALOG(id, unused, linesPerBox, leftOffset, width, text)
