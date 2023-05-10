#include <ultra64.h>
#include "internal.h"
#include "load.h"
#include "data.h"
#include "seqplayer.h"
#include "synthesis.h"
#include "pc/debuglog.h"

#ifdef VERSION_EU

#ifdef __sgi
#define stubbed_printf
#else
#define stubbed_printf(...)
#endif

#define SAMPLES_TO_OVERPRODUCE 0x10
#define EXTRA_BUFFERED_AI_SAMPLES_TARGET 0x40

#ifdef VERSION_JP
typedef u16 FadeT;
#else
typedef s32 FadeT;
#endif

extern volatile u8 gAudioResetStatus;
extern u8 gAudioResetPresetIdToLoad;
extern OSMesgQueue *OSMesgQueues[];
extern struct EuAudioCmd sAudioCmd[0x100];

void seq_player_fade_from_zero_volume(s32 player, FadeT fadeInTime);
void seq_player_fade_to_zero_volume(s32 player, FadeT fadeOutTime);
void port_eu_init_queues(void);
void decrease_sample_dma_ttls(void);
s32 audio_shut_down_and_reset_step(void);
void process_queued_audio_cmds(u32);

struct SPTask *create_next_audio_frame_task(void) {
    return NULL;
}
void create_next_audio_buffer(s16 *samples, u32 num_samples) {
    s32 writtenCmds;
    OSMesg msg;
 
    gAudioFrameCount++;
    decrease_sample_dma_ttls();
    if (osRecvMesg(OSMesgQueues[2], &msg, OS_MESG_NOBLOCK) != -1) {
        gAudioResetPresetIdToLoad = (u8) (s32) msg;
        gAudioResetStatus = 5;
    }

    if (gAudioResetStatus != 0) {
        audio_reset_session();
        gAudioResetStatus = 0;
    }
    if (osRecvMesg(OSMesgQueues[1], &msg, OS_MESG_NOBLOCK) != -1) {
        process_queued_audio_cmds((u32) msg);
    }
    synthesis_execute(gAudioCmdBuffers[0], &writtenCmds, samples, num_samples);
    gAudioRandom = ((gAudioRandom + gAudioFrameCount) * gAudioFrameCount);
    gAudioRandom = gAudioRandom + writtenCmds / 8;
}

void eu_process_audio_cmd(struct EuAudioCmd *cmd) {
    s32 i;

    switch (cmd->u.s.op) {
    case AUDIO_CMD_PRELOAD_SEQUENCE:
        preload_sequence(cmd->u.s.arg2, PRELOAD_BANKS | PRELOAD_SEQUENCE);
        break;

    case AUDIO_CMD_LOAD_SEQUENCE:
    case AUDIO_CMD_LOAD_SEQUENCE2:
        load_sequence(cmd->u.s.arg1, cmd->u.s.arg2, cmd->u.s.arg3);
        seq_player_fade_from_zero_volume(cmd->u.s.arg1, cmd->u2.as_s32);
        //LOG_DEBUG("Playing sequence with arguments: %d, 0x%X, %d", cmd->u.s.arg1, cmd->u.s.arg2, cmd->u.s.arg3);
        break;

    case AUDIO_CMD_FADE_TO_ZERO_VOLUME:
        if (gSequencePlayers[cmd->u.s.arg1].enabled != FALSE) {
            if (cmd->u2.as_s32 == 0) {
                sequence_player_disable(&gSequencePlayers[cmd->u.s.arg1]);
            }
            else {
                seq_player_fade_to_zero_volume(cmd->u.s.arg1, cmd->u2.as_s32);
            }
        }
        break;

    case AUDIO_CMD_SOUND_MODE:
        gSoundMode = cmd->u2.as_s32;
        break;

    case AUDIO_CMD_MUTE_ALL_SEQUENCE_PLAYERS:
        for (i = 0; i < 4; i++) {
            gSequencePlayers[i].muted = TRUE;
            gSequencePlayers[i].recalculateVolume = TRUE;
        }
        break;

    case AUDIO_CMD_UNMUTE_ALL_SEQUENCE_PLAYERS:
        for (i = 0; i < 4; i++) {
            gSequencePlayers[i].muted = FALSE;
            gSequencePlayers[i].recalculateVolume = TRUE;
        }
        break;
    }
}

const char undefportcmd[] = "Undefined Port Command %d\n";

extern OSMesgQueue *OSMesgQueues[];
extern u8 gQueuedAudioCmdCount;
extern u8 gLastQueuedAudioCmdCount;
extern OSMesg OSMesg0;
extern OSMesg OSMesg1;
extern OSMesg OSMesg2;
extern OSMesg OSMesg3;

void seq_player_fade_to_zero_volume(s32 player, FadeT fadeOutTime) {
    if (fadeOutTime == 0) {
        fadeOutTime = 1;
    }
    gSequencePlayers[player].fadeVelocity = -(gSequencePlayers[player].fadeVolume / fadeOutTime);
    gSequencePlayers[player].state = 2; // These are reversed compared to USA, Which is 2 for a fade in and 1 for a fade out.
    gSequencePlayers[player].fadeRemainingFrames = fadeOutTime;

}

void seq_player_fade_from_zero_volume(s32 player, FadeT fadeInTime) {
    if (fadeInTime != 0) {
        gSequencePlayers[player].state = 1; // These are reversed compared to USA, Which is 2 for a fade in and 1 for a fade out.
        gSequencePlayers[player].fadeTimerUnkEu = fadeInTime;
        gSequencePlayers[player].fadeRemainingFrames = fadeInTime;
        gSequencePlayers[player].fadeVolume = 0.0f;
        gSequencePlayers[player].fadeVelocity = 0.0f;
    }
}

void port_eu_init_queues(void) {
    gQueuedAudioCmdCount = 0;
    gLastQueuedAudioCmdCount = 0;
    osCreateMesgQueue(OSMesgQueues[0], &OSMesg0, 1);
    osCreateMesgQueue(OSMesgQueues[1], &OSMesg1, 4);
    osCreateMesgQueue(OSMesgQueues[2], &OSMesg2, 1);
    osCreateMesgQueue(OSMesgQueues[3], &OSMesg3, 1);
}

void queue_audio_cmd(s32 arg0, s32 *arg1) {
    struct EuAudioCmd *cmd = &sAudioCmd[gQueuedAudioCmdCount & 0xff];
    cmd->u.first = arg0;
    cmd->u2.as_u32 = *arg1;
    gQueuedAudioCmdCount++;
}

void queue_audio_cmd_f32(u32 arg0, f32 arg1) {
    queue_audio_cmd(arg0, (s32*) &arg1);
}

void queue_audio_cmd_u32(u32 arg0, u32 arg1) {
    queue_audio_cmd(arg0, (s32*) &arg1);
}

void queue_audio_cmd_s8(u32 arg0, s8 arg1) {
    s32 sp1C = arg1 << 24;
    queue_audio_cmd(arg0, &sp1C);
}

void send_process_queued_audio_cmds(void) {
    osSendMesg(OSMesgQueues[1],
            (OSMesg)(u32)((gLastQueuedAudioCmdCount & 0xff) << 8 | (gQueuedAudioCmdCount & 0xff)),
            OS_MESG_NOBLOCK);
    gLastQueuedAudioCmdCount = gQueuedAudioCmdCount;
}

void process_queued_audio_cmds(u32 arg0) {
    struct EuAudioCmd *cmd;
    struct SequencePlayer *seqPlayer;
    struct SequenceChannel *chan;
    u8 end = arg0 & 0xff;
    u8 i = (arg0 >> 8) & 0xff;

    for (;;) {
        if (i == end) break;
        cmd = &sAudioCmd[i++ & 0xff];

        if (cmd->u.s.arg1 < SEQUENCE_PLAYERS) {
            seqPlayer = &gSequencePlayers[cmd->u.s.arg1];
            if ((cmd->u.s.op & 0x80) != 0) {
                eu_process_audio_cmd(cmd);
            }
            else if ((cmd->u.s.op & 0x40) != 0) {
                switch (cmd->u.s.op) {
                case AUDIO_CMD_FADE_VOLUME_SCALE:
                    seqPlayer->fadeVolumeScale = cmd->u2.as_f32;
                    seqPlayer->recalculateVolume = TRUE;
                    break;

                case AUDIO_CMD_TEMPO:
                    seqPlayer->tempo = cmd->u2.as_s32 * TATUMS_PER_BEAT;
                    break;

                case AUDIO_CMD_TRANSPOSITION:
                    seqPlayer->transposition = cmd->u2.as_s8;
                    break;

                case AUDIO_CMD_SEQUENCE_VARIATION:
                    seqPlayer->seqVariationEu[cmd->u.s.arg3] = cmd->u2.as_s8;
                    break;
                }
            }
            else if (seqPlayer->enabled != FALSE && cmd->u.s.arg2 < 0x10) {
                chan = seqPlayer->channels[cmd->u.s.arg2];
                if (IS_SEQUENCE_CHANNEL_VALID(chan))
                {
                    switch (cmd->u.s.op) {
                    case AUDIO_CMD_VOLUME_SCALE:
                        chan->volumeScale = cmd->u2.as_f32;
                        chan->changes.as_bitfields.volume = TRUE;
                        break;
                    case AUDIO_CMD_VOLUME:
                        chan->volume = cmd->u2.as_f32;
                        chan->changes.as_bitfields.volume = TRUE;
                        break;
                    case AUDIO_CMD_NEW_PAN:
                        chan->newPan = cmd->u2.as_s8;
                        chan->changes.as_bitfields.pan = TRUE;
                        break;
                    case AUDIO_CMD_FREQ_SCALE:
                        chan->freqScale = cmd->u2.as_f32;
                        chan->changes.as_bitfields.freqScale = TRUE;
                        break;
                    case AUDIO_CMD_REVERB:
                        chan->reverb = cmd->u2.as_s8;
                        break;
                    case AUDIO_CMD_SOUND_SCRIPT:
                        if (cmd->u.s.arg3 < 8) {
                            chan->soundScriptIO[cmd->u.s.arg3] = cmd->u2.as_s8;
                        }
                        break;
                    case AUDIO_CMD_GENERAL_STOP:
                        chan->stopSomething2 = cmd->u2.as_s8;
                    }
                }
            }
        }

        cmd->u.s.op = 0;
    }
}

void port_eu_init(void) {
    port_eu_init_queues();
}

#endif
