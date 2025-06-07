#ifndef RENDER_CORE_H
#define RENDER_CORE_H

// Define Render Backends
//=============================================================================

#define RENDER_BACKEND_STUB     0
#define RENDER_BACKEND_XCB      1

// Context detection for Render Backends
//=============================================================================

#ifndef RENDER_BACKEND
#    if OS_LINUX
#        define RENDER_BACKEND RENDER_BACKEND_XCB
#    endif
#endif

// Functions
//=============================================================================

internal Draw_Buffer render_init(Alloc);
internal void render_begin(void);
internal void render_end(void);

#endif // RENDER_CORE_H
