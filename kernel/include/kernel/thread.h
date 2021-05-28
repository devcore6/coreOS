#ifndef __KERNEL_THREAD_H
# define __KERNEL_THREAD_H
# include <stdint.h>
# ifdef __cplusplus
extern "C" {
# endif

struct _thread_t {
	uint32_t pid;
	uint32_t *page_directory;
};

extern _thread_t* __this_thread;
extern _thread_t** _threads;

# ifdef __cplusplus
}
# endif
#endif
