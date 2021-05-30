#include <kernel/protovector.hpp>
#include <kernel/keyboard.hpp>

#include <kernel/vga.h>
#include <kernel/kwait.h>
#include <kernel/stdio.h>

#include <stdio.h>

tty_t::tty_t() {
	stdin_buf = new protovector<char>;
	stdout_buf = new protovector<char>;
	stderr_buf = new protovector<char>;
}

tty_t::~tty_t() {
	delete stdin_buf;
	delete stdout_buf;
	delete stderr_buf;
}

char tty_t::get() {
	_kwait_while(stdin_pos >= stdin_buf->size());
	return stdin_buf->at(stdin_pos++);
}

bool tty_t::ungetchar() {
	stdin_buf->pop_back();
	stdin_pos--;
	if(last_stdin && stdin_removable < stdin_pos && driver) {
		driver->removeentry();
		return true;
	}
	return false;
}

void tty_t::putchar(char c) {
	last_stdin = false;
	stdout_buf->push_back(c);
	if(driver) {
		stdout_pos++;
		driver->putchar(c);
	}
}

void tty_t::putechar(char c) {
	last_stdin = false;
	stderr_buf->push_back(c);
	if(driver) {
		stderr_pos++;
		driver->putchar(c);
	}
}

void tty_t::print(char *str) {
	while(*str && *str != EOF) {
		putchar(*str);
		str++;
	}
}

bool tty_t::print_s(const char *str, size_t len) {
	for(size_t i = 0; str[i] && str[i] != EOF; i++) {
		if(i == len) return true;
		putchar(str[i]);
	}
	return false;
}

void tty_t::stderr(char *str) {
	while(*str && *str != EOF) {
		putechar(*str);
		str++;
	}
}

bool tty_t::stderr_s(const char *str, size_t len) {
	for(size_t i = 0; str[i] && str[i] != EOF; i++) {
		if(i == len) return true;
		putechar(str[i]);
	}
	return false;
}

void tty_t::flush() {
	if(!driver) return;
	if(stdout_pos != stdout_buf->size()) {
		driver->writestring(stdout_buf->data() + stdout_pos);
	}
	if(stderr_pos != stderr_buf->size()) {
		driver->writestring(stderr_buf->data() + stderr_pos);
	}
}

tty_t *ttys = nullptr;
tty_t *active_tty = nullptr;
keyboard_t *os_kb = nullptr;

extern "C" char _kget() {
	tty_t *tty = active_tty;
	if(!tty) return 0;
	return tty->get();
}

extern "C" void _kputchar(char c) {
	if(!active_tty) return;
	active_tty->putchar(c);
}

extern "C" void _kprint(char *str) {
	if(!active_tty) return;
	active_tty->print(str);
}

extern "C" bool _kprints(const char *str, size_t len) {
	if(!active_tty) return false;
	active_tty->print_s(str, len);
	return true;
}

extern "C" void _kerror(char *str) {
	if(!active_tty) return;
	active_tty->stderr(str);
}

extern "C" bool _kerrors(const char *str, size_t len) {
	if(!active_tty) return false;
	active_tty->stderr_s(str, len);
	return true;
}
