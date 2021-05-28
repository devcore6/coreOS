#ifndef __KERNEL_ARCH_I386_IO_H
# define __KERNEL_ARCH_I386_IO_H
# include <stdint.h>

inline uint8_t outb(uint16_t port, uint8_t value) {
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
	return value;
}

inline uint16_t outw(uint16_t port, uint16_t value) {
	asm volatile ("outw %1, %0" : : "dN" (port), "a" (value));
	return value;
}

inline uint32_t outl(uint16_t port, uint32_t value) {
	asm volatile ("outl %1, %0" : : "dN" (port), "a" (value));
	return value;
}

inline uint8_t inb(uint16_t port) {
	uint8_t result;
	asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));
	return result;
}

inline uint16_t inw(uint16_t port) {
	uint16_t result;
	asm volatile("inw %1, %0" : "=a" (result) : "dN" (port));
	return result;
}

inline uint32_t inl(uint16_t port) {
	uint32_t result;
	asm volatile("inl %1, %0" : "=a" (result) : "dN" (port));
	return result;
}
#endif
