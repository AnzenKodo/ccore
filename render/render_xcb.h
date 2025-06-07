#ifndef RENDER_XCB_H
#define RENDER_XCB_H

// External Includes
//=============================================================================

#include <xcb/xcb_image.h>

// Types
//=============================================================================

typedef struct Render_Xcb_State Render_Xcb_State;
struct Render_Xcb_State
{
    xcb_pixmap_t pixmap;
    xcb_gcontext_t gc;
    xcb_image_t *image;
};

// Global Variables
//=============================================================================

global Render_Xcb_State render_xcb_state = ZERO_STRUCT;

// Functions
//=============================================================================

#endif // RENDER_XCB_H
