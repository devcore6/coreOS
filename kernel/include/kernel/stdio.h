#ifndef __KERNEL_STDIO_H
# define __KERNEL_STDIO_H

# ifdef __cplusplus
#  include <kernel/protovector.hpp>
#  include <kernel/keyboard.hpp>

#  include <kernel/vga.h>

class tty_driver {
public:
	virtual void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) { }
	virtual void disable_cursor() { }
	virtual void update_cursor(int x, int y) { }
	virtual void update_cursor_auto() { }
	virtual void initialize() { }
	virtual void putentryat(unsigned char c, uint8_t color, size_t x, size_t y) { }
	virtual void putchar(char c) { }
	virtual void write(const char* data, size_t size) { }
	virtual void writestring(const char* data) { }
	virtual void linebreak() { }
	virtual void removeentry() { }
	virtual void clear() { }
	virtual void setbuf(const char *buf) { }
	virtual void flush() { }
};

class vga_tty_driver : public tty_driver {
private:
	size_t _row;
	size_t _column;
	uint8_t _color;
	uint16_t* _buffer = nullptr;

	void scroll() {
		memmove(_buffer, _buffer + 80, 24 * 80 * sizeof(uint16_t));
		for(size_t x = 0; x < 80; x++) {
			*(_buffer + x + (24 * 80)) = vga_entry(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
		}
		_row--;
		_column = 0;
	}

public:
	void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) { vga_enable_cursor(cursor_start, cursor_end); }
	void disable_cursor() { vga_disable_cursor(); }
	void update_cursor(int x, int y) { vga_update_cursor(x, y); }
	void update_cursor_auto() { vga_update_cursor(_column, _row); }
	void initialize() {
		vga_initialize();
		if(_buffer) free(_buffer);
		_buffer = (uint16_t*)malloc(sizeof(uint16_t) * 80 * 25);
		_row = 0;
		_column = 0;
		_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		for(size_t y = 0; y < 25; y++) {
			for(size_t x = 0; x < 80; x++) {
				const size_t index = y * 80 + x;
				_buffer[index] = vga_entry(' ', _color);
			}
		}
	}
	void putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
		const size_t index = y * 80 + x;
		_buffer[index] = vga_entry(c, color);
		vga_putentryat(c, color, x, y);
	}
	void putchar(char c) {
		if(c == '\n') {
			_column = 0;
			if(++_row == 25) scroll();
			vga_linebreak();
			return;
		}
		unsigned char uc = c;
		putentryat(uc, _color, _column, _row);
		if(++_column == 80) {
			_column = 0;
			if(++_row == 25)
				scroll();
		}
		update_cursor_auto();
		vga_putchar(c);
	}
	void write(const char* data, size_t size) {
		for(size_t i = 0; i < size; i++) putchar(data[i]);
	}
	void writestring(const char* data) {
		for(size_t i = 0; i < strlen(data); i++) putchar(data[i]);
	}
	void linebreak() {
		_column = 0;
		if(++_row == 25) scroll();
	}
	void removeentry() {
		if(_column == 0) return;
		_column--;
		putchar(' ');
		_column--;
		update_cursor_auto();
	}
	void clear() {
		if(!_buffer) return;
		for(size_t y = 0; y < 25; y++) {
			for(size_t x = 0; x < 80; x++) {
				const size_t index = y * 80 + x;
				_buffer[index] = vga_entry(' ', _color);
			}
		}
	}
	void setbuf(const char* buf) {
		initialize();
		writestring(buf);
	}
	void flush() { memcpy((void*)0xE00B8000, _buffer, sizeof(uint16_t) * 80 * 25); update_cursor_auto(); }
};

class tty_t {
private:
	protovector<char> *stdout_buf = nullptr;
	size_t stdout_pos = 0;
	protovector<char> *stderr_buf = nullptr;
	size_t stderr_pos = 0;

public:
	protovector<char> *stdin_buf = nullptr;
	size_t stdin_pos = 0;
	size_t stdin_removable = 0;
	bool last_stdin = false;
	tty_driver *driver = nullptr;		// Primary screen/terminal output
	tty_driver *secondary = nullptr;	// Will be used to mirror output onto serial/file

	tty_t();
	~tty_t();

	char get();
	void add(char c);
	bool ungetchar();
	void putchar(char c);
	void putechar(char c);
	void print(char *str);
	bool print_s(const char *str, size_t len);
	void stderr(char *str);
	bool stderr_s(const char *str, size_t len);
	void flush();
};

extern keyboard_t *os_kb;

extern "C" {
# else
#  include <stdbool.h>
# endif

# include <stddef.h>

extern void flush_stdout();
extern char _kget();
extern void _kputchar(char c);
extern void _kprint(char *str);
extern bool _kprints(const char *str, size_t len);
extern void _kerror(char *str);
extern bool _kerrors(const char *str, size_t len);

# ifdef __cplusplus
}
# endif

#endif
