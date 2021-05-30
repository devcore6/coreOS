#ifndef __KERNEL_THREAD_H
# define __KERNEL_THREAD_H
# include <stddef.h>
# include <stdint.h>
# include <pthread.h>
# ifdef __cplusplus
extern "C" {
# endif

struct _thread_t {
	pthread_t pid = 0;
	pthread_t parent = 0;
	uint32_t sleep_until = 0;
	uint32_t *page_directory = NULL;
	uint32_t esp = 0,
			 ebp = 0,
			 eip = 0,
			 cs = 0,
			 ds = 0,
			 ss = 0;
	char *stack = NULL;
	char *fstate = NULL;
	void *(*start_routine) (void *);
	void *arg;
};

extern _thread_t* __this_thread;
extern _thread_t** _threads;

#define _yield() if(__this_thread) { \
	pthread_t __pid = pthread_self() + 1; \
	for(; __pid < 65536; __pid++) { \
		if(!_threads[__pid]) continue; \
		if(_threads[__pid]->sleep_until > system_timer_ms) continue; \
		break; \
	} \
	if(__pid == 65536) for(__pid = 1; __pid < pthread_self(); __pid++) { \
		if(!_threads[__pid]) continue; \
		if(_threads[__pid]->sleep_until > system_timer_ms) continue; \
		break; \
	} \
	if(__pid != pthread_self()) _load(__pid); \
}

extern void _load(pthread_t pid);

# ifdef __cplusplus
}
# endif
#endif
