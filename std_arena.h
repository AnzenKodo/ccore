#ifndef STD_ARENA
#define STD_ARENA

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Arena {
    struct Arena *next;
    size_t capacity;
    size_t size;
    uint8_t *data;
} Arena;

void arena_init(Arena *arena, size_t capacity) {
    void *data = malloc(sizeof(uint8_t) * capacity);
    arena->data = data;
    arena->capacity = capacity;
}

void *arena_alloc(Arena *arena, size_t size) {
    assert(arena->capacity >= size);

    Arena *current = arena;
    while (!(current->size + size < current->capacity)) {
        if (current->next == NULL) {
            Arena *next = malloc(sizeof(Arena));
            next->capacity = arena->capacity;
            next->size = 0;
            next->next = NULL;
            next->data = malloc(sizeof(uint8_t) * arena->capacity);
            current->next = next;
        }
        current = current->next;
    }

   uint8_t *data = &current->data[current->size];
   current->size += size;
   return data;
}

void *arena_realloc(Arena *arena, void *old_ptr, size_t old_size, size_t new_size) {
    if (new_size <= old_size) return old_ptr;

    void *new_ptr = arena_alloc(arena, new_size);
    char *new_ptr_char = new_ptr;
    char *old_ptr_char = old_ptr;

    for (size_t i = 0; i < old_size; ++i) {
        new_ptr_char[i] = old_ptr_char[i];
    }

    return new_ptr;
}

void arena_reset(Arena *arena) {
    Arena *current = arena;

    while (current != NULL) {
        current->size = 0;
        current = current->next;
    }
}

void arena_free(Arena *arena) {
    free(arena->data);
    arena->capacity = 0;
    arena->size = 0;

    Arena *current = arena->next;
    while(current != NULL) {
        Arena *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    arena->next = NULL;
}

#endif // STD_ARENA
