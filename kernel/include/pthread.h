#ifndef __PTHREAD_H
# define __PTHREAD_H
typedef unsigned long pthread_t;

# ifdef __cplusplus
extern "C" {
# endif

struct pthread_attr_t {
	// int flags;
	// int stacksize;
	// int contentionscope;
	// int inheritsched;
	// int detachstate;
	// int sched;
	// sched_param param;
	// timespec period;
};

extern int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
						  void *(*start_routine) (void *), void *arg);
extern void [[noreturn]] pthread_exit(void *retval);
extern pthread_t pthread_self();

# ifdef __cplusplus
}
# endif
#endif
