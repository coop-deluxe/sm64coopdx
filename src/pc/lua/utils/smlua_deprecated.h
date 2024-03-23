#pragma once

char* network_discord_id_from_local_index(u8 localIndex);
void djui_hud_set_render_behind_hud(bool enable);

struct ModAudio* audio_stream_load_url(const char* url);
f32 audio_stream_get_tempo(struct ModAudio* audio);
void audio_stream_set_tempo(struct ModAudio* audio, f32 tempo);
void audio_stream_set_speed(struct ModAudio* audio, f32 initial_freq, f32 speed, bool pitch);
