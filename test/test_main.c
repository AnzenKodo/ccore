#include "base/base_include.h"
#include "platform/os/os_include.h"

#include "base/base_include.c"

#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void) {
    Str8 str = str8("hello world");

    // Memory =================================================================

    AssertAlways(mem_match(str.str, "hello world", str.size) == true);

    // String =================================================================

    AssertAlways(str8_match(str, str8("hello world")) == true);

    Str8 str_post = str8_postfix(str, 3);
    AssertAlways(str8_match(str_post, str8("rld")) == true);
    printf("\nstr8_postfix %s", str_post.str);

    // Arena testing ==========================================================

    U64 size = MB(5);
    void *buffer = os_memory_alloc(size);

    Alloc alloc = alloc_arena_init(buffer, size);
    U64 *ptr = alloc_make(alloc, U64, 1);
    ptr = alloc_make(alloc, U64, 1);
    ptr = alloc_make(alloc, U64, 1);
    alloc_free(alloc, ptr, 1);

    Arena *arena = (Arena *)alloc.context;
    printf("\n\nArena Size %lu", arena->size);
    printf("\nArena Offset %lu", arena->offset);
    printf("\nArena Committed %lu", arena->committed);
    AssertAlways(arena->size == 5242880);
    AssertAlways(arena->offset == 16);
    AssertAlways(arena->committed == 16);

    os_memory_free(buffer, 10);
    return 0;
}
