struct Character* get_character(struct MarioState* m);
void play_character_sound(struct MarioState* m, enum CharacterSound characterSound);
void play_character_sound_offset(struct MarioState* m, enum CharacterSound characterSound, u32 offset);
void play_character_sound_if_no_flag(struct MarioState* m, enum CharacterSound characterSound, u32 flags);
f32 get_character_anim_offset(struct MarioState* m);
void update_character_anim_offset(struct MarioState* m);
