#ifndef RENDER_H
#define RENDER_H

// Include file
//=============

#if OS_LINUX
// #   include "core/render/render_opengl.h"
#   include "core/render/render_x11.h"
#else
#   error OS render layer not implemented for this operating system.
#endif

#endif // RENDER_H
