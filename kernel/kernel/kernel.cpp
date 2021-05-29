#include <kernel/arch/i386/pit.h>
#include <kernel/arch/i386/paging.h>

#include <kernel/protovector.hpp>
#include <kernel/thread.h>

#include <vga/vga.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" _thread_t* __this_thread = nullptr;
extern "C" _thread_t** _threads;

extern "C" uint32_t *page_map = (uint32_t*)0xE0400000;

#include<kernel/stdio.h>

extern protovector<char> *_stdin_buf;
extern protovector<char> *_stdout_buf;
extern protovector<char> *_stderr_buf;

void init_stdio() {
	_stdin_buf = new protovector<char>;
	_stdout_buf = new protovector<char>;
	_stderr_buf = new protovector<char>;
}

void deinit_stdio() {
	asm volatile("cli");
	delete _stdin_buf; _stdin_buf = nullptr;
	delete _stdout_buf; _stdout_buf = nullptr;
	delete _stderr_buf; _stderr_buf = nullptr;
	asm volatile("sti");
}

extern "C" void _main() [[noreturn]] {
	memset(page_map, 0, 0x400000);
	for(uint32_t i = 0; i < 0xb00; i++) page_map[i] = 1;
	vga_initialize();
	init_stdio();
	char *test = new char[512];
	printf("input something: ");
	gets(test);
	printf("your input: %s\n", test);
	deinit_stdio();
	disable_cursor();
	asm volatile("cli");
	while(true) {
		asm volatile("hlt");
	}
	__builtin_unreachable();
}
 