#include <stdlib.h>

#if defined(__is_libk)
# include <stdint.h>
extern void* _malloc(size_t size, uint32_t flags);
#endif

void *malloc(size_t size) {
#if defined(__is_libk)
	return _malloc(size, 0x02);
#else
	// implement system call
	return 0;
#endif
}
