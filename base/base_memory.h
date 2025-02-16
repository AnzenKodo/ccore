#ifndef BASE_MEM_H
#define BASE_MEM_H

// ak: Memory Operation Functions
//====================================================================

fn inline void *memory_set(void *dest, U8 c, ISize n);
fn inline I32 memory_cmp(void const *s1, void const *s2, ISize size);
fn inline void *memory_copy(void *dest, void const *source, ISize n);
fn inline void *memory_move(void *dest, void const *source, ISize n);

// ak: Memory Operation Macros
//====================================================================

#define MemoryZero(s,z)       memory_set((s),0,(z))
#define MemoryZeroStruct(s)   MemoryZero((s),sizeof(*(s)))
#define MemoryZeroArray(a)    MemoryZero((a),sizeof(a))
#define MemoryZeroTyped(m,c)  MemoryZero((m),sizeof(*(m))*(c))

#define MemoryMatch(a,b,z)         (memory_cmp((a),(b),(z)) == 0)
#define MemoryMatchStruct(a,b)     MemoryoryMatch((a),(b),sizeof(*(a)))
#define MemoryMatchArray(a,b)      MemoryoryMatch((a),(b),sizeof(a))

#define MemoryCopy(dst, src, size)    memory_copy((dst), (src), (size))
#define MemoryMove(dst, src, size)    memory_move((dst), (src), (size))

#endif // BASE_MEM_H
