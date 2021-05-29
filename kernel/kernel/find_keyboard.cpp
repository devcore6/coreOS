#include <kernel/keyboard.hpp>

#include <ps2/kb.hpp>

keyboard_t *os_keyboard = nullptr;

keyboard_t *find_keyboard() {
	if(!os_keyboard) {
		os_keyboard = new keyboard_t;
		// do something to detect available keyboard drivers, for now we only have ps2
		os_keyboard->driver = new ps2_keyboard;
	}
	return os_keyboard;
}
