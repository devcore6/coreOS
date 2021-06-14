#ifndef __DRIVERS_PS2_KB_HPP
# define __DRIVERS_PS2_KB_HPP
# include <kernel/keyboard.hpp>
# include <kernel/io.h>

# include <stdint.h>
# include <stddef.h>
# include <stdio.h>

class ps2_keyboard : public keyboard_driver {
public:
	uint16_t poll_keyboard() {
		uint16_t val = 0;
		for(size_t i = 0; i < 128; i++) {
			val = inb(0x64);
			if(val & 0x01) {
				val = inb(0x60);
				/*if(val == PS2_EXTENDED) {
					outb(0x64, 0xD2);
					while(!(val & 0x01)) asm volatile("nop");
					val = inb(0x60);
				}*/
				return val;
			}
		}
		return 0;
	}

	char get_char(uint16_t c,
				  bool numpad,
				  bool caps,
				  bool ctrl,
				  bool alt,
				  bool altgr,
				  bool super) {
		switch(c) {
			case PS2_1: return caps ? '!' : '1';
			case PS2_2: return caps ? '@' : '2';
			case PS2_3: return caps ? '#' : '3';
			case PS2_4: return caps ? '$' : '4';
			case PS2_5: return caps ? '%' : '5';
			case PS2_6: return caps ? '^' : '6';
			case PS2_7: return caps ? '&' : '7';
			case PS2_8: return caps ? '*' : '8';
			case PS2_9: return caps ? '(' : '9';
			case PS2_0: return caps ? ')' : '0';
			case PS2_MINUS: return caps ? '_' : '-';
			case PS2_EQUAL: return caps ? '+' : '=';
			case PS2_TAB: return '\t';
			case PS2_Q: return caps ? 'Q' : 'q';
			case PS2_W: return caps ? 'W' : 'w';
			case PS2_E: return caps ? 'E' : 'e';
			case PS2_R: return caps ? 'R' : 'r';
			case PS2_T: return caps ? 'T' : 't';
			case PS2_Y: return caps ? 'Y' : 'y';
			case PS2_U: return caps ? 'U' : 'u';
			case PS2_I: return caps ? 'I' : 'i';
			case PS2_O: return caps ? 'O' : 'o';
			case PS2_P: return caps ? 'P' : 'p';
			case PS2_LEFTBRACKET: return caps ? '{' : '[';
			case PS2_RIGHTBRACKET: return caps ? '}' : ']';
			case PS2_ENTER: return '\n';
			case PS2_A: return caps ? 'A' : 'a';
			case PS2_S: return caps ? 'S' : 's';
			case PS2_D: return caps ? 'D' : 'd';
			case PS2_F: return caps ? 'F' : 'f';
			case PS2_G: return caps ? 'G' : 'g';
			case PS2_H: return caps ? 'H' : 'h';
			case PS2_J: return caps ? 'J' : 'j';
			case PS2_K: return caps ? 'K' : 'k';
			case PS2_L: return caps ? 'L' : 'l';
			case PS2_SEMICOLON: return caps ? ':' : ';';
			case PS2_SINGLEQUOTE: return caps ? '"' : '\'';
			case PS2_ACCENT: return caps ? '~' : '`';
			case PS2_Z: return caps ? 'Z' : 'z';
			case PS2_X: return caps ? 'X' : 'x';
			case PS2_C: return caps ? 'C' : 'c';
			case PS2_V: return caps ? 'V' : 'v';
			case PS2_B: return caps ? 'B' : 'b';
			case PS2_N: return caps ? 'N' : 'n';
			case PS2_M: return caps ? 'M' : 'm';
			case PS2_COMMA: return caps ? '<' : ',';
			case PS2_DOT: return caps ? '>' : '.';
			case PS2_SLASH: return caps ? '?' : '/';
			case PS2_KPMUL: return numpad ? '*' : 0;
			case PS2_SPACE: return ' ';
			case PS2_KP7: return numpad ? '7' : 0;
			case PS2_KP8: return numpad ? '8' : 0;
			case PS2_KP9: return numpad ? '9' : 0;
			case PS2_KPMINUS: return numpad ? '-' : 0;
			case PS2_KP4: return numpad ? '4' : 0;
			case PS2_KP5: return numpad ? '5' : 0;
			case PS2_KP6: return numpad ? '6' : 0;
			case PS2_KPPLUS: return numpad ? '+' : 0;
			case PS2_KP1: return numpad ? '1' : 0;
			case PS2_KP2: return numpad ? '2' : 0;
			case PS2_KP3: return numpad ? '3' : 0;
			case PS2_KP0: return numpad ? '0' : 0;
			case PS2_KPDOT: return numpad ? '.' : 0;
		}
		return 0;
	}
	void update_lights(bool num_lock,
					   bool caps_lock,
					   bool scroll_lock) {

	}
	void enable() { }
	void disable() { }
};

#endif