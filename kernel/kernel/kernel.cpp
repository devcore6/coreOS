#include <kernel/arch/i386/pit.h>
#include <kernel/arch/i386/paging.h>

#include <kernel/thread.h>

#include <vga/vga.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" _thread_t* __this_thread = nullptr;
extern "C" _thread_t** _threads;

extern "C" uint32_t *page_map = (uint32_t*)0xE0400000;

extern "C" void _main() {
	memset(page_map, 0, 0x400000);
	for(uint32_t i = 0; i < 0x800; i++) page_map[i] = 1;
	vga_initialize();
}
 