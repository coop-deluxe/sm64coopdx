#pragma once

extern struct ThreadHandle gRenderThread;

bool render_thread_processing_dl(Gfx *dlCommands);
void set_dl_for_render_thread(Gfx *dlCommands);
void *render_thread_init(UNUSED void *dummy);
