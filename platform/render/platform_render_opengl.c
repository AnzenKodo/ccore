typedef struct Render_Opengl_State Render_Opengl_State;
struct Render_Opengl_State {
    GLXContext context;
    Arena *arena;
};
global Render_Opengl_State *render_opengl_state;

fn void render_set_wl_linux_visual_info(
    XVisualInfo *visual_info
) {
    Display *display = wl_linux_state->display;
    int screen = wl_linux_state->screen;
    int attr[] = {
        GLX_RGBA,           // RGBA color model
        GLX_DEPTH_SIZE, 24, // Depth buffer size
        GLX_DOUBLEBUFFER,   // Double buffer
        None                // End of attribute list
    };

    XVisualInfo *xvisual_info = glXChooseVisual(display, screen, attr);
    *visual_info = *xvisual_info;
    XFree(xvisual_info);
}

fn Draw_Canvas render_init(void)
{
    Display *display = wl_linux_state->display;
    Window window = wl_linux_state->window;
    XVisualInfo visual_info = wl_linux_state->visual_info;

    GLXContext context = glXCreateContext(display, &visual_info, NULL, GL_TRUE);
    glXMakeCurrent(display, window, context);

    Arena *arena = arena_alloc();
    render_opengl_state = arena_push(arena, Render_Opengl_State, 1);
    render_opengl_state->arena = arena;
    render_opengl_state->context = context;

    Draw_Canvas canvas;
    return canvas;
}

fn void render_close(void)
{
    Display *display = wl_linux_state->display;
    GLXContext context = render_opengl_state->context;
    Arena *arena = render_opengl_state->arena;

    glXMakeCurrent(display, None, NULL);
    glXDestroyContext(display, context);
    arena_free(arena);
}


fn void render_begin(void)
{
    glViewport(0,0,wl_get_window_width(),wl_get_window_height());
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

fn void render_end(void)
{
    Display *display = wl_linux_state->display;
    Window window = wl_linux_state->window;

	// glEnd();
    glXSwapBuffers(display, window);
}
