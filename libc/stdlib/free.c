#include <stdlib.h>

#if defined(__is_libk)
extern void _free(void* ptr);
#endif

void free(void* ptr) {
#if defined(__is_libk)
	_free(ptr);
#else
	// implement system call
#endif
}
