#include <kernel/arch/i386/pit.h>
#include <kernel/arch/i386/paging.h>

#include <kernel/protovector.hpp>
#include <kernel/keyboard.hpp>

#include <kernel/thread.h>
#include <kernel/stdio.h>
#include <kernel/kwait.h>

#include <drivers/ps2/kb.hpp>

#include <vga/vga.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

extern "C" _thread_t* __this_thread = nullptr;
extern "C" _thread_t** _threads = nullptr;

extern "C" uint32_t *page_map = (uint32_t*)0xE0400000;

extern tty_t *ttys;
extern tty_t *active_tty;

void init_stdio() {
	ttys = new tty_t[12];
	for(size_t i = 0; i < 12; i++) {
		ttys[i].driver = new vga_tty_driver;
		ttys[i].driver->initialize();
	}
	active_tty = &ttys[0];
	os_kb = new keyboard_t;
	os_kb->driver = new ps2_keyboard;
}

void deinit_stdio() {
	for(size_t i = 0; i < 12; i++) {
		if(ttys[i].driver) delete ttys[i].driver;
		if(ttys[i].secondary) delete ttys[i].secondary;
	}
	delete[] ttys;
	ttys = nullptr;
	active_tty = nullptr;
	delete os_kb->driver;
	delete os_kb;
	os_kb = nullptr;
}

extern "C" void _load(pthread_t pid) {
	asm volatile goto("cli;"								// Disable interrupts
					  "movl %%ebp, %0;" 					// Save base pointer
					  "movl %%esp, %1;"						// Save stack pointer
					  "pushal;"								// Push general purpose registers
					  "pushfl;"								// Push %flags
					  "movw %%cs, %2;"						// Push code segment for far jump
					  "call %l3"							// Will push address to next instruction onto stack
					  : "=m"(__this_thread->ebp),
					    "=m"(__this_thread->esp),
					    "=m"(__this_thread->cs)
					  :
					  :
					  : jump); 

// will run on parent thread when resuming
	return;
jump:
	asm volatile("popl %0;"									// Pull return address from stack
				 : "=m"(__this_thread->eip));

	__this_thread = _threads[pid];

	asm volatile("movl %0, %%ebp;"							// Load new base pointer
				 "movl %1, %%esp;"							// Load new stack pointer
				 "pushl %%eax;"								// Temporarily store %eax
				 "movl %%cr0, %%eax;"						// Copy %cr0 onto %eax
				 "orl %%eax, 8;"							// Set task switch flag
				 "movl %%eax, %%cr0;"						// Save new %cr0
				 "pushfl;"									// Temporarily push %flags register
				 "popl %%eax;"								// Pop it on %eax
				 "orl %%eax, 0x4200;"						// Set new task flag & interrupt flag
				 "pushl %%eax;"								// Push it back on the stack
				 "popfl;"									// And pop back onto %flags
				 "popl %%eax;"								// Pop original %eax
				 "pushfl;"									// Need %flags back on stack for iret
				 "pushl %2;"								// Push code segment for iret
				 "pushl %3;"								// Push address for iret
				 "sti;"										// Re-enable interrupts
				 "iret;"									// Should jump to subroutine and be interpreted as new task
				 :
				 : "m"(__this_thread->ebp),
				   "m"(__this_thread->esp),
				   "m"(__this_thread->cs),
				   "m"(__this_thread->eip));
}

void *pthread_test(void *arg) {
	while(true) {
		printf("Greetings from PID %i!\n", pthread_self());
		_yield();
	}
	__builtin_unreachable();
}

void *pthread_test_master(void *arg) {
	pthread_t pid = 0;
	printf("Greetings from PID %i!\n", pthread_self());
	pthread_create(&pid, nullptr, pthread_test, nullptr);
	while(true) {
		printf("Greetings from PID %i!\n", pthread_self());
		_yield();
	}
	__builtin_unreachable();
}

extern "C" [[noreturn]] void _main() {
	asm volatile("cli");
	memset(page_map, 0, 0x400000);
	for(uint32_t i = 0; i < 0xb00; i++) page_map[i] = 1;
	init_stdio();
	_threads = (_thread_t**)malloc(sizeof(_thread_t*) * 65536);
	memset(_threads, 0, sizeof(_thread_t*) * 65536);
	asm volatile("sti");

	pthread_t pid = 0;
	pthread_create(&pid, nullptr, pthread_test_master, nullptr);

	asm volatile("cli");
	deinit_stdio();
	vga_disable_cursor();
	while(true) {
		asm volatile("hlt");
	}
	__builtin_unreachable();
}
 