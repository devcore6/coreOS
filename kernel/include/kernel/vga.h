#ifndef __KERNEL_VGA_H
# define __KERNEL_VGA_H
# ifdef _ARCH_i386
#  include <kernel/arch/i386/vga.h>
# endif
# ifdef _ARCH_x86_64
#  include <kernel/arch/x86_64/vga.h>
# endif
#endif
