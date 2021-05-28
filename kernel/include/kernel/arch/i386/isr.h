#ifndef __KERNEL_ARCH_I386_ISR_H
# define __KERNEL_ARCH_I386_ISR_H
# include <stdint.h>
# include <stdio.h>
# ifdef __cplusplus
extern "C" {
# endif

	struct interrupt_frame {
		uint16_t ip;
		uint16_t cs;
		uint16_t flags;
		uint16_t sp;
		uint16_t ss;
	} __attribute__((packed));

	extern void divide_by_zero(struct interrupt_frame*);
	extern void double_fault(struct interrupt_frame*);
	extern void protection_fault(struct interrupt_frame*);
	extern void page_fault(struct interrupt_frame*);
	extern void irq0();
	extern void irq1(struct interrupt_frame*);
	extern void irq2(struct interrupt_frame*);
	extern void irq3(struct interrupt_frame*);
	extern void irq4(struct interrupt_frame*);
	extern void irq5(struct interrupt_frame*);
	extern void irq6(struct interrupt_frame*);
	extern void irq7(struct interrupt_frame*);
	extern void irq8(struct interrupt_frame*);
	extern void irq9(struct interrupt_frame*);
	extern void irq10(struct interrupt_frame*);
	extern void irq11(struct interrupt_frame*);
	extern void irq12(struct interrupt_frame*);
	extern void irq13(struct interrupt_frame*);
	extern void irq14(struct interrupt_frame*);
	extern void irq15(struct interrupt_frame*);

# ifdef __cplusplus
}
# endif
#endif
