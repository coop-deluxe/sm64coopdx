#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <PR/ultratypes.h>

#include "types.h"
#include "area.h"

#include "course_table.h"

#define EEPROM_SIZE 0x200
#define NUM_SAVE_FILES 4

struct SaveBlockSignature
{
    u16 magic;
    u16 chksum;
};

struct SaveFile
{
    // Location of lost cap.
    // Note: the coordinates get set, but are never actually used, since the
    // cap can always be found in a fixed spot within the course
    u8 capLevel;
    u8 capArea;
    Vec3s capPos;

    u32 flags;

    // Star flags for each course.
    // The most significant bit of the byte *following* each course is set if the
    // cannon is open.
    u8 courseStars[COURSE_COUNT];

    u8 courseCoinScores[COURSE_STAGES_COUNT];

    struct SaveBlockSignature signature;
};

enum SaveFileIndex {
    SAVE_FILE_A,
    SAVE_FILE_B,
    SAVE_FILE_C,
    SAVE_FILE_D
};

struct MainMenuSaveData
{
    // Each save file has a 2 bit "age" for each course. The higher this value,
    // the older the high score is. This is used for tie-breaking when displaying
    // on the high score screen.
    u32 coinScoreAges[NUM_SAVE_FILES];
    u16 soundMode;

#ifdef VERSION_EU
    u16 language;
#define SUBTRAHEND 8
#else
#define SUBTRAHEND 6
#endif

    // Pad to match the EEPROM size of 0x200 (10 bytes on JP/US, 8 bytes on EU)
    u8 filler[EEPROM_SIZE / 2 - SUBTRAHEND - NUM_SAVE_FILES * (4 + sizeof(struct SaveFile))];

    struct SaveBlockSignature signature;
};

struct SaveBuffer
{
    // Each of the four save files has two copies. If one is bad, the other is used as a backup.
    struct SaveFile files[NUM_SAVE_FILES][2];
    // The main menu data has two copies. If one is bad, the other is used as a backup.
    struct MainMenuSaveData menuData[2];
};

extern u8 gLastCompletedCourseNum;
extern u8 gLastCompletedStarNum;
extern s8 sUnusedGotGlobalCoinHiScore;
extern u8 gGotFileCoinHiScore;
extern u8 gCurrCourseStarFlags;
extern s8 gLevelToCourseNumTable[];

// game progress flags
#define SAVE_FLAG_FILE_EXISTS            /* 0x00000001 */ (1 << 0)
#define SAVE_FLAG_HAVE_WING_CAP          /* 0x00000002 */ (1 << 1)
#define SAVE_FLAG_HAVE_METAL_CAP         /* 0x00000004 */ (1 << 2)
#define SAVE_FLAG_HAVE_VANISH_CAP        /* 0x00000008 */ (1 << 3)
#define SAVE_FLAG_HAVE_KEY_1             /* 0x00000010 */ (1 << 4)
#define SAVE_FLAG_HAVE_KEY_2             /* 0x00000020 */ (1 << 5)
#define SAVE_FLAG_UNLOCKED_BASEMENT_DOOR /* 0x00000040 */ (1 << 6)
#define SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR /* 0x00000080 */ (1 << 7)
#define SAVE_FLAG_DDD_MOVED_BACK         /* 0x00000100 */ (1 << 8)
#define SAVE_FLAG_MOAT_DRAINED           /* 0x00000200 */ (1 << 9)
#define SAVE_FLAG_UNLOCKED_PSS_DOOR      /* 0x00000400 */ (1 << 10)
#define SAVE_FLAG_UNLOCKED_WF_DOOR       /* 0x00000800 */ (1 << 11)
#define SAVE_FLAG_UNLOCKED_CCM_DOOR      /* 0x00001000 */ (1 << 12)
#define SAVE_FLAG_UNLOCKED_JRB_DOOR      /* 0x00002000 */ (1 << 13)
#define SAVE_FLAG_UNLOCKED_BITDW_DOOR    /* 0x00004000 */ (1 << 14)
#define SAVE_FLAG_UNLOCKED_BITFS_DOOR    /* 0x00008000 */ (1 << 15)
#define SAVE_FLAG_CAP_ON_GROUND          /* 0x00010000 */ (1 << 16)
#define SAVE_FLAG_CAP_ON_KLEPTO          /* 0x00020000 */ (1 << 17)
#define SAVE_FLAG_CAP_ON_UKIKI           /* 0x00040000 */ (1 << 18)
#define SAVE_FLAG_CAP_ON_MR_BLIZZARD     /* 0x00080000 */ (1 << 19)
#define SAVE_FLAG_UNLOCKED_50_STAR_DOOR  /* 0x00100000 */ (1 << 20)
#define SAVE_FLAG_COLLECTED_TOAD_STAR_1  /* 0x01000000 */ (1 << 24)
#define SAVE_FLAG_COLLECTED_TOAD_STAR_2  /* 0x02000000 */ (1 << 25)
#define SAVE_FLAG_COLLECTED_TOAD_STAR_3  /* 0x04000000 */ (1 << 26)
#define SAVE_FLAG_COLLECTED_MIPS_STAR_1  /* 0x08000000 */ (1 << 27)
#define SAVE_FLAG_COLLECTED_MIPS_STAR_2  /* 0x10000000 */ (1 << 28)

#define SAVE_FLAG_TO_STAR_FLAG(cmd) (((cmd) >> 24) & 0x7F)
#define STAR_FLAG_TO_SAVE_FLAG(cmd) ((cmd) << 24)

// Variable for setting a warp checkpoint.

// possibly a WarpDest struct where arg is a union. TODO: Check?
struct WarpCheckpoint {
    /*0x00*/ u8 actNum;
    /*0x01*/ u8 courseNum;
    /*0x02*/ u8 levelID;
    /*0x03*/ u8 areaNum;
    /*0x04*/ u8 warpNode;
};

extern struct WarpCheckpoint gWarpCheckpoint;

extern s8 gMainMenuDataModified;
extern s8 gSaveFileModified;

s8 get_level_num_from_course_num(s16 courseNum);
s8 get_level_course_num(s16 levelNum);

/* |description|
Marks the coin score for a specific course as the newest among all save files. Adjusts the age of other scores to reflect the update.
Useful for leaderboard tracking or displaying recent progress
|descriptionEnd| */
void touch_coin_score_age(s32 fileIndex, s32 courseIndex);

/* |description|
Saves the current state of the game into a specified save file. Includes data verification and backup management.
Useful for maintaining game progress during play or when saving manually
|descriptionEnd| */
void save_file_do_save(s32 fileIndex, s8 forceSave);

/* |description|
Erases all data in a specified save file, including backup slots. Marks the save file as modified and performs a save to apply the changes.
Useful for resetting a save file to its default state
|descriptionEnd| */
void save_file_erase(s32 fileIndex);

/* |description|
Erases the backup data for the current save file without affecting the primary save data. Reloads the save file afterward
|descriptionEnd| */
void save_file_erase_current_backup_save(void);

BAD_RETURN(s32) save_file_copy(s32 srcFileIndex, s32 destFileIndex);
void save_file_load_all(u8 reload);

/* |description|
Reloads the save file data into memory, optionally resetting all save files. Marks the save file as modified.
Useful for reloading state after data corruption or during development debugging
|descriptionEnd| */
void save_file_reload(u8 load_all);

void save_file_collect_star_or_key(s16 coinScore, s16 starIndex, u8 fromNetwork);
s32 save_file_exists(s32 fileIndex);

/* |description|
Determines the maximum coin score for a course across all save files. Returns the score along with the file index of the save containing it.
Useful for leaderboard-style comparisons and overall progress tracking
|descriptionEnd| */
u32 save_file_get_max_coin_score(s32 courseIndex);

/* |description|
Calculates the total number of stars collected in a specific course for a given save file.
Useful for determining completion status of individual levels
|descriptionEnd| */
s32 save_file_get_course_star_count(s32 fileIndex, s32 courseIndex);

/* |description|
Calculates the total number of stars collected across multiple courses within a specified range.
Useful for determining the overall progress toward game completion
|descriptionEnd| */
s32 save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);

/* |description|
Adds new flags to the save file's flag bitmask.
Useful for updating progress or triggering new gameplay features
|descriptionEnd| */
void save_file_set_flags(u32 flags);

/* |description|
Clears specific flags in the current save file. The flags are specified as a bitmask in the `flags` parameter. Ensures that the save file remains valid after clearing.
Useful for removing specific game states, such as collected items or completed objectives, without resetting the entire save
|descriptionEnd| */
void save_file_clear_flags(u32 flags);

/* |description|
Retrieves the bitmask of flags representing the current state of the save file. Flags indicate collected items, completed objectives, and other game states.
Useful for checking specific game progress details
|descriptionEnd| */
u32 save_file_get_flags(void);

/* |description|
Retrieves the bitmask of stars collected in a specific course or castle secret stars (-1).
Useful for evaluating level progress and completion
|descriptionEnd| */
u32 save_file_get_star_flags(s32 fileIndex, s32 courseIndex);

/* |description|
Adds specific star flags to the save file, indicating collected stars for a course or castle secret stars. Updates the save file flags as necessary.
Useful for recording progress after star collection
|descriptionEnd| */
void save_file_set_star_flags(s32 fileIndex, s32 courseIndex, u32 starFlags);

/* |description|
Removes specific star flags from the save file. This modifies the bitmask representing collected stars for a course or castle secret stars.
Useful for undoing progress or debugging collected stars
|descriptionEnd| */
void save_file_remove_star_flags(s32 fileIndex, s32 courseIndex, u32 starFlagsToRemove);

/* |description|
Returns the highest coin score for a specified course in the save file. Performs checks to ensure the coin score is valid.
Useful for tracking player achievements and high scores
|descriptionEnd| */
s32 save_file_get_course_coin_score(s32 fileIndex, s32 courseIndex);

/* |description|
Updates the coin score for a specific course in the save file. The new score is provided in the `coinScore` parameter.
Useful for manually setting achievements such as high coin counts in individual levels
|descriptionEnd| */
void save_file_set_course_coin_score(s32 fileIndex, s32 courseIndex, u8 coinScore);

/* |description|
Checks whether the cannon in the specified course is unlocked. Returns true if the cannon is unlocked, otherwise false.
Useful for tracking course-specific progress and enabling shortcuts
|descriptionEnd| */
s32 save_file_is_cannon_unlocked(s32 fileIndex, s32 courseIndex);

void save_file_set_cannon_unlocked(void);
void save_file_set_cap_pos(s16 x, s16 y, s16 z);

/* |description|
Retrieves the current position of Mario's cap, if it is on the ground in the current level and area. The position is stored in the provided `capPos` parameter.
Useful for tracking the cap's location after it has been dropped or lost
|descriptionEnd| */
s32 save_file_get_cap_pos(Vec3s capPos);

void save_file_set_sound_mode(u16 mode);

/* |description|
Returns the current sound mode (e.g., stereo, mono) stored in the save file.
Useful for checking the audio output preferences when loading a save
|descriptionEnd| */
u16 save_file_get_sound_mode(void);

void save_file_move_cap_to_default_location(void);
void disable_warp_checkpoint(void);
void check_if_should_set_warp_checkpoint(struct WarpNode *warpNode);
s32 check_warp_checkpoint(struct WarpNode *warpNode);

#ifdef VERSION_EU
enum EuLanguages {
    LANGUAGE_ENGLISH,
    LANGUAGE_FRENCH,
    LANGUAGE_GERMAN,
    LANGUAGE_MAX
};

void eu_set_language(u16 language);
u16 eu_get_language(void);
#endif

#endif // SAVE_FILE_H
