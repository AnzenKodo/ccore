#include "std_core.h"
#include "std_context.h"
#include "os/os.h"
#include "std_arena.h"

void arena_test(void) {
    // arena_init(&arena, 1024);
    // printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);
    // arena_alloc(&arena, 24);
    // printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);

    // arena_alloc(&arena, 1000);
    // printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);

    // void *ptr3 = arena_alloc(&arena, 100);
    // printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);
    // str_cpy(ptr3, "Hello");
    // printf(ptr3); printf("\n");

    // void *ptr4 = arena_realloc(&arena, ptr3, 100, 150);
    // printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);
    // base_print(ptr4); base_print("2");

    // Arena *current = &arena;
    // base_print("\n");
    // while (current != NULL) {
    //     printf("current: capacity: %zu, size: %zu, data ptr: %p\n", current->capacity, current->size, current->data);
    //     current = current->next;
    // }

    // arena_reset(&arena);
    // printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);

    // arena_free(&arena);
}

int main(void) {
    arena_test();
}
