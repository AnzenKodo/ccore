#ifndef STD_ARENA_H
#define STD_ARENA_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// Types
//======

typedef struct Arena {
    struct Arena *next;
    size_t capacity;
    size_t size;
    uint8_t *data;
} Arena;

typedef struct ArenaParams {
  ArenaFlags flags;
  U64 reserve_size;
  U64 commit_size;
  void *optional_backing_buffer;
} ArenaParams;

// Default
//========

global U64 arena_default_reserve_size = MB(64);
global U64 arena_default_commit_size  = KB(64);

// Function Define
//========

#define arena_alloc(...) arena_alloc_(&(ArenaParams){ /
    .reserve_size = arena_default_reserve_size, /
    .commit_size = arena_default_commit_size, /
    __VA_ARGS__ /
})

fn Arena *arena_alloc_(ArenaParams *params) {
    // rjf: round up reserve/commit sizes
    U64 reserve_size = params->reserve_size;
    U64 commit_size = params->commit_size;
    
    reserve_size = AlignPow2(
        reserve_size, os_get_system_info()->page_size
    );
    commit_size  = AlignPow2(
        commit_size,  os_get_system_info()->page_size
    );

    // rjf: reserve/commit initial block
    void *base = params->optional_backing_buffer;
    if(base == 0) {
        base = os_reserve(reserve_size);
        os_commit(base, commit_size);
    }

    // rjf: extract arena header & fill
    Arena *arena = (Arena *)base;
    arena->current = arena;
    arena->flags = params->flags;
    arena->cmt_size = params->commit_size;
    arena->res_size = params->reserve_size;
    arena->base_pos = 0;
    arena->pos = ARENA_HEADER_SIZE;
    arena->cmt = commit_size;
    arena->res = reserve_size;
    AsanPoisonMemoryRegion(base, commit_size);
    AsanUnpoisonMemoryRegion(base, ARENA_HEADER_SIZE);
    return arena;
}


// void arena_init(Arena *arena, size_t capacity) {
//     void *data = malloc(sizeof(uint8_t) * capacity);
//     if (data == NULL) {
//         printf("Error: Not enough memory. Buy more ram, poor mf.");
//     }
//     arena->data = data;
//     arena->capacity = capacity;
// }

// void *arena_alloc(Arena *arena, size_t size) {
//     assert(arena->capacity >= size);

//     Arena *current = arena;
//     while (!(current->size + size < current->capacity)) {
//         if (current->next == NULL) {
//             Arena *next = malloc(sizeof(Arena));
//             next->capacity = arena->capacity;
//             next->size = 0;
//             next->next = NULL;
//             next->data = malloc(sizeof(uint8_t) * arena->capacity);
//             current->next = next;
//         }
//         current = current->next;
//     }

//    uint8_t *data = &current->data[current->size];
//    current->size += size;
//    return data;
// }

// void *arena_realloc(Arena *arena, void *old_ptr, size_t old_size, size_t new_size) {
//     if (new_size <= old_size) return old_ptr;

//     void *new_ptr = arena_alloc(arena, new_size);
//     char *new_ptr_char = new_ptr;
//     char *old_ptr_char = old_ptr;

//     for (size_t i = 0; i < old_size; ++i) {
//         new_ptr_char[i] = old_ptr_char[i];
//     }

//     return new_ptr;
// }

// void arena_reset(Arena *arena) {
//     Arena *current = arena;

//     while (current != NULL) {
//         current->size = 0;
//         current = current->next;
//     }
// }

// void arena_free(Arena *arena) {
//     free(arena->data);
//     arena->capacity = 0;
//     arena->size = 0;

//     Arena *current = arena->next;
//     while(current != NULL) {
//         Arena *next = current->next;
//         free(current->data);
//         free(current);
//         current = next;
//     }

//     arena->next = NULL;
// }

#endif // STD_ARENA_H
