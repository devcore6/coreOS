#ifndef __KERNEL_THREAD_H
# define __KERNEL_THREAD_H
# include <stddef.h>
# include <stdint.h>
# include <pthread.h>
# include <kernel/arch/i386/pit.h>
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

extern uint32_t last_yield;
constexpr uint32_t yield_time = 2;

inline void _yield() {
	if(system_timer_ms <= last_yield + yield_time) return;
	last_yield = system_timer_ms;
	asm volatile("int $0x79;"
				 "sti;");
}

extern void _load(pthread_t pid);

# ifdef __cplusplus
}
# endif
#endif
