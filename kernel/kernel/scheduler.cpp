#include <kernel/arch/i386/pit.h>
#include <kernel/arch/i386/isr.h>
#include <kernel/arch/i386/io.h>
	
#include <kernel/thread.h>

#include <pthread.h>

extern "C" {

	void intyield(struct interrupt_frame*) {
		pthread_t __pid = pthread_self() + 1;
		for(; __pid < 65536; __pid++) {
			if(!_threads[__pid]) continue;
			if(_threads[__pid]->sleep_until > system_timer_ms) continue;
			break;
		}
		if(__pid == 65536) for(__pid = 1; __pid < pthread_self(); __pid++) {
			if(!_threads[__pid]) continue;
			if(_threads[__pid]->sleep_until > system_timer_ms) continue;
			break;
		}
		if(__pid == pthread_self()) return;

		asm volatile goto("movl %%ebp, %0;" 				// Save base pointer
						  "movl %%esp, %1;"					// Save stack pointer
						  "pushal;"							// Push general purpose registers
						  "pushfl;"							// Push %flags
						  "movw %%cs, %2;"					// Push code segment for far jump
						  "call %l3"						// Will push address to next instruction onto stack
						  : "=m"(__this_thread->ebp),
						    "=m"(__this_thread->esp),
						    "=m"(__this_thread->cs)
						  :
						  :
						  : jump); 

// will run on parent thread when resuming
		return;
	jump:
		asm volatile("popl %0;"								// Pull return address from stack
					 : "=m"(__this_thread->eip));

		__this_thread = _threads[__pid];

		asm volatile("movl %0, %%ebp;"						// Load new base pointer
					 "movl %1, %%esp;"						// Load new stack pointer
					 "pushl %%eax;"							// Temporarily store %eax
					 "movl %%cr0, %%eax;"					// Copy %cr0 onto %eax
					 "orl %%eax, 8;"						// Set task switch flag
					 "movl %%eax, %%cr0;"					// Save new %cr0
					 // idk why but if i uncomment this it will double fault lol
					 //"pushfl;"								// Temporarily push %flags register
					 //"popl %%eax;"							// Pop it on %eax
					 //"orl $0x4200, %%eax;"					// Set new task flag & interrupt flag
					 //"pushl %%eax;"							// Push it back on the stack
					 //"popfl;"								// And pop back onto %flags
					 "movb $0x20, %%al;"					// Tell PIC we are ready to receive interrutps again
					 "outb %%al, $0x20;"					// Tell PIC we are ready to receive interrupts again
					 "sti;"
					 "popl %%eax;"							// Pop original %eax
					 "pushfl;"								// Need %flags back on stack for iret
					 "pushl %2;"							// Push code segment for iret
					 "pushl %3;"							// Push address for iret
					 "iret;"								// Should jump to subroutine and be interpreted as new task
					 :
					 : "m"(__this_thread->ebp),
					   "m"(__this_thread->esp),
					   "m"(__this_thread->cs),
					   "m"(__this_thread->eip));
	}

}
