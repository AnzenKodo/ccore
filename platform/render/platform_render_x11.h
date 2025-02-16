#ifndef RENDER_X11_H
#define RENDER_X11_H

typedef struct Render_X11_State Render_X11_State;
struct Render_X11_State
{
  Arena *arena;
  XImage *image;
  GC gc;
};

global Render_X11_State *render_x11_state = 0;

#endif // RENDER_X11_H
