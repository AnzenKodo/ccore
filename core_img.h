#ifndef CORE_IMG_H
#define CORE_IMG_H

void ppm_save(Draw_Canvas canvas, Str8 name) {
    Os_File fd = os_file_open(name, Os_AccessFlag_Write);
    fmt_fprintf(fd, "P6\n%d %d 255\n", canvas.width, canvas.height);
    U32 *pixels = (U32 *)canvas.pixels;

    for (I32 i = 0; i < cast(I32)(canvas.width * canvas.height); i++) {
        U32 pixel = pixels[i];
        U8 r = (pixel >> 8) & 0xFF;
        U8 g = (pixel >> 0) & 0xFF;
        U8 b = (pixel >> 16) & 0xFF;
        os_write(fd, &r, sizeof(U8));
        os_write(fd, &g, sizeof(U8));
        os_write(fd, &b, sizeof(U8));
    }
    os_file_close(fd);
}

#endif // CORE_IMG_H
