#ifndef AUDIO_SEQPLAYER_H
#define AUDIO_SEQPLAYER_H

#include <PR/ultratypes.h>

#include "internal.h"
#include "playback.h"

void seq_channel_layer_disable(struct SequenceChannelLayer *seqPlayer);
void sequence_channel_disable(struct SequenceChannel *seqPlayer);
void sequence_player_disable(struct SequencePlayer* seqPlayer);
void audio_list_push_back(struct AudioListItem *list, struct AudioListItem *item);
void *audio_list_pop_back(struct AudioListItem *list);
void sequence_channel_set_volume(struct SequenceChannel *seqChannel, u8 volume);
void process_sequences(s32 iterationsRemaining);
void init_sequence_player(u32 player);
void init_sequence_players(void);
void sequence_player_set_tempo(u8 player, u16 tempo);
void sequence_player_set_tempoAcc(u8 player, u16 tempoAcc);
void sequence_player_set_transposition(u8 player, u16 transposition);
u16 sequence_player_get_tempo(u8 player);
u16 sequence_player_get_tempoAcc(u8 player);
u16 sequence_player_get_transposition(u8 player);

#endif // AUDIO_SEQPLAYER_H
