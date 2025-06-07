#ifndef BASE_MEM_H
#define BASE_MEM_H

internal inline bool mem_match(void const *s1, void const *s2, I64 size);
internal inline void *mem_copy(void *dest, void const *source, I64 n);
internal inline void *mem_move(void *dest, void const *source, I64 n);
internal inline void *mem_set(void *dest, U8 c, I64 n);

#endif // BASE_MEM_H
