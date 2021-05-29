#include <kernel/arch/i386/isr.h>
#include <kernel/arch/i386/vga.h>

#include <kernel/thread.h>
#include <kernel/stdio.h>
#include <kernel/io.h>

#include <stdlib.h>

extern tty_t *ttys;
extern tty_t *active_tty;

extern "C" {

	__attribute__((interrupt)) void divide_by_zero(struct interrupt_frame* frame) {
		if(__this_thread == nullptr) { // division by zero in kernel
			printf("Division by zero!\n");
			abort();
		} else {
			
		}
	}

	__attribute__((interrupt)) void double_fault(struct interrupt_frame* frame) {
		if(__this_thread == nullptr) { // double fault in kernel
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
		if(__this_thread == nullptr) { // protection fault in kernel
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

	__attribute__((interrupt)) void irq1(struct interrupt_frame* frame) {
		if(!active_tty) { outb(0x20, 0x20); return; }
		if(!os_kb) { outb(0x20, 0x20); return; }
		if(!os_kb->driver) { outb(0x20, 0x20); return; }
		uint16_t ic = os_kb->poll_keyboard();
		if(ic != 0) {
			if((os_kb->left_control || os_kb->right_control) && os_kb->alt) {
				switch(ic) {
					case PS2_F1: { active_tty = &ttys[0]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F2: { active_tty = &ttys[1]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F3: { active_tty = &ttys[2]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F4: { active_tty = &ttys[3]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F5: { active_tty = &ttys[4]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F6: { active_tty = &ttys[5]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F7: { active_tty = &ttys[6]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F8: { active_tty = &ttys[7]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F9: { active_tty = &ttys[8]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F10: { active_tty = &ttys[9]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F11: { active_tty = &ttys[10]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
					case PS2_F12: { active_tty = &ttys[11]; active_tty->driver->flush(); outb(0x20, 0x20); return; }
				}
			}
			char c = os_kb->get_char(ic);
			if(ic == PS2_BACKSPACE) active_tty->ungetchar();
			else if(c != 0) {
				if(c == '\n') {
					active_tty->last_stdin = false;
					active_tty->stdin_removable = active_tty->stdin_pos + 1;
				} else if(!active_tty->last_stdin) {
					active_tty->last_stdin = true;
					active_tty->stdin_removable = active_tty->stdin_pos;
				}
				active_tty->putchar(c);
				active_tty->stdin_buf->push_back(c);
			}
		}
		outb(0x20, 0x20);
	}
	__attribute__((interrupt)) void irq2(struct interrupt_frame* frame) { outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq3(struct interrupt_frame* frame) { outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq4(struct interrupt_frame* frame) { outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq5(struct interrupt_frame* frame) { outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq6(struct interrupt_frame* frame) { outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq7(struct interrupt_frame* frame) { outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq8(struct interrupt_frame* frame) { outb(0xA0, 0x20); outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq9(struct interrupt_frame* frame) { outb(0xA0, 0x20); outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq10(struct interrupt_frame* frame) { outb(0xA0, 0x20); outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq11(struct interrupt_frame* frame) { outb(0xA0, 0x20); outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq12(struct interrupt_frame* frame) { outb(0xA0, 0x20); outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq13(struct interrupt_frame* frame) { outb(0xA0, 0x20); outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq14(struct interrupt_frame* frame) { outb(0xA0, 0x20); outb(0x20, 0x20); }
	__attribute__((interrupt)) void irq15(struct interrupt_frame* frame) { outb(0xA0, 0x20); outb(0x20, 0x20); }
}
