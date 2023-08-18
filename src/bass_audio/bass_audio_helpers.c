#include "include/bass/bass.h"
#include "include/bass/bass_fx.h"
#include "pc/debuglog.h"

#include "bass_audio_helpers.h"

HSTREAM bassh_create_fx_stream_from_file(const char* data, QWORD length, QWORD offset) {
    HSTREAM raw_stream = BASS_StreamCreateFile(TRUE, data, offset, length, BASS_STREAM_PRESCAN | BASS_STREAM_DECODE);

    HSTREAM stream = BASS_FX_TempoCreate(raw_stream, BASS_STREAM_PRESCAN);

    return stream;
}

HSAMPLE bassh_create_sample_from_file(const char* data, QWORD length, QWORD offset) {
    return BASS_SampleLoad(TRUE, data, offset, length, MAX_SAMPLE_CONCURRENT_PLAYBACKS, BASS_SAMPLE_OVER_POS);
}

HSTREAM bassh_sample_get_stream(HSAMPLE sample) {
    return BASS_SampleGetChannel(sample, 0);
}

void bassh_free_sample(HSAMPLE sample) {
    BASS_SampleFree(sample);
}

void bassh_stop_sample(HSAMPLE sample) {
    BASS_SampleStop(sample);
}

void bassh_set_looping(HSTREAM stream, BOOL loop) {
    BASS_ChannelFlags(stream, loop == TRUE ? BASS_SAMPLE_LOOP : 0, BASS_SAMPLE_LOOP);
}

BOOL bassh_get_looping(HSTREAM stream) {
    return (BASS_ChannelFlags(stream, 0, 0) & BASS_SAMPLE_LOOP) > 0;
}

void bassh_set_frequency(HSTREAM stream, float frequency) {
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_FREQ, frequency);
}

float bassh_get_frequency(HSTREAM stream) {
    float val;
    BASS_ChannelGetAttribute(stream, BASS_ATTRIB_FREQ, &val);

    return val;
}

void bassh_set_tempo(HSTREAM stream, float tempo) {
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_TEMPO, tempo);
}

float bassh_get_tempo(HSTREAM stream) {
    float val;
    BASS_ChannelGetAttribute(stream, BASS_ATTRIB_TEMPO, &val);

    return val;
}

double bassh_get_stream_pos(HSTREAM stream) {
    DWORD pos_b = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);
    return BASS_ChannelBytes2Seconds(stream, pos_b);
}

void bassh_set_stream_pos(HSTREAM stream, double pos) {
    BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, pos), BASS_POS_BYTE);
}

void bassh_set_speed(HSTREAM stream, float initial_freq, float speed, BOOL pitch) {
    if (pitch) {
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_FREQ, initial_freq * speed);
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_TEMPO, 0);
    }
    else {
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_FREQ, initial_freq);
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_TEMPO, speed * 100 - 100);
    }
}

void bassh_set_stream_volume(HSTREAM stream, float volume) {
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_MUSIC_VOL_CHAN, volume);
}

float bassh_get_stream_volume(HSTREAM stream) {
    float volume;
    
    BASS_ChannelGetAttribute(stream, BASS_ATTRIB_MUSIC_VOL_CHAN, &volume);

    return volume;
}

void bassh_play_stream(HSTREAM stream, BOOL restart) {
    BASS_ChannelPlay(stream, restart);
}

void bassh_pause_stream(HSTREAM stream) {
    BASS_ChannelPause(stream);
}

void bassh_stop_stream(HSTREAM stream) {
    BASS_ChannelStop(stream);
}

void bassh_free_stream(HSTREAM stream) {
    BASS_ChannelFree(stream);
}

void bassh_init() {
    BOOL success = BASS_Init(-1, 44100, 0, 0, 0);

    if(success == FALSE) {
        //error handling? fucking nerd shit
        LOG_ERROR("Bass init failed!");
        return;
    }

    BASS_DEVICEINFO info;
    BASS_GetDeviceInfo(BASS_GetDevice(), &info);

    LOG_INFO("Bass Initialized on device: %s, with driver: %s", info.name, info.driver);
}

void bassh_deinit() {
    BASS_Free();
}

int bassh_device_count() {
    int count = 0;

    BASS_DEVICEINFO info;
    for(count = 0; BASS_GetDeviceInfo(count, &info); count++) {}

    return count;
}