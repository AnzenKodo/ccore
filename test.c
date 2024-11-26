#include "arena.h"
#include "str.h"
#include "base.h"
#include "args.h"
#include "str.h"

void arena_test(void) {
    Arena arena = {0};
    arena_init(&arena, 1024);
    printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);
    arena_alloc(&arena, 24);
    printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);

    arena_alloc(&arena, 1000);
    printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);

    void *ptr3 = arena_alloc(&arena, 100);
    printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);
    str_cpy(ptr3, "Hello");
    printf(ptr3); printf("\n");

    void *ptr4 = arena_realloc(&arena, ptr3, 100, 150);
    printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);
    base_print(ptr4); base_print("2");

    Arena *current = &arena;
    base_print("\n");
    while (current != NULL) {
        printf("current: capacity: %zu, size: %zu, data ptr: %p\n", current->capacity, current->size, current->data);
        current = current->next;
    }

    arena_reset(&arena);
    printf("capacity: %zu, size: %zu, data ptr: %p\n", arena.capacity, arena.size, arena.data);

    arena_free(&arena);
}

void args_test(int argc, char **argv) {
    args_init(argc, argv);
    args_get("--name", "-n", "Name of person");
    args_get_int("--age", "-a", "Age of person");
    args_get_int("--weight", "-w", "Weight of person");
    if (args_has("--help", "-h", "Show help")) {
        args_print_help(
            "example.c",
            "Examples of AK Libs.",
            "[options] [value]",
            "SPDX-License-Identifier: MIT (https://spdx.org/licenses/MIT)"
        );
    }
}

void str_test() {
    printf("Hello\n");
}

int main(int argc, char *argv[]) {
    // arena_test();
    // args_test(argc, argv);
    str_test();
}
