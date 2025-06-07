// Arena Allocator
//====================================================================

internal void *alloc_arena_push(void *context, U64 size, U64 align)
{
    void *result = 0;
    if (size)
    {
        Arena *arena = cast(Arena *)context;

        if (IsPow2(align))
        {
            U64 crr_ptr = IntFromPtr(arena->buffer) + arena->offset;
            U64 offset = AlignPow2(crr_ptr, align);
            offset -= IntFromPtr(arena->buffer);

            if (offset + size < arena->size)
            {
                arena->committed += size;
                arena->offset = offset + size;
                result = cast(void *)arena->buffer + offset;
            }
        }
    }

    return result;
}

internal void alloc_arena_pop(void *context, void *buffer, U64 size)
{
    Arena *arena = cast(Arena *)context;
    U64 offset = IntFromPtr(buffer) - IntFromPtr(arena->buffer);
    if (size <= offset) {
        arena->offset = offset;
        arena->committed -= size;
    }
}

internal void alloc_arena_reset(void *context)
{
    Arena *a = context;
    a->offset = 0;
    a->committed = 0;
}
