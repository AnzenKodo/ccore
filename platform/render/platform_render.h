#ifndef RENDER_H
#define RENDER_H

fn Draw_Buffer *render_init(void);
fn void render_draw(void);
fn void render_close(void);
fn void render_begin(void);
fn void render_end(void);

#if OS_LINUX
fn void render_set_wl_linux_visual_info(XVisualInfo *visual_info);
#endif

#endif // RENDER_H
