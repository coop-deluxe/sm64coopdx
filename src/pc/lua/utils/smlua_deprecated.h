#pragma once

/* |description|[DEPRECATED: Use `HOOK_ON_HUD_RENDER_BEHIND` instead] Sets if DJUI should render behind the vanilla HUD|descriptionEnd| */
void djui_hud_set_render_behind_hud(bool enable);

/* |description|[DEPRECATED: There may be a replacement for this function in the future]|descriptionEnd| */
f32 audio_stream_get_tempo(struct ModAudio* audio);
/* |description|[DEPRECATED: There may be a replacement for this function in the future]|descriptionEnd| */
void audio_stream_set_tempo(struct ModAudio* audio, f32 tempo);
/* |description|[DEPRECATED: There may be a replacement for this function in the future]|descriptionEnd| */
void audio_stream_set_speed(struct ModAudio* audio, f32 initial_freq, f32 speed, bool pitch);

/* |description|[DEPRECATED: Use `network_player_set_override_palette_color` instead]|descriptionEnd| */
void network_player_color_to_palette(struct NetworkPlayer *np, enum PlayerPart part, Color color);
/* |description|[DEPRECATED: Use `network_player_get_palette_color` or `network_player_get_override_palette_color` instead]|descriptionEnd| */
void network_player_palette_to_color(struct NetworkPlayer *np, enum PlayerPart part, Color out);
