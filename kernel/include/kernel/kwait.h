#ifndef __KERNEL__KWAIT_H
# define __KERNEL__KWAIT_H
# ifndef __cplusplus
#  include <stdbool.h>
# endif
# include <kernel/arch/i386/pit.h>
inline void _kwait(uint32_t ms) {
	uint32_t target_ms = system_timer_ms + ms;
	while(target_ms >= system_timer_ms) {
		// Put the CPU in a lower power state while we wait
		asm volatile("hlt");
	}
}

# define _kwait_for(expr) { while(!expr) { asm volatile("hlt"); } }
# define _kwait_while(expr) { while(expr) { asm volatile("hlt"); } }

#endif
