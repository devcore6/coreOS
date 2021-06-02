#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#ifdef __is_kernel
# include <kernel/thread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
				   void *(*start_routine) (void *), void *arg) {
	if(*thread == 0) (*thread)++;
	while(*thread < 65536) {
		if(_threads[*thread] == nullptr) break;
		(*thread)++;
	}
	if(*thread > 65535) return -1;							// No available PID

	_threads[*thread] = new _thread_t;						// Create new task structure before messing with our local stack
	_threads[*thread]->pid = *thread;
	_threads[*thread]->parent = __this_thread ? __this_thread->pid : 0;
	_threads[*thread]->sleep_until = 0;
	_threads[*thread]->stack = new char[0x4000];
	_threads[*thread]->ebp = (uint32_t)_threads[*thread]->stack + 0x4000;
	_threads[*thread]->esp = _threads[*thread]->ebp;
	//_threads[*thread]->fstate = new char[0x200];
	//_threads[*thread]->page_directory = new uint32_t[0x100000];
	_threads[*thread]->start_routine = start_routine;
	_threads[*thread]->arg = arg;

	if(!__this_thread) goto run;
	asm volatile goto("movl %%ebp, %0;" 					// Save base pointer
					  "movl %%esp, %1;"						// Save stack pointer
					  "pushal;"								// Push general purpose registers
					  "pushfl;"								// Push %flags
					  //"fxsave %2;"							// Save FPU state
					  "movw %%cs, %3;"						// Push code segment for far jump
					  "movw %%ds, %4;"						// Push data segment for far jump
					  "movw %%ss, %5;"						// Push stack segment for far jump
					  "call %l6"							// Will push address to next instruction onto stack
					  : "=m"(__this_thread->ebp),
					    "=m"(__this_thread->esp),
					    "=m"(__this_thread->fstate),
					    "=m"(__this_thread->cs),
					    "=m"(__this_thread->ds),
					    "=m"(__this_thread->ss)
					  :
					  :
					  : jump); 

// will run on parent thread when resuming
	asm volatile("sti");
	return 0;
jump:
	asm volatile("popl %0;"									// Pull return address from stack
				 : "=m"(__this_thread->eip));

run:

// todo: do stuff to set up page_directory and switch to it

	__this_thread = _threads[*thread];

	asm volatile("movl %0, %%ebp;"							// Load new base pointer
				 "movl %1, %%esp;"							// Load new stack pointer
				 "pushl %%eax;"								// Temporarily store %eax
				 "movl %%cr0, %%eax;"						// Copy %cr0 onto %eax
				 "orl %%eax, 8;"							// Set task switch flag
				 "movl %%eax, %%cr0;"						// Save new %cr0
				 //"pushfl;"									// Temporarily push %flags register
				 //"popl %%eax;"								// Pop it on %eax
				 //"orl $0x4200, %%eax;"						// Set new task flag
				 //"pushl %%eax;"								// Push it back on the stack
				 //"popfl;"									// And pop back onto %flags
				 "sti;"
				 "popl %%eax;"								// Pop original %eax
				 "pushl %2;"								// Push function parameter
				 "pushfl;"									// Need %flags on stack
				 "pushw %%cs;"								// This temporarily assumes the code segment remains the same
				 "pushl %3;"								// Push address for iret
				 "iret;"									// Should jump to subroutine and be interpreted as new task
				 :
				 : "m"(_threads[*thread]->ebp),
				   "m"(_threads[*thread]->esp),
				   "m"(_threads[*thread]->arg),
				   "m"(_threads[*thread]->start_routine));
	__builtin_unreachable();								// Indicate to GCC that any code from here on is unreachable, 
															// so it won't complain about the function not returning a value
}

#else
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
				   void *(*start_routine) (void *), void *arg) {

}
#endif

