#ifndef MEM_H_
#define MEM_H_

#include <stddef.h>

void* memset(void* bufptr, int value, size_t size);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
size_t strlen(const char*);

#endif
