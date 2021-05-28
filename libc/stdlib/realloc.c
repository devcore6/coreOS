#include <stdlib.h>

#if defined(__is_libk)
# include <stdint.h>
extern void* _realloc(void* ptr, size_t size, uint32_t flags);
#endif

void *realloc(void* ptr, size_t size) {
#if defined(__is_libk)
	return _realloc(ptr, size, 0x02);
#else
	// implement system call
	return 0;
#endif
}
