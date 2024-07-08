#pragma once

void djui_hud_set_render_behind_hud(bool enable);

struct ModAudio* audio_stream_load_url(const char* url);
f32 audio_stream_get_tempo(struct ModAudio* audio);
void audio_stream_set_tempo(struct ModAudio* audio, f32 tempo);
void audio_stream_set_speed(struct ModAudio* audio, f32 initial_freq, f32 speed, bool pitch);

void network_player_color_to_palette(struct NetworkPlayer *np, enum PlayerPart part, Color color);
void network_player_palette_to_color(struct NetworkPlayer *np, enum PlayerPart part, Color out);
