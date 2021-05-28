#ifndef __KERNEL_ARCH_I386_PAGING_H
# define __KERNEL_ARCH_I386_PAGING_H
# ifdef __cplusplus
extern "C" {
# endif
# include <stdint.h>

enum {
	PAGE_PRESENT			= 1 << 0,
	PAGE_READWRITE			= 1 << 1,
	PAGE_USERSUPERVISOR		= 1 << 2,
	PAGE_WRITETHROUGH		= 1 << 3,
	PAGE_NOCACHE			= 1 << 4,
	PAGE_ACCESSED			= 1 << 5
};

extern void map_page(void *physaddr, void *virtualaddr, uint32_t flags);
extern void *get_physaddr(void *virtualaddr);
# ifdef __cplusplus
}
# endif
#endif