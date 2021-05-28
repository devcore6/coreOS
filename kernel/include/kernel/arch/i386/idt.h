#ifndef __KERNEL_ARCH_I386_IDT_H
# define __KERNEL_ARCH_I386_IDT_H
# ifdef __cplusplus
extern "C" {
# endif

	struct IDT_entry{
		unsigned short int offset_lowerbits;
		unsigned short int selector;
		unsigned char zero;
		unsigned char type_attr;
		unsigned short int offset_higherbits;
	};

	struct IDT_entry IDT[256];

# ifdef __cplusplus
}
# endif
#endif
