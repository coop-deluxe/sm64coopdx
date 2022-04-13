#ifndef SMLUA_AUDIO_UTILS_H
#define SMLUA_AUDIO_UTILS_H

void smlua_audio_utils_reset_all(void);
bool smlua_audio_utils_override(u8 sequenceId, s32* bankId, void** seqData);
void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, u8 defaultVolume, const char* m64Name);

#endif