#ifndef GFX_SSGI_H
#define GFX_SSGI_H

#include <stdbool.h>

void ssgi_init(void);
void ssgi_resize(int width, int height);
void ssgi_start_frame(void);   // Bind scene FBO
void ssgi_render(void);        // AO pass
void ssgi_composite(void);     // Combine scene × AO → default framebuffer
void ssgi_set_projection_matrix(const float mtx[4][4]);
bool ssgi_is_enabled(void);

#endif
