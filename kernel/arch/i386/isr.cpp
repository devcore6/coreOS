#include <kernel/arch/i386/isr.h>
#include <kernel/arch/i386/vga.h>

#include <kernel/thread.h>

#include <stdlib.h>

extern "C" {

	__attribute__((interrupt)) void divide_by_zero(struct interrupt_frame* frame) {
		if(__this_thread == nullptr) { // division by zero in kernel
			printf("Division by zero!\n");
			abort();
		} else {
			
		}
	}

	__attribute__((interrupt)) void double_fault(struct interrupt_frame* frame) {
		if(__this_thread == nullptr) { // page fault in kernel
			vga_initialize();
			uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, cr0, cr2, cr3, cr4;
			asm("movl %%eax, %[a1] ;"
				"movl %%ebx, %[b1] ;"
				"movl %%ecx, %[c1] ;"
				"movl %%edx, %[d1] ;"
				"movl %%esi, %[a2] ;"
				"movl %%edi, %[b2] ;"
				"movl %%esp, %[c2] ;"
				"movl %%ebp, %[d2] ;"
				"movl %%cr0, %%eax ;"
				"movl %%eax, %[a3] ;"
				"movl %%cr2, %%eax ;"
				"movl %%eax, %[b3] ;"
				"movl %%cr3, %%eax ;"
				"movl %%eax, %[c3] ;"
				"movl %%cr4, %%eax ;"
				"movl %%eax, %[d3] ;"
				:
				[a1] "=m" (eax), [b1] "=m" (ebx), [c1] "=m" (ecx), [d1] "=m" (edx),
				[a2] "=m" (esi), [b2] "=m" (edi), [c2] "=m" (esp), [d2] "=m" (ebp),
				[a3] "=m" (cr0), [b3] "=m" (cr2), [c3] "=m" (cr3), [d3] "=m" (cr4)
			);
			printf("double fault!\n");
			printf("  eax: %08x - ebx: %08x - ecx: %08x - edx: %08x\n", eax, ebx, ecx, edx);
			printf("  esi: %08x - edi: %08x - esp: %08x - ebp: %08x\n", esi, edi, esp, ebp);
			printf("  cr0: %08x - cr2: %08x - cr3: %08x - cr4: %08x\n", cr0, cr2, cr3, cr4);
			printf("   ip: %04x     -  cs: %04x     -  sp: %04x     -  ss: %04x\n", frame->ip, frame->cs, frame->sp, frame->ss);
			printf("flags: %04x\n", frame->flags);
			abort();
		} else {
			
		}
	}

	__attribute__((interrupt)) void protection_fault(struct interrupt_frame* frame) {
		if(__this_thread == nullptr) { // page fault in kernel
			vga_initialize();
			uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, cr0, cr2, cr3, cr4;
			asm("movl %%eax, %[a1] ;"
				"movl %%ebx, %[b1] ;"
				"movl %%ecx, %[c1] ;"
				"movl %%edx, %[d1] ;"
				"movl %%esi, %[a2] ;"
				"movl %%edi, %[b2] ;"
				"movl %%esp, %[c2] ;"
				"movl %%ebp, %[d2] ;"
				"movl %%cr0, %%eax ;"
				"movl %%eax, %[a3] ;"
				"movl %%cr2, %%eax ;"
				"movl %%eax, %[b3] ;"
				"movl %%cr3, %%eax ;"
				"movl %%eax, %[c3] ;"
				"movl %%cr4, %%eax ;"
				"movl %%eax, %[d3] ;"
				:
				[a1] "=m" (eax), [b1] "=m" (ebx), [c1] "=m" (ecx), [d1] "=m" (edx),
				[a2] "=m" (esi), [b2] "=m" (edi), [c2] "=m" (esp), [d2] "=m" (ebp),
				[a3] "=m" (cr0), [b3] "=m" (cr2), [c3] "=m" (cr3), [d3] "=m" (cr4)
			);
			printf("general protection fault!\n");
			printf("  eax: %08x - ebx: %08x - ecx: %08x - edx: %08x\n", eax, ebx, ecx, edx);
			printf("  esi: %08x - edi: %08x - esp: %08x - ebp: %08x\n", esi, edi, esp, ebp);
			printf("  cr0: %08x - cr2: %08x - cr3: %08x - cr4: %08x\n", cr0, cr2, cr3, cr4);
			printf("   ip: %04x     -  cs: %04x     -  sp: %04x     -  ss: %04x\n", frame->ip, frame->cs, frame->sp, frame->ss);
			printf("flags: %04x\n", frame->flags);
			abort();
		} else {
			
		}
	}

	__attribute__((interrupt)) void page_fault(struct interrupt_frame* frame) {
		if(__this_thread == nullptr) { // page fault in kernel
			vga_initialize();
			uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, cr0, cr2, cr3, cr4;
			asm("movl %%eax, %[a1] ;"
				"movl %%ebx, %[b1] ;"
				"movl %%ecx, %[c1] ;"
				"movl %%edx, %[d1] ;"
				"movl %%esi, %[a2] ;"
				"movl %%edi, %[b2] ;"
				"movl %%esp, %[c2] ;"
				"movl %%ebp, %[d2] ;"
				"movl %%cr0, %%eax ;"
				"movl %%eax, %[a3] ;"
				"movl %%cr2, %%eax ;"
				"movl %%eax, %[b3] ;"
				"movl %%cr3, %%eax ;"
				"movl %%eax, %[c3] ;"
				"movl %%cr4, %%eax ;"
				"movl %%eax, %[d3] ;"
				:
				[a1] "=m" (eax), [b1] "=m" (ebx), [c1] "=m" (ecx), [d1] "=m" (edx),
				[a2] "=m" (esi), [b2] "=m" (edi), [c2] "=m" (esp), [d2] "=m" (ebp),
				[a3] "=m" (cr0), [b3] "=m" (cr2), [c3] "=m" (cr3), [d3] "=m" (cr4)
			);
			printf("page fault!\n");
			printf("  eax: %08x - ebx: %08x - ecx: %08x - edx: %08x\n", eax, ebx, ecx, edx);
			printf("  esi: %08x - edi: %08x - esp: %08x - ebp: %08x\n", esi, edi, esp, ebp);
			printf("  cr0: %08x - cr2: %08x - cr3: %08x - cr4: %08x\n", cr0, cr2, cr3, cr4);
			printf("   ip: %04x     -  cs: %04x     -  sp: %04x     -  ss: %04x\n", frame->ip, frame->cs, frame->sp, frame->ss);
			printf("flags: %04x\n", frame->flags);
			abort();
		} else {
			
		}
	}
	/*__attribute__((interrupt)) void irq0(struct interrupt_frame* frame) {
		printf("irq0: ip: %i\n", frame->ip);
		printf("irq0: cs: %i\n", frame->cs);
		printf("irq0: flags: %i\n", frame->flags);
		printf("irq0: sp: %i\n", frame->sp);
		printf("irq0: ss: %i\n", frame->ss);
	}*/
	__attribute__((interrupt)) void irq1(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq2(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq3(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq4(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq5(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq6(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq7(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq8(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq9(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq10(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq11(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq12(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq13(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq14(struct interrupt_frame* frame) {}
	__attribute__((interrupt)) void irq15(struct interrupt_frame* frame) {}
}
