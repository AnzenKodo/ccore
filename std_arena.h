/********************************************************************************
 * Arena Allocator implementation in pure C as an stb-style single-file library.
 * Taken inspiration from
 *  - https://github.com/tsoding/arena by Alexey Kutepov
 *  - https://github.com/CobbCoding1/c-allocators by CobbCoding
 * -----------------------------------------------------------------------------
 * MIT License
 *
 * Copyright 2024 AnzenKodo
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
********************************************************************************/

#ifndef LIBS_ARENA
#define LIBS_ARENA

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

#endif // LIBS_ARENA
