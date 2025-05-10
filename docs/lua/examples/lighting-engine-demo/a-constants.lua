LEVEL_HL           = level_register("level_hl_entry", COURSE_BOB, "Black Mesa", "hl", 28000, 0x28, 0x28, 0x28)
LEVEL_CANALS       = level_register("level_canals_entry", COURSE_WF, "Sunset Canals", "canals", 28000, 0x20, 0x20, 0x20)

SOUND_CUSTOM_FLASHLIGHT = audio_sample_load("flashlight.ogg")

DEFAULT_LIGHTING_DIR = 0x28 / 127