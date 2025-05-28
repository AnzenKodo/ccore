#ifndef RENDER_x11_H
#define RENDER_x11_H

// Types
//=============================================================================

typedef struct Render_X11_State Render_X11_State;
struct Render_X11_State
{
  XImage image;
};

// Global Variables
//=============================================================================

global Render_X11_State render_x11_state = ZERO_STRUCT;

// Functions
//=============================================================================

internal void render_set_wl_linux_visual_info(XVisualInfo *visual_info, Display *display);

#endif // RENDER_x11_H
