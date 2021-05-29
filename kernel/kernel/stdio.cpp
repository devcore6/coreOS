#include <kernel/protovector.hpp>
#include <kernel/keyboard.hpp>

#include <kernel/vga.h>

#include <stdio.h>

protovector<char> *_stdin_buf = nullptr;
size_t _stdin_pos = 0;
protovector<char> *_stdout_buf = nullptr;
size_t _stdout_pos = 0;
protovector<char> *_stderr_buf = nullptr;
size_t _stderr_pos = 0;

void try_removeentry() {
	vga_removeentry();
	_stdin_buf->pop_back();
	_stdin_pos--;
	_stdout_buf->pop_back();
	_stdout_pos--;
}

extern "C" void on_pit_tick() { // called every PIT tick
	if(!_stdin_buf) return;
	auto kb = find_keyboard();
	uint16_t c = 0;
	while((c = kb->__poll_keyboard()) != 0 && c <= 0x80) {
		if(c == PS2_BACKSPACE) try_removeentry();
		else {
			putchar(kb->get_char(c));
			_stdin_buf->push_back(kb->get_char(c));
		}
	}
}

extern "C" void flush_stdout() {
	vga_setbuf(_stdout_buf->data());
}

extern "C" char _kget() {
	while(_stdin_pos == _stdin_buf->size()) {
		asm volatile("hlt");
	}
	_stdin_pos++;
	return _stdin_buf->at(_stdin_pos - 1);
}

extern "C" void _kputchar(char c) {
	_stdout_buf->push_back(c);
	_stdout_pos++;
	vga_putchar(c);
}

extern "C" void _kprint(char *str) {
	while(*str && *str != EOF) { _stdout_buf->push_back(*str); str++; _stdout_pos++; }
	flush_stdout();
}

extern "C" bool _kprints(const char *str, size_t len) {
	size_t i = 0;
	while(*str && *str != EOF) {
		if(i == len) return true;
		_stdout_buf->push_back(*str);
		str++;
		_stdout_pos++;
		i++;
	}
	flush_stdout();
	return false;
}

extern "C" void _kerror(char *str) {
	while(*str && *str != EOF) { _stderr_buf->push_back(*str); str++; _stderr_pos++; }
}
