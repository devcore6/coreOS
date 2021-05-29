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

extern "C" _thread_t* __this_thread = nullptr;
extern "C" _thread_t** _threads;

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

extern "C" void _main() [[noreturn]] {
	asm volatile("cli");
	memset(page_map, 0, 0x400000);
	for(uint32_t i = 0; i < 0xb00; i++) page_map[i] = 1;
	init_stdio();
	asm volatile("sti");
	char test [512] = { };
	printf("waiting 3 seconds, input something: ");
	_kwait(3000);
	printf("waited\n");
	gets(test);
	printf("your input: %s\n", test);
	asm volatile("cli");
	deinit_stdio();
	vga_disable_cursor();
	while(true) {
		asm volatile("hlt");
	}
	__builtin_unreachable();
}
 