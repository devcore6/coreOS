#include <pthread.h>

void [[noreturn]] pthread_exit(void *retval) {
	// do stuff to actally exit
	while(true) {
		asm volatile("hlt");
	}
	__builtin_unreachable();
}
