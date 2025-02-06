#ifndef STD_OS_LINUX_H
#define STD_OS_LINUX_H

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

// Memory Allocation
//==================

fn void *os_alloc(U64 size)
{
    void *result = mmap(0, size, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if(result == MAP_FAILED) { result = 0; }
    return result;
}

fn I32 os_commit(void *ptr, U64 size)
{
    mprotect(ptr, size, PROT_READ|PROT_WRITE);
    return 1;
}

fn void os_decommit(void *ptr, U64 size)
{
    madvise(ptr, size, MADV_DONTNEED);
    mprotect(ptr, size, PROT_NONE);
}

fn void os_free(void *ptr, U64 size)
{
    munmap(ptr, size);
}

fn void os_write(I32 fd, void *data, U64 size)
{
    write(fd, data, size);
}

fn void os_write_str8(I32 fd, Str8 str)
{
    os_write(fd, str.str, str.size+1);
}

// File System
//============

fn Os_File os_file_open(Str8 path, Os_AccessFlags flags)
{
    I32 linux_flags = 0;
    if(flags & Os_AccessFlag_Read && flags & Os_AccessFlag_Write) {
        linux_flags = O_RDWR;
    } else if(flags & Os_AccessFlag_Write) {
        linux_flags = O_WRONLY|O_TRUNC;
    } else if(flags & Os_AccessFlag_Read) {
        linux_flags = O_RDONLY;
    }
    if(flags & Os_AccessFlag_Append) {
        linux_flags |= O_APPEND;
    }
    if(flags & (Os_AccessFlag_Write|Os_AccessFlag_Append)) {
        linux_flags |= O_CREAT;
    }

    I32 fd = open((char *)path.str, linux_flags, 0755);
    Os_File os_fd;
    if(fd != -1) { os_fd = (Os_File)fd; }

    return os_fd;
}

fn void os_file_close(Os_File fd)
{
    close((int)fd);
}

fn U64 os_file_read(Os_File fd, Rng1U64 rng, void *out_data)
{
    U64 total_num_bytes_to_read = dim_1u64(rng);
    U64 total_num_bytes_read = 0;
    U64 total_num_bytes_left_to_read = total_num_bytes_to_read;
    for(;total_num_bytes_left_to_read > 0;)
    {
        int read_result = pread(
            fd,
            cast(U8 *)out_data + total_num_bytes_read, total_num_bytes_left_to_read,
            rng.min + total_num_bytes_read
        );
        if(read_result >= 0)
        {
            total_num_bytes_read += read_result;
            total_num_bytes_left_to_read -= read_result;
        }
        else if(errno != EINTR)
        {
            break;
        }
    }
    return total_num_bytes_read;
}

fn U64 os_file_write(Os_File fd, Rng1U64 rng, void *data)
{
    U64 total_num_bytes_to_write = dim_1u64(rng);
    U64 total_num_bytes_written = 0;
    U64 total_num_bytes_left_to_write = total_num_bytes_to_write;
    for(;total_num_bytes_left_to_write > 0;)
    {
        int write_result = pwrite(
            fd,
            (U8 *)data + total_num_bytes_written,
            total_num_bytes_left_to_write,
            rng.min + total_num_bytes_written
        );
        if(write_result >= 0)
        {
            total_num_bytes_written += write_result;
            total_num_bytes_left_to_write -= write_result;
        }
        else if(errno != EINTR)
        {
            break;
        }
    }
    return total_num_bytes_written;
}

fn Bool os_mkdir(const char *path)
{
    I32 result = mkdir(path, 0700);

    if (result == 0) {
        return true;
    } else {
        return false;
    }
}

fn Bool os_exist(const char *path)
{
    struct stat buffer;

    if (stat(path, &buffer) == 0) {
        return true;
    } else {
        return false;
    }
}

// Exit
//=====

fn void os_exit(I32 exit_code)
{
    _exit(exit_code);
}

#endif // STD_OS_LINUX_H
