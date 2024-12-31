#ifndef STD_OS_LINUX_H
#define STD_OS_LINUX_H

#include <sys/mman.h>
#include <unistd.h>

// Function Define
//=====================

fn void *os_alloc(U64 size);
fn I32 os_commit(void *ptr, U64 size);
fn void os_decommit(void *ptr, U64 size);
fn void os_free(void *ptr, U64 size);

fn void os_exit(I32 exit_code);

// Memory Allocation
//==================

fn void *os_alloc(U64 size) {
    void *result = mmap(0, size, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if(result == MAP_FAILED) { result = 0 }
    return result;
}

fn I32 os_commit(void *ptr, U64 size) {
    mprotect(ptr, size, PROT_READ|PROT_WRITE);
    return 1;
}

fn void os_decommit(void *ptr, U64 size) {
    madvise(ptr, size, MADV_DONTNEED);
    mprotect(ptr, size, PROT_NONE);
}

fn void os_free(void *ptr, U64 size) {
    munmap(ptr, size);
}

// Exit
//=====

fn void os_exit(I32 exit_code) {
    exit(exit_code);
}

#endif // STD_OS_LINUX_H
