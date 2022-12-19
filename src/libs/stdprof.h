#include <stdlib.h>

extern void* malloc_prof(size_t taille);
extern void* calloc_prof(size_t nb, size_t taille);
extern void* realloc_prof(void* ptr, size_t taille);
extern void free_prof(void* ptr);
