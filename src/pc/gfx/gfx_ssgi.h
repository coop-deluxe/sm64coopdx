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

// Tunable parameters (unsigned int × 10 for DJUI slider, divided by 10.0 in shader)
extern unsigned int gSSGI_AoIntensity;  // ÷10 → float. Power curve: higher = subtler (default 15 → 1.5)
extern unsigned int gSSGI_Radius;       // ÷10 → float. Sample radius (default 15 → 1.5)
extern unsigned int gSSGI_Thickness;    // ÷10 → float. Depth rejection (default 3 → 0.3)
extern unsigned int gSSGI_Enabled;      // 0=off, 1=on

#endif
