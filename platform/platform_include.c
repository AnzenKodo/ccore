// OS Layer
//====================================================================

#if OS_LINUX
#   include "os/platform_os_linux.c"
#else
#   error OS layer not implemented for this operating system.
#endif

#ifdef ENABLE_WINDOW_LAYER

// Window Layer
//====================================================================

#   if OS_LINUX
#      include "window_layer/platform_window_layer_linux.c"
#   else
#      error OS window layer not implemented for this operating system.
#   endif

// Render Layer
//====================================================================

#   if RENDER_BACKEND == RENDER_BACKEND_X11
#      include "render/platform_render_x11.c"
#   elif RENDER_BACKEND == RENDER_BACKEND_OPENGL
#      include "render/platform_render_opengl.c"
#   endif

#endif
