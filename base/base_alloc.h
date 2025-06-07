#ifndef BASE_ALLOC_H
#define BASE_ALLOC_H

// Allocator
//====================================================================

typedef struct {
    void *(*alloc)(void *context, U64 size, U64 align);
    void (*free)(void *context, void *buffer, U64 size);
    void *context;
} Alloc;

#define alloc_make(a, T, n) (cast(T *)((a).alloc((a).context, sizeof(T)*n, AlignOf(T))))
#define alloc_free(a, p, n) ((a).free((a).context, p, sizeof(*p)*n))

// Arena Allocator
//====================================================================

typedef struct {
    void *buffer;
    U64 size;
    U64 offset;
    U64 committed;
} Arena;

#define alloc_arena_init(b, s) (Alloc){alloc_arena_push, alloc_arena_pop, &(Arena){.buffer = b, .size = s}}

internal void *alloc_arena_push(void *context, U64 size, U64 align);
internal void alloc_arena_pop(void *context, void *buffer, U64 size);
internal void alloc_arena_reset(void *context);

#endif // BASE_ALLOC_H
