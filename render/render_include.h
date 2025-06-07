#ifndef RENDER_INCLUDE_H
#define RENDER_INCLUDE_H

#include "render_core.h"

#if RENDER_BACKEND == RENDER_BACKEND_XCB
#   include "render_xcb.h"
#endif

#endif // RENDER_INCLUDE_H
