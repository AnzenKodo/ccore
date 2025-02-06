#ifndef OS_CORE_H
#define OS_CORE_H

#define OS_STDIN  0
#define OS_STDOUT 1
#define OS_STDERR 2

typedef I32 Os_File;

enum Os_AccessFlags
{
    Os_AccessFlag_Read       = (1<<0),
    Os_AccessFlag_Write      = (1<<1),
    Os_AccessFlag_Execute    = (1<<2),
    Os_AccessFlag_Append     = (1<<3),
    Os_AccessFlag_ShareRead  = (1<<4),
    Os_AccessFlag_ShareWrite = (1<<5),
    Os_AccessFlag_Inherited  = (1<<6),
};
typedef enum Os_AccessFlags Os_AccessFlags;

// Function Define
//=====================

fn void *os_alloc(U64 size);
fn I32 os_commit(void *ptr, U64 size);
fn void os_decommit(void *ptr, U64 size);
fn void os_free(void *ptr, U64 size);

fn void os_exit(I32 exit_code);


#if OS_LINUX
#   include "ccore/os/os_core/os_core_linux.h"
#else
#   error OS layer not implemented for this operating system.
#endif

#endif // OS_CORE_H
