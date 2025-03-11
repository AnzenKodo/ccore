#ifndef CORE_IMG_H
#define CORE_IMG_H

void ppm_save(Draw_Buffer buffer, Str8 name) {
    Os_File fd = os_file_open(name, Os_AccessFlag_Write);
    fmt_fprintf(fd, "P6\n%d %d 255\n", buffer.width, buffer.height);
    U32 *memory = (U32 *)buffer.memory;

    for (I32 i = 0; i < cast(I32)(buffer.width * buffer.height); i++) {
        U32 pixel = memory[i];
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
