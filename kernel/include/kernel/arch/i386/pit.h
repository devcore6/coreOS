#ifndef __KERNEL_ARCH_I386_PIT_H
# define __KERNEL_ARCH_I386_PIT_H
# ifdef __cplusplus
extern "C" {
# endif
extern volatile unsigned long system_timer_fractions;	// GCC will optimize these out if they're not volatile
extern volatile unsigned long system_timer_ms;			// GCC will optimize these out if they're not volatile
# ifdef __cplusplus
}
# endif
#endif
