#ifndef SMLUA_AUDIO_UTILS_H
#define SMLUA_AUDIO_UTILS_H

bool smlua_audio_utils_override(u8 sequenceId, s32* bankId, void** seqData);

void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, const char* m64Name);

#endif