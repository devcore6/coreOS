ENTRY(bootstrap)
OUTPUT_FORMAT(elf64-x86_64)

SECTIONS {
	. = 0x0;

	. = 0xFFFFFFFF80000000

	.text : AT(ADDR(.text) - 0xFFFFFFFF80000000) {
		*(.text)
		
		*(.rodata*)
	}

	.data ALIGN (0x1000) : AT(ADDR(.data) - 0xFFFFFFFF80000000) {
		*(.data)
	}

	.bss : AT(ADDR(.bss) - 0xFFFFFFFF80000000) {
		_sbss = .;
		*(COMMON)
		*(.bss)
		_ebss = .;
	}
}