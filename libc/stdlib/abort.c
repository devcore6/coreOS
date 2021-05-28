#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) {
#if defined(__is_libk)
	// TODO: Add proper kernel panic.
	printf("kernel: panic: abort()\n");
	// put CPU in lower power state
	while(1) {
		asm volatile("hlt");
	}
#else
	// TODO: Abnormally terminate the process as if by SIGABRT.
	printf("abort()\n");
	while (1) { }
#endif
	__builtin_unreachable();
}
