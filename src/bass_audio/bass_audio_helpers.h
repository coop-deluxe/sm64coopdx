#include "include/bass/bass.h"

#define MAX_SAMPLE_CONCURRENT_PLAYBACKS 32

HSTREAM bassh_create_fx_stream_from_file(const char* data, QWORD length, QWORD offset);
HSAMPLE bassh_create_sample_from_file(const char* data, QWORD length, QWORD offset);

HSTREAM bassh_sample_get_stream(HSAMPLE sample);
void bassh_free_sample(HSAMPLE sample);
void bassh_stop_sample(HSAMPLE sample);
void bassh_set_looping(HSTREAM stream, BOOL loop);

void bassh_set_stream_volume(HSTREAM stream, float volume);
float bassh_get_stream_volume(HSTREAM stream);
void bassh_set_looping(HSTREAM stream, BOOL loop);
BOOL bassh_get_looping(HSTREAM stream);
void bassh_set_frequency(HSTREAM stream, float frequency);
float bassh_get_frequency(HSTREAM stream);
void bassh_set_tempo(HSTREAM stream, float tempo);
float bassh_get_tempo(HSTREAM stream);

void bassh_set_speed(HSTREAM stream, float initial_freq, float speed, BOOL pitch);

double bassh_get_stream_pos(HSTREAM stream);
void bassh_set_stream_pos(HSTREAM stream, double pos);

void bassh_play_stream(HSTREAM stream, BOOL restart);
void bassh_pause_stream(HSTREAM stream);
void bassh_stop_stream(HSTREAM stream);
void bassh_free_stream(HSTREAM stream);

int bassh_device_count();

void bassh_init();
void bassh_deinit();
