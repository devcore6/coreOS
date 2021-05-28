#include <kernel/putchar.h>

#include <vga/vga.h>

void klinebreak() {
	if(get_vga_mode()) {
		//__vga_putc('\n');
	} else {
		vga_linebreak();
	}
}

void kputc(c) {
	if(get_vga_mode()) {
		//__vga_putc(c);
	} else {
		vga_putchar(c);
		update_cursor_auto();
	}
}
