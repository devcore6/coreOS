#ifndef __KERNEL_KEYBOARD_HPP
# define __KERNEL_KEYBOARD_HPP
# include <cstdint>
# include <kernel/kwait.h>

enum {
	PS2_ESCAPE					= 0x01,
	PS2_1 						= 0x02,
	PS2_2						= 0x03,
	PS2_3						= 0x04,
	PS2_4						= 0x05,
	PS2_5						= 0x06,
	PS2_6						= 0x07,
	PS2_7						= 0x08,
	PS2_8						= 0x09,
	PS2_9						= 0x0A,
	PS2_0						= 0x0B,
	PS2_MINUS					= 0x0C,
	PS2_EQUAL					= 0x0D,
	PS2_BACKSPACE				= 0x0E,
	PS2_TAB						= 0x0F,
	PS2_Q						= 0x10,
	PS2_W						= 0x11,
	PS2_E						= 0x12,
	PS2_R						= 0x13,
	PS2_T						= 0x14,
	PS2_Y						= 0x15,
	PS2_U						= 0x16,
	PS2_I						= 0x17,
	PS2_O						= 0x18,
	PS2_P						= 0x19,
	PS2_LEFTBRACKET				= 0x1A,
	PS2_RIGHTBRACKET			= 0x1B,
	PS2_ENTER					= 0x1C,
	PS2_LEFTCONTROL				= 0x1D,
	PS2_A						= 0x1E,
	PS2_S						= 0x1F,
	PS2_D						= 0x20,
	PS2_F						= 0x21,
	PS2_G						= 0x22,
	PS2_H						= 0x23,
	PS2_J						= 0x24,
	PS2_K						= 0x25,
	PS2_L						= 0x26,
	PS2_SEMICOLON				= 0x27,
	PS2_SINGLEQUOTE				= 0x28,
	PS2_ACCENT					= 0x29,
	PS2_LEFTSHIFT				= 0x2A,
	PS2_Z						= 0x2C,
	PS2_X						= 0x2D,
	PS2_C						= 0x2E,
	PS2_V						= 0x2F,
	PS2_B						= 0x30,
	PS2_N						= 0x31,
	PS2_M						= 0x32,
	PS2_COMMA					= 0x33,
	PS2_DOT						= 0x34,
	PS2_SLASH					= 0x35,
	PS2_RIGHTSHIFT				= 0x36,
	PS2_KPMUL					= 0x37,
	PS2_LEFTALT					= 0x38,
	PS2_SPACE					= 0x39,
	PS2_CAPSLOCK				= 0x3A,
	PS2_F1						= 0x3B,
	PS2_F2						= 0x3C,
	PS2_F3						= 0x3D,
	PS2_F4						= 0x3E,
	PS2_F5						= 0x3F,
	PS2_F6						= 0x40,
	PS2_F7						= 0x41,
	PS2_F8						= 0x42,
	PS2_F9						= 0x43,
	PS2_F10						= 0x44,
	PS2_NUMLOCK					= 0x45,
	PS2_SCROLLOCK				= 0x46,
	PS2_KP7						= 0x47,
	PS2_KP8						= 0x48,
	PS2_KP9						= 0x49,
	PS2_KPMINUS					= 0x4A,
	PS2_KP4						= 0x4B,
	PS2_KP5						= 0x4C,
	PS2_KP6						= 0x4D,
	PS2_KPPLUS					= 0x4E,
	PS2_KP1						= 0x4F,
	PS2_KP2						= 0x50,
	PS2_KP3						= 0x51,
	PS2_KP0						= 0x52,
	PS2_KPDOT					= 0x53,
	PS2_F11						= 0x57,
	PS2_F12						= 0x58,
	PS2_RELEASE_ESCAPE			= 0x81,
	PS2_RELEASE_1 				= 0x82,
	PS2_RELEASE_2				= 0x83,
	PS2_RELEASE_3				= 0x84,
	PS2_RELEASE_4				= 0x85,
	PS2_RELEASE_5				= 0x86,
	PS2_RELEASE_6				= 0x87,
	PS2_RELEASE_7				= 0x88,
	PS2_RELEASE_8				= 0x89,
	PS2_RELEASE_9				= 0x8A,
	PS2_RELEASE_0				= 0x8B,
	PS2_RELEASE_MINUS			= 0x8C,
	PS2_RELEASE_EQUAL			= 0x8D,
	PS2_RELEASE_BACKSPACE		= 0x8E,
	PS2_RELEASE_TAB				= 0x8F,
	PS2_RELEASE_Q				= 0x90,
	PS2_RELEASE_W				= 0x91,
	PS2_RELEASE_E				= 0x92,
	PS2_RELEASE_R				= 0x93,
	PS2_RELEASE_T				= 0x94,
	PS2_RELEASE_Y				= 0x95,
	PS2_RELEASE_U				= 0x96,
	PS2_RELEASE_I				= 0x97,
	PS2_RELEASE_O				= 0x98,
	PS2_RELEASE_P				= 0x99,
	PS2_RELEASE_LEFTBRACKET		= 0x9A,
	PS2_RELEASE_RIGHTBRACKET	= 0x9B,
	PS2_RELEASE_ENTER			= 0x9C,
	PS2_RELEASE_LEFTCONTROL		= 0x9D,
	PS2_RELEASE_A				= 0x9E,
	PS2_RELEASE_S				= 0x9F,
	PS2_RELEASE_D				= 0xA0,
	PS2_RELEASE_F				= 0xA1,
	PS2_RELEASE_G				= 0xA2,
	PS2_RELEASE_H				= 0xA3,
	PS2_RELEASE_J				= 0xA4,
	PS2_RELEASE_K				= 0xA5,
	PS2_RELEASE_L				= 0xA6,
	PS2_RELEASE_SEMICOLON		= 0xA7,
	PS2_RELEASE_SINGLEQUOTE		= 0xA8,
	PS2_RELEASE_ACCENT			= 0xA9,
	PS2_RELEASE_LEFTSHIFT		= 0xAA,
	PS2_RELEASE_Z				= 0xAC,
	PS2_RELEASE_X				= 0xAD,
	PS2_RELEASE_C				= 0xAE,
	PS2_RELEASE_V				= 0xAF,
	PS2_RELEASE_B				= 0xB0,
	PS2_RELEASE_N				= 0xB1,
	PS2_RELEASE_M				= 0xB2,
	PS2_RELEASE_COMMA			= 0xB3,
	PS2_RELEASE_DOT				= 0xB4,
	PS2_RELEASE_SLASH			= 0xB5,
	PS2_RELEASE_RIGHTSHIFT		= 0xB6,
	PS2_RELEASE_KPMUL			= 0xB7,
	PS2_RELEASE_LEFTALT			= 0xB8,
	PS2_RELEASE_SPACE			= 0xB9,
	PS2_RELEASE_CAPSLOCK		= 0xBA,
	PS2_RELEASE_F1				= 0xBB,
	PS2_RELEASE_F2				= 0xBC,
	PS2_RELEASE_F3				= 0xBD,
	PS2_RELEASE_F4				= 0xBE,
	PS2_RELEASE_F5				= 0xCF,
	PS2_RELEASE_F6				= 0xC0,
	PS2_RELEASE_F7				= 0xC1,
	PS2_RELEASE_F8				= 0xC2,
	PS2_RELEASE_F9				= 0xC3,
	PS2_RELEASE_F10				= 0xC4,
	PS2_RELEASE_NUMLOCK			= 0xC5,
	PS2_RELEASE_SCROLLOCK		= 0xC6,
	PS2_RELEASE_KP7				= 0xC7,
	PS2_RELEASE_KP8				= 0xC8,
	PS2_RELEASE_KP9				= 0xC9,
	PS2_RELEASE_KPMINUS			= 0xCA,
	PS2_RELEASE_KP4				= 0xCB,
	PS2_RELEASE_KP5				= 0xCC,
	PS2_RELEASE_KP6				= 0xCD,
	PS2_RELEASE_KPPLUS			= 0xDE,
	PS2_RELEASE_KP1				= 0xDF,
	PS2_RELEASE_KP2				= 0xD0,
	PS2_RELEASE_KP3				= 0xD1,
	PS2_RELEASE_KP0				= 0xD2,
	PS2_RELEASE_KPDOT			= 0xD3,
	PS2_RELEASE_F11				= 0xD7,
	PS2_RELEASE_F12				= 0xD8,

	PS2_EXTENDED				= 0xE0
};

class keyboard_driver {
public:
	virtual uint16_t poll_keyboard() { return 0; }
	virtual char get_char(uint16_t c,
						  bool numpad,
						  bool caps,
						  bool ctrl,
						  bool alt,
						  bool altgr,
						  bool super) { return 0; }
	virtual void update_lights(bool num_lock,
							   bool caps_lock,
							   bool scroll_lock) { }
	virtual void enable() { }
	virtual void disable() { }
};

class keyboard_t {
public:
	uint16_t poll_keyboard() {

		if(driver) {
			uint16_t keystroke = driver->poll_keyboard();

			switch(keystroke) {
				case PS2_LEFTSHIFT: { left_shift = true; break; }
				case PS2_RIGHTSHIFT: { right_shift = true; break; }
				case PS2_LEFTCONTROL: { left_control = true; break; }
				//case PS2_RIGHTCONTROL: { right_control = true; break; }
				case PS2_LEFTALT: { alt = true; break; }
				//case PS2_ALTGR: { altgr = true; break; }
				//case PS2_LEFTSUPER: { left_super = true; break; }
				//case PS2_RIGHTSUPER: { right_super = true; break; }

				case PS2_RELEASE_LEFTSHIFT: { left_shift = false; break; }
				case PS2_RELEASE_RIGHTSHIFT: { right_shift = false; break; }
				case PS2_RELEASE_LEFTCONTROL: { left_control = false; break; }
				//case PS2_RELEASE_RIGHTCONTROL: { right_control = false; break; }
				case PS2_RELEASE_LEFTALT: { alt = false; break; }
				//case PS2_RELEASE_ALTGR: { altgr = false; break; }
				//case PS2_RELEASE_LEFTSUPER: { left_super = false; break; }
				//case PS2_RELEASE_RIGHTSUPER: { right_super = false; break; }

				case PS2_NUMLOCK: { num_lock = !num_lock; driver->update_lights(num_lock, caps_lock, scroll_lock); break; }
				case PS2_CAPSLOCK: { caps_lock = !caps_lock; driver->update_lights(num_lock, caps_lock, scroll_lock); break; }
				case PS2_SCROLLOCK: { scroll_lock = !scroll_lock; driver->update_lights(num_lock, caps_lock, scroll_lock); break; }
			}

			return keystroke;
		}

		return 0;
	}

	char get_char(uint16_t c) {

		if(driver) return driver->get_char(c,
			num_lock,
			(left_shift || right_shift || caps_lock),
			(left_control || right_control),
			alt,
			alt_gr,
			(left_super || right_super));

		return 0;
	}

	bool left_shift = false;
	bool right_shift = false;
	bool left_control = false;
	bool right_control = false;
	bool alt = false;
	bool alt_gr = false;
	bool left_super = false;
	bool right_super = false;

	bool num_lock = false;
	bool caps_lock = false;
	bool scroll_lock = false;

	keyboard_driver *driver = nullptr;
};

#endif
