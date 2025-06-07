#ifndef OS_CORE_H
#define OS_CORE_H

// Memory Allocation
//====================================================================

internal void *os_memory_create(U64 size);
internal I32 os_memory_commit(void *ptr, U64 size);
internal void os_memory_decommit(void *ptr, U64 size);
internal void *os_memory_alloc(U64 size);
internal void os_memory_free(void *ptr, U64 size);

// File System
//====================================================================

internal bool os_dir_make(Str8 path);

// Exit
//====================================================================

internal void os_exit(I32 exit_code);

// Time
//=============================================================================

internal U32 os_now_unix(void);
internal void os_sleep_ms(U32 msec);

// Program Entry Points
//=============================================================================

internal void entry_point(char *argv[]);

#endif // OS_CORE_H
