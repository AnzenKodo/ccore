// Memory Allocation
//=============================================================================

internal void *os_memory_create(U64 size)
{
    void *result = mmap(0, size, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if(result == MAP_FAILED) { result = 0; }
    return result;
}

internal I32 os_memory_commit(void *ptr, U64 size)
{
    mprotect(ptr, size, PROT_READ|PROT_WRITE);
    return 1;
}

internal void os_memory_decommit(void *ptr, U64 size)
{
    madvise(ptr, size, MADV_DONTNEED);
    mprotect(ptr, size, PROT_NONE);
}

internal void *os_memory_alloc(U64 size)
{
    void *result = os_memory_create(size);
    os_memory_commit(result, size);
    return result;
}

internal void os_memory_free(void *ptr, U64 size)
{
    munmap(ptr, size);
}

// File System
//=============================================================================

internal bool os_dir_make(Str8 path)
{
    I32 result = mkdir((const char *)path.str, 0700);

    if (result == 0) {
        return true;
    } else {
        return false;
    }
}

// Exit
//=============================================================================

internal void os_exit(I32 exit_code)
{
    _exit(exit_code);
}

// Time
//=============================================================================

internal U32 os_now_unix(void)
{
    time_t t = time(0);
    return (U32)t;
}

internal U64
os_now_microsec(void)
{
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  U64 result = t.tv_sec*Million(1) + (t.tv_nsec/Thousand(1));
  return result;
}

internal void
os_sleep_microsec(U64 micosec)
{
    struct timespec ts = {
        .tv_sec = micosec / Million(1),
        .tv_nsec = (micosec % Million(1)) * Thousand(1),
    };
    nanosleep(&ts, NULL);
}

// OS Entry Points
//=============================================================================

int main(int argc, char *argv[])
{
    entry_point(argv);
}
