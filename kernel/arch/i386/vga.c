#include <kernel/arch/i386/vga.h>
#include <kernel/arch/i386/io.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xE00B8000;

static size_t vga_row;
static size_t vga_column;
static uint8_t vga_color;
static uint16_t* vga_buffer;

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void update_cursor(int x, int y) {
	uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void update_cursor_auto() {
	uint16_t pos = vga_row * VGA_WIDTH + vga_column;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void vga_initialize(void) {
	vga_row = 0;
	vga_column = 0;
	vga_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	vga_buffer = VGA_MEMORY;
	for(size_t y = 0; y < VGA_HEIGHT; y++) {
		for(size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			vga_buffer[index] = vga_entry(' ', vga_color);
		}
	}
}

void vga_setcolor(uint8_t color) {
	vga_color = color;
}

void vga_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	vga_buffer[index] = vga_entry(c, color);
}

void vga_scroll() {
	memmove(vga_buffer, vga_buffer + VGA_WIDTH, (VGA_HEIGHT - 1) * VGA_WIDTH * sizeof(uint16_t));
	for(size_t x = 0; x < VGA_WIDTH; x++) {
		*(vga_buffer + x + ((VGA_HEIGHT - 1) * VGA_WIDTH)) = vga_entry(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
	}
	vga_row--;
	vga_column = 0;
}

void vga_putchar(char c) {
	if(c == '\n') {
		vga_linebreak();
		return;
	}
	unsigned char uc = c;
	vga_putentryat(uc, vga_color, vga_column, vga_row);
	if(++vga_column == VGA_WIDTH) {
		vga_column = 0;
		if(++vga_row == VGA_HEIGHT)
			vga_scroll();
	}
	update_cursor_auto();
}

void vga_write(const char* data, size_t size) {
	for(size_t i = 0; i < size; i++)
		vga_putchar(data[i]);
}

void vga_writestring(const char* data) {
	vga_write(data, strlen(data));
}

void vga_linebreak() {
	vga_column = 0;
	if(++vga_row == VGA_HEIGHT)
		vga_scroll();
	update_cursor_auto();
}

void vga_removeentry() {
	if(vga_column == 0) return;
	vga_column--;
	vga_putchar(' ');
	vga_column--;
	update_cursor_auto();
}

void vga_setbuf(const char *buf) {
	vga_initialize();
	vga_writestring(buf);
}
