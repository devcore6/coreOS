#ifndef __KERNEL_ARCH_I386_VGA_H
# define __KERNEL_ARCH_I386_VGA_H
# include <stdint.h>
# include <stddef.h>
# ifdef __cplusplus
extern "C" {
# endif

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}
extern void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
extern void disable_cursor();
extern void update_cursor(int x, int y);
extern void update_cursor_auto();
extern void vga_initialize();
extern void vga_putentryat(unsigned char c, uint8_t color, size_t x, size_t y);
extern void vga_putchar(char c);
extern void vga_write(const char* data, size_t size);
extern void vga_writestring(const char* data);
extern void vga_linebreak();
extern void vga_removeentry();
extern void vga_setbuf(const char *buf);

# ifdef __cplusplus
}
# endif
#endif
