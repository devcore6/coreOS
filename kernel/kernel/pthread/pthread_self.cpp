#include <kernel/thread.h>
#include <pthread.h>

pthread_t pthread_self() {
	return __this_thread ? __this_thread->pid : 0;
}
