#ifndef CONTROLLER_BIND_MAPPING_H
#define CONTROLLER_BIND_MAPPING_H

#if defined(CAPI_SDL1) || defined(CAPI_SDL2)
void controller_bind_init(void);
int translate_sdl_scancode(int scancode);
const char* translate_bind_to_name(int bind);
#endif

#endif