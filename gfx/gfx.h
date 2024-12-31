#ifndef GFX_H
#define GFX_H

fn void gfx_gfx_init(void);
fn void gfx_open_window(Str8 title);

#if OS_LINUX
#   include "std/gfx/gfx_linux.h"
#else
#   error OS core layer not implemented for this operating system.
#endif


#endif // GFX_H
