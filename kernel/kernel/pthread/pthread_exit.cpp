#include <pthread.h>

void pthread_exit(void *retval) [[noreturn]] {
	// do stuff to actally exit
	while(true) {
		asm volatile("hlt");
	}
	__builtin_unreachable();
}
