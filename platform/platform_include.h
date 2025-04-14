#ifndef OS_INCLUDE_H
#define OS_INCLUDE_H

// OS Layer
//====================================================================

#include "os/platform_os.h"

// Window Layer
//====================================================================

#ifdef ENABLE_WINDOW_LAYER
#   include "window_layer/platform_window_layer.h"

#   if OS_LINUX
#      include "window_layer/platform_window_layer_linux.h"
#   else
#      error OS window layer not implemented for this operating system.
#   endif
#endif

// Render Layer
//====================================================================

#define RENDER_BACKEND_STUB     0
#define RENDER_BACKEND_X11      1
#define RENDER_BACKEND_OPENGL   2

#ifdef ENABLE_WINDOW_LAYER
#   include "render/platform_render.h"

#   ifndef RENDER_BACKEND
#       if OS_LINUX
#           define RENDER_BACKEND RENDER_BACKEND_X11
#       endif
#   endif
#endif

#if RENDER_BACKEND == RENDER_BACKEND_X11
#   include "render/platform_render_x11.h"
#elif RENDER_BACKEND == RENDER_BACKEND_OPENGL
#   include "render/platform_render_opengl.h"
#endif

#endif // OS_INCLUDE_H
